
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"


msg bi_add_ABc(OUT word* C, IN word A, IN word B, IN int c) {
    
    int c_out = 0;  // 반환용 carry(c')
    *C = A + B;
    c_out = (*C < A) ? 1 : 0;   // if A + B < A, then c' = 1

    *C += c;
    c_out = (*C < c) ? c_out + 1 : c_out;   // if A + B + c < c, then c' += 1 
    
    return c_out;   // c' 반환

}

msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B) {

    // [n >= m]
    int n = (*A)->word_len;
    int m = (*B)->word_len;
    (*B)->word_len = n; // 자릿수 맞추기
    memset(((*B)->a) + m, 0, WORD_ARR_BYTELEN(n - m));

    int c = 0;
    for (int j = 0; j < n; j++) {
        c = bi_add_ABc(&((*C)->a[j]), (*A)->a[j], (*B)->a[j], c);   // 연산
    }

    bi_refine(*B);
    return bi_refine(*C);
    
}

msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B) {
    
}

msg bi_sub_AbB(OUT word* C, IN word A, IN int b, IN word B) {
    int b_out = 0;
    *C = A - b;

    b_out = (A < b) ? 1 : 0;
    b_out = (*C < B) ? b_out + 1 : b_out;
    *C = *C - B;

    return b_out;
}

msg bi_subc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;
    (*B)->word_len = n;
    memset(((*B)->a) + m, 0, WORD_ARR_BYTELEN(n - m));

    int b = 0;
    for (int j = 0; j < n; j++) {
        b = bi_sub_AbB(&((*C)->a[j]), (*A)->a[j], b, (*B)->a[j]);
    }

    bi_refine(*B);
    return bi_refine(*C);
}

msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B) {

}
