#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"

#define WORD_BIT                32  // OPTION: 8, 32, 64
#define BINARY_STRING_LENGTH    WORD_BIT          // 2진수 문자열 길이
#define HEX_STRING_LENGTH       (WORD_BIT >> 2)   // 16진수 문자열 길이

typedef uint8_t     byte;
typedef uint32_t     msg;

#if    WORD_BIT == 8
typedef uint8_t   word;
#elif  WORD_BIT == 32
typedef uint32_t  word;
#elif  WORD_BIT == 64
typedef uint64_t  word;
#else
#error Error: Unsupported word bit (only 8, 32, 64)
#endif

#endif  // CONFIG_H