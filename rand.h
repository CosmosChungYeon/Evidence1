#ifndef RAND_H
#define RAND_H

#include "config.h"
#include "stdlib.h"

/**
 * @brief DRBG를 사용하여 무작위 바이트 생성
 *
 * @return DRBG에서 생성된 무작위 바이트 반환
 * @note 이 기능은 아직 미완성
 */
byte DRBG();

/**
 * @brief 무작위 바이트 반환
 *
 * @details 'USE_DRBG' 옵션에 따라 이 함수는 'stdlib'의 'rand()'를 사용하거나 'DRBG()' 함수를 사용
 *
 * @return 무작위 바이트 반환
 */
byte byte_rand();

#endif  // RAND_H