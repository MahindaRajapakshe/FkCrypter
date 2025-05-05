//
// Created by white on 5/5/2025.
//


#include "xxtea.h"

#define DELTA 0x9e3779b9

static void btea(uint32_t* v, int n, const uint32_t* k) {
    uint32_t y, z, sum;
    unsigned p, rounds, e;

    if (n > 1) {
        rounds = 6 + 52/n;
        sum = 0;
        z = v[n - 1];
        do {
            sum += DELTA;
            e = (sum >> 2) & 3;
            for (p = 0; p < (unsigned)(n - 1); p++) {
                y = v[p + 1];
                v[p] += ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (k[(p & 3) ^ e] ^ z));
                z = v[p];
            }
            y = v[0];
            v[n - 1] += ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (k[(p & 3) ^ e] ^ z));
        } while (--rounds);
    }
}

void xxtea_encrypt(uint8_t* data, size_t len, const uint8_t key[16]) {
    if (len % 4 != 0) return;
    btea((uint32_t*)data, len / 4, (uint32_t*)key);
}

void xxtea_decrypt(uint8_t* data, size_t len, const uint8_t key[16]) {
    if (len % 4 != 0) return;
    btea((uint32_t*)data, -(int)(len / 4), (uint32_t*)key);
}

