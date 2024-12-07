#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"

#define WORD_BITLEN             64                   // OPTION: 8, 32, 64
#define BINARY_STRING_LENGTH    (WORD_BITLEN)        // Binary string length
#define HEX_STRING_LENGTH       (WORD_BITLEN >> 2)   // Hexadecimal string length

#define USE_DRBG                0                    // 0: rand(), 1: DRBG

typedef uint8_t     byte;                            // byte
typedef uint32_t     msg;                            // MESSAGE type

/* Conditional definitions based on the word bit length (8, 32, or 64 bits) */
/* Sets type aliases, word and bit masks, format strings, and test word lengths accordingly */
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
#pragma message(UnSupportWordBitLenErrMsg)            // Unsupported word bit length
typedef uint32_t        word;
#define WORD_MASK       0x0000FFFF
#define MSB_BIT_MASK	0x80000000
#define FORMAT          "%08x"
#define TEST_WORD_LEN   32
#endif

#define WORD_ARR_BYTELEN(word_len) (sizeof(word) * (word_len))   // Byte length of WORD array

#define FLAG			20      // Karatsuba's FLAG word_len
#define RAND_CHOICE		1       // Random choice of word length (using in test.c)

/* For Diffie-Hellman. prime p = 1024-bit, q = 160-bit */
#define PRIME1024       "599a67c641f4698988a99e769ff894fffc4ae6c6c7ef558b3d02194b2975e297fbb78e450190e5006de413d57e5f71586c53a055d4bd8f84e696be39ce217bdc0e5740a2d3ff45da38190b7ce9e3abefd3a935f381a96f01c7582cfc1602d53043b38e2f543f5c5ee9d921bcb51d978eb8db3abcc2b6d9e54d5dd46acf604505"
#define PRIME160        "93ee4cd258f13c51a512e87e3e1a9106db935e39"

#endif  // CONFIG_H
