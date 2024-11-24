
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

    /*clock_t start, end;
    start = clock();
    result = test_bi_add(10000);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/
    //printf("%d\n", result);

    /*clock_t start, end;
    start = clock();
    result = test_bi_sub(10000);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/
    //printf("%d\n", result);

    /*clock_t start, end;
    start = clock();
    result = test_bi_textbook_mulc(100);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/
    //printf("%d\n", result);

    /*clock_t start, end;
    start = clock();
    result = test_bi_karatsuba_mulc(100);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/
    //printf("%d\n", result);

    /*clock_t start, end;
    start = clock();
    result = test_bi_mul(100);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/

    /*clock_t start, end;
    start = clock();
    result = test_bi_long_div(100);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/
    //printf("%d\n", result);

    /*clock_t start, end;
    start = clock();
    result = test_bi_div(100);
    end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", duration);*/

    ////word a[] = { 0xf9, 0x99, 0x2e, 0x0b, 0x06, 0x0a, 0x62, 0x91 };
    ////word b[] = { 0x32, 0x70, 0x0b, 0x6d, 0x56, 0x3a, 0x07, 0x06 };
    ////word a[] = { 0x0b2e99f9, 0x91620a06 };
    ////word b[] = { 0x6d0b7032, 0x06073a56 };
    ////word a[] = { 0x91620a060b2e99f9 };
    ////word b[] = { 0x06073a566d0b7032 };
    //bi_set_from_string(&A, "91620a060b2e99f9", 16);
    //bi_set_from_string(&B, "6073a566d0b7032", 16);
    ////bi_set_from_array(&A, 0, 1, a);
    ////bi_set_from_array(&B, 0, 1, b);
    //bi_print(A, 16);
    //printf("\n");
    //bi_print(B, 16);
    //printf("\n");
    //result = bi_long_div(&Q, &R, &A, &B);
    //bi_print(Q, 16);
    //printf("\n");
    //bi_print(R, 16);
    //printf("\n");
    //printf("return = %d", result);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    bi_delete(&Q);
    bi_delete(&R);

    return 0;
}