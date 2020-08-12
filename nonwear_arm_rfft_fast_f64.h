// #include "arm_common_tables.h"
// #include "arm_math.h"
#include <stdint.h>
typedef double float64_t;

/**
 * @brief Error status returned by some functions in the library.
 */
typedef enum {
  NONWEAR_ARM_MATH_SUCCESS = 0, /**< No error */
  NONWEAR_ARM_MATH_ARGUMENT_ERROR =
      -1, /**< One or more arguments are incorrect */
  NONWEAR_ARM_MATH_LENGTH_ERROR = -2, /**< Length of data buffer is incorrect */
  NONWEAR_ARM_MATH_SIZE_MISMATCH =
      -3, /**< Size of matrices is not compatible with the operation */
  NONWEAR_ARM_MATH_NANINF =
      -4, /**< Not-a-number (NaN) or infinity is generated */
  NONWEAR_ARM_MATH_SINGULAR =
      -5, /**< Input matrix is singular and cannot be inverted */
  NONWEAR_ARM_MATH_TEST_FAILURE = -6 /**< Test Failed */
} nonwear_arm_status;

/**
 * @brief Instance structure for the Double Precision Floating-point CFFT/CIFFT
 * function.
 */
typedef struct {
  uint16_t fftLen;              /**< length of the FFT. */
  const float64_t *pTwiddle;    /**< points to the Twiddle factor table. */
  const uint16_t *pBitRevTable; /**< points to the bit reversal table. */
  uint16_t bitRevLength;        /**< bit reversal table length. */
} nonwear_arm_cfft_instance_f64;

/**
 * @brief Instance structure for the Double Precision Floating-point RFFT/RIFFT
 * function.
 */
typedef struct {
  nonwear_arm_cfft_instance_f64 Sint; /**< Internal CFFT structure. */
  uint16_t fftLenRFFT;                /**< length of the real sequence */
  const float64_t *pTwiddleRFFT;      /**< Twiddle factors real stage  */
} nonwear_arm_rfft_fast_instance_f64;

// /**
//  * @brief Instance structure for the Double Precision Floating-point
//  CFFT/CIFFT
//  * function.
//  */
// typedef struct {
//   uint16_t fftLen;              /**< length of the FFT. */
//   const float64_t *pTwiddle;    /**< points to the Twiddle factor table. */
//   const uint16_t *pBitRevTable; /**< points to the bit reversal table. */
//   uint16_t bitRevLength;        /**< bit reversal table length. */
// } arm_cfft_instance_f64;

void nonwear_arm_rfft_fast_f64(nonwear_arm_rfft_fast_instance_f64 *S,
                               float64_t *p, float64_t *pOut, uint8_t ifftFlag);