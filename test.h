#ifndef TEST_H
#define TEST_H

#include "basic_func.h"
#include "calc_operations.h"
#include "DH.h"

/**
 * @brief Tests the addition operation.
 * @param test_num The test case number to execute.
 * @return The result of the addition test as a `msg`.
 */
msg test_bi_add(int test_num);

/**
 * @brief Tests the subtraction operation.
 * @param test_num The test case number to execute.
 * @return The result of the subtraction test as a `msg`.
 */
msg test_bi_sub(int test_num);

/**
 * @brief Tests the textbook multiplication algorithm.
 * @param test_num The test case number to execute.
 * @return The result of the textbook multiplication test as a `msg`.
 */
msg test_bi_textbook_mulc(int test_num);

/**
 * @brief Tests the improved textbook multiplication algorithm.
 * @param test_num The test case number to execute.
 * @return The result of the improved textbook multiplication test as a `msg`.
 */
msg test_bi_improved_textbook_mulc(int test_num);

/**
 * @brief Tests the Karatsuba multiplication algorithm.
 * @param test_num The test case number to execute.
 * @return The result of the Karatsuba multiplication test as a `msg`.
 */
msg test_bi_Karatsuba_mulc(int test_num);

/**
 * @brief Tests the generic multiplication operation.
 * @param test_num The test case number to execute.
 * @return The result of the generic multiplication test as a `msg`.
 */
msg test_bi_mul(int test_num);

/**
 * @brief Tests the long division algorithm.
 * @param test_num The test case number to execute.
 * @return The result of the long division test as a `msg`.
 */
msg test_bi_long_div(int test_num);

/**
 * @brief Tests the generic division operation.
 * @param test_num The test case number to execute.
 * @return The result of the generic division test as a `msg`.
 */
msg test_bi_div(int test_num);

/**
 * @brief Tests the Barrett reduction algorithm.
 * @param test_num The test case number to execute.
 * @return The result of the Barrett reduction test as a `msg`.
 */
msg test_bi_barrett_red(int test_num);

/**
 * @brief Tests the left-to-right modular exponentiation.
 * @param test_num The test case number to execute.
 * @return The result of the left-to-right modular exponentiation test as a `msg`.
 */
msg test_bi_l2r_mod_exp(int test_num);

/**
 * @brief Tests the right-to-left modular exponentiation.
 * @param test_num The test case number to execute.
 * @return The result of the right-to-left modular exponentiation test as a `msg`.
 */
msg test_bi_r2l_mod_exp(int test_num);

/**
 * @brief Tests the Diffie-Hellman key exchange using 1024-bit p and 160-bit q parameters.
 * @param test_num The test case number to execute.
 * @return The result of the Diffie-Hellman key exchange test as a `msg`.
 */
msg test_DH_1024_160(int test_num);

#endif  // TEST_H
