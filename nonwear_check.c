#include "nonwear_check.h"

#include <math.h>
// #include <stdio.h>
#include <stdlib.h>

#include "nonwear_ar_solver.h"
#include "nonwear_arm_rfft_fast_f64.h"
#include "nonwear_model.h"

extern nonwear_arm_status nonwear_arm_rfft_64_fast_init_f64(
    nonwear_arm_rfft_fast_instance_f64* S);

#define NWC_HANN_SCALE (0.041666666666666664353702032031)
#define NWC_FEATS_LENGTH (35u)
#define NWC_PROBA_TH (0.6f)  // min prob to comfirm nonwear
#define NWC_CHECK_RESULTS_SIZE (10u)
// #define NWC_FEAT_SIZE (21u)
#define NWC_LOWER_PPG_TH (500u)
#define NWC_RULE_RESULTS_SIZE (6u)

// /* hann_window */
const static float64_t k_hann_window[64] = {
    0.000000000000000000000000000000, 0.002407636663901591145275915551,
    0.009607359798384784710378880845, 0.021529832133895587809035987448,
    0.038060233744356630758431947470, 0.059039367825822530733148596482,
    0.084265193848727326653147429170, 0.113494773318631503311593178296,
    0.146446609406726269142495766573, 0.182803357918177367125167620543,
    0.222214883490199022197941758350, 0.264301631587001151224569639453,
    0.308658283817455136865959275383, 0.354857661372768862229065689462,
    0.402454838991935903713681454974, 0.450991429835219670430035421305,
    0.500000000000000000000000000000, 0.549008570164780440592267041211,
    0.597545161008064207308621007542, 0.645142338627231137770934310538,
    0.691341716182544918645191955875, 0.735698368412998959797732823063,
    0.777785116509801088824360704166, 0.817196642081822743897134841973,
    0.853553390593273730857504233427, 0.886505226681368552199558052962,
    0.915734806151272673346852570830, 0.940960632174177469266851403518,
    0.961939766255643369241568052530, 0.978470167866104523213266475068,
    0.990392640201615215289621119155, 0.997592363336098464365875315707,
    1.000000000000000000000000000000, 0.997592363336098464365875315707,
    0.990392640201615215289621119155, 0.978470167866104523213266475068,
    0.961939766255643369241568052530, 0.940960632174177469266851403518,
    0.915734806151272673346852570830, 0.886505226681368552199558052962,
    0.853553390593273730857504233427, 0.817196642081822854919437304488,
    0.777785116509801088824360704166, 0.735698368412998959797732823063,
    0.691341716182545140689796880906, 0.645142338627231137770934310538,
    0.597545161008064207308621007542, 0.549008570164780218547662116180,
    0.500000000000000000000000000000, 0.450991429835219892474640346336,
    0.402454838991935792691378992458, 0.354857661372768862229065689462,
    0.308658283817454970332505581609, 0.264301631587001151224569639453,
    0.222214883490199022197941758350, 0.182803357918177145080562695512,
    0.146446609406726269142495766573, 0.113494773318631669845046872069,
    0.084265193848727326653147429170, 0.059039367825822530733148596482,
    0.038060233744356741780734409986, 0.021529832133895587809035987448,
    0.009607359798384784710378880845, 0.002407636663901535634124684293};

static float64_t k_ppg[64u];
static float64_t k_mem_pool[256u];
static float64_t* k_mat[10u];
static float64_t k_variance;
static float64_t k_mean;

static inline int _CmpFunc(const void* a, const void* b) {
  return (*(float64_t*)a > *(float64_t*)b) ? 1 : -1;
}

/*
 * _Mean
 */
static float64_t _Mean(const float64_t* data, uint32_t data_length) {
  uint32_t count;      /*<< loop counter */
  float64_t sum = 0.0; /*<< temporary result storage */

  /* Initialize counter with number of samples */
  count = data_length;
  while (count > 0U) {
    sum += *data++;
    count--;
  }

  float64_t mean = (sum / data_length);

  return mean;
}

/*
 * _Variance
 */
