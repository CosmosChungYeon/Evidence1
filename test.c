#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "basic_func.h"
#include "config.h"
#include "bi_def.h"
#include "msg.h"
#include "const.h"

int main() {
    srand(time(NULL));

	bigint* A; // bigint 구조체 포인터 초기화
    bigint* B = NULL;
    bigint* C = NULL;
    bigint* D = NULL;
    bigint* E = NULL;
    msg result;

    // 1. bi_set_from_array 테스트
    word arr[] = {0x12345678, 0x9ABCDEF0};
    result = bi_set_from_array(&A, 0, 2, arr);
    printf("bi_set_from_array result: %d\n", result);
    bi_print(A, 16);
    bi_delete(&A);

    // 2. bi_set_from_string 테스트 (16진수)
    result = bi_set_from_string(&B, "0x11234GG56789", 16);
    printf("bi_set_from_string result (16): %d\n", result);
    bi_print(B, 16);
    bi_delete(&B);

    // 3. bi_set_from_string 테스트 (16진수)
    result = bi_set_from_string(&C, "-0x11A2B3C4D", 16);
    printf("bi_set_from_string result (16): %d\n", result);
    bi_print(C, 2);
    bi_delete(&C);

    // 4. bi_get_random 테스트
    result = bi_get_random(&D, 2);
    printf("bi_get_random result: %d\n", result);
    bi_print(D, 2);

    // 5. bi_assign 테스트
    result = bi_assign(&E, D);
    printf("bi_assign result: %d\n", result);
    printf("Copied bigint:\n");
    bi_print(E, 2);
    bi_delete(&E);

    // 6. bi_refine 테스트
    result = bi_set_from_string(&E, "0b0000000000000000000000000000000000000000001111001010101", 2);
    printf("%d\n", E->word_len);
    bi_print(E, 2);

    // 7. bi_delete 테스트
    bi_delete(&E);
    if (E == NULL) {
        printf("bi_delete successful.\n");
    }

    return 0;
}