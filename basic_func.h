#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include "bi_def.h"
#include "array_func.h"

/**
 * @brief 주어진 부호, 배열 길이, 배열에서 큰 정수 설정
 * 
 * @param[out] dst 대상 큰 정수의 이중 포인터
 * @param[in] sign 부호
 * @param[in] word_len 배열의 길이
 * @param[in] a 배열
 * @return 성공 실패 여부 반환
 */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a);

/**
 * @brief 지정된 진수의 문자열에서 큰 정수 설정
 * 
 * @param[out] dst 대상 큰 정수의 이중 포인터
 * @param[in] int_str 문자열
 * @param[in] base 진수(2, 10, 16)
 * @note 음수이면 문자열은 "-"로 시작
 * @return 성공 실패 여부 반환
 */
msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base);

/**
 * @brief 무작위 값으로 지정된 배열 길이의 큰 정수 초기화
 * 
 * @param[out] dst 대상 큰 정수의 이중 포인터
 * @param[in] word_len 배열의 길이
 * @return 성공 실패 여부 반환
 */
msg bi_get_random(OUT bigint** dst, IN int word_len);

/**
 * @brief 지정된 진수로 큰 정수 출력
 * 
 * @param[in] dst 대상 큰 정수의 포인터
 * @param[in] base 진수(2, 10, 16)
 * @return 성공 실패 여부 반환
 */
msg bi_print(IN const bigint* dst, IN int base); // const**

/**
 * @brief 지정된 배열 길이로 큰 정수 초기화
 * 
 * @param[out] dst 대상 큰 정수의 이중 포인터
 * @param[in] word_len 배열의 길이
 * @return 성공 실패 여부 반환
 */
msg bi_new(OUT bigint** dst, IN int word_len);

/**
 * @brief 대상 큰 정수에 할당된 메모리 해제
 * 
 * @param[in, out] dst 삭제할 대상 큰 정수의 이중 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_delete(UPDATE bigint** dst);

/**
 * @brief 대상 큰 정수의 메모리 재할당(배열 길이 줄이는 용도)
 * 
 * @param[in, out] dst 메모리 재할당할 대상 큰 정수의 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_refine(UPDATE bigint* dst);

/**
 * @brief src 큰 정수를 대상 큰 정수로 복사
 * 
 * @param[in, out] dst 대상 큰 정수의 이중 포인터
 * @param[in] src src 큰 정수의 포인터
 * @return 성공 실패 여부 반환
 */
msg bi_assign(UPDATE bigint** dst, IN const bigint* src);

/**
 * @brief 두 개의 큰 정수의 절댓값 비교
 * 
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return |A| > |B|이면 COMPARE_GREATER, |A| < |B|이면 COMPARE_LESS, |A| == |B|이면 COMPARE_EQUAL
 */
msg bi_compareABS(IN bigint** A, IN bigint** B);

/**
 * @brief 부호 고려한 두 개의 큰 정수 비교
 * 
 * @param[in] A 첫 번째 큰 정수의 이중 포인터
 * @param[in] B 두 번째 큰 정수의 이중 포인터
 * @return A > B이면 COMPARE_GREATER, A < B이면 COMPARE_LESS, A == B이면 COMPARE_EQUAL
 */
msg bi_compare(IN bigint** A, IN bigint** B);

/**
 * @brief 워드 단위로 Left Shift
 *
 * @param[in] T Left Shift 대상 큰 정수의 이중 포인터
 * @param[in] shift_words shift 이동량
 * @return 성공 실패 여부 반환
 */
msg bi_shift_left(UPDATE bigint** T, IN int shift_words);

#endif  // BASIC_FUNC_H