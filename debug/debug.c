#ifdef ALGO_DEBUG

#include "debug.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

INTERMEDIATES PLOT = {{0}, 0,   {0}, 0,   {0}, 0,   {0}, 0,   {0},
                      0,   {0}, 0,   {0}, 0,   {0}, 0,   {0}, 0};

/* Init*/
void DebugInit() {
  PLOT.num_peaks_accys_length = 0;
  PLOT.maximum_acczs_length = 0;
  PLOT.medain_acczs_length = 0;
  PLOT.ar_1s_length = 0;
  PLOT.agg_autocorrelations_length = 0;
  PLOT.cq_040_080s_length = 0;
  PLOT.probas_length = 0;
  PLOT.preds_length = 0;
  PLOT.results_length = 0;
}

/* 获取所有满足target_format格式的文件路径. */
uint16_t ListFilesRecursively(char *base_dir, char *target_format,
                              char (*target_dirs)[1000],
                              char (*target_filenames)[1000]) {
  // char dir[1000];
  // char path[1000];
  struct dirent *dp;
  DIR *dir = opendir(base_dir);

  uint16_t num_targets = 0;

  /* Unable to open directory stream. */
  if (!dir) {
    return num_targets;
  }

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
      /* Construct new path from our base dir. */
      // snprintf(path, 900, "%s/%s", base_dir, dp->d_name);

      if (strstr(dp->d_name, target_format)) {
        strcpy(*target_dirs, base_dir);
        strcpy(*target_filenames, dp->d_name);

        target_dirs += 1;
        target_filenames += 1;
        num_targets += 1;
      }

      char *base_dir_temp[1000];
      snprintf(base_dir_temp, 900, "%s/%s", base_dir, dp->d_name);
      uint16_t num_targets_temp = ListFilesRecursively(
          base_dir_temp, target_format, target_dirs, target_filenames);
      target_dirs += num_targets_temp;
      target_filenames += num_targets_temp;
      num_targets += num_targets_temp;
    }
  }

  closedir(dir);

  return num_targets;
}

uint16_t ReadMTKData(const char *path, uint8_t value_category_id, int16_t *accx,
                     int16_t *accy, int16_t *accz, uint16_t length) {
  uint16_t counter = 0;

  FILE *fp_in = fopen(path, "r");
  char *line = malloc(1024);
  while (fgets(line, 1024, fp_in)) {
    uint16_t i = 0;
    char *tok = strtok(line, ",");

    /* 如果不是指定的值类型则结束循环. */
    if (value_category_id != (uint8_t)atoi(tok)) {
      continue;
    }

    for (tok; tok && *tok; i++, tok = strtok(NULL, ",\n")) {
      /* 满足条件则赋值. */
      switch (i) {
        case (1):
          accx[counter] = ((int16_t)atoi(tok)) >> 6;
          break;
        case (2):
          accy[counter] = ((int16_t)atoi(tok)) >> 6;
          break;
        case (3):
          accz[counter] = ((int16_t)atoi(tok)) >> 6;
          break;
        default:
          continue;
      }
    }

    ++counter;
    // if (++counter > length) {
    //   exit(0);
    // }
  }
  fclose(fp_in);

  return counter;
}

/* 写入整型中间变量. */
void WriteInt(const char *path, uint8_t *data, uint32_t dataSize) {
  // printf("path: %s\n", path);
  FILE *fp = fopen(path, "w");
  uint32_t m;
  for (m = 0; m < dataSize; ++m) {
    fprintf(fp, "%u\n", data[m]);
  }
  fclose(fp);
}

/* 写入浮点类型中间变量 */
void WriteFloat(char *path, float *data, int32_t dataSize) {
  FILE *fp = fopen(path, "w");
  int32_t m;
  for (m = 0; m < dataSize; ++m) {
    fprintf(fp, "%f\n", data[m]);
  }
  fclose(fp);
}

#endif /* ALGO_DEBUG */
