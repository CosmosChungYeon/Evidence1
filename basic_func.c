#include <stdio.h>      // printf
#include <stdlib.h>     // calloc, realloc
#include <stdint.h>     // uint32_t
#include <string.h>     // strlen
#include <time.h>       // bi_gen_random

#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "msg.h"
#include "const.h"


/* array로부터 bigint Set */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a) {

    /* 부호값 체크 */
    if (sign != 0 && sign != 1){
        puts(SignValErrMsg);    // fprintf
        return SignValErr;
    }

    /* 워드 길이 체크 */
    if (word_len <= 0 ){
        puts(WordLenErrMsg);
        return WordLenErr;
    }

    /* a 배열 NULL인지 체크 */
    if (a == NULL){
        puts(SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* bigint 초기화 */
    bi_new(dst, word_len);

    (*dst)->sign = sign;
    memcpy((*dst)->a, a, word_len * sizeof(word));

    return bi_refine(*dst);
}

/* 2진수, 16진수 string으로부터 bigint Set */
msg bi_set_from_string(bigint** dst, char* int_str, int base) {

    /* 문자열 NULL 체크 */
    if (int_str == NULL) {
        puts(StrNULLErrMsg);
        return StrNULLErr;
    }

    /* 부호값 처리 */
    int sign = 0;
    if (int_str[0] == '-'){
        sign = 1;
        int_str++;
    }

    /* 진수에 따른 문자열 유효성 검사 */
    int i = 0;
    while (int_str[i] != '\0') {
        if (base == 2) {
            if (int_str[i] != '0' && int_str[i] != '1') {
                puts(BinInputErrMsg);
                return BinInputErr;
            }
        } 
        else if (base == 16) {
            if (!((int_str[i] >= '0' && int_str[i] <= '9') || 
                (int_str[i] >= 'a' && int_str[i] <= 'f') || 
                (int_str[i] >= 'A' && int_str[i] <= 'F'))) {
                puts(HexInputErrMsg);
                return HexInputErr;
            }
        }
        else if (base == 10) {
            if (!(int_str[i] >= '0' && int_str[i] <= '9')) {
                puts(DecInputErrMsg);
                return DecInputErr;
            }
        }
        else {
            puts(UnSupportBaseErrMsg);
            return UnSupportBaseErr;
        }
        i++;
    }

    /* 문자열 -> 정수 */
    int str_len = strlen(int_str);
    int word_len;

    // base에 따라 word_len 계산
    if (base == 2) {
        word_len = (str_len / (sizeof(word) << 3)) + (str_len % (sizeof(word) << 3) != 0);
    }
    else if (base == 16) {
        word_len = (str_len / (sizeof(word) << 1)) + (str_len % (sizeof(word) << 1) != 0);
    }
    else if (base == 10) {

    }

    /* bigint 초기화 */
    bi_new(dst, word_len);

    (*dst)->sign = sign;

    /* 2진수 처리 */
    if (base == 2) {
        int bit_pos = 0;
        for (int i = str_len - 1; i >= 0; i--) {
            if (int_str[i] == '1') {
                (*dst)->a[bit_pos / 32] |= (1 << (bit_pos % 32));
            }
            bit_pos++;
        }
    }
    /* 16진수 처리 */
    else if (base == 16) {
        int bit_pos = 0;
        for (int i = str_len - 1; i >= 0; i--) {
            char c = int_str[i];
            int value = (c >= '0' && c <= '9') ? (c - '0') : 
                        (c >= 'a' && c <= 'f') ? (c - 'a' + 10) : (c - 'A' + 10);
            (*dst)->a[bit_pos / 32] |= value << (bit_pos % 32);
            bit_pos += 4;  // 4비트씩 이동
        }
    }
    else if (base == 10) {

    }

    return bi_refine(*dst);
}

/* 임의의 값으로 bigint 초기화 */
/* 마지막 원소가 nonzero여야 함 */
msg bi_get_random(bigint** dst, int word_len) {
    /* NULL 체크 */
    if (*dst == NULL) {
        puts(DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* 워드 길이 체크 */
    if (word_len <= 0) {
        puts(WordLenErrMsg);
        return WordLenErr;
    }

    /* 워드 메모리 할당 */
    (*dst)->a = (word*)calloc(word_len, sizeof(word));
    if ((*dst)->a == NULL) {
        puts(MemAllocErrMsg);
        return MemAllocErr;
    }
    (*dst)->word_len = word_len;

    /* 워드 배열에 임의의 값 입력 */
    for (int i = 0; i < word_len; i++) {
        (*dst)->a[i] = ((word)rand() << 16) | (word)rand();  // 32비트 채우기
    }

    /* 마지막 원소가 nonzero여야 함 */
    while ((*dst)->a[word_len - 1] == 0) {
        (*dst)->a[word_len - 1] = ((word)rand() << 16) | (word)rand();  // DRBG 붙이기 용이하게
    }

    return CLEAR;
}

/* 진수 출력 */
msg bi_print(const bigint* dst, int base) {
    /* bigint NULL 체크 */
    if (dst == NULL || dst->word_len <= 0 || dst->a == NULL) {
        puts(DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* 진수 체크 */
    if (base != 2 && base != 16) {
        puts(UnSupportBaseErrMsg);
        return UnSupportBaseErr;
    }

    /* Bigint 출력 */
    printf("BigInt (base %d): ", base);
    if (dst->sign == 1) {
        printf("-");
    }

    if (base == 16) {
        printf("0x");
        for (int i = dst->word_len - 1; i >= 0; i--) {
            printf("%08X", dst->a[i]);  // 각 word를 16진수로 출력
        }
    }
    // 2진수 출력
    else if (base == 2) {
        printf("0b");
        int leading_zero = 1;  // 처음의 0들을 건너뛰기 위한 플래그
        for (int i = dst->word_len - 1; i >= 0; i--) {
            for (int j = (sizeof(word) << 3) - 1; j >= 0; j--) {
                int bit = (dst->a[i] >> j) & 1;  // 해당 비트를 추출
                if (bit == 1) {
                    leading_zero = 0;  // 처음으로 1을 만나면 leading_zero 해제
                }
                if (!leading_zero) {
                    printf("%d", bit);
                }
            }
        }
        // 모든 비트가 0일 경우 0 출력
        if (leading_zero) {
            printf("0");
        }
    }
    printf("\n");

    return 1;
}

/* 초기화 */
msg bi_new(bigint** dst, int word_len) {
    /* 메모리 해제 */
    if (*dst != NULL){
        bi_delete(dst);
    }

    /* 워드 길이 체크 */
    if (word_len <= 0 ){
        puts(WordLenErrMsg);
        return WordLenErr;
    }

    /* bigint 메모리 할당 */
    *dst = (bigint*)calloc(1, sizeof(bigint));
    if (*dst == NULL) {
        puts(MemAllocErrMsg);
        return MemAllocErr;
    }

    /* 초기화 */
    (*dst)->sign = NON_NEGATIVE;
    (*dst)->word_len = word_len;
    (*dst)->a = (word*)calloc(word_len, sizeof(word));
    if ((*dst)->a == NULL) {
        puts(MemAllocErrMsg);
        free(*dst);
        return MemAllocErr;
    }
    return CLEAR;
}

/* 메모리 해제 */
msg bi_delete(bigint** dst) {
    /* 메모리 해제 확인 */
	if (*dst == NULL) {
		return CLEAR;
	}

    /* 비밀값 제거 */
	(*dst)->sign = NON_NEGATIVE;
	(*dst)->word_len = 0;

	if ((*dst)->a != NULL){
		free((*dst)->a);
		(*dst)->a = NULL;
	}

    /* 메모리 해제 */
	free(*dst);
	*dst = NULL;

	return CLEAR;
}

/* 메모리 재할당 */
msg bi_refine(bigint* dst) {
    /* bigint NULL 체크 */
	if (dst == NULL) {
		puts(DSTpNULLErrMsg);
		return DSTpNULLErr;
	}

    /* 새로운 워드 길이 계산 */
	int new_word_len = dst->word_len;
	while (new_word_len > 1 && dst->a[new_word_len - 1] == 0){
		new_word_len--;
	}

    /* 메모리 재할당 */
	if (new_word_len != dst->word_len){
		word* new_a = (word*)realloc(dst->a, new_word_len * sizeof(word));
		if (new_a == NULL){
			puts(MemAllocErrMsg);
			return(MemAllocErr);
		}
		dst->a = new_a;
		dst->word_len = new_word_len;
	}

	return CLEAR;
} 

/* 대입 */
msg bi_assign(bigint** dst, bigint* src) {
    /* Source 에러 체크 */
    if (src == NULL || src->a == NULL || src->word_len <= 0) { 
        puts(SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* 일치 여부 체크 */
	if (*dst == src){
		return CLEAR;
	}

    /* bigint NULL이면 초기화 */
	if (*dst == NULL) {
        bi_new(dst, src->word_len);
    }

    /* 대입 */
	(*dst)->sign = src->sign;

	if ((*dst)->a != NULL){
		free((*dst)->a);
	}

	(*dst)->a = (word*)calloc(src->word_len, sizeof(word));
	if ((*dst)->a == NULL){
		puts(MemAllocErrMsg);
		return MemAllocErr;
	}

    memcpy((*dst)->a, src->a, src->word_len * sizeof(word));

	return CLEAR;
}