#ifndef TEST_H
#define TEST_H

#include "basic_func.h"
#include "calc_operations.h"
#include "DH.h"

msg test_bi_add(int test_num);                     // Tests the addition operation
msg test_bi_sub(int test_num);                     // Tests the subtraction operation
msg test_bi_textbook_mulc(int test_num);           // Tests the textbook multiplication
msg test_bi_improved_textbook_mulc(int test_num);  // Tests the improved textbook multiplication
msg test_bi_Karatsuba_mulc(int test_num);          // Tests the Karatsuba multiplication
msg test_bi_mul(int test_num);                     // Tests the generic multiplication
msg test_bi_long_div(int test_num);                // Tests the long division
msg test_bi_div(int test_num);                     // Tests the generic division
msg test_bi_barrett_red(int test_num);             // Tests the Barrett reduction
msg test_bi_l2r_mod_exp(int test_num);             // Tests the left-to-right modular exponentiation
msg test_bi_r2l_mod_exp(int test_num);             // Tests the right-to-left modular exponentiation

msg test_DH_1024_160(int test_num);                // Tests the Diffie-Hellman key exchange using 1024-bit p and 160-bit q parameters

#endif  // TEST_H