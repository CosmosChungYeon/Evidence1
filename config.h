#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"


#define WORD_BITLEN             32                   // OPTION: 8, 32, 64
#define BINARY_STRING_LENGTH    (WORD_BITLEN)        // 2진수 문자열 길이
#define HEX_STRING_LENGTH       (WORD_BITLEN >> 2)   // 16진수 문자열 길이

#define USE_DRBG                1                    // 0: rand(), 1: DRBG

typedef uint8_t     byte;                 
typedef uint32_t     msg;                            // MESSAGE type

#if    WORD_BITLEN == 8
typedef uint8_t     word;
#elif  WORD_BITLEN == 32
typedef uint32_t    word;
#elif  WORD_BITLEN == 64
typedef uint64_t    word;
#else
#pragma message(UnSupportWordBitLenErrMsg) // 지원하지 않는 word bitlen
typedef uint32_t    word;
#endif

#define WORD_ARR_BYTELEN(word_len) (sizeof(word) * (word_len))   // WORD 배열의 BYTE 길이

#endif  // CONFIG_H