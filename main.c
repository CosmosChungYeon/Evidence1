
#include <stdio.h>      // printf
#include <stdlib.h>     // calloc, realloc
#include <stdint.h>     // uint32_t
#include <string.h>     // strlen
#include <time.h>       // bi_gen_random

#include "basic_func.h"
#include "calc_operations.h"
#include "config.h"
#include "bi_def.h"
#include "msg.h"
#include "test.h"
#include "DH.h"

#include "const.h"

int main() {
    srand(time(NULL));

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;

    msg result;

    int test_num = 100;
    // result = test_bi_add(test_num);
    // result = test_bi_sub(test_num);
    // result = test_bi_textbook_mulc(test_num);
    // result = test_bi_improved_textbook_mulc(test_num);
    // result = test_bi_karatsuba_mulc(test_num);
    // result = test_bi_mul(test_num);
    // result = test_bi_long_div(test_num);
    // result = test_bi_div(test_num);
    // result = test_bi_barrett_red(test_num);
    // result = test_bi_l2r_mod_exp(test_num);
    // result = test_bi_r2l_mod_exp(test_num);
    result = test_DH_1024_160(test_num);

    result = bi_delete(&A);
    result = bi_delete(&B);
    result = bi_delete(&C);
    result = bi_delete(&Q);
    result = bi_delete(&R);

    return 0;
}