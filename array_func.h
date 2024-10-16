#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include "bi_def.h"
#include "rand.h"

/*
 * 함수명: array_init
 * 함수인자: UPDATE word* a, int IN word_len
 * 함수역할: array a 초기화
 */
msg array_init(UPDATE word* a, int IN word_len);

/*
 * 함수명: array_copy
 * 함수인자: OUT word* dst, IN word* src, IN int word_len
 * 함수역할: dst array에 src array 복사
 */
msg array_copy(OUT word* dst, IN word* src, IN int word_len);

/*
 * 함수명: array_rand
 * 함수인자: OUT word* dst, IN int word_len
 * 함수역할: dst array에 word_len만큼 임의의 값으로 할당
 */
msg array_rand(OUT word* dst, IN int word_len);

#endif  // ARRAY_FUNC_H