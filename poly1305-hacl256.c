#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/unaligned.h>
#include "vec-intrin.h"

#define load64_le(x) get_unaligned_le64(x)
#define store64_le(d, s) put_unaligned_le64(s, d)
#define KRML_CHECK_SIZE(a,b) {}


__always_inline static uint64_t FStar_UInt64_eq_mask(uint64_t a, uint64_t b)
{
  uint64_t x = a ^ b;
  uint64_t minus_x = ~x + (uint64_t)1U;
  uint64_t x_or_minus_x = x | minus_x;
  uint64_t xnx = x_or_minus_x >> (uint32_t)63U;
  return xnx - (uint64_t)1U;
}

__always_inline static uint64_t FStar_UInt64_gte_mask(uint64_t a, uint64_t b)
{
  uint64_t x = a;
  uint64_t y = b;
  uint64_t x_xor_y = x ^ y;
  uint64_t x_sub_y = x - y;
  uint64_t x_sub_y_xor_y = x_sub_y ^ y;
  uint64_t q = x_xor_y | x_sub_y_xor_y;
  uint64_t x_xor_q = x ^ q;
  uint64_t x_xor_q_ = x_xor_q >> (uint32_t)63U;
  return x_xor_q_ - (uint64_t)1U;
}


uint32_t Hacl_Poly1305_256_blocklen = (uint32_t)16U;

