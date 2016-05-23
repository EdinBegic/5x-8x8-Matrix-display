#ifndef MAX7219_H
#define MAX7219_H
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>

//Koristeći datasheet za max7219 driver, možemo definisati njegove registre

#define NO_OP_REG           0x00    // Registar koji se koristi kada je više displeja kaskadno povezano, to nije slucaj kod nas (5 odvojenih CS signala)
#define DIGIT_0_REG         0x01    // Registar koji kontroliše paljenje dioda u prvom redu 
#define DIGIT_1_REG         0x02    // Registar koji kontroliše paljenje dioda u drugom redu
#define DIGIT_2_REG         0x03    // Registar koji kontroliše paljenje dioda u trećem redu
#define DIGIT_3_REG         0x04    // Registar koji kontroliše paljenje dioda u četvrtom redu
#define DIGIT_4_REG         0x05    // Registar koji kontroliše paljenje dioda u petom redu
#define DIGIT_5_REG         0x06    // Registar koji kontroliše paljenje dioda u šestom redu
#define DIGIT_6_REG         0x07    // Registar koji kontroliše paljenje dioda u sedmom redu
#define DIGIT_7_REG         0x08    // Registar koji kontroliše paljenje dioda u osmom redu
#define DECODE_MODE_REG     0x09    // Upisom u ovaj registar mozemo direktno ispisati vrijednost na cijelom displeju, ne koristimo u našem slučaju
#define INTENSITY_MODE_REG  0x0A    // Registar koji kontroliše jačinu osvjetljenja dioda
#define SCAN_LIMIT_REG      0x0B    // Registar koji kontroliše koliko je dozvoljeno da dioda bude u isto vrijeme upaljeno, mi ćemo postaviti na svih 8 
#define SHUTDOWN_REG        0x0C    // Registar koji reguliše da li je displej upaljen ili ugašen (tj. reguliše propusnost napona)
#define DISPLAY_TEST_REG    0x0F    // Registar koji ima dva stanja, Normal mode i Display test mode, čijim aktiviranjem se sve diode pale pri najvećem osvjetljenju

// Pošto  Serial Interface radi na frekvenciji od 10Mhz mozemo istu definisati također kao konstantu
#define frekvencija  10000000

