#ifndef TEST_H
#define TEST_H

#include "bi_def.h"

msg test_bi_add(int test_num);
msg test_bi_sub(int test_num);
msg test_bi_textbook_mulc(int test_num);
msg test_bi_improved_textbook_mulc(int test_num);
msg test_bi_karatsuba_mulc(int test_num);
msg test_bi_mul(int test_num);
msg test_bi_long_div(int test_num);
msg test_bi_div(int test_num);
msg test_bi_barrett_red(int test_num);
msg test_bi_l2r_mod_exp(int test_num);
msg test_bi_r2l_mod_exp(int test_num);

msg test_DH_1024_160(int test_num);

#endif  // TEST_H