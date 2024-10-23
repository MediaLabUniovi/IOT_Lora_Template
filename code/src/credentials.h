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
    static const u1_t PROGMEM APPEUI[8]  = {};  // INTRODUCIR EN LSB

    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    static const u1_t PROGMEM DEVEUI[8]  = {};  // INTRODUCIR EN LSB

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = {};  // INTRODUCIR EN MSB

#endif
