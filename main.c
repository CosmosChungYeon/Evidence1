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

    //result = test_bi_add(100);
    //printf("%d\n", result);

    //result = test_bi_sub(100);
    //printf("%d\n", result);

    //result = test_bi_textbook_mulc(100);
    //printf("%d\n", result);

    result = test_bi_long_div(100);
    //printf("%d\n", result);

    /*bi_set_from_string(&A, "1234567890000", 16);
    bi_set_from_string(&B, "123456789", 16);
    bi_print(A, 16);
    printf("\n");
    bi_print(B, 16);
    printf("\n");
    result = bi_karatsuba_mulc(&C, &A, &B, 1);
    bi_print(C, 16);
    printf("\n");*/

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);

    return 0;
}