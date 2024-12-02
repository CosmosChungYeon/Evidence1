
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "const.h"

msg bi_add_ABc(OUT word* C, IN word* A, IN word* B, IN int c) {
    int c_out = 0;  // 반환용 carry(c')
    *C = *A + *B;
    c_out = (*C < *A) ? CARRY1 : CARRY0;     // if A + B < A, then c' = 1

    *C += c;
    c_out = (*C < c) ? c_out + 1 : c_out;   // if A + B + c < c, then c' += 1 

    return c_out;   // c' 반환
}

msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    /* [n >= m] */
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* tmp 초기화 */
    bigint* tmp = NULL;
    bi_new(&tmp, n + 1);  // +1 워드는 최종 carry를 위한 공간

    /* carry 연산하면서 A + B 수행 */
    int c = 0;
    for (int j = 0; j < n; j++) {
        word a_value = (*A)->a[j];
        word b_value = (j < m) ? (*B)->a[j] : 0;

        c = bi_add_ABc(&(tmp->a[j]), &a_value, &b_value, c);
    }

    /* 마지막 carry 처리 */
    tmp->a[n] = (c == CARRY1) ? CARRY1 : CARRY0;

    /* C를 삭제하기 때문에 둘다 sign일 경우 음수로 지정 */
    tmp->sign = ((*A)->sign == NEGATIVE && (*B)->sign == NEGATIVE) ? NEGATIVE : NON_NEGATIVE;

    // 결과를 `C`에 복사
    bi_assign(C, tmp);

    // 메모리 해제
    bi_delete(&tmp);
    return bi_refine(*C);
}

msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B) {
    if (*A == NULL || *B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;

    bi_new(C, max_word_len);

    if ((*A)->sign != (*B)->sign) {
        // A > 0 and B < 0 
        if ((*A)->sign == NON_NEGATIVE) {
            (*B)->sign = NON_NEGATIVE;
            msg result = bi_sub(C, A, B);
            (*B)->sign = NEGATIVE;
            return result;
        }
        // A < 0 and B > 0 
        else {
            (*A)->sign = NON_NEGATIVE;
            msg result = bi_sub(C, B, A);
            (*A)->sign = NEGATIVE;
            return result;
        }
    }

    /* 부호가 같은 경우 */
    (*C)->sign = (*A)->sign;

    // wordlen A >= wordlen B
    if (n >= m) {
        return bi_addc(C, A, B);
    }
    else {
        return bi_addc(C, B, A);
    }

    return bi_refine(*C);
}

msg bi_sub_AbB(OUT word* C, IN word* A, IN int b, IN word* B) {
    int b_out = 0;  // 반환용 borrow(b')
    *C = *A - b;
    b_out = (*A < b) ? BORROW1 : BORROW0;    // if A < b, then b' = 1

    b_out = (*C < *B) ? b_out + 1 : b_out;   // if C < B, then b' += 1 
    *C -= *B;

    return b_out;   // b' 반환
}

msg bi_subc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    /* [n >= m] */
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* borrow 연산하면서 A - B 수행 */
    int b = 0;
    for (int j = 0; j < n; j++) {
        word a_value = (*A)->a[j];
        word b_value = (j < m) ? (*B)->a[j] : 0;
        b = bi_sub_AbB(&((*C)->a[j]), &a_value, b, &b_value);
    }

    return bi_refine(*C);
}

msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B) {
    if (*A == NULL || *B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;

    bi_new(C, max_word_len);

    int sign_A = (*A)->sign;
    int sign_B = (*B)->sign;

    if (sign_A != sign_B) {
        // A > 0, B < 0인 경우 (A - (-B) = A + B)
        if (sign_A == NON_NEGATIVE) {
            (*B)->sign = NON_NEGATIVE;  // B를 양수로 변경
            msg result = bi_add(C, A, B);  // C = A + B
            (*B)->sign = sign_B;  // B의 부호를 원래대로 복원
            return result;
        }
        // A < 0, B > 0인 경우 (-A - B = -(A + B))
        else {
            (*A)->sign = NON_NEGATIVE;  // A를 양수로 변경
            msg result = bi_add(C, A, B);  // C = A + B
            (*A)->sign = sign_A;  // A의 부호를 원래대로 복원
            (*C)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            return result;
        }
    }

    /* 부호가 같은 경우 */
    // A > 0, B > 0인 경우
    if (sign_A == NON_NEGATIVE && sign_B == NON_NEGATIVE) {
        if (bi_compare(A, B) == COMPARE_GREATER) {
            return bi_subc(C, A, B);  // A > B일 때 C = A - B
        }
        else {
            // A < B인 경우 C = B - A, 결과 부호는 음수로 설정
            msg result = bi_subc(C, B, A);
            (*C)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            return result;
        }
    }

    // A < 0, B < 0인 경우
    if (sign_A == NEGATIVE && sign_B == NEGATIVE) {
        if (bi_compare(A, B) == COMPARE_GREATER) {
            // A > B일 경우 C = B - A, 결과 부호는 양수로 설정
            return bi_subc(C, B, A);
        }
        else {
            // A < B일 경우 C = A - B, 결과 부호는 음수로 설정
            msg result = bi_subc(C, A, B);
            (*C)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
            return result;
        }
    }

    return bi_refine(*C);
}

msg bi_mul_AB(OUT word C[2], IN word* A, IN word* B) {
    /* 하나의 워드를 두 개로 나눔 */
    /* 상위비트(A1, B1)와 하위비트(A0, B0)로 나눔 */
    word A1 = *A >> (WORD_BITLEN / 2);
    word A0 = *A & WORD_MASK;
    word B1 = *B >> (WORD_BITLEN / 2);
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
    C0 = C0 + (T0 << (WORD_BITLEN / 2));
    C1 = C1 + (T1 << (WORD_BITLEN / 2)) + (T0 >> (WORD_BITLEN / 2)) + (C0 < T);

    C[1] = C1;
    C[0] = C0;

    return CLEAR;
}

msg bi_textbook_mulc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    msg result;

    /* 워드 길이 2로 초기화 */
    bi_new(C, 2);

    /* Aj*Bi 단일 워드 곱셈의 합 */
    for (int Aj = 0; Aj < n; Aj++) {
        for (int Bi = 0; Bi < m; Bi++) {
            /* 단일 워드 곱셈 저장 */
            bigint* T = NULL;
            result = bi_new(&T, 2);
            result = bi_mul_AB(T->a, &((*A)->a[Aj]), &((*B)->a[Bi]));

            /* Aj + Bi만큼 left shift */
            bi_word_shift_left(&T, Aj + Bi);

            /* 2 + Aj + Bi에 carry 발생을 고려하여 C의 워드 길이 1 증가 */
            int required_len = 2 + Aj + Bi + CARRY1;
            if ((*C)->word_len < required_len) {
                // bigint의 배열 확장
                word* temp = (word*)realloc((*C)->a, required_len * sizeof(word));
                if (temp == NULL) {
                    fprintf(stderr, MemAllocErrMsg);
                    return MemAllocErr;
                }
                (*C)->a = temp;

                /* 새로 확장된 부분을 0으로 초기화 */
                memset((*C)->a + (*C)->word_len, 0, (required_len - (*C)->word_len) * sizeof(word));
                (*C)->word_len = required_len;
            }

            /* C = C + T */
            result = bi_addc(C, C, &T);

            bi_delete(&T);
        }
    }
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
    bi_new(C, n + m);

    bigint* T0 = NULL, * T1 = NULL, * T = NULL;
    bigint* temp0 = NULL, * temp1 = NULL;
    /* 주어진 알고리즘대로 모든 조합의 곱셈을 수행 */
    for (int i = 0; i < m; i++) {
        bi_new(&T0, n);
        bi_new(&T1, n);

        for (int k = 0; k < n; k += 2) {
            bi_new(&temp0, 2);
            bi_new(&temp1, 2);
            bi_mul_AB(temp0->a, &((*A)->a[k]), &((*B)->a[i]));
            bi_mul_AB(temp1->a, &((*A)->a[k + 1]), &((*B)->a[i]));
            T0->a[k] += temp0->a[0];
            T0->a[k + 1] += temp0->a[1];

            T1->a[k] += temp1->a[0];
            T1->a[k + 1] += temp1->a[1];

            /* 초기화 */
            bi_delete(&temp0);
            bi_delete(&temp1);
        }

        // T0과 T1을 합치고, 필요한 만큼 비트 시프트를 적용합니다.
        bi_new(&T, n + 2);
        bi_word_shift_left(&T1, 1); // 시프트 적용
        bi_addc(&T, &T1, &T0); // T = T0 + T1
        bi_word_shift_left(&T, i); // 시프트 적용
        bi_addc(C, C, &T);  // C = C + T

        /* C에서 carry 발생을 고려하여 C의 워드 길이 1 증가 */
        int required_len = n + m;
        if ((*C)->word_len < required_len) {
            // bigint의 배열 확장
            word* temp = (word*)realloc((*C)->a, required_len * sizeof(word));
            if (temp == NULL) {
                fprintf(stderr, MemAllocErrMsg);
                return MemAllocErr;
            }
            (*C)->a = temp;

            /* 새로 확장된 부분을 0으로 초기화 */
            memset((*C)->a + (*C)->word_len, 0, (required_len - (*C)->word_len) * sizeof(word));
            (*C)->word_len = required_len;
        }


        /* 초기화 */
        bi_delete(&T0);
        bi_delete(&T1);
        bi_delete(&T);
    }

    return bi_refine(*C); // C의 불필요한 leading zeros 제거
}

