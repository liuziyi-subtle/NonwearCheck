#include "nonwear_arm_rfft_fast_f64.h"

#define NONWEAR_ARMBITREVINDEXTABLEF64_32_TABLE_LENGTH ((uint16_t)24)
// const uint16_t
//     armBitRevIndexTableF64_32[ARMBITREVINDEXTABLEF64_32_TABLE_LENGTH];

// const uint64_t twiddleCoefF64_32[64];
// const uint64_t twiddleCoefF64_rfft_64[64];

const uint16_t nonwear_armBitRevIndexTableF64_32
    [NONWEAR_ARMBITREVINDEXTABLEF64_32_TABLE_LENGTH] = {
        /* 4x2, size 24 */
        8,  128, 16, 64,  24,  192, 40,  160, 48,  96,  56,  224,
        72, 144, 88, 208, 104, 176, 120, 240, 152, 200, 184, 232};

const uint64_t nonwear_twiddleCoefF64_32[64] = {
    0x3ff0000000000000, 0x0000000000000000,  //       1,       0'
    0x3fef6297cff75cb0, 0x3fc8f8b83c69a60a,  // 0.98079, 0.19509'
    0x3fed906bcf328d46, 0x3fd87de2a6aea963,  // 0.92388, 0.38268'
    0x3fea9b66290ea1a3, 0x3fe1c73b39ae68c8,  // 0.83147, 0.55557'
    0x3fe6a09e667f3bcc, 0x3fe6a09e667f3bcc,  // 0.70711, 0.70711'
    0x3fe1c73b39ae68c8, 0x3fea9b66290ea1a3,  // 0.55557, 0.83147'
    0x3fd87de2a6aea963, 0x3fed906bcf328d46,  // 0.38268, 0.92388'
    0x3fc8f8b83c69a60a, 0x3fef6297cff75cb0,  // 0.19509, 0.98079'
    0x0000000000000000, 0x3ff0000000000000,  //       0,       1'
    0xbfc8f8b83c69a60a, 0x3fef6297cff75cb0,  //-0.19509, 0.98079'
    0xbfd87de2a6aea963, 0x3fed906bcf328d46,  //-0.38268, 0.92388'
    0xbfe1c73b39ae68c8, 0x3fea9b66290ea1a3,  //-0.55557, 0.83147'
    0xbfe6a09e667f3bcc, 0x3fe6a09e667f3bcc,  //-0.70711, 0.70711'
    0xbfea9b66290ea1a3, 0x3fe1c73b39ae68c8,  //-0.83147, 0.55557'
    0xbfed906bcf328d46, 0x3fd87de2a6aea963,  //-0.92388, 0.38268'
    0xbfef6297cff75cb0, 0x3fc8f8b83c69a60a,  //-0.98079, 0.19509'
    0xbff0000000000000, 0x0000000000000000,  //      -1,       0'
    0xbfef6297cff75cb0, 0xbfc8f8b83c69a60a,  //-0.98079,-0.19509'
    0xbfed906bcf328d46, 0xbfd87de2a6aea963,  //-0.92388,-0.38268'
    0xbfea9b66290ea1a3, 0xbfe1c73b39ae68c8,  //-0.83147,-0.55557'
    0xbfe6a09e667f3bcc, 0xbfe6a09e667f3bcc,  //-0.70711,-0.70711'
    0xbfe1c73b39ae68c8, 0xbfea9b66290ea1a3,  //-0.55557,-0.83147'
    0xbfd87de2a6aea963, 0xbfed906bcf328d46,  //-0.38268,-0.92388'
    0xbfc8f8b83c69a60a, 0xbfef6297cff75cb0,  //-0.19509,-0.98079'
    0x0000000000000000, 0xbff0000000000000,  //       0,      -1'
    0x3fc8f8b83c69a60a, 0xbfef6297cff75cb0,  // 0.19509,-0.98079'
    0x3fd87de2a6aea963, 0xbfed906bcf328d46,  // 0.38268,-0.92388'
    0x3fe1c73b39ae68c8, 0xbfea9b66290ea1a3,  // 0.55557,-0.83147'
    0x3fe6a09e667f3bcc, 0xbfe6a09e667f3bcc,  // 0.70711,-0.70711'
    0x3fea9b66290ea1a3, 0xbfe1c73b39ae68c8,  // 0.83147,-0.55557'
    0x3fed906bcf328d46, 0xbfd87de2a6aea963,  // 0.92388,-0.38268'
    0x3fef6297cff75cb0, 0xbfc8f8b83c69a60a,  // 0.98079,-0.19509'
};

