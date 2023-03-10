#include "humidity.h"


const uint8_t Ihumidity_tga_zic[1241] = {
0x80,  0xCF,  0x04,  0x01,  0x80,  0xDE,  0x42,  0xB6,  0x46,  0xB6,  0x04,  0x21,  0x80,  0xDC,  0x3E,  0x95, 
0x53,  0x5C,  0xC0,  0x42,  0x95,  0x08,  0x42,  0x80,  0xDA,  0x3A,  0x53,  0x86,  0xC2,  0x46,  0x95,  0x80, 
0xD9,  0x36,  0x11,  0x86,  0xC0,  0x53,  0x7C,  0x86,  0xC1,  0x3E,  0x53,  0x80,  0xD7,  0x2D,  0xAE,  0x53, 
0x5B,  0x86,  0xC1,  0x8C,  0x86,  0xC1,  0x36,  0x10,  0x80,  0xD5,  0x25,  0x4B,  0x53,  0x3B,  0x86,  0x8C, 
0xC0,  0x86,  0xC1,  0x8C,  0x86,  0x8F,  0x29,  0x8C,  0x80,  0xD3,  0x1C,  0xE8,  0x4F,  0x1A,  0x57,  0x7C, 
0x5B,  0x7C,  0x96,  0x86,  0xC0,  0x8C,  0xC0,  0x86,  0xC0,  0x8C,  0x95,  0x18,  0xE7,  0x80,  0xD1,  0x0C, 
0x63,  0x4A,  0xF8,  0x63,  0x9D,  0x73,  0xDE,  0x7B,  0xFF,  0x9C,  0x5B,  0x7D,  0x8C,  0x86,  0xC4,  0x4A, 
0xD7,  0x88,  0x80,  0xD0,  0x42,  0x74,  0x67,  0xBD,  0x9D,  0x7F,  0xFF,  0xC0,  0x9D,  0x9B,  0x8C,  0x86, 
0xC4,  0x8C,  0x3E,  0x73,  0x80,  0xCF,  0x31,  0xAE,  0x9B,  0x9D,  0xA2,  0xC1,  0x9D,  0x9B,  0x8C,  0x86, 
0x8C,  0x86,  0xC0,  0x8C,  0x86,  0x8C,  0x86,  0x31,  0xCE,  0x80,  0xCD,  0x19,  0x08,  0x57,  0x5B,  0x9C, 
0xA2,  0xC2,  0x77,  0xFF,  0x5F,  0x9D,  0x8C,  0xC1,  0x86,  0xC1,  0x8C,  0x86,  0xC0,  0x4F,  0x3A,  0x1D, 
0x08,  0x80,  0xCC,  0x9F,  0x9B,  0x9D,  0xA2,  0xC2,  0x6F,  0xDE,  0x96,  0x8C,  0x86,  0xC3,  0x4F,  0x5C, 
0x4B,  0x5B,  0x47,  0x3B,  0xC0,  0x3A,  0xB6,  0x84,  0x80,  0xCA,  0x36,  0x32,  0x8C,  0x6B,  0xBE,  0xA2, 
0xC2,  0xA8,  0xA9,  0x8C,  0xC0,  0x86,  0xC0,  0xAD,  0xAF,  0x43,  0x3B,  0xC4,  0x32,  0x11,  0x80,  0xC9, 
0x21,  0x2A,  0x8F,  0x96,  0xAC,  0xA2,  0xC1,  0x9D,  0x67,  0xBE,  0x96,  0xC0,  0x86,  0x4B,  0x5C,  0xAF, 
0xC1,  0xB3,  0xC4,  0x43,  0x1A,  0x21,  0x4A,  0x80,  0xC7,  0x84,  0x9A,  0x86,  0x8C,  0xA1,  0x9D,  0xA2, 
0x9D,  0xB6,  0x9E,  0x8C,  0xAD,  0xAE,  0xC3,  0xAF,  0xC1,  0xB3,  0xC2,  0x3E,  0xB7,  0x99,  0x80,  0xC6, 
0x3A,  0x31,  0x86,  0xC0,  0x8C,  0x96,  0x9B,  0xA1,  0xA9,  0x96,  0xAD,  0xC6,  0xAE,  0xC0,  0xAF,  0xC0, 
0xB3,  0xC2,  0x32,  0x10,  0x80,  0xC5,  0x18,  0xC6,  0xAA,  0x86,  0xC0,  0x8C,  0xC0,  0x96,  0xC0,  0x8C, 
0xAD,  0x86,  0xC0,  0x8C,  0xC3,  0x86,  0xAD,  0xC0,  0xAE,  0xC0,  0xAF,  0xB3,  0xC1,  0x42,  0xF9,  0xBD, 
0x80,  0xC4,  0xA0,  0x86,  0x8C,  0x86,  0x8C,  0x96,  0xC0,  0xAD,  0x86,  0x8C,  0x96,  0xC6,  0x8C,  0x86, 
0xAD,  0xC0,  0xAE,  0xAF,  0xB3,  0xC1,  0xB1,  0x80,  0xC3,  0x1C,  0xE7,  0x8F,  0x8C,  0x86,  0x8C,  0x96, 
0xC0,  0x4F,  0x5B,  0x3E,  0xF5,  0x2A,  0x6F,  0x26,  0x6D,  0x32,  0xB1,  0x53,  0x5A,  0x9E,  0x5B,  0x9D, 
0xC1,  0x9E,  0xA7,  0x42,  0xF6,  0xAA,  0x8C,  0xAD,  0xC0,  0xAE,  0xAF,  0xB3,  0xC0,  0xBE,  0x10,  0x85, 
0x80,  0xC2,  0x3E,  0x53,  0x8C,  0xC1,  0x96,  0x86,  0xAD,  0x36,  0xB3,  0x0E,  0x24,  0x32,  0x90,  0x3A, 
0xD3,  0x22,  0x4B,  0x1A,  0x27,  0x57,  0x7B,  0xA9,  0x9B,  0xC0,  0xA9,  0x3E,  0xD3,  0x16,  0x48,  0xA7, 
0x96,  0x8C,  0xAD,  0xC0,  0x4B,  0x3B,  0xAF,  0xB3,  0xC0,  0x32,  0x32,  0x80,  0xC1,  0x10,  0x84,  0xAA, 
0x86,  0x8C,  0xC0,  0xAD,  0xB7,  0x81,  0x12,  0x26,  0x36,  0xB2,  0x9E,  0xA9,  0x5B,  0x7B,  0x12,  0x25, 
0x42,  0xF4,  0xA1,  0xC0,  0x9B,  0xAB,  0x9F,  0x42,  0xF5,  0x8A,  0x9E,  0x96,  0x86,  0xAD,  0xAE,  0xAF, 
0xB3,  0xC0,  0xBE,  0x14,  0xC6,  0x80,  0xC0,  0x2D,  0xAE,  0x8C,  0x86,  0x8C,  0xB7,  0xAE,  0xAD,  0x47, 
0x19,  0x91,  0x4B,  0x17,  0xA9,  0x9B,  0xC0,  0x2A,  0x6D,  0x36,  0x8F,  0x6B,  0xBE,  0xC1,  0x3E,  0xD2, 
0x1E,  0x49,  0x5F,  0x9C,  0xA9,  0x8A,  0x5B,  0x7C,  0x96,  0x86,  0xAD,  0xA3,  0xAF,  0xB3,  0x43,  0x1B, 
0xB4,  0x80,  0xC0,  0x42,  0x95,  0x86,  0xC0,  0xA3,  0xAF,  0xAE,  0xAD,  0x4B,  0x19,  0x91,  0x4F,  0x38, 
0xA9,  0x9B,  0x67,  0xBE,  0xB9,  0x36,  0x8E,  0x6F,  0xDE,  0xC0,  0x63,  0x7B,  0x0E,  0x25,  0x53,  0x16, 
0xA1,  0x9B,  0xA9,  0x9E,  0x96,  0x8C,  0xAD,  0xAE,  0xAF,  0xB3,  0x3E,  0xF9,  0x36,  0x74,  0x80,  0xC0, 
0x4A,  0xF8,  0x86,  0xA3,  0xAF,  0xA3,  0xAD,  0x86,  0x4B,  0x39,  0x91,  0xAC,  0x9B,  0xA1,  0x84,  0x2A, 
0x6C,  0x3A,  0xB0,  0x73,  0xDE,  0xC0,  0x3E,  0xB1,  0x2A,  0x6B,  0x6B,  0xBD,  0x84,  0xA1,  0x9B,  0xA9, 
0xB6,  0x8C,  0xAD,  0xAE,  0xAF,  0xB3,  0x3E,  0xF8,  0x42,  0xD8,  0x80,  0xC0,  0xAA,  0xAE,  0xB3,  0xAF, 
0xAE,  0xAD,  0x8C,  0x96,  0x16,  0x28,  0x36,  0xB1,  0x9B,  0x84,  0xBF,  0x91,  0x82,  0x77,  0xDF,  0x6B, 
0x9B,  0x91,  0x5B,  0x58,  0xB1,  0x84,  0x67,  0x9D,  0x5F,  0x7C,  0xB6,  0x9E,  0x96,  0x86,  0xAD,  0xA3, 
0xB3,  0x3E,  0xD8,  0xBE,  0x0C,  0x63,  0x80,  0x4B,  0x3A,  0xB3,  0xC0,  0xAF,  0xAE,  0xAD,  0x8C,  0x96, 
0xB2,  0x91,  0x8B,  0x36,  0xB0,  0x1A,  0x27,  0x2A,  0x4B,  0x6F,  0xBD,  0x7B,  0xFF,  0x3E,  0xB0,  0x32, 
0x6D,  0x77,  0xDE,  0xB1,  0x4A,  0xF4,  0x16,  0x27,  0x91,  0x8A,  0x3A,  0xD3,  0x96,  0x86,  0xAD,  0xA3, 
0xB3,  0x3A,  0xD7,  0xBE,  0x21,  0x29,  0x80,  0xBE,  0xB3,  0xC0,  0xAF,  0xAE,  0xAD,  0x8C,  0x96,  0x5B, 
0x9D,  0xBC,  0x42,  0xD2,  0x90,  0x4F,  0x15,  0xB7,  0x88,  0x67,  0x7A,  0x91,  0x67,  0x79,  0xA2,  0x82, 
0x91,  0x46,  0xF4,  0x53,  0x38,  0x3E,  0xD4,  0x91,  0x3A,  0xD5,  0x86,  0xAD,  0xA3,  0xAF,  0xB4,  0xBE, 
0x21,  0x08,  0x80,  0xA6,  0xB3,  0xC0,  0xAF,  0xAE,  0xAD,  0x8C,  0x96,  0xBB,  0xA9,  0x9B,  0x84,  0x6F, 
0xBE,  0x8E,  0xA2,  0x36,  0x8E,  0x3A,  0x8E,  0xA2,  0x8E,  0x2E,  0x6C,  0x36,  0x8F,  0x84,  0x9B,  0xA9, 
0x2E,  0x8F,  0x1E,  0x4B,  0x86,  0xAD,  0xA3,  0xB3,  0x3A,  0xB6,  0xBE,  0x80,  0xC0,  0x3A,  0x96,  0xB3, 
0xC0,  0xAF,  0xAE,  0xAD,  0x86,  0x96,  0x9E,  0xA9,  0x9B,  0x67,  0xBD,  0x84,  0xB1,  0x5F,  0x59,  0x91, 
0xA0,  0x8E,  0x8D,  0x0E,  0x25,  0x83,  0xBF,  0x9B,  0xA9,  0x87,  0x91,  0x4F,  0x5B,  0xAD,  0xAF,  0x43, 
0x1A,  0x36,  0x96,  0x3E,  0xB7,  0x80,  0xC0,  0x36,  0x53,  0xB3,  0xC1,  0xAF,  0xAD,  0x86,  0x96,  0x9E, 
0xA9,  0x9B,  0xC0,  0x67,  0xBE,  0x6B,  0xBD,  0xA1,  0x3A,  0xB0,  0xB1,  0xC0,  0x8B,  0x91,  0x9D,  0x9B, 
0xA9,  0xBB,  0x87,  0x91,  0xA5,  0xAE,  0xAF,  0x3E,  0xF9,  0x3A,  0xB7,  0xB0,  0x80,  0xC0,  0x2D,  0xAD, 
0xB3,  0x43,  0x1B,  0xB3,  0xAF,  0xAE,  0xAD,  0x8C,  0x96,  0x9E,  0xA9,  0x9B,  0xBF,  0x53,  0x37,  0x91, 
0x5F,  0x7B,  0x8D,  0x84,  0x8B,  0x1E,  0x49,  0x3E,  0xB2,  0x9B,  0xA9,  0x9E,  0x36,  0xB1,  0x16,  0x48, 
0xA5,  0xAE,  0xAF,  0x36,  0xB6,  0x3E,  0xF8,  0x29,  0x8C,  0x80,  0xC0,  0x10,  0x84,  0xBE,  0x81,  0xB3, 
0xAF,  0xAE,  0xAD,  0x86,  0x96,  0x5B,  0x7C,  0xBB,  0xA9,  0x9B,  0x22,  0x4A,  0x3A,  0xB2,  0xBF,  0xB2, 
0xBF,  0xC0,  0x85,  0x1A,  0x28,  0x53,  0x5A,  0x9E,  0x4F,  0x39,  0x16,  0x27,  0x2E,  0x91,  0xAE,  0xA3, 
0x81,  0x32,  0x74,  0x42,  0xD8,  0x08,  0x42,  0x80,  0xC1,  0x36,  0x32,  0xB8,  0x9F,  0xB3,  0xAF,  0xAE, 
0xAD,  0x8C,  0x96,  0x9E,  0xC0,  0x46,  0xF5,  0xA4,  0x5B,  0x7B,  0x9B,  0xC2,  0x95,  0x22,  0x6C,  0x91, 
0x12,  0x25,  0x91,  0x1E,  0x4B,  0x4B,  0x3A,  0xAE,  0xAF,  0x90,  0xA8,  0x97,  0x80,  0xC2,  0x1C,  0xE7, 
0xBE,  0x9F,  0x81,  0xAF,  0xA3,  0x4B,  0x5C,  0xAD,  0x8C,  0x96,  0x8F,  0xC0,  0x9E,  0xA9,  0xC2,  0xBB, 
0xC0,  0x8F,  0x4B,  0x18,  0x42,  0xF6,  0x43,  0x17,  0xA5,  0xAE,  0xAF,  0x9F,  0x93,  0xB9,  0x14,  0xA5, 
0x80,  0xC3,  0x36,  0x11,  0xB8,  0x3A,  0xD7,  0x81,  0xAF,  0xAE,  0xAD,  0xC0,  0x86,  0x8C,  0x96,  0x8F, 
0x9E,  0xC3,  0x96,  0xC0,  0x8C,  0x86,  0xAD,  0xAE,  0xAF,  0x81,  0x93,  0x3A,  0xD8,  0x9D,  0x80,  0xC4, 
0x0C,  0x64,  0x3E,  0xB6,  0x81,  0xA8,  0x81,  0xAF,  0xAE,  0xB6,  0xAD,  0x86,  0x8C,  0xC0,  0x96,  0xC2, 
0x8C,  0xC1,  0xAD,  0xC0,  0xAE,  0xA3,  0x81,  0x36,  0x75,  0x90,  0x3E,  0x96,  0xB5,  0x80,  0xC5,  0x21, 
0x29,  0xBE,  0x9F,  0x3A,  0xB6,  0x81,  0xAF,  0xA3,  0xAE,  0xAD,  0xC0,  0x86,  0xC4,  0xAD,  0xC0,  0xAE, 
0xC0,  0xAF,  0x81,  0x32,  0x75,  0x36,  0x95,  0x3E,  0xD7,  0xB1,  0x80,  0xC7,  0x25,  0x4B,  0xBE,  0x9F, 
0x99,  0x3E,  0xD8,  0xB3,  0xAF,  0xAE,  0xC1,  0xAD,  0xC2,  0xB6,  0xAE,  0xC0,  0xA3,  0xAF,  0xB0,  0x32, 
0x54,  0x99,  0xA2,  0x1D,  0x08,  0x80,  0xC9,  0x25,  0x4A,  0x42,  0xD7,  0x81,  0x90,  0x99,  0xB9,  0x81, 
0xAF,  0xC0,  0xA3,  0xC0,  0xAE,  0xA3,  0xAF,  0xC0,  0xB3,  0xB9,  0x99,  0x88,  0xA8,  0x3E,  0xB7,  0x82, 
0x80,  0xCB,  0x83,  0x36,  0x53,  0x81,  0xB9,  0x99,  0x93,  0x36,  0x96,  0xB0,  0x9F,  0xBE,  0x9F,  0xC0, 
0xB0,  0xB4,  0x93,  0x32,  0x53,  0xB4,  0xB9,  0x32,  0x32,  0x10,  0x84,  0x80,  0xCE,  0x1D,  0x29,  0x3A, 
0x75,  0x81,  0x9F,  0xA8,  0x99,  0x88,  0xC2,  0x93,  0x99,  0x87,  0x9F,  0x36,  0x74,  0x1D,  0x09,  0x80, 
0xD2,  0x84,  0x32,  0x11,  0x9A,  0xB7,  0xBE,  0x3F,  0x1A,  0x9F,  0xBE,  0x87,  0x8A,  0x29,  0xF0,  0x18, 
0xE7,  0x80,  0xD9,  0x00,  0x01,  0x08,  0x42,  0x80,  0xCE,  
};
