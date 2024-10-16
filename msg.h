#ifndef MSG_H
#define MSG_H

#define CLEAR               1       // 문제 없음

/* 0x001* CONFIG 관련 오류 */
#define UnSupportWordBitLenErr  0x0010  // 16: 지원하지 않는 WORD_BITLEN 오류
#define UnSupportUseDRBGValErr  0x0011  // 17: 지원하지 않는 USE_DRBG 값 오류

/* 0x01** 메모리 관련 오류 */
#define MemAllocErr             0x0100   // 256: 메모리 할당 오류
#define SrcNULLErr              0x0101   // 257: Source bigint NULL 오류
#define SrcArrNULLErr           0x0102   // 258: Source array or bigint array NULL 오류
#define DSTpNULLErr             0x0103   // 259: Destination bigint NULL 오류

/* 0x02** BIGINT SET 입력 관련 오류 */
#define SignValErr              0x0200   // 512: 부호값 오류
#define WordLenErr              0x0201   // 513: 워드 길이 오류
#define StrNULLErr              0x0202   // 514: 문자열 NULL 오류

/* 0x03** BASE 입력 관련 오류 */
#define UnSupportBaseErr        0x0300   // 768: 지원하지 않는 Base 오류
#define BinInputErr             0x0301   // 769: 2진수 입력 유효성 오류
#define DecInputErr             0x0302   // 770: 10진수 입력 유효성 오류
#define HexInputErr             0x0303   // 771: 16진수 입력 유효성 오류

/* 0x04** 초기화 관련 오류 */
#define NOTInitErr              0x0400   // 1024: 초기화 실패 오류


/* 오류 메시지 */
#define UnSupportWordBitLenErrMsg   "Error: Unsupported word bitlen (only 8, 32, 64)\n Force the bitlen to 32\n\n"
#define UnSupportUseDRBGValErrMsg   "Error: Unsupported USE_DRBG value (0: not use, 1: use)\n Force to use DRBG\n\n"


#define MemAllocErrMsg              "Error: Failed to allocate memory\n\n"
#define SrcNULLErrMsg               "Error: Source bigint is NULL\n\n"
#define SrcArrNULLErrMsg            "Error: Source (bigint) array is NULL\n\n"
#define DSTpNULLErrMsg              "Error: Destination pointer is NULL\n\n"

#define SignValErrMsg               "Error: Invalid sign value (must be 0(+) or 1(-))\n\n"
#define WordLenErrMsg               "Error: Invalid word_len value (must be > 0)\n\n"
#define StrNULLErrMsg               "Error: Int_Str array is NULL\n\n"

#define UnSupportBaseErrMsg         "Error: Unsupported base (only 2(0b), 10, 16(0x))\n\n"
#define BinInputErrMsg              "Error: Invalid binary value (0~1)\n\n"
#define DecInputErrMsg              "Error: Invalid decimal value (0~9)\n\n"
#define HexInputErrMsg              "Error: Invalid hexadecimal value (0~9, a~f, A~F)\n\n"

#define NOTInitErrMsg               "Error: Failed to initialize array\n\n"

#endif  // MSG_H