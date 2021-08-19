#include "nonwear_check.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "nonwear_model.h"

typedef float float32_t;
typedef double float64_t;

#define NWC_PPG_LENGTH (128u)
#define NWC_FEATS_LENGTH (16u)
#define NWC_PROBA_TH (0.6f)  // min prob to comfirm nonwear
#define NWC_CHECK_RESULTS_SIZE (10u)
#define NWC_LOWER_PPG_TH_G (-5000)
#define NWC_LOWER_PPG_TH_IR (-5000)
#define NWC_RULE_RESULTS_SIZE (2u)

static float32_t k_ppg[NWC_PPG_LENGTH];
static union NonwearEntry k_feats[NWC_FEATS_LENGTH];
static float32_t* k_mat[10u];
static float32_t k_mem_pool[256u];

static float32_t k_variance;
static float32_t k_mean;

static uint8_t k_ind_set[128] = {0};
static uint8_t k_inc_set[128] = {0};


float32_t _Mean(const float32_t* data, uint16_t data_length) {
  uint16_t count;      /*<< loop counter */
  float64_t sum = 0.0; /*<< temporary result storage */

  /* Initialize counter with number of samples */
  count = data_length;
  while (count > 0u) {
    sum += (float64_t)*data++;
    count--;
  }

  // float32_t mean = (sum / data_length);
  float64_t mean = sum / (float64_t)data_length;

  return (float32_t)mean;
}

float32_t _Variance(const float32_t* data, uint16_t data_length,
                    uint16_t ddof) {
  uint16_t counter;    /*<< loop counter */
  float64_t sum = 0.0; /*<< temporary result storage */
  float64_t f_sum = 0.0;
  float64_t f_mean, f_value;
  const float32_t* p_input = data;

  if (data_length <= 1u) {
    return .0;
  }

  /* Initialize counter with number of samples */
  counter = data_length;
  while (counter > 0u) {
    sum += (float64_t)*p_input++;
    counter--;
  }

  f_mean = sum / data_length;

  p_input = data;
  counter = data_length;
  while (counter > 0u) {
    f_value = (float64_t)*p_input++ - f_mean;
    f_sum += f_value * f_value;

    counter--;
  }

  /* Variance */
  float32_t variance = (float32_t)(f_sum / (data_length - ddof));

  return variance;
}

/* To left if shift > 0 else right. */
static void _Roll(float32_t* data, int16_t data_length, int16_t shift) {
  /* first roll within [0, shift - 1] and [shift, data_length - 1],
   * then flip the whole data. */
  if (shift == 0) {
    return;
  }

  /* p points to the element which will be the new data[0],
   * p must exchange with data[data_length - 1]. */
  float32_t* p = &data[(data_length + shift) % data_length];
  float32_t* q = &data[data_length - 1];
  float32_t temp;
  while (p < q) {
    temp = *p;
    *p++ = *q;
    *q-- = temp;
  }

  /* p points to the element which will be the new data[data_length - 1],
   * p must exchange with data[0]. */
  p = &data[(data_length + shift - 1) % data_length];
  q = data;
  while (p > q) {
    temp = *p;
    *p-- = *q;
    *q++ = temp;
  }

  /* roll the whole data*/
  p = data;
  q = &data[data_length - 1];
  while (p < q) {
    temp = *p;
    *p++ = *q;
    *q-- = temp;
  }

  return;
}

