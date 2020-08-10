#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static const float threshold[] = {
    7.5f,       8.5f,       9.5f,       10.5f,      11.5f,      12.5f,
    13.5f,      14.5f,      15.5f,      16.5f,      17.5f,      18.5f,
    0.5f,       1.5f,       2.5f,       3.5f,       4.5f,       5.5f,
    6.5f,       0.306666f,  0.308036f,  0.348561f,  0.471194f,  0.484319f,
    0.504152f,  0.548312f,  0.558102f,  0.59727f,   0.627722f,  0.647683f,
    0.69189f,   0.801257f,  0.871435f,  0.873313f,  0.873671f,  0.886948f,
    0.88975f,   0.892367f,  0.903465f,  0.924384f,  0.934075f,  0.940702f,
    0.972171f,  -1103.64f,  -992.787f,  -990.09f,   -987.028f,  -962.744f,
    -959.272f,  -958.082f,  -957.839f,  -956.575f,  -954.361f,  -953.59f,
    -945.946f,  -875.611f,  -630.442f,  -379.364f,  -315.968f,  -153.45f,
    -133.341f,  672.156f,   1082.68f,   1082.78f,   1159.08f,   1159.11f,
    1164.3f,    1169.87f,   1404.45f,   2099.83f,   2154.92f,   2188.57f,
    2189.61f,   2190.1f,    2225.64f,   2279.25f,   2386.77f,   2446.06f,
    2452.98f,   2453.0f,    2453.0f,    2454.15f,   2456.3f,    2456.42f,
    2462.34f,   2467.45f,   2479.66f,   2804.95f,   2841.97f,   2876.04f,
    2912.49f,   2934.19f,   2959.45f,   3046.56f,   3404.34f,   3465.39f,
    3996.44f,   4012.64f,   4265.07f,   4271.5f,    4272.38f,   4305.96f,
    4306.5f,    4320.72f,   4609.89f,   4674.6f,    4700.05f,   4724.41f,
    4736.03f,   4746.36f,   4791.85f,   5248.86f,   5250.98f,   5255.63f,
    5261.47f,   5300.27f,   5302.7f,    5311.25f,   5393.05f,   5552.87f,
    5814.4f,    6172.32f,   6468.1f,    6555.76f,   6993.85f,   7213.16f,
    7271.03f,   7287.35f,   7314.18f,   7316.24f,   7316.91f,   7317.33f,
    7319.04f,   7321.45f,   7321.62f,   7541.29f,   7562.69f,   7563.04f,
    7643.53f,   10270.5f,   10306.5f,   10313.9f,   10342.6f,   10862.6f,
    10973.6f,   11023.6f,   15107.0f,   17628.6f,   20538.4f,   24139.8f,
    26501.9f,   29433.7f,   29435.8f,   32916.1f,   32934.9f,   86230.0f,
    86259.4f,   86305.6f,   86320.7f,   97039.2f,   0.0560998f, 0.0563036f,
    0.0680548f, 0.0692146f, 0.0795738f, 0.0796108f, 0.0925119f, 0.118171f,
    0.119295f,  0.119986f,  0.135683f,  0.143005f,  0.146946f,  0.147205f,
    0.172421f,  0.187489f,  0.189334f,  0.213244f,  0.213388f,  0.21535f,
    0.234396f,  0.32656f,   0.373416f,  0.37347f,   0.375124f,  0.401254f,
    0.497575f,  0.664391f,  0.678281f,  0.688692f,  0.697751f,  0.702342f,
    0.73277f,   0.762227f,  0.946872f,  1.17771f,   1.2784f,    1.41735f,
    2.5794f,    2.78534f,   4.69312f,   9.30159f,   22.4309f,   0.0411917f,
    0.0690988f, 0.0690993f, 0.0862111f, 0.0922067f, 0.0995721f, 0.104078f,
    0.105545f,  0.122201f,  0.124244f,  0.156996f,  0.157009f,  0.163307f,
    0.323168f,  0.359783f,  0.694927f,  2.99301f,   3.36302f,   3.36674f,
    13.5169f,   15.9456f,   1.14558f,   1.14706f,   1.26001f,   1.34517f,
    1.42766f,   1.53208f,   1.57195f,   1.61371f,   1.63214f,   1.64133f,
    1.68556f,   1.6862f,    1.6928f,    1.77981f,   1.80979f,   1.87342f,
    1.87461f,   1.8869f,    1.89351f,   1.91106f,   1.91383f,   1.94736f,
    1.96162f,   1.99485f,   1.99874f,   2.00193f,   2.03972f,   2.04833f,
    2.06577f,   2.06587f,   2.08719f,   2.09041f,   2.11722f,   2.14109f,
    2.16127f,   2.16448f,   0.0811349f, 0.0970331f, 0.105238f,  0.136812f,
    0.210573f,  0.226829f,  0.232819f,  0.277026f,  0.28827f,   0.290878f,
    0.540133f,  0.691538f,  0.714155f,  0.72077f,   0.843575f,  0.966564f,
    1.13007f,   1.44018f,   1.51821f,   1.71643f,   2.18234f,   2.28466f,
    2.60191f,   3.15677f,   3.17128f,   5.86855f,   29.8585f,   31.8172f,
    84.9897f,   293.232f,   458.878f,   778.513f,   0.0383786f, 0.0395225f,
    0.0830075f, 0.0834234f, 0.238872f,  1.43173f,   6.28368f,   24.2839f,
    34.42f,
};
static const int th_begin[] = {
    0, 12, 19, 43, 160, 203, 224, 260, 292,
};

