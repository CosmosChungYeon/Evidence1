#include "rand.h"

byte DRBG() {
    return rand() % 0xff;   // 미완
}

byte byte_rand() {
    // USE_DRBG 값에 따른 함수 선정
#if   USE_DRBG == 0
    return rand() % 0xff;   // stdlib 내장 rand() 사용
#elif USE_DRBG == 1
    return DRBG();
#else
    fprintf(stderr, UnSupportUseDRBGValErrMsg);
    return DRBG();
#endif
}