#include <iostream>
#include <ctime>
#include <string>
#include <stdio.h>
#include <vector>
#include <bitset>
#include <cstdint>
#include <thread>
#include <chrono>
using namespace std;
const uint8_t ascii_niz[] =                        // Pro�irena ASCII tabela, znak se sastoji iz 8 bita
{
  0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xFF
    ,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0
    ,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF
    ,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xFF
    ,0x0C,0x18,0x30,0x7E,0x0C,0x18,0x30,0x00
    ,0xFF,0xC3,0xE7,0xDB,0xDB,0xE7,0xC3,0xFF
    ,0x00,0x01,0x03,0x06,0xCC,0x78,0x30,0x00
    ,0x3C,0x66,0xC3,0xC3,0xFF,0x24,0xE7,0x00
    ,0x00,0x00,0x30,0x60,0xFF,0x60,0x30,0x00
    ,0x00,0x00,0x0C,0x06,0xFF,0x06,0x0C,0x00
    ,0x18,0x18,0x18,0x18,0xDB,0x7E,0x3C,0x18
    ,0x18,0x3C,0x7E,0xDB,0x18,0x18,0x18,0x18
    ,0x18,0x5A,0x3C,0x99,0xDB,0x7E,0x3C,0x18
    ,0x00,0x03,0x33,0x63,0xFE,0x60,0x30,0x00
    ,0x3C,0x66,0xFF,0xDB,0xDB,0xFF,0x66,0x3C
    ,0x3C,0x66,0xC3,0xDB,0xDB,0xC3,0x66,0x3C
    ,0xFF,0xC3,0xC3,0xFF,0xC3,0xC3,0xC3,0xFF
    ,0x3C,0x7E,0xDB,0xDB,0xDF,0xC3,0x66,0x3C
    ,0x3C,0x66,0xC3,0xDF,0xDB,0xDB,0x7E,0x3C
    ,0x3C,0x66,0xC3,0xFB,0xDB,0xDB,0x7E,0x3C
    ,0x3C,0x7E,0xDB,0xDB,0xFB,0xC3,0x66,0x3C
    ,0x00,0x01,0x33,0x1E,0xCE,0x7B,0x31,0x00
    ,0x7E,0x66,0x66,0x66,0x66,0x66,0x66,0xE7
    ,0x03,0x03,0x03,0xFF,0x03,0x03,0x03,0x00
    ,0xFF,0x66,0x3C,0x18,0x18,0x3C,0x66,0xFF
    ,0x18,0x18,0x3C,0x3C,0x3C,0x3C,0x18,0x18
    ,0x3C,0x66,0x66,0x30,0x18,0x00,0x18,0x00
    ,0x3C,0x66,0xC3,0xFF,0xC3,0xC3,0x66,0x3C
    ,0xFF,0xDB,0xDB,0xDB,0xFB,0xC3,0xC3,0xFF
    ,0xFF,0xC3,0xC3,0xFB,0xDB,0xDB,0xDB,0xFF
    ,0xFF,0xC3,0xC3,0xDF,0xDB,0xDB,0xDB,0xFF
    ,0xFF,0xDB,0xDB,0xDB,0xDF,0xC3,0xC3,0xFF
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00
    ,0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00
    ,0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00
    ,0x18,0x3E,0x58,0x3C,0x1A,0x7C,0x18,0x00
    ,0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00
    ,0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00
    ,0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00
    ,0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00
    ,0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00
    ,0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00
    ,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30
    ,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00
    ,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00
    ,0x7C,0xC6,0xCE,0xD6,0xE6,0xC6,0x7C,0x00
    ,0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00
    ,0x3C,0x66,0x06,0x3C,0x60,0x66,0x7E,0x00
    ,0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00
    ,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00
    ,0x7E,0x62,0x60,0x7C,0x06,0x66,0x3C,0x00
    ,0x3C,0x66,0x60,0x7C,0x66,0x66,0x3C,0x00
    ,0x7E,0x66,0x06,0x0C,0x18,0x18,0x18,0x00
    ,0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00
    ,0x3C,0x66,0x66,0x3E,0x06,0x66,0x3C,0x00
    ,0x00,0x00,0x18,0x18,0x00,0x18,0x18,0x00
    ,0x00,0x00,0x18,0x18,0x00,0x18,0x18,0x30
    ,0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00
    ,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00
    ,0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00
    ,0x3C,0x66,0x66,0x0C,0x18,0x00,0x18,0x00
    ,0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x7C,0x00
    ,0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x00
    ,0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00
    ,0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00
    ,0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00
    ,0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00
    ,0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00
    ,0x3C,0x66,0xC0,0xC0,0xCE,0x66,0x3E,0x00
    ,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00
    ,0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00
    ,0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00
    ,0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00
    ,0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00
    ,0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00
    ,0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00
    ,0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00
    ,0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00
    ,0x38,0x6C,0xC6,0xC6,0xDA,0xCC,0x76,0x00
    ,0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00
    ,0x3C,0x66,0x60,0x3C,0x06,0x66,0x3C,0x00
    ,0x7E,0x5A,0x18,0x18,0x18,0x18,0x3C,0x00
    ,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00
    ,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00
    ,0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00
    ,0xC6,0x6C,0x38,0x38,0x6C,0xC6,0xC6,0x00
    ,0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00
    ,0xFE,0xC6,0x8C,0x18,0x32,0x66,0xFE,0x00
    ,0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00
    ,0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00
    ,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00
    ,0x18,0x3C,0x7E,0x18,0x18,0x18,0x18,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
    ,0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00
    ,0xE0,0x60,0x7C,0x66,0x66,0x66,0xDC,0x00
    ,0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00
    ,0x1C,0x0C,0x7C,0xCC,0xCC,0xCC,0x76,0x00
    ,0x00,0x00,0x3C,0x66,0x7E,0x60,0x3C,0x00
    ,0x1C,0x36,0x30,0x78,0x30,0x30,0x78,0x00
    ,0x00,0x00,0x3E,0x66,0x66,0x3E,0x06,0x7C
    ,0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00
    ,0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00
    ,0x06,0x00,0x0E,0x06,0x06,0x66,0x66,0x3C
    ,0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00
    ,0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00
    ,0x00,0x00,0x6C,0xFE,0xD6,0xD6,0xC6,0x00
    ,0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00
    ,0x00,0x00,0x3C,0x66,0x66,0x66,0x3C,0x00
    ,0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0
    ,0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E
    ,0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00
    ,0x00,0x00,0x3C,0x60,0x3C,0x06,0x7C,0x00
    ,0x30,0x30,0x7C,0x30,0x30,0x36,0x1C,0x00
    ,0x00,0x00,0x66,0x66,0x66,0x66,0x3E,0x00
    ,0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00
    ,0x00,0x00,0xC6,0xD6,0xD6,0xFE,0x6C,0x00
    ,0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00
    ,0x00,0x00,0x66,0x66,0x66,0x3E,0x06,0x7C
    ,0x00,0x00,0x7E,0x4C,0x18,0x32,0x7E,0x00
    ,0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00
    ,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00
    ,0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00
    ,0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00
    ,0xCC,0x33,0xCC,0x33,0xCC,0x33,0xCC,0x33
    ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    ,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00
    ,0x0F,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00
    ,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0
    ,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0
    ,0x0F,0x0F,0x0F,0x0F,0xF0,0xF0,0xF0,0xF0
    ,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0
    ,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F
    ,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F
    ,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F
    ,0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x0F
    ,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF
    ,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF
    ,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF
    ,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
    ,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00
    ,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x1F,0x1F,0x00,0x00,0x00
    ,0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18
    ,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18
    ,0x00,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18
    ,0x18,0x18,0x18,0x1F,0x1F,0x18,0x18,0x18
    ,0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00
    ,0x18,0x18,0x18,0xF8,0xF0,0x00,0x00,0x00
    ,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00
    ,0x18,0x18,0x18,0xFF,0xFF,0x00,0x00,0x00
    ,0x00,0x00,0x00,0xF0,0xF8,0x18,0x18,0x18
    ,0x18,0x18,0x18,0xF8,0xF8,0x18,0x18,0x18
    ,0x00,0x00,0x00,0xFF,0xFF,0x18,0x18,0x18
    ,0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18
    ,0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00
    ,0x0C,0x18,0x30,0x00,0x00,0x00,0x00,0x00
    ,0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x3C,0x66,0x60,0xF8,0x60,0x66,0xFE,0x00
    ,0x38,0x44,0xBA,0xA2,0xBA,0x44,0x38,0x00
    ,0x7E,0xF4,0xF4,0x74,0x34,0x34,0x34,0x00
    ,0x1E,0x30,0x38,0x6C,0x38,0x18,0xF0,0x00
    ,0x18,0x18,0x0C,0x00,0x00,0x00,0x00,0x00
    ,0x40,0xC0,0x44,0x4C,0x54,0x1E,0x04,0x00
    ,0x40,0xC0,0x4C,0x52,0x44,0x08,0x1E,0x00
    ,0xE0,0x10,0x62,0x16,0xEA,0x0F,0x02,0x00
    ,0x00,0x18,0x18,0x7E,0x18,0x18,0x7E,0x00
    ,0x18,0x18,0x00,0x7E,0x00,0x18,0x18,0x00
    ,0x00,0x00,0x00,0x7E,0x06,0x06,0x00,0x00
    ,0x18,0x00,0x18,0x30,0x66,0x66,0x3C,0x00
    ,0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x00
    ,0x00,0x00,0x73,0xDE,0xCC,0xDE,0x73,0x00
    ,0x7C,0xC6,0xC6,0xFC,0xC6,0xC6,0xF8,0xC0
    ,0x00,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00
    ,0x3C,0x60,0x60,0x3C,0x66,0x66,0x3C,0x00
    ,0x00,0x00,0x1E,0x30,0x7C,0x30,0x1E,0x00
    ,0x38,0x6C,0xC6,0xFE,0xC6,0x6C,0x38,0x00
    ,0x00,0xC0,0x60,0x30,0x38,0x6C,0xC6,0x00
    ,0x00,0x00,0x66,0x66,0x66,0x7C,0x60,0x60
    ,0x00,0x00,0x00,0xFE,0x6C,0x6C,0x6C,0x00
    ,0x00,0x00,0x00,0x7E,0xD8,0xD8,0x70,0x00
    ,0x03,0x06,0x0C,0x3C,0x66,0x3C,0x60,0xC0
    ,0x03,0x06,0x0C,0x66,0x66,0x3C,0x60,0xC0
    ,0x00,0xE6,0x3C,0x18,0x38,0x6C,0xC7,0x00
    ,0x00,0x00,0x66,0xC3,0xDB,0xDB,0x7E,0x00
    ,0xFE,0xC6,0x60,0x30,0x60,0xC6,0xFE,0x00
    ,0x00,0x7C,0xC6,0xC6,0xC6,0x6C,0xEE,0x00
    ,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,0x00
    ,0x18,0x0C,0x06,0x03,0x01,0x00,0x00,0x00
    ,0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x18
    ,0x00,0x00,0x00,0x80,0xC0,0x60,0x30,0x18
    ,0x18,0x3C,0x66,0xC3,0x81,0x00,0x00,0x00
    ,0x18,0x0C,0x06,0x03,0x03,0x06,0x0C,0x18
    ,0x00,0x00,0x00,0x81,0xC3,0x66,0x3C,0x18
    ,0x18,0x30,0x60,0xC0,0xC0,0x60,0x30,0x18
    ,0x18,0x30,0x60,0xC1,0x83,0x06,0x0C,0x18
    ,0x18,0x0C,0x06,0x83,0xC1,0x60,0x30,0x18
    ,0x18,0x3C,0x66,0xC3,0xC3,0x66,0x3C,0x18
    ,0xC3,0xE7,0x7E,0x3C,0x3C,0x7E,0xE7,0xC3
    ,0x03,0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC0
    ,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03
    ,0xCC,0xCC,0x33,0x33,0xCC,0xCC,0x33,0x33
    ,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55
    ,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00
    ,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
    ,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF
    ,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0
    ,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80
    ,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01
    ,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF
    ,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF
    ,0xAA,0x55,0xAA,0x55,0x00,0x00,0x00,0x00
    ,0x0A,0x05,0x0A,0x05,0x0A,0x05,0x0A,0x05
    ,0x00,0x00,0x00,0x00,0xAA,0x55,0xAA,0x55
    ,0xA0,0x50,0xA0,0x50,0xA0,0x50,0xA0,0x50
    ,0xAA,0x54,0xA8,0x50,0xA0,0x40,0x80,0x00
    ,0xAA,0x55,0x2A,0x15,0x0A,0x05,0x02,0x01
    ,0x01,0x02,0x05,0x0A,0x15,0x2A,0x55,0xAA
    ,0x00,0x80,0x40,0xA0,0x50,0xA8,0x54,0xAA
    ,0x7E,0xFF,0x99,0xFF,0xBD,0xC3,0xFF,0x7E
    ,0x7E,0xFF,0x99,0xFF,0xC3,0xBD,0xFF,0x7E
    ,0x38,0x38,0xFE,0xFE,0xFE,0x10,0x38,0x00
    ,0x10,0x38,0x7C,0xFE,0x7C,0x38,0x10,0x00
    ,0x6C,0xFE,0xFE,0xFE,0x7C,0x38,0x10,0x00
    ,0x10,0x38,0x7C,0xFE,0xFE,0x10,0x38,0x00
    ,0x00,0x3C,0x66,0xC3,0xC3,0x66,0x3C,0x00
    ,0x00,0x3C,0x7E,0xFF,0xFF,0x7E,0x3C,0x00
    ,0x00,0x7E,0x66,0x66,0x66,0x66,0x7E,0x00
    ,0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00
    ,0x0F,0x07,0x0D,0x78,0xCC,0xCC,0xCC,0x78
    ,0x3C,0x66,0x66,0x66,0x3C,0x18,0x7E,0x18
    ,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x7C,0x38
    ,0x18,0x1C,0x1E,0x1B,0x18,0x78,0xF8,0x70
    ,0x99,0x5A,0x24,0xC3,0xC3,0x24,0x5A,0x99
    ,0x10,0x38,0x38,0x38,0x38,0x38,0x7C,0xD6
    ,0x18,0x3C,0x7E,0xFF,0x18,0x18,0x18,0x18
    ,0x18,0x18,0x18,0x18,0xFF,0x7E,0x3C,0x18
    ,0x10,0x30,0x70,0xFF,0xFF,0x70,0x30,0x10
    ,0x08,0x0C,0x0E,0xFF,0xFF,0x0E,0x0C,0x08
    ,0x00,0x00,0x18,0x3C,0x7E,0xFF,0xFF,0x00
    ,0x00,0x00,0xFF,0xFF,0x7E,0x3C,0x18,0x00
    ,0x80,0xE0,0xF8,0xFE,0xF8,0xE0,0x80,0x00
    ,0x02,0x0E,0x3E,0xFE,0x3E,0x0E,0x02,0x00
    ,0x38,0x38,0x92,0x7C,0x10,0x28,0x28,0x28
    ,0x38,0x38,0x10,0xFE,0x10,0x28,0x44,0x82
    ,0x38,0x38,0x12,0x7C,0x90,0x28,0x24,0x22
    ,0x38,0x38,0x90,0x7C,0x12,0x28,0x48,0x88
    ,0x00,0x3C,0x18,0x3C,0x3C,0x3C,0x18,0x00
    ,0x3C,0xFF,0xFF,0x18,0x0C,0x18,0x30,0x18
    ,0x18,0x3C,0x7E,0x18,0x18,0x7E,0x3C,0x18
    ,0x00,0x24,0x66,0xFF,0x66,0x24,0x00,0x00
};

