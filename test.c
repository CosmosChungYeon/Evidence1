#include "test.h"
#include "basic_func.h"
#include "calc_operations.h"
#include "const.h"
#include <stdio.h>
#include <time.h>

msg test_bi_add(int test_num) {
    
    double exec_time = 0;
    
    FILE* file = fopen("bi_add_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len); 
        
        
        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_add(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a + b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&C);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("add[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_sub(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_sub_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_sub(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a - b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("sub[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_textbook_mulc(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_textbook_mulc_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");
    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        A->sign = NON_NEGATIVE;
        B->sign = NON_NEGATIVE;

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_textbook_mulc(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a * b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("textbook_mulc[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_improved_textbook_mulc(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_improved_mulc_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        A->sign = NON_NEGATIVE;
        B->sign = NON_NEGATIVE;

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_improved_textbook_mulc(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a * b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("improved_textbook_mulc[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_karatsuba_mulc(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_karatsuba_mulc_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        A->sign = NON_NEGATIVE;
        B->sign = NON_NEGATIVE;

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_karatsuba_mulc(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a * b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        bi_delete(&C);
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("karatsuba_mulc[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_mul(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_mul_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* C = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        fprintf(file, "a = ");
        bi_fprint(file,  A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_mul(&C, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "c = a * b\n");
        fprintf(file, "if (c != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('c = ', hex(c))\n");
        fprintf(file, "    print('wrong answer = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("mul[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_long_div(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_long_div_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* Q = NULL;
        bigint* R = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        A->sign = NON_NEGATIVE;
        B->sign = NON_NEGATIVE;

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_long_div(&Q, &R, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "Q = a // b\n");
        fprintf(file, "R = a %% b\n");
        fprintf(file, "if (Q != ");
        bi_fprint(file, Q, 16);
        fprintf(file, " or R != ");
        bi_fprint(file, R, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('Q = ', hex(Q))\n");
        fprintf(file, "    print('R = ', hex(R))\n");
        fprintf(file, "    print('wrong Q = ', hex(");
        bi_fprint(file, Q, 16);
        fprintf(file, "))\n");
        fprintf(file, "    print('wrong R = ', hex(");
        bi_fprint(file, R, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&Q);
        bi_delete(&R);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("long_div[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_div(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_div_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    fprintf(file, "def c_style_divmod(a, b) :\n");
    fprintf(file, "    Q = a // b\n");
    fprintf(file, "    R = a - Q * b\n");
    fprintf(file, "    if R < 0 :\n");
    fprintf(file, "        if b > 0 :\n");
    fprintf(file, "            R += b\n");
    fprintf(file, "            Q -= 1\n");
    fprintf(file, "        else :\n");
    fprintf(file, "            R -= b\n");
    fprintf(file, "            Q += 1\n");
    fprintf(file, "    return Q, R\n");

    for (int i = 0; i < test_num; i++) {
        bigint* A = NULL;
        bigint* B = NULL;
        bigint* Q = NULL;
        bigint* R = NULL;
        msg result;

        int A_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int B_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&B, B_word_len);

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "b = ");
        bi_fprint(file, B, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_div(&Q, &R, &A, &B);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&A);
        bi_delete(&B);
        fprintf(file, "Q, R = c_style_divmod(a, b)\n");
        fprintf(file, "if (Q != ");
        bi_fprint(file, Q, 16);
        fprintf(file, " or R != ");
        bi_fprint(file, R, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('a = ', hex(a))\n");
        fprintf(file, "    print('b = ', hex(b))\n");
        fprintf(file, "    print('Q = ', hex(Q))\n");
        fprintf(file, "    print('R = ', hex(R))\n");
        fprintf(file, "    print('wrong Q = ', hex(");
        bi_fprint(file, Q, 16);
        fprintf(file, "))\n");
        fprintf(file, "    print('wrong R = ', hex(");
        bi_fprint(file, R, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&Q);
        bi_delete(&R);

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("div[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_barrett_reduction(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_barrett_reduction_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* R = NULL;
        bigint* A = NULL;
        bigint* N = NULL;
        bigint* W = NULL;
        bigint* Q = NULL;
        bigint* Re = NULL;
        bigint* T = NULL;
        msg result;
        

        int N_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int A_word_len = N_word_len << 1;

        result = bi_get_random(&A, A_word_len);
        result = bi_get_random(&N, N_word_len);
        
        A->sign = NON_NEGATIVE;
        N->sign = NON_NEGATIVE;

        fprintf(file, "a = ");
        bi_fprint(file, A, 16);
        fprintf(file, "\n");
        fprintf(file, "N = ");
        bi_fprint(file, N, 16);
        fprintf(file, "\n");

        bi_set_from_string(&W, "1", 16);
        bi_word_shift_left(&W, A->word_len);
        bi_long_div(&Q, &Re, &W, &N);
        bi_assign(&T, Q);
        bi_delete(&Q);
        bi_delete(&Re);
        bi_delete(&W);

        clock_t start, end;
        start = clock();
        result = bi_barrett_reduction(&R, &A, &N, &T);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        if (result != CLEAR) {
            bi_delete(&A);
            bi_delete(&N);
            bi_delete(&T);
            bi_delete(&R);
            continue;
        }
        fprintf(file, "R = a %% N\n");
        fprintf(file, "if (R != ");
        bi_fprint(file, R, 16);
        fprintf(file,"):\n");
        fprintf(file, "    print('R = ', hex(R))\n");
        fprintf(file, "    print('wrong R = ', hex(");
        bi_fprint(file, R, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&A);
        bi_delete(&N);
        bi_delete(&T);
        bi_delete(&R);

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("barrett_reduction[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_l2r_modular_exp(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_l2r_modular_exp_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* C = NULL;
        bigint* X = NULL;
        bigint* N = NULL;
        bigint* M = NULL;
       
        msg result;

        int X_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int N_word_len = 1;
        int M_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;

        result = bi_get_random(&X, X_word_len);
        result = bi_get_random(&N, N_word_len);
        result = bi_get_random(&M, M_word_len);

        X->sign = NON_NEGATIVE;
        N->sign = NON_NEGATIVE;
        M->sign = NON_NEGATIVE;

        fprintf(file, "X = ");
        bi_fprint(file, X, 16);
        fprintf(file, "\n");
        fprintf(file, "N = ");
        bi_fprint(file, N, 16);
        fprintf(file, "\n");
        fprintf(file, "M = ");
        bi_fprint(file, M, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        result = bi_l2r_modular_exp(&C, &X, &N, &M);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "C = pow(X, N, M)\n");
        fprintf(file, "if (C != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('C = ', hex(C))\n");
        fprintf(file, "    print('wrong C = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);
        bi_delete(&X);
        bi_delete(&N);
        bi_delete(&M);

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("l2r_modular_exp[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_r2l_modular_exp(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_r2l_modular_exp_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* C = NULL;
        bigint* X = NULL;
        bigint* N = NULL;
        bigint* M = NULL;
       
        msg result;

        int X_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int N_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int M_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;

        result = bi_get_random(&X, X_word_len);
        result = bi_get_random(&N, N_word_len);
        result = bi_get_random(&M, M_word_len);

        X->sign = NON_NEGATIVE;
        N->sign = NON_NEGATIVE;
        M->sign = NON_NEGATIVE;

        fprintf(file, "X = ");
        bi_fprint(file, X, 16);
        fprintf(file, "\n");
        fprintf(file, "N = ");
        bi_fprint(file, N, 16);
        fprintf(file, "\n");
        fprintf(file, "M = ");
        bi_fprint(file, M, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        result = bi_r2l_modular_exp(&C, &X, &N, &M);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "C = pow(X, N, M)\n");
        fprintf(file, "if (C != ");
        bi_fprint(file, C, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('C = ', hex(C))\n");
        fprintf(file, "    print('wrong C = ', hex(");
        bi_fprint(file, C, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&C);
        bi_delete(&X);
        bi_delete(&N);
        bi_delete(&M);

        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("r2l_modular_exp[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}