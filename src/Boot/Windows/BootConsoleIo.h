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

#ifndef TC_HEADER_Boot_BootConsoleIo
#define TC_HEADER_Boot_BootConsoleIo

#include "Platform.h"

#define TC_DEBUG_PORT 0

#define TC_BIOS_KEY_ESC 1
#define TC_BIOS_KEY_BACKSPACE 14
#define TC_BIOS_KEY_ENTER 28
#define TC_BIOS_KEY_F1 0x3b
#define TC_BIOS_KEY_F2 0x3c
#define TC_BIOS_KEY_F3 0x3d
#define TC_BIOS_KEY_F4 0x3e
#define TC_BIOS_KEY_F5 0x3f
#define TC_BIOS_KEY_F6 0x40
#define TC_BIOS_KEY_F7 0x41
#define TC_BIOS_KEY_F8 0x42
#define TC_BIOS_KEY_F9 0x43
#define TC_BIOS_KEY_F10 0x44

#define TC_BIOS_SHIFTMASK_CAPSLOCK	(1 << 6)
#define TC_BIOS_SHIFTMASK_LSHIFT	(1 << 1)
#define TC_BIOS_SHIFTMASK_RSHIFT	(1 << 0)

#define TC_BIOS_CHAR_BACKSPACE		8

#define TC_BIOS_MAX_CHARS_PER_LINE	80

void Beep ();
void ClearBiosKeystrokeBuffer ();
void ClearScreen ();
void DisableScreenOutput ();
void EnableScreenOutput ();
bool EscKeyPressed ();
uint8 GetKeyboardChar ();
uint8 GetKeyboardChar (uint8 *scanCode);
uint8 GetShiftFlags ();
int GetString (char *buffer, size_t bufferSize);
void InitVideoMode ();
bool IsKeyboardCharAvailable ();
bool IsPrintable (char c);
bool IsDigit (char c);
void Print (const char *str);
void Print (uint32 number);
void Print (const uint64 &number);
void PrintBackspace ();
void PrintChar (char c);
void PrintCharAtCursor (char c);
void PrintEndl ();
void PrintEndl (int cnt);
void PrintRepeatedChar (char c, int n);
void PrintError (const char *message);
void PrintErrorNoEndl (const char *message);
void PrintHex (uint8 b);
void PrintHex (uint16 data);
void PrintHex (uint32 data);
void PrintHex (const uint64 &data);

#endif // TC_HEADER_Boot_BootConsoleIo
