#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"

#define WORD_BITLEN             64                   // OPTION: 8, 32, 64
#define BINARY_STRING_LENGTH    (WORD_BITLEN)        // 2진수 문자열 길이
#define HEX_STRING_LENGTH       (WORD_BITLEN >> 2)   // 16진수 문자열 길이

#define USE_DRBG                1                    // 0: rand(), 1: DRBG

typedef uint8_t     byte;
typedef uint32_t     msg;                            // MESSAGE type

#if    WORD_BITLEN == 8
typedef uint8_t         word;
#define WORD_MASK       0x0F
#define MSB_BIT_MASK	0x80
#define FORMAT          "%02x"
#define TEST_WORD_LEN   128
#elif  WORD_BITLEN == 32
typedef uint32_t        word;
#define WORD_MASK       0x0000FFFF
#define MSB_BIT_MASK	0x80000000
#define FORMAT          "%08x"
#define TEST_WORD_LEN   32
#elif  WORD_BITLEN == 64
typedef uint64_t        word;
#define WORD_MASK       0x00000000FFFFFFFF
#define MSB_BIT_MASK	0x8000000000000000
#define FORMAT          "%016llx"
#define TEST_WORD_LEN   16
#else
#pragma message(UnSupportWordBitLenErrMsg) // 지원하지 않는 word bitlen
typedef uint32_t        word;
#define WORD_MASK       0x0000FFFF
#define MSB_BIT_MASK	0x80000000
#define FORMAT          "%08x"
#define TEST_WORD_LEN   32
#endif

#define WORD_ARR_BYTELEN(word_len) (sizeof(word) * (word_len))   // WORD 배열의 BYTE 길이

#define FLAG			10
#define RAND_CHOICE		0

#define PRIME2048       "807de6a5a4a3a189b7ee2dd0ea37840cdd208d70a2c56fb6f3b797639b36b9b3138008c4f6c1823a9af8c0eff462d18471c95d8d9cd1ee280d5632cba33c37c2f69f1850873d903123b590009b7fe4aab3200b7256874bffbeabda9fdcdabedf6dc14d51a4ae0de627910ebbfa196d0cc7b79be976f191723610f556955d0874062758d32487cadbb758db89d72a3398d977969d7ab29a5072a6a7e020d4c7e439669cb919f81a5fca51888fad990c09b5bae4287443cb4d4c63c6bbaffc051611318796de99e88f39e5e1c2ed1cb31e3a930a79cbf8f84614145fafaac3c4908ef24d0efd687d80093cfa7439663ce4b9c491ddefa841b83a4b141c2aea324d"

#endif  // CONFIG_H