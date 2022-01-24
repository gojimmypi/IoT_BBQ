#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    int int_to_string_VERSION();

    char *int_to_string(char *dest, size_t n, long x);
    char *int_to_hex(char *dest, unsigned long n);

#ifdef __cplusplus
}
#endif