void Hacl_Poly1305_256_poly1305_init(Lib_IntVector_Intrinsics_vec256 *ctx, uint8_t *key)
{
  Lib_IntVector_Intrinsics_vec256 *acc = ctx;
  Lib_IntVector_Intrinsics_vec256 *pre = ctx + (uint32_t)5U;
  uint8_t *kr = key;
  acc[0U] = Lib_IntVector_Intrinsics_vec256_zero;
  acc[1U] = Lib_IntVector_Intrinsics_vec256_zero;
  acc[2U] = Lib_IntVector_Intrinsics_vec256_zero;
  acc[3U] = Lib_IntVector_Intrinsics_vec256_zero;
  acc[4U] = Lib_IntVector_Intrinsics_vec256_zero;
  uint64_t u0 = load64_le(kr);
  uint64_t lo = u0;
  uint64_t u = load64_le(kr + (uint32_t)8U);
  uint64_t hi = u;
  uint64_t mask0 = (uint64_t)0x0ffffffc0fffffffU;
  uint64_t mask1 = (uint64_t)0x0ffffffc0ffffffcU;
  uint64_t lo1 = lo & mask0;
  uint64_t hi1 = hi & mask1;
  Lib_IntVector_Intrinsics_vec256 *r = pre;
  Lib_IntVector_Intrinsics_vec256 *r5 = pre + (uint32_t)5U;
  Lib_IntVector_Intrinsics_vec256 *rn = pre + (uint32_t)10U;
  Lib_IntVector_Intrinsics_vec256 *rn_5 = pre + (uint32_t)15U;
  Lib_IntVector_Intrinsics_vec256 r_vec0 = Lib_IntVector_Intrinsics_vec256_load64(lo1);
  Lib_IntVector_Intrinsics_vec256 r_vec1 = Lib_IntVector_Intrinsics_vec256_load64(hi1);
  Lib_IntVector_Intrinsics_vec256
  f00 =
    Lib_IntVector_Intrinsics_vec256_and(r_vec0,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  f15 =
    Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(r_vec0,
        (uint32_t)26U),
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  f20 =
    Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(r_vec0,
        (uint32_t)52U),
      Lib_IntVector_Intrinsics_vec256_shift_left64(Lib_IntVector_Intrinsics_vec256_and(r_vec1,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffU)),
        (uint32_t)12U));
  Lib_IntVector_Intrinsics_vec256
  f30 =
    Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(r_vec1,
        (uint32_t)14U),
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  f40 = Lib_IntVector_Intrinsics_vec256_shift_right64(r_vec1, (uint32_t)40U);
  Lib_IntVector_Intrinsics_vec256 f0 = f00;
  Lib_IntVector_Intrinsics_vec256 f1 = f15;
  Lib_IntVector_Intrinsics_vec256 f2 = f20;
  Lib_IntVector_Intrinsics_vec256 f3 = f30;
  Lib_IntVector_Intrinsics_vec256 f4 = f40;
  r[0U] = f0;
  r[1U] = f1;
  r[2U] = f2;
  r[3U] = f3;
  r[4U] = f4;
  Lib_IntVector_Intrinsics_vec256 f200 = r[0U];
  Lib_IntVector_Intrinsics_vec256 f210 = r[1U];
  Lib_IntVector_Intrinsics_vec256 f220 = r[2U];
  Lib_IntVector_Intrinsics_vec256 f230 = r[3U];
  Lib_IntVector_Intrinsics_vec256 f240 = r[4U];
  r5[0U] = Lib_IntVector_Intrinsics_vec256_smul64(f200, (uint64_t)5U);
  r5[1U] = Lib_IntVector_Intrinsics_vec256_smul64(f210, (uint64_t)5U);
  r5[2U] = Lib_IntVector_Intrinsics_vec256_smul64(f220, (uint64_t)5U);
  r5[3U] = Lib_IntVector_Intrinsics_vec256_smul64(f230, (uint64_t)5U);
  r5[4U] = Lib_IntVector_Intrinsics_vec256_smul64(f240, (uint64_t)5U);
  Lib_IntVector_Intrinsics_vec256 r0 = r[0U];
  Lib_IntVector_Intrinsics_vec256 r10 = r[1U];
  Lib_IntVector_Intrinsics_vec256 r20 = r[2U];
  Lib_IntVector_Intrinsics_vec256 r30 = r[3U];
  Lib_IntVector_Intrinsics_vec256 r40 = r[4U];
  Lib_IntVector_Intrinsics_vec256 r510 = r5[1U];
  Lib_IntVector_Intrinsics_vec256 r520 = r5[2U];
  Lib_IntVector_Intrinsics_vec256 r530 = r5[3U];
  Lib_IntVector_Intrinsics_vec256 r540 = r5[4U];
  Lib_IntVector_Intrinsics_vec256 f100 = r[0U];
  Lib_IntVector_Intrinsics_vec256 f110 = r[1U];
  Lib_IntVector_Intrinsics_vec256 f120 = r[2U];
  Lib_IntVector_Intrinsics_vec256 f130 = r[3U];
  Lib_IntVector_Intrinsics_vec256 f140 = r[4U];
  Lib_IntVector_Intrinsics_vec256 a00 = Lib_IntVector_Intrinsics_vec256_mul64(r0, f100);
  Lib_IntVector_Intrinsics_vec256 a10 = Lib_IntVector_Intrinsics_vec256_mul64(r10, f100);
  Lib_IntVector_Intrinsics_vec256 a20 = Lib_IntVector_Intrinsics_vec256_mul64(r20, f100);
  Lib_IntVector_Intrinsics_vec256 a30 = Lib_IntVector_Intrinsics_vec256_mul64(r30, f100);
  Lib_IntVector_Intrinsics_vec256 a40 = Lib_IntVector_Intrinsics_vec256_mul64(r40, f100);
  Lib_IntVector_Intrinsics_vec256
  a010 =
    Lib_IntVector_Intrinsics_vec256_add64(a00,
      Lib_IntVector_Intrinsics_vec256_mul64(r540, f110));
  Lib_IntVector_Intrinsics_vec256
  a110 =
    Lib_IntVector_Intrinsics_vec256_add64(a10,
      Lib_IntVector_Intrinsics_vec256_mul64(r0, f110));
  Lib_IntVector_Intrinsics_vec256
  a210 =
    Lib_IntVector_Intrinsics_vec256_add64(a20,
      Lib_IntVector_Intrinsics_vec256_mul64(r10, f110));
  Lib_IntVector_Intrinsics_vec256
  a310 =
    Lib_IntVector_Intrinsics_vec256_add64(a30,
      Lib_IntVector_Intrinsics_vec256_mul64(r20, f110));
  Lib_IntVector_Intrinsics_vec256
  a410 =
    Lib_IntVector_Intrinsics_vec256_add64(a40,
      Lib_IntVector_Intrinsics_vec256_mul64(r30, f110));
  Lib_IntVector_Intrinsics_vec256
  a020 =
    Lib_IntVector_Intrinsics_vec256_add64(a010,
      Lib_IntVector_Intrinsics_vec256_mul64(r530, f120));
  Lib_IntVector_Intrinsics_vec256
  a120 =
    Lib_IntVector_Intrinsics_vec256_add64(a110,
      Lib_IntVector_Intrinsics_vec256_mul64(r540, f120));
  Lib_IntVector_Intrinsics_vec256
  a220 =
    Lib_IntVector_Intrinsics_vec256_add64(a210,
      Lib_IntVector_Intrinsics_vec256_mul64(r0, f120));
  Lib_IntVector_Intrinsics_vec256
  a320 =
    Lib_IntVector_Intrinsics_vec256_add64(a310,
      Lib_IntVector_Intrinsics_vec256_mul64(r10, f120));
  Lib_IntVector_Intrinsics_vec256
  a420 =
    Lib_IntVector_Intrinsics_vec256_add64(a410,
      Lib_IntVector_Intrinsics_vec256_mul64(r20, f120));
  Lib_IntVector_Intrinsics_vec256
  a030 =
    Lib_IntVector_Intrinsics_vec256_add64(a020,
      Lib_IntVector_Intrinsics_vec256_mul64(r520, f130));
  Lib_IntVector_Intrinsics_vec256
  a130 =
    Lib_IntVector_Intrinsics_vec256_add64(a120,
      Lib_IntVector_Intrinsics_vec256_mul64(r530, f130));
  Lib_IntVector_Intrinsics_vec256
  a230 =
    Lib_IntVector_Intrinsics_vec256_add64(a220,
      Lib_IntVector_Intrinsics_vec256_mul64(r540, f130));
  Lib_IntVector_Intrinsics_vec256
  a330 =
    Lib_IntVector_Intrinsics_vec256_add64(a320,
      Lib_IntVector_Intrinsics_vec256_mul64(r0, f130));
  Lib_IntVector_Intrinsics_vec256
  a430 =
    Lib_IntVector_Intrinsics_vec256_add64(a420,
      Lib_IntVector_Intrinsics_vec256_mul64(r10, f130));
  Lib_IntVector_Intrinsics_vec256
  a040 =
    Lib_IntVector_Intrinsics_vec256_add64(a030,
      Lib_IntVector_Intrinsics_vec256_mul64(r510, f140));
  Lib_IntVector_Intrinsics_vec256
  a140 =
    Lib_IntVector_Intrinsics_vec256_add64(a130,
      Lib_IntVector_Intrinsics_vec256_mul64(r520, f140));
  Lib_IntVector_Intrinsics_vec256
  a240 =
    Lib_IntVector_Intrinsics_vec256_add64(a230,
      Lib_IntVector_Intrinsics_vec256_mul64(r530, f140));
  Lib_IntVector_Intrinsics_vec256
  a340 =
    Lib_IntVector_Intrinsics_vec256_add64(a330,
      Lib_IntVector_Intrinsics_vec256_mul64(r540, f140));
  Lib_IntVector_Intrinsics_vec256
  a440 =
    Lib_IntVector_Intrinsics_vec256_add64(a430,
      Lib_IntVector_Intrinsics_vec256_mul64(r0, f140));
  Lib_IntVector_Intrinsics_vec256 t00 = a040;
  Lib_IntVector_Intrinsics_vec256 t10 = a140;
  Lib_IntVector_Intrinsics_vec256 t20 = a240;
  Lib_IntVector_Intrinsics_vec256 t30 = a340;
  Lib_IntVector_Intrinsics_vec256 t40 = a440;
  Lib_IntVector_Intrinsics_vec256
  l0 = Lib_IntVector_Intrinsics_vec256_add64(t00, Lib_IntVector_Intrinsics_vec256_zero);
  Lib_IntVector_Intrinsics_vec256
  tmp00 =
    Lib_IntVector_Intrinsics_vec256_and(l0,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c00 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(t10, c00);
  Lib_IntVector_Intrinsics_vec256
  tmp10 =
    Lib_IntVector_Intrinsics_vec256_and(l1,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c10 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(t20, c10);
  Lib_IntVector_Intrinsics_vec256
  tmp20 =
    Lib_IntVector_Intrinsics_vec256_and(l2,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c20 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(t30, c20);
  Lib_IntVector_Intrinsics_vec256
  tmp30 =
    Lib_IntVector_Intrinsics_vec256_and(l3,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c30 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l4 = Lib_IntVector_Intrinsics_vec256_add64(t40, c30);
  Lib_IntVector_Intrinsics_vec256
  tmp40 =
    Lib_IntVector_Intrinsics_vec256_and(l4,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c40 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256
  l5 =
    Lib_IntVector_Intrinsics_vec256_add64(tmp00,
      Lib_IntVector_Intrinsics_vec256_smul64(c40, (uint64_t)5U));
  Lib_IntVector_Intrinsics_vec256
  tmp010 =
    Lib_IntVector_Intrinsics_vec256_and(l5,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c50 = Lib_IntVector_Intrinsics_vec256_shift_right64(l5, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 tmp11 = Lib_IntVector_Intrinsics_vec256_add64(tmp10, c50);
  Lib_IntVector_Intrinsics_vec256 o00 = tmp010;
  Lib_IntVector_Intrinsics_vec256 o10 = tmp11;
  Lib_IntVector_Intrinsics_vec256 o20 = tmp20;
  Lib_IntVector_Intrinsics_vec256 o30 = tmp30;
  Lib_IntVector_Intrinsics_vec256 o40 = tmp40;
  rn[0U] = o00;
  rn[1U] = o10;
  rn[2U] = o20;
  rn[3U] = o30;
  rn[4U] = o40;
  Lib_IntVector_Intrinsics_vec256 f201 = rn[0U];
  Lib_IntVector_Intrinsics_vec256 f211 = rn[1U];
  Lib_IntVector_Intrinsics_vec256 f221 = rn[2U];
  Lib_IntVector_Intrinsics_vec256 f231 = rn[3U];
  Lib_IntVector_Intrinsics_vec256 f241 = rn[4U];
  rn_5[0U] = Lib_IntVector_Intrinsics_vec256_smul64(f201, (uint64_t)5U);
  rn_5[1U] = Lib_IntVector_Intrinsics_vec256_smul64(f211, (uint64_t)5U);
  rn_5[2U] = Lib_IntVector_Intrinsics_vec256_smul64(f221, (uint64_t)5U);
  rn_5[3U] = Lib_IntVector_Intrinsics_vec256_smul64(f231, (uint64_t)5U);
  rn_5[4U] = Lib_IntVector_Intrinsics_vec256_smul64(f241, (uint64_t)5U);
  Lib_IntVector_Intrinsics_vec256 r00 = rn[0U];
  Lib_IntVector_Intrinsics_vec256 r1 = rn[1U];
  Lib_IntVector_Intrinsics_vec256 r2 = rn[2U];
  Lib_IntVector_Intrinsics_vec256 r3 = rn[3U];
  Lib_IntVector_Intrinsics_vec256 r4 = rn[4U];
  Lib_IntVector_Intrinsics_vec256 r51 = rn_5[1U];
  Lib_IntVector_Intrinsics_vec256 r52 = rn_5[2U];
  Lib_IntVector_Intrinsics_vec256 r53 = rn_5[3U];
  Lib_IntVector_Intrinsics_vec256 r54 = rn_5[4U];
  Lib_IntVector_Intrinsics_vec256 f10 = rn[0U];
  Lib_IntVector_Intrinsics_vec256 f11 = rn[1U];
  Lib_IntVector_Intrinsics_vec256 f12 = rn[2U];
  Lib_IntVector_Intrinsics_vec256 f13 = rn[3U];
  Lib_IntVector_Intrinsics_vec256 f14 = rn[4U];
  Lib_IntVector_Intrinsics_vec256 a0 = Lib_IntVector_Intrinsics_vec256_mul64(r00, f10);
  Lib_IntVector_Intrinsics_vec256 a1 = Lib_IntVector_Intrinsics_vec256_mul64(r1, f10);
  Lib_IntVector_Intrinsics_vec256 a2 = Lib_IntVector_Intrinsics_vec256_mul64(r2, f10);
  Lib_IntVector_Intrinsics_vec256 a3 = Lib_IntVector_Intrinsics_vec256_mul64(r3, f10);
  Lib_IntVector_Intrinsics_vec256 a4 = Lib_IntVector_Intrinsics_vec256_mul64(r4, f10);
  Lib_IntVector_Intrinsics_vec256
  a01 =
    Lib_IntVector_Intrinsics_vec256_add64(a0,
      Lib_IntVector_Intrinsics_vec256_mul64(r54, f11));
  Lib_IntVector_Intrinsics_vec256
  a11 =
    Lib_IntVector_Intrinsics_vec256_add64(a1,
      Lib_IntVector_Intrinsics_vec256_mul64(r00, f11));
  Lib_IntVector_Intrinsics_vec256
  a21 = Lib_IntVector_Intrinsics_vec256_add64(a2, Lib_IntVector_Intrinsics_vec256_mul64(r1, f11));
  Lib_IntVector_Intrinsics_vec256
  a31 = Lib_IntVector_Intrinsics_vec256_add64(a3, Lib_IntVector_Intrinsics_vec256_mul64(r2, f11));
  Lib_IntVector_Intrinsics_vec256
  a41 = Lib_IntVector_Intrinsics_vec256_add64(a4, Lib_IntVector_Intrinsics_vec256_mul64(r3, f11));
  Lib_IntVector_Intrinsics_vec256
  a02 =
    Lib_IntVector_Intrinsics_vec256_add64(a01,
      Lib_IntVector_Intrinsics_vec256_mul64(r53, f12));
  Lib_IntVector_Intrinsics_vec256
  a12 =
    Lib_IntVector_Intrinsics_vec256_add64(a11,
      Lib_IntVector_Intrinsics_vec256_mul64(r54, f12));
  Lib_IntVector_Intrinsics_vec256
  a22 =
    Lib_IntVector_Intrinsics_vec256_add64(a21,
      Lib_IntVector_Intrinsics_vec256_mul64(r00, f12));
  Lib_IntVector_Intrinsics_vec256
  a32 =
    Lib_IntVector_Intrinsics_vec256_add64(a31,
      Lib_IntVector_Intrinsics_vec256_mul64(r1, f12));
  Lib_IntVector_Intrinsics_vec256
  a42 =
    Lib_IntVector_Intrinsics_vec256_add64(a41,
      Lib_IntVector_Intrinsics_vec256_mul64(r2, f12));
  Lib_IntVector_Intrinsics_vec256
  a03 =
    Lib_IntVector_Intrinsics_vec256_add64(a02,
      Lib_IntVector_Intrinsics_vec256_mul64(r52, f13));
  Lib_IntVector_Intrinsics_vec256
  a13 =
    Lib_IntVector_Intrinsics_vec256_add64(a12,
      Lib_IntVector_Intrinsics_vec256_mul64(r53, f13));
  Lib_IntVector_Intrinsics_vec256
  a23 =
    Lib_IntVector_Intrinsics_vec256_add64(a22,
      Lib_IntVector_Intrinsics_vec256_mul64(r54, f13));
  Lib_IntVector_Intrinsics_vec256
  a33 =
    Lib_IntVector_Intrinsics_vec256_add64(a32,
      Lib_IntVector_Intrinsics_vec256_mul64(r00, f13));
  Lib_IntVector_Intrinsics_vec256
  a43 =
    Lib_IntVector_Intrinsics_vec256_add64(a42,
      Lib_IntVector_Intrinsics_vec256_mul64(r1, f13));
  Lib_IntVector_Intrinsics_vec256
  a04 =
    Lib_IntVector_Intrinsics_vec256_add64(a03,
      Lib_IntVector_Intrinsics_vec256_mul64(r51, f14));
  Lib_IntVector_Intrinsics_vec256
  a14 =
    Lib_IntVector_Intrinsics_vec256_add64(a13,
      Lib_IntVector_Intrinsics_vec256_mul64(r52, f14));
  Lib_IntVector_Intrinsics_vec256
  a24 =
    Lib_IntVector_Intrinsics_vec256_add64(a23,
      Lib_IntVector_Intrinsics_vec256_mul64(r53, f14));
  Lib_IntVector_Intrinsics_vec256
  a34 =
    Lib_IntVector_Intrinsics_vec256_add64(a33,
      Lib_IntVector_Intrinsics_vec256_mul64(r54, f14));
  Lib_IntVector_Intrinsics_vec256
  a44 =
    Lib_IntVector_Intrinsics_vec256_add64(a43,
      Lib_IntVector_Intrinsics_vec256_mul64(r00, f14));
  Lib_IntVector_Intrinsics_vec256 t0 = a04;
  Lib_IntVector_Intrinsics_vec256 t1 = a14;
  Lib_IntVector_Intrinsics_vec256 t2 = a24;
  Lib_IntVector_Intrinsics_vec256 t3 = a34;
  Lib_IntVector_Intrinsics_vec256 t4 = a44;
  Lib_IntVector_Intrinsics_vec256
  l = Lib_IntVector_Intrinsics_vec256_add64(t0, Lib_IntVector_Intrinsics_vec256_zero);
  Lib_IntVector_Intrinsics_vec256
  tmp0 =
    Lib_IntVector_Intrinsics_vec256_and(l,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l6 = Lib_IntVector_Intrinsics_vec256_add64(t1, c0);
  Lib_IntVector_Intrinsics_vec256
  tmp1 =
    Lib_IntVector_Intrinsics_vec256_and(l6,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l6, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l7 = Lib_IntVector_Intrinsics_vec256_add64(t2, c1);
  Lib_IntVector_Intrinsics_vec256
  tmp2 =
    Lib_IntVector_Intrinsics_vec256_and(l7,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l7, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l8 = Lib_IntVector_Intrinsics_vec256_add64(t3, c2);
  Lib_IntVector_Intrinsics_vec256
  tmp3 =
    Lib_IntVector_Intrinsics_vec256_and(l8,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l8, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l9 = Lib_IntVector_Intrinsics_vec256_add64(t4, c3);
  Lib_IntVector_Intrinsics_vec256
  tmp4 =
    Lib_IntVector_Intrinsics_vec256_and(l9,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l9, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256
  l10 =
    Lib_IntVector_Intrinsics_vec256_add64(tmp0,
      Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
  Lib_IntVector_Intrinsics_vec256
  tmp01 =
    Lib_IntVector_Intrinsics_vec256_and(l10,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l10, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 tmp110 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
  Lib_IntVector_Intrinsics_vec256 o0 = tmp01;
  Lib_IntVector_Intrinsics_vec256 o1 = tmp110;
  Lib_IntVector_Intrinsics_vec256 o2 = tmp2;
  Lib_IntVector_Intrinsics_vec256 o3 = tmp3;
  Lib_IntVector_Intrinsics_vec256 o4 = tmp4;
  rn[0U] = o0;
  rn[1U] = o1;
  rn[2U] = o2;
  rn[3U] = o3;
  rn[4U] = o4;
  Lib_IntVector_Intrinsics_vec256 f202 = rn[0U];
  Lib_IntVector_Intrinsics_vec256 f21 = rn[1U];
  Lib_IntVector_Intrinsics_vec256 f22 = rn[2U];
  Lib_IntVector_Intrinsics_vec256 f23 = rn[3U];
  Lib_IntVector_Intrinsics_vec256 f24 = rn[4U];
  rn_5[0U] = Lib_IntVector_Intrinsics_vec256_smul64(f202, (uint64_t)5U);
  rn_5[1U] = Lib_IntVector_Intrinsics_vec256_smul64(f21, (uint64_t)5U);
  rn_5[2U] = Lib_IntVector_Intrinsics_vec256_smul64(f22, (uint64_t)5U);
  rn_5[3U] = Lib_IntVector_Intrinsics_vec256_smul64(f23, (uint64_t)5U);
  rn_5[4U] = Lib_IntVector_Intrinsics_vec256_smul64(f24, (uint64_t)5U);
}

inline void
Hacl_Poly1305_256_poly1305_update(
  Lib_IntVector_Intrinsics_vec256 *ctx,
  uint32_t len1,
  uint8_t *text
)
{
  Lib_IntVector_Intrinsics_vec256 *pre = ctx + (uint32_t)5U;
  Lib_IntVector_Intrinsics_vec256 *acc = ctx;
  uint32_t sz_block = (uint32_t)64U;
  uint32_t len0 = len1 / sz_block * sz_block;
  uint8_t *t0 = text;
  if (len0 > (uint32_t)0U)
  {
    uint32_t bs = (uint32_t)64U;
    uint8_t *text0 = t0;
    KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec256), (uint32_t)5U);
    Lib_IntVector_Intrinsics_vec256 e5[5U];
    uint32_t _i;
    for (_i = 0U; _i < (uint32_t)5U; ++_i)
      e5[_i] = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256 lo00 = Lib_IntVector_Intrinsics_vec256_load_le(text0);
    Lib_IntVector_Intrinsics_vec256
    hi00 = Lib_IntVector_Intrinsics_vec256_load_le(text0 + (uint32_t)32U);
    Lib_IntVector_Intrinsics_vec256
    lo10 = Lib_IntVector_Intrinsics_vec256_interleave_low128(lo00, hi00);
    Lib_IntVector_Intrinsics_vec256
    hi10 = Lib_IntVector_Intrinsics_vec256_interleave_high128(lo00, hi00);
    Lib_IntVector_Intrinsics_vec256 lo20 = lo10;
    Lib_IntVector_Intrinsics_vec256 hi20 = hi10;
    Lib_IntVector_Intrinsics_vec256
    lo3 = Lib_IntVector_Intrinsics_vec256_interleave_low64(lo20, hi20);
    Lib_IntVector_Intrinsics_vec256
    hi3 = Lib_IntVector_Intrinsics_vec256_interleave_high64(lo20, hi20);
    Lib_IntVector_Intrinsics_vec256
    f00 =
      Lib_IntVector_Intrinsics_vec256_and(lo3,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f15 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(lo3,
          (uint32_t)26U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f25 =
      Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(lo3,
          (uint32_t)52U),
        Lib_IntVector_Intrinsics_vec256_shift_left64(Lib_IntVector_Intrinsics_vec256_and(hi3,
            Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffU)),
          (uint32_t)12U));
    Lib_IntVector_Intrinsics_vec256
    f30 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(hi3,
          (uint32_t)14U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f40 = Lib_IntVector_Intrinsics_vec256_shift_right64(hi3, (uint32_t)40U);
    Lib_IntVector_Intrinsics_vec256 f01 = f00;
    Lib_IntVector_Intrinsics_vec256 f16 = f15;
    Lib_IntVector_Intrinsics_vec256 f26 = f25;
    Lib_IntVector_Intrinsics_vec256 f31 = f30;
    Lib_IntVector_Intrinsics_vec256 f41 = f40;
    e5[0U] = f01;
    e5[1U] = f16;
    e5[2U] = f26;
    e5[3U] = f31;
    e5[4U] = f41;
    uint64_t b = (uint64_t)0x1000000U;
    Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_load64(b);
    Lib_IntVector_Intrinsics_vec256 f42 = e5[4U];
    e5[4U] = Lib_IntVector_Intrinsics_vec256_or(f42, mask);
    Lib_IntVector_Intrinsics_vec256 acc0 = acc[0U];
    Lib_IntVector_Intrinsics_vec256 acc1 = acc[1U];
    Lib_IntVector_Intrinsics_vec256 acc2 = acc[2U];
    Lib_IntVector_Intrinsics_vec256 acc3 = acc[3U];
    Lib_IntVector_Intrinsics_vec256 acc4 = acc[4U];
    Lib_IntVector_Intrinsics_vec256 e0 = e5[0U];
    Lib_IntVector_Intrinsics_vec256 e1 = e5[1U];
    Lib_IntVector_Intrinsics_vec256 e2 = e5[2U];
    Lib_IntVector_Intrinsics_vec256 e3 = e5[3U];
    Lib_IntVector_Intrinsics_vec256 e4 = e5[4U];
    Lib_IntVector_Intrinsics_vec256 r00 = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256 r15 = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256 r25 = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256 r35 = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256 r45 = Lib_IntVector_Intrinsics_vec256_zero;
    Lib_IntVector_Intrinsics_vec256
    r01 =
      Lib_IntVector_Intrinsics_vec256_insert64(r00,
        Lib_IntVector_Intrinsics_vec256_extract64(acc0, (uint32_t)0U),
        (uint32_t)0U);
    Lib_IntVector_Intrinsics_vec256
    r110 =
      Lib_IntVector_Intrinsics_vec256_insert64(r15,
        Lib_IntVector_Intrinsics_vec256_extract64(acc1, (uint32_t)0U),
        (uint32_t)0U);
    Lib_IntVector_Intrinsics_vec256
    r210 =
      Lib_IntVector_Intrinsics_vec256_insert64(r25,
        Lib_IntVector_Intrinsics_vec256_extract64(acc2, (uint32_t)0U),
        (uint32_t)0U);
    Lib_IntVector_Intrinsics_vec256
    r310 =
      Lib_IntVector_Intrinsics_vec256_insert64(r35,
        Lib_IntVector_Intrinsics_vec256_extract64(acc3, (uint32_t)0U),
        (uint32_t)0U);
    Lib_IntVector_Intrinsics_vec256
    r410 =
      Lib_IntVector_Intrinsics_vec256_insert64(r45,
        Lib_IntVector_Intrinsics_vec256_extract64(acc4, (uint32_t)0U),
        (uint32_t)0U);
    Lib_IntVector_Intrinsics_vec256 f02 = Lib_IntVector_Intrinsics_vec256_add64(r01, e0);
    Lib_IntVector_Intrinsics_vec256 f17 = Lib_IntVector_Intrinsics_vec256_add64(r110, e1);
    Lib_IntVector_Intrinsics_vec256 f27 = Lib_IntVector_Intrinsics_vec256_add64(r210, e2);
    Lib_IntVector_Intrinsics_vec256 f32 = Lib_IntVector_Intrinsics_vec256_add64(r310, e3);
    Lib_IntVector_Intrinsics_vec256 f43 = Lib_IntVector_Intrinsics_vec256_add64(r410, e4);
    Lib_IntVector_Intrinsics_vec256 acc01 = f02;
    Lib_IntVector_Intrinsics_vec256 acc11 = f17;
    Lib_IntVector_Intrinsics_vec256 acc21 = f27;
    Lib_IntVector_Intrinsics_vec256 acc31 = f32;
    Lib_IntVector_Intrinsics_vec256 acc41 = f43;
    acc[0U] = acc01;
    acc[1U] = acc11;
    acc[2U] = acc21;
    acc[3U] = acc31;
    acc[4U] = acc41;
    uint32_t len11 = len0 - bs;
    uint8_t *text1 = t0 + bs;
    uint32_t nb = len11 / bs;
    uint32_t i;
    for (i = (uint32_t)0U; i < nb; i = i + (uint32_t)1U)
    {
      uint8_t *block = text1 + i * bs;
      KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec256), (uint32_t)5U);
      Lib_IntVector_Intrinsics_vec256 e[5U];
      uint32_t _i;
      for (_i = 0U; _i < (uint32_t)5U; ++_i)
        e[_i] = Lib_IntVector_Intrinsics_vec256_zero;
      Lib_IntVector_Intrinsics_vec256 lo0 = Lib_IntVector_Intrinsics_vec256_load_le(block);
      Lib_IntVector_Intrinsics_vec256
      hi0 = Lib_IntVector_Intrinsics_vec256_load_le(block + (uint32_t)32U);
      Lib_IntVector_Intrinsics_vec256
      lo1 = Lib_IntVector_Intrinsics_vec256_interleave_low128(lo0, hi0);
      Lib_IntVector_Intrinsics_vec256
      hi1 = Lib_IntVector_Intrinsics_vec256_interleave_high128(lo0, hi0);
      Lib_IntVector_Intrinsics_vec256 lo2 = lo1;
      Lib_IntVector_Intrinsics_vec256 hi2 = hi1;
      Lib_IntVector_Intrinsics_vec256
      lo = Lib_IntVector_Intrinsics_vec256_interleave_low64(lo2, hi2);
      Lib_IntVector_Intrinsics_vec256
      hi = Lib_IntVector_Intrinsics_vec256_interleave_high64(lo2, hi2);
      Lib_IntVector_Intrinsics_vec256
      f00 =
        Lib_IntVector_Intrinsics_vec256_and(lo,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      f15 =
        Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(lo,
            (uint32_t)26U),
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      f25 =
        Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(lo,
            (uint32_t)52U),
          Lib_IntVector_Intrinsics_vec256_shift_left64(Lib_IntVector_Intrinsics_vec256_and(hi,
              Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffU)),
            (uint32_t)12U));
      Lib_IntVector_Intrinsics_vec256
      f30 =
        Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(hi,
            (uint32_t)14U),
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      f40 = Lib_IntVector_Intrinsics_vec256_shift_right64(hi, (uint32_t)40U);
      Lib_IntVector_Intrinsics_vec256 f0 = f00;
      Lib_IntVector_Intrinsics_vec256 f1 = f15;
      Lib_IntVector_Intrinsics_vec256 f2 = f25;
      Lib_IntVector_Intrinsics_vec256 f3 = f30;
      Lib_IntVector_Intrinsics_vec256 f41 = f40;
      e[0U] = f0;
      e[1U] = f1;
      e[2U] = f2;
      e[3U] = f3;
      e[4U] = f41;
      uint64_t b = (uint64_t)0x1000000U;
      Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_load64(b);
      Lib_IntVector_Intrinsics_vec256 f4 = e[4U];
      e[4U] = Lib_IntVector_Intrinsics_vec256_or(f4, mask);
      Lib_IntVector_Intrinsics_vec256 *rn = pre + (uint32_t)10U;
      Lib_IntVector_Intrinsics_vec256 *rn5 = pre + (uint32_t)15U;
      Lib_IntVector_Intrinsics_vec256 r0 = rn[0U];
      Lib_IntVector_Intrinsics_vec256 r1 = rn[1U];
      Lib_IntVector_Intrinsics_vec256 r2 = rn[2U];
      Lib_IntVector_Intrinsics_vec256 r3 = rn[3U];
      Lib_IntVector_Intrinsics_vec256 r4 = rn[4U];
      Lib_IntVector_Intrinsics_vec256 r51 = rn5[1U];
      Lib_IntVector_Intrinsics_vec256 r52 = rn5[2U];
      Lib_IntVector_Intrinsics_vec256 r53 = rn5[3U];
      Lib_IntVector_Intrinsics_vec256 r54 = rn5[4U];
      Lib_IntVector_Intrinsics_vec256 f10 = acc[0U];
      Lib_IntVector_Intrinsics_vec256 f110 = acc[1U];
      Lib_IntVector_Intrinsics_vec256 f120 = acc[2U];
      Lib_IntVector_Intrinsics_vec256 f130 = acc[3U];
      Lib_IntVector_Intrinsics_vec256 f140 = acc[4U];
      Lib_IntVector_Intrinsics_vec256 a0 = Lib_IntVector_Intrinsics_vec256_mul64(r0, f10);
      Lib_IntVector_Intrinsics_vec256 a1 = Lib_IntVector_Intrinsics_vec256_mul64(r1, f10);
      Lib_IntVector_Intrinsics_vec256 a2 = Lib_IntVector_Intrinsics_vec256_mul64(r2, f10);
      Lib_IntVector_Intrinsics_vec256 a3 = Lib_IntVector_Intrinsics_vec256_mul64(r3, f10);
      Lib_IntVector_Intrinsics_vec256 a4 = Lib_IntVector_Intrinsics_vec256_mul64(r4, f10);
      Lib_IntVector_Intrinsics_vec256
      a01 =
        Lib_IntVector_Intrinsics_vec256_add64(a0,
          Lib_IntVector_Intrinsics_vec256_mul64(r54, f110));
      Lib_IntVector_Intrinsics_vec256
      a11 =
        Lib_IntVector_Intrinsics_vec256_add64(a1,
          Lib_IntVector_Intrinsics_vec256_mul64(r0, f110));
      Lib_IntVector_Intrinsics_vec256
      a21 =
        Lib_IntVector_Intrinsics_vec256_add64(a2,
          Lib_IntVector_Intrinsics_vec256_mul64(r1, f110));
      Lib_IntVector_Intrinsics_vec256
      a31 =
        Lib_IntVector_Intrinsics_vec256_add64(a3,
          Lib_IntVector_Intrinsics_vec256_mul64(r2, f110));
      Lib_IntVector_Intrinsics_vec256
      a41 =
        Lib_IntVector_Intrinsics_vec256_add64(a4,
          Lib_IntVector_Intrinsics_vec256_mul64(r3, f110));
      Lib_IntVector_Intrinsics_vec256
      a02 =
        Lib_IntVector_Intrinsics_vec256_add64(a01,
          Lib_IntVector_Intrinsics_vec256_mul64(r53, f120));
      Lib_IntVector_Intrinsics_vec256
      a12 =
        Lib_IntVector_Intrinsics_vec256_add64(a11,
          Lib_IntVector_Intrinsics_vec256_mul64(r54, f120));
      Lib_IntVector_Intrinsics_vec256
      a22 =
        Lib_IntVector_Intrinsics_vec256_add64(a21,
          Lib_IntVector_Intrinsics_vec256_mul64(r0, f120));
      Lib_IntVector_Intrinsics_vec256
      a32 =
        Lib_IntVector_Intrinsics_vec256_add64(a31,
          Lib_IntVector_Intrinsics_vec256_mul64(r1, f120));
      Lib_IntVector_Intrinsics_vec256
      a42 =
        Lib_IntVector_Intrinsics_vec256_add64(a41,
          Lib_IntVector_Intrinsics_vec256_mul64(r2, f120));
      Lib_IntVector_Intrinsics_vec256
      a03 =
        Lib_IntVector_Intrinsics_vec256_add64(a02,
          Lib_IntVector_Intrinsics_vec256_mul64(r52, f130));
      Lib_IntVector_Intrinsics_vec256
      a13 =
        Lib_IntVector_Intrinsics_vec256_add64(a12,
          Lib_IntVector_Intrinsics_vec256_mul64(r53, f130));
      Lib_IntVector_Intrinsics_vec256
      a23 =
        Lib_IntVector_Intrinsics_vec256_add64(a22,
          Lib_IntVector_Intrinsics_vec256_mul64(r54, f130));
      Lib_IntVector_Intrinsics_vec256
      a33 =
        Lib_IntVector_Intrinsics_vec256_add64(a32,
          Lib_IntVector_Intrinsics_vec256_mul64(r0, f130));
      Lib_IntVector_Intrinsics_vec256
      a43 =
        Lib_IntVector_Intrinsics_vec256_add64(a42,
          Lib_IntVector_Intrinsics_vec256_mul64(r1, f130));
      Lib_IntVector_Intrinsics_vec256
      a04 =
        Lib_IntVector_Intrinsics_vec256_add64(a03,
          Lib_IntVector_Intrinsics_vec256_mul64(r51, f140));
      Lib_IntVector_Intrinsics_vec256
      a14 =
        Lib_IntVector_Intrinsics_vec256_add64(a13,
          Lib_IntVector_Intrinsics_vec256_mul64(r52, f140));
      Lib_IntVector_Intrinsics_vec256
      a24 =
        Lib_IntVector_Intrinsics_vec256_add64(a23,
          Lib_IntVector_Intrinsics_vec256_mul64(r53, f140));
      Lib_IntVector_Intrinsics_vec256
      a34 =
        Lib_IntVector_Intrinsics_vec256_add64(a33,
          Lib_IntVector_Intrinsics_vec256_mul64(r54, f140));
      Lib_IntVector_Intrinsics_vec256
      a44 =
        Lib_IntVector_Intrinsics_vec256_add64(a43,
          Lib_IntVector_Intrinsics_vec256_mul64(r0, f140));
      Lib_IntVector_Intrinsics_vec256 t01 = a04;
      Lib_IntVector_Intrinsics_vec256 t1 = a14;
      Lib_IntVector_Intrinsics_vec256 t2 = a24;
      Lib_IntVector_Intrinsics_vec256 t3 = a34;
      Lib_IntVector_Intrinsics_vec256 t4 = a44;
      Lib_IntVector_Intrinsics_vec256
      l = Lib_IntVector_Intrinsics_vec256_add64(t01, Lib_IntVector_Intrinsics_vec256_zero);
      Lib_IntVector_Intrinsics_vec256
      tmp0 =
        Lib_IntVector_Intrinsics_vec256_and(l,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256 l0 = Lib_IntVector_Intrinsics_vec256_add64(t1, c0);
      Lib_IntVector_Intrinsics_vec256
      tmp1 =
        Lib_IntVector_Intrinsics_vec256_and(l0,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(t2, c1);
      Lib_IntVector_Intrinsics_vec256
      tmp2 =
        Lib_IntVector_Intrinsics_vec256_and(l1,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(t3, c2);
      Lib_IntVector_Intrinsics_vec256
      tmp3 =
        Lib_IntVector_Intrinsics_vec256_and(l2,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(t4, c3);
      Lib_IntVector_Intrinsics_vec256
      tmp4 =
        Lib_IntVector_Intrinsics_vec256_and(l3,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256
      l4 =
        Lib_IntVector_Intrinsics_vec256_add64(tmp0,
          Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
      Lib_IntVector_Intrinsics_vec256
      tmp01 =
        Lib_IntVector_Intrinsics_vec256_and(l4,
          Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
      Lib_IntVector_Intrinsics_vec256
      c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
      Lib_IntVector_Intrinsics_vec256 tmp11 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
      Lib_IntVector_Intrinsics_vec256 o00 = tmp01;
      Lib_IntVector_Intrinsics_vec256 o10 = tmp11;
      Lib_IntVector_Intrinsics_vec256 o20 = tmp2;
      Lib_IntVector_Intrinsics_vec256 o30 = tmp3;
      Lib_IntVector_Intrinsics_vec256 o40 = tmp4;
      acc[0U] = o00;
      acc[1U] = o10;
      acc[2U] = o20;
      acc[3U] = o30;
      acc[4U] = o40;
      Lib_IntVector_Intrinsics_vec256 f100 = acc[0U];
      Lib_IntVector_Intrinsics_vec256 f11 = acc[1U];
      Lib_IntVector_Intrinsics_vec256 f12 = acc[2U];
      Lib_IntVector_Intrinsics_vec256 f13 = acc[3U];
      Lib_IntVector_Intrinsics_vec256 f14 = acc[4U];
      Lib_IntVector_Intrinsics_vec256 f20 = e[0U];
      Lib_IntVector_Intrinsics_vec256 f21 = e[1U];
      Lib_IntVector_Intrinsics_vec256 f22 = e[2U];
      Lib_IntVector_Intrinsics_vec256 f23 = e[3U];
      Lib_IntVector_Intrinsics_vec256 f24 = e[4U];
      Lib_IntVector_Intrinsics_vec256 o0 = Lib_IntVector_Intrinsics_vec256_add64(f100, f20);
      Lib_IntVector_Intrinsics_vec256 o1 = Lib_IntVector_Intrinsics_vec256_add64(f11, f21);
      Lib_IntVector_Intrinsics_vec256 o2 = Lib_IntVector_Intrinsics_vec256_add64(f12, f22);
      Lib_IntVector_Intrinsics_vec256 o3 = Lib_IntVector_Intrinsics_vec256_add64(f13, f23);
      Lib_IntVector_Intrinsics_vec256 o4 = Lib_IntVector_Intrinsics_vec256_add64(f14, f24);
      acc[0U] = o0;
      acc[1U] = o1;
      acc[2U] = o2;
      acc[3U] = o3;
      acc[4U] = o4;
    }
    Lib_IntVector_Intrinsics_vec256 *r = pre;
    Lib_IntVector_Intrinsics_vec256 *r_5 = pre + (uint32_t)5U;
    Lib_IntVector_Intrinsics_vec256 *r4 = pre + (uint32_t)10U;
    Lib_IntVector_Intrinsics_vec256 a0 = acc[0U];
    Lib_IntVector_Intrinsics_vec256 a1 = acc[1U];
    Lib_IntVector_Intrinsics_vec256 a2 = acc[2U];
    Lib_IntVector_Intrinsics_vec256 a3 = acc[3U];
    Lib_IntVector_Intrinsics_vec256 a4 = acc[4U];
    Lib_IntVector_Intrinsics_vec256 r10 = r[0U];
    Lib_IntVector_Intrinsics_vec256 r11 = r[1U];
    Lib_IntVector_Intrinsics_vec256 r12 = r[2U];
    Lib_IntVector_Intrinsics_vec256 r13 = r[3U];
    Lib_IntVector_Intrinsics_vec256 r14 = r[4U];
    Lib_IntVector_Intrinsics_vec256 r151 = r_5[1U];
    Lib_IntVector_Intrinsics_vec256 r152 = r_5[2U];
    Lib_IntVector_Intrinsics_vec256 r153 = r_5[3U];
    Lib_IntVector_Intrinsics_vec256 r154 = r_5[4U];
    Lib_IntVector_Intrinsics_vec256 r40 = r4[0U];
    Lib_IntVector_Intrinsics_vec256 r41 = r4[1U];
    Lib_IntVector_Intrinsics_vec256 r42 = r4[2U];
    Lib_IntVector_Intrinsics_vec256 r43 = r4[3U];
    Lib_IntVector_Intrinsics_vec256 r44 = r4[4U];
    Lib_IntVector_Intrinsics_vec256 a010 = Lib_IntVector_Intrinsics_vec256_mul64(r10, r10);
    Lib_IntVector_Intrinsics_vec256 a110 = Lib_IntVector_Intrinsics_vec256_mul64(r11, r10);
    Lib_IntVector_Intrinsics_vec256 a210 = Lib_IntVector_Intrinsics_vec256_mul64(r12, r10);
    Lib_IntVector_Intrinsics_vec256 a310 = Lib_IntVector_Intrinsics_vec256_mul64(r13, r10);
    Lib_IntVector_Intrinsics_vec256 a410 = Lib_IntVector_Intrinsics_vec256_mul64(r14, r10);
    Lib_IntVector_Intrinsics_vec256
    a020 =
      Lib_IntVector_Intrinsics_vec256_add64(a010,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r11));
    Lib_IntVector_Intrinsics_vec256
    a120 =
      Lib_IntVector_Intrinsics_vec256_add64(a110,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r11));
    Lib_IntVector_Intrinsics_vec256
    a220 =
      Lib_IntVector_Intrinsics_vec256_add64(a210,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r11));
    Lib_IntVector_Intrinsics_vec256
    a320 =
      Lib_IntVector_Intrinsics_vec256_add64(a310,
        Lib_IntVector_Intrinsics_vec256_mul64(r12, r11));
    Lib_IntVector_Intrinsics_vec256
    a420 =
      Lib_IntVector_Intrinsics_vec256_add64(a410,
        Lib_IntVector_Intrinsics_vec256_mul64(r13, r11));
    Lib_IntVector_Intrinsics_vec256
    a030 =
      Lib_IntVector_Intrinsics_vec256_add64(a020,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r12));
    Lib_IntVector_Intrinsics_vec256
    a130 =
      Lib_IntVector_Intrinsics_vec256_add64(a120,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r12));
    Lib_IntVector_Intrinsics_vec256
    a230 =
      Lib_IntVector_Intrinsics_vec256_add64(a220,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r12));
    Lib_IntVector_Intrinsics_vec256
    a330 =
      Lib_IntVector_Intrinsics_vec256_add64(a320,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r12));
    Lib_IntVector_Intrinsics_vec256
    a430 =
      Lib_IntVector_Intrinsics_vec256_add64(a420,
        Lib_IntVector_Intrinsics_vec256_mul64(r12, r12));
    Lib_IntVector_Intrinsics_vec256
    a040 =
      Lib_IntVector_Intrinsics_vec256_add64(a030,
        Lib_IntVector_Intrinsics_vec256_mul64(r152, r13));
    Lib_IntVector_Intrinsics_vec256
    a140 =
      Lib_IntVector_Intrinsics_vec256_add64(a130,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r13));
    Lib_IntVector_Intrinsics_vec256
    a240 =
      Lib_IntVector_Intrinsics_vec256_add64(a230,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r13));
    Lib_IntVector_Intrinsics_vec256
    a340 =
      Lib_IntVector_Intrinsics_vec256_add64(a330,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r13));
    Lib_IntVector_Intrinsics_vec256
    a440 =
      Lib_IntVector_Intrinsics_vec256_add64(a430,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r13));
    Lib_IntVector_Intrinsics_vec256
    a050 =
      Lib_IntVector_Intrinsics_vec256_add64(a040,
        Lib_IntVector_Intrinsics_vec256_mul64(r151, r14));
    Lib_IntVector_Intrinsics_vec256
    a150 =
      Lib_IntVector_Intrinsics_vec256_add64(a140,
        Lib_IntVector_Intrinsics_vec256_mul64(r152, r14));
    Lib_IntVector_Intrinsics_vec256
    a250 =
      Lib_IntVector_Intrinsics_vec256_add64(a240,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r14));
    Lib_IntVector_Intrinsics_vec256
    a350 =
      Lib_IntVector_Intrinsics_vec256_add64(a340,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r14));
    Lib_IntVector_Intrinsics_vec256
    a450 =
      Lib_IntVector_Intrinsics_vec256_add64(a440,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r14));
    Lib_IntVector_Intrinsics_vec256 t010 = a050;
    Lib_IntVector_Intrinsics_vec256 t10 = a150;
    Lib_IntVector_Intrinsics_vec256 t20 = a250;
    Lib_IntVector_Intrinsics_vec256 t30 = a350;
    Lib_IntVector_Intrinsics_vec256 t40 = a450;
    Lib_IntVector_Intrinsics_vec256
    l0 = Lib_IntVector_Intrinsics_vec256_add64(t010, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp00 =
      Lib_IntVector_Intrinsics_vec256_and(l0,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c00 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(t10, c00);
    Lib_IntVector_Intrinsics_vec256
    tmp10 =
      Lib_IntVector_Intrinsics_vec256_and(l1,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c10 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(t20, c10);
    Lib_IntVector_Intrinsics_vec256
    tmp20 =
      Lib_IntVector_Intrinsics_vec256_and(l2,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c20 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(t30, c20);
    Lib_IntVector_Intrinsics_vec256
    tmp30 =
      Lib_IntVector_Intrinsics_vec256_and(l3,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c30 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l4 = Lib_IntVector_Intrinsics_vec256_add64(t40, c30);
    Lib_IntVector_Intrinsics_vec256
    tmp40 =
      Lib_IntVector_Intrinsics_vec256_and(l4,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c40 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l5 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp00,
        Lib_IntVector_Intrinsics_vec256_smul64(c40, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp010 =
      Lib_IntVector_Intrinsics_vec256_and(l5,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c50 = Lib_IntVector_Intrinsics_vec256_shift_right64(l5, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 tmp11 = Lib_IntVector_Intrinsics_vec256_add64(tmp10, c50);
    Lib_IntVector_Intrinsics_vec256 r20 = tmp010;
    Lib_IntVector_Intrinsics_vec256 r21 = tmp11;
    Lib_IntVector_Intrinsics_vec256 r22 = tmp20;
    Lib_IntVector_Intrinsics_vec256 r23 = tmp30;
    Lib_IntVector_Intrinsics_vec256 r24 = tmp40;
    Lib_IntVector_Intrinsics_vec256 a011 = Lib_IntVector_Intrinsics_vec256_mul64(r10, r20);
    Lib_IntVector_Intrinsics_vec256 a111 = Lib_IntVector_Intrinsics_vec256_mul64(r11, r20);
    Lib_IntVector_Intrinsics_vec256 a211 = Lib_IntVector_Intrinsics_vec256_mul64(r12, r20);
    Lib_IntVector_Intrinsics_vec256 a311 = Lib_IntVector_Intrinsics_vec256_mul64(r13, r20);
    Lib_IntVector_Intrinsics_vec256 a411 = Lib_IntVector_Intrinsics_vec256_mul64(r14, r20);
    Lib_IntVector_Intrinsics_vec256
    a021 =
      Lib_IntVector_Intrinsics_vec256_add64(a011,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r21));
    Lib_IntVector_Intrinsics_vec256
    a121 =
      Lib_IntVector_Intrinsics_vec256_add64(a111,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r21));
    Lib_IntVector_Intrinsics_vec256
    a221 =
      Lib_IntVector_Intrinsics_vec256_add64(a211,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r21));
    Lib_IntVector_Intrinsics_vec256
    a321 =
      Lib_IntVector_Intrinsics_vec256_add64(a311,
        Lib_IntVector_Intrinsics_vec256_mul64(r12, r21));
    Lib_IntVector_Intrinsics_vec256
    a421 =
      Lib_IntVector_Intrinsics_vec256_add64(a411,
        Lib_IntVector_Intrinsics_vec256_mul64(r13, r21));
    Lib_IntVector_Intrinsics_vec256
    a031 =
      Lib_IntVector_Intrinsics_vec256_add64(a021,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r22));
    Lib_IntVector_Intrinsics_vec256
    a131 =
      Lib_IntVector_Intrinsics_vec256_add64(a121,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r22));
    Lib_IntVector_Intrinsics_vec256
    a231 =
      Lib_IntVector_Intrinsics_vec256_add64(a221,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r22));
    Lib_IntVector_Intrinsics_vec256
    a331 =
      Lib_IntVector_Intrinsics_vec256_add64(a321,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r22));
    Lib_IntVector_Intrinsics_vec256
    a431 =
      Lib_IntVector_Intrinsics_vec256_add64(a421,
        Lib_IntVector_Intrinsics_vec256_mul64(r12, r22));
    Lib_IntVector_Intrinsics_vec256
    a041 =
      Lib_IntVector_Intrinsics_vec256_add64(a031,
        Lib_IntVector_Intrinsics_vec256_mul64(r152, r23));
    Lib_IntVector_Intrinsics_vec256
    a141 =
      Lib_IntVector_Intrinsics_vec256_add64(a131,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r23));
    Lib_IntVector_Intrinsics_vec256
    a241 =
      Lib_IntVector_Intrinsics_vec256_add64(a231,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r23));
    Lib_IntVector_Intrinsics_vec256
    a341 =
      Lib_IntVector_Intrinsics_vec256_add64(a331,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r23));
    Lib_IntVector_Intrinsics_vec256
    a441 =
      Lib_IntVector_Intrinsics_vec256_add64(a431,
        Lib_IntVector_Intrinsics_vec256_mul64(r11, r23));
    Lib_IntVector_Intrinsics_vec256
    a051 =
      Lib_IntVector_Intrinsics_vec256_add64(a041,
        Lib_IntVector_Intrinsics_vec256_mul64(r151, r24));
    Lib_IntVector_Intrinsics_vec256
    a151 =
      Lib_IntVector_Intrinsics_vec256_add64(a141,
        Lib_IntVector_Intrinsics_vec256_mul64(r152, r24));
    Lib_IntVector_Intrinsics_vec256
    a251 =
      Lib_IntVector_Intrinsics_vec256_add64(a241,
        Lib_IntVector_Intrinsics_vec256_mul64(r153, r24));
    Lib_IntVector_Intrinsics_vec256
    a351 =
      Lib_IntVector_Intrinsics_vec256_add64(a341,
        Lib_IntVector_Intrinsics_vec256_mul64(r154, r24));
    Lib_IntVector_Intrinsics_vec256
    a451 =
      Lib_IntVector_Intrinsics_vec256_add64(a441,
        Lib_IntVector_Intrinsics_vec256_mul64(r10, r24));
    Lib_IntVector_Intrinsics_vec256 t011 = a051;
    Lib_IntVector_Intrinsics_vec256 t11 = a151;
    Lib_IntVector_Intrinsics_vec256 t21 = a251;
    Lib_IntVector_Intrinsics_vec256 t31 = a351;
    Lib_IntVector_Intrinsics_vec256 t41 = a451;
    Lib_IntVector_Intrinsics_vec256
    l6 = Lib_IntVector_Intrinsics_vec256_add64(t011, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp02 =
      Lib_IntVector_Intrinsics_vec256_and(l6,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c01 = Lib_IntVector_Intrinsics_vec256_shift_right64(l6, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l7 = Lib_IntVector_Intrinsics_vec256_add64(t11, c01);
    Lib_IntVector_Intrinsics_vec256
    tmp12 =
      Lib_IntVector_Intrinsics_vec256_and(l7,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c11 = Lib_IntVector_Intrinsics_vec256_shift_right64(l7, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l8 = Lib_IntVector_Intrinsics_vec256_add64(t21, c11);
    Lib_IntVector_Intrinsics_vec256
    tmp21 =
      Lib_IntVector_Intrinsics_vec256_and(l8,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c21 = Lib_IntVector_Intrinsics_vec256_shift_right64(l8, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l9 = Lib_IntVector_Intrinsics_vec256_add64(t31, c21);
    Lib_IntVector_Intrinsics_vec256
    tmp31 =
      Lib_IntVector_Intrinsics_vec256_and(l9,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c31 = Lib_IntVector_Intrinsics_vec256_shift_right64(l9, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l10 = Lib_IntVector_Intrinsics_vec256_add64(t41, c31);
    Lib_IntVector_Intrinsics_vec256
    tmp41 =
      Lib_IntVector_Intrinsics_vec256_and(l10,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c41 = Lib_IntVector_Intrinsics_vec256_shift_right64(l10, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l11 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp02,
        Lib_IntVector_Intrinsics_vec256_smul64(c41, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp011 =
      Lib_IntVector_Intrinsics_vec256_and(l11,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c51 = Lib_IntVector_Intrinsics_vec256_shift_right64(l11, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 tmp110 = Lib_IntVector_Intrinsics_vec256_add64(tmp12, c51);
    Lib_IntVector_Intrinsics_vec256 r30 = tmp011;
    Lib_IntVector_Intrinsics_vec256 r31 = tmp110;
    Lib_IntVector_Intrinsics_vec256 r32 = tmp21;
    Lib_IntVector_Intrinsics_vec256 r33 = tmp31;
    Lib_IntVector_Intrinsics_vec256 r34 = tmp41;
    Lib_IntVector_Intrinsics_vec256
    v12120 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r20, r10);
    Lib_IntVector_Intrinsics_vec256
    v34340 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r40, r30);
    Lib_IntVector_Intrinsics_vec256
    r12340 = Lib_IntVector_Intrinsics_vec256_interleave_low128(v34340, v12120);
    Lib_IntVector_Intrinsics_vec256
    v12121 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r21, r11);
    Lib_IntVector_Intrinsics_vec256
    v34341 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r41, r31);
    Lib_IntVector_Intrinsics_vec256
    r12341 = Lib_IntVector_Intrinsics_vec256_interleave_low128(v34341, v12121);
    Lib_IntVector_Intrinsics_vec256
    v12122 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r22, r12);
    Lib_IntVector_Intrinsics_vec256
    v34342 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r42, r32);
    Lib_IntVector_Intrinsics_vec256
    r12342 = Lib_IntVector_Intrinsics_vec256_interleave_low128(v34342, v12122);
    Lib_IntVector_Intrinsics_vec256
    v12123 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r23, r13);
    Lib_IntVector_Intrinsics_vec256
    v34343 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r43, r33);
    Lib_IntVector_Intrinsics_vec256
    r12343 = Lib_IntVector_Intrinsics_vec256_interleave_low128(v34343, v12123);
    Lib_IntVector_Intrinsics_vec256
    v12124 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r24, r14);
    Lib_IntVector_Intrinsics_vec256
    v34344 = Lib_IntVector_Intrinsics_vec256_interleave_low64(r44, r34);
    Lib_IntVector_Intrinsics_vec256
    r12344 = Lib_IntVector_Intrinsics_vec256_interleave_low128(v34344, v12124);
    Lib_IntVector_Intrinsics_vec256
    r123450 = Lib_IntVector_Intrinsics_vec256_smul64(r12340, (uint64_t)5U);
    Lib_IntVector_Intrinsics_vec256
    r123451 = Lib_IntVector_Intrinsics_vec256_smul64(r12341, (uint64_t)5U);
    Lib_IntVector_Intrinsics_vec256
    r123452 = Lib_IntVector_Intrinsics_vec256_smul64(r12342, (uint64_t)5U);
    Lib_IntVector_Intrinsics_vec256
    r123453 = Lib_IntVector_Intrinsics_vec256_smul64(r12343, (uint64_t)5U);
    Lib_IntVector_Intrinsics_vec256
    r123454 = Lib_IntVector_Intrinsics_vec256_smul64(r12344, (uint64_t)5U);
    Lib_IntVector_Intrinsics_vec256 a01 = Lib_IntVector_Intrinsics_vec256_mul64(r12340, a0);
    Lib_IntVector_Intrinsics_vec256 a11 = Lib_IntVector_Intrinsics_vec256_mul64(r12341, a0);
    Lib_IntVector_Intrinsics_vec256 a21 = Lib_IntVector_Intrinsics_vec256_mul64(r12342, a0);
    Lib_IntVector_Intrinsics_vec256 a31 = Lib_IntVector_Intrinsics_vec256_mul64(r12343, a0);
    Lib_IntVector_Intrinsics_vec256 a41 = Lib_IntVector_Intrinsics_vec256_mul64(r12344, a0);
    Lib_IntVector_Intrinsics_vec256
    a02 =
      Lib_IntVector_Intrinsics_vec256_add64(a01,
        Lib_IntVector_Intrinsics_vec256_mul64(r123454, a1));
    Lib_IntVector_Intrinsics_vec256
    a12 =
      Lib_IntVector_Intrinsics_vec256_add64(a11,
        Lib_IntVector_Intrinsics_vec256_mul64(r12340, a1));
    Lib_IntVector_Intrinsics_vec256
    a22 =
      Lib_IntVector_Intrinsics_vec256_add64(a21,
        Lib_IntVector_Intrinsics_vec256_mul64(r12341, a1));
    Lib_IntVector_Intrinsics_vec256
    a32 =
      Lib_IntVector_Intrinsics_vec256_add64(a31,
        Lib_IntVector_Intrinsics_vec256_mul64(r12342, a1));
    Lib_IntVector_Intrinsics_vec256
    a42 =
      Lib_IntVector_Intrinsics_vec256_add64(a41,
        Lib_IntVector_Intrinsics_vec256_mul64(r12343, a1));
    Lib_IntVector_Intrinsics_vec256
    a03 =
      Lib_IntVector_Intrinsics_vec256_add64(a02,
        Lib_IntVector_Intrinsics_vec256_mul64(r123453, a2));
    Lib_IntVector_Intrinsics_vec256
    a13 =
      Lib_IntVector_Intrinsics_vec256_add64(a12,
        Lib_IntVector_Intrinsics_vec256_mul64(r123454, a2));
    Lib_IntVector_Intrinsics_vec256
    a23 =
      Lib_IntVector_Intrinsics_vec256_add64(a22,
        Lib_IntVector_Intrinsics_vec256_mul64(r12340, a2));
    Lib_IntVector_Intrinsics_vec256
    a33 =
      Lib_IntVector_Intrinsics_vec256_add64(a32,
        Lib_IntVector_Intrinsics_vec256_mul64(r12341, a2));
    Lib_IntVector_Intrinsics_vec256
    a43 =
      Lib_IntVector_Intrinsics_vec256_add64(a42,
        Lib_IntVector_Intrinsics_vec256_mul64(r12342, a2));
    Lib_IntVector_Intrinsics_vec256
    a04 =
      Lib_IntVector_Intrinsics_vec256_add64(a03,
        Lib_IntVector_Intrinsics_vec256_mul64(r123452, a3));
    Lib_IntVector_Intrinsics_vec256
    a14 =
      Lib_IntVector_Intrinsics_vec256_add64(a13,
        Lib_IntVector_Intrinsics_vec256_mul64(r123453, a3));
    Lib_IntVector_Intrinsics_vec256
    a24 =
      Lib_IntVector_Intrinsics_vec256_add64(a23,
        Lib_IntVector_Intrinsics_vec256_mul64(r123454, a3));
    Lib_IntVector_Intrinsics_vec256
    a34 =
      Lib_IntVector_Intrinsics_vec256_add64(a33,
        Lib_IntVector_Intrinsics_vec256_mul64(r12340, a3));
    Lib_IntVector_Intrinsics_vec256
    a44 =
      Lib_IntVector_Intrinsics_vec256_add64(a43,
        Lib_IntVector_Intrinsics_vec256_mul64(r12341, a3));
    Lib_IntVector_Intrinsics_vec256
    a05 =
      Lib_IntVector_Intrinsics_vec256_add64(a04,
        Lib_IntVector_Intrinsics_vec256_mul64(r123451, a4));
    Lib_IntVector_Intrinsics_vec256
    a15 =
      Lib_IntVector_Intrinsics_vec256_add64(a14,
        Lib_IntVector_Intrinsics_vec256_mul64(r123452, a4));
    Lib_IntVector_Intrinsics_vec256
    a25 =
      Lib_IntVector_Intrinsics_vec256_add64(a24,
        Lib_IntVector_Intrinsics_vec256_mul64(r123453, a4));
    Lib_IntVector_Intrinsics_vec256
    a35 =
      Lib_IntVector_Intrinsics_vec256_add64(a34,
        Lib_IntVector_Intrinsics_vec256_mul64(r123454, a4));
    Lib_IntVector_Intrinsics_vec256
    a45 =
      Lib_IntVector_Intrinsics_vec256_add64(a44,
        Lib_IntVector_Intrinsics_vec256_mul64(r12340, a4));
    Lib_IntVector_Intrinsics_vec256 t01 = a05;
    Lib_IntVector_Intrinsics_vec256 t1 = a15;
    Lib_IntVector_Intrinsics_vec256 t2 = a25;
    Lib_IntVector_Intrinsics_vec256 t3 = a35;
    Lib_IntVector_Intrinsics_vec256 t4 = a45;
    Lib_IntVector_Intrinsics_vec256
    l12 = Lib_IntVector_Intrinsics_vec256_add64(t01, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp03 =
      Lib_IntVector_Intrinsics_vec256_and(l12,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c02 = Lib_IntVector_Intrinsics_vec256_shift_right64(l12, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l13 = Lib_IntVector_Intrinsics_vec256_add64(t1, c02);
    Lib_IntVector_Intrinsics_vec256
    tmp13 =
      Lib_IntVector_Intrinsics_vec256_and(l13,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c12 = Lib_IntVector_Intrinsics_vec256_shift_right64(l13, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l14 = Lib_IntVector_Intrinsics_vec256_add64(t2, c12);
    Lib_IntVector_Intrinsics_vec256
    tmp22 =
      Lib_IntVector_Intrinsics_vec256_and(l14,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c22 = Lib_IntVector_Intrinsics_vec256_shift_right64(l14, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l15 = Lib_IntVector_Intrinsics_vec256_add64(t3, c22);
    Lib_IntVector_Intrinsics_vec256
    tmp32 =
      Lib_IntVector_Intrinsics_vec256_and(l15,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c32 = Lib_IntVector_Intrinsics_vec256_shift_right64(l15, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l16 = Lib_IntVector_Intrinsics_vec256_add64(t4, c32);
    Lib_IntVector_Intrinsics_vec256
    tmp42 =
      Lib_IntVector_Intrinsics_vec256_and(l16,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c42 = Lib_IntVector_Intrinsics_vec256_shift_right64(l16, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l17 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp03,
        Lib_IntVector_Intrinsics_vec256_smul64(c42, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp01 =
      Lib_IntVector_Intrinsics_vec256_and(l17,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c52 = Lib_IntVector_Intrinsics_vec256_shift_right64(l17, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 tmp111 = Lib_IntVector_Intrinsics_vec256_add64(tmp13, c52);
    Lib_IntVector_Intrinsics_vec256 o00 = tmp01;
    Lib_IntVector_Intrinsics_vec256 o10 = tmp111;
    Lib_IntVector_Intrinsics_vec256 o20 = tmp22;
    Lib_IntVector_Intrinsics_vec256 o30 = tmp32;
    Lib_IntVector_Intrinsics_vec256 o40 = tmp42;
    Lib_IntVector_Intrinsics_vec256
    v00 = Lib_IntVector_Intrinsics_vec256_interleave_high128(o00, o00);
    Lib_IntVector_Intrinsics_vec256 v10 = Lib_IntVector_Intrinsics_vec256_add64(o00, v00);
    Lib_IntVector_Intrinsics_vec256
    v20 =
      Lib_IntVector_Intrinsics_vec256_add64(v10,
        Lib_IntVector_Intrinsics_vec256_shuffle64(v10,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U));
    Lib_IntVector_Intrinsics_vec256
    v01 = Lib_IntVector_Intrinsics_vec256_interleave_high128(o10, o10);
    Lib_IntVector_Intrinsics_vec256 v11 = Lib_IntVector_Intrinsics_vec256_add64(o10, v01);
    Lib_IntVector_Intrinsics_vec256
    v21 =
      Lib_IntVector_Intrinsics_vec256_add64(v11,
        Lib_IntVector_Intrinsics_vec256_shuffle64(v11,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U));
    Lib_IntVector_Intrinsics_vec256
    v02 = Lib_IntVector_Intrinsics_vec256_interleave_high128(o20, o20);
    Lib_IntVector_Intrinsics_vec256 v12 = Lib_IntVector_Intrinsics_vec256_add64(o20, v02);
    Lib_IntVector_Intrinsics_vec256
    v22 =
      Lib_IntVector_Intrinsics_vec256_add64(v12,
        Lib_IntVector_Intrinsics_vec256_shuffle64(v12,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U));
    Lib_IntVector_Intrinsics_vec256
    v03 = Lib_IntVector_Intrinsics_vec256_interleave_high128(o30, o30);
    Lib_IntVector_Intrinsics_vec256 v13 = Lib_IntVector_Intrinsics_vec256_add64(o30, v03);
    Lib_IntVector_Intrinsics_vec256
    v23 =
      Lib_IntVector_Intrinsics_vec256_add64(v13,
        Lib_IntVector_Intrinsics_vec256_shuffle64(v13,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U));
    Lib_IntVector_Intrinsics_vec256
    v04 = Lib_IntVector_Intrinsics_vec256_interleave_high128(o40, o40);
    Lib_IntVector_Intrinsics_vec256 v14 = Lib_IntVector_Intrinsics_vec256_add64(o40, v04);
    Lib_IntVector_Intrinsics_vec256
    v24 =
      Lib_IntVector_Intrinsics_vec256_add64(v14,
        Lib_IntVector_Intrinsics_vec256_shuffle64(v14,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U,
          (uint32_t)1U));
    Lib_IntVector_Intrinsics_vec256
    l = Lib_IntVector_Intrinsics_vec256_add64(v20, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp0 =
      Lib_IntVector_Intrinsics_vec256_and(l,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l18 = Lib_IntVector_Intrinsics_vec256_add64(v21, c0);
    Lib_IntVector_Intrinsics_vec256
    tmp1 =
      Lib_IntVector_Intrinsics_vec256_and(l18,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l18, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l19 = Lib_IntVector_Intrinsics_vec256_add64(v22, c1);
    Lib_IntVector_Intrinsics_vec256
    tmp2 =
      Lib_IntVector_Intrinsics_vec256_and(l19,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l19, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l20 = Lib_IntVector_Intrinsics_vec256_add64(v23, c2);
    Lib_IntVector_Intrinsics_vec256
    tmp3 =
      Lib_IntVector_Intrinsics_vec256_and(l20,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l20, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l21 = Lib_IntVector_Intrinsics_vec256_add64(v24, c3);
    Lib_IntVector_Intrinsics_vec256
    tmp4 =
      Lib_IntVector_Intrinsics_vec256_and(l21,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l21, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l22 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp0,
        Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp0_ =
      Lib_IntVector_Intrinsics_vec256_and(l22,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l22, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 o0 = tmp0_;
    Lib_IntVector_Intrinsics_vec256 o1 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
    Lib_IntVector_Intrinsics_vec256 o2 = tmp2;
    Lib_IntVector_Intrinsics_vec256 o3 = tmp3;
    Lib_IntVector_Intrinsics_vec256 o4 = tmp4;
    acc[0U] = o0;
    acc[1U] = o1;
    acc[2U] = o2;
    acc[3U] = o3;
    acc[4U] = o4;
  }
  uint32_t len11 = len1 - len0;
  uint8_t *t1 = text + len0;
  uint32_t nb = len11 / (uint32_t)16U;
  uint32_t rem1 = len11 % (uint32_t)16U;
  uint32_t i;
  for (i = (uint32_t)0U; i < nb; i = i + (uint32_t)1U)
  {
    uint8_t *block = t1 + i * (uint32_t)16U;
    KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec256), (uint32_t)5U);
    Lib_IntVector_Intrinsics_vec256 e[5U];
    uint32_t _i;
    for (_i = 0U; _i < (uint32_t)5U; ++_i)
      e[_i] = Lib_IntVector_Intrinsics_vec256_zero;
    uint64_t u0 = load64_le(block);
    uint64_t lo = u0;
    uint64_t u = load64_le(block + (uint32_t)8U);
    uint64_t hi = u;
    Lib_IntVector_Intrinsics_vec256 f0 = Lib_IntVector_Intrinsics_vec256_load64(lo);
    Lib_IntVector_Intrinsics_vec256 f1 = Lib_IntVector_Intrinsics_vec256_load64(hi);
    Lib_IntVector_Intrinsics_vec256
    f010 =
      Lib_IntVector_Intrinsics_vec256_and(f0,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f110 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(f0,
          (uint32_t)26U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f20 =
      Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(f0,
          (uint32_t)52U),
        Lib_IntVector_Intrinsics_vec256_shift_left64(Lib_IntVector_Intrinsics_vec256_and(f1,
            Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffU)),
          (uint32_t)12U));
    Lib_IntVector_Intrinsics_vec256
    f30 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(f1,
          (uint32_t)14U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f40 = Lib_IntVector_Intrinsics_vec256_shift_right64(f1, (uint32_t)40U);
    Lib_IntVector_Intrinsics_vec256 f01 = f010;
    Lib_IntVector_Intrinsics_vec256 f111 = f110;
    Lib_IntVector_Intrinsics_vec256 f2 = f20;
    Lib_IntVector_Intrinsics_vec256 f3 = f30;
    Lib_IntVector_Intrinsics_vec256 f41 = f40;
    e[0U] = f01;
    e[1U] = f111;
    e[2U] = f2;
    e[3U] = f3;
    e[4U] = f41;
    uint64_t b = (uint64_t)0x1000000U;
    Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_load64(b);
    Lib_IntVector_Intrinsics_vec256 f4 = e[4U];
    e[4U] = Lib_IntVector_Intrinsics_vec256_or(f4, mask);
    Lib_IntVector_Intrinsics_vec256 *r = pre;
    Lib_IntVector_Intrinsics_vec256 *r5 = pre + (uint32_t)5U;
    Lib_IntVector_Intrinsics_vec256 r0 = r[0U];
    Lib_IntVector_Intrinsics_vec256 r1 = r[1U];
    Lib_IntVector_Intrinsics_vec256 r2 = r[2U];
    Lib_IntVector_Intrinsics_vec256 r3 = r[3U];
    Lib_IntVector_Intrinsics_vec256 r4 = r[4U];
    Lib_IntVector_Intrinsics_vec256 r51 = r5[1U];
    Lib_IntVector_Intrinsics_vec256 r52 = r5[2U];
    Lib_IntVector_Intrinsics_vec256 r53 = r5[3U];
    Lib_IntVector_Intrinsics_vec256 r54 = r5[4U];
    Lib_IntVector_Intrinsics_vec256 f10 = e[0U];
    Lib_IntVector_Intrinsics_vec256 f11 = e[1U];
    Lib_IntVector_Intrinsics_vec256 f12 = e[2U];
    Lib_IntVector_Intrinsics_vec256 f13 = e[3U];
    Lib_IntVector_Intrinsics_vec256 f14 = e[4U];
    Lib_IntVector_Intrinsics_vec256 a0 = acc[0U];
    Lib_IntVector_Intrinsics_vec256 a1 = acc[1U];
    Lib_IntVector_Intrinsics_vec256 a2 = acc[2U];
    Lib_IntVector_Intrinsics_vec256 a3 = acc[3U];
    Lib_IntVector_Intrinsics_vec256 a4 = acc[4U];
    Lib_IntVector_Intrinsics_vec256 a01 = Lib_IntVector_Intrinsics_vec256_add64(a0, f10);
    Lib_IntVector_Intrinsics_vec256 a11 = Lib_IntVector_Intrinsics_vec256_add64(a1, f11);
    Lib_IntVector_Intrinsics_vec256 a21 = Lib_IntVector_Intrinsics_vec256_add64(a2, f12);
    Lib_IntVector_Intrinsics_vec256 a31 = Lib_IntVector_Intrinsics_vec256_add64(a3, f13);
    Lib_IntVector_Intrinsics_vec256 a41 = Lib_IntVector_Intrinsics_vec256_add64(a4, f14);
    Lib_IntVector_Intrinsics_vec256 a02 = Lib_IntVector_Intrinsics_vec256_mul64(r0, a01);
    Lib_IntVector_Intrinsics_vec256 a12 = Lib_IntVector_Intrinsics_vec256_mul64(r1, a01);
    Lib_IntVector_Intrinsics_vec256 a22 = Lib_IntVector_Intrinsics_vec256_mul64(r2, a01);
    Lib_IntVector_Intrinsics_vec256 a32 = Lib_IntVector_Intrinsics_vec256_mul64(r3, a01);
    Lib_IntVector_Intrinsics_vec256 a42 = Lib_IntVector_Intrinsics_vec256_mul64(r4, a01);
    Lib_IntVector_Intrinsics_vec256
    a03 =
      Lib_IntVector_Intrinsics_vec256_add64(a02,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a11));
    Lib_IntVector_Intrinsics_vec256
    a13 =
      Lib_IntVector_Intrinsics_vec256_add64(a12,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a11));
    Lib_IntVector_Intrinsics_vec256
    a23 =
      Lib_IntVector_Intrinsics_vec256_add64(a22,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a11));
    Lib_IntVector_Intrinsics_vec256
    a33 =
      Lib_IntVector_Intrinsics_vec256_add64(a32,
        Lib_IntVector_Intrinsics_vec256_mul64(r2, a11));
    Lib_IntVector_Intrinsics_vec256
    a43 =
      Lib_IntVector_Intrinsics_vec256_add64(a42,
        Lib_IntVector_Intrinsics_vec256_mul64(r3, a11));
    Lib_IntVector_Intrinsics_vec256
    a04 =
      Lib_IntVector_Intrinsics_vec256_add64(a03,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a21));
    Lib_IntVector_Intrinsics_vec256
    a14 =
      Lib_IntVector_Intrinsics_vec256_add64(a13,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a21));
    Lib_IntVector_Intrinsics_vec256
    a24 =
      Lib_IntVector_Intrinsics_vec256_add64(a23,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a21));
    Lib_IntVector_Intrinsics_vec256
    a34 =
      Lib_IntVector_Intrinsics_vec256_add64(a33,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a21));
    Lib_IntVector_Intrinsics_vec256
    a44 =
      Lib_IntVector_Intrinsics_vec256_add64(a43,
        Lib_IntVector_Intrinsics_vec256_mul64(r2, a21));
    Lib_IntVector_Intrinsics_vec256
    a05 =
      Lib_IntVector_Intrinsics_vec256_add64(a04,
        Lib_IntVector_Intrinsics_vec256_mul64(r52, a31));
    Lib_IntVector_Intrinsics_vec256
    a15 =
      Lib_IntVector_Intrinsics_vec256_add64(a14,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a31));
    Lib_IntVector_Intrinsics_vec256
    a25 =
      Lib_IntVector_Intrinsics_vec256_add64(a24,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a31));
    Lib_IntVector_Intrinsics_vec256
    a35 =
      Lib_IntVector_Intrinsics_vec256_add64(a34,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a31));
    Lib_IntVector_Intrinsics_vec256
    a45 =
      Lib_IntVector_Intrinsics_vec256_add64(a44,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a31));
    Lib_IntVector_Intrinsics_vec256
    a06 =
      Lib_IntVector_Intrinsics_vec256_add64(a05,
        Lib_IntVector_Intrinsics_vec256_mul64(r51, a41));
    Lib_IntVector_Intrinsics_vec256
    a16 =
      Lib_IntVector_Intrinsics_vec256_add64(a15,
        Lib_IntVector_Intrinsics_vec256_mul64(r52, a41));
    Lib_IntVector_Intrinsics_vec256
    a26 =
      Lib_IntVector_Intrinsics_vec256_add64(a25,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a41));
    Lib_IntVector_Intrinsics_vec256
    a36 =
      Lib_IntVector_Intrinsics_vec256_add64(a35,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a41));
    Lib_IntVector_Intrinsics_vec256
    a46 =
      Lib_IntVector_Intrinsics_vec256_add64(a45,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a41));
    Lib_IntVector_Intrinsics_vec256 t01 = a06;
    Lib_IntVector_Intrinsics_vec256 t11 = a16;
    Lib_IntVector_Intrinsics_vec256 t2 = a26;
    Lib_IntVector_Intrinsics_vec256 t3 = a36;
    Lib_IntVector_Intrinsics_vec256 t4 = a46;
    Lib_IntVector_Intrinsics_vec256
    l = Lib_IntVector_Intrinsics_vec256_add64(t01, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp0 =
      Lib_IntVector_Intrinsics_vec256_and(l,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l0 = Lib_IntVector_Intrinsics_vec256_add64(t11, c0);
    Lib_IntVector_Intrinsics_vec256
    tmp1 =
      Lib_IntVector_Intrinsics_vec256_and(l0,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(t2, c1);
    Lib_IntVector_Intrinsics_vec256
    tmp2 =
      Lib_IntVector_Intrinsics_vec256_and(l1,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(t3, c2);
    Lib_IntVector_Intrinsics_vec256
    tmp3 =
      Lib_IntVector_Intrinsics_vec256_and(l2,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(t4, c3);
    Lib_IntVector_Intrinsics_vec256
    tmp4 =
      Lib_IntVector_Intrinsics_vec256_and(l3,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l4 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp0,
        Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp01 =
      Lib_IntVector_Intrinsics_vec256_and(l4,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 tmp11 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
    Lib_IntVector_Intrinsics_vec256 o0 = tmp01;
    Lib_IntVector_Intrinsics_vec256 o1 = tmp11;
    Lib_IntVector_Intrinsics_vec256 o2 = tmp2;
    Lib_IntVector_Intrinsics_vec256 o3 = tmp3;
    Lib_IntVector_Intrinsics_vec256 o4 = tmp4;
    acc[0U] = o0;
    acc[1U] = o1;
    acc[2U] = o2;
    acc[3U] = o3;
    acc[4U] = o4;
  }
  uint8_t *b = t1 + nb * (uint32_t)16U;
  if (rem1 > (uint32_t)0U)
  {
    KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec256), (uint32_t)5U);
    Lib_IntVector_Intrinsics_vec256 e[5U];
    uint32_t _i;
    for (_i = 0U; _i < (uint32_t)5U; ++_i)
      e[_i] = Lib_IntVector_Intrinsics_vec256_zero;
    uint8_t tmp[16U] = { 0U };
    memcpy(tmp, b, rem1 * sizeof b[0U]);
    uint64_t u0 = load64_le(tmp);
    uint64_t lo = u0;
    uint64_t u = load64_le(tmp + (uint32_t)8U);
    uint64_t hi = u;
    Lib_IntVector_Intrinsics_vec256 f0 = Lib_IntVector_Intrinsics_vec256_load64(lo);
    Lib_IntVector_Intrinsics_vec256 f1 = Lib_IntVector_Intrinsics_vec256_load64(hi);
    Lib_IntVector_Intrinsics_vec256
    f010 =
      Lib_IntVector_Intrinsics_vec256_and(f0,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f110 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(f0,
          (uint32_t)26U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f20 =
      Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(f0,
          (uint32_t)52U),
        Lib_IntVector_Intrinsics_vec256_shift_left64(Lib_IntVector_Intrinsics_vec256_and(f1,
            Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffU)),
          (uint32_t)12U));
    Lib_IntVector_Intrinsics_vec256
    f30 =
      Lib_IntVector_Intrinsics_vec256_and(Lib_IntVector_Intrinsics_vec256_shift_right64(f1,
          (uint32_t)14U),
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    f40 = Lib_IntVector_Intrinsics_vec256_shift_right64(f1, (uint32_t)40U);
    Lib_IntVector_Intrinsics_vec256 f01 = f010;
    Lib_IntVector_Intrinsics_vec256 f111 = f110;
    Lib_IntVector_Intrinsics_vec256 f2 = f20;
    Lib_IntVector_Intrinsics_vec256 f3 = f30;
    Lib_IntVector_Intrinsics_vec256 f4 = f40;
    e[0U] = f01;
    e[1U] = f111;
    e[2U] = f2;
    e[3U] = f3;
    e[4U] = f4;
    uint64_t b1 = (uint64_t)1U << rem1 * (uint32_t)8U % (uint32_t)26U;
    Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_load64(b1);
    Lib_IntVector_Intrinsics_vec256 fi = e[rem1 * (uint32_t)8U / (uint32_t)26U];
    e[rem1 * (uint32_t)8U / (uint32_t)26U] = Lib_IntVector_Intrinsics_vec256_or(fi, mask);
    Lib_IntVector_Intrinsics_vec256 *r = pre;
    Lib_IntVector_Intrinsics_vec256 *r5 = pre + (uint32_t)5U;
    Lib_IntVector_Intrinsics_vec256 r0 = r[0U];
    Lib_IntVector_Intrinsics_vec256 r1 = r[1U];
    Lib_IntVector_Intrinsics_vec256 r2 = r[2U];
    Lib_IntVector_Intrinsics_vec256 r3 = r[3U];
    Lib_IntVector_Intrinsics_vec256 r4 = r[4U];
    Lib_IntVector_Intrinsics_vec256 r51 = r5[1U];
    Lib_IntVector_Intrinsics_vec256 r52 = r5[2U];
    Lib_IntVector_Intrinsics_vec256 r53 = r5[3U];
    Lib_IntVector_Intrinsics_vec256 r54 = r5[4U];
    Lib_IntVector_Intrinsics_vec256 f10 = e[0U];
    Lib_IntVector_Intrinsics_vec256 f11 = e[1U];
    Lib_IntVector_Intrinsics_vec256 f12 = e[2U];
    Lib_IntVector_Intrinsics_vec256 f13 = e[3U];
    Lib_IntVector_Intrinsics_vec256 f14 = e[4U];
    Lib_IntVector_Intrinsics_vec256 a0 = acc[0U];
    Lib_IntVector_Intrinsics_vec256 a1 = acc[1U];
    Lib_IntVector_Intrinsics_vec256 a2 = acc[2U];
    Lib_IntVector_Intrinsics_vec256 a3 = acc[3U];
    Lib_IntVector_Intrinsics_vec256 a4 = acc[4U];
    Lib_IntVector_Intrinsics_vec256 a01 = Lib_IntVector_Intrinsics_vec256_add64(a0, f10);
    Lib_IntVector_Intrinsics_vec256 a11 = Lib_IntVector_Intrinsics_vec256_add64(a1, f11);
    Lib_IntVector_Intrinsics_vec256 a21 = Lib_IntVector_Intrinsics_vec256_add64(a2, f12);
    Lib_IntVector_Intrinsics_vec256 a31 = Lib_IntVector_Intrinsics_vec256_add64(a3, f13);
    Lib_IntVector_Intrinsics_vec256 a41 = Lib_IntVector_Intrinsics_vec256_add64(a4, f14);
    Lib_IntVector_Intrinsics_vec256 a02 = Lib_IntVector_Intrinsics_vec256_mul64(r0, a01);
    Lib_IntVector_Intrinsics_vec256 a12 = Lib_IntVector_Intrinsics_vec256_mul64(r1, a01);
    Lib_IntVector_Intrinsics_vec256 a22 = Lib_IntVector_Intrinsics_vec256_mul64(r2, a01);
    Lib_IntVector_Intrinsics_vec256 a32 = Lib_IntVector_Intrinsics_vec256_mul64(r3, a01);
    Lib_IntVector_Intrinsics_vec256 a42 = Lib_IntVector_Intrinsics_vec256_mul64(r4, a01);
    Lib_IntVector_Intrinsics_vec256
    a03 =
      Lib_IntVector_Intrinsics_vec256_add64(a02,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a11));
    Lib_IntVector_Intrinsics_vec256
    a13 =
      Lib_IntVector_Intrinsics_vec256_add64(a12,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a11));
    Lib_IntVector_Intrinsics_vec256
    a23 =
      Lib_IntVector_Intrinsics_vec256_add64(a22,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a11));
    Lib_IntVector_Intrinsics_vec256
    a33 =
      Lib_IntVector_Intrinsics_vec256_add64(a32,
        Lib_IntVector_Intrinsics_vec256_mul64(r2, a11));
    Lib_IntVector_Intrinsics_vec256
    a43 =
      Lib_IntVector_Intrinsics_vec256_add64(a42,
        Lib_IntVector_Intrinsics_vec256_mul64(r3, a11));
    Lib_IntVector_Intrinsics_vec256
    a04 =
      Lib_IntVector_Intrinsics_vec256_add64(a03,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a21));
    Lib_IntVector_Intrinsics_vec256
    a14 =
      Lib_IntVector_Intrinsics_vec256_add64(a13,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a21));
    Lib_IntVector_Intrinsics_vec256
    a24 =
      Lib_IntVector_Intrinsics_vec256_add64(a23,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a21));
    Lib_IntVector_Intrinsics_vec256
    a34 =
      Lib_IntVector_Intrinsics_vec256_add64(a33,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a21));
    Lib_IntVector_Intrinsics_vec256
    a44 =
      Lib_IntVector_Intrinsics_vec256_add64(a43,
        Lib_IntVector_Intrinsics_vec256_mul64(r2, a21));
    Lib_IntVector_Intrinsics_vec256
    a05 =
      Lib_IntVector_Intrinsics_vec256_add64(a04,
        Lib_IntVector_Intrinsics_vec256_mul64(r52, a31));
    Lib_IntVector_Intrinsics_vec256
    a15 =
      Lib_IntVector_Intrinsics_vec256_add64(a14,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a31));
    Lib_IntVector_Intrinsics_vec256
    a25 =
      Lib_IntVector_Intrinsics_vec256_add64(a24,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a31));
    Lib_IntVector_Intrinsics_vec256
    a35 =
      Lib_IntVector_Intrinsics_vec256_add64(a34,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a31));
    Lib_IntVector_Intrinsics_vec256
    a45 =
      Lib_IntVector_Intrinsics_vec256_add64(a44,
        Lib_IntVector_Intrinsics_vec256_mul64(r1, a31));
    Lib_IntVector_Intrinsics_vec256
    a06 =
      Lib_IntVector_Intrinsics_vec256_add64(a05,
        Lib_IntVector_Intrinsics_vec256_mul64(r51, a41));
    Lib_IntVector_Intrinsics_vec256
    a16 =
      Lib_IntVector_Intrinsics_vec256_add64(a15,
        Lib_IntVector_Intrinsics_vec256_mul64(r52, a41));
    Lib_IntVector_Intrinsics_vec256
    a26 =
      Lib_IntVector_Intrinsics_vec256_add64(a25,
        Lib_IntVector_Intrinsics_vec256_mul64(r53, a41));
    Lib_IntVector_Intrinsics_vec256
    a36 =
      Lib_IntVector_Intrinsics_vec256_add64(a35,
        Lib_IntVector_Intrinsics_vec256_mul64(r54, a41));
    Lib_IntVector_Intrinsics_vec256
    a46 =
      Lib_IntVector_Intrinsics_vec256_add64(a45,
        Lib_IntVector_Intrinsics_vec256_mul64(r0, a41));
    Lib_IntVector_Intrinsics_vec256 t01 = a06;
    Lib_IntVector_Intrinsics_vec256 t11 = a16;
    Lib_IntVector_Intrinsics_vec256 t2 = a26;
    Lib_IntVector_Intrinsics_vec256 t3 = a36;
    Lib_IntVector_Intrinsics_vec256 t4 = a46;
    Lib_IntVector_Intrinsics_vec256
    l = Lib_IntVector_Intrinsics_vec256_add64(t01, Lib_IntVector_Intrinsics_vec256_zero);
    Lib_IntVector_Intrinsics_vec256
    tmp0 =
      Lib_IntVector_Intrinsics_vec256_and(l,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l0 = Lib_IntVector_Intrinsics_vec256_add64(t11, c0);
    Lib_IntVector_Intrinsics_vec256
    tmp1 =
      Lib_IntVector_Intrinsics_vec256_and(l0,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(t2, c1);
    Lib_IntVector_Intrinsics_vec256
    tmp2 =
      Lib_IntVector_Intrinsics_vec256_and(l1,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(t3, c2);
    Lib_IntVector_Intrinsics_vec256
    tmp3 =
      Lib_IntVector_Intrinsics_vec256_and(l2,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(t4, c3);
    Lib_IntVector_Intrinsics_vec256
    tmp4 =
      Lib_IntVector_Intrinsics_vec256_and(l3,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256
    l4 =
      Lib_IntVector_Intrinsics_vec256_add64(tmp0,
        Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
    Lib_IntVector_Intrinsics_vec256
    tmp01 =
      Lib_IntVector_Intrinsics_vec256_and(l4,
        Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
    Lib_IntVector_Intrinsics_vec256
    c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
    Lib_IntVector_Intrinsics_vec256 tmp11 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
    Lib_IntVector_Intrinsics_vec256 o0 = tmp01;
    Lib_IntVector_Intrinsics_vec256 o1 = tmp11;
    Lib_IntVector_Intrinsics_vec256 o2 = tmp2;
    Lib_IntVector_Intrinsics_vec256 o3 = tmp3;
    Lib_IntVector_Intrinsics_vec256 o4 = tmp4;
    acc[0U] = o0;
    acc[1U] = o1;
    acc[2U] = o2;
    acc[3U] = o3;
    acc[4U] = o4;
  }
}

void
Hacl_Poly1305_256_poly1305_update_blocks(
  Lib_IntVector_Intrinsics_vec256 *ctx,
  uint32_t len1,
  uint8_t *text
)
{
  Hacl_Poly1305_256_poly1305_update(ctx, len1, text);
}

void
(*Hacl_Poly1305_256_poly1305_update_padded)(
  Lib_IntVector_Intrinsics_vec256 *x0,
  uint32_t x1,
  uint8_t *x2
) = Hacl_Poly1305_256_poly1305_update;

void
Hacl_Poly1305_256_poly1305_update_last(
  Lib_IntVector_Intrinsics_vec256 *ctx,
  uint32_t len1,
  uint8_t *text
)
{
  Hacl_Poly1305_256_poly1305_update(ctx, len1, text);
}

void
Hacl_Poly1305_256_poly1305_finish(
  uint8_t *tag,
  uint8_t *key,
  Lib_IntVector_Intrinsics_vec256 *ctx
)
{
  Lib_IntVector_Intrinsics_vec256 *acc = ctx;
  uint8_t *ks = key + (uint32_t)16U;
  Lib_IntVector_Intrinsics_vec256 f00 = acc[0U];
  Lib_IntVector_Intrinsics_vec256 f12 = acc[1U];
  Lib_IntVector_Intrinsics_vec256 f22 = acc[2U];
  Lib_IntVector_Intrinsics_vec256 f32 = acc[3U];
  Lib_IntVector_Intrinsics_vec256 f40 = acc[4U];
  Lib_IntVector_Intrinsics_vec256
  l = Lib_IntVector_Intrinsics_vec256_add64(f00, Lib_IntVector_Intrinsics_vec256_zero);
  Lib_IntVector_Intrinsics_vec256
  tmp0 =
    Lib_IntVector_Intrinsics_vec256_and(l,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c0 = Lib_IntVector_Intrinsics_vec256_shift_right64(l, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l0 = Lib_IntVector_Intrinsics_vec256_add64(f12, c0);
  Lib_IntVector_Intrinsics_vec256
  tmp1 =
    Lib_IntVector_Intrinsics_vec256_and(l0,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c1 = Lib_IntVector_Intrinsics_vec256_shift_right64(l0, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l1 = Lib_IntVector_Intrinsics_vec256_add64(f22, c1);
  Lib_IntVector_Intrinsics_vec256
  tmp2 =
    Lib_IntVector_Intrinsics_vec256_and(l1,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c2 = Lib_IntVector_Intrinsics_vec256_shift_right64(l1, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l2 = Lib_IntVector_Intrinsics_vec256_add64(f32, c2);
  Lib_IntVector_Intrinsics_vec256
  tmp3 =
    Lib_IntVector_Intrinsics_vec256_and(l2,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c3 = Lib_IntVector_Intrinsics_vec256_shift_right64(l2, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 l3 = Lib_IntVector_Intrinsics_vec256_add64(f40, c3);
  Lib_IntVector_Intrinsics_vec256
  tmp4 =
    Lib_IntVector_Intrinsics_vec256_and(l3,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c4 = Lib_IntVector_Intrinsics_vec256_shift_right64(l3, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256
  l4 =
    Lib_IntVector_Intrinsics_vec256_add64(tmp0,
      Lib_IntVector_Intrinsics_vec256_smul64(c4, (uint64_t)5U));
  Lib_IntVector_Intrinsics_vec256
  tmp0_ =
    Lib_IntVector_Intrinsics_vec256_and(l4,
      Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU));
  Lib_IntVector_Intrinsics_vec256
  c5 = Lib_IntVector_Intrinsics_vec256_shift_right64(l4, (uint32_t)26U);
  Lib_IntVector_Intrinsics_vec256 f010 = tmp0_;
  Lib_IntVector_Intrinsics_vec256 f110 = Lib_IntVector_Intrinsics_vec256_add64(tmp1, c5);
  Lib_IntVector_Intrinsics_vec256 f210 = tmp2;
  Lib_IntVector_Intrinsics_vec256 f310 = tmp3;
  Lib_IntVector_Intrinsics_vec256 f410 = tmp4;
  Lib_IntVector_Intrinsics_vec256
  mh = Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3ffffffU);
  Lib_IntVector_Intrinsics_vec256
  ml = Lib_IntVector_Intrinsics_vec256_load64((uint64_t)0x3fffffbU);
  Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_eq64(f410, mh);
  Lib_IntVector_Intrinsics_vec256
  mask1 =
    Lib_IntVector_Intrinsics_vec256_and(mask,
      Lib_IntVector_Intrinsics_vec256_eq64(f310, mh));
  Lib_IntVector_Intrinsics_vec256
  mask2 =
    Lib_IntVector_Intrinsics_vec256_and(mask1,
      Lib_IntVector_Intrinsics_vec256_eq64(f210, mh));
  Lib_IntVector_Intrinsics_vec256
  mask3 =
    Lib_IntVector_Intrinsics_vec256_and(mask2,
      Lib_IntVector_Intrinsics_vec256_eq64(f110, mh));
  Lib_IntVector_Intrinsics_vec256
  mask4 =
    Lib_IntVector_Intrinsics_vec256_and(mask3,
      Lib_IntVector_Intrinsics_vec256_lognot(Lib_IntVector_Intrinsics_vec256_gt64(ml, f010)));
  Lib_IntVector_Intrinsics_vec256 ph = Lib_IntVector_Intrinsics_vec256_and(mask4, mh);
  Lib_IntVector_Intrinsics_vec256 pl = Lib_IntVector_Intrinsics_vec256_and(mask4, ml);
  Lib_IntVector_Intrinsics_vec256 o0 = Lib_IntVector_Intrinsics_vec256_sub64(f010, pl);
  Lib_IntVector_Intrinsics_vec256 o1 = Lib_IntVector_Intrinsics_vec256_sub64(f110, ph);
  Lib_IntVector_Intrinsics_vec256 o2 = Lib_IntVector_Intrinsics_vec256_sub64(f210, ph);
  Lib_IntVector_Intrinsics_vec256 o3 = Lib_IntVector_Intrinsics_vec256_sub64(f310, ph);
  Lib_IntVector_Intrinsics_vec256 o4 = Lib_IntVector_Intrinsics_vec256_sub64(f410, ph);
  Lib_IntVector_Intrinsics_vec256 f01 = o0;
  Lib_IntVector_Intrinsics_vec256 f111 = o1;
  Lib_IntVector_Intrinsics_vec256 f211 = o2;
  Lib_IntVector_Intrinsics_vec256 f311 = o3;
  Lib_IntVector_Intrinsics_vec256 f41 = o4;
  acc[0U] = f01;
  acc[1U] = f111;
  acc[2U] = f211;
  acc[3U] = f311;
  acc[4U] = f41;
  Lib_IntVector_Intrinsics_vec256 f02 = acc[0U];
  Lib_IntVector_Intrinsics_vec256 f13 = acc[1U];
  Lib_IntVector_Intrinsics_vec256 f2 = acc[2U];
  Lib_IntVector_Intrinsics_vec256 f3 = acc[3U];
  Lib_IntVector_Intrinsics_vec256 f4 = acc[4U];
  Lib_IntVector_Intrinsics_vec256
  lo0 =
    Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_or(f02,
        Lib_IntVector_Intrinsics_vec256_shift_left64(f13, (uint32_t)26U)),
      Lib_IntVector_Intrinsics_vec256_shift_left64(f2, (uint32_t)52U));
  Lib_IntVector_Intrinsics_vec256
  hi0 =
    Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_shift_right64(f2,
          (uint32_t)12U),
        Lib_IntVector_Intrinsics_vec256_shift_left64(f3, (uint32_t)14U)),
      Lib_IntVector_Intrinsics_vec256_shift_left64(f4, (uint32_t)40U));
  Lib_IntVector_Intrinsics_vec256 f10 = lo0;
  Lib_IntVector_Intrinsics_vec256 f11 = hi0;
  uint64_t u0 = load64_le(ks);
  uint64_t lo2 = u0;
  uint64_t u = load64_le(ks + (uint32_t)8U);
  uint64_t hi2 = u;
  Lib_IntVector_Intrinsics_vec256 f0 = Lib_IntVector_Intrinsics_vec256_load64(lo2);
  Lib_IntVector_Intrinsics_vec256 f1 = Lib_IntVector_Intrinsics_vec256_load64(hi2);
  Lib_IntVector_Intrinsics_vec256 f20 = f0;
  Lib_IntVector_Intrinsics_vec256 f21 = f1;
  Lib_IntVector_Intrinsics_vec256 r0 = Lib_IntVector_Intrinsics_vec256_add64(f10, f20);
  Lib_IntVector_Intrinsics_vec256 r1 = Lib_IntVector_Intrinsics_vec256_add64(f11, f21);
  Lib_IntVector_Intrinsics_vec256
  c =
    Lib_IntVector_Intrinsics_vec256_shift_right64(Lib_IntVector_Intrinsics_vec256_xor(r0,
        Lib_IntVector_Intrinsics_vec256_or(Lib_IntVector_Intrinsics_vec256_xor(r0, f20),
          Lib_IntVector_Intrinsics_vec256_xor(Lib_IntVector_Intrinsics_vec256_sub64(r0, f20), f20))),
      (uint32_t)63U);
  Lib_IntVector_Intrinsics_vec256 r11 = Lib_IntVector_Intrinsics_vec256_add64(r1, c);
  Lib_IntVector_Intrinsics_vec256 f30 = r0;
  Lib_IntVector_Intrinsics_vec256 f31 = r11;
  Lib_IntVector_Intrinsics_vec256
  lo = Lib_IntVector_Intrinsics_vec256_interleave_low64(f30, f31);
  Lib_IntVector_Intrinsics_vec256
  hi = Lib_IntVector_Intrinsics_vec256_interleave_high64(f30, f31);
  Lib_IntVector_Intrinsics_vec256 lo1 = lo;
  Lib_IntVector_Intrinsics_vec256 hi1 = hi;
  Lib_IntVector_Intrinsics_vec256
  r00 = Lib_IntVector_Intrinsics_vec256_interleave_low128(lo1, hi1);
  uint8_t tmp[32U] = { 0U };
  Lib_IntVector_Intrinsics_vec256_store_le(tmp, r00);
  memcpy(tag, tmp, (uint32_t)16U * sizeof tmp[0U]);
}

void poly1305_hacl256(uint8_t *tag, uint32_t len1, uint8_t *text, uint8_t *key)
{
  KRML_CHECK_SIZE(sizeof (Lib_IntVector_Intrinsics_vec256), (uint32_t)5U + (uint32_t)20U);
  Lib_IntVector_Intrinsics_vec256 ctx[(uint32_t)5U + (uint32_t)20U];
  uint32_t _i;
  for (_i = 0U; _i < (uint32_t)5U + (uint32_t)20U; ++_i)
    ctx[_i] = Lib_IntVector_Intrinsics_vec256_zero;
  Hacl_Poly1305_256_poly1305_init(ctx, key);
  Hacl_Poly1305_256_poly1305_update_padded(ctx, len1, text);
  Hacl_Poly1305_256_poly1305_finish(tag, key, ctx);
}

