#include "test.h"

/*
	bigint* A; // bigint 구조
    bigint* B = NULL;
    bigint* C = NULL;
    bigint* D = NULL;
    bigint* E = NULL;
    msg result;

    // 1. bi_set_from_array
    word arr[] = {0x12345678, 0x9ABCDEF0};
    result = bi_set_from_array(&A, 0, 2, arr);
    printf("bi_set_from_array result: %d\n", result);
    bi_print(A, 16);
    bi_delete(&A);

    // 2. bi_set_from_string
    result = bi_set_from_string(&B, "1123456789", 16);
    printf("bi_set_from_string result (16): %d\n", result);
    bi_print(B, 16);
    bi_delete(&B);

    // 3. bi_set_from_string
    result = bi_set_from_string(&C, "-11A2B3C4D", 16);
    printf("bi_set_from_string result (16): %d\n", result);
    bi_print(C, 2);
    bi_delete(&C);

    // 4. bi_get_random
    result = bi_get_random(&D, 0, 2);
    printf("bi_get_random result: %d\n", result);
    bi_print(D, 2);

    // 5. bi_assign
    result = bi_assign(&E, D);
    printf("bi_assign result: %d\n", result);
    printf("Copied bigint:\n");
    bi_print(E, 2);
    bi_delete(&E);

    // 6. bi_refine
    result = bi_set_from_string(&E, "0000000000000000000000000000000000000000001111001010101", 2);
    printf("word_len = %d\n", E->word_len);
    bi_print(E, 2);

    // 7. bi_delete
    bi_delete(&E);
    if (E == NULL) {
        printf("bi_delete successful.\n");
    }
*/

msg test_bi_set_from_array() {

}

msg test_bi_set_from_string() {

}

msg test_bi_new() {

}

msg test_bi_delete() {

}

msg test_bi_gen_random() {

}

msg test_bi_refine() {

}

msg test_bi_assign() {
    
}
