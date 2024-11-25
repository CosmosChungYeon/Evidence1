#ifndef BI_DEF_H
#define BI_DEF_H

#include "config.h"

/**
 * @struct bigint
 * @brief 큰 정수를 나타내는 구조체
 * 
 * 큰 정수에 대한 부호, 배열 길이, 배열에 대한 정보 저장
 */
typedef struct {
	int sign;		// 부호값
	int word_len;	// 워드 길이
	word* a;		// 워드 배열
} bigint;

#define OUT			// OUTPUT
#define IN			// INPUT
#define UPDATE		// UPDATE

#endif  // BI_DEF_H