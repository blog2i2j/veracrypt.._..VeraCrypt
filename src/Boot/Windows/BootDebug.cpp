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

#include "Platform.h"
#include "Bios.h"
#include "BootConsoleIo.h"
#include "BootDefs.h"
#include "BootDiskIo.h"
#include "BootDebug.h"


#ifdef TC_BOOT_TRACING_ENABLED

void InitDebugPort ()
{
	__asm
	{
		mov dx, TC_DEBUG_PORT
		mov ah, 1
		int 0x17
		mov dx, TC_DEBUG_PORT
		mov ah, 0xe2
		int 0x17
	}
}


void WriteDebugPort (uint8 dataByte)
{
	__asm
	{
		mov al, dataByte
		mov dx, TC_DEBUG_PORT
		mov ah, 0
		int 0x17
	}
}

#endif // TC_BOOT_TRACING_ENABLED


#ifdef TC_BOOT_DEBUG_ENABLED

extern "C" void PrintDebug (uint32 debugVal)
{
	Print (debugVal);
	PrintEndl();
}


void PrintVal (const char *message, const uint32 value, bool newLine, bool hex)
{
	Print (message);
	Print (": ");

	if (hex)
		PrintHex (value);
	else
		Print (value);

	if (newLine)
		PrintEndl();
}


void PrintVal (const char *message, const uint64 &value, bool newLine, bool hex)
{
	Print (message);
	Print (": ");
	PrintHex (value);
	if (newLine)
		PrintEndl();
}


void PrintHexDump (uint8 *mem, size_t size, uint16 *memSegment)
{
	const size_t width = 16;
	for (size_t pos = 0; pos < size; )
	{
		for (int pass = 1; pass <= 2; ++pass)
		{
			size_t i;
			for (i = 0; i < width && pos < size; ++i)
			{
				uint8 dataByte;
				if (memSegment)
				{
					__asm
					{
						push es
						mov si, ss:memSegment
						mov es, ss:[si]
						mov si, ss:mem
						add si, pos
						mov al, es:[si]
						mov dataByte, al
						pop es
					}
					pos++;
				}
				else
					dataByte = mem[pos++];

				if (pass == 1)
				{
					PrintHex (dataByte);
					PrintChar (' ');
				}
				else
					PrintChar (IsPrintable (dataByte) ? dataByte : '.');
			}

			if (pass == 1)
			{
				pos -= i;
				PrintChar (' ');
			}
		}

		PrintEndl ();
	}
}


void PrintHexDump (uint16 memSegment, uint16 memOffset, size_t size)
{
	PrintHexDump ((uint8 *) memOffset, size, &memSegment);
}

#endif // TC_BOOT_DEBUG_ENABLED


#ifdef TC_BOOT_STACK_CHECKING_ENABLED

extern "C" char end[];

static void PrintStackInfo ()
{
	uint16 spReg;
	__asm mov spReg, sp

	Print ("Stack: "); Print (TC_BOOT_LOADER_STACK_TOP - spReg);
	Print ("/"); Print (TC_BOOT_LOADER_STACK_TOP - (uint16) end);
}


void CheckStack ()
{
	uint16 spReg;
	__asm mov spReg, sp

	if (*(uint32 *) end != 0x12345678UL || spReg < (uint16) end)
	{
		__asm cli
		__asm mov sp, TC_BOOT_LOADER_STACK_TOP

		PrintError ("Stack overflow");
		TC_THROW_FATAL_EXCEPTION;
	}
}


void InitStackChecker ()
{
	*(uint32 *) end = 0x12345678UL;

	PrintStackInfo();
	PrintEndl();
}

#endif // TC_BOOT_STACK_CHECKING_ENABLED
