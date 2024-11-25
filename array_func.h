#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include "bi_def.h"
#include "rand.h"

/**
 * @brief 배열 값 0으로 초기화
 *
 * @param[out] a 초기화할 배열
 * @param[in] word_len 배열의 길이
 * @return 초기화 여부 반환 (성공: CLEAR, 실패: NOTInitErr)
 */
msg array_init(UPDATE word* a, int IN word_len);

/**
 * @brief src 배열을 대상 배열로 배열 복사
 *
 * @param[out] dst 복사 대상 배열
 * @param[in] src 복사할 src 배열
 * @param[in] word_len 배열의 길이
 * @return 복사 성공 여부 반환
 */
msg array_copy(OUT word* dst, IN word* src, IN int word_len);

/**
 * @brief 대상 배열을 무작위 값으로 채움
 *
 * @param[out] dst 무작위 값으로 채워지는 배열
 * @param[in] word_len 배열의 길이
 * @return 무작위 할당 성공 여부
 */
msg array_rand(OUT word* dst, IN int word_len);

#endif  // ARRAY_FUNC_H