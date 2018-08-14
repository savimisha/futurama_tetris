#include "sha.h"
#include "sha3.h"

typedef unsigned char BYTE;

QByteArray SHA::sha3(QByteArray data) {
    auto *out = new BYTE[32];
    sha3_ctx_t ctx;
    sha3_init(&ctx, 32);
    sha3_update(&ctx, data.data(), data.length());
    sha3_final(out, &ctx);
    QByteArray result(reinterpret_cast<char*>(out), 32);
    delete[] out;
    return result;
}
