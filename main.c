#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nonwear_check.h"
#include "test_data.h"

#define ARRAY_SIZE (64)

int main(int argc, char **argv) {
  // 输入结构体
  bioSignal_t s;

  s.time_stamp = NULL;
  s.serial_number = 0;

  s.sensor_type = ALG_SOURCE_PPG_G;

  // 初始化算法
  NonWearCheck(NULL, true);

  // 调用算法
  s.sample_length = ARRAY_SIZE;
  int32_t i;
  for (i = 0; i <= test_length - ARRAY_SIZE; i += ARRAY_SIZE) {
    s.sig_t.signal = test;
    uint8_t res = NonWearCheck(&s, false);
    if (res > 0) {
      printf("res: %u\n", res);
    }
  }

  return 0;
}
