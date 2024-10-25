#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include "bi_def.h"
#include "rand.h"

/**
 * @brief Initializes an array with zero values.
 * 
 * @param[out] a Array to be initialized.
 * @param[in] word_len Length of the array in words.
 * @return CLEAR if initialization is successful, otherwise NOTInitErr.
 */
msg array_init(UPDATE word* a, int IN word_len);

/**
 * @brief Copies the source array to the destination array.
 * 
 * @param[out] dst Destination array.
 * @param[in] src Source array to copy from.
 * @param[in] word_len Length of the arrays in words.
 * @return CLEAR if copy is successful, otherwise MemAllocErr.
 */
msg array_copy(OUT word* dst, IN word* src, IN int word_len);

/**
 * @brief Fills the destination array with random values.
 * 
 * @param[out] dst Array to be filled with random values.
 * @param[in] word_len Length of the array in words.
 * @return CLEAR if random assignment is successful.
 */
msg array_rand(OUT word* dst, IN int word_len);

#endif  // ARRAY_FUNC_H