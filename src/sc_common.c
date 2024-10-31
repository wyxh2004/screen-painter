#include "sc_common.h"

int delay(int ms) __attribute__((weak));

int delay(int ms)
{
    volatile int i;
    while (ms--) {
        for (i = 0; i < 10000; i++)
            ;
    }
    return 0;
}