const uint64_t nonwear_twiddleCoefF64_rfft_64[64] = {
    0x0000000000000000, 0x3ff0000000000000,  //       0,        1'
    0x3fb917a6bc29b42c, 0x3fefd88da3d12526,  // 0.098017,  0.99518'
    0x3fc8f8b83c69a60a, 0x3fef6297cff75cb0,  // 0.19509,  0.98079'
    0x3fd294062ed59f05, 0x3fee9f4156c62dda,  // 0.29028,  0.95694'
    0x3fd87de2a6aea963, 0x3fed906bcf328d46,  // 0.38268,  0.92388'
    0x3fde2b5d3806f63b, 0x3fec38b2f180bdb1,  //  0.4714,  0.88192'
    0x3fe1c73b39ae68c8, 0x3fea9b66290ea1a3,  // 0.55557,  0.83147'
    0x3fe44cf325091dd6, 0x3fe8bc806b151741,  // 0.63439,  0.77301'
    0x3fe6a09e667f3bcc, 0x3fe6a09e667f3bcc,  // 0.70711,  0.70711'
    0x3fe8bc806b151741, 0x3fe44cf325091dd6,  // 0.77301,  0.63439'
    0x3fea9b66290ea1a3, 0x3fe1c73b39ae68c8,  // 0.83147,  0.55557'
    0x3fec38b2f180bdb1, 0x3fde2b5d3806f63b,  // 0.88192,   0.4714'
    0x3fed906bcf328d46, 0x3fd87de2a6aea963,  // 0.92388,  0.38268'
    0x3fee9f4156c62dda, 0x3fd294062ed59f05,  // 0.95694,  0.29028'
    0x3fef6297cff75cb0, 0x3fc8f8b83c69a60a,  // 0.98079,  0.19509'
    0x3fefd88da3d12526, 0x3fb917a6bc29b42c,  // 0.99518, 0.098017'
    0x3ff0000000000000, 0x0000000000000000,  //       1,        0'
    0x3fefd88da3d12526, 0xbfb917a6bc29b42c,  // 0.99518,-0.098017'
    0x3fef6297cff75cb0, 0xbfc8f8b83c69a60a,  // 0.98079, -0.19509'
    0x3fee9f4156c62dda, 0xbfd294062ed59f05,  // 0.95694, -0.29028'
    0x3fed906bcf328d46, 0xbfd87de2a6aea963,  // 0.92388, -0.38268'
    0x3fec38b2f180bdb1, 0xbfde2b5d3806f63b,  // 0.88192,  -0.4714'
    0x3fea9b66290ea1a3, 0xbfe1c73b39ae68c8,  // 0.83147, -0.55557'
    0x3fe8bc806b151741, 0xbfe44cf325091dd6,  // 0.77301, -0.63439'
    0x3fe6a09e667f3bcc, 0xbfe6a09e667f3bcc,  // 0.70711, -0.70711'
    0x3fe44cf325091dd6, 0xbfe8bc806b151741,  // 0.63439, -0.77301'
    0x3fe1c73b39ae68c8, 0xbfea9b66290ea1a3,  // 0.55557, -0.83147'
    0x3fde2b5d3806f63b, 0xbfec38b2f180bdb1,  //  0.4714, -0.88192'
    0x3fd87de2a6aea963, 0xbfed906bcf328d46,  // 0.38268, -0.92388'
    0x3fd294062ed59f05, 0xbfee9f4156c62dda,  // 0.29028, -0.95694'
    0x3fc8f8b83c69a60a, 0xbfef6297cff75cb0,  // 0.19509, -0.98079'
    0x3fb917a6bc29b42c, 0xbfefd88da3d12526,  // 0.098017, -0.99518'
};

nonwear_arm_status nonwear_arm_rfft_64_fast_init_f64(
    nonwear_arm_rfft_fast_instance_f64 *S) {
  nonwear_arm_cfft_instance_f64 *Sint;

  if (!S) return NONWEAR_ARM_MATH_ARGUMENT_ERROR;

  Sint = &(S->Sint);
  Sint->fftLen = 32U;
  S->fftLenRFFT = 64U;

  Sint->bitRevLength = NONWEAR_ARMBITREVINDEXTABLEF64_32_TABLE_LENGTH;
  Sint->pBitRevTable = (uint16_t *)nonwear_armBitRevIndexTableF64_32;
  Sint->pTwiddle = (float64_t *)nonwear_twiddleCoefF64_32;
  S->pTwiddleRFFT = (float64_t *)nonwear_twiddleCoefF64_rfft_64;

  return NONWEAR_ARM_MATH_SUCCESS;
}