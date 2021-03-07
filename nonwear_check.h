#ifndef __NONWEAR_CHECK_H__
#define __NONWEAR_CHECK_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  NWC_SOURCE_ECG = 0,
  NWC_SOURCE_ACC = 0,
  NWC_SOURCE_PPG_G,
  NWC_SOURCE_PPG_IR
} nwc_bioSigSource_t;

typedef struct {
  nwc_bioSigSource_t sensor_type;
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
  uint8_t* led;
  uint8_t is_from_ui;
} nwc_bioSignal_t;

uint8_t NonWearCheck(nwc_bioSignal_t* s, bool init);

uint8_t NonWearCheckToAir(nwc_bioSignal_t* s, bool init);

#endif /* __NONWEAR_CHECK_H__ */
