/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "(?:vmovdqa32|vpblendmd)\[ \\t\]+\[^\{\n\]*%ymm\[0-9\]+\[^\n\]*%ymm\[0-9\]+\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "(?:vmovdqa32|vpblendmd)\[ \\t\]+\[^\{\n\]*%xmm\[0-9\]+\[^\n\]*%xmm\[0-9\]+\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*%ymm\[0-9\]+\[^\n\]*%ymm\[0-9\]+\{%k\[1-7\]\}\{z\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*%xmm\[0-9\]+\[^\n\]*%xmm\[0-9\]+\{%k\[1-7\]\}\{z\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*\\)\[^\n\]*%ymm\[0-9\]+\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*\\)\[^\n\]*%xmm\[0-9\]+\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*\\)\[^\n\]*%ymm\[0-9\]+\{%k\[1-7\]\}\{z\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*\\)\[^\n\]*%xmm\[0-9\]+\{%k\[1-7\]\}\{z\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*%ymm\[0-9\]+\[^\n\]*\\)\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa32\[ \\t\]+\[^\{\n\]*%xmm\[0-9\]+\[^\n\]*\\)\{%k\[1-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa\[ \\t\]+\\(\[^\{\n\]*\\)\[^\n\]*%ymm\[0-9\]+(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa\[ \\t\]+\\(\[^\{\n\]*\\)\[^\n\]*%xmm\[0-9\]+(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa\[ \\t\]+\[^\{\n\]*%ymm\[0-9\]+\[^\n\]*\[ \\t\]+\\(\[^\n\]*\\)(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa\[ \\t\]+\[^\{\n\]*%xmm\[0-9\]+\[^\n\]*\[ \\t\]+\\(\[^\n\]*\\)(?:\n|\[ \\t\]+#)" 1 } } */

#include <immintrin.h>

int *p, *p1, *p2;
volatile __m256i yy, y2, yyy;
volatile __m128i xx, x2, xxx;
volatile __mmask8 m;

void extern
avx512vl_test (void)
{
  yy = _mm256_mask_mov_epi32 (yy, m, y2);
  xx = _mm_mask_mov_epi32 (xx, m, x2);

  yy = _mm256_maskz_mov_epi32 (m, y2);
  xx = _mm_maskz_mov_epi32 (m, x2);

  yy = _mm256_mask_load_epi32 (yy, m, p);
  xx = _mm_mask_load_epi32 (xx, m, p);

  yyy = _mm256_load_epi32 (p2);
  xxx = _mm_load_epi32 (p1);

  yy = _mm256_maskz_load_epi32 (m, p);
  xx = _mm_maskz_load_epi32 (m, p);

  _mm256_mask_store_epi32 (p, m, yy);
  _mm_mask_store_epi32 (p, m, xx);

  _mm256_store_epi32 (p2, yyy);
  _mm_store_epi32 (p2, xxx);
}
