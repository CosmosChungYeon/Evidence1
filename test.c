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

        /*printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");*/
        bi_add(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        /*printf("c = a + b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");*/

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

        /*printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");*/
        bi_sub(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        /*printf("c = a - b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");*/

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

        /*printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");*/
        bi_textbook_mulc(&C, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        /*printf("c = a * b\n");
        printf("if (c != ");
        bi_print(C, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('c = ', hex(c))\n");
        printf("    print('wrong answer = ', hex(");
        bi_print(C, 16);
        printf("))\n");*/

        bi_delete(&C);
    }
    return CLEAR;
}

msg test_bi_karatsuba_mulc(int test_num) {
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
        bi_karatsuba_mulc(&C, &A, &B);
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

msg test_bi_mul(int test_num) {
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
        bi_mul(&C, &A, &B);
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

msg test_bi_improved_textbook_mulc(int test_num) {
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
        bi_improved_textbook_mulc(&C, &A, &B);
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


msg test_bi_long_div(int test_num) {
    printf("cnt = 0\n");
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* Q = NULL;
        bigint* R = NULL;
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
        bi_long_div(&Q, &R, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("Q = a // b\n");        
        printf("R = a %% b\n");
        printf("if (Q != ");
        bi_print(Q, 16);
        printf(" or R != ");
        bi_print(R, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('Q = ', hex(Q))\n");
        printf("    print('R = ', hex(R))\n");
        printf("    print('wrong Q = ', hex(");
        bi_print(Q, 16);
        printf("))\n");
        printf("    print('wrong R = ', hex(");
        bi_print(R, 16);
        printf("))\n");
        printf("    cnt = cnt + 1\n");

        bi_delete(&Q);
        bi_delete(&R);

    }
    printf("print(cnt)\n");
    return CLEAR;
}

msg test_bi_div(int test_num) {
    printf("cnt = 0\n");
    printf("def c_style_divmod(a, b) :\n");
    printf("    Q = a // b\n");
    printf("    R = a - Q * b\n");
    printf("    if R < 0 :\n");
    printf("        if b > 0 :\n");
    printf("            R += b\n");
    printf("            Q -= 1\n");
    printf("        else :\n");
    printf("            R -= b\n");
    printf("            Q += 1\n");
    printf("    return Q, R\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* Q = NULL;
        bigint* R = NULL;
        msg result;

        result = bi_get_random(&A, 3);
        result = bi_get_random(&B, 2);

        printf("a = ");
        bi_print(A, 16);
        printf("\n");
        printf("b = ");
        bi_print(B, 16);
        printf("\n");
        bi_div(&Q, &R, &A, &B);
        bi_delete(&A);
        bi_delete(&B);
        printf("Q, R = c_style_divmod(a, b)\n");
        printf("if (Q != ");
        bi_print(Q, 16);
        printf(" or R != ");
        bi_print(R, 16);
        printf("):\n");
        printf("    print('a = ', hex(a))\n");
        printf("    print('b = ', hex(b))\n");
        printf("    print('Q = ', hex(Q))\n");
        printf("    print('R = ', hex(R))\n");
        printf("    print('wrong Q = ', hex(");
        bi_print(Q, 16);
        printf("))\n");
        printf("    print('wrong R = ', hex(");
        bi_print(R, 16);
        printf("))\n");
        printf("    cnt = cnt + 1\n");

        bi_delete(&Q);
        bi_delete(&R);
    }
    printf("print(cnt)\n");
    return CLEAR;
}
