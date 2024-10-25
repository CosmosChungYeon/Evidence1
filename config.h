#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include "msg.h"

/** @brief Bit length of a word. 
 * 
 * @details Options are 8, 32, or 64 bits.
 */
#define WORD_BITLEN             32                   // OPTION: 8, 32, 64

/** @brief Length of a binary string, based on WORD_BITLEN. */
#define BINARY_STRING_LENGTH    (WORD_BITLEN)        // 2진수 문자열 길이

/** @brief Length of a hexadecimal string, calculated based on WORD_BITLEN. */
#define HEX_STRING_LENGTH       (WORD_BITLEN >> 2)   // 16진수 문자열 길이


/** @brief Random number generation method.
 * 
 * @details Set to 0 to use `rand()`, or 1 to use DRBG (Deterministic Random Bit Generator).
 */
#define USE_DRBG                1                    // 0: rand(), 1: DRBG


/** @typedef byte
 *  @brief Defines an 8-bit byte type.
 */
typedef uint8_t     byte;

/** @typedef msg
 *  @brief Defines the type for message codes.
 */                       
typedef uint32_t     msg;                            // MESSAGE type

/**
 * @brief Defines the `word` type based on `WORD_BITLEN`.
 * 
 * @details If `WORD_BITLEN` is 8, `word` is `uint8_t`. If 32, `word` is `uint32_t`.
 * If 64, `word` is `uint64_t`. Otherwise, defaults to `uint32_t` and issues a warning.
 */
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

/** 
 * @brief Calculates the byte length of a word array.
 * 
 * @param word_len Length of the word array.
 */
#define WORD_ARR_BYTELEN(word_len) (sizeof(word) * (word_len))   // WORD 배열의 BYTE 길이

#endif  // CONFIG_H