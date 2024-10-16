#include <string.h>
#include <stdlib.h>
#include "array_func.h"
#include "msg.h"

/*
 * 함수명: array_init
 * 함수인자: UPDATE word* a, int IN word_len
 * 함수역할: array a 초기화
 */
msg array_init(UPDATE word* a, int IN word_len) {
    memset(a, 0, WORD_ARR_BYTELEN(word_len));   // array a의 길이만큼 0으로 초기화 (바이트단위)
    word result = 0;                            // 초기화 확인
    for (int i = 0; i < word_len; i++){
        result |= a[i];                         // WORD 단위로 OR 연산을 통해 확인
    }
    if (result == 0){                           // 0이면 CLEAR 반환
        return CLEAR;
    }
    else {
        fprintf(stderr, NOTInitErrMsg);         // 아니면 ERROR 반환
        return NOTInitErr;
    }
}

/*
 * 함수명: array_copy
 * 함수인자: OUT word* dst, IN word* src, IN int word_len
 * 함수역할: dst array에 src array 복사
 */
msg array_copy(OUT word* dst, IN word* src, IN int word_len) {
    if (dst != NULL){                           // NULL이 아니면 메모리 해제
		free(dst);
	}

	dst = (word*)calloc(word_len, sizeof(word));    // src의 word_len만큼 메모리 할당
	if (dst == NULL){
		fprintf(stderr, MemAllocErrMsg);
		return MemAllocErr;
	}

    memcpy(dst, src, WORD_ARR_BYTELEN(word_len));      // src배열을 dst배열에 복사 (바이트 단위)
    return CLEAR;
}

/*
 * 함수명: array_rand
 * 함수인자: OUT word* dst, IN int word_len
 * 함수역할: dst array에 word_len만큼 임의의 값으로 할당
 */
msg array_rand(OUT word* dst, IN int word_len) {
    byte* p = (byte*)dst;                           // dst 포인터주소를 byte type으로 변경
    int cnt = WORD_ARR_BYTELEN(word_len);           // 배열의 바이트 길이
    while(cnt > 0) {                                // 0이 될 때까지 바이트 단위로 임의의 값 입력
        *p = byte_rand();
        p++;
        cnt--;
    }
    return CLEAR;
}

