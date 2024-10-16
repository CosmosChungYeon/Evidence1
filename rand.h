#ifndef RAND_H
#define RAND_H

#include "config.h"
#include "stdlib.h"


/*
 * 함수명: DRBG
 * 함수인자: -
 * 함수역할: DRBG로 임의의 한 바이트 반환
 */
byte DRBG();

/*
 * 함수명: byte_rand
 * 함수인자: -
 * 함수역할: 임의의 한 바이트 반환
 * OPTION: rand() 또는 DRBG(미완)
 */
byte byte_rand();

#endif  // RAND_H