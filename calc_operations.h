#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include "basic_func.h"

/**
 * @brief Addition of two words with a carry
 *
 * @param[out] result Pointer to store the result
 * @param[in] op1 First word
 * @param[in] op2 Second word
 * @param[in] carry_in Carry from the previous operation
 * @return Carry bit after the addition
 */
msg bi_add_ABc(OUT word* result, IN word* op1, IN word* op2, IN int carry_in);

/**
 * @brief Addition of two big integers with the same sign and carry
 *        (word_len(op1) >= word_len(op2))
 *
 * @param[out] result Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_addc(OUT bigint** result, IN bigint** op1, IN bigint** op2);

/**
 * @brief Addition of two big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_add(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Subtraction of two words with a borrow
 *
 * @param[out] res Pointer to store the result
 * @param[in] op1 First word
 * @param[in] borrow_in Borrow from the previous operation
 * @param[in] op2 Second word (to subtract)
 * @return Borrow bit after the subtraction
 */
msg bi_sub_AbB(OUT word* res, IN word* op1, IN int borrow_in, IN word* op2);

/**
 * @brief Subtraction of two big integers with the same sign and borrow (A >= B > 0)
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_subc(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Subtraction of two big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_sub(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Multiplication of two single words
 *
 * @param[out] res Array to store the result of the word multiplication
 * @param[in] A First word
 * @param[in] B Second word
 * @return Success or failure status
 */
msg bi_mul_AB(OUT word res[2], IN word* A, IN word* B);

/**
 * @brief Textbook multiplication for big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_textbook_mulc(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Improved textbook multiplication for big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_improved_textbook_mulc(bigint** res, bigint** op1, bigint** op2);

/**
 * @brief Karatsuba multiplication for big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_Karatsuba_mulc(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Signed multiplication of two big integers
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] op1 Pointer to the first big integer
 * @param[in] op2 Pointer to the second big integer
 * @return Success or failure status
 */
msg bi_mul(OUT bigint** res, IN bigint** op1, IN bigint** op2);

/**
 * @brief Long division with bits
 *
 * @param[out] quot Pointer to the quotient big integer
 * @param[out] rem Pointer to the remainder big integer
 * @param[in] divd Pointer to the dividend big integer
 * @param[in] divs Pointer to the divisor big integer
 * @return Success or failure status
 */
msg bi_long_div(OUT bigint** quot, OUT bigint** rem, IN bigint** divd, IN bigint** divs);

/**
 * @brief Modulus operation for big integers
 *
 * @param[in, out] rem Pointer to the remainder big integer (updated)
 * @param[in] divs Pointer to the divisor big integer
 * @return Success or failure status
 */
msg bi_mod(UPDATE bigint** rem, IN bigint** divs);

/**
 * @brief Signed division of two big integers
 *
 * @param[out] quot Pointer to the quotient big integer
 * @param[out] rem Pointer to the remainder big integer
 * @param[in] divd Pointer to the dividend big integer
 * @param[in] divs Pointer to the divisor big integer
 * @return Success or failure status
 */
msg bi_div(OUT bigint** quot, OUT bigint** rem, IN bigint** divd, IN bigint** divs);

/**
 * @brief Left-to-right modular exponentiation (res = base^exp mod mod)
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] base Pointer to the base big integer
 * @param[in] exp Pointer to the exponent big integer
 * @param[in] mod Pointer to the modulus big integer
 * @return Success or failure status
 */
msg bi_l2r_mod_exp(OUT bigint** res, IN bigint** base, IN bigint** exp, IN bigint** mod);

/**
 * @brief Right-to-left modular exponentiation (res = base^exp mod mod)
 *
 * @param[out] res Pointer to the result big integer
 * @param[in] base Pointer to the base big integer
 * @param[in] exp Pointer to the exponent big integer
 * @param[in] mod Pointer to the modulus big integer
 * @return Success or failure status
 */
msg bi_r2l_mod_exp(OUT bigint** res, IN bigint** base, IN bigint** exp, IN bigint** mod);

/**
 * @brief Barrett reduction (Length of divd = 2 * length of mod)
 *
 * @param[out] rem Pointer to the result (remainder) big integer
 * @param[in] divd Pointer to the dividend big integer
 * @param[in] mod Pointer to the modulus big integer
 * @param[in] precomp Pointer to the precomputed value big integer
 * @return Success or failure status
 * @note Limitation: For 8-bit word, test cases fail due to reduced word length in divd or mod
 */
msg bi_barrett_red(OUT bigint** rem, IN bigint** divd, IN bigint** mod, IN bigint** precomp);

#endif  // CALC_OPERATIONS_H