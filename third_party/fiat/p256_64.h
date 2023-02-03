/* Autogenerated: src/ExtractionOCaml/word_by_word_montgomery --static p256 '2^256 - 2^224 + 2^192 + 2^96 - 1' 64 mul square add sub opp from_montgomery nonzero selectznz to_bytes from_bytes */
/* curve description: p256 */
/* requested operations: mul, square, add, sub, opp, from_montgomery, nonzero, selectznz, to_bytes, from_bytes */
/* m = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff (from "2^256 - 2^224 + 2^192 + 2^96 - 1") */
/* machine_wordsize = 64 (from "64") */
/*                                                                    */
/* NOTE: In addition to the bounds specified above each function, all */
/*   functions synthesized for this Montgomery arithmetic require the */
/*   input to be strictly less than the prime modulus (m), and also   */
/*   require the input to be in the unique saturated representation.  */
/*   All functions also ensure that these two properties are true of  */
/*   return values.                                                   */

#include <stdint.h>
typedef unsigned char fiat_p256_uint1;
typedef signed char fiat_p256_int1;
typedef signed __int128 fiat_p256_int128;
typedef unsigned __int128 fiat_p256_uint128;

#if (-1 & 3) != 3
#error "This code only works on a two's complement system"
#endif


/*
 * The function fiat_p256_addcarryx_u64 is an addition with carry.
 * Postconditions:
 *   out1 = (arg1 + arg2 + arg3) mod 2^64
 *   out2 = ⌊(arg1 + arg2 + arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
static void fiat_p256_addcarryx_u64(uint64_t* out1, fiat_p256_uint1* out2, fiat_p256_uint1 arg1, uint64_t arg2, uint64_t arg3) {
  fiat_p256_uint128 x1 = ((arg1 + (fiat_p256_uint128)arg2) + arg3);
  uint64_t x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  fiat_p256_uint1 x3 = (fiat_p256_uint1)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p256_subborrowx_u64 is a subtraction with borrow.
 * Postconditions:
 *   out1 = (-arg1 + arg2 + -arg3) mod 2^64
 *   out2 = -⌊(-arg1 + arg2 + -arg3) / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0x1]
 */
static void fiat_p256_subborrowx_u64(uint64_t* out1, fiat_p256_uint1* out2, fiat_p256_uint1 arg1, uint64_t arg2, uint64_t arg3) {
  fiat_p256_int128 x1 = ((arg2 - (fiat_p256_int128)arg1) - arg3);
  fiat_p256_int1 x2 = (fiat_p256_int1)(x1 >> 64);
  uint64_t x3 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  *out1 = x3;
  *out2 = (fiat_p256_uint1)(0x0 - x2);
}

/*
 * The function fiat_p256_mulx_u64 is a multiplication, returning the full double-width result.
 * Postconditions:
 *   out1 = (arg1 * arg2) mod 2^64
 *   out2 = ⌊arg1 * arg2 / 2^64⌋
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0xffffffffffffffff]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 *   out2: [0x0 ~> 0xffffffffffffffff]
 */
static void fiat_p256_mulx_u64(uint64_t* out1, uint64_t* out2, uint64_t arg1, uint64_t arg2) {
  fiat_p256_uint128 x1 = ((fiat_p256_uint128)arg1 * arg2);
  uint64_t x2 = (uint64_t)(x1 & UINT64_C(0xffffffffffffffff));
  uint64_t x3 = (uint64_t)(x1 >> 64);
  *out1 = x2;
  *out2 = x3;
}