msg bi_karatsuba_mulc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* 긴 워드 길이, 짧은 워드 길이 */
    int max_len = (n > m) ? n : m;
    int min_len = (n > m) ? m : n;

    /* 둘 중 하나가 0이면 0 반환 */
    if (((n == 1) && ((*A)->a[0] == 0)) || ((m == 1) && ((*B)->a[0] == 0))) {
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
    bigint* S_sum1 = NULL, * S_sum2 = NULL;
    bigint* C_tmp = NULL;

    bi_new(&A1, lw_len); bi_new(&A0, lw_len);
    bi_new(&B1, lw_len); bi_new(&B0, lw_len);

    // A1: 상위 부분 복사
    for (int i = 0; i < A1->word_len; i++) {
        if (i + lw_len < n) {
            A1->a[i] = (*A)->a[i + lw_len];
        }
        else {
            A1->a[i] = 0;  // 나머지는 0으로 채움
        }
    }

    // A0: 하위 부분 복사
    for (int i = 0; i < lw_len; i++) {
        if (i < n) {
            A0->a[i] = (*A)->a[i];
        }
        else {
            A0->a[i] = 0;  // 나머지는 0으로 채움
        }
    }

    // B1: 상위 부분 복사
    for (int i = 0; i < B1->word_len; i++) {
        if (i + lw_len < m) {
            B1->a[i] = (*B)->a[i + lw_len];
        }
        else {
            B1->a[i] = 0;  // 나머지는 0으로 채움
        }
    }

    // B0: 하위 부분 복사
    for (int i = 0; i < lw_len; i++) {
        if (i < m) {
            B0->a[i] = (*B)->a[i];
        }
        else {
            B0->a[i] = 0;  // 나머지는 0으로 채움
        }
    }

    /* A1*B1, A0*B0 */
    bi_karatsuba_mulc(&T1, &A1, &B1);
    bi_karatsuba_mulc(&T0, &A0, &B0);

    /* C = (T1 << 2lw) + T0 */
    bi_assign(&T_tmp, T1);
    bi_word_shift_left(&T_tmp, 2 * lw_len);
    bi_add(C, &T_tmp, &T0);

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
    bi_add(&S_sum1, &S, &T1);

    /* S = S + T0 */
    bi_add(&S_sum2, &S_sum1, &T0);

    /* S = S << lw */
    bi_word_shift_left(&S_sum2, lw_len);

    /* C = C + S */
    bi_assign(&C_tmp, *C);
    bi_add(C, &C_tmp, &S_sum2);

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&B1);
    bi_delete(&B0);
    bi_delete(&S1);
    bi_delete(&S0);
    bi_delete(&S);
    bi_delete(&T1);
    bi_delete(&T_tmp);
    bi_delete(&S_sum1);
    bi_delete(&T0);
    bi_delete(&S_sum2);
    bi_delete(&C_tmp);

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
    //bi_improved_textbook_mulc(C, A, B);
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
    if (((*B)->word_len == 1) && ((*B)->a[0] == 0x0)) {
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
        bigint* tmpB = NULL;
        bigint* tmpR = NULL;
        bi_assign(&tmpB, *B);
        bi_assign(&tmpR, *R);

        bi_refine(tmpB);
        bi_refine(tmpR);

        if (bi_compareABS(&tmpR, &tmpB) != COMPARE_LESS) {
            /* Q = Q + (1 << j) */
            (*Q)->a[j / WORD_BITLEN] ^= ((word)1 << (j % WORD_BITLEN));

            /* R - B */
            bi_subc(R, R, B);
        }
        bi_delete(&tmpB);
        bi_delete(&tmpR);
    }

    bi_refine(*Q);
    bi_refine(*R);

    return CLEAR;
}

