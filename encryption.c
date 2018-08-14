#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "encryption.h"
#include "keccak-tiny.h"
#include "rijndael-alg-fst.h"

void xor_buf(const BYTE[], BYTE[], size_t);
void generate_key(const BYTE *, BYTE *);
void aes_256_cbc_pkcs7_file_encrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_file_decrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_encrypt(const BYTE in[], size_t in_len, BYTE out[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_decrypt(const BYTE in[], size_t in_len, BYTE out[], size_t *out_len, const BYTE key[], const BYTE iv[]);

void encrypt_file(const BYTE array[], const char in_filename[], const char out_filename[])
{
    BYTE key[AES_KEY_BYTES];
    generate_key(array, key);
    BYTE iv[AES_KEY_BYTES];
    sha3_256(iv, AES_KEY_BYTES, key, AES_KEY_BYTES);
    aes_256_cbc_pkcs7_file_encrypt(in_filename, out_filename, key, iv);
}

void decrypt_file(const BYTE array[], const char in_filename[], const char out_filename[])
{
    BYTE key[AES_KEY_BYTES];
    generate_key(array, key);
    BYTE iv[AES_KEY_BYTES];
    sha3_256(iv, AES_KEY_BYTES, key, AES_KEY_BYTES);
    aes_256_cbc_pkcs7_file_decrypt(in_filename, out_filename, key, iv);
}

void encrypt_raw(const BYTE array[], const BYTE in[], const size_t in_len, BYTE out[])
{ //out length = (in_len / AES_BLOCK_SIZE) * AES_BLOCK_SIZE + AES_BLOCK_SIZE
    BYTE key[AES_KEY_BYTES];
    generate_key(array, key);
    BYTE iv[AES_KEY_BYTES];
    sha3_256(iv, AES_KEY_BYTES, key, AES_KEY_BYTES);
    aes_256_cbc_pkcs7_encrypt(in, in_len, out, key, iv);
}

void decrypt_raw(const BYTE array[], const BYTE in[], const size_t in_len, BYTE out[], size_t *out_len)
{ //out len must be same as in_len. out_len will have actual len after unpad.
    BYTE key[AES_KEY_BYTES];
    generate_key(array, key);
    BYTE iv[AES_KEY_BYTES];
    sha3_256(iv, AES_KEY_BYTES, key, AES_KEY_BYTES);
    aes_256_cbc_pkcs7_decrypt(in, in_len, out, out_len, key, iv);
}

void aes_256_cbc_pkcs7_file_encrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[])
{
    FILE *in_file, *out_file;
    BYTE *in, *out;
    size_t out_len;
    long in_len;

    in_file = fopen(in_filename, "rb");
    out_file = fopen(out_filename, "wb");
    if (in_file == NULL || out_file == NULL)
    {
        return;
    }
    fseek(in_file, 0L, SEEK_END);
    in_len = ftell(in_file);
    rewind(in_file);
    in = (BYTE*)malloc(sizeof(BYTE) * in_len);
    out_len = (size_t)((in_len / AES_BLOCK_SIZE) * AES_BLOCK_SIZE + AES_BLOCK_SIZE);
    out = (BYTE*)malloc(sizeof(BYTE) * out_len);
    fread(in, sizeof(BYTE), (size_t)in_len, in_file);
    aes_256_cbc_pkcs7_encrypt(in, (size_t)in_len, out, key, iv);
    fwrite(out, sizeof(BYTE), out_len, out_file);
    fclose(in_file);
    fclose(out_file);
    free((void*)in);
    free((void*)out);
}

void aes_256_cbc_pkcs7_file_decrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[])
{
    FILE *in_file, *out_file;
    BYTE *in, *out;
    size_t out_len;
    long in_len;

    in_file = fopen(in_filename, "rb");
    out_file = fopen(out_filename, "wb");
    if (in_file == NULL || out_file == NULL)
    {
        return;
    }
    fseek(in_file, 0L, SEEK_END);
    in_len = ftell(in_file);
    rewind(in_file);
    in = (BYTE*)malloc(sizeof(BYTE) * in_len);
    out = (BYTE*)malloc(sizeof(BYTE) * in_len);
    fread(in, sizeof(BYTE), (size_t)in_len, in_file);
    aes_256_cbc_pkcs7_decrypt(in, (size_t)in_len, out, &out_len, key, iv);
    fwrite(out, sizeof(BYTE), out_len, out_file);
    fclose(in_file);
    fclose(out_file);
    free((void*)in);
    free((void*)out);
}

