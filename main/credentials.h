/* ***********************************************************************************************************************************************************
Credentials file
*********************************************************************************************************************************************************** */

#pragma once

#define USE_OTAA

#ifdef USE_OTAA

    // This EUI must be in little-endian format, so least-significant-byte
    // first. When copying an EUI from ttnctl output, this means to reverse
    // the bytes. For TTN issued EUIs the last bytes should be 0x00, 0x00,
    // 0x00.
    static const u1_t PROGMEM APPEUI[8]  = { 0x88, 0x99, 0x99, 0x11, 0x66, 0x00, 0x55, 0x00 };  // INTRODUCIR EN LSB

    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    static const u1_t PROGMEM DEVEUI[8]  = { 0x41, 0x29, 0x06, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };  // INTRODUCIR EN LSB

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = { 0x0C, 0x80, 0x56, 0x82, 0xEF, 0xC9, 0x8E, 0x9F, 0x1B, 0x18, 0x85, 0xA4, 0xBD, 0x28, 0x54, 0xA7 };  // INTRODUCIR EN MSB

#endif
