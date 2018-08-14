#include "aes.h"
#include "encryption.h"

QByteArray AES::encrypt(QByteArray data){
   auto enc_len = (data.length() / AES_BLOCK_SIZE) * AES_BLOCK_SIZE + AES_BLOCK_SIZE;
   auto *enc_text = new BYTE[enc_len];
   const BYTE in[] = {
       0x50, 0xf0, 0x0c, 0x24, 0xa1, 0xe5, 0x58, 0x2e, 0x55, 0x0b, 0x66, 0xca, 0x04, 0xf2, 0x90, 0x1b,
       0xde, 0x3f, 0x5d, 0xfd, 0x38, 0xf0, 0x27, 0x3d, 0x10, 0x6e, 0x98, 0x19, 0x04, 0x3d, 0xa5, 0x85,
       0x6c, 0xc6, 0x99, 0x45, 0x67, 0xce, 0x5c, 0xd4, 0xa3, 0xbe, 0x60, 0x7f, 0xb5, 0x84, 0xd6, 0x18,
       0x9c, 0x09, 0x86, 0xb1, 0x81, 0xc0, 0x7d, 0x33, 0xff, 0x0b, 0xee, 0x34, 0xf8, 0x10, 0xa6, 0x60,
       0xa4, 0xd8, 0xaa, 0xb2, 0x94, 0xd4, 0x7a, 0xe1, 0x78, 0x61, 0x8e, 0x4f, 0x4c, 0x5b, 0x40, 0x3b,
       0x43, 0xd2, 0x3c, 0xdc, 0xc7, 0xc2, 0xfa, 0x42, 0x43, 0xef, 0xe7, 0x2d, 0x1d, 0x51, 0x93, 0x4d,
       0x79, 0xdc, 0x33, 0xcf, 0x0c, 0x69, 0x10, 0x0c, 0x56, 0x50, 0xef, 0x91, 0xc6, 0xf9, 0xa8, 0x51,
       0xe7, 0x8f, 0x20, 0xad, 0xc6, 0xe7, 0xa7, 0xd7, 0x1c, 0xf6, 0xc8, 0x0a, 0xa4, 0x72, 0xa0, 0x2a,
       0xa0, 0x43, 0xdb, 0x6e, 0xc5, 0x80, 0x09, 0x0b, 0x70, 0x60, 0x90, 0xfb, 0xf3, 0x85, 0x14, 0x4e,
       0x14, 0x5e, 0xa7, 0xa3, 0x87, 0xf7, 0xdc, 0x4b, 0xe5, 0xfb, 0x4d, 0xdf, 0xf5, 0xe5, 0x07, 0xa8,
       0xcb, 0x89, 0xc0, 0xda, 0xe6, 0x10, 0x1b, 0xa2, 0x63, 0x73, 0x02, 0x8e, 0x88, 0x2f, 0xcf, 0x5d,
       0x18, 0x06, 0xf3, 0xcc, 0x0e, 0x87, 0x78, 0x51, 0x05, 0x55, 0xdc, 0x0d, 0x01, 0x68, 0xc5, 0xf3,
       0xad, 0x5e, 0xbd, 0xb8, 0x79, 0x1c, 0x43, 0x4f, 0x25, 0x6a, 0xd3, 0x2b, 0x44, 0x61, 0x28, 0xc6,
       0x83, 0x94, 0x2c, 0xbe, 0xfa, 0xc2, 0x0a, 0x30, 0x65, 0x44, 0xa1, 0xfb, 0x49, 0xd9, 0x99, 0xa2,
       0x85, 0xb9, 0x06, 0x80, 0x6a, 0x7e, 0x92, 0x24, 0x3d, 0x94, 0x94, 0x8f, 0x2d, 0xe8, 0x02, 0x18,
       0xf6, 0x8e, 0x61, 0xa7, 0x63, 0x43, 0x67, 0x68, 0x89, 0x62, 0x67, 0x73, 0x28, 0x85, 0x80, 0xd3,
       0xe1
   };
   encrypt_raw(in, reinterpret_cast<BYTE*>(data.data()), data.length(), enc_text);
   auto result = QByteArray(reinterpret_cast<char*>(enc_text), enc_len);
   delete[] enc_text;
   return result;
}

