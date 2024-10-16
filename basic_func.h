#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include "bi_def.h"

/*
 * 함수명: bi_set_from_array
 * 함수인자: OUT bigint** dst, IN int sign, IN int word_len, IN const word* a
 * 함수역할: sign, word_len, array로부터 bigint setting
 */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a);

/*
 * 함수명: bi_set_from_string
 * 함수인자: OUT bigint** dst, IN const char* int_str, IN int base
 * 함수역할: base, string으로부터 bigint setting (2진수, 10진수, 16진수)
 * 입력 문자열: 음수면 "-" 양수면 "" + "진수표현문자열"
 */
msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base);

/*
 * 함수명: bi_get_random
 * 함수인자: OUT bigint** dst, IN int word_len
 * 함수역할: 임의의 값으로 word_len만큼 bigint 초기화
 */
msg bi_get_random(OUT bigint** dst, IN int word_len);

/*
 * 함수명: bi_print
 * 함수인자: IN const bigint* dst, IN int base
 * 함수역할: bigint를 base에 맞게 출력 (2진수, 10진수, 16진수)
 */
msg bi_print(IN const bigint* dst, IN int base); // const**

/*
 * 함수명: bi_new
 * 함수인자: OUT bigint** dst, IN int word_len
 * 함수역할: bigint를 word_len만큼 초기화
 */
msg bi_new(OUT bigint** dst, IN int word_len);

/*
 * 함수명: bi_delete
 * 함수인자: UPDATE bigint** dst
 * 함수역할: bigint의 메모리를 해제
 */
msg bi_delete(UPDATE bigint** dst);

/*
 * 함수명: bi_refine
 * 함수인자: UPDATE bigint* dst
 * 함수역할: bigint의 메모리를 재할당 (word_len 줄이는 용도)
 */
msg bi_refine(UPDATE bigint* dst);

/*
 * 함수명: bi_assign
 * 함수인자: UPDATE bigint** dst, IN const bigint* src
 * 함수역할: bigint* dst에 src를 복사(대입, *dst = src)
 */
msg bi_assign(UPDATE bigint** dst, IN const bigint* src);

#endif  // BASIC_FUNC_H