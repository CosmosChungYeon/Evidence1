#ifndef MSG_H
#define MSG_H

#define CLEAR               1       // No issues

#define COMPARE_GREATER     1       // A > B
#define COMPARE_EQUAL       0       // A = B
#define COMPARE_LESS       -1       // A < B

/** @name CONFIG related errors */
/**@{*/
/** @brief Unsupported WORD_BITLEN error  */
#define UnSupportWordBitLenErr  0x0010   // 16
/** @brief Unsupported USE_DRBG value error */
#define UnSupportUseDRBGValErr  0x0011   // 17
/**@}*/

/** @name Memory-related errors */
/**@{*/
/** @brief Memory allocation error */
#define MemAllocErr             0x0100   // 256
/** @brief Source bigint NULL error */
#define SrcNULLErr              0x0101   // 257
/** @brief Source array or bigint array NULL error */
#define SrcArrNULLErr           0x0102   // 258
/** @brief Destination bigint NULL error */
#define DSTpNULLErr             0x0103   // 259
/**@}*/

/** @name BIGINT SET input-related error */
/**@{*/
/** @brief Invalid sign value error */
#define SignValErr              0x0200   // 512 
/** @brief Negative sign value error */
#define SignNEGErr				0x0201	 // 513
/** @brief Invalid word length error */
#define WordLenErr              0x0202   // 514
/** @brief Word length not double error (barrett reduction) */
#define WordLenNotDoubleErr		0x0203	 // 515

/** @brief String NULL error */
#define StrNULLErr              0x0204   // 516
/** @brief Zero divisor error  */
#define ZeroDivisorErr			0x0205   // 517
/**@}*/

/** @name BASE input-related errors */
/**@{*/
/** @brief Unsupported base error */
#define UnSupportBaseErr        0x0300   // 768
/** @brief Binary input validation error */
#define BinInputErr             0x0301   // 769
/** @brief Hexadecimal input validation error */
#define HexInputErr             0x0302   // 770
/**@}*/

/** @name Initialization-related errors */
/**@{*/
/** @brief Initialization failure error */
#define NOTInitErr              0x0400   // 1024
/**@}*/

/** @name File-related errors */
/**@{*/
/** @brief File creation failure error */
#define FileError               0x0500   // 1280
/**@}*/


/** @name Error messages */
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

#define UnSupportBaseErrMsg         "Error: Unsupported base (only 2, 16)\n\n"
#define BinInputErrMsg              "Error: Invalid binary value (0~1)\n\n"
#define HexInputErrMsg              "Error: Invalid hexadecimal value (0~9, a~f, A~F)\n\n"

#define NOTInitErrMsg               "Error: Failed to initialize array\n\n"

#define FileErrorMsg                "Error: Failed to open file\n\n"
/**@}*/

#endif  // MSG_H
