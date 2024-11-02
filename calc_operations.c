
#include "calc_operations.h"
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "const.h"

msg bi_add_ABc(OUT word* C, IN word A, IN word B, IN int c) {
    int c_out = 0;  // 반환용 carry(c')
    *C = A + B;
    c_out = (*C < A) ? CARRY1 : CARRY0;     // if A + B < A, then c' = 1

    *C += c;
    c_out = (*C < c) ? c_out + 1 : c_out;   // if A + B + c < c, then c' += 1 
    
    return c_out;   // c' 반환
}

msg bi_addc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    /* [n >= m] */
    int n = (*A)->word_len;
    int m = (*B)->word_len;
    
    /* A 배열 길이 만큼 늘리고 는만큼 0으로 채우기 */
    (*B)->word_len = n;
    memset(((*B)->a) + m, 0, WORD_ARR_BYTELEN(n - m));

    /* carry 연산하면서 A + B 수행 */
    int c = 0;
    for (int j = 0; j < n; j++) {
        c = bi_add_ABc(&((*C)->a[j]), (*A)->a[j], (*B)->a[j], c);
    }

    /* B 배열 원래대로 */
    bi_refine(*B);
    return bi_refine(*C);
    
}

msg bi_add(OUT bigint** C, IN bigint** A, IN bigint** B) {
    
}

msg bi_sub_AbB(OUT word* C, IN word A, IN int b, IN word B) {
    int b_out = 0;  // 반환용 borrow(b')
    *C = A - b;
    b_out = (A < b) ? BORROW1 : BORROW0;    // if A < b, then b' = 1

    b_out = (*C < B) ? b_out + 1 : b_out;   // if C < B, then b' += 1 
    *C -= B;

    return b_out;   // b' 반환
}

msg bi_subc(OUT bigint** C, IN bigint** A, IN bigint** B) {
    /* [n >= m] */
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* A 배열 길이 만큼 늘리고 는만큼 0으로 채우기 */
    (*B)->word_len = n;
    memset(((*B)->a) + m, 0, WORD_ARR_BYTELEN(n - m));

    /* borrow 연산하면서 A - B 수행 */
    int b = 0;
    for (int j = 0; j < n; j++) {
        b = bi_sub_AbB(&((*C)->a[j]), (*A)->a[j], b, (*B)->a[j]);
    }
    
    /* B 배열 원래대로 */
    bi_refine(*B);
    return bi_refine(*C);
}

msg bi_sub(OUT bigint** C, IN bigint** A, IN bigint** B) {

}
