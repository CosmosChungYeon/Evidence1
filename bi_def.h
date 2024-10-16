#ifndef BI_DEF_H
#define BI_DEF_H

#include "config.h"

/* bigint 구조체 */
typedef struct {
	int sign;		// 부호값
	int word_len;	// 워드 길이
	word* a;		// 워드 배열
} bigint;

#define OUT			// OUTPUT 
#define IN			// INPUT
#define UPDATE		// UPDATE

#endif  // BI_DEF_H