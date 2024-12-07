
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "const.h"

msg bi_add_ABc(OUT word* res, IN word* op1, IN word* op2, IN int carry_in) {
    int carry_out = 0; // Carry out (c')

    /* Add op1 and op2 */
    *res = *op1 + *op2;
    carry_out = (*res < *op1) ? CARRY1 : CARRY0; // Check for carry: if op1 + op2 < op1, carry = 1

    /* Add the input carry */
    *res += (word)carry_in;
    carry_out += (*res < (word)carry_in) ? CARRY1 : CARRY0; // If result + carry_in < carry_in, additional carry

    return (msg)carry_out; // Return the carry out
}

msg bi_addc(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    /* Ensure op1 has more or equal word length (op1_wlen >= op2_wlen) */
    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;

    /* Initialize a temporary bigint to store the result, with extra space for the final carry */
    bigint* tmp_res = NULL;
    bi_new(&tmp_res, op1_wlen + 1); // +1 word for the final carry

    /* Perform addition word by word with carry propagation */
    int carry = 0;
    for (int idx = 0; idx < op1_wlen; idx++) {
        word val_op1 = (*op1)->a[idx];
        word val_op2 = (idx < op2_wlen) ? (*op2)->a[idx] : 0; // Use 0 if op2 is shorter

        carry = bi_add_ABc(&(tmp_res->a[idx]), &val_op1, &val_op2, carry);
    }

    /* Handle the final carry */
    tmp_res->a[op1_wlen] = (carry == CARRY1) ? CARRY1 : CARRY0;

    /* Set the sign of the result */
    tmp_res->sign = ((*op1)->sign == NEGATIVE && (*op2)->sign == NEGATIVE) ? NEGATIVE : NON_NEGATIVE;

    /* Assign the result to the output and clean up temporary memory */
    bi_assign(res, tmp_res);
    bi_delete(&tmp_res);

    return bi_refine(*res); // Refine the result
}

