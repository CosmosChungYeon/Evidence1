
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "bi_def.h"
#include "rand.h"
#include "array_func.h"
#include "basic_func.h"
#include "calc_operations.h"
#include "config.h"
#include "const.h"
#include "msg.h"
#include "DH.h"
#include "test.h"

int main(void) {
    srand(time(NULL));

    printf("[TEST WORDBIT : %d BIT]\n", WORD_BITLEN);
    if(RAND_CHOICE){
        printf("RAND TEST WORD LEN\n");
    }
    else{
        printf("FIXED TEST WORD LEN\n");
    }
    int test_num = 100;
    test_bi_add(test_num);
    test_bi_sub(test_num);
    test_bi_textbook_mulc(test_num);
    test_bi_improved_textbook_mulc(test_num);
    test_bi_Karatsuba_mulc(test_num);
    test_bi_mul(test_num);
    test_bi_textbook_sqrc(test_num);
    test_bi_Karatsuba_sqrc(test_num);
    if (!RAND_CHOICE) {
        test_bi_naive_div(test_num);
    }
    test_bi_long_div(test_num);
    test_bi_div(test_num);
    test_bi_barrett_red(test_num);
    test_bi_l2r_mod_exp(test_num);
    test_bi_r2l_mod_exp(test_num);
    test_DH_1024_160(test_num);

    return 0;
}
