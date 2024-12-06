#include "test.h"
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

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_add(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 + op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
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
    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_sub(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 - op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
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
    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        op1->sign = NON_NEGATIVE;
        op2->sign = NON_NEGATIVE;

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_textbook_mulc(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 * op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
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

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        op1->sign = NON_NEGATIVE;
        op2->sign = NON_NEGATIVE;

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_improved_textbook_mulc(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 * op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("improved_textbook_mulc[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_Karatsuba_mulc(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_Karatsuba_mulc_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int i = 0; i < test_num; i++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        op1->sign = NON_NEGATIVE;
        op2->sign = NON_NEGATIVE;

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_Karatsuba_mulc(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 * op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("Karatsuba_mulc[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
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

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* op1 = NULL;
        bigint* op2 = NULL;
        bigint* res = NULL;

        int op1_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int op2_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&op1, op1_word_len);
        bi_get_random(&op2, op2_word_len);

        fprintf(file, "op1 = ");
        bi_fprint(file, op1, 16);
        fprintf(file, "\n");
        fprintf(file, "op2 = ");
        bi_fprint(file, op2, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_mul(&res, &op1, &op2);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&op1);
        bi_delete(&op2);
        fprintf(file, "res = op1 * op2\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('op1 = ', hex(op1))\n");
        fprintf(file, "    print('op2 = ', hex(op2))\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
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

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* divd = NULL;
        bigint* divs = NULL;
        bigint* quot = NULL;
        bigint* rem = NULL;

        int divd_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int divs_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&divd, divd_word_len);
        bi_get_random(&divs, divs_word_len);

        divd->sign = NON_NEGATIVE;
        divs->sign = NON_NEGATIVE;

        fprintf(file, "divd = ");
        bi_fprint(file, divd, 16);
        fprintf(file, "\n");
        fprintf(file, "divs = ");
        bi_fprint(file, divs, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_long_div(&quot, &rem, &divd, &divs);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&divd);
        bi_delete(&divs);
        fprintf(file, "quot = divd // divs\n");
        fprintf(file, "rem = divd %% divs\n");
        fprintf(file, "if (quot != ");
        bi_fprint(file, quot, 16);
        fprintf(file, " or rem != ");
        bi_fprint(file, rem, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('divd = ', hex(divd))\n");
        fprintf(file, "    print('divs = ', hex(divs))\n");
        fprintf(file, "    print('quot = ', hex(quot))\n");
        fprintf(file, "    print('rem = ', hex(rem))\n");
        fprintf(file, "    print('wrong_quot = ', hex(");
        bi_fprint(file, quot, 16);
        fprintf(file, "))\n");
        fprintf(file, "    print('wrong_rem = ', hex(");
        bi_fprint(file, rem, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&quot);
        bi_delete(&rem);
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

    fprintf(file, "def c_style_divmod(divd, divs) :\n");
    fprintf(file, "    quot = divd // divs\n");
    fprintf(file, "    rem = divd - quot * divs\n");
    fprintf(file, "    if rem < 0 :\n");
    fprintf(file, "        if divs > 0 :\n");
    fprintf(file, "            rem += divs\n");
    fprintf(file, "            quot -= 1\n");
    fprintf(file, "        else :\n");
    fprintf(file, "            rem -= divs\n");
    fprintf(file, "            quot += 1\n");
    fprintf(file, "    return quot, rem\n");

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* divd = NULL;
        bigint* divs = NULL;
        bigint* quot = NULL;
        bigint* rem = NULL;

        int divd_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int divs_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        bi_get_random(&divd, divd_word_len);
        bi_get_random(&divs, divs_word_len);

        fprintf(file, "divd = ");
        bi_fprint(file, divd, 16);
        fprintf(file, "\n");
        fprintf(file, "divs = ");
        bi_fprint(file, divs, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_div(&quot, &rem, &divd, &divs);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        bi_delete(&divd);
        bi_delete(&divs);
        fprintf(file, "quot, rem = c_style_divmod(divd, divs)\n");
        fprintf(file, "if (quot != ");
        bi_fprint(file, quot, 16);
        fprintf(file, " or rem != ");
        bi_fprint(file, rem, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('divd = ', hex(divd))\n");
        fprintf(file, "    print('divs = ', hex(divs))\n");
        fprintf(file, "    print('quot = ', hex(quot))\n");
        fprintf(file, "    print('rem = ', hex(rem))\n");
        fprintf(file, "    print('wrong_quot = ', hex(");
        bi_fprint(file, quot, 16);
        fprintf(file, "))\n");
        fprintf(file, "    print('wrong_rem = ', hex(");
        bi_fprint(file, rem, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&quot);
        bi_delete(&rem);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("div[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_barrett_red(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_barrett_reduction_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* rem = NULL;
        bigint* divd = NULL;
        bigint* mod = NULL;
        bigint* W = NULL;
        bigint* quot_precomp = NULL;
        bigint* rem_precomp = NULL;
        bigint* precomp = NULL;
        msg result;

        int mod_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int divd_word_len = mod_word_len << 1;

        bi_get_random(&divd, divd_word_len);
        bi_get_random(&mod, mod_word_len);

        divd->sign = NON_NEGATIVE;
        mod->sign = NON_NEGATIVE;

        fprintf(file, "divd = ");
        bi_fprint(file, divd, 16);
        fprintf(file, "\n");
        fprintf(file, "mod = ");
        bi_fprint(file, mod, 16);
        fprintf(file, "\n");

        bi_set_one(&W);
        bi_word_shift_left(&W, divd_word_len);
        bi_long_div(&quot_precomp, &rem_precomp, &W, &mod);
        bi_assign(&precomp, quot_precomp);
        bi_delete(&quot_precomp);
        bi_delete(&rem_precomp);
        bi_delete(&W);

        clock_t start, end;
        start = clock();

        result = bi_barrett_red(&rem, &divd, &mod, &precomp);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        if (result != CLEAR) {
            bi_delete(&mod);
            bi_delete(&divd);
            bi_delete(&precomp);
            bi_delete(&rem);
            continue;
        }
        fprintf(file, "rem = divd %% mod\n");
        fprintf(file, "if (rem != ");
        bi_fprint(file, rem, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('rem = ', hex(rem))\n");
        fprintf(file, "    print('wrong_rem = ', hex(");
        bi_fprint(file, rem, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&divd);
        bi_delete(&mod);
        bi_delete(&precomp);
        bi_delete(&rem);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("barrett_reduction[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_l2r_mod_exp(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_l2r_modular_exp_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* res = NULL;
        bigint* base = NULL;
        bigint* exp = NULL;
        bigint* mod = NULL;

        int base_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int exp_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int mod_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;

        bi_get_random(&base, base_word_len);
        bi_get_random(&exp, exp_word_len);
        bi_get_random(&mod, mod_word_len);

        base->sign = NON_NEGATIVE;
        exp->sign = NON_NEGATIVE;
        mod->sign = NON_NEGATIVE;

        fprintf(file, "base = ");
        bi_fprint(file, base, 16);
        fprintf(file, "\n");
        fprintf(file, "exp = ");
        bi_fprint(file, exp, 16);
        fprintf(file, "\n");
        fprintf(file, "mod = ");
        bi_fprint(file, mod, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_l2r_mod_exp(&res, &base, &exp, &mod);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "res = pow(base, exp, mod)\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
        bi_delete(&base);
        bi_delete(&exp);
        bi_delete(&mod);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("l2r_modular_exp[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_bi_r2l_mod_exp(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("bi_r2l_modular_exp_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* res = NULL;
        bigint* base = NULL;
        bigint* exp = NULL;
        bigint* mod = NULL;

        int base_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int exp_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;
        int mod_word_len = (RAND_CHOICE) ? 1 + rand() % (TEST_WORD_LEN - 1) : TEST_WORD_LEN;

        bi_get_random(&base, base_word_len);
        bi_get_random(&exp, exp_word_len);
        bi_get_random(&mod, mod_word_len);

        base->sign = NON_NEGATIVE;
        exp->sign = NON_NEGATIVE;
        mod->sign = NON_NEGATIVE;

        fprintf(file, "base = ");
        bi_fprint(file, base, 16);
        fprintf(file, "\n");
        fprintf(file, "exp = ");
        bi_fprint(file, exp, 16);
        fprintf(file, "\n");
        fprintf(file, "mod = ");
        bi_fprint(file, mod, 16);
        fprintf(file, "\n");

        clock_t start, end;
        start = clock();

        bi_r2l_mod_exp(&res, &base, &exp, &mod);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "res = pow(base, exp, mod)\n");
        fprintf(file, "if (res != ");
        bi_fprint(file, res, 16);
        fprintf(file, "):\n");
        fprintf(file, "    print('res = ', hex(res))\n");
        fprintf(file, "    print('wrong_res = ', hex(");
        bi_fprint(file, res, 16);
        fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        bi_delete(&res);
        bi_delete(&base);
        bi_delete(&exp);
        bi_delete(&mod);
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    printf("r2l_modular_exp[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}

msg test_DH_1024_160(int test_num) {
    double exec_time = 0;
    FILE* file = fopen("DH_1024_160_test_output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, FileErrorMsg);
        return FileError;
    }
    fprintf(file, "fail_cnt = 0\n");

    bigint* p = NULL;
    bigint* q = NULL;
    bigint* g = NULL;

    bi_set_from_string(&p, PRIME1024, 16);
    bi_set_from_string(&q, PRIME160, 16);
    bi_dh_find_generator_g(&g, &p, &q);
    
    fprintf(file, "p = "); bi_fprint(file, p, 16); fprintf(file, "\n");
    fprintf(file, "q = "); bi_fprint(file, q, 16); fprintf(file, "\n");
    fprintf(file, "g = "); bi_fprint(file, g, 16); fprintf(file, "\n");
    bi_print(q, 16); printf("\n");
    bi_print(g, 16); printf("\n");
    for (int cnt = 0; cnt < test_num; cnt++) {
        bigint* keyA = NULL;
        bigint* keyB = NULL;

        bigint* gA = NULL;
        bigint* gB = NULL;
        bigint* gAB = NULL;
        
        clock_t start, end;
        start = clock();
        
        bi_dh_private_key_gen(&keyA, &q);
        bi_dh_private_key_gen(&keyB, &q);
        bi_dh_public_key_gen(&gA, &g, &keyA, &p);
        bi_dh_public_key_gen(&gB, &g, &keyB, &p);
        bi_dh_session_key_gen(&gAB, &gB, &keyA, &p);

        end = clock();
        double duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(file, "keyA = "); bi_fprint(file, keyA, 16); fprintf(file, "\n");
        fprintf(file, "keyB = "); bi_fprint(file, keyB, 16); fprintf(file, "\n");

        fprintf(file, "gA = "); fprintf(file, "pow(g, keyA, p)\n");
        fprintf(file, "if (gA != "); bi_fprint(file, gA, 16); fprintf(file, "):\n");
        fprintf(file, "    print('gA = ', hex(gA))\n");
        fprintf(file, "    print('wrong_gA = ', hex("); bi_fprint(file, gA, 16); fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        fprintf(file, "gB = "); fprintf(file, "pow(g, keyB, p)\n");
        fprintf(file, "if (gB != "); bi_fprint(file, gB, 16); fprintf(file, "):\n");
        fprintf(file, "    print('gB = ', hex(gB))\n");
        fprintf(file, "    print('wrong_gB = ', hex("); bi_fprint(file, gB, 16); fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");
        
        fprintf(file, "gAB = "); fprintf(file, "pow(gB, keyA, p)\n");
        fprintf(file, "if (gAB != "); bi_fprint(file, gAB, 16); fprintf(file, "):\n");
        fprintf(file, "    print('gAB = ', hex(gAB))\n");
        fprintf(file, "    print('wrong_gAB = ', hex("); bi_fprint(file, gAB, 16); fprintf(file, "))\n");
        fprintf(file, "    fail_cnt = fail_cnt + 1\n");

        bi_delete(&keyA);
        bi_delete(&keyB);
        bi_delete(&gA);
        bi_delete(&gB);
        bi_delete(&gAB);
        
        exec_time += duration;
    }
    fprintf(file, "print(fail_cnt)\n");
    fclose(file);

    bi_delete(&p);
    bi_delete(&q);
    bi_delete(&g);

    printf("DH[test_num = %d] execution Time: %.6f seconds\n", test_num, exec_time);
    return CLEAR;
}