QByteArray AES::decrypt(QByteArray data){
    auto *dec_text = new BYTE[data.length()];
    const BYTE in[] = {
        0x50, 0xf0, 0x0c, 0x24, 0xa1, 0xe5, 0x58, 0x2e, 0x55, 0x0b, 0x66, 0xca, 0x04, 0xf2, 0x90, 0x1b,
        0xde, 0x3f, 0x5d, 0xfd, 0x38, 0xf0, 0x27, 0x3d, 0x10, 0x6e, 0x98, 0x19, 0x04, 0x3d, 0xa5, 0x85,
        0x6c, 0xc6, 0x99, 0x45, 0x67, 0xce, 0x5c, 0xd4, 0xa3, 0xbe, 0x60, 0x7f, 0xb5, 0x84, 0xd6, 0x18,
        0x9c, 0x09, 0x86, 0xb1, 0x81, 0xc0, 0x7d, 0x33, 0xff, 0x0b, 0xee, 0x34, 0xf8, 0x10, 0xa6, 0x60,
        0xa4, 0xd8, 0xaa, 0xb2, 0x94, 0xd4, 0x7a, 0xe1, 0x78, 0x61, 0x8e, 0x4f, 0x4c, 0x5b, 0x40, 0x3b,
        0x43, 0xd2, 0x3c, 0xdc, 0xc7, 0xc2, 0xfa, 0x42, 0x43, 0xef, 0xe7, 0x2d, 0x1d, 0x51, 0x93, 0x4d,
        0x79, 0xdc, 0x33, 0xcf, 0x0c, 0x69, 0x10, 0x0c, 0x56, 0x50, 0xef, 0x91, 0xc6, 0xf9, 0xa8, 0x51,
        0xe7, 0x8f, 0x20, 0xad, 0xc6, 0xe7, 0xa7, 0xd7, 0x1c, 0xf6, 0xc8, 0x0a, 0xa4, 0x72, 0xa0, 0x2a,
        0xa0, 0x43, 0xdb, 0x6e, 0xc5, 0x80, 0x09, 0x0b, 0x70, 0x60, 0x90, 0xfb, 0xf3, 0x85, 0x14, 0x4e,
        0x14, 0x5e, 0xa7, 0xa3, 0x87, 0xf7, 0xdc, 0x4b, 0xe5, 0xfb, 0x4d, 0xdf, 0xf5, 0xe5, 0x07, 0xa8,
        0xcb, 0x89, 0xc0, 0xda, 0xe6, 0x10, 0x1b, 0xa2, 0x63, 0x73, 0x02, 0x8e, 0x88, 0x2f, 0xcf, 0x5d,
        0x18, 0x06, 0xf3, 0xcc, 0x0e, 0x87, 0x78, 0x51, 0x05, 0x55, 0xdc, 0x0d, 0x01, 0x68, 0xc5, 0xf3,
        0xad, 0x5e, 0xbd, 0xb8, 0x79, 0x1c, 0x43, 0x4f, 0x25, 0x6a, 0xd3, 0x2b, 0x44, 0x61, 0x28, 0xc6,
        0x83, 0x94, 0x2c, 0xbe, 0xfa, 0xc2, 0x0a, 0x30, 0x65, 0x44, 0xa1, 0xfb, 0x49, 0xd9, 0x99, 0xa2,
        0x85, 0xb9, 0x06, 0x80, 0x6a, 0x7e, 0x92, 0x24, 0x3d, 0x94, 0x94, 0x8f, 0x2d, 0xe8, 0x02, 0x18,
        0xf6, 0x8e, 0x61, 0xa7, 0x63, 0x43, 0x67, 0x68, 0x89, 0x62, 0x67, 0x73, 0x28, 0x85, 0x80, 0xd3,
        0xe1
    };
    size_t out_len;
    decrypt_raw(in, reinterpret_cast<BYTE*>(data.data()), data.length(), dec_text, &out_len);
    auto result = QByteArray(reinterpret_cast<char*>(dec_text), out_len);
    delete[] dec_text;
    return result;
}
