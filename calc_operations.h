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
msg bi_add_ABc(OUT word* C, IN word* A, IN word* B, IN int c);

/**
 * @brief carry와 두 개의 부호가 같은 큰 정수의 덧셈(word_len(A) >= word_len(B))
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B);


//msg bi_addc_using_mul(OUT bigint** C, IN bigint** A, IN bigint** B);

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
msg bi_sub_AbB(OUT word* C, IN word* A, IN int b, IN word* B);

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


/**
 * @brief 단일 워드 곱셈
 *
 * @param[out] C[2] 단일 워드 곱셈 결과 반환
 * @param[in] A 첫 번째 단일 워드
 * @param[in] B 두 번째 단일 워드
 * @return 성공 실패 여부 반환
 */
msg bi_mul_AB(OUT word C[2], IN word* A, IN word* B);

/**
 * @brief textbook 곱셈
 *
 * @param[out] C 워드 곱셈 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_textbook_mulc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief improved textbook 곱셈
 *
 * @param[out] C 워드 곱셈 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_improved_textbook_mulc(bigint** C, bigint** A, bigint** B);

/**
 * @brief karatsuba 곱셈
 *
 * @param[out] C 워드 곱셈 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_karatsuba_mulc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief 부호 고려 곱셈
 *
 * @param[out] C 워드 곱셈 결과 큰 정수의 이중 포인터
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_mul(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief long division bit 나눗셈
 *
 * @param[out] Q 나눗셈 결과 몫 큰 정수의 이중 포인터
 * @param[out] R 나눗셈 결과 나머지 큰 정수의 이중 포인터
 * @param[in] A dividend 첫 번째 큰 정수의 이중 포인터
 * @param[in] B divisor 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_long_div(OUT bigint** Q, OUT bigint** R, IN bigint** A, IN bigint** B);

/**
 * @brief 부호 고려 나눗셈
 *
 * @param[out] Q 나눗셈 결과 몫 큰 정수의 이중 포인터
 * @param[out] R 나눗셈 결과 나머지 큰 정수의 이중 포인터
 * @param[in] A dividend 첫 번째 큰 정수의 이중 포인터
 * @param[in] B divisor 두 번째 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_div(OUT bigint** Q, OUT bigint** R, IN bigint** A, IN bigint** B);

/**
 * @brief left to right modular exponentiation (C = X^N mod M)
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] X 대상 큰 정수의 이중 포인터
 * @param[in] N 지수 큰 정수의 이중 포인터
 * @param[in] M modular 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_l2r_mod_exp(OUT bigint** C, IN bigint** X, IN bigint** N, IN bigint** M);

/**
 * @brief right to left modular exponentiation (C = X^N mod M)
 *
 * @param[out] C 결과 큰 정수의 이중 포인터
 * @param[in] X 대상 큰 정수의 이중 포인터
 * @param[in] N 지수 큰 정수의 이중 포인터
 * @param[in] M modular 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_r2l_mod_exp(OUT bigint** C, IN bigint** X, IN bigint** N, IN bigint** M);

/**
 * @brief barrett reduction (A의 워드 길이 = N의 워드 길이의 두 배)
 *
 * @param[out] R reduction 결과 큰 정수의 이중 포인터
 * @param[in] A reduction 대상 큰 정수의 이중 포인터
 * @param[in] N modular 큰 정수의 이중 포인터
 * @param[in] T 사전 계산 가능한 값 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
// 한계: word 8bit 시 test에서 워드 길이가 A 또는 N이 1씩 감소해서 에러 발생
msg bi_barrett_red(OUT bigint** R, IN bigint** A, IN bigint** N, IN bigint** T);

#endif  // CALC_OPERATIONS_H