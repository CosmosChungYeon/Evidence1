#ifndef MSG_H
#define MSG_H

#define CLEAR               1       // 문제 없음

#define COMPARE_GREATER     1
#define COMPARE_EQUAL       0
#define COMPARE_LESS        -1

/** @name CONFIG 관련 오류 */
/**@{*/
/** @brief 지원하지 않는 WORD_BITLEN 오류  */
#define UnSupportWordBitLenErr  0x0010  // 16: 지원하지 않는 WORD_BITLEN 오류
/** @brief 지원하지 않는 USE_DRBG 값 오류 */
#define UnSupportUseDRBGValErr  0x0011  // 17: 지원하지 않는 USE_DRBG 값 오류
/**@}*/

/** @name 메모리 관련 오류 */
/**@{*/
/** @brief 메모리 할당 오류 */
#define MemAllocErr             0x0100   // 256: 메모리 할당 오류
/** @brief Source bigint NULL 오류 */
#define SrcNULLErr              0x0101   // 257: Source bigint NULL 오류
/** @brief Source array or bigint array NULL 오류 */
#define SrcArrNULLErr           0x0102   // 258: Source array or bigint array NULL 오류
/** @brief Destination bigint NULL 오류 */
#define DSTpNULLErr             0x0103   // 259: Destination bigint NULL 오류
/**@}*/

/** @name BIGINT SET 입력 관련 오류 */
/**@{*/
/** @brief 부호값 오류 */
#define SignValErr              0x0200   // 512: 부호값 오류
/** @brief 부호값 음의 정수 오류 */
#define SignNEGErr				0x0201	 // 513: 부호값 음의 정수 오류
/** @brief 워드 길이 오류 */
#define WordLenErr              0x0202   // 514: 워드 길이 오류
/** @brief 워드 길이 2배 아님 오류(barrett reduction) */
#define WordLenNotDoubleErr		0x0203	 // 515: 워드 길이 2배 아님 오류(barrett reduction)

/** @brief 문자열 NULL 오류 */
#define StrNULLErr              0x0204   // 516: 문자열 NULL 오류
/** @brief divisor 0 오류 */
#define ZeroDivisorErr			0x0205   // 517: Divisor 0 오류
/**@}*/

/** @name BASE 입력 관련 오류 */
/**@{*/
/** @brief 지원하지 않는 Base 오류 */
#define UnSupportBaseErr        0x0300   // 768: 지원하지 않는 Base 오류
/** @brief 2진수 입력 유효성 오류 */
#define BinInputErr             0x0301   // 769: 2진수 입력 유효성 오류
/** @brief 10진수 입력 유효성 오류 */
#define DecInputErr             0x0302   // 770: 10진수 입력 유효성 오류
/** @brief 16진수 입력 유효성 오류 */
#define HexInputErr             0x0303   // 771: 16진수 입력 유효성 오류
/**@}*/

/** @name 초기화 관련 오류 */
/**@{*/
/** @brief 초기화 실패 오류 */
#define NOTInitErr              0x0400   // 1024: 초기화 실패 오류
/**@}*/

/** @name 파일 관련 오류 */
/**@{*/
/** @brief 파일 생성 실패 오류 */
#define FileError               0x0500   // 1280:파일 생성 실패 오류
/**@}*/


/** @name 오류 메시지 */
/**@{*/
#define UnSupportWordBitLenErrMsg   "Error: Unsupported word bitlen (only 8, 32, 64)\n Force the bitlen to 32\n\n"
#define UnSupportUseDRBGValErrMsg   "Error: Unsupported USE_DRBG value (0: not use, 1: use)\n Force to use DRBG\n\n"

#define MemAllocErrMsg              "Error: Failed to allocate memory\n\n"
#define SrcNULLErrMsg               "Error: Source bigint is NULL\n\n"
#define SrcArrNULLErrMsg            "Error: Source (bigint) array is NULL\n\n"
#define DSTpNULLErrMsg              "Error: Destination pointer is NULL\n\n"

#define SignValErrMsg               "Error: Invalid sign value (must be 0(+) or 1(-))\n\n"
#define SignNEGErrMsg     		    "Error: Sign value is NEGATIVE (must be NON_NEGATIVE)\n\n"
#define WordLenErrMsg               "Error: Invalid word_len value (must be > 0)\n\n"
#define WordLenNotDoubleErrMsg		"Error: Invalid word_len value (barrett reduction)\n\n"
#define StrNULLErrMsg               "Error: Int_Str array is NULL\n\n"
#define ZeroDivisorErrMsg			"Error: Invalid divisor value (must not be zero)\n\n"

#define UnSupportBaseErrMsg         "Error: Unsupported base (only 2(0b), 10, 16(0x))\n\n"
#define BinInputErrMsg              "Error: Invalid binary value (0~1)\n\n"
#define DecInputErrMsg              "Error: Invalid decimal value (0~9)\n\n"
#define HexInputErrMsg              "Error: Invalid hexadecimal value (0~9, a~f, A~F)\n\n"

#define NOTInitErrMsg               "Error: Failed to initialize array\n\n"

#define FileErrorMsg                "Error: Failed to open file\n\n"
/**@}*/

#endif  // MSG_H