void aes_256_cbc_pkcs7_encrypt(const BYTE in[],
                               size_t in_len,
                               BYTE out[],
                               const BYTE key[],
                               const BYTE iv[]) { //out length = (in_len / AES_BLOCK_SIZE) * AES_BLOCK_SIZE + AES_BLOCK_SIZE
    BYTE buf_in[AES_BLOCK_SIZE], buf_out[AES_BLOCK_SIZE], iv_buf[AES_BLOCK_SIZE];
    size_t blocks, idx;
    u32 rk[4 * (MAXNR + 1)];
    int nr;

    blocks = in_len / AES_BLOCK_SIZE;
    memcpy(iv_buf, iv, AES_BLOCK_SIZE);
    nr = rijndaelKeySetupEnc(rk, key, AES_KEY_BITS);

    for (idx = 0; idx < blocks; idx++) {
        memcpy(buf_in, &in[idx * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
        xor_buf(iv_buf, buf_in, AES_BLOCK_SIZE);
        rijndaelEncrypt(rk, nr, buf_in, buf_out);
        memcpy(&out[idx * AES_BLOCK_SIZE], buf_out, AES_BLOCK_SIZE);
        memcpy(iv_buf, buf_out, AES_BLOCK_SIZE);
    }

    size_t last_block_len = in_len - blocks * AES_BLOCK_SIZE;
    size_t pad_count = AES_BLOCK_SIZE - last_block_len;
    memset(buf_in, (int) pad_count, AES_BLOCK_SIZE);
    memcpy(buf_in, &in[blocks * AES_BLOCK_SIZE], last_block_len);
    xor_buf(iv_buf, buf_in, AES_BLOCK_SIZE);
    rijndaelEncrypt(rk, nr, buf_in, buf_out);
    memcpy(&out[blocks * AES_BLOCK_SIZE], buf_out, AES_BLOCK_SIZE);
}

void aes_256_cbc_pkcs7_decrypt(const BYTE in[],
                               size_t in_len,
                               BYTE out[],
                               size_t *out_len,
                               const BYTE key[],
                               const BYTE iv[]) { //out len must be same as in_len. out_len will have actual len after unpad.
    BYTE buf_in[AES_BLOCK_SIZE], buf_out[AES_BLOCK_SIZE], iv_buf[AES_BLOCK_SIZE];
    size_t blocks, idx;
    u32 rk[4 * (MAXNR + 1)];
    int nr;

    blocks = in_len / AES_BLOCK_SIZE;
    memcpy(iv_buf, iv, AES_BLOCK_SIZE);
    nr = rijndaelKeySetupDec(rk, key, AES_KEY_BITS);

    for (idx = 0; idx < blocks; idx++) {
        memcpy(buf_in, &in[idx * AES_BLOCK_SIZE], AES_BLOCK_SIZE);
        rijndaelDecrypt(rk, nr, buf_in, buf_out);
        xor_buf(iv_buf, buf_out, AES_BLOCK_SIZE);
        memcpy(&out[idx * AES_BLOCK_SIZE], buf_out, AES_BLOCK_SIZE);
        memcpy(iv_buf, buf_in, AES_BLOCK_SIZE);
    }
    *out_len = in_len - out[in_len - 1];
}

void generate_key(const BYTE array[], BYTE key[]) {
    const int ARRAY_SIZE = 257;
    BYTE hash[AES_KEY_BYTES];
    sha3_256(hash, AES_KEY_BYTES, array, ARRAY_SIZE);
    memcpy(key, hash, AES_KEY_BYTES);
}

void xor_buf(const BYTE in[], BYTE out[], size_t len) {
    size_t idx;

    for (idx = 0; idx < len; idx++)
        out[idx] ^= in[idx];
}

void print_hex(BYTE bytes[], size_t len)
{
    char converted[len * 2 + 1];
    unsigned int i;
    for(i = 0; i < len; i++) {
        sprintf(&converted[i * 2], "%02X", bytes[i]);
    }
    printf("%s\n", converted);
}
