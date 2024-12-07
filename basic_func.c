#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_func.h"
#include "calc_operations.h"
#include "msg.h"
#include "const.h"

msg bi_set_from_array(OUT bigint** dst, IN int sign, IN int word_len, IN const word* a) {
    /* Check sign value */
    if (sign != NON_NEGATIVE && sign != NEGATIVE) {
        fprintf(stderr, SignValErrMsg);
        return SignValErr;
    }

    /* Check word length */
    if (word_len <= NON_NEGATIVE) {
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* Check if the array is NULL */
    if (a == NULL) {
        fprintf(stderr, SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* Initialize bigint */
    bi_new(dst, word_len);

    (*dst)->sign = sign;
    
    for (int idx = 0; idx < word_len; idx++) {            
        (*dst)->a[idx] = a[idx];
    }

    return bi_refine(*dst); // Reallocate memory
}

msg bi_set_from_string(OUT bigint** dst, IN const char* int_str, IN int base) {
    /* Check if the string is NULL */
    if (int_str == NULL) {
        fprintf(stderr, StrNULLErrMsg);
        return StrNULLErr;
    }

    /* Handle the sign */
    int sign = NON_NEGATIVE;
    if (int_str[0] == '-') {
        sign = NEGATIVE;
        int_str++;
    }

    /* Validate the string based on the given base */
    int idx = 0;
    while (int_str[idx] != '\0') { // Iterate through the string
        if (base == 2) {           // Binary base
            if (int_str[idx] != '0' && int_str[idx] != '1') {
                fprintf(stderr, BinInputErrMsg);
                return BinInputErr;
            }
        }
        else if (base == 16) {     // Hexadecimal base
            if (!((int_str[idx] >= '0' && int_str[idx] <= '9') ||
                (int_str[idx] >= 'a' && int_str[idx] <= 'f') ||
                (int_str[idx] >= 'A' && int_str[idx] <= 'F'))) {
                fprintf(stderr, HexInputErrMsg);
                return HexInputErr;
            }
        }
        else {
            fprintf(stderr, UnSupportBaseErrMsg);
            return UnSupportBaseErr;
        }
        idx++;
    }

    /* Convert string to integer */
    int str_len = strlen(int_str);
    int word_len = 1;

    /* Calculate word length based on base */
    if (base == 2) {       // Binary
        word_len = (str_len / BINARY_STRING_LENGTH) + (str_len % BINARY_STRING_LENGTH != 0); // Ceiling
    }
    else if (base == 16) { // Hexadecimal
        word_len = (str_len / HEX_STRING_LENGTH) + (str_len % HEX_STRING_LENGTH != 0);       // Ceiling
    }

    /* Initialize bigint */
    bi_new(dst, word_len);

    (*dst)->sign = sign;

    /* Process binary base */
    if (base == 2) {
        int bit_pos = 0; // Bit position tracker
        for (int idx = str_len - 1; idx >= 0; idx--) { // Process string from LSB
            if (int_str[idx] == '1') {
                (*dst)->a[bit_pos / WORD_BITLEN] |= ((word)1 << (bit_pos % WORD_BITLEN)); // Set bit
            }
            bit_pos++;
        }
    }
    /* Process hexadecimal base */
    else if (base == 16) {
        int word_idx = 0;  // Word index
        int bit_pos = 0;   // Bit position within the word

        for (int idx = str_len - 1; idx >= 0; idx--) { // Process string from LSB
            char c = int_str[idx];
            int value = (c >= '0' && c <= '9') ? (c - '0')      :
                        (c >= 'a' && c <= 'f') ? (c - 'a' + 10) :
                        (c - 'A' + 10);  // Convert character to hexadecimal value

            /* Add value to the current word */
            (*dst)->a[word_idx] |= ((word)value << bit_pos);

            /* Update bit position */
            bit_pos += 4; // Each hexadecimal digit is 4 bits
            if (bit_pos >= WORD_BITLEN) {  // Move to the next word if the current one is full
                bit_pos -= WORD_BITLEN;
                word_idx++;
            }
        }
    }

    return bi_refine(*dst); // Reallocate memory
}

msg bi_get_random(OUT bigint** dst, IN int word_len) {
    /* Check word length */
    if (word_len <= 0) {
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* Initialize bigint */
    bi_new(dst, word_len);

    /* Set a random sign value */
    (*dst)->sign = byte_rand() % 2;

    /* Populate the array with random values */
    array_rand((*dst)->a, word_len);

    return bi_refine(*dst); // Reallocate memory (last element might be zero)
}

msg bi_print(IN const bigint* dst, IN int base) {
    /* Check if bigint is NULL */
    if (dst == NULL || dst->word_len <= 0 || dst->a == NULL) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* Check if base is supported */
    if (base != 2 && base != 16) {
        fprintf(stderr, UnSupportBaseErrMsg);
        return UnSupportBaseErr;
    }

    /* Print the sign if negative */
    if (dst->sign == NEGATIVE) {
        printf("-");
    }

    /* Print in binary format */
    if (base == 2) {
        printf("0b");
        int leading_zero = 1; // Flag to skip leading zeros
        for (int word_idx = dst->word_len - 1; word_idx >= 0; word_idx--) { // Traverse words in reverse
            for (int bit_idx = WORD_BITLEN - 1; bit_idx >= 0; bit_idx--) {  // Traverse bits in reverse
                int bit = (dst->a[word_idx] >> bit_idx) & 1;                // Extract bit (MSB first)
                if (bit == 1) {
                    leading_zero = 0;  // Disable leading zero flag
                }
                if (!leading_zero) {   // Start printing after first 1
                    printf("%d", bit);
                }
            }
        }
        // If all bits are zero, print 0
        if (leading_zero) {
            printf("0");
        }
    }
    /* Print in hexadecimal format */
    else if (base == 16) {
        printf("0x");
        int leading_zero = 1; // Flag to skip leading zeros
        for (int word_idx = dst->word_len - 1; word_idx >= 0; word_idx--) { // Traverse words in reverse
            if (dst->a[word_idx] != 0) {
                if (leading_zero) {   // Print without padding if first non-zero word
                    printf(FORMAT, dst->a[word_idx]);
                    leading_zero = 0; // Disable leading zero flag
                }
                else {
                    printf(FORMAT, dst->a[word_idx]); // Print with padding
                }
            }
            else if (!leading_zero) { // Print zero-padded words after first non-zero
                printf(FORMAT, dst->a[word_idx]);
            }
        }

        // If all words are zero, print 0
        if (leading_zero) {
            printf("0");
        }
    }

    return CLEAR;
}

msg bi_fprint(IN FILE* file, IN const bigint* dst, IN int base) {
    /* Check if bigint is NULL */
    if (dst == NULL || dst->word_len <= 0 || dst->a == NULL) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* Check if base is supported */
    if (base != 2 && base != 16) {
        fprintf(stderr, UnSupportBaseErrMsg);
        return UnSupportBaseErr;
    }

    /* Print the sign if negative */
    if (dst->sign == NEGATIVE) {
        fprintf(file, "-");
    }

    /* Print in binary format */
    if (base == 2) {
        fprintf(file, "0b");
        int leading_zero = 1; // Flag to skip leading zeros
        for (int word_idx = dst->word_len - 1; word_idx >= 0; word_idx--) { // Traverse words in reverse
            for (int bit_idx = WORD_BITLEN - 1; bit_idx >= 0; bit_idx--) {  // Traverse bits in reverse
                int bit = (dst->a[word_idx] >> bit_idx) & 1;                // Extract bit (MSB first)
                if (bit == 1) {
                    leading_zero = 0; // Disable leading zero flag
                }
                if (!leading_zero) {  // Start printing after first 1
                    fprintf(file, "%d", bit);
                }
            }
        }
        // If all bits are zero, print 0
        if (leading_zero) {
            fprintf(file, "0");
        }
    }
    /* Print in hexadecimal format */
    else if (base == 16) {
        fprintf(file, "0x");
        int leading_zero = 1; // Flag to skip leading zeros
        for (int word_idx = dst->word_len - 1; word_idx >= 0; word_idx--) { // Traverse words in reverse
            if (dst->a[word_idx] != 0) {
                if (leading_zero) {   // Print without padding if first non-zero word
                    fprintf(file, FORMAT, dst->a[word_idx]);
                    leading_zero = 0; // Disable leading zero flag
                }
                else { // Print with padding
                    fprintf(file, FORMAT, dst->a[word_idx]);
                }
            }
            else if (!leading_zero) { // Print zero-padded words after first non-zero
                fprintf(file, FORMAT, dst->a[word_idx]);
            }
        }

        // If all words are zero, print 0
        if (leading_zero) {
            fprintf(file, "0");
        }
    }

    return CLEAR;
}

msg bi_new(OUT bigint** dst, IN int word_len) {
    /* Free memory if dst is not NULL */
    if (*dst != NULL) {
        bi_delete(dst);
    }

    /* Check word length */
    if (word_len < 1) {
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* Allocate memory for bigint */
    *dst = (bigint*)calloc(1, sizeof(bigint));
    if (*dst == NULL) {
        fprintf(stderr, MemAllocErrMsg);
        return MemAllocErr;
    }

    /* Initialize bigint fields */
    (*dst)->sign = NON_NEGATIVE; // Initialize as non-negative
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
    /* Check if memory is already NULL */
    if (*dst == NULL) {
        return CLEAR;
    }

    /* Initialize the array to zero to remove sensitive data */
    array_init((*dst)->a, (*dst)->word_len);

    /* Reset bigint fields */
    (*dst)->sign = NON_NEGATIVE;
    (*dst)->word_len = 0;

    /* Free allocated memory */
    free((*dst)->a);
    free(*dst);
    *dst = NULL;

    if (*dst != NULL) {
        fprintf(stderr, NOTInitErrMsg);
        return NOTInitErr;
    }

    return CLEAR;
}

msg bi_refine(UPDATE bigint* dst) {
    /* Check for NULL pointer */
    if (dst == NULL) {
        fprintf(stderr, DSTpNULLErrMsg);
        return DSTpNULLErr;
    }

    /* Calculate the new word length by removing leading zeros */
    int new_word_len = dst->word_len;
    word* a = dst->a;
    while (new_word_len > 1 && a[new_word_len - 1] == 0) { // Reduce word length if the last element is zero
        new_word_len--;
    }

    /* Reallocate memory if word length has changed */
    if (new_word_len != dst->word_len) {
        word* new_a = (word*)realloc(dst->a, new_word_len * sizeof(word));
        if (new_a == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return(MemAllocErr);
        }
        dst->a = new_a;
        dst->word_len = new_word_len;
    }

    /* Set the sign to non-negative if the value is zero */
    if ((dst->word_len) == 1 && (dst->a[0] == 0x0)) {
        dst->sign = NON_NEGATIVE;
    }

    return CLEAR;
}

msg bi_assign(UPDATE bigint** dst, IN const bigint* src) {
    /* Check if the source bigint is NULL */
    if (src == NULL) {
        fprintf(stderr, SrcNULLErrMsg);
        return SrcNULLErr;
    }

    /* Check if the source array is NULL */
    if (src->a == NULL) {
        fprintf(stderr, SrcArrNULLErrMsg);
        return SrcArrNULLErr;
    }

    /* Check if the source word length is valid */
    if (src->word_len <= 0) {
        fprintf(stderr, WordLenErrMsg);
        return WordLenErr;
    }

    /* Skip copying if the source and destination are the same */
    if (*dst == src) {
        return CLEAR;
    }

    /* Initialize the destination bigint */
    bi_new(dst, src->word_len);

    /* Copy the sign and array values */
    (*dst)->sign = src->sign;
    array_copy((*dst)->a, src->a, src->word_len);

    return CLEAR;
}

msg bi_compareABS(IN bigint** A, IN bigint** B) {
    int A_wlen = (*A)->word_len;
    int B_wlen = (*B)->word_len;

    /* Compare word lengths */
    if (A_wlen != B_wlen) {
        return (A_wlen > B_wlen) ? COMPARE_GREATER : COMPARE_LESS;
    }

    word* a = (*A)->a;
    word* b = (*B)->a;

    /* Compare values from most significant word to least significant word */
    for (int idx = A_wlen - 1; idx >= 0; idx--) {
        if (a[idx] != b[idx]) {
            return (a[idx] > b[idx]) ? COMPARE_GREATER : COMPARE_LESS;
        }
    }

    /* The arrays are equal */
    return COMPARE_EQUAL;
}

msg bi_compare(IN bigint** A, IN bigint** B) {
    /* Compare signs */
    if ((*A)->sign != (*B)->sign) {
        return ((*A)->sign == NON_NEGATIVE) ? COMPARE_GREATER : COMPARE_LESS;
    }

    /* Create refined copies of A and B */
    bigint* tmpA = NULL, * tmpB = NULL;
    bi_assign(&tmpA, *A);
    bi_assign(&tmpB, *B);
    bi_refine(tmpA);
    bi_refine(tmpB);

    /* Compare absolute values */
    msg ret = bi_compareABS(&tmpA, &tmpB);

    bi_delete(&tmpA);
    bi_delete(&tmpB);

    /* Adjust result based on sign */
    return ((*A)->sign == NON_NEGATIVE) ? ret : ret * (-1);
}

msg bi_word_shift_left(UPDATE bigint** dst, IN int shift_count) {
    /* Get original length and calculate new length after the shift */
    int original_len = (*dst)->word_len;
    int new_len = original_len + shift_count;

    /* Update word length */
    (*dst)->word_len = new_len;

    /* Expand the array to accommodate the shift */
    word* word_tmp = (word*)realloc((*dst)->a, new_len * sizeof(word));
    if (word_tmp == NULL) {
        fprintf(stderr, MemAllocErrMsg);
        return MemAllocErr;
    }
    (*dst)->a = word_tmp;

    /* Move existing data to the left by shift_count positions */
    memmove((*dst)->a + shift_count, (*dst)->a, original_len * sizeof(word));

    /* Initialize the newly added portion with zeros */
    memset((*dst)->a, 0, shift_count * sizeof(word));

    return CLEAR;
}

msg bi_word_shift_right(UPDATE bigint** dst, IN int shift_count) {
    /* Get the current length */
    int original_len = (*dst)->word_len;

    /* Handle cases where the shift count is greater than or equal to the length */
    if (shift_count >= original_len) {
        (*dst)->word_len = 0;

        /* Free the memory and reset the array */
        free((*dst)->a);
        (*dst)->a = NULL;

        return CLEAR;
    }

    /* Shift the data to the right by shift_count positions */
    memmove((*dst)->a, (*dst)->a + shift_count, (original_len - shift_count) * sizeof(word));

    /* Update the word length */
    (*dst)->word_len -= shift_count;

    /* Reduce memory usage by resizing the array */
    word* word_tmp = (word*)realloc((*dst)->a, (*dst)->word_len * sizeof(word));
    if (word_tmp == NULL && (*dst)->word_len > 0) {
        fprintf(stderr, MemAllocErrMsg);
        return MemAllocErr;
    }
    (*dst)->a = word_tmp;

    return CLEAR;
}

msg bi_doubling(UPDATE bigint* dst) {
    word carry = 0; // Carry for the next word
    for (int idx = 0; idx < dst->word_len; idx++) {
        word next_carry = (dst->a[idx] & MSB_BIT_MASK) >> (WORD_BITLEN - 1); // Extract the MSB of the current word to use as carry for the next word
        dst->a[idx] = (dst->a[idx] << 1) | carry; // Double the current word and add the carry from the previous word
        carry = next_carry;                       // Update carry for the next word
    }

    /* If there is a carry left, extend the array to accommodate it */
    if (carry) {
        dst->word_len += 1; // Increase the word length
        word* tmp = (word*)realloc(dst->a, dst->word_len * sizeof(word));
        if (tmp == NULL) {
            fprintf(stderr, MemAllocErrMsg);
            return MemAllocErr;
        }
        dst->a = tmp;
        dst->a[dst->word_len - 1] = carry; // Store the carry in the new MSB
    }

    return CLEAR;
}

msg bi_plus_one(UPDATE bigint** dst) {
    bigint* one = NULL;
    bi_set_one(&one);        // Set the value of "one" to 1

    bi_addc(dst, dst, &one); // Add one to the current bigint
    bi_delete(&one);
    return CLEAR;
}

msg bi_zero_check(IN bigint** src) {
    /* Check if the bigint is zero by verifying it has one word and its value is 0 */
    return (((*src)->word_len == 1) && ((*src)->a[0] == 0x0));
}

msg bi_set_one(UPDATE bigint** dst) {
    /* Set the bigint to the value of 1 in binary representation */
    bi_set_from_string(dst, "1", 2);
    return CLEAR;
}
