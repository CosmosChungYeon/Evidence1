#ifndef BI_DEF_H
#define BI_DEF_H

#include "config.h"

/**
 * @struct bigint
 * @brief Structure representing a big integer.
 * 
 * This structure holds information about the sign, word length, and word array 
 * for a large integer.
 */
typedef struct {
	int sign;		// 부호값
	int word_len;	// 워드 길이
	word* a;		// 워드 배열
} bigint;

/** @def OUT
 *  @brief Macro indicating output parameter.
 */
#define OUT			// OUTPUT

/** @def IN
 *  @brief Macro indicating input parameter.
 */
#define IN			// INPUT

/** @def UPDATE
 *  @brief Macro indicating update parameter.
 */
#define UPDATE		// UPDATE

#endif  // BI_DEF_H