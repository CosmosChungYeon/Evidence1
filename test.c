#include <stdio.h>
#include <stdint.h>

typedef uint32_t msg;
typedef uint32_t word;

typedef struct {
	int sign;
	int word_len;
	word* a;
} bigint;

/* bigint <- array */
msg bi_set_from_array(bigint* dst, int sign, int word_len, word* a);

/* bigint <- string */
/* str = 0x123qqppqqwq 에러메시지 필요*/
msg bi_set_from_string(bigint* dst, char* int_str, int base);

/* A[4] = {1,2,3,0} -> {1,2,3,*1*} 마지막 원소가 nonzero여야 함 */
msg bi_get_random(bigint* dst, int word_len);

msg bi_print(bigint* dst, int base);

msg bi_new(bigint* dst, int word_len);
msg bi_delete(bigint* dst);

msg bi_refine(bigint* dst); // 메모리 조정

/* tmp <- x */
msg bi_assign(bigint* dst, bigint* src);

int main() {
	//puts("HELLO KMU!!");
		
	bigint a, b, c;
	/*
		a = -0x123213129389213
		b = 0x1fffff9389213
		a = b
	*/
	bi_set_from_string(&a, "-0x123213129389213", 16);
	bi_set_from_string(&b, "0x1fffff9389213", 16);
	bi_assign(&a, &b);
	
	return 0;
}