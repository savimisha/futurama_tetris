
#ifndef __KEY_H__
#define __KEY_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define AES_BLOCK_SIZE 16
#define AES_KEY_BITS 256
#define AES_KEY_BYTES 32

typedef unsigned char BYTE;

void encrypt_file(const BYTE array[], const char in_filename[], const char out_filename[]);
void decrypt_file(const BYTE array[], const char in_filename[], const char out_filename[]);

void encrypt_raw(const BYTE array[], const BYTE in[], const size_t in_len, BYTE out[]);
void decrypt_raw(const BYTE array[], const BYTE in[], const size_t in_len, BYTE out[], size_t *out_len);

void aes_256_cbc_pkcs7_file_encrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_file_decrypt(const char in_filename[], const char out_filename[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_encrypt(const BYTE in[], size_t in_len, BYTE out[], const BYTE key[], const BYTE iv[]);
void aes_256_cbc_pkcs7_decrypt(const BYTE in[], size_t in_len, BYTE out[], size_t *out_len, const BYTE key[], const BYTE iv[]);

#ifdef __cplusplus
}
#endif
#endif //__KEY_H__
