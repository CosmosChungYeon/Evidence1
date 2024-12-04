#ifndef DH_H
#define DH_H

#include "basic_func.h"
#include "calc_operations.h"
#include "config.h"
#include "bi_def.h"
#include <string.h>

msg bi_dh_private_key_gen(OUT bigint** key, IN bigint** p);

msg bi_dh_public_key_gen(OUT bigint** gA, IN bigint** g, IN bigint** key, IN bigint** p);

msg bi_dh_session_key_gen(OUT bigint** gAB, IN bigint** gB, IN bigint** key, IN bigint** p);

#endif  // DH_H