msg bi_add(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    /* Check if either input big integer is NULL */
    if (*op1 == NULL || *op2 == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;
    int max_wlen = (op1_wlen > op2_wlen) ? op1_wlen + 1 : op2_wlen + 1;

    bigint* tmp = NULL;
    bi_new(&tmp, max_wlen);

    /* Handle case where signs are different */
    if ((*op1)->sign != (*op2)->sign) {
        /* Case: op1 > 0 and op2 < 0 */
        if ((*op1)->sign == NON_NEGATIVE) {
            (*op2)->sign = NON_NEGATIVE;
            bi_sub(&tmp, op1, op2);
            (*op2)->sign = NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
        /* Case: op1 < 0 and op2 > 0 */
        else {
            (*op1)->sign = NON_NEGATIVE;
            bi_sub(&tmp, op2, op1);
            (*op1)->sign = NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
    }

    /* Case where signs are the same */
    (tmp)->sign = (*op1)->sign;

    /* Perform addition with carry */
    if (op1_wlen >= op2_wlen) {
        bi_addc(&tmp, op1, op2);
        bi_assign(res, tmp);
        bi_delete(&tmp);
        return bi_refine(*res);
    }
    else {
        bi_addc(&tmp, op2, op1);
        bi_assign(res, tmp);
        bi_delete(&tmp);
        return bi_refine(*res);
    }

    return bi_refine(*res);
}

msg bi_sub_AbB(OUT word* res, IN word* op1, IN int borrow_in, IN word* op2) {
    int borrow_out = 0;  // Borrow output (b')

    *res = *op1 - (word)borrow_in;  // Subtract the borrow from the op1
    borrow_out = (*op1 < (word)borrow_in) ? BORROW1 : BORROW0;  // If op1 < borrow_in, set borrow_out to 1

    /* If result < op2, update borrow_out and subtract op2 */
    borrow_out = (*res < *op2) ? borrow_out + 1 : borrow_out;
    *res -= *op2;

    return (msg)borrow_out;  // Return the borrow output
}

msg bi_subc(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;

    /* Perform subtraction with borrow */
    int borrow = 0;
    for (int idx = 0; idx < op1_wlen; idx++) {
        word val_op1 = (*op1)->a[idx];
        word val_op2 = (idx < op2_wlen) ? (*op2)->a[idx] : 0;

        borrow = bi_sub_AbB(&((*res)->a[idx]), &val_op1, borrow, &val_op2);
    }

    return bi_refine(*res);  // Refine the result
}

msg bi_sub(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    /* Check if either input big integer is NULL */
    if (*op1 == NULL || *op2 == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;
    int max_wlen = (op1_wlen > op2_wlen) ? op1_wlen + 1 : op2_wlen + 1;

    bigint* tmp = NULL;
    bi_new(&tmp, max_wlen);

    int sign_op1 = (*op1)->sign;
    int sign_op2 = (*op2)->sign;

    /* Handle case where signs are different */
    if (sign_op1 != sign_op2) {
        /* Case: op1 > 0 and op2 < 0 (A - (-B) = A + B) */
        if (sign_op1 == NON_NEGATIVE) {
            (*op2)->sign = NON_NEGATIVE;
            bi_add(&tmp, op1, op2);
            (*op2)->sign = sign_op2;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
        /* Case: op1 < 0 and op2 > 0 (-A - B = -(A + B)) */
        else {
            (*op1)->sign = NON_NEGATIVE;
            bi_add(&tmp, op1, op2);
            (*op1)->sign = sign_op1;
            (tmp)->sign = NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
    }

    /* Case where signs are the same */
    /* Both operands are positive */
    if (sign_op1 == NON_NEGATIVE && sign_op2 == NON_NEGATIVE) {
        /* Case: op1 > op2: Perform subtraction res = op1 - op2 */
        if (bi_compare(op1, op2) == COMPARE_GREATER) {
            bi_subc(&tmp, op1, op2);
            (tmp)->sign = NON_NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
        /* Case: op1 < op2: Perform subtraction res = op2 - op1 */
        else {
            bi_subc(&tmp, op2, op1);
            (tmp)->sign = NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
    }

    /* Both operands are negative */
    if (sign_op1 == NEGATIVE && sign_op2 == NEGATIVE) {
        /* Case: op1 > op2: Perform subtraction res = op2 - op1 */
        if (bi_compare(op1, op2) == COMPARE_GREATER) {
            bi_subc(&tmp, op2, op1);
            (tmp)->sign = NON_NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
        /* Case: op1 < op2: Perform subtraction res = op1 - op2 */
        else {
            bi_subc(&tmp, op1, op2);
            (tmp)->sign = NEGATIVE;
            bi_assign(res, tmp);
            bi_delete(&tmp);
            return bi_refine(*res);
        }
    }

    return bi_refine(*res);
}

msg bi_mul_AB(OUT word res[2], IN word* A, IN word* B) {
    /* Split a single word into two parts */
    /* Divide into upper bits (A1, B1) and lower bits (A0, B0) */
    word A1 = *A >> (WORD_BITLEN >> 1);
    word A0 = *A & WORD_MASK;
    word B1 = *B >> (WORD_BITLEN >> 1);
    word B0 = *B & WORD_MASK;

    /* Compute A1 * B0 + A0 * B1 with carry */
    word T1 = A1 * B0;
    word T0 = A0 * B1;

    T0 = T1 + T0;
    T1 = (T0 < T1);

    /* Compute A1 * B1 and A0 * B0 */
    word C1 = A1 * B1;
    word C0 = A0 * B0;

    word T = C0;

    /* Compute lower and upper parts of the result */
    C0 = C0 + (T0 << (WORD_BITLEN >> 1));
    C1 = C1 + (T1 << (WORD_BITLEN >> 1))
         + (T0 >> (WORD_BITLEN >> 1))
         + (C0 < T);

    /* Store the result in the output array */
    res[1] = C1;
    res[0] = C0;

    return CLEAR;
}

msg bi_textbook_mulc(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;

    bigint* tmp = NULL;
    bi_new(&tmp, op1_wlen + op2_wlen);

    /* Temporary bigint to store intermediate Aj * Bi results */
    bigint* AjBi = NULL;

    /* Perform the multiplication operation for all words in both operands */
    for (int Aj = 0; Aj < op1_wlen; Aj++) {
        for (int Bi = 0; Bi < op2_wlen; Bi++) {
            bi_new(&AjBi, 2);
            /* Multiply the words at indices Aj and Bi */
            bi_mul_AB(AjBi->a, &((*op1)->a[Aj]), &((*op2)->a[Bi]));

            /* Shift the result to the correct position based on word indices Aj and Bi */
            bi_word_shift_left(&AjBi, Aj + Bi);

            /* Add the shifted product to the current result */
            if (AjBi->word_len < tmp->word_len) {
                bi_addc(&tmp, &tmp, &AjBi);
            }
            else {
                bi_addc(&tmp, &AjBi, &tmp);
            }
        }
    }

    bi_assign(res, tmp);

    bi_delete(&AjBi);
    bi_delete(&tmp);

    return bi_refine(*res);
}

msg bi_improved_textbook_mulc(bigint** res, bigint** op1, bigint** op2) {
    /* If the length of op1 or op2 is odd, extend it to even by appending a zero */
    if ((*op1)->word_len % 2 == 1) {
        int new_len = (*op1)->word_len + 1;
        word* tmp = (word*)realloc((*op1)->a, new_len * sizeof(word));
        if (tmp == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return MemAllocErr;
        }
        (*op1)->a = tmp;
        (*op1)->a[new_len - 1] = 0;
        (*op1)->word_len = new_len;
    }

    if ((*op2)->word_len % 2 == 1) {
        int new_len = (*op2)->word_len + 1;
        word* tmp = (word*)realloc((*op2)->a, new_len * sizeof(word));
        if (tmp == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return MemAllocErr;
        }
        (*op2)->a = tmp;
        (*op2)->a[new_len - 1] = 0;
        (*op2)->word_len = new_len;
    }

    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;

    bigint *tmp = NULL;
    bi_new(&tmp, op1_wlen + op2_wlen);

    bigint* T0 = NULL, * T1 = NULL, * T = NULL;
    bigint* tmp0 = NULL, * tmp1 = NULL;
    bi_new(&tmp0, 2);
    bi_new(&tmp1, 2);
    bi_new(&T, op1_wlen + 2);

    /* Perform multiplication according to the improved textbook algorithm */
    for (int Bi = 0; Bi < op2_wlen; Bi++) {
        bi_new(&T0, op1_wlen);
        bi_new(&T1, op1_wlen);
        for (int Aj= 0; Aj < op1_wlen; Aj += 2) {
            
            bi_mul_AB(tmp0->a, &((*op1)->a[Aj]), &((*op2)->a[Bi]));
            bi_mul_AB(tmp1->a, &((*op1)->a[Aj + 1]), &((*op2)->a[Bi]));
            T0->a[Aj] += tmp0->a[0];
            T0->a[Aj + 1] += tmp0->a[1];

            T1->a[Aj] += tmp1->a[0];
            T1->a[Aj + 1] += tmp1->a[1];
        }
  
        /* Combine T0 and T1, applying necessary bit shifts */
        bi_word_shift_left(&T1, 1);
        bi_addc(&T, &T1, &T0);
        bi_word_shift_left(&T, Bi);
        if (T->word_len < tmp->word_len){
            bi_addc(&tmp, &tmp, &T);
        }
        else{
            bi_addc(&tmp, &T ,&tmp);
        }
    }

    bi_delete(&T0);
    bi_delete(&T1); 
    bi_delete(&tmp0);
    bi_delete(&tmp1);
    bi_delete(&T);

    bi_assign(res, tmp);
    bi_delete(&tmp);
    return bi_refine(*res);
}

msg bi_Karatsuba_mulc(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    int op1_wlen = (*op1)->word_len;
    int op2_wlen = (*op2)->word_len;

    int max_wlen = (op1_wlen > op2_wlen) ? op1_wlen : op2_wlen;
    int min_wlen = (op1_wlen > op2_wlen) ? op2_wlen : op1_wlen;

    /* If either operand is zero, return zero */
    if (bi_zero_check(op1) || bi_zero_check(op2)) {
        bi_new(res, 1);
        (*res)->a[0] = 0;
        return CLEAR;
    }

    /* Base case: Use the improved textbook multiplication if the size is below the threshold */
    if (min_wlen <= FLAG) {
        return bi_improved_textbook_mulc(res, op1, op2);
    }

    int lw_len = (max_wlen + 1) >> 1;

    bigint* A1 = NULL, * A0 = NULL;
    bigint* B1 = NULL, * B0 = NULL;
    bigint* T1 = NULL, * T0 = NULL;
    bigint* T_tmp = NULL;
    bigint* S1 = NULL, * S0 = NULL;
    bigint* S = NULL;
    bigint *tmp = NULL;

    /* Split operands into high and low parts */
    bi_new(&A1, lw_len); bi_new(&A0, lw_len);
    bi_new(&B1, lw_len); bi_new(&B0, lw_len);
    array_copy_high(A1->a, (*op1)->a, lw_len, op1_wlen);
    array_copy_low(A0->a, (*op1)->a, lw_len, op1_wlen);
    array_copy_high(B1->a, (*op2)->a, lw_len, op2_wlen);
    array_copy_low(B0->a, (*op2)->a, lw_len, op2_wlen);

    /* Recursively compute A1*B1 and A0*B0 */
    bi_Karatsuba_mulc(&T1, &A1, &B1);
    bi_Karatsuba_mulc(&T0, &A0, &B0);

    /* Compute C = (T1 << 2*lw) + T0 */
    bi_assign(&T_tmp, T1);
    bi_word_shift_left(&T_tmp, 2 * lw_len);
    bi_add(&tmp, &T_tmp, &T0);

    /* Compute S1 = A0 - A1 and S0 = B1 - B0 */
    bi_sub(&S1, &A0, &A1);
    bi_sub(&S0, &B1, &B0);

    /* Compute S = (-1)^(sign(S1) ^ sign(S0)) * |S1| * |S0| */
    int sign_S1 = S1->sign;
    int sign_S0 = S0->sign;
    S1->sign = NON_NEGATIVE;
    S0->sign = NON_NEGATIVE;
    bi_Karatsuba_mulc(&S, &S1, &S0);

    S->sign = (sign_S1 ^ sign_S0) ? NEGATIVE : NON_NEGATIVE;

    /* Update S: S = S + T1 + T0 */
    bi_add(&S, &S, &T1);
    bi_add(&S, &S, &T0);

    /* Shift S left by lw bits */
    bi_word_shift_left(&S, lw_len);

    /* Final result: C = C + S */
    bi_add(res, &tmp, &S);

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

    return bi_refine(*res);
}

msg bi_mul(OUT bigint** res, IN bigint** op1, IN bigint** op2) {
    /* Check if either operand is NULL */
    if (*op1 == NULL || *op2 == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    int sign_op1 = (*op1)->sign;
    int sign_op2 = (*op2)->sign;

    /* Convert both operands to their absolute values */
    (*op1)->sign = NON_NEGATIVE;
    (*op2)->sign = NON_NEGATIVE;

    /* Perform multiplication on absolute values using Karatsuba algorithm */
    bi_Karatsuba_mulc(res, op1, op2);

    /* Set the sign of the result based on the signs of the operands */
    (*res)->sign = (sign_op1 == sign_op2) ? NON_NEGATIVE : NEGATIVE;

    /* Restore the original signs of the operands */
    (*op1)->sign = sign_op1;
    (*op2)->sign = sign_op2;

    return CLEAR;
}

msg bi_sqr_A(OUT word res[2], IN word* A) {
    /* Split a single word into two parts (upper and lower halves) */
    word A1 = *A >> (WORD_BITLEN >> 1);             
    word A0 = *A & WORD_MASK;                       

    /* Compute partial products */
    word C1 = A1 * A1;                              
    word C0 = A0 * A0;

    word T = A0 * A1;

    /* Compute the low part of the result (C0) */
    word carry_low = 0;                                   

    for (int idx = 0; idx < 2; idx++){
        C0 += T << (WORD_BITLEN >> 1);                                  
        if (C0 < T << (WORD_BITLEN >> 1)) {                             
            carry_low += (word)1;
        }
    }
    
    /* Compute the high part of the result (C1) */
    C1 += (T >> (WORD_BITLEN >> 1));
    C1 += (T >> (WORD_BITLEN >> 1));
    C1 += (word)carry_low;

    /* Store the result in the output array */
    res[1] = C1;                                    // High part of result
    res[0] = C0;                                    // Low part of result

    return CLEAR;
}

msg bi_textbook_sqrc(OUT bigint** res, IN bigint** op1) {
    int op1_wlen = (*op1)->word_len;

    bigint* tmp = NULL;
    bi_new(&tmp, (2 * op1_wlen));

    /* Temporary bigint to store intermediate Aj * Bi results */
    bigint* T1 = NULL;
    bigint* T2 = NULL;

    bigint* C1 = NULL;
    bigint* C2 = NULL;

    bi_new(&C1, 1);
    bi_new(&C2, 1);

    /* Perform the multiplication operation for all words in both operands */
    for (int Aj = 0; Aj < op1_wlen; Aj++) {
        bi_new(&T1, 2);
            
        /* Multiply the words at indices Aj and Bi */
        bi_sqr_A(T1->a, &((*op1)->a[Aj]));

        /* Shift the result to the correct position based on word indices Aj and Bi */
        bi_word_shift_left(&T1, (2 * Aj));

        bi_add(&C1, &T1, &C1);

        for (int Bi = Aj + 1; Bi < op1_wlen; Bi++) {
            bi_new(&T2, 2);
            
            bi_mul_AB(T2->a, &((*op1)->a[Bi]),&((*op1)->a[Aj]));
            
            bi_word_shift_left(&T2, (Aj + Bi));
        
            bi_add(&C2, &C2, &T2);
        }
    }

    bi_doubling(C2);
    bi_add(&tmp, &C1, &C2);

    bi_delete(&T1);
    bi_delete(&T2);
    bi_delete(&C1);
    bi_delete(&C2);

    bi_assign(res, tmp);
    bi_delete(&tmp);

    return bi_refine(*res);
}

msg bi_Karatsuba_sqrc(OUT bigint** res, IN bigint** op1) {
    int op1_wlen = (*op1)->word_len;
    /* If operand is zero, return zero */
    if (bi_zero_check(op1)) {
        bi_new(res, 1);
        (*res)->a[0] = 0;
        return CLEAR;
    }

    /* Base case: Use the improved textbook multiplication if the size is below the threshold */
    if (op1_wlen <= FLAG) {
        return bi_textbook_sqrc(res, op1);
    }

    int lw_len = (op1_wlen + 1) >> 1;

    bigint* A1 = NULL, * A0 = NULL;
    bigint* T1 = NULL, * T0 = NULL;
    bigint* T_tmp = NULL;
    bigint* S = NULL;
    bigint *tmp = NULL;

    /* Split operand into high and low parts */
    bi_new(&A1, lw_len); bi_new(&A0, lw_len);
    array_copy_high(A1->a, (*op1)->a, lw_len, op1_wlen);
    array_copy_low(A0->a, (*op1)->a, lw_len, op1_wlen);

    /* Recursively compute A1*A1 and A0*A0 */
    bi_Karatsuba_sqrc(&T1, &A1);
    bi_Karatsuba_sqrc(&T0, &A0);

    /* Compute C = (T1 << 2*lw) + T0 */
    bi_assign(&T_tmp, T1);
    bi_word_shift_left(&T_tmp, 2 * lw_len);
    bi_add(&tmp, &T_tmp, &T0);

    bi_Karatsuba_mulc(&S, &A1, &A0);

    /* Shift S left by lw+1 bits */
    bi_word_shift_left(&S, lw_len);
    bi_doubling(S);

    /* Final result: C = C + S */
    bi_add(res, &tmp, &S);

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&S);
    bi_delete(&T1);
    bi_delete(&T_tmp);
    bi_delete(&T0);
    bi_delete(&tmp);

    return bi_refine(*res);
}

msg bi_naive_div(OUT bigint** quot, OUT bigint** rem, IN bigint** divd, IN bigint** divs) {
    /* Check if dividend or divisor is NULL */
    if (*divd == NULL || *divs == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Check for zero divisor */
    if (bi_zero_check(divs)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    bigint* one = NULL; 
    bi_set_one(&one);

    bi_assign(rem, *divd);
    bi_new(quot, 1);

    /* Naive Division: Repeated subtraction */
    while (bi_compareABS(rem, divs) != (msg)COMPARE_LESS) {
        bi_add(quot, quot, &one);
        bi_sub(rem, rem, divs);
    }

    bi_refine(*quot);
    bi_refine(*rem);
    bi_delete(&one);
    return CLEAR;
}

msg bi_long_div(OUT bigint** quot, OUT bigint** rem, IN bigint** divd, IN bigint** divs) {
    /* Check if dividend or divisor is NULL */
    if (*divd == NULL || *divs == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Check for zero divisor */
    if (bi_zero_check(divs)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    int divd_wlen = (*divd)->word_len;

    bi_new(quot, divd_wlen);
    bi_new(rem, divd_wlen);

    /* Perform bit-wise division */
    for (int bit_idx = (divd_wlen * WORD_BITLEN) - 1; bit_idx >= 0; bit_idx--) {
        /* R = 2R (left shift remainder) */
        bi_doubling(*rem);

        /* Add the current bit of the dividend to the remainder */
        if (((*divd)->a[bit_idx / WORD_BITLEN] & ((word)1 << (bit_idx % WORD_BITLEN))) != 0) {
            (*rem)->a[0] ^= 1;
        }

        /* Check if remainder is greater than or equal to the divisor */
        if (bi_compare(rem, divs) != (msg)COMPARE_LESS) {
            /* Update quotient: Q = Q + (1 << bit_idx) */
            (*quot)->a[bit_idx / WORD_BITLEN] ^= ((word)1 << (bit_idx % WORD_BITLEN));

            /* Update remainder: R = R - divisor */
            bi_subc(rem, rem, divs);
        }
    }

    bi_refine(*quot);
    bi_refine(*rem);

    return CLEAR;
}

msg bi_mod(UPDATE bigint** rem, IN bigint** divs) {
    bigint* quot = NULL, * rem_tmp = NULL;

    /* Perform long division to calculate remainder */
    bi_long_div(&quot, &rem_tmp, rem, divs);
    bi_assign(rem, rem_tmp);

    bi_delete(&quot);
    bi_delete(&rem_tmp);
    return CLEAR;
}

msg bi_div(OUT bigint** quot, OUT bigint** rem, IN bigint** divd, IN bigint** divs) {
    /* Check if dividend or divisor is NULL */
    if (*divd == NULL || *divs == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Check for zero divisor */
    if (bi_zero_check(divs)) {
        fprintf(stderr, ZeroDivisorErrMsg);
        return ZeroDivisorErr;
    }

    /* Perform division based on absolute values */
    int sign_divd = (*divd)->sign;
    int sign_divs = (*divs)->sign;

    (*divd)->sign = NON_NEGATIVE;
    (*divs)->sign = NON_NEGATIVE;
    bi_long_div(quot, rem, divd, divs);

    /* If dividend is negative and remainder is not zero */
    if (sign_divd == NEGATIVE && !bi_zero_check(rem)) {
        bi_plus_one(quot);      // Update quotient: quot = quot + 1
        bi_sub(rem, divs, rem); // Update remainder: rem = divs - rem
    }

    /* Set the sign of the quotient based on the signs of dividend and divisor */
    (*quot)->sign = (sign_divd == sign_divs) ? NON_NEGATIVE : NEGATIVE;
    
    /* Remainder is always non-negative */
    (*rem)->sign = NON_NEGATIVE;

    (*divd)->sign = sign_divd;
    (*divs)->sign = sign_divs;

    return CLEAR;
}

msg bi_l2r_mod_exp(OUT bigint** res, IN bigint** base, IN bigint** exp, IN bigint** mod) {
    /* Check for NULL inputs */
    if ((*base == NULL) || (*mod == NULL)) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* Initialize result: t = 1 */
    bi_set_one(res);

    int total_exp_bits = (*exp)->word_len * WORD_BITLEN;

    /* Left-to-Right Modular Exponentiation */
    for (int bit_idx = total_exp_bits - 1; bit_idx >= 0; bit_idx--) {
        /* t = t^2 */
        bi_Karatsuba_sqrc(res, res);

        /* t = t mod M */
        bi_mod(res, mod);

        /* Check the current bit: ni = (exp >> i) & 1 */
        if (((*exp)->a[bit_idx / WORD_BITLEN] & ((word)1 << (bit_idx % WORD_BITLEN))) != 0) {
            /* t = t * X */
            bi_Karatsuba_mulc(res, res, base);

            /* t = t mod M */
            bi_mod(res, mod);
        }
    }

    return CLEAR;
}

msg bi_r2l_mod_exp(OUT bigint** res, IN bigint** base, IN bigint** exp, IN bigint** mod) {
    /* Check for NULL inputs */
    if ((*base == NULL) || (*mod == NULL)) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    bigint* t1 = NULL;

    /* Initialize t0 = 1 and t1 = base */
    bi_set_one(res);
    bi_assign(&t1, *base);

    int total_exp_bits = (*exp)->word_len * WORD_BITLEN;

    /* Right-to-Left Modular Exponentiation */
    for (int bit_idx = 0; bit_idx < total_exp_bits; bit_idx++) {
        /* Check the current bit: ni = (exp >> i) & 1 */
        if (((*exp)->a[bit_idx / WORD_BITLEN] & ((word)1 << (bit_idx % WORD_BITLEN))) != 0) {
            /* t0 = t0 * t1^ni */
            bi_Karatsuba_mulc(res, res, &t1);

            /* t0 = t0 mod M */
            bi_mod(res, mod);
        }
        /* t1 = t1^2 mod M */
        bi_Karatsuba_sqrc(&t1, &t1);

        bi_mod(&t1, mod);
    }
    return CLEAR;
}

msg bi_barrett_red(OUT bigint** rem, IN bigint** divd, IN bigint** mod, IN bigint** precomp) {
    int mod_wlen = (*mod)->word_len;
    int divd_wlen = (*divd)->word_len;

    /* Check if dividend word length is twice the modulus word length */
    if ((divd_wlen >> 1) != mod_wlen) {
        fprintf(stderr, WordLenNotDoubleErrMsg);
        return WordLenNotDoubleErr;
    }

    /* Check if dividend sign is non-negative */
    if ((*divd)->sign != NON_NEGATIVE) {
        fprintf(stderr, SignNEGErrMsg);
        return SignNEGErr;
    }
    bigint* quot_hat = NULL;
    bigint* divd_tmp = NULL;
    bigint* rem_tmp = NULL;

    /* Calculate quot_hat = ((divd >> w(n - 1)) * precomp) >> w(n + 1) */
    bi_assign(&divd_tmp, *divd);
    bi_word_shift_right(&divd_tmp, mod_wlen - 1);
    bi_Karatsuba_mulc(&quot_hat, &divd_tmp, precomp);
    bi_word_shift_right(&quot_hat, mod_wlen + 1);

    /* Calculate rem = divd - mod * quot_hat */
    bi_Karatsuba_mulc(&rem_tmp, mod, &quot_hat);
    bi_sub(rem, divd, &rem_tmp);

    bi_delete(&rem_tmp);

    bi_refine(*rem);
    bi_refine(*mod);

    /* If rem >= mod, subtract mod until rem < mod */
    while (bi_compare(rem, mod) != (msg)COMPARE_LESS) {
        bi_sub(rem, rem, mod);
    }
    bi_delete(&quot_hat);
    bi_delete(&divd_tmp);

    return CLEAR;
}
