#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include <stdio.h>
#include <stdint.h>

typedef uint32_t msg;	// config.h
typedef uint32_t word;

// constant.h
#define NON_NEGATIVE 0	// 양수
#define NEGATIVE 	 1	// 음수

/* bigint 구조체 */ // bi_def.c
typedef struct {
	int sign;		// 부호값
	int word_len;	// 워드 길이
	word* a;		// 워드 배열
} bigint;

typedef bigint* pbigint; // 참고

#define OUT
#define IN

/* array로부터 bigint Set */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN word* a);

/* 2진수, 16진수 string으로부터 bigint Set */
msg bi_set_from_string(bigint** dst, char* int_str, int base);

/* 임의의 값으로 bigint 초기화 */
/* 마지막 원소가 nonzero여야 함 */
msg bi_get_random(bigint** dst, int word_len);

/* 2진수, 10진수, 16진수 출력 */
msg bi_print(const bigint* dst, int base); // const**

/* 초기화 */
msg bi_new(bigint** dst, int word_len);

/* 메모리 해제 */
msg bi_delete(bigint** dst);

/* 메모리 재할당 */
msg bi_refine(bigint* dst);

/* 대입 */
msg bi_assign(bigint** dst, bigint* src);

#endif  // BASIC_FUNC_H