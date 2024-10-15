#include "rand.h"

byte DRBG() {
    return rand() % 0xff;
}

byte byte_rand() {
#if   USE_DRBG == 0
    return rand() % 0xff;
#elif USE_DRBG == 1
    return DRBG();
#else
    return 0;
#endif
}