/*
 * The function fiat_p256_cmovznz_u64 is a single-word conditional move.
 * Postconditions:
 *   out1 = (if arg1 = 0 then arg2 else arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [0x0 ~> 0xffffffffffffffff]
 *   arg3: [0x0 ~> 0xffffffffffffffff]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
static void fiat_p256_cmovznz_u64(uint64_t* out1, fiat_p256_uint1 arg1, uint64_t arg2, uint64_t arg3) {
  fiat_p256_uint1 x1 = (!(!arg1));
  uint64_t x2 = ((fiat_p256_int1)(0x0 - x1) & UINT64_C(0xffffffffffffffff));
  // Note this line has been patched from the synthesized code to add value
  // barriers.
  //
  // Clang recognizes this pattern as a select. While it usually transforms it
  // to a cmov, it sometimes further transforms it into a branch, which we do
  // not want.
  uint64_t x3 = ((value_barrier_u64(x2) & arg3) | (value_barrier_u64(~x2) & arg2));
  *out1 = x3;
}

/*
 * The function fiat_p256_mul multiplies two field elements in the Montgomery domain.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 *   0 ≤ eval arg2 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval (from_montgomery arg2)) mod m
 *   0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 *   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_mul(uint64_t out1[4], const uint64_t arg1[4], const uint64_t arg2[4]) {
  uint64_t x1 = (arg1[1]);
  uint64_t x2 = (arg1[2]);
  uint64_t x3 = (arg1[3]);
  uint64_t x4 = (arg1[0]);
  uint64_t x5;
  uint64_t x6;
  fiat_p256_mulx_u64(&x5, &x6, x4, (arg2[3]));
  uint64_t x7;
  uint64_t x8;
  fiat_p256_mulx_u64(&x7, &x8, x4, (arg2[2]));
  uint64_t x9;
  uint64_t x10;
  fiat_p256_mulx_u64(&x9, &x10, x4, (arg2[1]));
  uint64_t x11;
  uint64_t x12;
  fiat_p256_mulx_u64(&x11, &x12, x4, (arg2[0]));
  uint64_t x13;
  fiat_p256_uint1 x14;
  fiat_p256_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  uint64_t x15;
  fiat_p256_uint1 x16;
  fiat_p256_addcarryx_u64(&x15, &x16, x14, x10, x7);
  uint64_t x17;
  fiat_p256_uint1 x18;
  fiat_p256_addcarryx_u64(&x17, &x18, x16, x8, x5);
  uint64_t x19 = (x18 + x6);
  uint64_t x20;
  uint64_t x21;
  fiat_p256_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffff00000001));
  uint64_t x22;
  uint64_t x23;
  fiat_p256_mulx_u64(&x22, &x23, x11, UINT32_C(0xffffffff));
  uint64_t x24;
  uint64_t x25;
  fiat_p256_mulx_u64(&x24, &x25, x11, UINT64_C(0xffffffffffffffff));
  uint64_t x26;
  fiat_p256_uint1 x27;
  fiat_p256_addcarryx_u64(&x26, &x27, 0x0, x25, x22);
  uint64_t x28 = (x27 + x23);
  uint64_t x29;
  fiat_p256_uint1 x30;
  fiat_p256_addcarryx_u64(&x29, &x30, 0x0, x11, x24);
  uint64_t x31;
  fiat_p256_uint1 x32;
  fiat_p256_addcarryx_u64(&x31, &x32, x30, x13, x26);
  uint64_t x33;
  fiat_p256_uint1 x34;
  fiat_p256_addcarryx_u64(&x33, &x34, x32, x15, x28);
  uint64_t x35;
  fiat_p256_uint1 x36;
  fiat_p256_addcarryx_u64(&x35, &x36, x34, x17, x20);
  uint64_t x37;
  fiat_p256_uint1 x38;
  fiat_p256_addcarryx_u64(&x37, &x38, x36, x19, x21);
  uint64_t x39;
  uint64_t x40;
  fiat_p256_mulx_u64(&x39, &x40, x1, (arg2[3]));
  uint64_t x41;
  uint64_t x42;
  fiat_p256_mulx_u64(&x41, &x42, x1, (arg2[2]));
  uint64_t x43;
  uint64_t x44;
  fiat_p256_mulx_u64(&x43, &x44, x1, (arg2[1]));
  uint64_t x45;
  uint64_t x46;
  fiat_p256_mulx_u64(&x45, &x46, x1, (arg2[0]));
  uint64_t x47;
  fiat_p256_uint1 x48;
  fiat_p256_addcarryx_u64(&x47, &x48, 0x0, x46, x43);
  uint64_t x49;
  fiat_p256_uint1 x50;
  fiat_p256_addcarryx_u64(&x49, &x50, x48, x44, x41);
  uint64_t x51;
  fiat_p256_uint1 x52;
  fiat_p256_addcarryx_u64(&x51, &x52, x50, x42, x39);
  uint64_t x53 = (x52 + x40);
  uint64_t x54;
  fiat_p256_uint1 x55;
  fiat_p256_addcarryx_u64(&x54, &x55, 0x0, x31, x45);
  uint64_t x56;
  fiat_p256_uint1 x57;
  fiat_p256_addcarryx_u64(&x56, &x57, x55, x33, x47);
  uint64_t x58;
  fiat_p256_uint1 x59;
  fiat_p256_addcarryx_u64(&x58, &x59, x57, x35, x49);
  uint64_t x60;
  fiat_p256_uint1 x61;
  fiat_p256_addcarryx_u64(&x60, &x61, x59, x37, x51);
  uint64_t x62;
  fiat_p256_uint1 x63;
  fiat_p256_addcarryx_u64(&x62, &x63, x61, x38, x53);
  uint64_t x64;
  uint64_t x65;
  fiat_p256_mulx_u64(&x64, &x65, x54, UINT64_C(0xffffffff00000001));
  uint64_t x66;
  uint64_t x67;
  fiat_p256_mulx_u64(&x66, &x67, x54, UINT32_C(0xffffffff));
  uint64_t x68;
  uint64_t x69;
  fiat_p256_mulx_u64(&x68, &x69, x54, UINT64_C(0xffffffffffffffff));
  uint64_t x70;
  fiat_p256_uint1 x71;
  fiat_p256_addcarryx_u64(&x70, &x71, 0x0, x69, x66);
  uint64_t x72 = (x71 + x67);
  uint64_t x73;
  fiat_p256_uint1 x74;
  fiat_p256_addcarryx_u64(&x73, &x74, 0x0, x54, x68);
  uint64_t x75;
  fiat_p256_uint1 x76;
  fiat_p256_addcarryx_u64(&x75, &x76, x74, x56, x70);
  uint64_t x77;
  fiat_p256_uint1 x78;
  fiat_p256_addcarryx_u64(&x77, &x78, x76, x58, x72);
  uint64_t x79;
  fiat_p256_uint1 x80;
  fiat_p256_addcarryx_u64(&x79, &x80, x78, x60, x64);
  uint64_t x81;
  fiat_p256_uint1 x82;
  fiat_p256_addcarryx_u64(&x81, &x82, x80, x62, x65);
  uint64_t x83 = ((uint64_t)x82 + x63);
  uint64_t x84;
  uint64_t x85;
  fiat_p256_mulx_u64(&x84, &x85, x2, (arg2[3]));
  uint64_t x86;
  uint64_t x87;
  fiat_p256_mulx_u64(&x86, &x87, x2, (arg2[2]));
  uint64_t x88;
  uint64_t x89;
  fiat_p256_mulx_u64(&x88, &x89, x2, (arg2[1]));
  uint64_t x90;
  uint64_t x91;
  fiat_p256_mulx_u64(&x90, &x91, x2, (arg2[0]));
  uint64_t x92;
  fiat_p256_uint1 x93;
  fiat_p256_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  uint64_t x94;
  fiat_p256_uint1 x95;
  fiat_p256_addcarryx_u64(&x94, &x95, x93, x89, x86);
  uint64_t x96;
  fiat_p256_uint1 x97;
  fiat_p256_addcarryx_u64(&x96, &x97, x95, x87, x84);
  uint64_t x98 = (x97 + x85);
  uint64_t x99;
  fiat_p256_uint1 x100;
  fiat_p256_addcarryx_u64(&x99, &x100, 0x0, x75, x90);
  uint64_t x101;
  fiat_p256_uint1 x102;
  fiat_p256_addcarryx_u64(&x101, &x102, x100, x77, x92);
  uint64_t x103;
  fiat_p256_uint1 x104;
  fiat_p256_addcarryx_u64(&x103, &x104, x102, x79, x94);
  uint64_t x105;
  fiat_p256_uint1 x106;
  fiat_p256_addcarryx_u64(&x105, &x106, x104, x81, x96);
  uint64_t x107;
  fiat_p256_uint1 x108;
  fiat_p256_addcarryx_u64(&x107, &x108, x106, x83, x98);
  uint64_t x109;
  uint64_t x110;
  fiat_p256_mulx_u64(&x109, &x110, x99, UINT64_C(0xffffffff00000001));
  uint64_t x111;
  uint64_t x112;
  fiat_p256_mulx_u64(&x111, &x112, x99, UINT32_C(0xffffffff));
  uint64_t x113;
  uint64_t x114;
  fiat_p256_mulx_u64(&x113, &x114, x99, UINT64_C(0xffffffffffffffff));
  uint64_t x115;
  fiat_p256_uint1 x116;
  fiat_p256_addcarryx_u64(&x115, &x116, 0x0, x114, x111);
  uint64_t x117 = (x116 + x112);
  uint64_t x118;
  fiat_p256_uint1 x119;
  fiat_p256_addcarryx_u64(&x118, &x119, 0x0, x99, x113);
  uint64_t x120;
  fiat_p256_uint1 x121;
  fiat_p256_addcarryx_u64(&x120, &x121, x119, x101, x115);
  uint64_t x122;
  fiat_p256_uint1 x123;
  fiat_p256_addcarryx_u64(&x122, &x123, x121, x103, x117);
  uint64_t x124;
  fiat_p256_uint1 x125;
  fiat_p256_addcarryx_u64(&x124, &x125, x123, x105, x109);
  uint64_t x126;
  fiat_p256_uint1 x127;
  fiat_p256_addcarryx_u64(&x126, &x127, x125, x107, x110);
  uint64_t x128 = ((uint64_t)x127 + x108);
  uint64_t x129;
  uint64_t x130;
  fiat_p256_mulx_u64(&x129, &x130, x3, (arg2[3]));
  uint64_t x131;
  uint64_t x132;
  fiat_p256_mulx_u64(&x131, &x132, x3, (arg2[2]));
  uint64_t x133;
  uint64_t x134;
  fiat_p256_mulx_u64(&x133, &x134, x3, (arg2[1]));
  uint64_t x135;
  uint64_t x136;
  fiat_p256_mulx_u64(&x135, &x136, x3, (arg2[0]));
  uint64_t x137;
  fiat_p256_uint1 x138;
  fiat_p256_addcarryx_u64(&x137, &x138, 0x0, x136, x133);
  uint64_t x139;
  fiat_p256_uint1 x140;
  fiat_p256_addcarryx_u64(&x139, &x140, x138, x134, x131);
  uint64_t x141;
  fiat_p256_uint1 x142;
  fiat_p256_addcarryx_u64(&x141, &x142, x140, x132, x129);
  uint64_t x143 = (x142 + x130);
  uint64_t x144;
  fiat_p256_uint1 x145;
  fiat_p256_addcarryx_u64(&x144, &x145, 0x0, x120, x135);
  uint64_t x146;
  fiat_p256_uint1 x147;
  fiat_p256_addcarryx_u64(&x146, &x147, x145, x122, x137);
  uint64_t x148;
  fiat_p256_uint1 x149;
  fiat_p256_addcarryx_u64(&x148, &x149, x147, x124, x139);
  uint64_t x150;
  fiat_p256_uint1 x151;
  fiat_p256_addcarryx_u64(&x150, &x151, x149, x126, x141);
  uint64_t x152;
  fiat_p256_uint1 x153;
  fiat_p256_addcarryx_u64(&x152, &x153, x151, x128, x143);
  uint64_t x154;
  uint64_t x155;
  fiat_p256_mulx_u64(&x154, &x155, x144, UINT64_C(0xffffffff00000001));
  uint64_t x156;
  uint64_t x157;
  fiat_p256_mulx_u64(&x156, &x157, x144, UINT32_C(0xffffffff));
  uint64_t x158;
  uint64_t x159;
  fiat_p256_mulx_u64(&x158, &x159, x144, UINT64_C(0xffffffffffffffff));
  uint64_t x160;
  fiat_p256_uint1 x161;
  fiat_p256_addcarryx_u64(&x160, &x161, 0x0, x159, x156);
  uint64_t x162 = (x161 + x157);
  uint64_t x163;
  fiat_p256_uint1 x164;
  fiat_p256_addcarryx_u64(&x163, &x164, 0x0, x144, x158);
  uint64_t x165;
  fiat_p256_uint1 x166;
  fiat_p256_addcarryx_u64(&x165, &x166, x164, x146, x160);
  uint64_t x167;
  fiat_p256_uint1 x168;
  fiat_p256_addcarryx_u64(&x167, &x168, x166, x148, x162);
  uint64_t x169;
  fiat_p256_uint1 x170;
  fiat_p256_addcarryx_u64(&x169, &x170, x168, x150, x154);
  uint64_t x171;
  fiat_p256_uint1 x172;
  fiat_p256_addcarryx_u64(&x171, &x172, x170, x152, x155);
  uint64_t x173 = ((uint64_t)x172 + x153);
  uint64_t x174;
  fiat_p256_uint1 x175;
  fiat_p256_subborrowx_u64(&x174, &x175, 0x0, x165, UINT64_C(0xffffffffffffffff));
  uint64_t x176;
  fiat_p256_uint1 x177;
  fiat_p256_subborrowx_u64(&x176, &x177, x175, x167, UINT32_C(0xffffffff));
  uint64_t x178;
  fiat_p256_uint1 x179;
  fiat_p256_subborrowx_u64(&x178, &x179, x177, x169, 0x0);
  uint64_t x180;
  fiat_p256_uint1 x181;
  fiat_p256_subborrowx_u64(&x180, &x181, x179, x171, UINT64_C(0xffffffff00000001));
  uint64_t x182;
  fiat_p256_uint1 x183;
  fiat_p256_subborrowx_u64(&x182, &x183, x181, x173, 0x0);
  uint64_t x184;
  fiat_p256_cmovznz_u64(&x184, x183, x174, x165);
  uint64_t x185;
  fiat_p256_cmovznz_u64(&x185, x183, x176, x167);
  uint64_t x186;
  fiat_p256_cmovznz_u64(&x186, x183, x178, x169);
  uint64_t x187;
  fiat_p256_cmovznz_u64(&x187, x183, x180, x171);
  out1[0] = x184;
  out1[1] = x185;
  out1[2] = x186;
  out1[3] = x187;
}

/*
 * The function fiat_p256_square squares a field element in the Montgomery domain.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) * eval (from_montgomery arg1)) mod m
 *   0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_square(uint64_t out1[4], const uint64_t arg1[4]) {
  uint64_t x1 = (arg1[1]);
  uint64_t x2 = (arg1[2]);
  uint64_t x3 = (arg1[3]);
  uint64_t x4 = (arg1[0]);
  uint64_t x5;
  uint64_t x6;
  fiat_p256_mulx_u64(&x5, &x6, x4, (arg1[3]));
  uint64_t x7;
  uint64_t x8;
  fiat_p256_mulx_u64(&x7, &x8, x4, (arg1[2]));
  uint64_t x9;
  uint64_t x10;
  fiat_p256_mulx_u64(&x9, &x10, x4, (arg1[1]));
  uint64_t x11;
  uint64_t x12;
  fiat_p256_mulx_u64(&x11, &x12, x4, (arg1[0]));
  uint64_t x13;
  fiat_p256_uint1 x14;
  fiat_p256_addcarryx_u64(&x13, &x14, 0x0, x12, x9);
  uint64_t x15;
  fiat_p256_uint1 x16;
  fiat_p256_addcarryx_u64(&x15, &x16, x14, x10, x7);
  uint64_t x17;
  fiat_p256_uint1 x18;
  fiat_p256_addcarryx_u64(&x17, &x18, x16, x8, x5);
  uint64_t x19 = (x18 + x6);
  uint64_t x20;
  uint64_t x21;
  fiat_p256_mulx_u64(&x20, &x21, x11, UINT64_C(0xffffffff00000001));
  uint64_t x22;
  uint64_t x23;
  fiat_p256_mulx_u64(&x22, &x23, x11, UINT32_C(0xffffffff));
  uint64_t x24;
  uint64_t x25;
  fiat_p256_mulx_u64(&x24, &x25, x11, UINT64_C(0xffffffffffffffff));
  uint64_t x26;
  fiat_p256_uint1 x27;
  fiat_p256_addcarryx_u64(&x26, &x27, 0x0, x25, x22);
  uint64_t x28 = (x27 + x23);
  uint64_t x29;
  fiat_p256_uint1 x30;
  fiat_p256_addcarryx_u64(&x29, &x30, 0x0, x11, x24);
  uint64_t x31;
  fiat_p256_uint1 x32;
  fiat_p256_addcarryx_u64(&x31, &x32, x30, x13, x26);
  uint64_t x33;
  fiat_p256_uint1 x34;
  fiat_p256_addcarryx_u64(&x33, &x34, x32, x15, x28);
  uint64_t x35;
  fiat_p256_uint1 x36;
  fiat_p256_addcarryx_u64(&x35, &x36, x34, x17, x20);
  uint64_t x37;
  fiat_p256_uint1 x38;
  fiat_p256_addcarryx_u64(&x37, &x38, x36, x19, x21);
  uint64_t x39;
  uint64_t x40;
  fiat_p256_mulx_u64(&x39, &x40, x1, (arg1[3]));
  uint64_t x41;
  uint64_t x42;
  fiat_p256_mulx_u64(&x41, &x42, x1, (arg1[2]));
  uint64_t x43;
  uint64_t x44;
  fiat_p256_mulx_u64(&x43, &x44, x1, (arg1[1]));
  uint64_t x45;
  uint64_t x46;
  fiat_p256_mulx_u64(&x45, &x46, x1, (arg1[0]));
  uint64_t x47;
  fiat_p256_uint1 x48;
  fiat_p256_addcarryx_u64(&x47, &x48, 0x0, x46, x43);
  uint64_t x49;
  fiat_p256_uint1 x50;
  fiat_p256_addcarryx_u64(&x49, &x50, x48, x44, x41);
  uint64_t x51;
  fiat_p256_uint1 x52;
  fiat_p256_addcarryx_u64(&x51, &x52, x50, x42, x39);
  uint64_t x53 = (x52 + x40);
  uint64_t x54;
  fiat_p256_uint1 x55;
  fiat_p256_addcarryx_u64(&x54, &x55, 0x0, x31, x45);
  uint64_t x56;
  fiat_p256_uint1 x57;
  fiat_p256_addcarryx_u64(&x56, &x57, x55, x33, x47);
  uint64_t x58;
  fiat_p256_uint1 x59;
  fiat_p256_addcarryx_u64(&x58, &x59, x57, x35, x49);
  uint64_t x60;
  fiat_p256_uint1 x61;
  fiat_p256_addcarryx_u64(&x60, &x61, x59, x37, x51);
  uint64_t x62;
  fiat_p256_uint1 x63;
  fiat_p256_addcarryx_u64(&x62, &x63, x61, x38, x53);
  uint64_t x64;
  uint64_t x65;
  fiat_p256_mulx_u64(&x64, &x65, x54, UINT64_C(0xffffffff00000001));
  uint64_t x66;
  uint64_t x67;
  fiat_p256_mulx_u64(&x66, &x67, x54, UINT32_C(0xffffffff));
  uint64_t x68;
  uint64_t x69;
  fiat_p256_mulx_u64(&x68, &x69, x54, UINT64_C(0xffffffffffffffff));
  uint64_t x70;
  fiat_p256_uint1 x71;
  fiat_p256_addcarryx_u64(&x70, &x71, 0x0, x69, x66);
  uint64_t x72 = (x71 + x67);
  uint64_t x73;
  fiat_p256_uint1 x74;
  fiat_p256_addcarryx_u64(&x73, &x74, 0x0, x54, x68);
  uint64_t x75;
  fiat_p256_uint1 x76;
  fiat_p256_addcarryx_u64(&x75, &x76, x74, x56, x70);
  uint64_t x77;
  fiat_p256_uint1 x78;
  fiat_p256_addcarryx_u64(&x77, &x78, x76, x58, x72);
  uint64_t x79;
  fiat_p256_uint1 x80;
  fiat_p256_addcarryx_u64(&x79, &x80, x78, x60, x64);
  uint64_t x81;
  fiat_p256_uint1 x82;
  fiat_p256_addcarryx_u64(&x81, &x82, x80, x62, x65);
  uint64_t x83 = ((uint64_t)x82 + x63);
  uint64_t x84;
  uint64_t x85;
  fiat_p256_mulx_u64(&x84, &x85, x2, (arg1[3]));
  uint64_t x86;
  uint64_t x87;
  fiat_p256_mulx_u64(&x86, &x87, x2, (arg1[2]));
  uint64_t x88;
  uint64_t x89;
  fiat_p256_mulx_u64(&x88, &x89, x2, (arg1[1]));
  uint64_t x90;
  uint64_t x91;
  fiat_p256_mulx_u64(&x90, &x91, x2, (arg1[0]));
  uint64_t x92;
  fiat_p256_uint1 x93;
  fiat_p256_addcarryx_u64(&x92, &x93, 0x0, x91, x88);
  uint64_t x94;
  fiat_p256_uint1 x95;
  fiat_p256_addcarryx_u64(&x94, &x95, x93, x89, x86);
  uint64_t x96;
  fiat_p256_uint1 x97;
  fiat_p256_addcarryx_u64(&x96, &x97, x95, x87, x84);
  uint64_t x98 = (x97 + x85);
  uint64_t x99;
  fiat_p256_uint1 x100;
  fiat_p256_addcarryx_u64(&x99, &x100, 0x0, x75, x90);
  uint64_t x101;
  fiat_p256_uint1 x102;
  fiat_p256_addcarryx_u64(&x101, &x102, x100, x77, x92);
  uint64_t x103;
  fiat_p256_uint1 x104;
  fiat_p256_addcarryx_u64(&x103, &x104, x102, x79, x94);
  uint64_t x105;
  fiat_p256_uint1 x106;
  fiat_p256_addcarryx_u64(&x105, &x106, x104, x81, x96);
  uint64_t x107;
  fiat_p256_uint1 x108;
  fiat_p256_addcarryx_u64(&x107, &x108, x106, x83, x98);
  uint64_t x109;
  uint64_t x110;
  fiat_p256_mulx_u64(&x109, &x110, x99, UINT64_C(0xffffffff00000001));
  uint64_t x111;
  uint64_t x112;
  fiat_p256_mulx_u64(&x111, &x112, x99, UINT32_C(0xffffffff));
  uint64_t x113;
  uint64_t x114;
  fiat_p256_mulx_u64(&x113, &x114, x99, UINT64_C(0xffffffffffffffff));
  uint64_t x115;
  fiat_p256_uint1 x116;
  fiat_p256_addcarryx_u64(&x115, &x116, 0x0, x114, x111);
  uint64_t x117 = (x116 + x112);
  uint64_t x118;
  fiat_p256_uint1 x119;
  fiat_p256_addcarryx_u64(&x118, &x119, 0x0, x99, x113);
  uint64_t x120;
  fiat_p256_uint1 x121;
  fiat_p256_addcarryx_u64(&x120, &x121, x119, x101, x115);
  uint64_t x122;
  fiat_p256_uint1 x123;
  fiat_p256_addcarryx_u64(&x122, &x123, x121, x103, x117);
  uint64_t x124;
  fiat_p256_uint1 x125;
  fiat_p256_addcarryx_u64(&x124, &x125, x123, x105, x109);
  uint64_t x126;
  fiat_p256_uint1 x127;
  fiat_p256_addcarryx_u64(&x126, &x127, x125, x107, x110);
  uint64_t x128 = ((uint64_t)x127 + x108);
  uint64_t x129;
  uint64_t x130;
  fiat_p256_mulx_u64(&x129, &x130, x3, (arg1[3]));
  uint64_t x131;
  uint64_t x132;
  fiat_p256_mulx_u64(&x131, &x132, x3, (arg1[2]));
  uint64_t x133;
  uint64_t x134;
  fiat_p256_mulx_u64(&x133, &x134, x3, (arg1[1]));
  uint64_t x135;
  uint64_t x136;
  fiat_p256_mulx_u64(&x135, &x136, x3, (arg1[0]));
  uint64_t x137;
  fiat_p256_uint1 x138;
  fiat_p256_addcarryx_u64(&x137, &x138, 0x0, x136, x133);
  uint64_t x139;
  fiat_p256_uint1 x140;
  fiat_p256_addcarryx_u64(&x139, &x140, x138, x134, x131);
  uint64_t x141;
  fiat_p256_uint1 x142;
  fiat_p256_addcarryx_u64(&x141, &x142, x140, x132, x129);
  uint64_t x143 = (x142 + x130);
  uint64_t x144;
  fiat_p256_uint1 x145;
  fiat_p256_addcarryx_u64(&x144, &x145, 0x0, x120, x135);
  uint64_t x146;
  fiat_p256_uint1 x147;
  fiat_p256_addcarryx_u64(&x146, &x147, x145, x122, x137);
  uint64_t x148;
  fiat_p256_uint1 x149;
  fiat_p256_addcarryx_u64(&x148, &x149, x147, x124, x139);
  uint64_t x150;
  fiat_p256_uint1 x151;
  fiat_p256_addcarryx_u64(&x150, &x151, x149, x126, x141);
  uint64_t x152;
  fiat_p256_uint1 x153;
  fiat_p256_addcarryx_u64(&x152, &x153, x151, x128, x143);
  uint64_t x154;
  uint64_t x155;
  fiat_p256_mulx_u64(&x154, &x155, x144, UINT64_C(0xffffffff00000001));
  uint64_t x156;
  uint64_t x157;
  fiat_p256_mulx_u64(&x156, &x157, x144, UINT32_C(0xffffffff));
  uint64_t x158;
  uint64_t x159;
  fiat_p256_mulx_u64(&x158, &x159, x144, UINT64_C(0xffffffffffffffff));
  uint64_t x160;
  fiat_p256_uint1 x161;
  fiat_p256_addcarryx_u64(&x160, &x161, 0x0, x159, x156);
  uint64_t x162 = (x161 + x157);
  uint64_t x163;
  fiat_p256_uint1 x164;
  fiat_p256_addcarryx_u64(&x163, &x164, 0x0, x144, x158);
  uint64_t x165;
  fiat_p256_uint1 x166;
  fiat_p256_addcarryx_u64(&x165, &x166, x164, x146, x160);
  uint64_t x167;
  fiat_p256_uint1 x168;
  fiat_p256_addcarryx_u64(&x167, &x168, x166, x148, x162);
  uint64_t x169;
  fiat_p256_uint1 x170;
  fiat_p256_addcarryx_u64(&x169, &x170, x168, x150, x154);
  uint64_t x171;
  fiat_p256_uint1 x172;
  fiat_p256_addcarryx_u64(&x171, &x172, x170, x152, x155);
  uint64_t x173 = ((uint64_t)x172 + x153);
  uint64_t x174;
  fiat_p256_uint1 x175;
  fiat_p256_subborrowx_u64(&x174, &x175, 0x0, x165, UINT64_C(0xffffffffffffffff));
  uint64_t x176;
  fiat_p256_uint1 x177;
  fiat_p256_subborrowx_u64(&x176, &x177, x175, x167, UINT32_C(0xffffffff));
  uint64_t x178;
  fiat_p256_uint1 x179;
  fiat_p256_subborrowx_u64(&x178, &x179, x177, x169, 0x0);
  uint64_t x180;
  fiat_p256_uint1 x181;
  fiat_p256_subborrowx_u64(&x180, &x181, x179, x171, UINT64_C(0xffffffff00000001));
  uint64_t x182;
  fiat_p256_uint1 x183;
  fiat_p256_subborrowx_u64(&x182, &x183, x181, x173, 0x0);
  uint64_t x184;
  fiat_p256_cmovznz_u64(&x184, x183, x174, x165);
  uint64_t x185;
  fiat_p256_cmovznz_u64(&x185, x183, x176, x167);
  uint64_t x186;
  fiat_p256_cmovznz_u64(&x186, x183, x178, x169);
  uint64_t x187;
  fiat_p256_cmovznz_u64(&x187, x183, x180, x171);
  out1[0] = x184;
  out1[1] = x185;
  out1[2] = x186;
  out1[3] = x187;
}

/*
 * The function fiat_p256_add adds two field elements in the Montgomery domain.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 *   0 ≤ eval arg2 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) + eval (from_montgomery arg2)) mod m
 *   0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 *   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_add(uint64_t out1[4], const uint64_t arg1[4], const uint64_t arg2[4]) {
  uint64_t x1;
  fiat_p256_uint1 x2;
  fiat_p256_addcarryx_u64(&x1, &x2, 0x0, (arg1[0]), (arg2[0]));
  uint64_t x3;
  fiat_p256_uint1 x4;
  fiat_p256_addcarryx_u64(&x3, &x4, x2, (arg1[1]), (arg2[1]));
  uint64_t x5;
  fiat_p256_uint1 x6;
  fiat_p256_addcarryx_u64(&x5, &x6, x4, (arg1[2]), (arg2[2]));
  uint64_t x7;
  fiat_p256_uint1 x8;
  fiat_p256_addcarryx_u64(&x7, &x8, x6, (arg1[3]), (arg2[3]));
  uint64_t x9;
  fiat_p256_uint1 x10;
  fiat_p256_subborrowx_u64(&x9, &x10, 0x0, x1, UINT64_C(0xffffffffffffffff));
  uint64_t x11;
  fiat_p256_uint1 x12;
  fiat_p256_subborrowx_u64(&x11, &x12, x10, x3, UINT32_C(0xffffffff));
  uint64_t x13;
  fiat_p256_uint1 x14;
  fiat_p256_subborrowx_u64(&x13, &x14, x12, x5, 0x0);
  uint64_t x15;
  fiat_p256_uint1 x16;
  fiat_p256_subborrowx_u64(&x15, &x16, x14, x7, UINT64_C(0xffffffff00000001));
  uint64_t x17;
  fiat_p256_uint1 x18;
  fiat_p256_subborrowx_u64(&x17, &x18, x16, x8, 0x0);
  uint64_t x19;
  fiat_p256_cmovznz_u64(&x19, x18, x9, x1);
  uint64_t x20;
  fiat_p256_cmovznz_u64(&x20, x18, x11, x3);
  uint64_t x21;
  fiat_p256_cmovznz_u64(&x21, x18, x13, x5);
  uint64_t x22;
  fiat_p256_cmovznz_u64(&x22, x18, x15, x7);
  out1[0] = x19;
  out1[1] = x20;
  out1[2] = x21;
  out1[3] = x22;
}

/*
 * The function fiat_p256_sub subtracts two field elements in the Montgomery domain.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 *   0 ≤ eval arg2 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = (eval (from_montgomery arg1) - eval (from_montgomery arg2)) mod m
 *   0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 *   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_sub(uint64_t out1[4], const uint64_t arg1[4], const uint64_t arg2[4]) {
  uint64_t x1;
  fiat_p256_uint1 x2;
  fiat_p256_subborrowx_u64(&x1, &x2, 0x0, (arg1[0]), (arg2[0]));
  uint64_t x3;
  fiat_p256_uint1 x4;
  fiat_p256_subborrowx_u64(&x3, &x4, x2, (arg1[1]), (arg2[1]));
  uint64_t x5;
  fiat_p256_uint1 x6;
  fiat_p256_subborrowx_u64(&x5, &x6, x4, (arg1[2]), (arg2[2]));
  uint64_t x7;
  fiat_p256_uint1 x8;
  fiat_p256_subborrowx_u64(&x7, &x8, x6, (arg1[3]), (arg2[3]));
  uint64_t x9;
  fiat_p256_cmovznz_u64(&x9, x8, 0x0, UINT64_C(0xffffffffffffffff));
  uint64_t x10;
  fiat_p256_uint1 x11;
  fiat_p256_addcarryx_u64(&x10, &x11, 0x0, x1, (x9 & UINT64_C(0xffffffffffffffff)));
  uint64_t x12;
  fiat_p256_uint1 x13;
  fiat_p256_addcarryx_u64(&x12, &x13, x11, x3, (x9 & UINT32_C(0xffffffff)));
  uint64_t x14;
  fiat_p256_uint1 x15;
  fiat_p256_addcarryx_u64(&x14, &x15, x13, x5, 0x0);
  uint64_t x16;
  fiat_p256_uint1 x17;
  fiat_p256_addcarryx_u64(&x16, &x17, x15, x7, (x9 & UINT64_C(0xffffffff00000001)));
  out1[0] = x10;
  out1[1] = x12;
  out1[2] = x14;
  out1[3] = x16;
}

/*
 * The function fiat_p256_opp negates a field element in the Montgomery domain.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 * Postconditions:
 *   eval (from_montgomery out1) mod m = -eval (from_montgomery arg1) mod m
 *   0 ≤ eval out1 < m
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_opp(uint64_t out1[4], const uint64_t arg1[4]) {
  uint64_t x1;
  fiat_p256_uint1 x2;
  fiat_p256_subborrowx_u64(&x1, &x2, 0x0, 0x0, (arg1[0]));
  uint64_t x3;
  fiat_p256_uint1 x4;
  fiat_p256_subborrowx_u64(&x3, &x4, x2, 0x0, (arg1[1]));
  uint64_t x5;
  fiat_p256_uint1 x6;
  fiat_p256_subborrowx_u64(&x5, &x6, x4, 0x0, (arg1[2]));
  uint64_t x7;
  fiat_p256_uint1 x8;
  fiat_p256_subborrowx_u64(&x7, &x8, x6, 0x0, (arg1[3]));
  uint64_t x9;
  fiat_p256_cmovznz_u64(&x9, x8, 0x0, UINT64_C(0xffffffffffffffff));
  uint64_t x10;
  fiat_p256_uint1 x11;
  fiat_p256_addcarryx_u64(&x10, &x11, 0x0, x1, (x9 & UINT64_C(0xffffffffffffffff)));
  uint64_t x12;
  fiat_p256_uint1 x13;
  fiat_p256_addcarryx_u64(&x12, &x13, x11, x3, (x9 & UINT32_C(0xffffffff)));
  uint64_t x14;
  fiat_p256_uint1 x15;
  fiat_p256_addcarryx_u64(&x14, &x15, x13, x5, 0x0);
  uint64_t x16;
  fiat_p256_uint1 x17;
  fiat_p256_addcarryx_u64(&x16, &x17, x15, x7, (x9 & UINT64_C(0xffffffff00000001)));
  out1[0] = x10;
  out1[1] = x12;
  out1[2] = x14;
  out1[3] = x16;
}

/*
 * The function fiat_p256_nonzero outputs a single non-zero word if the input is non-zero and zero otherwise.
 * Preconditions:
 *   0 ≤ eval arg1 < m
 * Postconditions:
 *   out1 = 0 ↔ eval (from_montgomery arg1) mod m = 0
 *
 * Input Bounds:
 *   arg1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [0x0 ~> 0xffffffffffffffff]
 */