char diodaOn = 'I';
char diodaOff = ' ';
void prikaziVektor(vector<uint8_t>&v4,vector<uint8_t>&v3,vector<uint8_t>&v2,vector<uint8_t>&v1,vector<uint8_t>&v0, int redni_broj_uredjaja)
{
                    cout <<"     5       4         3       2        1" << endl;

            for(int i = 1; i <= 8; i++)
            {
                int j = i - 1;
                bitset<8> x4(v4[j]);
                bitset<8> x3(v3[j]);
                bitset<8> x2(v2[j]);
                bitset<8> x1(v1[j]);
                bitset<8> x0(v0[j]);
                string s4 = x4.to_string();
                string s3 = x3.to_string();
                string s2 = x2.to_string();
                string s1 = x1.to_string();
                string s0 = x0.to_string();
                cout << "|";
                for(int k = 0; k < s4.length(); k++)
                {
                    if(s4[k] == '1')
                        cout << diodaOn;
                    else
                    cout << diodaOff;
                }
                cout << "|";
                for(int k = 0; k < s3.length(); k++)
                {
                    if(s3[k] == '1')
                        cout << diodaOn;
                    else
                    cout << diodaOff;
                }
                cout << "|";
                for(int k = 0; k < s2.length(); k++)
                {
                    if(s2[k] == '1')
                        cout << diodaOn;
                    else
                    cout << diodaOff;
                }
                cout << "|";
                for(int k = 0; k < s1.length(); k++)
                {
                    if(s1[k] == '1')
                        cout << diodaOn;
                    else
                    cout << diodaOff;
                }
                cout << "|";
                for(int k = 0; k < s0.length(); k++)
                {
                    if(s0[k] == '1')
                        cout << diodaOn;
                    else
                    cout << diodaOff;
                }
                cout << "|";

                cout << endl;
            }
}
void pomocnaShift(int shift_poz, int& vrijednost, bool prviDisplej)
{
            if(prviDisplej)
            {
                int maska0 = 0xFF << (7 - shift_poz);
                vrijednost = vrijednost & maska0;            // AND-ovanjem vrijednosti znaka i maske, dobijamo bit kojeg shiftamo
                vrijednost = vrijednost >> (7 - shift_poz); // posto je na suprotnom dijelu niza, potrebno je shiftati
            }
            else
            {
                int maska1 = 0xFF << 7;
                vrijednost = vrijednost & maska1;
                vrijednost = vrijednost >> 7;
            }
            vrijednost = vrijednost & 1;                // AND-ovanjem sa 1, osiguravamo da je nova vrijednost jedino taj bit kojeg prenosimo
}
 void popuniSveVektore(vector<uint8_t>&v4, vector<uint8_t>&v3,vector<uint8_t>&v2,vector<uint8_t>&v1,vector<uint8_t>&v0, int shift_poz, char znak)
        {
                                        // Maska nam sluzi da bi odredili koji bit iz niza kojeg citamo, �iftamo u red displeja
                                            // pri tome je obrnut raspored MSB i LSB kod pojedinih displeja
        for(int i=0;i<8;i++)            // Punimo sve redove odgovarajucim podacima
        {
                int vrijednost4=ascii_niz[znak*8+i]; // vrijednost reda krajnjeg displeja ocitavamo iz unosa korisnika
                int vrijednost3=v4[i];               // dok ostali displeji kupe vrijednost iz njima susjednog displeja
                int vrijednost2=v3[i];
                int vrijednost1=v2[i];
                int vrijednost0=v1[i];

                pomocnaShift(shift_poz,vrijednost4,true);
                pomocnaShift(shift_poz,vrijednost3,false);
                pomocnaShift(shift_poz,vrijednost2,false);
                pomocnaShift(shift_poz,vrijednost1,false);
                pomocnaShift(shift_poz,vrijednost0,false);

                v4[i] = v4[i] << 1;
                v3[i] = v3[i] << 1;
                v2[i] = v2[i] << 1;
                v1[i] = v1[i] << 1;
                v0[i] = v0[i] << 1;

                v4[i] = v4[i] | vrijednost4;
                v3[i] = v3[i] | vrijednost3;
                v2[i] = v2[i] | vrijednost2;
                v1[i] = v1[i] | vrijednost1;
                v0[i] = v0[i] | vrijednost0;
    }
}
 void prikaziStringScroll(const string& s)
{
            // Koristit �emo vectore kao kontenjersku klasu, koji �e �uvati trenutne vrijednosti za redove na displejima
            vector<uint8_t> displej0;
            vector<uint8_t> displej1;
            vector<uint8_t> displej2;
            vector<uint8_t> displej3;
            vector<uint8_t> displej4;

            // Na po�etku displeji su uga�eni
            for(int i = 0; i < 8; i++)
            {
                displej0.push_back(0);
                displej1.push_back(0);
                displej2.push_back(0);
                displej3.push_back(0);
                displej4.push_back(0);

            }
            prikaziVektor(displej4,displej3,displej2,displej1,displej0, 0);
            for(int i = 0; i < s.length(); i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    popuniSveVektore(displej4, displej3,displej2,displej1,displej0,j,s[i]); // j �e nam sluziti kao kursor na poziciju bita kojeg
                                                                                           // pomjeramo ulijevo
                    if(j==8) // Provjeriti moze li i bez ovog if-a
                        popuniSveVektore(displej4,displej3,displej2,displej1,displej0,7,' ');
                    prikaziVektor(displej0,displej1,displej2,displej3,displej4, 0);
                    this_thread::sleep_for(chrono::milliseconds(300));
                    cout << endl;
                }
            }
}
int main()
{
    cout << "unesite string : ";
    string s;
    getline(cin, s);
    for(int i = 0; i < 4; i++)
        s.push_back(' ');
  while(1)
  {
    prikaziStringScroll(s);
  }
}