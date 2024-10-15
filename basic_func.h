#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include "bi_def.h"

/* array로부터 bigint Set */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN word* a);

/* 2진수, 16진수 string으로부터 bigint Set */
msg bi_set_from_string(OUT bigint** dst, IN char* int_str, IN int base);

/* 임의의 값으로 bigint 초기화 */
/* 마지막 원소가 nonzero여야 함 */
msg bi_get_random(OUT bigint** dst, IN int sign, IN int word_len);

/* 2진수, 10진수, 16진수 출력 */
msg bi_print(const bigint* dst, IN int base); // const**

/* 초기화 */
msg bi_new(OUT bigint** dst, IN int word_len);

/* 메모리 해제 */
msg bi_delete(UPDATE bigint** dst);

/* 메모리 재할당 */
msg bi_refine(UPDATE bigint* dst);

/* 대입 */
msg bi_assign(UPDATE bigint** dst, IN bigint* src);

#endif  // BASIC_FUNC_H