const uint8_t ascii_niz[] =                        // Proširena ASCII tabela, znak se sastoji iz 8 bita
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00
   0x7E, 0x81, 0x95, 0xB1, 0xB1, 0x95, 0x81, 0x7E, // 0x01
   0x7E, 0xFF, 0xEB, 0xCF, 0xCF, 0xEB, 0xFF, 0x7E, // 0x02
   0x0E, 0x1F, 0x3F, 0x7E, 0x3F, 0x1F, 0x0E, 0x00, // 0x03
   0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00, // 0x04
   0x18, 0xBA, 0xFF, 0xFF, 0xFF, 0xBA, 0x18, 0x00, // 0x05
   0x10, 0xB8, 0xFC, 0xFF, 0xFC, 0xB8, 0x10, 0x00, // 0x06
   0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00, // 0x07
   0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF, // 0x08
   0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00, // 0x09
   0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF, // 0x0A
   0x70, 0xF8, 0x88, 0x88, 0xFD, 0x7F, 0x07, 0x0F, // 0x0B
   0x00, 0x4E, 0x5F, 0xF1, 0xF1, 0x5F, 0x4E, 0x00, // 0x0C
   0xC0, 0xE0, 0xFF, 0x7F, 0x05, 0x05, 0x07, 0x07, // 0x0D
   0xC0, 0xFF, 0x7F, 0x05, 0x05, 0x65, 0x7F, 0x3F, // 0x0E
   0x99, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x99, // 0x0F
   0x7F, 0x3E, 0x3E, 0x1C, 0x1C, 0x08, 0x08, 0x00, // 0x10
   0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x00, // 0x11
   0x00, 0x24, 0x66, 0xFF, 0xFF, 0x66, 0x24, 0x00, // 0x12
   0x00, 0x5F, 0x5F, 0x00, 0x00, 0x5F, 0x5F, 0x00, // 0x13
   0x06, 0x0F, 0x09, 0x7F, 0x7F, 0x01, 0x7F, 0x7F, // 0x14
   0x40, 0xDA, 0xBF, 0xA5, 0xFD, 0x59, 0x03, 0x02, // 0x15
   0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00, // 0x16
   0x80, 0x94, 0xB6, 0xFF, 0xFF, 0xB6, 0x94, 0x80, // 0x17
   0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00, // 0x18
   0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00, // 0x19
   0x08, 0x08, 0x08, 0x2A, 0x3E, 0x1C, 0x08, 0x00, // 0x1A
   0x08, 0x1C, 0x3E, 0x2A, 0x08, 0x08, 0x08, 0x00, // 0x1B
   0x3C, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, // 0x1C
   0x08, 0x1C, 0x3E, 0x08, 0x08, 0x3E, 0x1C, 0x08, // 0x1D
   0x30, 0x38, 0x3C, 0x3E, 0x3E, 0x3C, 0x38, 0x30, // 0x1E
   0x06, 0x0E, 0x1E, 0x3E, 0x3E, 0x1E, 0x0E, 0x06, // 0x1F
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ' '
   0x00, 0x06, 0x5F, 0x5F, 0x06, 0x00, 0x00, 0x00, // '!'
   0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x00, // '"'
   0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00, // '#'
   0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, 0x00, // '$'
   0x46, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x62, 0x00, // '%'
   0x30, 0x7A, 0x4F, 0x5D, 0x37, 0x7A, 0x48, 0x00, // '&'
   0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // '''
   0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00, // '('
   0x00, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x00, // ')'
   0x08, 0x2A, 0x3E, 0x1C, 0x1C, 0x3E, 0x2A, 0x08, // '*'
   0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00, 0x00, // '+'
   0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, // ','
   0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, // '-'
   0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, // '.'
   0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, // '/'
   0x3E, 0x7F, 0x71, 0x59, 0x4D, 0x7F, 0x3E, 0x00, // '0'
   0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00, // '1'
   0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x00, // '2'
   0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00, // '3'
   0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00, // '4'
   0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, 0x00, // '5'
   0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00, 0x00, // '6'
   0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00, 0x00, // '7'
   0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00, // '8'
   0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00, 0x00, // '9'
   0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, // ':'
   0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00, 0x00, // ';'
   0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x00, // '<'
   0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00, // '='
   0x00, 0x41, 0x63, 0x36, 0x1C, 0x08, 0x00, 0x00, // '>'
   0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00, 0x00, // '?'
   0x3E, 0x7F, 0x41, 0x5D, 0x5D, 0x1F, 0x1E, 0x00, // '@'
   0x7C, 0x7E, 0x13, 0x13, 0x7E, 0x7C, 0x00, 0x00, // 'A'
   0x41, 0x7F, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, // 'B'
   0x1C, 0x3E, 0x63, 0x41, 0x41, 0x63, 0x22, 0x00, // 'C'
   0x41, 0x7F, 0x7F, 0x41, 0x63, 0x3E, 0x1C, 0x00, // 'D'
   0x41, 0x7F, 0x7F, 0x49, 0x5D, 0x41, 0x63, 0x00, // 'E'
   0x41, 0x7F, 0x7F, 0x49, 0x1D, 0x01, 0x03, 0x00, // 'F'
   0x1C, 0x3E, 0x63, 0x41, 0x51, 0x73, 0x72, 0x00, // 'G'
   0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 0x00, 0x00, // 'H'
   0x00, 0x41, 0x7F, 0x7F, 0x41, 0x00, 0x00, 0x00, // 'I'
   0x30, 0x70, 0x40, 0x41, 0x7F, 0x3F, 0x01, 0x00, // 'J'
   0x41, 0x7F, 0x7F, 0x08, 0x1C, 0x77, 0x63, 0x00, // 'K'
   0x41, 0x7F, 0x7F, 0x41, 0x40, 0x60, 0x70, 0x00, // 'L'
   0x7F, 0x7F, 0x0E, 0x1C, 0x0E, 0x7F, 0x7F, 0x00, // 'M'
   0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F, 0x7F, 0x00, // 'N'
   0x1C, 0x3E, 0x63, 0x41, 0x63, 0x3E, 0x1C, 0x00, // 'O'
   0x41, 0x7F, 0x7F, 0x49, 0x09, 0x0F, 0x06, 0x00, // 'P'
   0x1E, 0x3F, 0x21, 0x71, 0x7F, 0x5E, 0x00, 0x00, // 'Q'
   0x41, 0x7F, 0x7F, 0x09, 0x19, 0x7F, 0x66, 0x00, // 'R'
   0x26, 0x6F, 0x4D, 0x59, 0x73, 0x32, 0x00, 0x00, // 'S'
   0x03, 0x41, 0x7F, 0x7F, 0x41, 0x03, 0x00, 0x00, // 'T'
   0x7F, 0x7F, 0x40, 0x40, 0x7F, 0x7F, 0x00, 0x00, // 'U'
   0x1F, 0x3F, 0x60, 0x60, 0x3F, 0x1F, 0x00, 0x00, // 'V'
   0x7F, 0x7F, 0x30, 0x18, 0x30, 0x7F, 0x7F, 0x00, // 'W'
   0x43, 0x67, 0x3C, 0x18, 0x3C, 0x67, 0x43, 0x00, // 'X'
   0x07, 0x4F, 0x78, 0x78, 0x4F, 0x07, 0x00, 0x00, // 'Y'
   0x47, 0x63, 0x71, 0x59, 0x4D, 0x67, 0x73, 0x00, // 'Z'
   0x00, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, // '['
   0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, // '\'
   0x00, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00, 0x00, // ']'
   0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00, // '^'
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // '_'
   0x00, 0x00, 0x03, 0x07, 0x04, 0x00, 0x00, 0x00, // '`'
   0x20, 0x74, 0x54, 0x54, 0x3C, 0x78, 0x40, 0x00, // 'a'
   0x41, 0x7F, 0x3F, 0x48, 0x48, 0x78, 0x30, 0x00, // 'b'
   0x38, 0x7C, 0x44, 0x44, 0x6C, 0x28, 0x00, 0x00, // 'c'
   0x30, 0x78, 0x48, 0x49, 0x3F, 0x7F, 0x40, 0x00, // 'd'
   0x38, 0x7C, 0x54, 0x54, 0x5C, 0x18, 0x00, 0x00, // 'e'
   0x48, 0x7E, 0x7F, 0x49, 0x03, 0x02, 0x00, 0x00, // 'f'
   0x98, 0xBC, 0xA4, 0xA4, 0xF8, 0x7C, 0x04, 0x00, // 'g'
   0x41, 0x7F, 0x7F, 0x08, 0x04, 0x7C, 0x78, 0x00, // 'h'
   0x00, 0x44, 0x7D, 0x7D, 0x40, 0x00, 0x00, 0x00, // 'i'
   0x60, 0xE0, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x00, // 'j'
   0x41, 0x7F, 0x7F, 0x10, 0x38, 0x6C, 0x44, 0x00, // 'k'
   0x00, 0x41, 0x7F, 0x7F, 0x40, 0x00, 0x00, 0x00, // 'l'
   0x7C, 0x7C, 0x18, 0x38, 0x1C, 0x7C, 0x78, 0x00, // 'm'
   0x7C, 0x7C, 0x04, 0x04, 0x7C, 0x78, 0x00, 0x00, // 'n'
   0x38, 0x7C, 0x44, 0x44, 0x7C, 0x38, 0x00, 0x00, // 'o'
   0x84, 0xFC, 0xF8, 0xA4, 0x24, 0x3C, 0x18, 0x00, // 'p'
   0x18, 0x3C, 0x24, 0xA4, 0xF8, 0xFC, 0x84, 0x00, // 'q'
   0x44, 0x7C, 0x78, 0x4C, 0x04, 0x1C, 0x18, 0x00, // 'r'
   0x48, 0x5C, 0x54, 0x54, 0x74, 0x24, 0x00, 0x00, // 's'
   0x00, 0x04, 0x3E, 0x7F, 0x44, 0x24, 0x00, 0x00, // 't'
   0x3C, 0x7C, 0x40, 0x40, 0x3C, 0x7C, 0x40, 0x00, // 'u'
   0x1C, 0x3C, 0x60, 0x60, 0x3C, 0x1C, 0x00, 0x00, // 'v'
   0x3C, 0x7C, 0x70, 0x38, 0x70, 0x7C, 0x3C, 0x00, // 'w'
   0x44, 0x6C, 0x38, 0x10, 0x38, 0x6C, 0x44, 0x00, // 'x'
   0x9C, 0xBC, 0xA0, 0xA0, 0xFC, 0x7C, 0x00, 0x00, // 'y'
   0x4C, 0x64, 0x74, 0x5C, 0x4C, 0x64, 0x00, 0x00, // 'z'
   0x08, 0x08, 0x3E, 0x77, 0x41, 0x41, 0x00, 0x00, // ''
   0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, // '|'
   0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00, 0x00, // '}'
   0x02, 0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00, // '~'
   0x70, 0x78, 0x4C, 0x46, 0x4C, 0x78, 0x70, 0x00  // 0x7F
 /*  0x0E, 0x9F, 0x91, 0xB1, 0xFB, 0x4A, 0x00, 0x00, // 0x80
   0x3A, 0x7A, 0x40, 0x40, 0x7A, 0x7A, 0x40, 0x00, // 0x81
   0x38, 0x7C, 0x54, 0x55, 0x5D, 0x19, 0x00, 0x00, // 0x82
   0x02, 0x23, 0x75, 0x55, 0x55, 0x7D, 0x7B, 0x42, // 0x83
   0x21, 0x75, 0x54, 0x54, 0x7D, 0x79, 0x40, 0x00, // 0x84
   0x21, 0x75, 0x55, 0x54, 0x7C, 0x78, 0x40, 0x00, // 0x85
   0x20, 0x74, 0x57, 0x57, 0x7C, 0x78, 0x40, 0x00, // 0x86
   0x18, 0x3C, 0xA4, 0xA4, 0xE4, 0x40, 0x00, 0x00, // 0x87
   0x02, 0x3B, 0x7D, 0x55, 0x55, 0x5D, 0x1B, 0x02, // 0x88
   0x39, 0x7D, 0x54, 0x54, 0x5D, 0x19, 0x00, 0x00, // 0x89
   0x39, 0x7D, 0x55, 0x54, 0x5C, 0x18, 0x00, 0x00, // 0x8A
   0x01, 0x45, 0x7C, 0x7C, 0x41, 0x01, 0x00, 0x00, // 0x8B
   0x02, 0x03, 0x45, 0x7D, 0x7D, 0x43, 0x02, 0x00, // 0x8C
   0x01, 0x45, 0x7D, 0x7C, 0x40, 0x00, 0x00, 0x00, // 0x8D
   0x79, 0x7D, 0x16, 0x12, 0x16, 0x7D, 0x79, 0x00, // 0x8E
   0x70, 0x78, 0x2B, 0x2B, 0x78, 0x70, 0x00, 0x00, // 0x8F
   0x44, 0x7C, 0x7C, 0x55, 0x55, 0x45, 0x00, 0x00, // 0x90
   0x20, 0x74, 0x54, 0x54, 0x7C, 0x7C, 0x54, 0x54, // 0x91
   0x7C, 0x7E, 0x0B, 0x09, 0x7F, 0x7F, 0x49, 0x00, // 0x92
   0x32, 0x7B, 0x49, 0x49, 0x7B, 0x32, 0x00, 0x00, // 0x93
   0x32, 0x7A, 0x48, 0x48, 0x7A, 0x32, 0x00, 0x00, // 0x94
   0x32, 0x7A, 0x4A, 0x48, 0x78, 0x30, 0x00, 0x00, // 0x95
   0x3A, 0x7B, 0x41, 0x41, 0x7B, 0x7A, 0x40, 0x00, // 0x96
   0x3A, 0x7A, 0x42, 0x40, 0x78, 0x78, 0x40, 0x00, // 0x97
   0x9A, 0xBA, 0xA0, 0xA0, 0xFA, 0x7A, 0x00, 0x00, // 0x98
   0x01, 0x19, 0x3C, 0x66, 0x66, 0x3C, 0x19, 0x01, // 0x99
   0x3D, 0x7D, 0x40, 0x40, 0x7D, 0x3D, 0x00, 0x00, // 0x9A
   0x18, 0x3C, 0x24, 0xE7, 0xE7, 0x24, 0x24, 0x00, // 0x9B
   0x68, 0x7E, 0x7F, 0x49, 0x43, 0x66, 0x20, 0x00, // 0x9C
   0x2B, 0x2F, 0xFC, 0xFC, 0x2F, 0x2B, 0x00, 0x00, // 0x9D
   0xFF, 0xFF, 0x09, 0x09, 0x2F, 0xF6, 0xF8, 0xA0, // 0x9E
   0x40, 0xC0, 0x88, 0xFE, 0x7F, 0x09, 0x03, 0x02, // 0x9F
   0x20, 0x74, 0x54, 0x55, 0x7D, 0x79, 0x40, 0x00, // 0xA0
   0x00, 0x44, 0x7D, 0x7D, 0x41, 0x00, 0x00, 0x00, // 0xA1
   0x30, 0x78, 0x48, 0x4A, 0x7A, 0x32, 0x00, 0x00, // 0xA2
   0x38, 0x78, 0x40, 0x42, 0x7A, 0x7A, 0x40, 0x00, // 0xA3
   0x7A, 0x7A, 0x0A, 0x0A, 0x7A, 0x70, 0x00, 0x00, // 0xA4
   0x7D, 0x7D, 0x19, 0x31, 0x7D, 0x7D, 0x00, 0x00, // 0xA5
   0x00, 0x26, 0x2F, 0x29, 0x2F, 0x2F, 0x28, 0x00, // 0xA6
   0x00, 0x26, 0x2F, 0x29, 0x2F, 0x26, 0x00, 0x00, // 0xA7
   0x30, 0x78, 0x4D, 0x45, 0x60, 0x20, 0x00, 0x00, // 0xA8
   0x38, 0x38, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, // 0xA9
   0x08, 0x08, 0x08, 0x08, 0x38, 0x38, 0x00, 0x00, // 0xAA
   0x4F, 0x6F, 0x30, 0x18, 0xCC, 0xEE, 0xBB, 0x91, // 0xAB
   0x4F, 0x6F, 0x30, 0x18, 0x6C, 0x76, 0xFB, 0xF9, // 0xAC
   0x00, 0x00, 0x00, 0x7B, 0x7B, 0x00, 0x00, 0x00, // 0xAD
   0x08, 0x1C, 0x36, 0x22, 0x08, 0x1C, 0x36, 0x22, // 0xAE
   0x22, 0x36, 0x1C, 0x08, 0x22, 0x36, 0x1C, 0x08, // 0xAF
   0xAA, 0x00, 0x55, 0x00, 0xAA, 0x00, 0x55, 0x00, // 0xB0
   0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, // 0xB1
   0xDD, 0xFF, 0xAA, 0x77, 0xDD, 0xAA, 0xFF, 0x77, // 0xB2
   0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, // 0xB3
   0x10, 0x10, 0x10, 0xFF, 0xFF, 0x00, 0x00, 0x00, // 0xB4
   0x14, 0x14, 0x14, 0xFF, 0xFF, 0x00, 0x00, 0x00, // 0xB5
   0x10, 0x10, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, // 0xB6
   0x10, 0x10, 0xF0, 0xF0, 0x10, 0xF0, 0xF0, 0x00, // 0xB7
   0x14, 0x14, 0x14, 0xFC, 0xFC, 0x00, 0x00, 0x00, // 0xB8
   0x14, 0x14, 0xF7, 0xF7, 0x00, 0xFF, 0xFF, 0x00, // 0xB9
   0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, // 0xBA
   0x14, 0x14, 0xF4, 0xF4, 0x04, 0xFC, 0xFC, 0x00, // 0xBB
   0x14, 0x14, 0x17, 0x17, 0x10, 0x1F, 0x1F, 0x00, // 0xBC
   0x10, 0x10, 0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x00, // 0xBD
   0x14, 0x14, 0x14, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 0xBE
   0x10, 0x10, 0x10, 0xF0, 0xF0, 0x00, 0x00, 0x00, // 0xBF
   0x00, 0x00, 0x00, 0x1F, 0x1F, 0x10, 0x10, 0x10, // 0xC0
   0x10, 0x10, 0x10, 0x1F, 0x1F, 0x10, 0x10, 0x10, // 0xC1
   0x10, 0x10, 0x10, 0xF0, 0xF0, 0x10, 0x10, 0x10, // 0xC2
   0x00, 0x00, 0x00, 0xFF, 0xFF, 0x10, 0x10, 0x10, // 0xC3
   0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 0xC4
   0x10, 0x10, 0x10, 0xFF, 0xFF, 0x10, 0x10, 0x10, // 0xC5
   0x00, 0x00, 0x00, 0xFF, 0xFF, 0x14, 0x14, 0x14, // 0xC6
   0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x10, // 0xC7
   0x00, 0x00, 0x1F, 0x1F, 0x10, 0x17, 0x17, 0x14, // 0xC8
   0x00, 0x00, 0xFC, 0xFC, 0x04, 0xF4, 0xF4, 0x14, // 0xC9
   0x14, 0x14, 0x17, 0x17, 0x10, 0x17, 0x17, 0x14, // 0xCA
   0x14, 0x14, 0xF4, 0xF4, 0x04, 0xF4, 0xF4, 0x14, // 0xCB
   0x00, 0x00, 0xFF, 0xFF, 0x00, 0xF7, 0xF7, 0x14, // 0xCC
   0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // 0xCD
   0x14, 0x14, 0xF7, 0xF7, 0x00, 0xF7, 0xF7, 0x14, // 0xCE
   0x14, 0x14, 0x14, 0x17, 0x17, 0x14, 0x14, 0x14, // 0xCF
   0x10, 0x10, 0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x10, // 0xD0
   0x14, 0x14, 0x14, 0xF4, 0xF4, 0x14, 0x14, 0x14, // 0xD1
   0x10, 0x10, 0xF0, 0xF0, 0x10, 0xF0, 0xF0, 0x10, // 0xD2
   0x00, 0x00, 0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x10, // 0xD3
   0x00, 0x00, 0x00, 0x1F, 0x1F, 0x14, 0x14, 0x14, // 0xD4
   0x00, 0x00, 0x00, 0xFC, 0xFC, 0x14, 0x14, 0x14, // 0xD5
   0x00, 0x00, 0xF0, 0xF0, 0x10, 0xF0, 0xF0, 0x10, // 0xD6
   0x10, 0x10, 0xFF, 0xFF, 0x10, 0xFF, 0xFF, 0x10, // 0xD7
   0x14, 0x14, 0x14, 0xFF, 0xFF, 0x14, 0x14, 0x14, // 0xD8
   0x10, 0x10, 0x10, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 0xD9
   0x00, 0x00, 0x00, 0xF0, 0xF0, 0x10, 0x10, 0x10, // 0xDA
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0xDB
   0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, // 0xDC
   0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, // 0xDD
   0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, // 0xDE
   0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // 0xDF
   0x38, 0x7C, 0x44, 0x6C, 0x38, 0x6C, 0x44, 0x00, // 0xE0
   0xFC, 0xFE, 0x2A, 0x2A, 0x3E, 0x14, 0x00, 0x00, // 0xE1
   0x7E, 0x7E, 0x02, 0x02, 0x06, 0x06, 0x00, 0x00, // 0xE2
   0x02, 0x7E, 0x7E, 0x02, 0x7E, 0x7E, 0x02, 0x00, // 0xE3
   0x63, 0x77, 0x5D, 0x49, 0x63, 0x63, 0x00, 0x00, // 0xE4
   0x38, 0x7C, 0x44, 0x7C, 0x3C, 0x04, 0x04, 0x00, // 0xE5
   0x80, 0xFE, 0x7E, 0x20, 0x20, 0x3E, 0x1E, 0x00, // 0xE6
   0x04, 0x06, 0x02, 0x7E, 0x7C, 0x06, 0x02, 0x00, // 0xE7
   0x99, 0xBD, 0xE7, 0xE7, 0xBD, 0x99, 0x00, 0x00, // 0xE8
   0x1C, 0x3E, 0x6B, 0x49, 0x6B, 0x3E, 0x1C, 0x00, // 0xE9
   0x4C, 0x7E, 0x73, 0x01, 0x73, 0x7E, 0x4C, 0x00, // 0xEA
   0x30, 0x78, 0x4A, 0x4F, 0x7D, 0x39, 0x00, 0x00, // 0xEB
   0x18, 0x3C, 0x24, 0x3C, 0x3C, 0x24, 0x3C, 0x18, // 0xEC
   0x98, 0xFC, 0x64, 0x3C, 0x3E, 0x27, 0x3D, 0x18, // 0xED
   0x1C, 0x3E, 0x6B, 0x49, 0x49, 0x00, 0x00, 0x00, // 0xEE
   0x7E, 0x7F, 0x01, 0x01, 0x7F, 0x7E, 0x00, 0x00, // 0xEF
   0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x00, 0x00, // 0xF0
   0x44, 0x44, 0x5F, 0x5F, 0x44, 0x44, 0x00, 0x00, // 0xF1
   0x40, 0x51, 0x5B, 0x4E, 0x44, 0x40, 0x00, 0x00, // 0xF2
   0x40, 0x44, 0x4E, 0x5B, 0x51, 0x40, 0x00, 0x00, // 0xF3
   0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01, 0x07, 0x06, // 0xF4
   0x60, 0xE0, 0x80, 0xFF, 0x7F, 0x00, 0x00, 0x00, // 0xF5
   0x08, 0x08, 0x6B, 0x6B, 0x08, 0x08, 0x00, 0x00, // 0xF6
   0x24, 0x36, 0x12, 0x36, 0x24, 0x36, 0x12, 0x00, // 0xF7
   0x00, 0x06, 0x0F, 0x09, 0x0F, 0x06, 0x00, 0x00, // 0xF8
   0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, // 0xF9
   0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, // 0xFA
   0x10, 0x30, 0x70, 0xC0, 0xFF, 0xFF, 0x01, 0x01, // 0xFB
   0x00, 0x1F, 0x1F, 0x01, 0x1F, 0x1E, 0x00, 0x00, // 0xFC
   0x00, 0x19, 0x1D, 0x17, 0x12, 0x00, 0x00, 0x00, // 0xFD
   0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00, // 0xFE
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 0xFF */
};