msg bi_div(OUT bigint** Q, OUT bigint** R, IN bigint** A, IN bigint** B) {
    /* bigint NULL 체크 */
    if (*A == NULL || *B == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Zero Divisor 체크 */
    if (((*B)->word_len == 1) && ((*B)->a[0] == 0x0)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    int sign_A = (*A)->sign;
    int sign_B = (*B)->sign;

    (*A)->sign = NON_NEGATIVE;  // A 절댓값
    (*B)->sign = NON_NEGATIVE;  // B 절댓값
    bi_long_div(Q, R, A, B);  // 절댓값 기준 나눗셈 수행

    /* A가 음수인 경우 Q = Q + 1, R = B - R */
    if (sign_A == NEGATIVE) {
        bigint* one = NULL;
        bi_set_from_string(&one, "1", 2);  // 1 생성
        bi_addc(Q, Q, &one);
        bi_delete(&one);

        bigint* new_R = NULL;
        bi_sub(&new_R, B, R);
        bi_assign(R, new_R);  // R 업데이트
        bi_delete(&new_R);
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
        bigint* t_tmp = NULL;
        bi_assign(&t_tmp, *C);
        bi_karatsuba_mulc(C, &t_tmp, &t_tmp);
        bi_delete(&t_tmp);
        
        /* t = t mod M */
        bigint* Q = NULL, * R = NULL;
        bi_long_div(&Q, &R, C, M);
        bi_assign(C, R);
        bi_delete(&Q);
        bi_delete(&R);

        /* 현재 비트 검사: ni = (N >> i) & 1 */
        if (((*N)->a[i / WORD_BITLEN] & ((word)1 << (i % WORD_BITLEN))) != 0) {
            /* t = t * X */
            bigint* t_tmp2 = NULL;
            bi_assign(&t_tmp2, *C);
            bi_karatsuba_mulc(C, &t_tmp2, X);
            bi_delete(&t_tmp2);

            /* t = t mod M */
            bi_long_div(&Q, &R, C, M);
            bi_assign(C, R);
            bi_delete(&Q);
            bi_delete(&R);
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
    bi_set_from_string(C, "1", 2);
    bi_assign(&t1, *X);
    /* N의 전체 비트 길이 계산 */
    int total_bits = (*N)->word_len * WORD_BITLEN;

    /* Right-to-Left Modular Exponentiation */
    for (int i = 0; i < total_bits; i++) {
        /* 현재 비트 검사: ni = (N >> i) & 1 */
        if (((*N)->a[i / WORD_BITLEN] & ((word)1 << (i % WORD_BITLEN))) != 0) {
            /* t0 = t0*t1^Ni */
            bigint* t0_tmp = NULL;
            bi_assign(&t0_tmp, *C);
            bi_karatsuba_mulc(C, &t0_tmp, &t1);
            bi_delete(&t0_tmp);
            
            /* t0 = t0 mod M */
            bigint* Q = NULL, * R = NULL;
            bi_long_div(&Q, &R, C, M);
            bi_assign(C, R);
            bi_delete(&Q);
            bi_delete(&R);
        }
        /* t1 = t1^2 mod M */
        bigint* t1_tmp = NULL;
        bi_assign(&t1_tmp, t1);
        bi_karatsuba_mulc(&t1, &t1_tmp, &t1_tmp);
        bi_delete(&t1_tmp);
        bigint* Q = NULL, * R = NULL;
        bi_long_div(&Q, &R, &t1, M);
        bi_assign(&t1, R);
        bi_delete(&Q);
        bi_delete(&R);
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
    while (bi_compareABS(R, N) != COMPARE_LESS) {
        bigint* new_R = NULL;
        bi_sub(&new_R, R, N);
        bi_assign(R, new_R);
        bi_delete(&new_R);
    }
    bi_delete(&Q_hat);
    bi_delete(&A_tmp);

    return CLEAR;
}