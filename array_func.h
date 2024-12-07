#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include "bi_def.h"
#include "rand.h"

/**
 * @brief Initialize an array with zero values
 *
 * @param[out] arr The array to be initialized
 * @param[in] word_len The length of the array
 * @return Initialization status (Success: CLEAR, Failure: NOTInitErr)
 */
msg array_init(UPDATE word* arr, IN int word_len);

/**
 * @brief Copy values from the source array to the destination array
 *
 * @param[out] dst The destination array
 * @param[in] src The source array to copy from
 * @param[in] word_len The length of the array
 * @return Status of the copy operation
 */
msg array_copy(OUT word* dst, IN word* src, IN int word_len);

/**
 * @brief Copy high-order values from the source array to the destination array
 *
 * @param[out] dst The destination array
 * @param[in] src The source array to copy from
 * @param[in] dst_word_len The length of the destination array
 * @param[in] src_word_len The length of the source array
 * @return Status of the copy operation
 */
msg array_copy_high(OUT word* dst, IN word* src, IN int dst_word_len, IN int src_word_len);

/**
 * @brief Copy low-order values from the source array to the destination array
 *
 * @param[out] dst The destination array
 * @param[in] src The source array to copy from
 * @param[in] dst_word_len The length of the destination array
 * @param[in] src_word_len The length of the source array
 * @return Status of the copy operation
 */
msg array_copy_low(OUT word* dst, IN word* src, IN int dst_word_len, IN int src_word_len);

/**
 * @brief Fill the target array with random values
 *
 * @param[out] dst The array to be filled with random values
 * @param[in] word_len The length of the array
 * @return Status of the random assignment
 */
msg array_rand(OUT word* dst, IN int word_len);

#endif  // ARRAY_FUNC_H