static void _SolveLE(float32_t** mat, float32_t* vec, uint16_t n) {
  // uint8_t i, j, k, maxi;
  int16_t i, j, k, maxi;
  float32_t vswap, *mswap, *hvec, max, h, pivot, q;

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
      mat[j][i] = .0f;
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

static void _ARLeastSquare(float32_t* data, uint16_t data_length,
                           uint8_t degree, float32_t* coefficients,
                           float32_t** mat) {
  int16_t i, j, k, hj, hi;

  for (i = 0u; i < degree; i++) {
    coefficients[i] = .0f;
    for (j = 0u; j < degree; j++) mat[i][j] = .0f;
  }

  for (i = degree - 1u; i < data_length - 1u; i++) {
    hi = i + 1u;
    for (j = 0u; j < degree; j++) {
      hj = i - j;
      coefficients[j] += (data[hi] * data[hj]);
      for (k = j; k < degree; k++) {
        mat[j][k] += (data[hj] * data[i - k]);
      }
    }
  }

  for (i = 0u; i < degree; i++) {
    coefficients[i] /= (data_length - degree);
    for (j = i; j < degree; j++) {
      mat[i][j] /= (data_length - degree);
      mat[j][i] = mat[i][j];
    }
  }

  _SolveLE(mat, coefficients, degree);

  return;
}

/* _AutoRegression */
static float32_t* _AutoRegression(float32_t* data, uint16_t data_length,
                                  uint8_t degree) {
  uint16_t i;

  float32_t* reduced_data = k_mem_pool;
  // float32_t mean = _Mean(data, data_length);
  for (i = 0; i < data_length; ++i) {
    reduced_data[i] = data[i] - k_mean;
  }

  float32_t* coefficients = k_mem_pool + data_length;
  float32_t* mat = coefficients + degree;

  for (i = 0; i < degree; ++i) {
    k_mat[i] = mat + i * degree;
  }

  _ARLeastSquare(reduced_data, data_length, degree, coefficients, k_mat);

  return coefficients;
}

/* _NumPeaks */
static uint16_t _NumPeaks(float32_t* data, uint16_t data_length,
                          uint8_t range) {
  uint16_t num_peaks = 0u, i = 0u, count = 0u;
  float32_t* p = &data[range];

  while (p < &data[data_length - range - 1u]) {
    while (i++ < range) {
      if ((*p > *(p - i)) && (*p > *(p + i))) {
        count += 1u;
      }
      // i++;
    }

    if (count == range) {
      p += (range + 1u);
      num_peaks += 1u;
    } else {
      p++;
    }

    count = 0u;
    i = 0u;
  }

  return num_peaks;
}

float32_t _AutoCorrelation(const float32_t* data, uint16_t data_length,
                           uint8_t lag) {
  // double mean = _Mean(data, data_length);
  // // double variance = _Variance(data, data_length, 0);
  // double variance = _Variance(data, data_length, 0U);

  float32_t sum = .0;
  const float32_t* p = &data[lag];
  // const float* q = &data[data_length - 1 - lag];
  uint16_t i = (uint16_t)lag;
  while (i++ < data_length) {
    // sum += ((double)*p++ - mean) * ((double)*q-- - mean);
    float32_t sum2p = (*p - k_mean) * (*(p - lag) - k_mean);
    sum += sum2p;
    p++;
  }

  float32_t result = sum / ((data_length - (uint16_t)lag) * k_variance);
  // printf("result: %f\n", result);

  return result;
}

static float32_t _Covariance(const float32_t* x, const float32_t* y,
                             const uint16_t length, const float32_t x_mean,
                             const float32_t y_mean) {
  float32_t covariance = .0;

  uint16_t i;

  for (i = 0; i < length; ++i) {
    float32_t delta1 = x[i] - x_mean;
    float32_t delta2 = y[i] - y_mean;
    covariance += (delta1 * delta2 - covariance) / (i + 1);
  }

  return covariance;
}

/* TODO: 此函数的准确性需要再做一次验证. */
static void _AggregateLinearTrend(float32_t* data, uint16_t data_length,
                                  uint16_t chunk_length,
                                  uint8_t aggregate_method,
                                  float32_t* intercept, float32_t* sterrest,
                                  float32_t* slope) {
  /* (x, y) pairs to fit. */
  float32_t* x = k_mem_pool;
  float32_t* y = x + data_length / chunk_length + 1u;

  /* the last chunk length might < chunk_length. */
  uint16_t last_chunk_length = data_length % chunk_length;

  uint16_t linreg_length = 0u;
  float32_t* p = data;
  while (p < &data[data_length - 1]) {
    float32_t* chunk = p;
    uint16_t length = ((p + (chunk_length - 1) <= &data[data_length - 1])
                           ? chunk_length
                           : last_chunk_length);
    if (aggregate_method == 0u) {
      y[linreg_length] = _Mean(p, length);
    } else if (aggregate_method == 1u) {
      y[linreg_length] = _Variance(p, length, 0u);
    } else {
      float32_t max_val = *p;
      float32_t* q = p;
      while (++q < p + length) {
        if (max_val < *q) {
          max_val = *q;
        }
      }
      y[linreg_length] = max_val;
    }

    x[linreg_length] = linreg_length;

    linreg_length++;
    p += length;
  }

  float32_t x_mean = _Mean(x, linreg_length);
  float32_t y_mean = _Mean(y, linreg_length);

  float32_t ssxym = _Covariance(x, y, linreg_length, x_mean, y_mean);
  float32_t ssxm = _Covariance(x, x, linreg_length, x_mean, x_mean);
  float32_t ssym = _Covariance(y, y, linreg_length, y_mean, y_mean);

  float32_t r = ssxym / sqrtf(ssxm * ssym);
  if (r > 1.0) {
    r = 1.0;
  } else if (r < -1.0) {
    r = -1.0;
  }

  if (sterrest) {
    *sterrest = sqrtf((1.0 - powf(r, 2)) * ssym / ssxm / (linreg_length - 2));
  }

  if (slope) {
    *slope = ssxym / ssxm;
  }

  if (intercept) {
    *intercept = y_mean - (ssxym / ssxm) * x_mean;
  }

  return;
}

/* 默认排序过 */
static float32_t _Quantile(const float32_t* data, uint32_t data_length,
                           float32_t q) {
  float32_t qIndexRight = 1.0 + (data_length - 1.0) * q;
  float32_t qIndexLeft = floor(qIndexRight);
  float32_t fraction = qIndexRight - qIndexLeft;
  uint32_t qIndex = (uint32_t)qIndexLeft;
  float32_t quantile =
      data[qIndex - 1u] + (data[qIndex] - data[qIndex - 1u]) * fraction;
  return quantile;
}

/*
 * TODO: 该函数与仿真结果有细微差异，需明确原因.
 */
static float32_t _BinnedEntropy(float32_t* data, uint16_t data_length,
                                uint16_t max_bins) {
  float32_t min = data[0];
  float32_t max = data[data_length - 1u];

  float32_t bin_range = (max - min) / max_bins;
  float32_t bin;

  float32_t binned_entropy = 0.0;
  float32_t* p = data;
  uint16_t count = 0u;
  float32_t left_edge = min, right_edge = min + bin_range;

  while (p <= &data[data_length - 1]) {    
    if ((*p >= left_edge) && (*p < right_edge)) {
      // printf("left_edge: %f, right_edge: %f\n", left_edge, right_edge);
      count++;
      p++;
    } else {
      if (p == &data[data_length - 1]) {
        p++;  /*<< make sure to quit loop.  */
        count++;
      }
      // printf("count: %u\n", count);

      bin = (float32_t)count / (float32_t)data_length;
      if (bin == .0) {
        bin = 1.0;
      }
      binned_entropy -= (bin * logf(bin));
      
      left_edge = right_edge;
      right_edge += bin_range;
      if (right_edge > max) {
        right_edge = max;
      }

      count = 0;
    }
  }

  return binned_entropy;
}

static float32_t _RatioBeyondSigma(float32_t* data, uint16_t data_length,
                                   float32_t r) {
  float r_sigma = r * sqrtf(k_variance);

  uint16_t i;
  uint16_t count = 0u;
  for (i = 0; i < data_length; ++i) {
    if (fabs(data[i] - k_mean) > r_sigma) {
      count += 1;
    }
  }

  float32_t result = (float32_t)count / (float32_t)data_length;

  return result;
}

static float32_t _ChangeQuantile(float32_t* data, uint16_t data_length,
                                 float32_t qh, float32_t ql, bool is_abs,
                                 uint8_t method) {
  uint16_t i;
  float32_t* diff = k_mem_pool;
  uint16_t diff_length = 0u;

  for (i = 1u; i < data_length; ++i) {
    if (((data[i] >= ql) && (data[i - 1] >= ql)) &&
        ((data[i] <= qh) && (data[i - 1] <= qh))) {
      if (is_abs) {
        diff[diff_length++] = fabs(data[i] - data[i - 1]);
      } else {
        diff[diff_length++] = data[i] - data[i - 1];
      }
    }
  }

  if (method == 0u) {
    return _Mean(diff, diff_length);
  } else {
    return _Variance(diff, diff_length, 0u);
  }
}


float32_t LempelZivComplexity(float32_t* data, uint16_t data_length, uint16_t num_bins) {
  uint16_t i, j;
  
  float32_t val_max = data[0], val_min = data[0];
  for (i = 0; i < data_length; ++i) {
    if (data[i] > val_max) {
      val_max = data[i];
    }

    if (data[i] < val_min) {
      val_min = data[i];
    }
  }
  float32_t interval = (val_max - val_min) / (double)(num_bins - 1);

  /* Get bins with the length of num_bins. */
  float32_t *bins = k_mem_pool;
  uint8_t bins_length = 0u;
  while (bins_length < num_bins) {
    bins[bins_length++] = val_min + interval * bins_length;
  }

  /* Get sequence. */
  float32_t *sequence = bins + bins_length;
  uint16_t sequence_length = 0;
  for (i = 0; i < data_length; ++i) {
    for (j = 0; j < bins_length; ++j) {
      if (data[i] <= bins[j]) {
        sequence[sequence_length++] = j;
        break;
      } else if (data[i] > bins[bins_length - 1]) {
        sequence[sequence_length++] = bins_length;
        break;
      }
    }
  }

  uint8_t *ind_set = k_ind_set;
  uint8_t *inc_set = k_inc_set;
  uint8_t ind_set_len = 0;
  uint16_t ind = 0, inc = 1;
  while (ind + inc < sequence_length) {
    uint8_t flag = 0;

    for (i = 0; i < ind_set_len; ++i) {
      uint8_t num_matched = 0;
      if (inc == inc_set[i]) {
        for (j = 0; j < inc; ++j) {
          if (sequence[ind + j] == sequence[ind_set[i] + j]) {
            num_matched++;
          }
        }

        if (num_matched == inc) {
          flag = 1;
        }
      }
    }

    if (flag) {
      inc++;
    } else {
      ind_set[ind_set_len] = ind;
      inc_set[ind_set_len] = inc;
      ind_set_len++;

      ind = ind + inc;
      inc = 1;
    }
  }

  return (float32_t)ind_set_len / (float32_t)sequence_length;
}


uint16_t LongestStrikeAboveMean(float32_t *data, uint16_t data_length) {
  uint16_t longest_strike = 0, longest_strike_temp = 0;
  float32_t *p = data, *q = data;
  
  while (q <= &data[data_length - 1]) {
    if ((*p > k_mean) && (*q > k_mean)) {
      longest_strike_temp += 1;
      q++;
    } else {
      p = q + 1;
      q = p;
      longest_strike_temp = 0;
    }

    if (longest_strike_temp > longest_strike) {
      longest_strike = longest_strike_temp;
    }
  }

  return longest_strike;
}


typedef struct _value2index 
{
  float32_t value;
  int32_t index;
} value2index;

static int CmpValue(const void *a, const void *b)
{
  if (((value2index*)a)->value - ((value2index*)b)->value > 0)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

static value2index src[5];
static value2index dst[5];

float32_t PermutationEntropy(float32_t *data, uint16_t data_length, uint8_t tau, uint8_t dimension) {
  uint16_t i, j, k;

  uint8_t* ind_set = k_ind_set;
  uint8_t ind_set_len = 0;

  uint8_t* num_set = k_inc_set;
  uint8_t num_set_len = 0;
  
  for (i = 0; i < 128; ++i) {
    ind_set[i] = 1;
    num_set[i] = 0;
  }

  for (i = 0; i < data_length - dimension + 1; ++i) {
    if (ind_set[i] == 0) {
      continue;
    }

    uint8_t counter = 1;
    ind_set[i] = 0;

    /* np.argsort(np.argsort(X)). */
    for (k = 0; k < 5; ++k) {
      src[k].index = k;
      src[k].value = data[i + k];
    }
    qsort(src, 5, sizeof(value2index), CmpValue);
    for (k = 0; k < 5; ++k) {
      src[k].value = src[k].index;
      src[k].index = k;
    }
    qsort(src, 5, sizeof(value2index), CmpValue);

    // printf("\n");
    // for (k = 0; k < 5; ++k) {
    //   printf("%d, ", src[k].index);
    // }

    for (j = i + 1; j < data_length - dimension + 1; ++j) {
      if (ind_set[j] == 0) {
        continue;
      }
      
      for (k = 0; k < 5; ++k) {
        dst[k].index = k;
        dst[k].value = data[j + k];
      }
      qsort(dst, 5, sizeof(value2index), CmpValue);
      for (k = 0; k < 5; ++k) {
        dst[k].value = dst[k].index;
        dst[k].index = k;
      }
      qsort(dst, 5, sizeof(value2index), CmpValue);

      uint8_t num_mapped = 0;
      for (k = 0; k < 5; ++k) {
        if (src[k].index == dst[k].index) {
          num_mapped += 1;
        }
      }

      if (num_mapped == 5) {
        ind_set[j] = 0;
        counter++;
      }
    }

    num_set[num_set_len++] = counter;
  }

  float32_t sum = .0f;
  for (i = 0; i < num_set_len; ++i) {
    float32_t prob = (float32_t)num_set[i] / (data_length - dimension + 1);
    sum = sum + prob * logf(prob);
  }

  return -sum;
}

static void _SortFunc(float32_t* data, uint16_t data_length) {
  float32_t temp;
  uint32_t i, j;
  // Sort the array nums in ascending order
  for (i = 0; i < data_length - 1; i++) {
    for (j = i + 1; j < data_length; j++) {
      if (data[j] < data[i]) {
        // swap elements
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }

  return;
}

static float _ExtractFeatsGreen(float32_t* data, uint16_t data_length,
                                union NonwearEntry* feats) {
  uint16_t i;

  /* First compute variance and mean to avoid repetitive computation in each
   * function. */
  k_variance = _Variance(data, (uint16_t)data_length, 0u);
  k_mean = _Mean(data, (uint16_t)data_length);

  /* ppg__ar_2 */
  float32_t* coefficients = _AutoRegression(data, data_length, 10u);
  feats[0].fvalue = coefficients[2];
  printf("ppg__ar_2: %f\n", feats[0].fvalue);

  /* ppg__number_peaks__n_3 */
  uint16_t num_peaks = _NumPeaks(data, data_length, 3u);
  feats[1].fvalue = (float32_t)num_peaks;
  printf("ppg__number_peaks__n_3: %f\n", feats[1].fvalue);

  /* ppg__autocorrelation__lag_4 */
  float32_t auto_correlation_lag4 = _AutoCorrelation(data, data_length, 4u);
  feats[2].fvalue = auto_correlation_lag4;
  printf("ppg__autocorrelation__lag_4: %f\n", feats[2].fvalue);

  /* ppg-g__agg_linear_trend__attr_"stderr"__chunk_len_5__f_agg_"var" */
  float32_t sterrest = .0f;
  _AggregateLinearTrend(data, data_length, 5u, 1u, NULL, &sterrest, NULL);
  feats[3].fvalue = sterrest;
  printf("ppg__agg_linear_trend__f_agg_var__chunk_len_5__attr_stderr: %f\n", feats[3].fvalue);

  /* ppg-g__agg_linear_trend__attr_"stderr"__chunk_len_10__f_agg_"mean" */
  _AggregateLinearTrend(data, data_length, 10u, 0u, NULL, &sterrest, NULL);
  feats[4].fvalue = sterrest;
  printf("ppg__agg_linear_trend__f_agg_mean__chunk_len_10__attr_stderr: %f\n", feats[4].fvalue);

  /* ppg-g__agg_linear_trend__attr_"stderr"__chunk_len_10__f_agg_"max" */
  _AggregateLinearTrend(data, data_length, 10u, 2u, NULL, &sterrest, NULL);
  feats[5].fvalue = sterrest;
  printf("ppg-g__agg_linear_trend__attr_stderr__chunk_len_10__f_agg_max: %f\n", feats[5].fvalue);

  /* ppg-g__permutation_entropy__dimension_5__tau_1 */
  float32_t permutation_entropy= PermutationEntropy(data, data_length, 1u, 5u);
  feats[6].fvalue = permutation_entropy;
  printf("ppg-g__permutation_entropy__dimension_5__tau_1: %f\n", feats[6].fvalue);

  /* ppg-g__lempel_ziv_complexity__bins_100 */
  float32_t lempel_ziv_complexity = LempelZivComplexity(data, data_length, 100u);
  feats[7].fvalue = lempel_ziv_complexity;
  printf("ppg-g__lempel_ziv_complexity__bins_100: %f\n", feats[7].fvalue);  

  /* sort data. */
  float32_t* data_sorted = k_mem_pool;
  for (i = 0u; i < data_length; ++i) {
    data_sorted[i] = data[i];
  }
  _SortFunc(data_sorted, data_length);

  float32_t q_000 = data_sorted[0];
  float32_t q_020 = _Quantile(data_sorted, data_length, 0.20);
  float32_t q_025 = _Quantile(data_sorted, data_length, 0.25);
  float32_t q_040 = _Quantile(data_sorted, data_length, 0.40);
  float32_t q_075 = _Quantile(data_sorted, data_length, 0.75);
  float32_t q_080 = _Quantile(data_sorted, data_length, 0.80);
  float32_t q_100 = data_sorted[data_length - 1];

  /* ppg__binned_entropy__max_bins_10 */
  float32_t binned_entropy = _BinnedEntropy(data_sorted, data_length, 10u);
  feats[8].fvalue = binned_entropy;
  printf("ppg__binned_entropy__max_bins_10: %f\n", binned_entropy);

  /*
   * ppg-g__change_quantiles__f_agg_"mean"__isabs_True__qh_0.2__ql_0.0
   * ppg-g__change_quantiles__f_agg_"mean"__isabs_True__qh_1.0__ql_0.8
   * ppg-g__change_quantiles__f_agg_"var"__isabs_True__qh_1.0__ql_0.0
   * ppg-g__change_quantiles__f_agg_"mean"__isabs_True__qh_0.8__ql_0.4
   */
  float32_t cq_000_020 =
      _ChangeQuantile(data, data_length, q_020, q_000, true, 0u);
  float32_t cq_080_100 =
      _ChangeQuantile(data, data_length, q_100, q_080, true, 0u);
  float32_t cq_000_100 =
      _ChangeQuantile(data, data_length, q_100, q_000, true, 1u);
  float32_t cq_080_040 =
      _ChangeQuantile(data, data_length, q_080, q_040, true, 0u);
  feats[9].fvalue = cq_000_020;
  feats[10].fvalue = cq_080_100;
  feats[11].fvalue = cq_000_100;
  feats[12].fvalue = cq_080_040;
  printf("ppg-g__change_quantiles__f_agg_mean__isabs_True__qh_0.2__ql_0.0: %f\n", feats[9].fvalue);
  printf("ppg-g__change_quantiles__f_agg_mean__isabs_True__qh_1.0__ql_0.8: %f\n", feats[10].fvalue);
  printf("ppg-g__change_quantiles__f_agg_var__isabs_True__qh_1.0__ql_0.0: %f\n", feats[11].fvalue);
  printf("ppg-g__change_quantiles__f_agg_mean__isabs_True__qh_0.8__ql_0.4: %f\n", feats[12].fvalue);

  /* ppg__ratio_beyond_r_sigma__r_1.5 */
  float32_t ratio_beyond_r_sigma = _RatioBeyondSigma(data, data_length, 1.5f);
  feats[13].fvalue = ratio_beyond_r_sigma;
  printf("ppg__ratio_beyond_r_sigma__r_1.5: %f\n", feats[13].fvalue);

  /* ppg-g__minimum */
  float32_t minimum = q_000;
  feats[14].fvalue = minimum;
  printf("ppg__minimum: %f\n", feats[14].fvalue);  


  /* 返回最大值, 用于基于最大值的判断条件. */
  float32_t maxVal = q_075 + 1.5 * (q_075 - q_025);

  return maxVal;
}

static float _ExtractFeatsIR(float32_t* data, uint16_t data_length,
                             union NonwearEntry* feats) {
  uint16_t i;

  /* First compute variance and mean to avoid repetitive computation in each
   * function. */
  k_variance = _Variance(data, (uint16_t)data_length, 0u);
  k_mean = _Mean(data, (uint16_t)data_length);

  /* ppg-ir__number_peaks__n_3 */
  uint16_t num_peaks = _NumPeaks(data, data_length, 3u);
  feats[0].fvalue = (float32_t)num_peaks;
  printf("ppg-ir__number_peaks__n_3: %f\n", feats[0].fvalue);

  /* ppg-ir__number_peaks__n_10 */
  num_peaks = _NumPeaks(data, data_length, 10u);
  feats[1].fvalue = (float32_t)num_peaks;
  printf("ppg-ir__number_peaks__n_10: %f\n", feats[1].fvalue);

  /* ppg-ir__autocorrelation__lag_2 */
  float32_t autocorrelation__lag_2 = _AutoCorrelation(data, data_length, 2u);
  feats[2].fvalue = autocorrelation__lag_2;
  printf("ppg-ir__autocorrelation__lag_2: %f\n", feats[2].fvalue);

  /* ppg-ir__agg_linear_trend__attr_"intercept"__chunk_len_50__f_agg_"max" */
  float32_t intercept = .0f;
  _AggregateLinearTrend(data, data_length, 50u, 2u, &intercept, NULL, NULL);
  feats[3].fvalue = intercept;
  printf("ppg-ir__agg_linear_trend__attr_intercept__chunk_len_50__f_agg_max: %f\n", feats[3].fvalue);

  /* ppg-ir__agg_linear_trend__attr_"stderr"__chunk_len_10__f_agg_"mean" */
  float32_t sterrest = 0.0f;
  _AggregateLinearTrend(data, data_length, 10u, 0u, NULL, &sterrest, NULL);
  feats[4].fvalue = sterrest;
  printf("ppg-ir__agg_linear_trend__attr_stderr__chunk_len_10__f_agg_mean: %f\n", feats[4].fvalue);

  /* ppg-ir__agg_linear_trend__attr_"stderr"__chunk_len_10__f_agg_"max" */
  _AggregateLinearTrend(data, data_length, 10u, 2u, NULL, &sterrest, NULL);
  feats[5].fvalue = sterrest;
  printf("ppg-ir__agg_linear_trend__attr_stderr__chunk_len_10__f_agg_max: %f\n", feats[5].fvalue);

  /* ppg-ir__agg_linear_trend__attr_"stderr"__chunk_len_5__f_agg_"max" */
  _AggregateLinearTrend(data, data_length, 5u, 2u, NULL, &sterrest, NULL);
  feats[6].fvalue = sterrest;
  printf("ppg-ir__agg_linear_trend__attr_stderr__chunk_len_5__f_agg_max: %f\n", feats[6].fvalue);

  /* ppg-ir__ar_0 */
  float32_t* coefficients = _AutoRegression(data, data_length, 10u);
  feats[7].fvalue = coefficients[0];
  printf("ppg-ir__ar_0: %f\n", feats[7].fvalue);  

  /* ppg-ir__lempel_ziv_complexity__bins_100 */
  float32_t lempel_ziv_complexity = LempelZivComplexity(data, data_length, 100u);
  feats[8].fvalue = lempel_ziv_complexity;
  printf("ppg-ir__lempel_ziv_complexity__bins_100: %f\n", feats[8].fvalue); 

  /* ppg-ir__number_peaks__n_1 */
  num_peaks = _NumPeaks(data, data_length, 1u);
  feats[9].fvalue = (float32_t)num_peaks;
  printf("ppg-ir__number_peaks__n_1: %f\n", feats[9].fvalue);

  /* ppg-ir__longest_strike_above_mean */
  uint16_t longest_strike = LongestStrikeAboveMean(data, data_length);
  feats[10].fvalue = (float32_t)longest_strike;
  printf("ppg-ir__longest_strike_above_mean: %f\n", feats[10].fvalue);

  /* sort data. */
  float32_t* data_sorted = k_mem_pool;
  for (i = 0u; i < data_length; ++i) {
    data_sorted[i] = data[i];
  }
  // qsort(data_sorted, data_length, sizeof(float32_t), _CmpFunc);
  _SortFunc(data_sorted, data_length);

  float32_t q_020 = _Quantile(data_sorted, data_length, 0.20);
  float32_t q_025 = _Quantile(data_sorted, data_length, 0.25);
  float32_t q_040 = _Quantile(data_sorted, data_length, 0.40);
  float32_t q_060 = _Quantile(data_sorted, data_length, 0.60);
  float32_t q_075 = _Quantile(data_sorted, data_length, 0.75);
  float32_t q_080 = _Quantile(data_sorted, data_length, 0.80);
  float32_t q_100 = data_sorted[data_length - 1];

  /* ppg__binned_entropy__max_bins_10 */
  float32_t binned_entropy = _BinnedEntropy(data_sorted, data_length, 10u);
  feats[11].fvalue = binned_entropy;
  printf("binned_entropy: %f\n", feats[11].fvalue);

  /*
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_1.0__ql_0.8
   * ppg__change_quantiles__f_agg_"var"__isabs_True__qh_1.0__ql_0.8
   */
  float32_t cq_false_080_100 =
      _ChangeQuantile(data, data_length, q_100, q_080, false, 1u);
  float32_t cq_true_080_100 =
      _ChangeQuantile(data, data_length, q_100, q_080, true, 1u);
  float32_t cq_true_060_020 =
      _ChangeQuantile(data, data_length, q_060, q_020, true, 0u);
  float32_t cq_true_080_040 =
      _ChangeQuantile(data, data_length, q_080, q_040, true, 0u);          
  feats[12].fvalue = cq_false_080_100;
  feats[13].fvalue = cq_true_080_100;
  feats[14].fvalue = cq_true_060_020;
  feats[15].fvalue = cq_true_080_040;
  printf("cq_false_080_100: %f\n", feats[12].fvalue);
  printf("cq_true_080_100: %f\n", feats[13].fvalue);
  printf("cq_true_060_020: %f\n", feats[14].fvalue);
  printf("cq_true_080_040: %f\n", feats[15].fvalue);

  /* 返回最大值, 用于基于最大值的判断条件. */
  float32_t maxVal = q_075 + 1.5 * (q_075 - q_025);

  return maxVal;
}

static uint8_t _Postprocess(float proba) {
  if (proba >= NWC_PROBA_TH) {
    return 1u;
  } else {
    return 0u;
  }
}

uint8_t NonWearCheck(nwc_bioSignal_t* s, bool init) {
  static uint8_t cPtr, rPtr;
  static uint8_t checkResults[NWC_CHECK_RESULTS_SIZE];
  static uint8_t ruleResults[NWC_RULE_RESULTS_SIZE];
  static uint16_t call_counter;

  uint16_t i;

  /* Initialization */
  if (init) {
    cPtr = 0u;
    for (i = 0u; i < NWC_CHECK_RESULTS_SIZE; i++) {
      checkResults[i] = 0u;
    }

    rPtr = 0u;
    for (i = 0u; i < NWC_RULE_RESULTS_SIZE; i++) {
      ruleResults[i] = 0u;
    }

    call_counter = 0u;

    return 0u;
  }

  call_counter += 1u;

  /* push the oldest values. */
  _Roll(k_ppg, NWC_PPG_LENGTH, (int16_t)s->sample_length);

  /* pull the newest values. */
  for (i = 0; i < (uint16_t)s->sample_length; ++i) {
    k_ppg[NWC_PPG_LENGTH - s->sample_length + i] =
        (float32_t)(s->sig_t.signal[i] - 5000000) / 1000.0;  // (float32_t)s->sig_t.signal[i];
  }

  if (call_counter < 2u) {
    return 0u;
  }

  // for (i = 0; i < NWC_PPG_LENGTH; ++i) {
  //   printf("k_ppg[%u]: %f\n", i, k_ppg[i]);
  // }

  /* Model result */
  float32_t proba = .0f, maxVal = .0f;
  if (s->sensor_type == NWC_SOURCE_PPG_G) {
    float32_t maxVal = _ExtractFeatsGreen(k_ppg, NWC_PPG_LENGTH, k_feats);
    proba = PredictGreen(k_feats);
    ruleResults[rPtr++] = maxVal < NWC_LOWER_PPG_TH_G ? 1u : 0u;
  } else if (s->sensor_type == NWC_SOURCE_PPG_IR) {
    float32_t maxVal = _ExtractFeatsIR(k_ppg, NWC_PPG_LENGTH, k_feats);
    proba = PredictIr(k_feats);
    ruleResults[rPtr++] = maxVal < NWC_LOWER_PPG_TH_IR ? 1u : 0u;
  } else {
    return 0u;
  }

  // for (i = 0; i < 9; ++i) {
  //   printf("[%u]: %f\n", i, k_feats[i].fvalue);
  // }
  printf("proba: %f\n", proba);

  /* Accept a 2-time consistant results from model */
  uint8_t checkResult = _Postprocess(proba);
  checkResults[cPtr++] = checkResult;
  if (cPtr == NWC_CHECK_RESULTS_SIZE) {
    cPtr = 0u;
  }

  uint8_t counts = 0u;
  uint8_t min_consecutive_counts =
      s->min_consecutive_counts >= 5u ? s->min_consecutive_counts : 5u;
  uint8_t j = min_consecutive_counts;
  while (j--) {
    counts += checkResults[((int32_t)(cPtr - 1 - j) + NWC_CHECK_RESULTS_SIZE) %
                           NWC_CHECK_RESULTS_SIZE];
  }

  /* Accept a 3-time consistant results from rule */
  if (rPtr == NWC_RULE_RESULTS_SIZE) {
    rPtr = 0u;
  }
  uint8_t ruleCounts = 0u;
  for (i = 0u; i < NWC_RULE_RESULTS_SIZE; ++i) {
    ruleCounts += ruleResults[i];
  }
  // printf("ruleCounts: %u\n", ruleCounts);

  /* TODO: 优先相信极低的DC值还是优先相信模型结果 */
  // if (counts == min_consecutive_counts) {
  //   return counts;
  // } else if (ruleCounts == NWC_RULE_RESULTS_SIZE) {
  //   return 255u;
  // } else {
  //   return 0u;
  // }

  if (ruleCounts == NWC_RULE_RESULTS_SIZE) {
    return 255u;
  } else if (counts == min_consecutive_counts) {
    return counts;
  } else {
    return 0u;
  }
}