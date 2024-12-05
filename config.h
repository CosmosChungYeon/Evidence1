#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"

#define WORD_BITLEN             64                   // OPTION: 8, 32, 64
#define BINARY_STRING_LENGTH    (WORD_BITLEN)        // 2진수 문자열 길이
#define HEX_STRING_LENGTH       (WORD_BITLEN >> 2)   // 16진수 문자열 길이

#define USE_DRBG                0                    // 0: rand(), 1: DRBG

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

#define FLAG			20
#define RAND_CHOICE		0

#define PRIME1024       "599a67c641f4698988a99e769ff894fffc4ae6c6c7ef558b3d02194b2975e297fbb78e450190e5006de413d57e5f71586c53a055d4bd8f84e696be39ce217bdc0e5740a2d3ff45da38190b7ce9e3abefd3a935f381a96f01c7582cfc1602d53043b38e2f543f5c5ee9d921bcb51d978eb8db3abcc2b6d9e54d5dd46acf604505"
#define PRIME256        "93ee4cd258f13c51a512e87e3e1a9106db935e39"
#define GENERATOR       "1371a16c9a5547424683c96456460b9a75b7e8b667452d33c365ea5f85e9e79a6b277b1eef45e56bb5b420b93f1a5af90b3784531519f4937577d839512d53b802a41afc2921058b2f1ea3c482e15073d2d381a2ae3452f4bdecd9483e9eb52dcf60e926b79e74a85f6b232065bad4eda418ece4f1a02a79665ff2cc6747ef5b"
#endif  // CONFIG_H