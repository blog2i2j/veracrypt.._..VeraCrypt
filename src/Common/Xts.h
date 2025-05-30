/*
 Derived from source code of TrueCrypt 7.1a, which is
 Copyright (c) 2008-2012 TrueCrypt Developers Association and which is governed
 by the TrueCrypt License 3.0.

 Modifications and additions to the original source code (contained in this file)
 and all other portions of this file are Copyright (c) 2013-2025 AM Crypto
 and are governed by the Apache License 2.0 the full text of which is
 contained in the file License.txt included in VeraCrypt binary and source
 code distribution packages.
*/

#ifndef XTS_H
#define XTS_H

// Header files (optional)

#include "Tcdefs.h"
#include "Common/Endian.h"
#include "Crypto.h"

#ifdef __cplusplus
extern "C" {
#endif

// Macros

#ifndef LITTLE_ENDIAN
#	define LITTLE_ENDIAN	1
#endif

#ifndef BIG_ENDIAN
#	define BIG_ENDIAN		2
#endif

#ifndef BYTE_ORDER
#	define BYTE_ORDER		LITTLE_ENDIAN
#endif

#ifndef LE64
#	if BYTE_ORDER == LITTLE_ENDIAN
#		define LE64(x)	(x)
#	endif
#endif

// Custom data types

#ifndef TC_LARGEST_COMPILER_UINT
#	ifdef TC_NO_COMPILER_INT64
		typedef unsigned __int32	TC_LARGEST_COMPILER_UINT;
#	else
		typedef unsigned __int64	TC_LARGEST_COMPILER_UINT;
#	endif
#endif

#ifndef TCDEFS_H
typedef union
{
	struct
	{
		unsigned __int32 LowPart;
		unsigned __int32 HighPart;
	};
#	ifndef TC_NO_COMPILER_INT64
	unsigned __int64 Value;
#	endif

} UINT64_STRUCT;
#endif

// Public function prototypes

void EncryptBufferXTS (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);
static void EncryptBufferXTSParallel (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);
static void EncryptBufferXTSNonParallel (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);
void DecryptBufferXTS (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);
static void DecryptBufferXTSParallel (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);
static void DecryptBufferXTSNonParallel (unsigned __int8 *buffer, TC_LARGEST_COMPILER_UINT length, const UINT64_STRUCT *startDataUnitNo, unsigned int startCipherBlockNo, unsigned __int8 *ks, unsigned __int8 *ks2, int cipher);

#ifdef __cplusplus
}
#endif

#endif	// #ifndef XTS_H
