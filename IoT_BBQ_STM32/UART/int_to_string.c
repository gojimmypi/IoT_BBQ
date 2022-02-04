#include "int_to_string.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    int int_to_string_VERSION() {
        return 1;
    }

   
    // based on code from https://stackoverflow.com/questions/3464194/how-can-i-convert-an-integer-to-a-hexadecimal-string-in-c
    // see also           https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
    // see also https://github.com/kevmuret/libhex/blob/master/hex.c
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