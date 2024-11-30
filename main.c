
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
    // result = test_bi_barrett_reduction(test_num);
    result = test_bi_l2r_modular_exp(test_num);
    result = test_bi_r2l_modular_exp(test_num);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    bi_delete(&Q);
    bi_delete(&R);

    return 0;
}