class Max7219
{
    private:
        // Kao privatne atribute potrebno je deklarisati SPI varijablu, jer ćemo preko nje povezivati nas displej i mikrokontroler

        SPI *spi0, *spi1, *spi2, *spi3, *spi4;
        DigitalOut *cs0, *cs1, *cs2, *cs3, *cs4;// Posto koristimo 5 led matrix displeja, potrebno je i svaki od njegovih chipova deklarisati
        PinName pin_mosi, pin_miso, pin_sclk; // Iako necemo koristiti master input - slave output, potrebno ga je definisati prilikom inicijalizacije SPI pokazivaca
        PinName pin_cs0, pin_cs1, pin_cs2, pin_cs3, pin_cs4; // Isto i za chip select-e
        // Kako koristimo potenciometar potrebno je definisati i kašnjenje prilikom shiftanja karaktera
        float kasnjenjeZnakPoZnak;
        float kasnjenjeScroll;
        int osvjetljenje;
        int broj_displeja;

        void dealocirajSPI(int redni_broj)
        {
            if(redni_broj == 0)
            {
               delete spi0;
               delete cs0;
               cs0 = 0;
               spi0 = 0;            
            }

            if(redni_broj == 1)
            {
               delete spi1;
               delete cs1;
               cs1 = 0;
               spi1 = 0;
            }

            if(redni_broj == 2)
            {
               delete spi2;
               delete cs2;
               cs2 = 0;
               spi2 = 0;   
            }

            if(redni_broj == 3)
            {
               delete spi3;
               delete cs3;
               cs3 = 0;
               spi3 = 0;              
            }

            if(redni_broj == 4)
            {
               delete spi4;
               delete cs4;
               cs4 = 0;
               spi4 = 0;              
            }
         
        }
        void alocirajSPI(int redni_broj)
        {
            dealocirajSPI(redni_broj);
            if(redni_broj == 0)
            {
               spi0 = new SPI(pin_mosi, pin_miso, pin_sclk);
               cs0 = new DigitalOut(pin_cs0);
               spi0->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
               spi0->frequency(frekvencija);               
            }

            if(redni_broj == 1)
            {
               spi1 = new SPI(pin_mosi, pin_miso, pin_sclk);
               cs1 = new DigitalOut(pin_cs1);
               spi1->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
               spi1->frequency(frekvencija);               
            }

           if(redni_broj == 2)
            {
               spi2 = new SPI(pin_mosi, pin_miso, pin_sclk);
               cs2 = new DigitalOut(pin_cs2);
               spi2->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
               spi2->frequency(frekvencija);               
            }

            if(redni_broj == 3)
            {
               spi3 = new SPI(pin_mosi, pin_miso, pin_sclk);
               cs3 = new DigitalOut(pin_cs3);
               spi3->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
               spi3->frequency(frekvencija);               
            }

            if(redni_broj == 4)
            {
               spi4 = new SPI(pin_mosi, pin_miso, pin_sclk);
               cs4 = new DigitalOut(pin_cs4);
               spi4->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
               spi4->frequency(frekvencija);               
            }
        }

