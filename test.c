#include "test.h"
#include "basic_func.h"
#include "calc_operations.h"

msg test_bi_add(int test_num) {
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        result = bi_get_random(&A, 31);
        result = bi_get_random(&B, 30);
        result = bi_get_random(&C, 31);
        A->sign = 0;
        B->sign = 0;
        C->sign = 0;
        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_addc(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("c = a + b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n") ;
        printf("    print('c = ', c)\n");
        printf("    print('wrong answer = ',");
        bi_print(C, 16);
        printf(")\n");

        bi_delete(&C);
    }
    return CLEAR;
}

msg test_bi_sub(int test_num) {
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        result = bi_get_random(&A, 31);
        result = bi_get_random(&B, 30);
        result = bi_get_random(&C, 31);
        A->sign = 0;
        B->sign = 0;
        C->sign = 0;
        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_subc(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("c = a - b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n") ;
        printf("    print('c = ', c)\n");
        printf("    print('wrong answer = ',");
        bi_print(C, 16);
        printf(")\n");

        bi_delete(&C);
    }
    return CLEAR;
}