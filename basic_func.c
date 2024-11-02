#include <stdio.h>      // printf
#include <stdlib.h>     // calloc, realloc
#include <string.h>     // strlen
 
#include "basic_func.h"
#include "msg.h"
#include "const.h"
#include "array_func.h"

msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a) {

    /* 부호값 체크 */
    if (sign != NON_NEGATIVE && sign != NEGATIVE){
        fprintf(stderr, SignValErrMsg);
        return SignValErr;
    }

    /* 워드 길이 체크 */
    if (word_len <= NON_NEGATIVE ){
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* a 배열 NULL인지 체크 */
    if (a == NULL){
        fprintf(stderr, SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* bigint 초기화 */
    bi_new(dst, word_len);

    (*dst)->sign = sign;
    memcpy((*dst)->a, a, word_len * sizeof(word));

    return bi_refine(*dst);     // 메모리 재할당
}

msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base) {

    /* 문자열 NULL 체크 */
    if (int_str == NULL) {
        fprintf(stderr, StrNULLErrMsg);
        return StrNULLErr;
    }

    /* 부호값 처리 */
    int sign = NON_NEGATIVE;
    if (int_str[0] == '-'){
        sign = NEGATIVE;
        int_str++;
    }

    /* 진수에 따른 문자열 유효성 검사 */
    int i = 0;
    while (int_str[i] != '\0') {                                // 문자열 끝까지
        /* 2진수 */
        if (base == 2) {
            if (int_str[i] != '0' && int_str[i] != '1') {
                fprintf(stderr, BinInputErrMsg);
                return BinInputErr;
            }
        } 
        /* 16진수 */
        else if (base == 16) {
            if (!((int_str[i] >= '0' && int_str[i] <= '9') || 
                (int_str[i] >= 'a' && int_str[i] <= 'f') || 
                (int_str[i] >= 'A' && int_str[i] <= 'F'))) {
                fprintf(stderr, HexInputErrMsg);
                return HexInputErr;
            }
        }
        /* 10진수 */
        else if (base == 10) {
            if (!(int_str[i] >= '0' && int_str[i] <= '9')) {
                fprintf(stderr, DecInputErrMsg);
                return DecInputErr;
            }
        }
        else {
            fprintf(stderr, UnSupportBaseErrMsg);
            return UnSupportBaseErr;
        }
        i++;
    }

    /* 문자열 -> 정수 */
    int str_len = strlen(int_str);
    int word_len;

    /* base에 따라 word_len 계산 */
    if (base == 2) {
        word_len = (str_len / BINARY_STRING_LENGTH) + (str_len % BINARY_STRING_LENGTH != 0);    // Ceiling
    }
    else if (base == 16) {
        word_len = (str_len / HEX_STRING_LENGTH) + (str_len % HEX_STRING_LENGTH != 0);          // Ceiling
    }
    else if (base == 10) {
        // 미완
    }

    /* bigint 초기화 */
    bi_new(dst, word_len);

    (*dst)->sign = sign;

    /* 2진수 처리 */
    if (base == 2) {
        int bit_pos = 0;                                            // 문자 하나씩
        for (int i = str_len - 1; i >= 0; i--) {                    // 거꾸로 (문자열에서 LSB는 가장 우측이기 때문)
            if (int_str[i] == '1') {                                // 1이면
                (*dst)->a[bit_pos / WORD_BITLEN] |= (1 << (bit_pos % WORD_BITLEN));   // 해당 위치에 1 입력
            }
            bit_pos++;
        }
    }
    /* 16진수 처리 */
    else if (base == 16) {
        int bit_pos = 0;                                            // 문자 하나씩
        for (int i = str_len - 1; i >= 0; i--) {                    // 거꾸로
            char c = int_str[i];                                    // 문자를 정수로 바꾸기 (0~9, a~f, A~F)
            int value = (c >= '0' && c <= '9') ? (c - '0') :                        // "0"~"9"면 0~9로 변환, 아니면  
                        (c >= 'a' && c <= 'f') ? (c - 'a' + 10) : (c - 'A' + 10);   // "a"~"f" 또는 "A"~"F"면 10~15로 변환
            (*dst)->a[bit_pos / WORD_BITLEN] |= value << (bit_pos % WORD_BITLEN);   // 해당 위치에 0~15 입력
            bit_pos += 4;  // 4비트씩 (문자 하나당 4비트이기 때문)
        }
    }
    /* 10진수 처리(미완) */
    else if (base == 10) {

    }

    return bi_refine(*dst);     // 메모리 재할당
}

msg bi_get_random(OUT bigint** dst, IN int word_len) {

    /* 워드 길이 체크 */
    if (word_len <= 0) {
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* bigint 초기화 */
    bi_new(dst, word_len);

    /* 부호값 임의의 값 설정 */
    (*dst)->sign = byte_rand() % 2;

    /* array word_len만큼 임의의 값 설정 */
    array_rand((*dst)->a, word_len);

    return bi_refine(*dst);     // 메모리 재할당(마지막 원소가 0일 수도 있음)
}

msg bi_print(IN const bigint* dst, IN int base) {

    /* bigint NULL 체크 */
    if (dst == NULL || dst->word_len <= 0 || dst->a == NULL) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* 진수값 체크 */
    if (base != 2 && base != 16) {
        fprintf(stderr, UnSupportBaseErrMsg);
        return UnSupportBaseErr;
    }

    /* Bigint 출력 */
    if (dst->sign == NEGATIVE) {        // 부호값 (음의 부호 처리)
        printf("-");
    }
    
    /* 2진수 출력 */
    if (base == 2) {
        printf("0b");
        int leading_zero = 1;                               // 처음의 0들을 건너뛰기 위한 플래그
        for (int i = dst->word_len - 1; i >= 0; i--) {      // WORD 배열 인덱스를 역순으로
            for (int j = WORD_BITLEN - 1; j >= 0; j--) {    // 각 WORD 내 비트를 역순으로
                int bit = (dst->a[i] >> j) & 1;             // 해당 비트를 추출 (MSB부터)
                if (bit == 1) {                             // 1이면
                    leading_zero = 0;                       // leading_zero 해제
                }
                if (!leading_zero) {                        // leading_zero 해제된 이후로 계속
                    printf("%d", bit);                      // 출력
                }
            }
        }
        // 모든 비트가 0일 경우 0 출력
        if (leading_zero) {
            printf("0");
        }
    }
    /* 16진수 출력 */
    else if (base == 16) {
        printf("0x"); 
        int leading_zero = 1;                                // 처음의 0들을 건너뛰기 위한 플래그
        for (int i = dst->word_len - 1; i >= 0; i--) {       // WORD 배열 인덱스를 역순으로
            if (dst->a[i] != 0) {                            
                if (leading_zero) {                          // leading_zero가 1인 경우
                    printf("%x", dst->a[i]);                 // 패딩 없이 출력
                    leading_zero = 0;                        // leading_zero 해제
                } else {
                    printf("%08x", dst->a[i]);               // 나머지 비트를 8자리로 패딩하여 출력
                }
            } else if (!leading_zero) {                      // leading_zero가 해제된 이후는
                printf("%08x", dst->a[i]);                   // 0포함 출력 (ex. 0x12345678 00012345)
            }
        }

        // 모든 비트가 0일 경우 0 출력
        if (leading_zero) {
            printf("0");
        }
    }
    return CLEAR;
}

msg bi_new(OUT bigint** dst, IN int word_len) {

    /* NULL이 아니면 메모리 해제 */
    if (*dst != NULL){
        bi_delete(dst);
    }

    /* 워드 길이 체크 */
    if (word_len <= 0 ){
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* bigint 메모리 할당 */
    *dst = (bigint*)calloc(1, sizeof(bigint));
    if (*dst == NULL) {
        fprintf(stderr, MemAllocErrMsg);
        return MemAllocErr;
    }

    /* 초기화 */
    (*dst)->sign = NON_NEGATIVE;    // 음이 아닌 정수로 초기화
    (*dst)->word_len = word_len;
    (*dst)->a = (word*)calloc(word_len, sizeof(word));
    if ((*dst)->a == NULL) {
        fprintf(stderr, MemAllocErrMsg);
        free(*dst);
        return MemAllocErr;
    }

    return CLEAR;
}

msg bi_delete(UPDATE bigint** dst) {
    /* 메모리 NULL 체크 */
	if (*dst == NULL) {
		return CLEAR;
	}

    array_init((*dst)->a, (*dst)->word_len);
    
    /* 비밀값 제거 */
	(*dst)->sign = NON_NEGATIVE;
	(*dst)->word_len = 0;

    /* 메모리 해제 */
    free((*dst)->a);
	free(*dst);
	*dst = NULL;

    if (*dst != NULL) {
        return printf("NO!");
    }

	return CLEAR;
}

msg bi_refine(UPDATE bigint* dst) {
    /* 메모리 NULL 체크 */
	if (dst == NULL) {
		fprintf(stderr, DSTpNULLErrMsg);
		return DSTpNULLErr;
	}

    /* 새로운 워드 길이 계산 */
	int new_word_len = dst->word_len;
	while (new_word_len > 1 && dst->a[new_word_len - 1] == 0){  // 마지막 원소부터 0이면 WORD_LEN 줄이기
		new_word_len--;
	}

    /* 메모리 재할당 */
	if (new_word_len != dst->word_len){              // WORD_LEN이 다르면 재할당
		dst->a = (word*)realloc(dst->a, new_word_len * sizeof(word));
		if (dst->a == NULL){
			fprintf(stderr, MemAllocErrMsg);
			return(MemAllocErr);
		}
		dst->word_len = new_word_len;
	}

    if ((dst->word_len) == 1 && (dst->a[0] == 0x0)){ // WORD_LEN이 1이고 값이 0이면 부호는 음이 아닌 정수로
        dst->sign = NON_NEGATIVE;
    }

	return CLEAR;
} 

msg bi_assign(UPDATE bigint** dst, IN const bigint* src) {
    /* Source bigint NULL 체크 */
    if (src == NULL) { 
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Source array NULL 체크 */
    if (src->a == NULL) { 
        fprintf(stderr, SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* Source 워드 길이 체크 */
    if (src->word_len <= 0) { 
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* 일치 여부 체크 */
	if (*dst == src){
		return CLEAR;
	}

    /* bigint 초기화 */
	bi_new(dst, src->word_len);

    /* 복사 */
	(*dst)->sign = src->sign;

	array_copy((*dst)->a, src->a, src->word_len);

	return CLEAR;
}

msg bi_compareABS(IN bigint** A, IN bigint** B) {
    int n = (*A)->word_len;
    int m = (*B)->word_len;

    /* 배열 길이 비교 */
    if (n > m) {
        return COMPARE_GREATER;
    }
    else if (n < m) {
        return COMPARE_LESS;
    }

    /* MSB에서 LSB까지 각 배열 값 비교 */
    for (int j = n - 1; j >= 0; j--){
        if ((*A)->a[j] > (*B)->a[j]){
            return COMPARE_GREATER;
        }
        else if ((*A)->a[j] < (*B)->a[j]) {
            return COMPARE_LESS;
        }
    }

    /* 배열이 같음 */
    return COMPARE_EQUAL;
}

msg bi_compare(IN bigint** A, IN bigint** B) {
    /* 부호 비교 */
    if (((*A)->sign == NON_NEGATIVE) && ((*B)->sign == NEGATIVE)) {
        return COMPARE_GREATER;
    }
    if (((*A)->sign == NEGATIVE) && ((*B)->sign == NON_NEGATIVE)) {
        return COMPARE_LESS;
    }

    /* 절댓값 비교 */
    msg ret = bi_compareABS(A, B);
    
    /* 부호에 따라 결과 조정 */
    if ((*A)->sign == NON_NEGATIVE) {
        return ret;
    }
    else {
        return ret * (-1); 
    }
}
