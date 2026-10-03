# Third-party notices

The ZeroKeyUSB firmware binaries and web tools in this repository include or
load the third-party components listed below. Each one remains under its own
license; the ZeroKeyUSB licenses described in [LICENSE](LICENSE) do not apply
to them and do not restrict the rights those licenses give you.

## Firmware (ZeroKeyOS)

| Component | Copyright | License |
|---|---|---|
| Arduino SAMD core (`cores/arduino`, variant `arduino_zero`) | Arduino LLC and contributors | LGPL-2.1-or-later |
| Arduino Wire and SPI libraries | Arduino LLC | LGPL-2.1-or-later |
| Arduino HID library | Arduino LLC; original code Peter Barrett | Permissive license (see source header) |
| Arduino Keyboard library | Arduino LLC; original code Peter Barrett | LGPL-3.0 |
| Adafruit GFX Library | Adafruit Industries | BSD License |
| Adafruit SSD1306 | Adafruit Industries | BSD License |
| Adafruit BusIO | Adafruit Industries | MIT |
| uBitcoin | Stepan Snigirev | MIT |
| trezor-crypto (bundled in uBitcoin) | Tomas Dzetkulic, Pavol Rusnak | MIT |
| SHA-2 (bundled in uBitcoin) | Aaron D. Gifford | BSD-3-Clause |
| SHA-3 (bundled in uBitcoin) | Aleksey Kravchenko | MIT |
| RIPEMD-160 (bundled in uBitcoin) | ARM Limited | Apache-2.0 |
| Bech32 / segwit_addr (bundled in uBitcoin) | Pieter Wuille | MIT |
| AES implementation (AESLib) | Brian Gladman | Gladman permissive license (see below) |
| Base64 (AESLib) | Adam Rudd | MIT |
| CMSIS | ARM Limited; Atmel / Microchip | See source headers |

### Notes on the LGPL components

The Arduino core, Wire, SPI and Keyboard libraries are licensed under the GNU
Lesser General Public License. Their source code is available from Arduino
(https://github.com/arduino/ArduinoCore-samd and
https://github.com/arduino-libraries/Keyboard). You may modify those libraries
and relink them with the rest of the firmware, as the LGPL allows.

### Brian Gladman AES license terms

The AES implementation carries the following notice, which must accompany
binary distributions:

    Copyright (c) 1998-2008, Brian Gladman, Worcester, UK. All rights reserved.

    LICENSE TERMS

    The redistribution and use of this software (with or without changes)
    is allowed without the payment of fees or royalties provided that:

     1. source code distributions include the above copyright notice, this
        list of conditions and the following disclaimer;

     2. binary distributions include the above copyright notice, this list
        of conditions and the following disclaimer in their documentation;

     3. the name of the copyright holder is not used to endorse products
        built using this software without specific written permission.

    DISCLAIMER

    This software is provided 'as is' with no explicit or implied warranties
    in respect of its properties, including, but not limited to, correctness
    and/or fitness for purpose.

## Web tools

| Component | Copyright | License |
|---|---|---|
| Bootstrap | The Bootstrap Authors | MIT |
