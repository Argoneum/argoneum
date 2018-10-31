#ifndef SKEIN_H
#define SKEIN_H

#include "sha256_y.h"

using namespace sha256_y;

inline void
skein_hash(const char* input, char* output, uint32_t len)
{
        char temp[64];

        sph_skein512_context ctx_skien;
        sph_skein512_init(&ctx_skien);
        sph_skein512(&ctx_skien, input, len);
        sph_skein512_close(&ctx_skien, &temp);

        SHA256_CTX ctx_sha256;
        SHA256_Init(&ctx_sha256);
        SHA256_Update(&ctx_sha256, &temp, 64);
        SHA256_Final((unsigned char*) output, &ctx_sha256);
}

#endif
