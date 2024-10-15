#include <string.h>
#include <stdlib.h>
#include "array_func.h"
#include "msg.h"

msg array_init(word* a, int word_len) {
    memset(a, 0, sizeof(word) * word_len);
    word result = 0;
    for (int i = 0; i < word_len; i++){
        result |= a[i];
    }
    if (result == 0){
        return CLEAR;
    }
    else {
        fprintf(stderr, NOTInitErrMsg);
        return NOTInitErr;
    }
}

msg array_copy(word* dst, word* src, int word_len) {
    
    return CLEAR;
}

msg array_rand(word* dst, int word_len) {
    byte* p = (byte*)dst;
    int cnt = word_len * sizeof(word);
    while(cnt > 0) {
        *p = byte_rand();
        p++;
        cnt--;
    }
    return CLEAR;
}