static const int th_len[] = {
    12, 7, 24, 117, 43, 21, 36, 32, 9,
};

static inline int quantize(float val, unsigned fid) {
  const float* array = &threshold[th_begin[fid]];
  int len = th_len[fid];
  int low = 0;
  int high = len;
  int mid;
  float mval;
  if (val < array[0]) {
    return -10;
  }
  while (low + 1 < high) {
    mid = (low + high) / 2;
    mval = array[mid];
    if (val == mval) {
      return mid * 2;
    } else if (val < mval) {
      high = mid;
    } else {
      low = mid;
    }
  }
  if (array[low] == val) {
    return low * 2;
  } else if (high == len) {
    return len * 2;
  } else {
    return low * 2 + 1;
  }
}

float PredictIr(union NonwearEntry* data) {
  float sum = 0.0f;
  for (int i = 0; i < 9; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 12) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.592332f;
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 10) {
        if (!(data[3].missing != -1) || data[3].qvalue < 72) {
          if (!(data[2].missing != -1) || data[2].qvalue < 16) {
            sum += 0.415385f;
          } else {
            sum += -0.514286f;
          }
        } else {
          sum += 0.583562f;
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 0) {
          if (!(data[5].missing != -1) || data[5].qvalue < 30) {
            sum += 0.516667f;
          } else {
            sum += -0.138462f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 6) {
            sum += 0.133333f;
          } else {
            sum += -0.556565f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 42) {
      if (!(data[4].missing != -1) || data[4].qvalue < 32) {
        if (!(data[4].missing != -1) || data[4].qvalue < 14) {
          sum += 0.595581f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 176) {
            sum += 0.573842f;
          } else {
            sum += 0.351724f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 132) {
          if (!(data[1].missing != -1) || data[1].qvalue < 10) {
            sum += 0.552542f;
          } else {
            sum += 0.275676f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 218) {
            sum += -0.134118f;
          } else {
            sum += 0.556364f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 42) {
        if (!(data[6].missing != -1) || data[6].qvalue < 22) {
          if (!(data[3].missing != -1) || data[3].qvalue < 142) {
            sum += 0.57037f;
          } else {
            sum += 0.375f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 134) {
            sum += 0.347368f;
          } else {
            sum += -0.140426f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 102) {
          if (!(data[2].missing != -1) || data[2].qvalue < 24) {
            sum += -0.12f;
          } else {
            sum += 0.490909f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 22) {
            sum += -0.453333f;
          } else {
            sum += 0.342857f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 12) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.459426f;
    } else {
      if (!(data[8].missing != -1) || data[8].qvalue < 4) {
        if (!(data[3].missing != -1) || data[3].qvalue < 82) {
          if (!(data[2].missing != -1) || data[2].qvalue < 20) {
            sum += 0.318111f;
          } else {
            sum += -0.417273f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 12) {
            sum += 0.453979f;
          } else {
            sum += 0.14484f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 0) {
          if (!(data[4].missing != -1) || data[4].qvalue < 80) {
            sum += 0.360204f;
          } else {
            sum += -0.314307f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 14) {
            sum += -0.0904684f;
          } else {
            sum += -0.431139f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 42) {
      if (!(data[4].missing != -1) || data[4].qvalue < 28) {
        if (!(data[4].missing != -1) || data[4].qvalue < 12) {
          sum += 0.462932f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 176) {
            sum += 0.446838f;
          } else {
            sum += 0.288788f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 170) {
          if (!(data[0].missing != -1) || data[0].qvalue < 14) {
            sum += 0.151916f;
          } else {
            sum += 0.443502f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 216) {
            sum += -0.293676f;
          } else {
            sum += 0.451926f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 42) {
        if (!(data[6].missing != -1) || data[6].qvalue < 24) {
          if (!(data[3].missing != -1) || data[3].qvalue < 142) {
            sum += 0.446269f;
          } else {
            sum += 0.272365f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 2) {
            sum += 0.449972f;
          } else {
            sum += -0.0345711f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 150) {
          if (!(data[4].missing != -1) || data[4].qvalue < 62) {
            sum += 0.242511f;
          } else {
            sum += -0.137008f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 224) {
            sum += -0.458219f;
          } else {
            sum += 0.463623f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 12) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.398082f;
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 10) {
        if (!(data[3].missing != -1) || data[3].qvalue < 68) {
          if (!(data[2].missing != -1) || data[2].qvalue < 20) {
            sum += 0.365637f;
          } else {
            sum += -0.411802f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 6) {
            sum += 0.397217f;
          } else {
            sum += 0.56845f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 6) {
          if (!(data[3].missing != -1) || data[3].qvalue < 92) {
            sum += 0.0662864f;
          } else {
            sum += 0.366343f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 8) {
            sum += 0.0650942f;
          } else {
            sum += -0.362361f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 40) {
      if (!(data[4].missing != -1) || data[4].qvalue < 20) {
        sum += 0.397539f;
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 14) {
          if (!(data[7].missing != -1) || data[7].qvalue < 36) {
            sum += 0.29584f;
          } else {
            sum += -0.228227f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 170) {
            sum += 0.390052f;
          } else {
            sum += 0.226823f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 42) {
        if (!(data[2].missing != -1) || data[2].qvalue < 0) {
          if (!(data[4].missing != -1) || data[4].qvalue < 76) {
            sum += 0.417338f;
          } else {
            sum += 0.0607673f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 90) {
            sum += 0.39962f;
          } else {
            sum += 0.0960813f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 98) {
          if (!(data[3].missing != -1) || data[3].qvalue < 30) {
            sum += 0.396018f;
          } else {
            sum += 0.149655f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 224) {
            sum += -0.274424f;
          } else {
            sum += 0.377702f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 10) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.361284f;
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 18) {
        if (!(data[3].missing != -1) || data[3].qvalue < 74) {
          if (!(data[7].missing != -1) || data[7].qvalue < 0) {
            sum += 0.291602f;
          } else {
            sum += -0.354803f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 12) {
            sum += 0.375048f;
          } else {
            sum += 0.111373f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 0) {
          if (!(data[7].missing != -1) || data[7].qvalue < 42) {
            sum += 0.37782f;
          } else {
            sum += -0.0685595f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 20) {
            sum += -0.130915f;
          } else {
            sum += -0.337077f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 40) {
      if (!(data[4].missing != -1) || data[4].qvalue < 22) {
        if (!(data[3].missing != -1) || data[3].qvalue < 180) {
          sum += 0.368266f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 188) {
            sum += -0.583222f;
          } else {
            sum += 0.375017f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 14) {
          if (!(data[3].missing != -1) || data[3].qvalue < 160) {
            sum += 0.168197f;
          } else {
            sum += -0.213341f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 170) {
            sum += 0.351664f;
          } else {
            sum += 0.163633f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 34) {
        if (!(data[6].missing != -1) || data[6].qvalue < 12) {
          if (!(data[5].missing != -1) || data[5].qvalue < 40) {
            sum += 0.360723f;
          } else {
            sum += 0.0664385f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 44) {
            sum += 0.36586f;
          } else {
            sum += -0.0175988f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 100) {
          if (!(data[2].missing != -1) || data[2].qvalue < 22) {
            sum += 0.09262f;
          } else {
            sum += 0.353509f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 18) {
            sum += -0.272812f;
          } else {
            sum += 0.171203f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 10) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.338187f;
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 8) {
        if (!(data[3].missing != -1) || data[3].qvalue < 66) {
          if (!(data[8].missing != -1) || data[8].qvalue < 0) {
            sum += 0.223936f;
          } else {
            sum += -0.346866f;
          }
        } else {
          sum += 0.404792f;
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 0) {
          if (!(data[2].missing != -1) || data[2].qvalue < 46) {
            sum += 0.315112f;
          } else {
            sum += -0.0808356f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 50) {
            sum += -0.181919f;
          } else {
            sum += -0.324302f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 32) {
      if (!(data[4].missing != -1) || data[4].qvalue < 10) {
        sum += 0.346931f;
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 172) {
          if (!(data[6].missing != -1) || data[6].qvalue < 66) {
            sum += 0.332841f;
          } else {
            sum += 0.133491f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 190) {
            sum += -0.637218f;
          } else {
            sum += 0.348567f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 140) {
        if (!(data[0].missing != -1) || data[0].qvalue < 18) {
          if (!(data[3].missing != -1) || data[3].qvalue < 100) {
            sum += 0.297573f;
          } else {
            sum += -0.0564295f;
          }
        } else {
          sum += 0.376017f;
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 228) {
          if (!(data[6].missing != -1) || data[6].qvalue < 16) {
            sum += 0.16966f;
          } else {
            sum += -0.279652f;
          }
        } else {
          sum += 0.453799f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 10) {
    if (!(data[3].missing != -1) || data[3].qvalue < 2) {
      sum += 0.321636f;
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 20) {
        if (!(data[3].missing != -1) || data[3].qvalue < 80) {
          if (!(data[7].missing != -1) || data[7].qvalue < 2) {
            sum += 0.197651f;
          } else {
            sum += -0.32896f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 46) {
            sum += 0.496874f;
          } else {
            sum += 0.217948f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 20) {
          if (!(data[3].missing != -1) || data[3].qvalue < 154) {
            sum += 0.308357f;
          } else {
            sum += -0.276679f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 22) {
            sum += -0.0120832f;
          } else {
            sum += -0.291489f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 30) {
      if (!(data[4].missing != -1) || data[4].qvalue < 10) {
        sum += 0.331587f;
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 172) {
          if (!(data[2].missing != -1) || data[2].qvalue < 26) {
            sum += 0.309886f;
          } else {
            sum += 0.139638f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 190) {
            sum += -0.468699f;
          } else {
            sum += 0.310585f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 40) {
        if (!(data[4].missing != -1) || data[4].qvalue < 46) {
          if (!(data[1].missing != -1) || data[1].qvalue < 4) {
            sum += 0.0284631f;
          } else {
            sum += 0.353125f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 10) {
            sum += 0.259918f;
          } else {
            sum += -0.019271f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 100) {
          if (!(data[3].missing != -1) || data[3].qvalue < 28) {
            sum += 0.322125f;
          } else {
            sum += 0.0747352f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 228) {
            sum += -0.169891f;
          } else {
            sum += 0.418434f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 8) {
    if (!(data[3].missing != -1) || data[3].qvalue < 0) {
      sum += 0.304084f;
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 12) {
        if (!(data[3].missing != -1) || data[3].qvalue < 36) {
          sum += -0.274166f;
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 70) {
            sum += 0.342524f;
          } else {
            sum += 0.0380083f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 0) {
          if (!(data[3].missing != -1) || data[3].qvalue < 210) {
            sum += 0.240727f;
          } else {
            sum += -0.261961f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 44) {
            sum += -0.149958f;
          } else {
            sum += -0.288196f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 38) {
      if (!(data[4].missing != -1) || data[4].qvalue < 20) {
        if (!(data[4].missing != -1) || data[4].qvalue < 10) {
          sum += 0.321569f;
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 16) {
            sum += 0.178642f;
          } else {
            sum += 0.319657f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 52) {
          if (!(data[3].missing != -1) || data[3].qvalue < 168) {
            sum += 0.320683f;
          } else {
            sum += 0.121079f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 18) {
            sum += -0.097559f;
          } else {
            sum += 0.241379f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 138) {
        if (!(data[6].missing != -1) || data[6].qvalue < 26) {
          if (!(data[4].missing != -1) || data[4].qvalue < 64) {
            sum += 0.430066f;
          } else {
            sum += 0.234472f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 118) {
            sum += -0.0284754f;
          } else {
            sum += 0.323138f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 228) {
          if (!(data[7].missing != -1) || data[7].qvalue < 48) {
            sum += 0.0197515f;
          } else {
            sum += -0.275781f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 60) {
            sum += 0.391915f;
          } else {
            sum += 0.0885754f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 14) {
    if (!(data[0].missing != -1) || data[0].qvalue < 6) {
      if (!(data[3].missing != -1) || data[3].qvalue < 0) {
        sum += 0.284987f;
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 2) {
          if (!(data[7].missing != -1) || data[7].qvalue < 28) {
            sum += 0.335304f;
          } else {
            sum += -0.129922f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 8) {
            sum += 0.1344f;
          } else {
            sum += -0.263451f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 40) {
        if (!(data[3].missing != -1) || data[3].qvalue < 60) {
          if (!(data[3].missing != -1) || data[3].qvalue < 34) {
            sum += 0.1984f;
          } else {
            sum += -0.334449f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 24) {
            sum += 0.382372f;
          } else {
            sum += 0.126893f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 126) {
          if (!(data[3].missing != -1) || data[3].qvalue < 116) {
            sum += -0.0568767f;
          } else {
            sum += 0.510817f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 230) {
            sum += -0.248475f;
          } else {
            sum += 0.39789f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || data[3].qvalue < 170) {
      if (!(data[4].missing != -1) || data[4].qvalue < 58) {
        if (!(data[0].missing != -1) || data[0].qvalue < 16) {
          if (!(data[7].missing != -1) || data[7].qvalue < 26) {
            sum += 0.314649f;
          } else {
            sum += 0.158833f;
          }
        } else {
          sum += 0.315857f;
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 14) {
          if (!(data[6].missing != -1) || data[6].qvalue < 30) {
            sum += 0.121704f;
          } else {
            sum += -0.270837f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 8) {
            sum += 0.333041f;
          } else {
            sum += 0.0934713f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 200) {
        if (!(data[4].missing != -1) || data[4].qvalue < 8) {
          if (!(data[2].missing != -1) || data[2].qvalue < 34) {
            sum += 0.0150583f;
          } else {
            sum += 0.231954f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 8) {
            sum += 0.110347f;
          } else {
            sum += -0.47461f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 68) {
          if (!(data[3].missing != -1) || data[3].qvalue < 214) {
            sum += 0.364626f;
          } else {
            sum += 0.257479f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 32) {
            sum += 0.168726f;
          } else {
            sum += -0.266435f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 14) {
    if (!(data[0].missing != -1) || data[0].qvalue < 4) {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[3].missing != -1) || data[3].qvalue < 208) {
          if (!(data[3].missing != -1) || data[3].qvalue < 192) {
            sum += -0.0505778f;
          } else {
            sum += 0.409505f;
          }
        } else {
          sum += -0.28171f;
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 0) {
          sum += 0.242357f;
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 2) {
            sum += 0.241206f;
          } else {
            sum += -0.26506f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 44) {
        if (!(data[6].missing != -1) || data[6].qvalue < 48) {
          if (!(data[2].missing != -1) || data[2].qvalue < 44) {
            sum += 0.247916f;
          } else {
            sum += 0.604423f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 6) {
            sum += 0.221544f;
          } else {
            sum += -0.138163f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 148) {
          if (!(data[3].missing != -1) || data[3].qvalue < 122) {
            sum += -0.0169564f;
          } else {
            sum += 0.587794f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 220) {
            sum += -0.278247f;
          } else {
            sum += 0.0179635f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 12) {
      sum += 0.305018f;
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 170) {
        if (!(data[0].missing != -1) || data[0].qvalue < 18) {
          if (!(data[3].missing != -1) || data[3].qvalue < 30) {
            sum += 0.287072f;
          } else {
            sum += 0.0512289f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 36) {
            sum += 0.317712f;
          } else {
            sum += 0.0840941f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 200) {
          if (!(data[7].missing != -1) || data[7].qvalue < 32) {
            sum += 0.026944f;
          } else {
            sum += -0.401448f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 68) {
            sum += 0.268648f;
          } else {
            sum += -0.107412f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 14) {
    if (!(data[6].missing != -1) || data[6].qvalue < 38) {
      if (!(data[3].missing != -1) || data[3].qvalue < 158) {
        if (!(data[4].missing != -1) || data[4].qvalue < 82) {
          if (!(data[0].missing != -1) || data[0].qvalue < 2) {
            sum += -0.138289f;
          } else {
            sum += 0.228061f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 58) {
            sum += 0.919764f;
          } else {
            sum += 0.108581f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 36) {
          if (!(data[3].missing != -1) || data[3].qvalue < 206) {
            sum += -0.217634f;
          } else {
            sum += 0.514107f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 232) {
            sum += -0.314277f;
          } else {
            sum += -0.0837383f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 20) {
        if (!(data[3].missing != -1) || data[3].qvalue < 76) {
          if (!(data[3].missing != -1) || data[3].qvalue < 10) {
            sum += 0.257137f;
          } else {
            sum += -0.283774f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 6) {
            sum += 0.382164f;
          } else {
            sum += 0.14892f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 8) {
          sum += 0.293958f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 2) {
            sum += 0.0371967f;
          } else {
            sum += -0.230608f;
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 12) {
      sum += 0.298451f;
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 20) {
        if (!(data[3].missing != -1) || data[3].qvalue < 30) {
          sum += 0.287582f;
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 22) {
            sum += 0.30062f;
          } else {
            sum += -0.0324093f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 48) {
          sum += 0.313604f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 152) {
            sum += 0.282945f;
          } else {
            sum += -0.111787f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 16) {
    if (!(data[0].missing != -1) || data[0].qvalue < 8) {
      if (!(data[3].missing != -1) || data[3].qvalue < 86) {
        if (!(data[7].missing != -1) || data[7].qvalue < 4) {
          sum += 0.159046f;
        } else {
          sum += -0.270898f;
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 120) {
          sum += 0.371801f;
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 12) {
            sum += 0.165086f;
          } else {
            sum += -0.169156f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 2) {
        sum += 0.303678f;
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 56) {
          if (!(data[3].missing != -1) || data[3].qvalue < 22) {
            sum += 0.254293f;
          } else {
            sum += -0.376835f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 180) {
            sum += 0.312463f;
          } else {
            sum += 0.0676584f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 54) {
      if (!(data[7].missing != -1) || data[7].qvalue < 30) {
        if (!(data[3].missing != -1) || data[3].qvalue < 78) {
          if (!(data[3].missing != -1) || data[3].qvalue < 12) {
            sum += 0.182194f;
          } else {
            sum += -0.157582f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 30) {
            sum += 0.186143f;
          } else {
            sum += 0.543086f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 146) {
          if (!(data[3].missing != -1) || data[3].qvalue < 124) {
            sum += 0.0433314f;
          } else {
            sum += 0.531335f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 222) {
            sum += -0.171304f;
          } else {
            sum += 0.146487f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 16) {
        sum += 0.279909f;
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 6) {
          if (!(data[4].missing != -1) || data[4].qvalue < 54) {
            sum += 0.101623f;
          } else {
            sum += -0.241653f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 18) {
            sum += -0.281718f;
          } else {
            sum += 0.0991509f;
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || data[2].qvalue < 14) {
    if (!(data[3].missing != -1) || data[3].qvalue < 182) {
      if (!(data[2].missing != -1) || data[2].qvalue < 6) {
        sum += 0.302881f;
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 8) {
          sum += -0.140651f;
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 26) {
            sum += 0.284886f;
          } else {
            sum += -0.00187213f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 196) {
        sum += -0.394831f;
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 70) {
          if (!(data[2].missing != -1) || data[2].qvalue < 10) {
            sum += 0.282895f;
          } else {
            sum += 0.0713136f;
          }
        } else {
          sum += -0.271973f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || data[0].qvalue < 4) {
      if (!(data[1].missing != -1) || data[1].qvalue < 6) {
        if (!(data[3].missing != -1) || data[3].qvalue < 94) {
          if (!(data[3].missing != -1) || data[3].qvalue < 52) {
            sum += 0.0362743f;
          } else {
            sum += 0.793368f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 36) {
            sum += 0.286949f;
          } else {
            sum += -0.147489f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 24) {
          sum += 0.13452f;
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 14) {
            sum += -0.0154347f;
          } else {
            sum += -0.281817f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[0].missing != -1) || data[0].qvalue < 6) {
          if (!(data[7].missing != -1) || data[7].qvalue < 34) {
            sum += 0.0583266f;
          } else {
            sum += -0.164409f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 66) {
            sum += 0.50049f;
          } else {
            sum += 0.117328f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 20) {
          sum += 0.297538f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 54) {
            sum += -0.272663f;
          } else {
            sum += -0.0146311f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 4) {
    if (!(data[4].missing != -1) || data[4].qvalue < 0) {
      if (!(data[0].missing != -1) || data[0].qvalue < 8) {
        sum += 0.0989734f;
      } else {
        sum += 0.296803f;
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 58) {
        sum += -0.0593619f;
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 4) {
          sum += 0.00440019f;
        } else {
          sum += 0.254135f;
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 28) {
      if (!(data[3].missing != -1) || data[3].qvalue < 136) {
        if (!(data[7].missing != -1) || data[7].qvalue < 62) {
          if (!(data[1].missing != -1) || data[1].qvalue < 6) {
            sum += 0.400709f;
          } else {
            sum += 0.140242f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 106) {
            sum += 0.225486f;
          } else {
            sum += -0.201501f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 34) {
          if (!(data[3].missing != -1) || data[3].qvalue < 204) {
            sum += -0.0863601f;
          } else {
            sum += 0.335332f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 164) {
            sum += 0.213768f;
          } else {
            sum += -0.279608f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 18) {
        sum += 0.288426f;
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 56) {
          if (!(data[3].missing != -1) || data[3].qvalue < 84) {
            sum += -0.294495f;
          } else {
            sum += 0.023795f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 32) {
            sum += -0.305185f;
          } else {
            sum += -0.153809f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 18) {
    if (!(data[4].missing != -1) || data[4].qvalue < 2) {
      if (!(data[0].missing != -1) || data[0].qvalue < 8) {
        sum += 0.0819539f;
      } else {
        sum += 0.29221f;
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 70) {
        if (!(data[0].missing != -1) || data[0].qvalue < 18) {
          if (!(data[3].missing != -1) || data[3].qvalue < 14) {
            sum += 0.156213f;
          } else {
            sum += -0.248003f;
          }
        } else {
          sum += 0.21941f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 18) {
          if (!(data[5].missing != -1) || data[5].qvalue < 14) {
            sum += 0.200181f;
          } else {
            sum += -0.0873394f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 38) {
            sum += 0.446978f;
          } else {
            sum += 0.212f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 64) {
      if (!(data[3].missing != -1) || data[3].qvalue < 144) {
        if (!(data[3].missing != -1) || data[3].qvalue < 112) {
          if (!(data[8].missing != -1) || data[8].qvalue < 16) {
            sum += -0.0824989f;
          } else {
            sum += 0.270862f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 54) {
            sum += 0.495648f;
          } else {
            sum += -0.00102907f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 32) {
          if (!(data[3].missing != -1) || data[3].qvalue < 202) {
            sum += -0.144027f;
          } else {
            sum += 0.193823f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 156) {
            sum += 0.19013f;
          } else {
            sum += -0.283555f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 6) {
        if (!(data[4].missing != -1) || data[4].qvalue < 52) {
          if (!(data[7].missing != -1) || data[7].qvalue < 50) {
            sum += -0.0566707f;
          } else {
            sum += 0.805565f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 0) {
            sum += 0.0203869f;
          } else {
            sum += -0.229499f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 16) {
          sum += 0.166248f;
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 20) {
            sum += -0.268216f;
          } else {
            sum += 0.116102f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 24) {
    if (!(data[4].missing != -1) || data[4].qvalue < 0) {
      if (!(data[0].missing != -1) || data[0].qvalue < 10) {
        if (!(data[5].missing != -1) || data[5].qvalue < 0) {
          sum += 0.168295f;
        } else {
          sum += -0.0133423f;
        }
      } else {
        sum += 0.291889f;
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 62) {
        if (!(data[3].missing != -1) || data[3].qvalue < 18) {
          sum += 0.231211f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 46) {
            sum += -0.331603f;
          } else {
            sum += -0.0701184f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 174) {
          if (!(data[6].missing != -1) || data[6].qvalue < 68) {
            sum += 0.309069f;
          } else {
            sum += -0.068511f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 198) {
            sum += -0.329565f;
          } else {
            sum += 0.319907f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 18) {
      if (!(data[2].missing != -1) || data[2].qvalue < 38) {
        if (!(data[4].missing != -1) || data[4].qvalue < 74) {
          if (!(data[0].missing != -1) || data[0].qvalue < 8) {
            sum += -0.0597696f;
          } else {
            sum += 0.208345f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 0) {
            sum += 0.0933482f;
          } else {
            sum += -0.354314f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 84) {
          if (!(data[1].missing != -1) || data[1].qvalue < 6) {
            sum += 0.411926f;
          } else {
            sum += 0.102206f;
          }
        } else {
          sum += -0.110079f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 4) {
        sum += 0.276485f;
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 8) {
          if (!(data[4].missing != -1) || data[4].qvalue < 60) {
            sum += 0.0400186f;
          } else {
            sum += -0.13987f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 12) {
            sum += 0.176489f;
          } else {
            sum += -0.235296f;
          }
        }
      }
    }
  }
  if (!(data[3].missing != -1) || data[3].qvalue < 6) {
    sum += 0.290905f;
  } else {
    if (!(data[0].missing != -1) || data[0].qvalue < 4) {
      if (!(data[1].missing != -1) || data[1].qvalue < 6) {
        if (!(data[3].missing != -1) || data[3].qvalue < 94) {
          if (!(data[3].missing != -1) || data[3].qvalue < 38) {
            sum += -0.233554f;
          } else {
            sum += 0.420094f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 0) {
            sum += 0.182933f;
          } else {
            sum += -0.0979355f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 14) {
          if (!(data[3].missing != -1) || data[3].qvalue < 104) {
            sum += -0.0766892f;
          } else {
            sum += 0.115395f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 8) {
            sum += -0.156183f;
          } else {
            sum += -0.296747f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[0].missing != -1) || data[0].qvalue < 6) {
          sum += -0.103038f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 212) {
            sum += 0.426742f;
          } else {
            sum += 0.0071082f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 20) {
          if (!(data[7].missing != -1) || data[7].qvalue < 16) {
            sum += 0.239647f;
          } else {
            sum += -0.035018f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 48) {
            sum += 0.278896f;
          } else {
            sum += 0.0848814f;
          }
        }
      }
    }
  }
  if (!(data[3].missing != -1) || data[3].qvalue < 6) {
    sum += 0.285723f;
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 60) {
      if (!(data[7].missing != -1) || data[7].qvalue < 24) {
        if (!(data[3].missing != -1) || data[3].qvalue < 42) {
          if (!(data[2].missing != -1) || data[2].qvalue < 18) {
            sum += 0.171572f;
          } else {
            sum += -0.16943f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 0) {
            sum += -0.0230031f;
          } else {
            sum += 0.280816f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 48) {
          if (!(data[3].missing != -1) || data[3].qvalue < 32) {
            sum += -0.133549f;
          } else {
            sum += -0.460784f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 166) {
            sum += 0.0815001f;
          } else {
            sum += -0.0660664f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 6) {
        if (!(data[3].missing != -1) || data[3].qvalue < 128) {
          if (!(data[3].missing != -1) || data[3].qvalue < 108) {
            sum += -0.0340158f;
          } else {
            sum += 0.496533f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 34) {
            sum += 0.14171f;
          } else {
            sum += -0.186719f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 16) {
          if (!(data[5].missing != -1) || data[5].qvalue < 2) {
            sum += 0.103105f;
          } else {
            sum += -0.227306f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 28) {
            sum += 0.192582f;
          } else {
            sum += -0.127821f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || data[0].qvalue < 18) {
    if (!(data[1].missing != -1) || data[1].qvalue < 4) {
      if (!(data[4].missing != -1) || data[4].qvalue < 50) {
        if (!(data[8].missing != -1) || data[8].qvalue < 10) {
          if (!(data[6].missing != -1) || data[6].qvalue < 58) {
            sum += 0.356487f;
          } else {
            sum += 0.0349002f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 162) {
            sum += 0.682899f;
          } else {
            sum += 0.206172f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 96) {
          if (!(data[3].missing != -1) || data[3].qvalue < 40) {
            sum += -0.0185905f;
          } else {
            sum += 0.450842f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 194) {
            sum += -0.167551f;
          } else {
            sum += 0.133059f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 130) {
        if (!(data[3].missing != -1) || data[3].qvalue < 122) {
          if (!(data[3].missing != -1) || data[3].qvalue < 114) {
            sum += -0.0930361f;
          } else {
            sum += 0.158059f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 52) {
            sum += 0.998846f;
          } else {
            sum += -0.212504f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 222) {
          if (!(data[6].missing != -1) || data[6].qvalue < 36) {
            sum += -0.0292885f;
          } else {
            sum += -0.223162f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 78) {
            sum += 0.291427f;
          } else {
            sum += -0.280193f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || data[3].qvalue < 178) {
      if (!(data[2].missing != -1) || data[2].qvalue < 36) {
        sum += 0.294419f;
      } else {
        sum += 0.00335805f;
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 200) {
        if (!(data[7].missing != -1) || data[7].qvalue < 46) {
          if (!(data[3].missing != -1) || data[3].qvalue < 184) {
            sum += -0.173049f;
          } else {
            sum += 0.232764f;
          }
        } else {
          sum += -0.335128f;
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 6) {
          sum += -0.102821f;
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 56) {
            sum += 0.262625f;
          } else {
            sum += 0.0211894f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || data[5].qvalue < 4) {
    if (!(data[0].missing != -1) || data[0].qvalue < 10) {
      if (!(data[3].missing != -1) || data[3].qvalue < 64) {
        sum += -0.0369607f;
      } else {
        sum += 0.201194f;
      }
    } else {
      sum += 0.277083f;
    }
  } else {
    if (!(data[6].missing != -1) || data[6].qvalue < 6) {
      if (!(data[5].missing != -1) || data[5].qvalue < 38) {
        if (!(data[6].missing != -1) || data[6].qvalue < 4) {
          if (!(data[6].missing != -1) || data[6].qvalue < 2) {
            sum += 0.234772f;
          } else {
            sum += -0.0277179f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 28) {
            sum += 0.145408f;
          } else {
            sum += 0.609293f;
          }
        }
      } else {
        sum += -0.10157f;
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 72) {
        if (!(data[8].missing != -1) || data[8].qvalue < 12) {
          if (!(data[3].missing != -1) || data[3].qvalue < 110) {
            sum += -0.120432f;
          } else {
            sum += 0.0281518f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 40) {
            sum += 0.0763232f;
          } else {
            sum += 0.563695f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 88) {
          if (!(data[3].missing != -1) || data[3].qvalue < 50) {
            sum += -0.0440853f;
          } else {
            sum += 0.478224f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 32) {
            sum += -0.335811f;
          } else {
            sum += -0.103084f;
          }
        }
      }
    }
  }
  if (!(data[3].missing != -1) || data[3].qvalue < 6) {
    sum += 0.27696f;
  } else {
    if (!(data[3].missing != -1) || data[3].qvalue < 44) {
      if (!(data[4].missing != -1) || data[4].qvalue < 6) {
        sum += 0.0606055f;
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 26) {
          sum += -0.110885f;
        } else {
          sum += -0.358602f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 26) {
        if (!(data[6].missing != -1) || data[6].qvalue < 62) {
          if (!(data[3].missing != -1) || data[3].qvalue < 180) {
            sum += 0.271339f;
          } else {
            sum += -0.0115159f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 186) {
            sum += -0.0136948f;
          } else {
            sum += 0.246279f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 42) {
          if (!(data[3].missing != -1) || data[3].qvalue < 226) {
            sum += -0.0807776f;
          } else {
            sum += 0.264488f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 56) {
            sum += 0.133495f;
          } else {
            sum += -0.035357f;
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
  // return sum;
}
