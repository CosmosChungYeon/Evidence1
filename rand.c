#include "rand.h"

byte DRBG() {
    return rand() % 0xff;   // This feature is not yet fully implemented.
}

byte byte_rand() {
    /* Choose the function based on the USE_DRBG value */
#if   USE_DRBG == 0
    return rand() % 0xff;   // Use stdlib's rand() function
#elif USE_DRBG == 1
    return DRBG();          // Use DRBG
#else
    fprintf(stderr, UnSupportUseDRBGValErrMsg);
    return DRBG();
#endif
}