        void upisiURegistar(int registar, int vrijednost, int redni_broj_uredjaja)
        {
            if(redni_broj_uredjaja == 0) // Upisivanje u reigstar se vrši, tako što prvo chip select uređaja postavimo na LOW,  te kroz SPI
            {                            // u željeni registar MAX7219 upisujemo vrijednost i neposredno CS postavljamo na HIGH
                alocirajSPI(redni_broj_uredjaja);
                cs0->write(0);
                spi0->write(registar);
                spi0->write(vrijednost);
                cs0->write(1);
            }
            else if(redni_broj_uredjaja == 1)
            {
               alocirajSPI(redni_broj_uredjaja);
                cs1->write(0);
                spi1->write(registar);
                spi1->write(vrijednost);
                cs1->write(1);
            }
            else if(redni_broj_uredjaja == 2)
            {
                alocirajSPI(redni_broj_uredjaja);
                cs2->write(0);
                spi2->write(registar);
                spi2->write(vrijednost);
                cs2->write(1);
            }
            else if(redni_broj_uredjaja == 3)
            {
                alocirajSPI(redni_broj_uredjaja);
                cs3->write(0);
                spi3->write(registar);
                spi3->write(vrijednost);
                cs3->write(1);
            }
            else if(redni_broj_uredjaja == 4)
            {
                alocirajSPI(redni_broj_uredjaja);
                cs4->write(0);
                spi4->write(registar);
                spi4->write(vrijednost);
                cs4->write(1);
            }
        }

