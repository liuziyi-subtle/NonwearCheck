#include <stdint.h>
typedef double float64_t;

void ARLeastSquare(float64_t *data, uint32_t data_length, uint8_t degree,
                   float64_t *coefficients, float64_t **mat);