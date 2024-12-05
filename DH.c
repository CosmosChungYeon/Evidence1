
#include "DH.h"
#include "config.h"
#include "const.h"

msg bi_dh_private_key_gen(OUT bigint** key, IN bigint** q) {
    bi_get_random(key, (*q)->word_len);
    while (bi_compareABS(key, q) == COMPARE_LESS) {
        bi_get_random(key, (*q)->word_len);
    }
    (*key)->sign = NON_NEGATIVE;
    return CLEAR;
}

msg bi_dh_public_key_gen(OUT bigint** gA, IN bigint** g, IN bigint** key, IN bigint** p) {
    bi_l2r_mod_exp(gA, g, key, p);
    return CLEAR;
}

msg bi_dh_session_key_gen(OUT bigint** gAB, IN bigint** gB, IN bigint** key, IN bigint** p) {
    bi_l2r_mod_exp(gAB, gB, key, p);
    return CLEAR;
}