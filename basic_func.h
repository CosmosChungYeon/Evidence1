#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include "bi_def.h"
#include "array_func.h"

/**
 * @brief Set a large integer with a given sign, array length, and array
 *
 * @param[out] dst Pointer to the target large integer
 * @param[in] sign Sign of the large integer (NON_NEGATIVE or NEGATIVE)
 * @param[in] word_len Length of the array
 * @param[in] a Array representing the large integer
 * @return Success or failure
 */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a);

/**
 * @brief Set a large integer from a string in a specified base
 *
 * @param[out] dst Pointer to the target large integer
 * @param[in] int_str Input string
 * @param[in] base Base of the number (2, 10, 16)
 * @note If negative, the string should start with '-'
 * @return Success or failure
 */
msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base);

/**
 * @brief Initialize a large integer of specified length with random values
 *
 * @param[out] dst Pointer to the target large integer
 * @param[in] word_len Length of the array
 * @return Success or failure
 */
msg bi_get_random(OUT bigint** dst, IN int word_len);

/**
 * @brief Print a large integer in the specified base
 *
 * @param[in] dst Pointer to the target large integer
 * @param[in] base Base of the number (2, 16)
 * @return Success or failure
 */
msg bi_print(IN const bigint* dst, IN int base);

/**
 * @brief Print a large integer to a file in the specified base
 *
 * @param[in] file File pointer
 * @param[in] dst Pointer to the target large integer
 * @param[in] base Base of the number (2, 16)
 * @return Success or failure
 */
msg bi_fprint(IN FILE* file, IN const bigint* dst, IN int base);

/**
 * @brief Initialize a large integer with the specified array length
 *
 * @param[out] dst Pointer to the target large integer
 * @param[in] word_len Length of the array
 * @return Success or failure
 */
msg bi_new(OUT bigint** dst, IN int word_len);

/**
 * @brief Free the memory allocated for a large integer
 *
 * @param[in, out] dst Pointer to the target large integer
 * @return Success or failure
 */
msg bi_delete(UPDATE bigint** dst);

/**
 * @brief Reallocate memory for a large integer (used to reduce array length)
 *
 * @param[in, out] dst Pointer to the target large integer
 * @return Success or failure
 */
msg bi_refine(UPDATE bigint* dst);

/**
 * @brief Copy a source large integer into a target large integer
 *
 * @param[in, out] dst Pointer to the target large integer
 * @param[in] src Pointer to the source large integer
 * @return Success or failure
 */
msg bi_assign(UPDATE bigint** dst, IN const bigint* src);

/**
 * @brief Compare the absolute values of two large integers
 *
 * @param[in] A Pointer to the first large integer
 * @param[in] B Pointer to the second large integer
 * @return COMPARE_GREATER if |A| > |B|, COMPARE_LESS if |A| < |B|, COMPARE_EQUAL if |A| == |B|
 */
msg bi_compareABS(IN bigint** A, IN bigint** B);

/**
 * @brief Compare two large integers considering their signs
 *
 * @param[in] A Pointer to the first large integer
 * @param[in] B Pointer to the second large integer
 * @return COMPARE_GREATER if A > B, COMPARE_LESS if A < B, COMPARE_EQUAL if A == B
 */
msg bi_compare(IN bigint** A, IN bigint** B);

/**
 * @brief Perform a left shift on a large integer by word units
 *
 * @param[in, out] dst Pointer to the large integer
 * @param[in] shift_count Number of words to shift
 * @return Success or failure
 */
msg bi_word_shift_left(UPDATE bigint** dst, IN int shift_count);

/**
 * @brief Perform a right shift on a large integer by word units
 *
 * @param[in, out] dst Pointer to the large integer
 * @param[in] shift_count Number of words to shift
 * @return Success or failure
 */
msg bi_word_shift_right(UPDATE bigint** dst, IN int shift_count);

/**
 * @brief Double the value of a large integer
 *
 * @param[in, out] dst Pointer to the large integer
 * @return Success or failure
 */
msg bi_doubling(UPDATE bigint* dst);

/**
 * @brief Add one to a large integer
 *
 * @param[in, out] dst Pointer to the large integer
 * @return Success or failure
 */
msg bi_plus_one(UPDATE bigint** dst);

/**
 * @brief Check if a large integer is zero
 *
 * @param[in] src Pointer to the large integer
 * @return True if zero, false otherwise
 */
msg bi_zero_check(IN bigint** src);

/**
 * @brief Set a large integer to one
 *
 * @param[in, out] dst Pointer to the large integer
 * @return Success or failure
 */
msg bi_set_one(UPDATE bigint** dst);

#endif  // BASIC_FUNC_H