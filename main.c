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
    msg result;
    
    //result = test_bi_add(10);
    //printf("%d\n", result);

    //result = test_bi_sub(10);
    //printf("%d\n", result);

    result = test_bi_textbook_mulc(10);
    printf("%d\n", result);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);

    return 0;
}