#include "int_to_string.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    int int_to_string_VERSION() {
        return 1;
    }

    // https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
    static char *int_to_string_helper(char *dest, size_t n, long x) {
        if (n == 0) {
            return NULL;
        }
        if (x <= -10) {
            dest = int_to_string_helper(dest, n - 1, x / 10);
            if (dest == NULL) return NULL;
        }
        *dest = (char)('0' - x % 10);
        return dest + 1;
    }

    char *int_to_string(char *dest, size_t n, long x) {
        char *p = dest;
        if (n == 0) {
            return NULL;
        }
        n--;
        if (x < 0) {
            if (n == 0) return NULL;
            n--;
            *p++ = '-';
        }
        else {
            x = -x;
        }
        p = int_to_string_helper(p, n, x);
        if (p == NULL) return NULL;
        *p = 0;
        return dest;
    }

    
    // based on code from https://stackoverflow.com/questions/3464194/how-can-i-convert-an-integer-to-a-hexadecimal-string-in-c
    char *int_to_base(char *dest, unsigned long n, int base)
    {
        char *outbuf = dest;
        int i = 12;
        int j = 0;

        do {
            outbuf[i] = "0123456789ABCDEF"[n % base];
            i--;
            n = n / base;
        } while (n > 0);


        while (++i < 13) {
            outbuf[j++] = outbuf[i];
        }

        outbuf[j] = 0;
        return dest;
    }

    char *int_to_hex(char *dest, unsigned long n)
    {
        return int_to_base(dest, n, 16);
    }

    char *int_to_dec(char *dest, unsigned long n)
    {
        return int_to_base(dest, n, 10);
    } 
    
    char *int_to_bin(char *dest, unsigned long n)
    {
        return int_to_base(dest, n, 2);
    }

#ifdef __cplusplus
}
#endif    