        void ocistiDisplej(int redni_broj_uredjaja)
        {
            for(int i = 1; i <= 8; i++) // Registri od 1 do 8 gase diode respektivno za redove na displeju
            {
                upisiURegistar(i,0,redni_broj_uredjaja);
            }
        }

        void ocistiDispleje()
        {
            for(int i = 0; i < broj_displeja; i++)
            {
                ocistiDisplej(i);
            }
        }

        void upisiZnakURegistre(const uint8_t* pok, int redni_broj_uredjaja)
        {
            // Nas pokazivac pokazuje na prvi red (8 bita) naseg znaka koji ce se ispisati
            // da bi cijeli znak ispisali, potrebno je pomjerati za jedno mjesto i to zapisati u odgovarajuci registar
            for(int i = 1; i <= 8; i++) 
            {
                upisiURegistar(i,*(pok++),redni_broj_uredjaja); // Moguca greska, provjeriti na labu
            }
        }

        void prikaziVektor(vector<uint8_t>&v, int redni_broj_uredjaja)
        {
            for(int i = 1; i <= 8; i++)
            {
                int j = i - 1;
                upisiURegistar(i,v[j], redni_broj_uredjaja);
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

        void popuniSveVektore(vector<uint8_t>&v4,vector<uint8_t>&v3,vector<uint8_t>&v2,vector<uint8_t>&v1,vector<uint8_t>&v0, int shift_poz, char znak)
        {
                                              // Maska nam sluzi da bi odredili koji bit iz niza kojeg citamo, šiftamo u red displeja
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
                
                v4[i] = v4[i] << 1;     // Sve podatke pomjeramo jedno mjesto u lijevo
                v3[i] = v3[i] << 1;
                v2[i] = v2[i] << 1;
                v1[i] = v1[i] << 1;
                v0[i] = v0[i] << 1;
                
                v4[i] = v4[i] | vrijednost4;    // sada unosimo vrijednost na najnizi bit, sto mozemo OR operacijom izvršiti
                v3[i] = v3[i] | vrijednost3;
                v2[i] = v2[i] | vrijednost2;
                v1[i] = v1[i] | vrijednost1;
                v0[i] = v0[i] | vrijednost0;
            }
         }
        
        void dodajIntUString(int broj, string &s)
        {
            if(broj < 10)
            {
                char cif = broj + '0';
                s.push_back('0');
                s.push_back(cif);
                return;
            }
            string pomocni;
        
            int cif1 = broj % 10;
            char cif2 = cif1 + '0';
            pomocni.push_back(cif2);
            broj /= 10;
            char cif3 = broj + '0';
            pomocni.push_back(cif3);
            for(int i = pomocni.length() - 1; i >= 0; i--)
            {
                s.push_back(pomocni[i]);
            }
        }

    public:

        Max7219(PinName Pin_mosi,PinName Pin_miso,PinName Pin_sclk,PinName Pin_cs0,PinName Pin_cs1,PinName Pin_cs2,PinName Pin_cs3,PinName Pin_cs4):spi0(0),spi1(0),spi2(0),spi3(0),spi4(0),cs0(0),cs1(0)/*,cs2(0),cs3(0),cs4(0)*/
        {
            spi0 = new SPI(Pin_mosi, Pin_miso, Pin_sclk);
            spi1 = new SPI(Pin_mosi, Pin_miso, Pin_sclk);
            spi2 = new SPI(Pin_mosi, Pin_miso, Pin_sclk);
            spi3 = new SPI(Pin_mosi, Pin_miso, Pin_sclk);
            spi4 = new SPI(Pin_mosi, Pin_miso, Pin_sclk);
            cs0 = new DigitalOut(Pin_cs0);
            cs1 = new DigitalOut(Pin_cs1);
            cs2 = new DigitalOut(Pin_cs2);
            cs3 = new DigitalOut(Pin_cs3);
            cs4 = new DigitalOut(Pin_cs4);
            //Potrebno je sada konfigurisati nas SPI
            spi0->format(8,0); // Posto je 8x8 displej, potrebno je 8 bita da se aktivira, te cemo najlakse tako slati podatke, te je mode 0
            spi0->frequency(frekvencija);
            spi1->format(8,0);
            spi1->frequency(frekvencija);
            spi2->format(8,0);
            spi2->frequency(frekvencija);
            spi3->format(8,0);
            spi3->frequency(frekvencija);
            spi4->format(8,0);
            spi4->frequency(frekvencija);
            pin_mosi = Pin_mosi;
            pin_miso = Pin_miso;
            pin_sclk = Pin_sclk;
            pin_cs0 =  Pin_cs0;
            pin_cs1 =  Pin_cs1;
            pin_cs2 =  Pin_cs2;
            pin_cs3 =  Pin_cs3;
            pin_cs4 =  Pin_cs4;
            // defaultno kasnjenje
            kasnjenjeZnakPoZnak  = 0.4;
            kasnjenjeScroll = 0.1;
            osvjetljenje = 15;
            broj_displeja = 5;
        }

        ~Max7219()
        {
            delete spi0;
            delete spi1;
            delete spi2;
            delete spi3;
            delete spi4;
            delete cs0;
            delete cs1;
            delete cs2;
            delete cs3;
            delete cs4;
            spi0=0;
            spi1=0;
            spi2=0;
            spi3=0;
            spi4=0;
            cs0=0;
            cs1=0;
            cs2=0;
            cs3=0;
            cs4=0; 
        }

        void displejInicijalizacija()
        {
            //Koristeći datasheet i ofc. dokumentaciju za ovaj driver, postepeno inicijaliziramo displej za sve uređaje
            for(int i = 0; i < broj_displeja; i++)
            {
                                                            
                upisiURegistar(DECODE_MODE_REG, 0x00,i);    // Decode mode postavljamo na nulu, jer ga necemo koristiti za ispis znakova, već
                                                            // ćemo ručno upisivati u Digit_1-Digit_8 register
                                       
                upisiURegistar(INTENSITY_MODE_REG, 0x0f,i); // Postavljamo intenzitet duty cycle-a na maksimalnu vrijednost, upisujuci u odgovarajući registar
                                                            // 0x0f predstavlja 31/32 vrijednost duty cycle-a kod MAX7219

                upisiURegistar(SCAN_LIMIT_REG,0x07,i);      // Upisivanjem vrijednosti 7 u scan_limit registar, dopuštamo paljenje dioda u svim redovima (red 0 do 7)
                upisiURegistar(SHUTDOWN_REG,0x01,i);        // Postavljamo ga u Normal Operation mode
                upisiURegistar(0xff,0,i);                   // Data registar postavljamo na nulu
                ocistiDisplej(i);                           // Upisuje u registre Digit0 - Digit7 vrijednost 0, kako bi displej bio ugasen

            }
        }

        void prikaziZnak(char c, int redni_broj_uredjaja)
        {
            // Znak potice iz  skraćene ASCII tabele, koja je 127 karaktera duga
            // prekoracenje treba zabraniti
            if(c > 127)
                return;
            const uint8_t *pok = ascii_niz + c * 8;        // Posto je ascii_niz zapravo 8x8 niz, tacnu poziciju naseg znaka, saznajemo
            upisiZnakURegistre(pok,redni_broj_uredjaja); // mnozenjem znaka sa duzinom jednog reda niza
        }
        
        void prikaziString(const string& s)
        {
            int redni_broj_uredjaja =  0;


            for(int i = 0; i < s.length(); i++)
            {
                if(redni_broj_uredjaja == broj_displeja)
                {
                    redni_broj_uredjaja = 0;
                    ocistiDispleje(); // Displeje cistimo, jer se moze desiti da se string sastoji od npr. 8 znakova, pri cemu
                }                      // bi onda dva displeja prikazivala staru vrijednost
                
                prikaziZnak(s[i],redni_broj_uredjaja++);
                if(redni_broj_uredjaja == broj_displeja) // Svi displeji prikazuju znak
                    wait(kasnjenjeZnakPoZnak);
            }
           // ocistiDispleje();
        }

        void prikaziStringScroll(string& s)
        {
            for(int i = 0; i < 4; i++)
               s.push_back(' ');
            
            // Koristit ćemo vectore kao kontenjersku klasu, koji će čuvati trenutne vrijednosti za redove na displejima
            vector<uint8_t> displej0, displej1, displej2, displej3, displej4;
            // Na početku displeji su ugašeni
            for(int i = 0; i < 8; i++)
            {
                displej0.push_back(0);
                displej1.push_back(0);
                displej2.push_back(0);
                displej3.push_back(0);
                displej4.push_back(0);
            }
            prikaziVektor(displej0, 0);
            prikaziVektor(displej1, 1);
            prikaziVektor(displej2, 2);
            prikaziVektor(displej3, 3);
            prikaziVektor(displej4, 4); 
            
            for(int i = 0; i < s.length(); i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    popuniSveVektore(displej4,displej3,displej2,displej1,displej0,j,s[i]); // j će nam sluziti kao kursor na poziciju bita kojeg
                                                                                           // pomjeramo ulijevo
                    if(j==8) // Provjeriti moze li i bez ovog if-a
                        popuniSveVektore(displej4,displej3,displej2,displej1,displej0,7,' ');
                  
                    prikaziVektor(displej4, 4);                                       
                    prikaziVektor(displej3, 3);
                    prikaziVektor(displej2, 2);
                    prikaziVektor(displej1, 1);
                    prikaziVektor(displej0, 0);
                    wait(kasnjenjeScroll);
                }
            }
        }

