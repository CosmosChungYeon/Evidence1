
#include "DH.h"
#include "config.h"
#include "const.h"

msg bi_dh_private_key_gen(OUT bigint** key, IN bigint** p) {
    bi_get_random(key, (*p)->word_len);
    (*key)->sign = NON_NEGATIVE;
    while (bi_compareABS(key, p) == COMPARE_LESS) {
        bi_get_random(key, (*p)->word_len);
    }
    return CLEAR;
}

msg bi_dh_public_key_gen(OUT bigint** gA, IN bigint** g, IN bigint** key, IN bigint** p) {
    bi_l2r_mod_exp(gA, g, key, p);
}

msg bi_dh_session_key_gen(OUT bigint** gAB, IN bigint** gB, IN bigint** key, IN bigint** p) {
    bi_l2r_mod_exp(gAB, gB, key, p);
}