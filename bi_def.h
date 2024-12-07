#ifndef BI_DEF_H
#define BI_DEF_H

#include "config.h"

/**
 * @struct bigint
 * @brief Structure representing a large integer
 *
 * This structure stores information about the sign, word length, and array of a large integer
 */
typedef struct {
	int sign;		// Sign value
	int word_len;	// Word Length
	word* a;		// Array of words
} bigint;

#define OUT			// OUTPUT
#define IN			// INPUT
#define UPDATE		// UPDATE

#endif  // BI_DEF_H
