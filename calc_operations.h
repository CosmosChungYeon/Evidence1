#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include <string.h>

/**
 * @brief carry와 두 배열의 덧셈
 *
 * @param[out] C 결과 배열의 포인터
 * @param[in] A 첫 번째 배열
 * @param[in] B 두 번째 배열
 * @param[in] c 이전 연산의 carry 비트
 * @return 덧셈 후 carry 비트 반환
 */
msg bi_add_ABc(OUT word* C, IN word A, IN word B, IN int c);

/**
 * @brief carry와 두 개의 부호가 같은 큰 정수의 덧셈(word_len(A) >= word_len(B))
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief 두 개의 큰 정수의 덧셈
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief A 배열에서 B 배열과 borrow 뺄셈
 *
 * @param[out] C 결과 배열의 포인터
 * @param[in] A 첫 번째 배열
 * @param[in] b 이전 연산의 borrow 비트
 * @param[in] B 두 번째 배열(뺄 배열)
 * @return 뺄셈 후 borrow 비트 반환
 */
msg bi_sub_AbB(OUT word* C, IN word A, IN int b, IN word B);

/**
 * @brief borrow와 두 개의 부호가 같은 큰 정수의 뺄셈(A >= B > 0)
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_subc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief 두 개의 큰 정수의 뺄셈
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B);

#endif  // CALC_OPERATIONS_H