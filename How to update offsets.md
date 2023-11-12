# How to update offsets

This is a guide on how to update the offsets for `rPrint` (for the people who don't know how to do it)

**I will record me changing the offsets later,
but for now,
this'll do.**
**Please follow this as it's written,
I can't guarantee that you'll
get the real print address if you miss 1 or 5 steps**

## Requirements
IDA (for disassembling the dump)
and PETools (for dumping fluster)

## Steps
- Open Fluster
- Get into a game (I recommend `a literal baseplate`.)
- Open PETools
- Wait for PETools to load
- Dump Roblox using PETools
- Remember where you stored the dump,
   as we'll need that dump for later when
   we disassemble Fluster with IDA.
- Open IDA
- Wait for IDA to load
- Crack open the dumped executable in IDA
- Rebase the program to `0x400000`.
- Wait for IDA to analyze it
- Open the strings view.
- Search for "`Invalid State passed to SetStateEnabled.`"
- Click the first option and Hit <kbd>X</kbd> on the keyboard.
- Select the first option (if not selected) and press enter.
- The disassembly should look something like this:
```asm
  push    offset aInvalidStatePa_0 ; "Invalid state passed to SetStateEnabled"...
  push    3
  call    sub_<OFFSET> ; <OFFSET> is a hexadecimal number.
  add     esp, 8
```
- Find the first `call` instruction.
- The first argument/parameter/whatever should start with `sub_`
- after "`sub_`", copy the hexadecimal numbers after the `sub_`
- You should have a hexidecimal number in your clipboard
  (e.g. `129D4A0`)
- Now, go into [offsets.h](./offsets.h) and
  change `rPrint` to its new address.
- before update example:
```cpp
#pragma once
#ifndef _OFFSETS_H
#define _OFFSETS_H

namespace Offsets {
	int rPrint = 0x129D4A0;
}

#endif
```
- after update example:
```cpp
#pragma once
#ifndef _OFFSETS_H
#define _OFFSETS_H

namespace Offsets {
	int rPrint = 0xAE85; // example offset; THIS IS NOT THE OFFSET OF PRINT.
}

#endif
```
