#include <string.h>
#include <stdlib.h>
#include "array_func.h"
#include "msg.h"

msg array_init(UPDATE word* arr, IN int word_len) {
    memset(arr, 0, WORD_ARR_BYTELEN(word_len));    // Initialize the array `arr` to zero (byte-level)
    word result = 0;                               // Check initialization
    for (int idx = 0; idx < word_len; idx++) {
        result |= arr[idx];                        // Perform OR operation on WORDs to verify initialization
    }

    return (result == 0) ? CLEAR : NOTInitErr;     // Return success if fully initialized to zero
}


msg array_copy(OUT word* dst, IN word* src, IN int word_len) {
    /* Copy contents of `src` array to `dst` array */
    for (int idx = 0; idx < word_len; idx++) {            
        dst[idx] = src[idx];
    }

    return CLEAR;
}

msg array_copy_high(OUT word* dst, IN word* src, IN int dst_word_len, IN int src_word_len) {
    /* Copy higher-order values from `src` to `dst` */
    for (int idx = 0; idx < dst_word_len; idx++) {
        if (idx + dst_word_len < src_word_len) {
            dst[idx] = src[idx + dst_word_len];
        }
        else {
            dst[idx] = 0;  // Fill remaining elements with 0
        }
    }
    return CLEAR;
}

msg array_copy_low(OUT word* dst, IN word* src, IN int dst_word_len, IN int src_word_len) {
    /* Copy lower-order values from `src` to `dst` */
    for (int idx = 0; idx < dst_word_len; idx++) {
        if (idx < src_word_len) {
            dst[idx] = src[idx];
        }
        else {
            dst[idx] = 0;  // Fill remaining elements with 0
        }
    }
    return CLEAR;
}

msg array_rand(OUT word* dst, IN int word_len) {
    byte* p = (byte*)dst;                  // Cast `dst` pointer to byte type
    int cnt = WORD_ARR_BYTELEN(word_len);  // Calculate the byte length of the array

    /* Fill the array with random byte values */
    while (cnt > 0) {
        *p = byte_rand();
        p++;
        cnt--;
    }
    return CLEAR;
}