static float64_t _Variance(const float64_t* data, uint32_t data_length,
                           uint32_t ddof) {
  uint32_t counter;    /*<< loop counter */
  float64_t sum = 0.0; /*<< temporary result storage */
  float64_t f_sum = 0.0;
  float64_t f_mean, f_value;
  const float64_t* p_input = data;

  if (data_length <= 1U) {
    return .0;
  }

  /* Initialize counter with number of samples */
  counter = data_length;
  while (counter > 0U) {
    sum += *p_input++;
    counter--;
  }

  f_mean = sum / data_length;

  p_input = data;
  counter = data_length;
  while (counter > 0U) {
    f_value = *p_input++ - f_mean;
    f_sum += f_value * f_value;

    counter--;
  }

  /* Variance */
  float64_t variance = f_sum / (data_length - ddof);

  return variance;
}

/*
 * _Kurtosis
 * 1.0/(n-2)/(n-3) * ((n**2-1.0)*m4/m2**2.0 - 3*(n-1)**2.0)
 */
static float64_t _Kurtosis(float64_t* data, uint32_t data_length) {
  float64_t M4 = .0;
  float64_t M2 = k_variance;
  uint32_t i;

  for (i = 0; i < data_length; i++) {
    float64_t x = (data[i] - k_mean);
    M4 += (x * x * x * x) / data_length;
  }

  float64_t kurtosis = (1.0 / (data_length - 2.0) / (data_length - 3.0)) *
                       ((data_length * data_length - 1.0) * M4 / (M2 * M2) -
                        3.0 * ((data_length - 1.0) * (data_length - 1.0)));

  return kurtosis;
}

/*
 * AbsoluteSumOfChanges
 */
static float64_t _AbsoluteSumOfChanges(float64_t* data, uint32_t data_length) {
  float64_t result = .0;

  uint32_t i;
  for (i = 0; i < data_length - 1; ++i) {
    result += fabs(data[i + 1] - data[i]);
  }

  return result;
}

/*
 * _AutoCorrelation
 */
static float64_t _AutoCorrelation(const float64_t* data, uint32_t data_length,
                                  uint8_t lag) {
  float64_t sum = .0;
  const float64_t* p = &data[lag];
  // const float* q = &data[data_length - 1 - lag];
  uint32_t i = (uint32_t)lag;
  while (i++ < data_length) {
    // sum += ((double)*p++ - mean) * ((double)*q-- - mean);
    float64_t sum2p = (*p - k_mean) * (*(p - lag) - k_mean);
    sum += sum2p;
    p++;
  }

  float64_t result = sum / ((data_length - (uint32_t)lag) * k_variance);

  return result;
}

static float64_t* _SpktWelchDensity(float64_t* data, uint32_t data_length) {
  float64_t* temp_data = k_mem_pool;
  float64_t* results = k_mem_pool + data_length;

  uint32_t i;
  for (i = 0; i < data_length; ++i) {
    temp_data[i] = (data[i] - k_mean) * k_hann_window[i];
  }

  nonwear_arm_rfft_fast_instance_f64 S;
  nonwear_arm_rfft_64_fast_init_f64(&S);
  nonwear_arm_rfft_fast_f64(&S, temp_data, results, 0);

  for (i = 0; i < data_length; i += 2) {
    results[i] = (pow(results[i], 2) + pow(results[i + 1], 2)) * NWC_HANN_SCALE;
  }

  float64_t* p = &results[1];
  float64_t* q = p + 1;
  while (p != &results[(int)(data_length / 2)]) {
    *p = *q;
    *p = (*p) * 2;
    q += 2;
    p++;
  }

  return results;
}

/*
   Gaussian elimination solver
   Author: Rainer Hegger Last modified: Aug 14th, 1998
   Modified (for personal style and context) by Paul Bourke
*/
static float64_t* _AutoRegression(float64_t* data, uint32_t data_length,
                                  uint8_t degree) {
  uint32_t i, j;

  float64_t* reduced_data = k_mem_pool;
  float64_t* coefficients = reduced_data + data_length;
  float64_t* mat = coefficients + degree;

  for (i = 0; i < degree; ++i) {
    k_mat[i] = mat + (i + 1) * degree;
  }

  for (i = 0; i < data_length; ++i) {
    reduced_data[i] = data[i] - k_mean;
  }

  ARLeastSquare(reduced_data, data_length, degree, coefficients, k_mat);

  return coefficients;
}

