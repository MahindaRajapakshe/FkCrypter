#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void xxtea_encrypt(uint8_t* data, size_t len, const uint8_t key[16]);
void xxtea_decrypt(uint8_t* data, size_t len, const uint8_t key[16]);

#ifdef __cplusplus
}
#endif
