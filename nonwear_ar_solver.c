#include "nonwear_ar_solver.h"

#include <math.h>

static void _SolveLE(float64_t **mat, float64_t *vec, uint8_t n) {
  // uint8_t i, j, k, maxi;
  int32_t i, j, k, maxi;
  float64_t vswap, *mswap, *hvec, max, h, pivot, q;
  
  for (i = 0; i < n - 1; i++) {
    max = fabs(mat[i][i]);
    maxi = i;
    for (j = i + 1; j < n; j++) {
      if ((h = fabs(mat[j][i])) > max) {
        max = h;
        maxi = j;
      }
    }
    if (maxi != i) {
      mswap = mat[i];
      mat[i] = mat[maxi];
      mat[maxi] = mswap;
      vswap = vec[i];
      vec[i] = vec[maxi];
      vec[maxi] = vswap;
    }

    hvec = mat[i];
    pivot = hvec[i];
    // if (fabs(pivot) == 0.0) {
    //   fprintf(stderr, "Singular matrix - fatal!\n");
    //   return (FALSE);
    // }
    for (j = i + 1; j < n; j++) {
      q = -mat[j][i] / pivot;
      mat[j][i] = 0.0;
      for (k = i + 1; k < n; k++) mat[j][k] += q * hvec[k];
      vec[j] += (q * vec[i]);
    }
  }
  
  vec[n - 1] /= mat[n - 1][n - 1];
  
  for (i = n - 2; i >= 0; i--) {
    hvec = mat[i];
    for (j = n - 1; j > i; j--) vec[i] -= (hvec[j] * vec[j]);
    vec[i] /= hvec[i];
  }
  
  return;
}

void ARLeastSquare(float64_t *data, uint32_t data_length, uint8_t degree,
                   float64_t *coefficients, float64_t **mat) {
  int i, j, k, hj, hi;

  for (i = 0; i < degree; i++) {
    coefficients[i] = 0.0;
    for (j = 0; j < degree; j++) mat[i][j] = 0.0;
  }
  
  for (i = degree - 1; i < data_length - 1; i++) {
    hi = i + 1;
    for (j = 0; j < degree; j++) {
      hj = i - j;
      coefficients[j] += (data[hi] * data[hj]);
      for (k = j; k < degree; k++) mat[j][k] += (data[hj] * data[i - k]);
    }
  }
  
  for (i = 0; i < degree; i++) {
    coefficients[i] /= (data_length - degree);
    for (j = i; j < degree; j++) {
      mat[i][j] /= (data_length - degree);
      mat[j][i] = mat[i][j];
    }
  }
  
  
  _SolveLE(mat, coefficients, degree);

  return;
}