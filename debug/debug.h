#ifdef ALGO_DEBUG

#include <stdint.h>

#define MAX_LENGTH (1000000)

typedef struct {
  float num_peaks_accys[MAX_LENGTH];
  uint32_t num_peaks_accys_length;

  float maximum_acczs[MAX_LENGTH];
  uint32_t maximum_acczs_length;

  float medain_acczs[MAX_LENGTH];
  uint32_t medain_acczs_length;

  float ar_1s[MAX_LENGTH];
  uint32_t ar_1s_length;

  float agg_autocorrelations[MAX_LENGTH];
  uint32_t agg_autocorrelations_length;

  float cq_040_080s[MAX_LENGTH];
  uint32_t cq_040_080s_length;

  float probas[MAX_LENGTH];
  uint32_t probas_length;

  float preds[MAX_LENGTH];
  uint32_t preds_length;

  uint8_t results[MAX_LENGTH];
  uint32_t results_length;
} INTERMEDIATES;

extern INTERMEDIATES PLOT;

void DebugInit();

uint16_t ListFilesRecursively(char *base_dir, char *target_format,
                              char (*target_dirs)[1000],
                              char (*target_filenames)[1000]);

uint16_t ReadMTKData(const char *path, uint8_t value_category_id,
                     int16_t accx[], int16_t accy[], int16_t accz[],
                     uint16_t length);

#endif /* ALGO_DEBUG */
