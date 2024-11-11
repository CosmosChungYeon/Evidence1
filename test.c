#include "test.h"
#include "basic_func.h"
#include "calc_operations.h"
#include "const.h"

msg test_bi_add(int test_num) {
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        result = bi_get_random(&A, TEST_WORD_LEN);
        result = bi_get_random(&B, TEST_WORD_LEN);

        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_add(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("c = a + b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n") ;
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");

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

        result = bi_get_random(&A, TEST_WORD_LEN);
        result = bi_get_random(&B, TEST_WORD_LEN);

        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_sub(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("c = a - b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n") ;
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");

        bi_delete(&C);
    }
    return CLEAR;
}

msg test_bi_textbook_mulc(int test_num) {
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        result = bi_get_random(&A, TEST_WORD_LEN);
        result = bi_get_random(&B, TEST_WORD_LEN);

        A->sign = NON_NEGATIVE;
        B->sign = NON_NEGATIVE;

        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_textbook_mulc(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("c = a * b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");

        bi_delete(&C);
    }
    return CLEAR;
}