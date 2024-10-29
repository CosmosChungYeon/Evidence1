#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include "bi_def.h"
#include "array_func.h"

/**
 * @brief Sets a bigint from an array with a given sign and word length.
 * 
 * @param[out] dst Pointer to the destination bigint.
 * @param[in] sign Sign of the bigint (positive or negative).
 * @param[in] word_len Length of the array in words.
 * @param[in] a Array to set bigint from.
 * @return Status message indicating success or failure.
 */
msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a);

/**
 * @brief Sets a bigint from a string in a specified base (binary, decimal, or hexadecimal).
 * 
 * @param[out] dst Pointer to the destination bigint.
 * @param[in] int_str String representation of the integer.
 * @param[in] base Numerical base of the string (2, 10, or 16).
 * @note If the integer is negative, the string should start with "-"; otherwise, it should start with an empty sign.
 * @return Status message indicating success or failure.
 */
msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base);

/**
 * @brief Initializes a bigint with a specified word length using random values.
 * 
 * @param[out] dst Pointer to the destination bigint.
 * @param[in] word_len Length of the bigint in words.
 * @return Status message indicating success or failure.
 */
msg bi_get_random(OUT bigint** dst, IN int word_len);

/**
 * @brief Prints a bigint in a specified base (binary, decimal, or hexadecimal).
 * 
 * @param[in] dst Pointer to the bigint to print.
 * @param[in] base Numerical base for output (2, 10, or 16).
 * @return Status message indicating success or failure.
 */
msg bi_print(IN const bigint* dst, IN int base); // const**

/**
 * @brief Initializes a bigint with a specified word length.
 * 
 * @param[out] dst Pointer to the destination bigint.
 * @param[in] word_len Length of the bigint in words.
 * @return Status message indicating success or failure.
 */
msg bi_new(OUT bigint** dst, IN int word_len);

/**
 * @brief Frees the memory allocated for a bigint.
 * 
 * @param[in, out] dst Pointer to the bigint to delete.
 * @return Status message indicating success or failure.
 */
msg bi_delete(UPDATE bigint** dst);

/**
 * @brief Reallocates memory for a bigint, typically used to reduce its word length.
 * 
 * @param[in, out] dst Pointer to the bigint to refine.
 * @return Status message indicating success or failure.
 */
msg bi_refine(UPDATE bigint* dst);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_assign(UPDATE bigint** dst, IN const bigint* src);

/**
 * 
 */
msg bi_compareABS(IN bigint** A, IN bigint** B);

/**
 * 
 */
msg bi_compare(IN bigint** A, IN bigint** B);

#endif  // BASIC_FUNC_H