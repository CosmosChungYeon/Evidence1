
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

/* bi_add에서는 잘 되고, bi_textbook_mul에서는 안 되는 addc */
//msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B) {
//    /* [n >= m] */
//    int n = (*A)->word_len;
//    int m = (*B)->word_len;
//
//
//    /* carry 연산하면서 A + B 수행 */
//
//    int c = 0;
//    for (int j = 0; j < n; j++) {
//        word b_value = (j < m) ? (*B)->a[j] : 0;
//        c = bi_add_ABc(&((*C)->a[j]), &((*A)->a[j]), &b_value, c);
//    }
//    if (c == CARRY1) {
//        (*C)->a[n] = CARRY1;
//    }
// 
//    return bi_refine(*C);
//}

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
    if (c == CARRY1) {
        tmp->a[n] = CARRY1;
    }

    /* C를 삭제하기 때문에 둘다 sign일 경우 음수로 지정 */
    if ((*A)->sign == NEGATIVE && (*B)->sign == NEGATIVE) {
        tmp->sign = NEGATIVE;
    }
    else {
        tmp->sign = NON_NEGATIVE;
    }

    // 결과를 `C`에 복사
    bi_assign(C, tmp);

    // 메모리 해제
    bi_delete(&tmp);
    return bi_refine(*C);
}

msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;
    bi_new(C, max_word_len);

    if (*A == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }
    if (*B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    // A > 0 and B < 0 
    if ((*A)->sign == NON_NEGATIVE && (*B)->sign == NEGATIVE) {
        (*B)->sign = NON_NEGATIVE;
        msg result = bi_sub(C, A, B);
        (*B)->sign = NEGATIVE;
        return result;
    }

    // A < 0 and B > 0 
    if ((*A)->sign == NEGATIVE && (*B)->sign == NON_NEGATIVE) {
        (*A)->sign = NON_NEGATIVE;
        msg result = bi_sub(C, B, A);
        (*A)->sign = NEGATIVE;
        return result;
    }

    // A < 0 and B < 0
    if (((*A)->sign && (*B)->sign) == NEGATIVE) {
        (*C)->sign = NEGATIVE;
    }

    // wordlen A >= wordlen B
    if ((*A)->word_len >= (*B)->word_len) {
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
    int n = (*A)->word_len;
    int m = (*B)->word_len;
    int max_word_len = (n > m) ? n + 1 : m + 1;
    bi_new(C, max_word_len);

    if (*A == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }
    if (*B == NULL) {
        printf("%s", SrcNULLErrMsg);
        return SrcNULLErr;
    }

    // A > 0, B > 0인 경우
    if ((*A)->sign == NON_NEGATIVE && (*B)->sign == NON_NEGATIVE) {
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
    if ((*A)->sign == NEGATIVE && (*B)->sign == NEGATIVE) {
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

    // A > 0, B < 0인 경우 (A - (-B) = A + B)
    if ((*A)->sign == NON_NEGATIVE && (*B)->sign == NEGATIVE) {
        (*B)->sign = NON_NEGATIVE;  // B를 양수로 변경
        msg result = bi_add(C, A, B);  // C = A + B
        (*B)->sign = NEGATIVE;  // B의 부호를 원래대로 복원
        return result;
    }

    // A < 0, B > 0인 경우 (-A - B = -(A + B))
    if ((*A)->sign == NEGATIVE && (*B)->sign == NON_NEGATIVE) {
        (*A)->sign = NON_NEGATIVE;  // A를 양수로 변경
        msg result = bi_add(C, A, B);  // C = A + B
        (*A)->sign = NEGATIVE;  // A의 부호를 원래대로 복원
        (*C)->sign = NEGATIVE;  // 결과 부호를 음수로 설정
        return result;
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
    

    /* 임시 R 생성 */
    bigint* tmpR = NULL;
    bi_new(&tmpR, n);

    /* 비트 단위 나눗셈 */
    for (int j = (n * WORD_BITLEN) - 1; j >= 0; j--) {
        
        /* R = 2R */
        bi_doubling(tmpR);

        /* R ^= Aj */
        if (((*A)->a[j / WORD_BITLEN] & (1 << (j % WORD_BITLEN))) != 0) {
            tmpR->a[0] ^= 1;
        }

        /* R >= B 체크 */
        bigint* tmpB = NULL;
        bigint* tmpRR = NULL;
        bi_assign(&tmpB, *B);
        bi_assign(&tmpRR, tmpR);
        bi_refine(tmpB);
        bi_refine(tmpRR);
        if (bi_compareABS(&tmpRR, &tmpB) != COMPARE_LESS) {
            /* Q = Q + (1 << j) */
            (*Q)->a[j / WORD_BITLEN] ^= (1 << (j % WORD_BITLEN));

            /* R - B */
            bi_subc(&tmpR, &tmpR, B);

            /* subc의 refine 문제 해결 */
            if (tmpR->word_len < n) {
                // bigint의 배열 확장
                word* temp = (word*)realloc(tmpR->a, n * sizeof(word));
                if (temp == NULL) {
                    fprintf(stderr, MemAllocErrMsg);
                    return MemAllocErr;
                }
                tmpR->a = temp;

                /* 새로 확장된 부분을 0으로 초기화 */
                memset(tmpR->a + tmpR->word_len, 0, (n - tmpR->word_len) * sizeof(word));
                tmpR->word_len = n;
            }
        }
        bi_delete(&tmpB);
        bi_delete(&tmpRR);
    }

    /* R = tmpR */
    bi_assign(R, tmpR);
    bi_delete(&tmpR);

    bi_refine(*Q);
    bi_refine(*R);
    return CLEAR;
}