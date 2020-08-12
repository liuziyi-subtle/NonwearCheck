#include <stdbool.h>
#include <stdint.h>

// #ifdef DEBUG_LOCAL
typedef enum {
  ALG_SOURCE_ECG = 0,
  ALG_SOURCE_PPG_G,
  ALG_SOURCE_PPG_IR
} bioSigSource_t;

typedef struct {
  bioSigSource_t sensor_type;
  int32_t sample_length;
  uint32_t* time_stamp;
  union {
    int32_t* signal;
    struct {
      int32_t* x;
      int32_t* y;
      int32_t* z;
    } acc_t;
  } sig_t;
  int32_t* serial_number;
  uint8_t min_consecutive_counts;
} bioSignal_t;
// #endif  // DEBUG_LOCAL

typedef float float32_t;
typedef double float64_t;

uint8_t NonWearCheck(bioSignal_t* s, bool init);