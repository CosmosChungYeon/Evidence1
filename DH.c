
#include "DH.h"
#include "const.h"

msg bi_dh_find_generator_g(OUT bigint** g, IN bigint** p, IN bigint** q) {
    bigint* h = NULL;          // Temporary variable for candidate h
    bigint* one = NULL;        // Constant 1
    bigint* p_minus_1 = NULL;  // p - 1
    bigint* quot = NULL;       // (p - 1) / q
    bigint* rem = NULL;        // Temporary for remainder

    /* Initialize constants and compute p - 1 */
    bi_set_one(&one);                           // Set one = 1
    bi_sub(&p_minus_1, p, &one);                // p_minus_1 = p - 1
    bi_long_div(&quot, &rem, &p_minus_1, q);    // quot = (p - 1) / q

    do {
        /* Generate random h in range [2, p-2] */
        do {
            bi_get_random(&h, (*p)->word_len);
        } while (bi_compareABS(&h, &p_minus_1) != (msg)COMPARE_LESS || bi_compare(&h, &one) != (msg)COMPARE_GREATER);
        h->sign = NON_NEGATIVE;

        /* Compute g = h^((p-1)/q) mod p */
        bi_l2r_mod_exp(g, &h, &quot, p);

    } while (bi_compare(g, &one) == (msg)COMPARE_EQUAL);  // Repeat until g ≠ 1 mod p

    bi_delete(&h);
    bi_delete(&one);
    bi_delete(&p_minus_1);
    bi_delete(&quot);
    bi_delete(&rem);

    return CLEAR;
}

msg bi_dh_private_key_gen(OUT bigint** key, IN bigint** q) {
    bigint* one = NULL;        // Constant 1
    bi_set_one(&one);          // Set one = 1

    /* Generate a random private key within the range of [2, q-1]. */
    bi_get_random(key, (*q)->word_len);
    do {
        bi_get_random(key, (*q)->word_len);
        #if WORD_BITLEN == 64
        (*key)->a[(*key)->word_len - 1] >>= 32;
        #endif
    } while (bi_compareABS(key, q) != (msg)COMPARE_LESS || bi_compare(key, &one) != (msg)COMPARE_GREATER);
    (*key)->sign = NON_NEGATIVE;

    bi_delete(&one);
    return CLEAR;
}

msg bi_dh_public_key_gen(OUT bigint** gA, IN bigint** g, IN bigint** key, IN bigint** p) {
    /* Compute the public key: gA = g^key mod p. */
    bi_l2r_mod_exp(gA, g, key, p);
    return CLEAR;
}

msg bi_dh_session_key_gen(OUT bigint** gAB, IN bigint** gB, IN bigint** key, IN bigint** p) {
    /* Compute the shared secret session key: gAB = gB^key mod p. */
    bi_l2r_mod_exp(gAB, gB, key, p);
    return CLEAR;
}
