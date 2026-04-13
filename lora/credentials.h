/* ***********************************************************************************************************************************************************
Credentials file
*********************************************************************************************************************************************************** */
#pragma once

#define USE_OTAA

#ifdef USE_OTAA

  static const u1_t PROGMEM APPEUI[8]  = {
    0xBE, 0x83, 0xC0, 0x0B,
    0x6B, 0x7B, 0x5B, 0x5E
  };  // LSB

  static const u1_t PROGMEM DEVEUI[8]  = {
    0x4A, 0x9D, 0xAA, 0x08,
    0xF6, 0x6E, 0xAA, 0x58
  };  // LSB

  static const u1_t PROGMEM APPKEY[16] = {
    0x36, 0xDD, 0xFB, 0xB1, 0xCA, 0x53, 0x82, 0x0A,
    0x00, 0xE5, 0x81, 0x64, 0x1A, 0x04, 0xF4, 0xBE
  };  // MSB

#endif
