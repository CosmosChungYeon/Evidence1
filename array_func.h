#ifndef ARRAY_FUNC_H
#define ARRAY_FUNC_H

#include "bi_def.h"
#include "rand.h"

msg array_init(word* a, int word_len);

msg array_copy(word* dst, word* src, int word_len);

msg array_rand(word* dst, int word_len);

#endif  // ARRAY_FUNC_H