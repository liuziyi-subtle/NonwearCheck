// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "nonwear_check.h"
// #include "test_data.h"

// #define ARRAY_SIZE (64)

// int main(int argc, char **argv) {
//   int32_t i;

//   /* 输入结构体 */
//   nwc_bioSignal_t s;

//   s.time_stamp = NULL;
//   s.serial_number = 0;
//   s.sensor_type = NWC_SOURCE_PPG_G;
//   s.sample_length = ARRAY_SIZE;

// #ifdef DEBUG_ONE
//   /* 调用算法 */
//   NonWearCheck(NULL, true);
//   for (i = 0; i < data_length; i += ARRAY_SIZE) {
//     s.sig_t.signal = &data[i];
//     uint8_t res = NonWearCheck(&s, false);
//   }
// #else
//   FILE *fpIn = fopen(pathIn, "r");
//   if (fpIn == NULL) {
//     printf("Cannot open file %s !", dir->d_name);
//     exit(-1);
//   }
//   printf("Processing %s\n", pathIn);

//   char *line = data_malloc(sizeof(char) * 1024);
//   fgets(line, 1024, fpIn);
//   fgets(line, 1024, fpIn);

//   while (fgets(line, 1024, fpIn)) {
//     for (tok = strtok(line, ","); tok && *tok; i++, tok = strtok(NULL,
//     ",\n")) {
//       switch (i) {
//         case (0):
//           ppg[num_rows] = (int32_t)atoi(tok);
//           break;
//         case (2):
//           segment_id = (int32_t)atoi(tok);
//           break;
//         default:
//           continue;
//       }

//       if (num_rows == 0) {
//         last_segment_id = segment_id;
//       }

//       if (segment_id != last_segment_id) {
//         NonWearCheck(NULL, true);
//       }

//       /* 每满128个数据，进入一次算法调用. 在算法调用时，分两次送入算法. */
//       if (num_rows % 128 == 0) {
//         int j = 0;
//         while
//           for (j = 0; j < 2; j++) {
//             uint8_t pred = NonWearCheck(&ppg[num_rows], false);
//           }
// #ifdef DEBUG
//         Debug.pred[Debug.pred_length++] = pred;
// #endif
//       }
//       ppg[num_rows] = (int32_t)atoi(tok);
//     }

// #endif

//   return 0;
// }

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "../nonwear_check.h"
#include "debug.h"

char target_dirs[5000][1000]; /* 作为局部变量定义在stack会过大. */
char target_filenames[5000][1000];

int main(int argc, char **argv) {
  uint16_t i = 0, j = 0;

  /* 输入结构体 */
  nwc_bioSignal_t s;
  s.time_stamp = NULL;
  s.serial_number = 0;
  s.sensor_type = NWC_SOURCE_PPG_G;
  s.sample_length = 64;
  s.is_from_ui = 0;

#if ALGO_DEBUG == 1
  char path[1000];

  uint16_t p_count =
      ListFilesRecursively(argv[1], ".csv", target_dirs, target_filenames);

  int16_t accx[1000000];
  int16_t accy[1000000];
  int16_t accz[1000000];
  while (i < p_count) {
    snprintf(path, 1000, "%s/%s", target_dirs[i], target_filenames[i]);
    DebugInit(&PLOT);

    uint16_t acc_length = ReadMTKData(path, 2, accx, accy, accz, 1000000);

    NonWalkCheck(NULL, NULL, NULL, 0, 0, 1);
    for (j = 0u; j < acc_length; j += 25) {
      NonWalkCheck(&accx[j], &accy[j], &accz[j], 25, 0, 0);
      uint8_t result = NonWalkCheck(NULL, NULL, NULL, 25, 1, 0);
      PLOT.results[PLOT.results_length++] = result;
    }

    snprintf(path, 1000, "%s/%s", argv[2], target_filenames[i]);
    WriteInt(path, PLOT.results, PLOT.results_length);

    i++;
  }
#else
#include "test_data.c"

  NonWearCheck(NULL, 1);
  for (i = 0u; i < test_data_length; i += 64) {
    s.sig_t.signal = &test_data[i];
    printf("start----------------\n");
    uint8_t res = NonWearCheck(&s, 0);
    if (res == 0) {
      printf("%u res: %u\n", i, res);
    }
    printf("end ----------------\n");
  }

#endif /* ALGO_DEBUG */

  return 0;
}
