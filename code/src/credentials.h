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
    static const u1_t PROGMEM APPEUI[8]  = {0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};  // INTRODUCIR EN LSB

    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    static const u1_t PROGMEM DEVEUI[8]  = {0xC4, 0xB4, 0x06, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};  // INTRODUCIR EN LSB

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = {0x73, 0x0A, 0x75, 0x4C, 0xB2, 0xCD, 0xE6, 0xE5, 0xBA, 0x54, 0x6A, 0x9E, 0x74, 0xD5, 0x81, 0x17};  // INTRODUCIR EN MSB

#endif
