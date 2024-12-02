
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
#include "dh.h"

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
    //result = test_bi_add(test_num);
    //result = test_bi_sub(test_num);
    //result = test_bi_textbook_mulc(test_num);
    //result = test_bi_improved_textbook_mulc(test_num);
    //result = test_bi_karatsuba_mulc(test_num);
    //result = test_bi_mul(test_num);
    //result = test_bi_long_div(test_num);
    //result = test_bi_div(test_num);
    //result = test_bi_l2r_mod_exp(test_num);
    //result = test_bi_r2l_mod_exp(test_num);
    //result = test_bi_barrett_red(test_num);


    bigint* p = NULL;
    bigint* g = NULL;
    bigint* gA = NULL;
    bigint* gB = NULL;
    bigint* gAB = NULL;
    bigint* key = NULL;

    bi_set_from_string(&p, "23", 16);
    bi_set_from_string(&g, "5", 16);
    bi_set_from_string(&gB, "13", 16);
    bi_dh_private_key_gen(&key, &p);
    bi_dh_public_key_gen(&gA, &g, &key, &p);
    bi_dh_session_key_gen(&gAB, &gB, &key, &p);
    
    printf("k = "); bi_print(key, 16); printf("\n");
    printf("p = "); bi_print(p, 16); printf("\n");
    printf("g = "); bi_print(g, 16); printf("\n");
    printf("gA = "); bi_print(gA, 16); printf("\n");
    printf("B = "); bi_print(gB, 16); printf("\n");
    printf("gAB = "); bi_print(gAB, 16); printf("\n");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    bi_delete(&Q);
    bi_delete(&R);

    bi_delete(&p);
    bi_delete(&g);
    bi_delete(&gA);
    bi_delete(&gB);
    bi_delete(&gAB);
    bi_delete(&key);

    return 0;
}