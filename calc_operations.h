#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include <string.h>

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_add_ABc(OUT word* C, IN word A, IN word B, IN int c);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_sub_AbB(OUT word* C, IN word A, IN int b, IN word B);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_subc(OUT bigint** C, IN bigint** A, IN bigint** B);

/**
 * @brief Copies a bigint from src to dst.
 * 
 * @param[in, out] dst Pointer to the destination bigint.
 * @param[in] src Pointer to the source bigint.
 * @return Status message indicating success or failure.
 */
msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B);

#endif  // CALC_OPERATIONS_H