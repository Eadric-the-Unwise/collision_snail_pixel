#include "hUGEDriver.h"
#include <stddef.h>

static const unsigned char order_cnt = 2;

static const unsigned char P0[] = {
    DN(C_5,7,0xC1B),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1B),
    DN(___,0,0x000),
    DN(C_5,7,0xC1B),
    DN(C_5,7,0xC1B),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(C_5,7,0xC1C),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P1[] = {
    DN(C_4,1,0x000),
    DN(C_5,1,0x000),
    DN(A_3,1,0x000),
    DN(A_4,1,0x000),
    DN(As3,1,0x000),
    DN(As4,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_4,1,0x000),
    DN(C_5,1,0x000),
    DN(A_3,1,0x000),
    DN(A_4,1,0x000),
    DN(As3,1,0x000),
    DN(As4,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(F_4,1,0x000),
    DN(F_5,1,0x000),
    DN(D_4,1,0x000),
    DN(D_5,1,0x000),
    DN(Ds4,1,0x000),
    DN(Ds5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(F_4,1,0x000),
    DN(F_5,1,0x000),
    DN(D_4,1,0x000),
    DN(D_5,1,0x000),
    DN(Ds4,1,0x000),
    DN(Ds5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P2[] = {
    DN(C_3,1,0x000),
    DN(C_4,1,0x000),
    DN(A_3,1,0x000),
    DN(A_3,1,0x000),
    DN(As3,1,0x000),
    DN(As4,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(C_3,1,0x000),
    DN(C_4,1,0x000),
    DN(A_3,1,0x000),
    DN(A_3,1,0x000),
    DN(As3,1,0x000),
    DN(As4,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(F_3,1,0x000),
    DN(F_4,1,0x000),
    DN(D_4,1,0x000),
    DN(D_4,1,0x000),
    DN(Ds4,1,0x000),
    DN(Ds5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(F_3,1,0x000),
    DN(F_4,1,0x000),
    DN(D_4,1,0x000),
    DN(D_4,1,0x000),
    DN(Ds4,1,0x000),
    DN(Ds5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P3[] = {
    DN(B_7,4,0x601),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_7,3,0x000),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_7,4,0x601),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_7,4,0x601),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_7,3,0x000),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_7,4,0x601),
    DN(___,0,0x000),
    DN(B_7,9,0x603),
    DN(B_6,2,0x610),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};

static const unsigned char* const order1[] = {P0};
static const unsigned char* const order2[] = {P1};
static const unsigned char* const order3[] = {P2};
static const unsigned char* const order4[] = {P3};

static const unsigned char duty_instruments[] = {
8,31,160,192,
8,64,240,128,
8,128,240,128,
8,192,240,128,
8,0,241,128,
8,64,241,128,
25,128,241,128,
8,192,241,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
8,128,240,128,
};
static const unsigned char wave_instruments[] = {
218,64,0,192,
0,32,1,128,
0,32,2,128,
0,32,3,128,
0,32,4,128,
0,32,5,128,
0,32,6,128,
0,32,7,128,
0,32,8,128,
0,32,9,128,
0,32,10,128,
0,32,11,128,
0,32,12,128,
0,32,13,128,
0,32,14,128,
};
static const unsigned char noise_instruments[] = {
240,0,0,0,0,0,0,0,
82,0,0,0,0,0,0,0,
81,0,0,0,0,0,0,0,
97,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
97,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
240,0,0,0,0,0,0,0,
};

static const unsigned char waves[] = {
    0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,
    0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,
    0,1,18,35,52,69,86,103,120,137,154,171,188,205,222,239,
    254,220,186,152,118,84,50,16,18,52,86,120,154,188,222,255,
    122,205,219,117,33,19,104,189,220,151,65,1,71,156,221,184,
    15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
    254,252,250,248,246,244,242,240,242,244,246,248,250,252,254,255,
    254,221,204,187,170,153,136,119,138,189,241,36,87,138,189,238,
    132,17,97,237,87,71,90,173,206,163,23,121,221,32,3,71,
    64,183,154,72,115,142,1,51,215,87,136,0,142,11,202,218,
    203,90,166,83,25,136,141,134,200,144,200,179,182,206,36,139,
    10,25,42,148,126,61,75,180,124,114,101,61,167,126,205,222,
    27,109,20,154,50,136,91,228,93,34,30,179,139,20,171,114,
    123,83,38,109,160,3,43,166,55,122,77,43,77,193,150,197,
};

const hUGESong_t songmario = {9, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