static void fiat_p256_nonzero(uint64_t* out1, const uint64_t arg1[4]) {
  uint64_t x1 = ((arg1[0]) | ((arg1[1]) | ((arg1[2]) | ((arg1[3]) | (uint64_t)0x0))));
  *out1 = x1;
}

/*
 * The function fiat_p256_selectznz is a multi-limb conditional select.
 * Postconditions:
 *   eval out1 = (if arg1 = 0 then eval arg2 else eval arg3)
 *
 * Input Bounds:
 *   arg1: [0x0 ~> 0x1]
 *   arg2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 *   arg3: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static void fiat_p256_selectznz(uint64_t out1[4], fiat_p256_uint1 arg1, const uint64_t arg2[4], const uint64_t arg3[4]) {
  uint64_t x1;
  fiat_p256_cmovznz_u64(&x1, arg1, (arg2[0]), (arg3[0]));
  uint64_t x2;
  fiat_p256_cmovznz_u64(&x2, arg1, (arg2[1]), (arg3[1]));
  uint64_t x3;
  fiat_p256_cmovznz_u64(&x3, arg1, (arg2[2]), (arg3[2]));
  uint64_t x4;
  fiat_p256_cmovznz_u64(&x4, arg1, (arg2[3]), (arg3[3]));
  out1[0] = x1;
  out1[1] = x2;
  out1[2] = x3;
  out1[3] = x4;
}

