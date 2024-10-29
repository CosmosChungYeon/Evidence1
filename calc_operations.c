
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"


msg bi_add_ABc(OUT word* C, IN word A, IN word B, IN int c) {

}

msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B) {

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
