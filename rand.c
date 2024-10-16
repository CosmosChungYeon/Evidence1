#include "rand.h"

/*
 * 함수명: DRBG
 * 함수인자: -
 * 함수역할: DRBG로 임의의 한 바이트 반환
 */
byte DRBG() {
    return rand() % 0xff;   // 미완
}

/*
 * 함수명: byte_rand
 * 함수인자: -
 * 함수역할: 임의의 한 바이트 반환
 * OPTION: rand() 또는 DRBG(미완)
 */
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