/*
 * data assumed to be sorted.
 */
void _ReoccuringProperty(float64_t* data, uint32_t data_length,
                         float64_t* unique2all, float64_t* sum_reoccuring,
                         float64_t* reoccuring_times2all) {
  if (data_length == 0u) {
    return;
  }

  float64_t* p = data;
  float64_t* q = data;
  uint32_t counts = 1u;
  uint32_t unique_counts = 1u;
  uint32_t reoccuring_counts = 0u;

  while (q++ != &data[data_length - 1]) {
    if (*q != *p) {
      unique_counts += 1u;
      if (counts > 1) {
        reoccuring_counts += counts;
        *sum_reoccuring += counts * (*p);
      }

      p = q;
      counts = 1;
    } else {
      counts++;

      /* the last element should be added if it is repeated more than 2 times */
      if (q == &data[data_length - 1]) {
        reoccuring_counts += counts;
        *sum_reoccuring += counts * (*p);
      }
    }
  }

  *unique2all = unique_counts / (float64_t)data_length;
  *reoccuring_times2all = (float64_t)reoccuring_counts / data_length;

  return;
}

/* 默认排序过 */
static float64_t _Quantile(const float64_t* data, uint32_t data_length,
                           float64_t q) {
  float64_t qIndexRight = 1.0 + (data_length - 1.0) * q;
  float64_t qIndexLeft = floor(qIndexRight);
  float64_t fraction = qIndexRight - qIndexLeft;
  uint32_t qIndex = (uint32_t)qIndexLeft;
  float64_t quantile =
      data[qIndex - 1u] + (data[qIndex] - data[qIndex - 1u]) * fraction;
  return quantile;
}

