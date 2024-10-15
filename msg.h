#ifndef MSG_H
#define MSG_H

#define CLEAR               1   // 문제 없음

#define MemAllocErr         0x0100   // 메모리 할당 오류
#define SrcArrNULLErr       0x0101  // Source array NULL 오류
#define DSTpNULLErr         0x0102  // Destination bigint NULL 오류

#define SignValErr          0x0200   // 부호값 오류
#define WordLenErr          0x0201   // 워드 길이 오류
#define StrNULLErr          0x0202   // 문자열 NULL 오류

#define UnSupportBaseErr    0x0300   // 지원하지 않는 Base 오류
#define BinInputErr         0x0301   // 2진수 입력 유효성 오류
#define DecInputErr         0x0302   // 10진수 입력 유효성 오류
#define HexInputErr         0x0303   // 16진수 입력 유효성 오류

#define MemAllocErrMsg      "Error: Failed to allocate memory"
#define SignValErrMsg       "Error: Invalid sign value (must be 0(+) or 1(-))"
#define WordLenErrMsg       "Error: Invalid word_len value (must be > 0)"
#define StrNULLErrMsg       "Error: Int_Str array is NULL"
#define UnSupportBaseErrMsg "Error: Unsupported base (only 2(0b), 10, 16(0x))"
#define BinInputErrMsg      "Error: Invalid binary value (0~1)"
#define DecInputErrMsg      "Error: Invalid decimal value (0~9)"
#define HexInputErrMsg      "Error: Invalid hexadecimal value (0~9, a~f, A~F)"
#define SrcArrNULLErrMsg    "Error: Source array is NULL"
#define DSTpNULLErrMsg      "Error: Destination pointer is NULL"

#endif  // MSG_H