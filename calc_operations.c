
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "const.h"

msg bi_add_ABc(OUT word* result, IN word* op1, IN word* op2, IN int carry_in) {
    int carry_out = 0; // Carry out (c')

    // Add op1 and op2
    *result = *op1 + *op2;
    carry_out = (*result < *op1) ? CARRY1 : CARRY0; // Check for carry: if op1 + op2 < op1, carry = 1

    // Add the input carry
    *result += carry_in;
    carry_out += (*result < carry_in) ? CARRY1 : CARRY0; // If result + carry_in < carry_in, additional carry

    return carry_out; // Return the carry out
}

msg bi_addc(OUT bigint** result, IN bigint** op1, IN bigint** op2) {
    // Ensure op1 has more or equal word length (n >= m)
    int len_op1 = (*op1)->word_len;
    int len_op2 = (*op2)->word_len;

    // Initialize a temporary bigint to store the result, with extra space for the final carry
    bigint* tmp_result = NULL;
    bi_new(&tmp_result, len_op1 + 1); // +1 word for the final carry

    // Perform addition word by word with carry propagation
    int carry = 0;
    for (int i = 0; i < len_op1; i++) {
        word val_op1 = (*op1)->a[i];
        word val_op2 = (i < len_op2) ? (*op2)->a[i] : 0; // Use 0 if op2 is shorter

        carry = bi_add_ABc(&(tmp_result->a[i]), &val_op1, &val_op2, carry);
    }

    // Handle the final carry
    tmp_result->a[len_op1] = (carry == CARRY1) ? CARRY1 : CARRY0;

    // Set the sign of the result
    tmp_result->sign = ((*op1)->sign == NEGATIVE && (*op2)->sign == NEGATIVE) ? NEGATIVE : NON_NEGATIVE;

    // Assign the result to the output and clean up temporary memory
    bi_assign(result, tmp_result);
    bi_delete(&tmp_result);

    return bi_refine(*result); // Refine the result to ensure proper formatting
}

msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B) {
    if (*A == NULL || *B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;

    bigint* tmp = NULL;
    bi_new(&tmp, max_word_len);

    if ((*A)->sign != (*B)->sign) {
        // A > 0 and B < 0 
        if ((*A)->sign == NON_NEGATIVE) {
            (*B)->sign = NON_NEGATIVE;
            bi_sub(&tmp, A, B);
            (*B)->sign = NEGATIVE;
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
        // A < 0 and B > 0 
        else {
            (*A)->sign = NON_NEGATIVE;
            bi_sub(&tmp, B, A);
            (*A)->sign = NEGATIVE;
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
    }

    /* 부호가 같은 경우 */
    (tmp)->sign = (*A)->sign;

    // wordlen A >= wordlen B
    if (n >= m) {
        bi_addc(&tmp, A, B);
        bi_assign(C, tmp);
        bi_delete(&tmp);
        return bi_refine(*C);
    }
    else {
        bi_addc(&tmp, B, A);
        bi_assign(C, tmp);
        bi_delete(&tmp);
        return bi_refine(*C);
    }

    // bi_delete(&tmp);
    return bi_refine(*C);
}

msg bi_sub_AbB(OUT word* result, IN word* op1, IN int borrow_in, IN word* op2) {
    int borrow_out = 0;  // Borrow output (b')

    *result = *op1 - borrow_in;  // Subtract the borrow from the op1
    borrow_out = (*op1 < borrow_in) ? BORROW1 : BORROW0;  // If op1 < borrow_in, set borrow_out to 1

    // If result < op2, update borrow_out and subtract op2
    borrow_out = (*result < *op2) ? borrow_out + 1 : borrow_out;
    *result -= *op2;

    return borrow_out;  // Return the borrow output
}

msg bi_subc(OUT bigint** result, IN bigint** op1, IN bigint** op2) {
    int len_op1 = (*op1)->word_len;
    int len_op2 = (*op2)->word_len;

    // Perform subtraction with borrow
    int borrow = 0;
    for (int j = 0; j < len_op1; j++) {
        word val_op1 = (*op1)->a[j];
        word val_op2 = (j < len_op2) ? (*op2)->a[j] : 0;

        borrow = bi_sub_AbB(&((*result)->a[j]), &val_op1, borrow, &val_op2);
    }

    return bi_refine(*result);  // Refine the result to adjust word length
}

msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B) {
    if (*A == NULL || *B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;

    bigint* tmp = NULL;
    bi_new(&tmp, max_word_len);

    int sign_A = (*A)->sign;
    int sign_B = (*B)->sign;

    if (sign_A != sign_B) {
        // A > 0, B < 0인 경우 (A - (-B) = A + B)
        if (sign_A == NON_NEGATIVE) {
            (*B)->sign = NON_NEGATIVE;  // B를 양수로 변경
            bi_add(&tmp, A, B);  // C = A + B
            (*B)->sign = sign_B;  // B의 부호를 원래대로 복원
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
        // A < 0, B > 0인 경우 (-A - B = -(A + B))
        else {
            (*A)->sign = NON_NEGATIVE;  // A를 양수로 변경
            bi_add(&tmp, A, B);  // C = A + B
            (*A)->sign = sign_A;  // A의 부호를 원래대로 복원
            (tmp)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
    }

    /* 부호가 같은 경우 */
    // A > 0, B > 0인 경우
    if (sign_A == NON_NEGATIVE && sign_B == NON_NEGATIVE) {
        if (bi_compare(A, B) == COMPARE_GREATER) {
            bi_subc(&tmp, A, B);  // A > B일 때 C = A - B
            (tmp)->sign = NON_NEGATIVE;
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
        else {
            // A < B인 경우 C = B - A, 결과 부호는 음수로 설정
            bi_subc(&tmp, B, A);
            (tmp)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
    }

    // A < 0, B < 0인 경우
    if (sign_A == NEGATIVE && sign_B == NEGATIVE) {
        if (bi_compare(A, B) == COMPARE_GREATER) {
            // A > B일 경우 C = B - A, 결과 부호는 양수로 설정
            bi_subc(&tmp, B, A);
            (tmp)->sign = NON_NEGATIVE;
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
        else {
            // A < B일 경우 C = A - B, 결과 부호는 음수로 설정
            bi_subc(&tmp, A, B);
            (tmp)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            bi_assign(C, tmp);
            bi_delete(&tmp);
            return bi_refine(*C);
        }
    }

    return bi_refine(*C);
}

msg bi_mul_AB(OUT word C[2], IN word* A, IN word* B) {
    /* 하나의 워드를 두 개로 나눔 */
    /* 상위비트(A1, B1)와 하위비트(A0, B0)로 나눔 */
    word A1 = *A >> (WORD_BITLEN >> 1);
    word A0 = *A & WORD_MASK;
    word B1 = *B >> (WORD_BITLEN >> 1);
    word B0 = *B & WORD_MASK;

    /* A1B0 + A0B1 = A1B0 + A0B1 + carry */
    word T1 = A1 * B0;
    word T0 = A0 * B1;

    T0 = T1 + T0;
    T1 = (T0 < T1);

    /* A1B1, A0B0 */
    word C1 = A1 * B1;
    word C0 = A0 * B0;

    word T = C0;

    /* C0: 두 개의 워드에서 하위 비트 */
    /* C1: 두 개의 워드에서 상위 비트 */
    C0 = C0 + (T0 << (WORD_BITLEN >> 1));
    C1 = C1 + (T1 << (WORD_BITLEN >> 1)) + (T0 >> (WORD_BITLEN >> 1)) + (C0 < T);

    C[1] = C1;
    C[0] = C0;

    return CLEAR;
}

msg bi_textbook_mulc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    // 결과 저장용 bigint 초기화
    bigint* tmp = NULL;
    bi_new(&tmp, n + m); // 최대 길이 n+m을 가지는 bigint 생성

    // 각 Aj*Bi 결과를 저장할 임시 bigint
    bigint* T = NULL;

    // 모든 곱셈 연산 처리
    for (int Aj = 0; Aj < n; Aj++) {
        for (int Bi = 0; Bi < m; Bi++) {
            bi_new(&T, 2); // 한 번만 생성
            // Aj와 Bi의 곱셈 
            bi_mul_AB(T->a, &((*A)->a[Aj]), &((*B)->a[Bi]));

            // 곱셈 결과를 올바른 위치에 더하기
            bi_word_shift_left(&T, Aj + Bi);
            if (T->word_len < tmp->word_len) {
                bi_addc(&tmp, &tmp, &T);
            }
            else {
                bi_addc(&tmp, &T, &tmp);
            }
        }
    }

    // 최종 결과 C에 할당 및 반환
    bi_assign(C, tmp);

    // 임시 변수 메모리 해제
    bi_delete(&T);
    bi_delete(&tmp);

    return bi_refine(*C);
}


msg bi_improved_textbook_mulc(bigint** C, bigint** A, bigint** B) {

    /* A와 B의 길이가 홀수라면 마지막에 0을 추가하여 짝수로 맞춘다. */
    if ((*A)->word_len % 2 == 1) {
        int new_len = (*A)->word_len + 1; // 길이를 1 증가
        word* temp = (word*)realloc((*A)->a, new_len * sizeof(word));
        if (temp == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return MemAllocErr;
        }
        (*A)->a = temp;
        (*A)->a[new_len - 1] = 0; // 새로 추가된 워드를 0으로 초기화
        (*A)->word_len = new_len;
    }

    if ((*B)->word_len % 2 == 1) {
        int new_len = (*B)->word_len + 1; // 길이를 1 증가
        word* temp = (word*)realloc((*B)->a, new_len * sizeof(word));
        if (temp == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return MemAllocErr;
        }
        (*B)->a = temp;
        (*B)->a[new_len - 1] = 0; // 새로 추가된 워드를 0으로 초기화
        (*B)->word_len = new_len;
    }

    /* A와 B의 워드 길이를 구합니다. */
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* 결과 큰 정수 C 초기화 */
    bigint *tmp = NULL;
    bi_new(&tmp, n + m);

    bigint* T0 = NULL, * T1 = NULL, * T = NULL;
    bigint* temp0 = NULL, * temp1 = NULL;
    bi_new(&temp0, 2);
    bi_new(&temp1, 2);
    bi_new(&T, n + 2);

    /* 주어진 알고리즘대로 모든 조합의 곱셈을 수행 */
    for (int i = 0; i < m; i++) {
        bi_new(&T0, n);
        bi_new(&T1, n);
        for (int j= 0; j < n; j += 2) {
            
            bi_mul_AB(temp0->a, &((*A)->a[j]), &((*B)->a[i]));
            bi_mul_AB(temp1->a, &((*A)->a[j + 1]), &((*B)->a[i]));
            T0->a[j] += temp0->a[0];
            T0->a[j + 1] += temp0->a[1];

            T1->a[j] += temp1->a[0];
            T1->a[j + 1] += temp1->a[1];
        }
  
        // T0과 T1을 합치고, 필요한 만큼 비트 시프트를 적용합니다.
        bi_word_shift_left(&T1, 1); // 시프트 적용
        bi_addc(&T, &T1, &T0); // T = T0 + T1
        bi_word_shift_left(&T, i); // 시프트 적용
        if (T->word_len < tmp->word_len){
            bi_addc(&tmp, &tmp, &T);
        }
        else{
            bi_addc(&tmp, &T ,&tmp);
        }
    }

    /* 초기화 */
    bi_delete(&T0);
    bi_delete(&T1); 
    bi_delete(&temp0);
    bi_delete(&temp1);
    bi_delete(&T);

    bi_assign(C, tmp);
    bi_delete(&tmp);
    return bi_refine(*C); // C의 불필요한 leading zeros 제거
}

msg bi_karatsuba_mulc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* 긴 워드 길이, 짧은 워드 길이 */
    int max_len = (n > m) ? n : m;
    int min_len = (n > m) ? m : n;

    /* 둘 중 하나가 0이면 0 반환 */
    if (bi_zero_check(A) || bi_zero_check(B)) {
        bi_new(C, 1);
        (*C)->a[0] = 0;
        return CLEAR;
    }

    /* FLAG 설정 */
    if (min_len <= FLAG) {
        return bi_improved_textbook_mulc(C, A, B);
    }

    /* word_shift 량 */
    int lw_len = (max_len + 1) >> 1;

    bigint* A1 = NULL, * A0 = NULL;
    bigint* B1 = NULL, * B0 = NULL;
    bigint* T1 = NULL, * T0 = NULL;
    bigint* T_tmp = NULL;
    bigint* S1 = NULL, * S0 = NULL;
    bigint* S = NULL;
    bigint *tmp = NULL;

    bi_new(&A1, lw_len); bi_new(&A0, lw_len);
    bi_new(&B1, lw_len); bi_new(&B0, lw_len);
    array_copy_high(A1->a, (*A)->a, lw_len, n);
    array_copy_low(A0->a, (*A)->a, lw_len, n);
    array_copy_high(B1->a, (*B)->a, lw_len, m);
    array_copy_low(B0->a, (*B)->a, lw_len, m);

    /* A1*B1, A0*B0 */
    bi_karatsuba_mulc(&T1, &A1, &B1);
    bi_karatsuba_mulc(&T0, &A0, &B0);

    /* C = (T1 << 2lw) + T0 */
    bi_assign(&T_tmp, T1);
    bi_word_shift_left(&T_tmp, 2 * lw_len);
    bi_add(&tmp, &T_tmp, &T0);

    /* S1 = A0 - A1 */
    /* S0 = B1 - B0 */
    bi_sub(&S1, &A0, &A1);
    bi_sub(&S0, &B1, &B0);

    /* S = (-1)^(sign(S1) ^ sign(S0) * |S1|*|S0| */
    int sign_S1 = S1->sign;
    int sign_S0 = S0->sign;
    S1->sign = NON_NEGATIVE;
    S0->sign = NON_NEGATIVE;
    bi_karatsuba_mulc(&S, &S1, &S0);

    S->sign = (sign_S1 ^ sign_S0) ? NEGATIVE : NON_NEGATIVE;

    /* S = S + T1 */
    bi_add(&S, &S, &T1);

    /* S = S + T0 */
    bi_add(&S, &S, &T0);

    /* S = S << lw */
    bi_word_shift_left(&S, lw_len);

    /* C = C + S */
    bi_add(C, &tmp, &S);

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&B1);
    bi_delete(&B0);
    bi_delete(&S1);
    bi_delete(&S0);
    bi_delete(&S);
    bi_delete(&T1);
    bi_delete(&T_tmp);
    bi_delete(&T0);
    bi_delete(&tmp);

    return bi_refine(*C);
}

msg bi_mul(OUT bigint** C, IN bigint** A, IN bigint** B) {
    if (*A == NULL || *B == NULL) {
        fprintf(stderr, "Error: NULL input in bi_mul.\n");
        return SrcNULLErr;
    }

    /* 부호 저장 */
    int sign_A = (*A)->sign;
    int sign_B = (*B)->sign;

    /* A와 B를 절댓값으로 변환 */
    (*A)->sign = NON_NEGATIVE;
    (*B)->sign = NON_NEGATIVE;

    /* 절댓값 곱셈 수행 */
    bi_karatsuba_mulc(C, A, B);

    /* 결과 부호 설정 */
    (*C)->sign = (sign_A == sign_B) ? NON_NEGATIVE : NEGATIVE;

    /* A와 B의 원래 부호 복구 */
    (*A)->sign = sign_A;
    (*B)->sign = sign_B;

    return CLEAR;
}

msg bi_long_div(OUT bigint** Q, OUT bigint** R, IN bigint** A, IN bigint** B) {
    /* bigint NULL 체크 */
    if (*A == NULL || *B == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Zero Divisor 체크 */
    if (bi_zero_check(B)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* Q와 R 초기화 */
    bi_new(Q, n);
    bi_new(R, n);

    /* 비트 단위 나눗셈 */
    for (int j = (n * WORD_BITLEN) - 1; j >= 0; j--) {

        /* R = 2R */
        bi_doubling(*R);

        /* R ^= Aj */
        if (((*A)->a[j / WORD_BITLEN] & ((word)1 << (j % WORD_BITLEN))) != 0) {
            (*R)->a[0] ^= 1;
        }

        /* R >= B 체크 */

        if (bi_compare(R, B) != COMPARE_LESS) {
            /* Q = Q + (1 << j) */
            (*Q)->a[j / WORD_BITLEN] ^= ((word)1 << (j % WORD_BITLEN));

            /* R - B */
            bi_subc(R, R, B);
        }
    }

    bi_refine(*Q);
    bi_refine(*R);

    return CLEAR;
}

msg bi_mod(UPDATE bigint** remainder, IN bigint** divisor) {
    bigint* Q = NULL, * R = NULL;
    bi_long_div(&Q, &R, remainder, divisor);
    bi_assign(remainder, R);

    bi_delete(&Q);
    bi_delete(&R);
    return CLEAR;
}

msg bi_div(OUT bigint** Q, OUT bigint** R, IN bigint** A, IN bigint** B) {
    /* bigint NULL 체크 */
    if (*A == NULL || *B == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Zero Divisor 체크 */
    if (bi_zero_check(B)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    int sign_A = (*A)->sign;
    int sign_B = (*B)->sign;

    (*A)->sign = NON_NEGATIVE;  // A 절댓값
    (*B)->sign = NON_NEGATIVE;  // B 절댓값
    bi_long_div(Q, R, A, B);  // 절댓값 기준 나눗셈 수행


    /* A가 음수인 경우 Q = Q + 1, R = B - R */
    if (sign_A == NEGATIVE && !bi_zero_check(R)) {
        bi_plus_one(Q);
        bi_sub(R, B, R);
    }

    (*Q)->sign = (sign_A == sign_B) ? NON_NEGATIVE : NEGATIVE;
    (*R)->sign = NON_NEGATIVE;   // R은 항상 양수
    (*A)->sign = sign_A;  // A 절댓값
    (*B)->sign = sign_B;  // B 절댓값

    return CLEAR;
}

msg bi_l2r_mod_exp(OUT bigint** C, IN bigint** X, IN bigint** N, IN bigint** M) {

    if ((*X == NULL) || (*M == NULL)) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* t 초기화: t = 1 */
    bi_set_from_string(C, "1", 2);

    /* N의 전체 비트 길이 계산 */
    int total_bits = (*N)->word_len * WORD_BITLEN;

    /* Left-to-Right Modular Exponentiation */
    for (int i = total_bits - 1; i >= 0; i--) {
        /* t = t^2 */
        bi_karatsuba_mulc(C, C, C);

        /* t = t mod M */
        bi_mod(C, M);

        /* 현재 비트 검사: ni = (N >> i) & 1 */
        if (((*N)->a[i / WORD_BITLEN] & ((word)1 << (i % WORD_BITLEN))) != 0) {
            /* t = t * X */
            bi_karatsuba_mulc(C, C, X);

            /* t = t mod M */
            bi_mod(C, M);
        }
    }

    return CLEAR;
}

msg bi_r2l_mod_exp(OUT bigint** C, IN bigint** X, IN bigint** N, IN bigint** M) {

    if ((*X == NULL) || (*M == NULL)) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    bigint* t1 = NULL;
    /* t0, t1 초기화: t0 = 1, t1 = X */
    bi_set_one(C);
    bi_assign(&t1, *X);

    /* N의 전체 비트 길이 계산 */
    int total_bits = (*N)->word_len * WORD_BITLEN;

    /* Right-to-Left Modular Exponentiation */
    for (int i = 0; i < total_bits; i++) {
        /* 현재 비트 검사: ni = (N >> i) & 1 */
        if (((*N)->a[i / WORD_BITLEN] & ((word)1 << (i % WORD_BITLEN))) != 0) {
            /* t0 = t0*t1^Ni */
            bi_karatsuba_mulc(C, C, &t1);

            /* t0 = t0 mod M */
            bi_mod(C, M);
        }
        /* t1 = t1^2 mod M */
        bi_karatsuba_mulc(&t1, &t1, &t1);

        bi_mod(&t1, M);
    }
    return CLEAR;
}

msg bi_barrett_red(OUT bigint** R, IN bigint** A, IN bigint** N, IN bigint** T) {
    /* 워드 길이 저장 */
    unsigned int n = (*N)->word_len;
    unsigned int double_n = (*A)->word_len;

    /* 워드 길이 2배 체크 */
    if ((double_n >> 1) != n) {
        fprintf(stderr, WordLenNotDoubleErrMsg);
        return WordLenNotDoubleErr;
    }

    /* 부호 NON NEGATIVE 확인 */
    if ((*A)->sign != NON_NEGATIVE) {
        fprintf(stderr, SignNEGErrMsg);
        return SignNEGErr;
    }
    bigint* Q_hat = NULL;
    bigint* A_tmp = NULL;
    bigint* R_tmp = NULL;

    /* Q = ((A >> w(n - 1)) * T) >> w(n + 1) */
    bi_assign(&A_tmp, *A);
    bi_word_shift_right(&A_tmp, n - 1);
    bi_karatsuba_mulc(&Q_hat, &A_tmp, T);
    bi_word_shift_right(&Q_hat, n + 1);

    /* R = A - N*Q */
    bi_karatsuba_mulc(&R_tmp, N, &Q_hat);
    bi_sub(R, A, &R_tmp);

    bi_delete(&R_tmp);

    /* refine */
    bi_refine(*R);
    bi_refine(*N);

    /* R >= N이라면 R - N 수행 */
    while (bi_compare(R, N) != COMPARE_LESS) {
        bi_sub(R, R, N);
    }
    bi_delete(&Q_hat);
    bi_delete(&A_tmp);

    return CLEAR;
}