static float64_t _ChangeQuantile(float64_t* data, uint32_t data_length,
                                 float64_t qh, float64_t ql, bool is_abs,
                                 uint8_t method) {
  uint32_t i;
  float64_t* diff = k_mem_pool;
  uint32_t diff_length = 0u;

  for (i = 1; i < data_length; ++i) {
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

static void _SortFunc(float64_t* data, uint32_t data_length) {
  float64_t temp;
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

static float _ExtractFeats(float64_t* data, uint32_t data_length,
                           union NonwearEntry* feats) {
  uint32_t i;
  /* First compute variance and mean to avoid repetitive computation in each
   * function. */
  k_variance = _Variance(data, data_length, 0u);
  k_mean = _Mean(data, data_length);

  /* ppg__kurtosis */
  feats[0].fvalue = _Kurtosis(data, data_length);

  /* ppg__absolute_sum_of_changes */
  feats[1].fvalue = _AbsoluteSumOfChanges(data, data_length);

  /*
   * ppg__autocorrelation__lag_1
   * ppg__autocorrelation__lag_2
   * ppg__autocorrelation__lag_3
   * ppg__autocorrelation__lag_4
   * ppg__autocorrelation__lag_5
   * ppg__autocorrelation__lag_6
   */
  feats[2].fvalue = _AutoCorrelation(data, data_length, 1u);
  feats[3].fvalue = _AutoCorrelation(data, data_length, 2u);
  feats[4].fvalue = _AutoCorrelation(data, data_length, 3u);
  feats[5].fvalue = _AutoCorrelation(data, data_length, 4u);
  feats[6].fvalue = _AutoCorrelation(data, data_length, 5u);
  feats[7].fvalue = _AutoCorrelation(data, data_length, 6u);

  /*
   * ppg__spkt_welch_density__coeff_2
   * ppg__spkt_welch_density__coeff_5
   * ppg__spkt_welch_density__coeff_8
   */
  float64_t* spk_welch_densities = _SpktWelchDensity(data, data_length);
  feats[8].fvalue = spk_welch_densities[2];
  feats[9].fvalue = spk_welch_densities[5];
  feats[10].fvalue = spk_welch_densities[8];

  /*
   * ppg__ar_coefficient__k_10__coeff_0
   * ppg__ar_coefficient__k_10__coeff_1
   * ppg__ar_coefficient__k_10__coeff_2',
   */
  float64_t* ar_coefficients = _AutoRegression(data, data_length, 10);
  feats[11].fvalue = ar_coefficients[0];
  feats[12].fvalue = ar_coefficients[1];
  feats[13].fvalue = ar_coefficients[2];

  float64_t* data_sorted = k_mem_pool;
  for (i = 0; i < data_length; ++i) {
    data_sorted[i] = data[i];
  }
  // qsort(data_sorted, data_length, sizeof(float64_t), _CmpFunc);
  _SortFunc(data_sorted, data_length);

  float64_t q_000 = data_sorted[0];
  float64_t q_020 = _Quantile(data_sorted, data_length, 0.20);
  float64_t q_025 = _Quantile(data_sorted, data_length, 0.25);
  float64_t q_040 = _Quantile(data_sorted, data_length, 0.40);
  float64_t q_060 = _Quantile(data_sorted, data_length, 0.60);
  float64_t q_075 = _Quantile(data_sorted, data_length, 0.75);
  float64_t q_080 = _Quantile(data_sorted, data_length, 0.80);
  float64_t q_100 = data_sorted[data_length - 1];

  /*
   * ppg__ratio_value_number_to_time_series_length
   * ppg__sum_of_reoccurring_data_points
   * ppg__percentage_of_reoccurring_values_to_all_values
   */
  float64_t unique2all = .0, sum_reoccuring = .0, reoccuring_times2all = .0;
  _ReoccuringProperty(data_sorted, data_length, &unique2all, &sum_reoccuring,
                      &reoccuring_times2all);
  feats[14].fvalue = unique2all;
  feats[15].fvalue = sum_reoccuring;
  feats[16].fvalue = reoccuring_times2all;

  /* ppg__iqrs */
  float64_t iqr = q_075 - q_025;
  feats[17].fvalue = iqr;

  /*
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_0.2__ql_0.0
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_0.4__ql_0.0
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_0.8__ql_0.0
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_1.0__ql_0.0
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_1.0__ql_0.2
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_0.6__ql_0.4
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_0.8__ql_0.4
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_1.0__ql_0.4
   * ppg__change_quantiles__f_agg_"var"__isabs_False__qh_1.0__ql_0.8
   * */
  bool is_abs = false;
  feats[18].fvalue =
      _ChangeQuantile(data, data_length, q_020, q_000, is_abs, 1);
  feats[19].fvalue =
      _ChangeQuantile(data, data_length, q_040, q_000, is_abs, 1);
  feats[20].fvalue =
      _ChangeQuantile(data, data_length, q_080, q_000, is_abs, 1);
  feats[21].fvalue =
      _ChangeQuantile(data, data_length, q_100, q_000, is_abs, 1);
  feats[22].fvalue =
      _ChangeQuantile(data, data_length, q_100, q_020, is_abs, 1);
  feats[23].fvalue =
      _ChangeQuantile(data, data_length, q_060, q_040, is_abs, 1);
  feats[24].fvalue =
      _ChangeQuantile(data, data_length, q_080, q_040, is_abs, 1);
  feats[25].fvalue =
      _ChangeQuantile(data, data_length, q_100, q_040, is_abs, 1);
  feats[26].fvalue =
      _ChangeQuantile(data, data_length, q_100, q_080, is_abs, 1);

  /*
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.2__ql_0.0
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.4__ql_0.0
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.8__ql_0.0
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.4__ql_0.2
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.6__ql_0.2
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.6__ql_0.4
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_0.8__ql_0.4
   * ppg__change_quantiles__f_agg_"mean"__isabs_True__qh_1.0__ql_0.6
   */
  is_abs = true;
  feats[27].fvalue =
      _ChangeQuantile(data, data_length, q_020, q_000, is_abs, 0);
  feats[28].fvalue =
      _ChangeQuantile(data, data_length, q_040, q_000, is_abs, 0);
  feats[29].fvalue =
      _ChangeQuantile(data, data_length, q_080, q_000, is_abs, 0);
  feats[30].fvalue =
      _ChangeQuantile(data, data_length, q_040, q_020, is_abs, 0);
  feats[31].fvalue =
      _ChangeQuantile(data, data_length, q_060, q_020, is_abs, 0);
  feats[32].fvalue =
      _ChangeQuantile(data, data_length, q_060, q_040, is_abs, 0);
  feats[33].fvalue =
      _ChangeQuantile(data, data_length, q_080, q_040, is_abs, 0);
  feats[34].fvalue =
      _ChangeQuantile(data, data_length, q_100, q_060, is_abs, 0);

  /* 返回最大值, 用于基于最大值的判断条件. */
  float64_t maxVal = q_075 + 1.5 * iqr;

  return maxVal;
}

/* _Postprocess */
static uint8_t _Postprocess(float64_t proba) {
  if (proba >= NWC_PROBA_TH) {
    return 1u;
  } else {
    return 0u;
  }
}

/* NonWearCheck */
uint8_t NonWearCheck(bioSignal_t* s, bool init) {
  static int32_t cPtr, rPtr;
  static uint8_t checkResults[NWC_CHECK_RESULTS_SIZE];
  static uint8_t ruleResults[NWC_RULE_RESULTS_SIZE];

  uint32_t i;

  /* Initialization */
  if (init) {
    cPtr = 0;
    for (i = 0; i < NWC_CHECK_RESULTS_SIZE; i++) {
      checkResults[i] = 0u;
    }

    rPtr = 0;
    for (i = 0; i < NWC_RULE_RESULTS_SIZE; i++) {
      ruleResults[i] = 0u;
    }

    return 0u;
  }

  /* Cast to float64_t */
  for (i = 0; i < s->sample_length; ++i) {
    k_ppg[i] = (float64_t)(s->sig_t.signal[i]);
  }

  /* Extract features */
  union NonwearEntry feats[NWC_FEATS_LENGTH];
  float64_t maxVal = _ExtractFeats(k_ppg, (uint32_t)s->sample_length, feats);

  /* Model result */
  float64_t predProba = .0f;
  if (s->sensor_type == ALG_SOURCE_PPG_G) {
    predProba = PredictGreen(feats);
  } else if (s->sensor_type == ALG_SOURCE_PPG_IR) {
    predProba = PredictIr(feats);
  } else {
    return 0u;
  }
  // printf("predProba: %f\n", predProba);

  /* Accept a 2-time consistant results from model */
  uint8_t checkResult = _Postprocess(predProba);
  checkResults[cPtr++] = checkResult;
  if (cPtr == NWC_CHECK_RESULTS_SIZE) {
    cPtr = 0u;
  }
  // uint8_t sum = 0u;
  uint8_t counts = 0u;
  uint8_t min_consecutive_counts =
      s->min_consecutive_counts >= 4u ? s->min_consecutive_counts : 4u;
  uint8_t j = min_consecutive_counts;
  while (j--) {
    counts += checkResults[((int32_t)(cPtr - 1 - j) + NWC_CHECK_RESULTS_SIZE) %
                           NWC_CHECK_RESULTS_SIZE];
  }

  /* Accept a 3-time consistant results from rule */
  ruleResults[rPtr++] = maxVal < NWC_LOWER_PPG_TH ? 1u : 0u;
  if (rPtr == NWC_RULE_RESULTS_SIZE) {
    rPtr = 0u;
  }
  uint8_t ruleCounts = 0u;
  for (i = 0u; i < NWC_RULE_RESULTS_SIZE; ++i) {
    ruleCounts += ruleResults[i];
  }

  /* TODO: 优先相信极低的DC值还是优先相信模型结果 */
  if (counts == min_consecutive_counts) {
    return counts;
  } else if (ruleCounts == NWC_RULE_RESULTS_SIZE) {
    return 255u;
  } else {
    return 0u;
  }
}