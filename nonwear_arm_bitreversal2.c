// #include "arm_common_tables.h"
// #include "arm_math.h"
// #include "arm_rfft_fast_f64.h"
#include <stdint.h>

// extern void arm_bitreversal_64(uint64_t *pSrc, const uint16_t bitRevLen,
//                                const uint16_t *pBitRevTab);

/**
  @brief         In-place 64 bit reversal function.
  @param[in,out] pSrc        points to in-place buffer of unknown 64-bit data
  type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @return        none
*/
void nonwear_arm_bitreversal_64(uint64_t *pSrc, const uint16_t bitRevLen,
                                const uint16_t *pBitRevTab) {
  uint64_t a, b, i, tmp;

  for (i = 0; i < bitRevLen;) {
    a = pBitRevTab[i] >> 2;
    b = pBitRevTab[i + 1] >> 2;

    // real
    tmp = pSrc[a];
    pSrc[a] = pSrc[b];
    pSrc[b] = tmp;

    // complex
    tmp = pSrc[a + 1];
    pSrc[a + 1] = pSrc[b + 1];
    pSrc[b + 1] = tmp;

    i += 2;
  }
}