        void postaviKasnjenjeZnakPoZnak(float t)
        {
            kasnjenjeZnakPoZnak = t;
        }

        void postaviKasnjenjeScroll(float t)
        {
            kasnjenjeScroll = t;
        }

        void prikazVremena()
        {
            time_t vrijeme;
            struct tm * informacije_o_vremenu;
            time (&vrijeme);
            informacije_o_vremenu = localtime (&vrijeme);
            int sat   = informacije_o_vremenu->tm_hour;
            int minut = informacije_o_vremenu->tm_min;
            string s;
            dodajIntUString(sat,s);
            s.push_back(':');
            dodajIntUString(minut,s);
            prikaziString(s); 
        }

        void smanjiOsvjetljenjeDispleja()
        {
            if(osvjetljenje == 0)
               return;
            osvjetljenje-=3;
            for(int i = 0; i < broj_displeja; i++)
               upisiURegistar(INTENSITY_MODE_REG, osvjetljenje, i);
        }

        void pojacajOsvjetljenjeDispleja()
        {
            if(osvjetljenje == 15)
               return;
            osvjetljenje+=3;
            for(int i = 0; i < broj_displeja; i++)
               upisiURegistar(INTENSITY_MODE_REG, osvjetljenje, i);
        }
        
        void ocisti()
        {
            ocistiDispleje();
        }

};

#endif // MAX7219_H
