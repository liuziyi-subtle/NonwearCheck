#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static const float threshold[] = {
    -0.260863f, -0.0906853f, -0.046913f,  0.0449589f,  0.0921735f, 0.100063f,
    0.108727f,  0.115558f,   0.121061f,   0.168141f,   0.171947f,  0.189199f,
    0.207183f,  0.208591f,   0.212549f,   0.221566f,   0.225169f,  0.227951f,
    0.254039f,  0.282092f,   0.420872f,   0.459644f,   0.465754f,  0.492255f,
    0.495816f,  0.501387f,   0.501913f,   0.503622f,   0.544697f,  0.544762f,
    0.545554f,  0.555523f,   0.561851f,   0.584886f,   0.591832f,  0.594405f,
    0.601124f,  0.632633f,   0.768524f,   0.810994f,   1.5f,       3.5f,
    4.5f,       6.5f,        7.5f,        8.5f,        9.5f,       10.5f,
    11.5f,      12.5f,       13.5f,       14.5f,       15.5f,      16.5f,
    17.5f,      18.5f,       20.5f,       0.0301194f,  0.060465f,  0.164036f,
    0.200005f,  0.217408f,   0.221462f,   0.33869f,    0.343207f,  0.369571f,
    0.381268f,  0.389214f,   0.404431f,   0.415321f,   0.429718f,  0.462149f,
    0.4826f,    0.526686f,   0.544269f,   0.578127f,   0.592217f,  0.634102f,
    0.656463f,  0.660907f,   0.669543f,   0.691857f,   0.70075f,   0.720428f,
    0.730374f,  0.763967f,   0.77847f,    0.81914f,    0.830728f,  0.838835f,
    0.877566f,  0.910316f,   0.911681f,   0.921765f,   0.935584f,  0.93862f,
    0.938635f,  0.946136f,   0.00120898f, 0.00705184f, 0.0160974f, 0.0172148f,
    0.0174532f, 0.023059f,   0.0423916f,  0.0508506f,  0.0509515f, 0.0706129f,
    0.124465f,  0.32577f,    0.359845f,   0.526694f,   0.530052f,  1.11577f,
    1.31987f,   1.32497f,    1.75563f,    2.70593f,    3.19564f,   3.23588f,
    4.44967f,   4.82014f,    8.08926f,    15.217f,     15.2691f,   663.847f,
    0.0114815f, 0.0114826f,  0.01149f,    0.0127427f,  0.0198855f, 0.0251971f,
    0.0284444f, 0.0286558f,  0.0328522f,  0.033765f,   0.0353877f, 0.0445785f,
    0.0845835f, 0.105995f,   0.115584f,   0.124706f,   0.145945f,  0.15429f,
    0.161039f,  0.16324f,    0.166801f,   0.178888f,   0.188908f,  0.201082f,
    0.209349f,  0.217887f,   0.219732f,   0.237801f,   0.288087f,  0.290278f,
    0.305099f,  0.359306f,   0.370058f,   0.39492f,    0.428381f,  0.433243f,
    0.440691f,  0.496645f,   0.505708f,   0.518932f,   0.561906f,  0.613604f,
    0.651527f,  0.651584f,   0.7691f,     0.787978f,   0.846011f,  1.04016f,
    1.08249f,   1.11814f,    1.17666f,    1.82458f,    2.59889f,   2.72758f,
    0.507709f,  1.29294f,    1.3126f,     1.33795f,    1.35934f,   1.3766f,
    1.45715f,   1.46437f,    1.58504f,    1.61498f,    1.65164f,   1.66957f,
    1.67952f,   1.6913f,     1.71832f,    1.74408f,    1.74718f,   1.74795f,
    1.75791f,   1.77469f,    1.78666f,    1.78884f,    1.7951f,    1.79803f,
    1.80463f,   1.81282f,    1.8291f,     1.84811f,    1.85585f,   1.87745f,
    1.88514f,   1.92749f,    1.93085f,    1.9406f,     1.94168f,   1.96361f,
    1.97807f,   1.98047f,    1.98048f,    1.98067f,    1.98318f,   1.98401f,
    1.98619f,   2.0154f,     2.02137f,    2.04234f,    2.04262f,   2.04721f,
    2.05278f,   2.06175f,    2.06213f,    2.06578f,    2.06618f,   2.0672f,
    2.06852f,   2.07356f,    2.07736f,    2.0818f,     2.09327f,   2.09664f,
    2.09976f,   2.10469f,    2.11117f,    2.1589f,     2.17843f,   2.17891f,
    2.20299f,   2.26156f,    2.2765f,     2.27666f,    2.27927f,   0.223935f,
    0.229887f,  0.273193f,   0.277962f,   0.302384f,   0.306746f,  0.306829f,
    0.318519f,  0.319575f,   0.335831f,   0.348443f,   0.61982f,   0.619974f,
    0.714945f,  0.785708f,   0.93606f,    1.04426f,    1.04602f,   1.31057f,
    1.33602f,   1.57677f,    1.73295f,    2.01312f,    2.17599f,   2.56774f,
    3.16577f,   3.39333f,    3.89384f,    4.10447f,    4.2152f,    5.23289f,
    5.49366f,   5.58572f,    5.9216f,     7.14935f,    7.27677f,   7.34205f,
    7.72643f,   8.73925f,    9.79071f,    10.7337f,    12.1498f,   13.4875f,
    18.0363f,   0.151719f,   0.166946f,   0.228178f,   0.233354f,  0.274142f,
    0.333758f,  0.386367f,   0.508097f,   0.51285f,    0.54399f,   0.598212f,
    0.617037f,  0.637024f,   0.643054f,   0.673582f,   0.685787f,  0.686278f,
    0.702235f,  0.702924f,   0.731716f,   0.836018f,   0.854462f,  1.00873f,
    1.01247f,   1.10832f,    1.10842f,    1.11769f,    1.35821f,   1.38158f,
    1.72854f,   2.10503f,    2.11124f,    2.11466f,    2.19712f,   2.33438f,
    2.79055f,   2.80618f,    2.83932f,    3.08447f,    3.16125f,   3.6737f,
    4.37488f,   4.94842f,    14.059f,     15.0219f,    15.9144f,   16.6665f,
    0.0424413f, 0.188084f,   0.207456f,   0.39402f,    0.442025f,  0.453198f,
    1.16303f,   1.22268f,    1.36738f,    1.44988f,    1.4538f,    1.45522f,
    1.71349f,   1.77857f,    2.40456f,    2.84667f,    2.91346f,   2.93269f,
    2.93821f,   3.14522f,    3.18378f,    4.62819f,    5.01432f,   6.1063f,
    7.66785f,   9.40404f,    11.1145f,    11.8571f,    12.9218f,   30.9229f,
    32.3361f,   63.6867f,    87.5805f,    89.245f,     101.016f,   112.045f,
    125.733f,   171.37f,     719.442f,    0.0664062f,  0.0742188f, 0.0820312f,
    0.0898438f, 0.105469f,   0.160156f,   0.175781f,
};

static const int th_begin[] = {
    0, 40, 57, 98, 126, 180, 251, 295, 342, 381,
};

static const int th_len[] = {
    40, 17, 41, 28, 54, 71, 44, 47, 39, 7,
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

float PredictGreen(union NonwearEntry* data) {
  float sum = 0.0f;
  for (int i = 0; i < 10; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 50) {
    if (!(data[1].missing != -1) || data[1].qvalue < 14) {
      if (!(data[7].missing != -1) || data[7].qvalue < 26) {
        if (!(data[2].missing != -1) || data[2].qvalue < 80) {
          sum += 0.568831f;
        } else {
          sum += 0.15f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 138) {
          if (!(data[3].missing != -1) || data[3].qvalue < 6) {
            sum += -.0f;
          } else {
            sum += -0.565714f;
          }
        } else {
          sum += 0.12f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 38) {
        if (!(data[2].missing != -1) || data[2].qvalue < 42) {
          sum += 0.596333f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 34) {
            sum += 0.542424f;
          } else {
            sum += 0.284211f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 20) {
          if (!(data[5].missing != -1) || data[5].qvalue < 80) {
            sum += 0.458824f;
          } else {
            sum += -0.138462f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 64) {
            sum += 0.5328f;
          } else {
            sum += 0.0352941f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 22) {
      if (!(data[7].missing != -1) || data[7].qvalue < 16) {
        sum += 0.572308f;
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 20) {
          if (!(data[1].missing != -1) || data[1].qvalue < 16) {
            sum += -0.311111f;
          } else {
            sum += 0.34382f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 16) {
            sum += -0.574185f;
          } else {
            sum += -0.404717f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 68) {
        if (!(data[5].missing != -1) || data[5].qvalue < 18) {
          sum += 0.587755f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 96) {
            sum += 0.459854f;
          } else {
            sum += -.0f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 32) {
          if (!(data[4].missing != -1) || data[4].qvalue < 82) {
            sum += 0.472727f;
          } else {
            sum += -0.00952381f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 72) {
            sum += 0.12f;
          } else {
            sum += -0.497436f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 54) {
    if (!(data[1].missing != -1) || data[1].qvalue < 14) {
      if (!(data[7].missing != -1) || data[7].qvalue < 36) {
        if (!(data[0].missing != -1) || data[0].qvalue < 0) {
          sum += 0.0909261f;
        } else {
          if (!(data[9].missing != -1) || data[9].qvalue < 0) {
            sum += 0.125504f;
          } else {
            sum += 0.446919f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 138) {
          sum += -0.441789f;
        } else {
          sum += 0.0986384f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 34) {
        if (!(data[2].missing != -1) || data[2].qvalue < 42) {
          sum += 0.461519f;
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 12) {
            sum += 0.358579f;
          } else {
            sum += 0.443857f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 22) {
          if (!(data[5].missing != -1) || data[5].qvalue < 72) {
            sum += 0.411903f;
          } else {
            sum += -0.0979416f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 16) {
            sum += 0.181747f;
          } else {
            sum += 0.451068f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 20) {
      if (!(data[7].missing != -1) || data[7].qvalue < 28) {
        if (!(data[8].missing != -1) || data[8].qvalue < 12) {
          if (!(data[5].missing != -1) || data[5].qvalue < 78) {
            sum += 0.281919f;
          } else {
            sum += -0.343273f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 24) {
            sum += 0.194698f;
          } else {
            sum += 0.478544f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 32) {
          if (!(data[6].missing != -1) || data[6].qvalue < 36) {
            sum += 0.382967f;
          } else {
            sum += -0.256819f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 14) {
            sum += -0.450279f;
          } else {
            sum += -0.358458f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 66) {
        if (!(data[5].missing != -1) || data[5].qvalue < 38) {
          if (!(data[0].missing != -1) || data[0].qvalue < 48) {
            sum += 0.43699f;
          } else {
            sum += 0.195366f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 74) {
            sum += 0.298858f;
          } else {
            sum += -0.126551f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 18) {
          if (!(data[1].missing != -1) || data[1].qvalue < 26) {
            sum += -0.106349f;
          } else {
            sum += 0.445976f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 28) {
            sum += -0.05369f;
          } else {
            sum += -0.429074f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 54) {
    if (!(data[1].missing != -1) || data[1].qvalue < 16) {
      if (!(data[7].missing != -1) || data[7].qvalue < 32) {
        if (!(data[9].missing != -1) || data[9].qvalue < 6) {
          if (!(data[4].missing != -1) || data[4].qvalue < 42) {
            sum += 0.264838f;
          } else {
            sum += -0.0674863f;
          }
        } else {
          sum += 0.395952f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 84) {
          sum += 0.293597f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 4) {
            sum += 0.219339f;
          } else {
            sum += -0.387102f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 56) {
        if (!(data[2].missing != -1) || data[2].qvalue < 50) {
          sum += 0.399787f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 34) {
            sum += 0.348074f;
          } else {
            sum += 0.150674f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 58) {
          sum += 0.377034f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 26) {
            sum += -0.512963f;
          } else {
            sum += 0.281154f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 18) {
      if (!(data[7].missing != -1) || data[7].qvalue < 16) {
        if (!(data[3].missing != -1) || data[3].qvalue < 12) {
          sum += 0.112763f;
        } else {
          sum += 0.389509f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 14) {
          if (!(data[6].missing != -1) || data[6].qvalue < 52) {
            sum += 0.277093f;
          } else {
            sum += -0.227111f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 50) {
            sum += -0.208094f;
          } else {
            sum += -0.379723f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 86) {
        if (!(data[0].missing != -1) || data[0].qvalue < 50) {
          if (!(data[2].missing != -1) || data[2].qvalue < 38) {
            sum += 0.376578f;
          } else {
            sum += 0.158385f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 16) {
            sum += 0.365003f;
          } else {
            sum += -0.312397f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 28) {
          if (!(data[8].missing != -1) || data[8].qvalue < 74) {
            sum += -0.302434f;
          } else {
            sum += 0.102791f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 40) {
            sum += 0.423254f;
          } else {
            sum += -0.159517f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 46) {
    if (!(data[4].missing != -1) || data[4].qvalue < 36) {
      if (!(data[2].missing != -1) || data[2].qvalue < 42) {
        if (!(data[0].missing != -1) || data[0].qvalue < 76) {
          sum += 0.364099f;
        } else {
          sum += 0.113001f;
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 34) {
          if (!(data[6].missing != -1) || data[6].qvalue < 12) {
            sum += 0.236875f;
          } else {
            sum += 0.339319f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 20) {
            sum += -0.448036f;
          } else {
            sum += 0.336632f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 120) {
        if (!(data[3].missing != -1) || data[3].qvalue < 14) {
          if (!(data[5].missing != -1) || data[5].qvalue < 82) {
            sum += 0.283859f;
          } else {
            sum += -0.096317f;
          }
        } else {
          sum += 0.352649f;
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 24) {
          sum += 0.29463f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 24) {
            sum += -0.303247f;
          } else {
            sum += 0.210487f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 18) {
      if (!(data[7].missing != -1) || data[7].qvalue < 28) {
        if (!(data[8].missing != -1) || data[8].qvalue < 26) {
          if (!(data[7].missing != -1) || data[7].qvalue < 16) {
            sum += 0.301118f;
          } else {
            sum += -0.206381f;
          }
        } else {
          sum += 0.388932f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 76) {
          if (!(data[4].missing != -1) || data[4].qvalue < 60) {
            sum += 0.560724f;
          } else {
            sum += -0.236654f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 104) {
            sum += -0.296659f;
          } else {
            sum += -0.358497f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 56) {
        if (!(data[6].missing != -1) || data[6].qvalue < 64) {
          if (!(data[0].missing != -1) || data[0].qvalue < 74) {
            sum += 0.358443f;
          } else {
            sum += 0.128265f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 24) {
            sum += -0.227956f;
          } else {
            sum += 0.288599f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 42) {
          if (!(data[2].missing != -1) || data[2].qvalue < 32) {
            sum += 0.277845f;
          } else {
            sum += -0.117037f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 48) {
            sum += -0.0435422f;
          } else {
            sum += -0.378352f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 58) {
    if (!(data[1].missing != -1) || data[1].qvalue < 16) {
      if (!(data[7].missing != -1) || data[7].qvalue < 34) {
        if (!(data[9].missing != -1) || data[9].qvalue < 0) {
          sum += 0.0658151f;
        } else {
          sum += 0.324712f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 64) {
          sum += 0.361074f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 24) {
            sum += 0.216721f;
          } else {
            sum += -0.278103f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 60) {
        if (!(data[2].missing != -1) || data[2].qvalue < 52) {
          if (!(data[2].missing != -1) || data[2].qvalue < 22) {
            sum += 0.346031f;
          } else {
            sum += 0.309408f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 132) {
            sum += 0.19999f;
          } else {
            sum += 0.334461f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 60) {
          if (!(data[5].missing != -1) || data[5].qvalue < 102) {
            sum += 0.347635f;
          } else {
            sum += -0.0418547f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 26) {
            sum += -0.395513f;
          } else {
            sum += 0.212774f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 14) {
      if (!(data[7].missing != -1) || data[7].qvalue < 28) {
        if (!(data[8].missing != -1) || data[8].qvalue < 14) {
          if (!(data[4].missing != -1) || data[4].qvalue < 72) {
            sum += -0.000298605f;
          } else {
            sum += -0.268011f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 60) {
            sum += 0.355978f;
          } else {
            sum += 0.0966093f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 0) {
          sum += 0.322629f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 0) {
            sum += 0.1066f;
          } else {
            sum += -0.320349f;
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || data[9].qvalue < 4) {
        if (!(data[2].missing != -1) || data[2].qvalue < 44) {
          if (!(data[3].missing != -1) || data[3].qvalue < 42) {
            sum += -0.0368391f;
          } else {
            sum += 0.51151f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 30) {
            sum += 0.383698f;
          } else {
            sum += -0.117791f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 24) {
          if (!(data[7].missing != -1) || data[7].qvalue < 60) {
            sum += 0.050739f;
          } else {
            sum += -0.268623f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 20) {
            sum += 0.278691f;
          } else {
            sum += -0.062046f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 46) {
    if (!(data[2].missing != -1) || data[2].qvalue < 42) {
      if (!(data[0].missing != -1) || data[0].qvalue < 56) {
        if (!(data[1].missing != -1) || data[1].qvalue < 14) {
          if (!(data[7].missing != -1) || data[7].qvalue < 38) {
            sum += 0.255974f;
          } else {
            sum += -0.192982f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 14) {
            sum += 0.331538f;
          } else {
            sum += 0.287039f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 58) {
          sum += 0.240629f;
        } else {
          sum += -0.160015f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 8) {
        if (!(data[6].missing != -1) || data[6].qvalue < 6) {
          if (!(data[6].missing != -1) || data[6].qvalue < 4) {
            sum += 0.175604f;
          } else {
            sum += -0.374008f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 0) {
            sum += 0.0272953f;
          } else {
            sum += 0.307884f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 18) {
          if (!(data[5].missing != -1) || data[5].qvalue < 100) {
            sum += 0.248677f;
          } else {
            sum += -0.246168f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 18) {
            sum += -0.194694f;
          } else {
            sum += 0.244202f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 16) {
      if (!(data[7].missing != -1) || data[7].qvalue < 46) {
        if (!(data[8].missing != -1) || data[8].qvalue < 18) {
          if (!(data[8].missing != -1) || data[8].qvalue < 6) {
            sum += 0.181882f;
          } else {
            sum += -0.21111f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 130) {
            sum += 0.364205f;
          } else {
            sum += -0.0847749f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 96) {
          if (!(data[4].missing != -1) || data[4].qvalue < 90) {
            sum += -0.0694147f;
          } else {
            sum += -0.242827f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 140) {
            sum += -0.31963f;
          } else {
            sum += -0.028145f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 92) {
        if (!(data[6].missing != -1) || data[6].qvalue < 56) {
          if (!(data[3].missing != -1) || data[3].qvalue < 48) {
            sum += 0.168016f;
          } else {
            sum += 0.415496f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 26) {
            sum += -0.149815f;
          } else {
            sum += 0.224791f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 70) {
          if (!(data[7].missing != -1) || data[7].qvalue < 74) {
            sum += 0.130118f;
          } else {
            sum += -0.182933f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 122) {
            sum += -0.109318f;
          } else {
            sum += -0.310647f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 56) {
    if (!(data[4].missing != -1) || data[4].qvalue < 34) {
      if (!(data[2].missing != -1) || data[2].qvalue < 42) {
        if (!(data[2].missing != -1) || data[2].qvalue < 14) {
          sum += 0.320377f;
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 6) {
            sum += -0.262675f;
          } else {
            sum += 0.289637f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 10) {
          if (!(data[5].missing != -1) || data[5].qvalue < 70) {
            sum += -0.697173f;
          } else {
            sum += 0.184498f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 16) {
            sum += 0.0262303f;
          } else {
            sum += 0.277906f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 112) {
        if (!(data[0].missing != -1) || data[0].qvalue < 60) {
          if (!(data[8].missing != -1) || data[8].qvalue < 16) {
            sum += 0.127908f;
          } else {
            sum += 0.359377f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 60) {
            sum += 0.224516f;
          } else {
            sum += -0.276246f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 40) {
          if (!(data[7].missing != -1) || data[7].qvalue < 30) {
            sum += 0.152238f;
          } else {
            sum += -0.29143f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 30) {
            sum += 0.351373f;
          } else {
            sum += -0.140709f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 14) {
      if (!(data[7].missing != -1) || data[7].qvalue < 44) {
        if (!(data[8].missing != -1) || data[8].qvalue < 22) {
          if (!(data[4].missing != -1) || data[4].qvalue < 66) {
            sum += 0.0149449f;
          } else {
            sum += -0.292638f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 66) {
            sum += 0.362292f;
          } else {
            sum += -0.0196891f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 26) {
          if (!(data[1].missing != -1) || data[1].qvalue < 4) {
            sum += 0.437958f;
          } else {
            sum += -0.137069f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 0) {
            sum += 0.0835558f;
          } else {
            sum += -0.290479f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 46) {
        if (!(data[6].missing != -1) || data[6].qvalue < 76) {
          if (!(data[8].missing != -1) || data[8].qvalue < 66) {
            sum += 0.160309f;
          } else {
            sum += 0.385268f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 6) {
            sum += 0.312643f;
          } else {
            sum += -0.235059f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || data[9].qvalue < 4) {
          if (!(data[2].missing != -1) || data[2].qvalue < 36) {
            sum += 0.5228f;
          } else {
            sum += -0.0849512f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 28) {
            sum += -0.175856f;
          } else {
            sum += 0.234299f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 44) {
    if (!(data[2].missing != -1) || data[2].qvalue < 22) {
      if (!(data[4].missing != -1) || data[4].qvalue < 40) {
        if (!(data[1].missing != -1) || data[1].qvalue < 14) {
          sum += 0.10478f;
        } else {
          sum += 0.311293f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 108) {
          sum += 0.180425f;
        } else {
          sum += -0.0352036f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 26) {
        if (!(data[3].missing != -1) || data[3].qvalue < 10) {
          if (!(data[6].missing != -1) || data[6].qvalue < 2) {
            sum += 0.0272577f;
          } else {
            sum += 0.231006f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 20) {
            sum += -0.528547f;
          } else {
            sum += 0.0264233f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || data[9].qvalue < 2) {
          if (!(data[4].missing != -1) || data[4].qvalue < 22) {
            sum += -0.410158f;
          } else {
            sum += 0.210049f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 62) {
            sum += 0.177406f;
          } else {
            sum += 0.308512f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 14) {
      if (!(data[7].missing != -1) || data[7].qvalue < 56) {
        if (!(data[8].missing != -1) || data[8].qvalue < 20) {
          if (!(data[8].missing != -1) || data[8].qvalue < 10) {
            sum += 0.0940239f;
          } else {
            sum += -0.204828f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 80) {
            sum += 0.363559f;
          } else {
            sum += -0.0192749f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 22) {
          if (!(data[1].missing != -1) || data[1].qvalue < 4) {
            sum += 0.363213f;
          } else {
            sum += -0.0992795f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 94) {
            sum += -0.208348f;
          } else {
            sum += -0.298901f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 98) {
        if (!(data[6].missing != -1) || data[6].qvalue < 54) {
          if (!(data[8].missing != -1) || data[8].qvalue < 64) {
            sum += 0.113046f;
          } else {
            sum += 0.370829f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 22) {
            sum += 0.0877539f;
          } else {
            sum += -0.217326f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 86) {
          if (!(data[0].missing != -1) || data[0].qvalue < 44) {
            sum += 0.0386304f;
          } else {
            sum += -0.285619f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 72) {
            sum += -0.300392f;
          } else {
            sum += -0.0581774f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 36) {
    if (!(data[2].missing != -1) || data[2].qvalue < 22) {
      if (!(data[1].missing != -1) || data[1].qvalue < 14) {
        sum += 0.0887986f;
      } else {
        sum += 0.30427f;
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 14) {
        if (!(data[8].missing != -1) || data[8].qvalue < 2) {
          if (!(data[4].missing != -1) || data[4].qvalue < 4) {
            sum += 0.274894f;
          } else {
            sum += 0.0708143f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 16) {
            sum += -0.385409f;
          } else {
            sum += 0.176385f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 26) {
          if (!(data[5].missing != -1) || data[5].qvalue < 4) {
            sum += -0.12002f;
          } else {
            sum += 0.282664f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 22) {
            sum += -0.141043f;
          } else {
            sum += 0.275902f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 10) {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[7].missing != -1) || data[7].qvalue < 66) {
          if (!(data[2].missing != -1) || data[2].qvalue < 74) {
            sum += 0.648643f;
          } else {
            sum += -0.0420703f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 72) {
            sum += -0.230858f;
          } else {
            sum += 0.246387f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 22) {
          if (!(data[2].missing != -1) || data[2].qvalue < 62) {
            sum += 0.256994f;
          } else {
            sum += -0.0704145f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 52) {
            sum += -0.0826463f;
          } else {
            sum += -0.277081f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 74) {
        if (!(data[4].missing != -1) || data[4].qvalue < 92) {
          if (!(data[0].missing != -1) || data[0].qvalue < 74) {
            sum += 0.23549f;
          } else {
            sum += -0.141163f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 10) {
            sum += 0.193495f;
          } else {
            sum += -0.10922f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 22) {
          if (!(data[2].missing != -1) || data[2].qvalue < 30) {
            sum += 0.133941f;
          } else {
            sum += -0.192426f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 82) {
            sum += 0.211066f;
          } else {
            sum += -0.129501f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 62) {
    if (!(data[2].missing != -1) || data[2].qvalue < 14) {
      if (!(data[0].missing != -1) || data[0].qvalue < 70) {
        if (!(data[1].missing != -1) || data[1].qvalue < 14) {
          if (!(data[7].missing != -1) || data[7].qvalue < 20) {
            sum += 0.206586f;
          } else {
            sum += -0.162687f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 38) {
            sum += 0.303667f;
          } else {
            sum += 0.144294f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 50) {
          sum += 0.119944f;
        } else {
          sum += -0.252508f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 12) {
        if (!(data[2].missing != -1) || data[2].qvalue < 70) {
          if (!(data[6].missing != -1) || data[6].qvalue < 44) {
            sum += -0.264988f;
          } else {
            sum += 0.191527f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 2) {
            sum += -0.212669f;
          } else {
            sum += 0.365896f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 30) {
          if (!(data[7].missing != -1) || data[7].qvalue < 48) {
            sum += 0.130649f;
          } else {
            sum += -0.127866f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 46) {
            sum += 0.337988f;
          } else {
            sum += -0.0823308f;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || data[8].qvalue < 68) {
      if (!(data[7].missing != -1) || data[7].qvalue < 64) {
        if (!(data[8].missing != -1) || data[8].qvalue < 38) {
          if (!(data[1].missing != -1) || data[1].qvalue < 10) {
            sum += -0.221515f;
          } else {
            sum += -0.034042f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 58) {
            sum += 0.185783f;
          } else {
            sum += -0.206731f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 22) {
          if (!(data[6].missing != -1) || data[6].qvalue < 28) {
            sum += 0.311347f;
          } else {
            sum += -0.249352f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 46) {
            sum += -0.215093f;
          } else {
            sum += 0.0847873f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 68) {
        if (!(data[7].missing != -1) || data[7].qvalue < 90) {
          if (!(data[0].missing != -1) || data[0].qvalue < 26) {
            sum += 0.480524f;
          } else {
            sum += 0.195461f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 16) {
            sum += 0.27228f;
          } else {
            sum += -0.23068f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 98) {
          if (!(data[0].missing != -1) || data[0].qvalue < 34) {
            sum += 0.378202f;
          } else {
            sum += -0.0176492f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 28) {
            sum += -0.244882f;
          } else {
            sum += 0.230445f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 34) {
    if (!(data[2].missing != -1) || data[2].qvalue < 40) {
      if (!(data[2].missing != -1) || data[2].qvalue < 14) {
        if (!(data[1].missing != -1) || data[1].qvalue < 14) {
          sum += 0.0548631f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 30) {
            sum += 0.297623f;
          } else {
            sum += 0.107895f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || data[9].qvalue < 2) {
          if (!(data[4].missing != -1) || data[4].qvalue < 8) {
            sum += -0.578397f;
          } else {
            sum += 0.133654f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 32) {
            sum += 0.267437f;
          } else {
            sum += -0.0330077f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 18) {
        if (!(data[4].missing != -1) || data[4].qvalue < 2) {
          if (!(data[7].missing != -1) || data[7].qvalue < 10) {
            sum += 0.271769f;
          } else {
            sum += 0.0208754f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 12) {
            sum += -0.404323f;
          } else {
            sum += 0.145277f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 26) {
          if (!(data[7].missing != -1) || data[7].qvalue < 4) {
            sum += -0.0549609f;
          } else {
            sum += 0.266172f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 20) {
            sum += -0.125042f;
          } else {
            sum += 0.222873f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || data[5].qvalue < 106) {
      if (!(data[6].missing != -1) || data[6].qvalue < 22) {
        if (!(data[4].missing != -1) || data[4].qvalue < 48) {
          if (!(data[5].missing != -1) || data[5].qvalue < 54) {
            sum += 0.165861f;
          } else {
            sum += -0.0149116f;
          }
        } else {
          sum += 0.387624f;
        }
      } else {
        if (!(data[9].missing != -1) || data[9].qvalue < 2) {
          if (!(data[6].missing != -1) || data[6].qvalue < 62) {
            sum += 0.220267f;
          } else {
            sum += -0.0431745f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 94) {
            sum += 0.0285246f;
          } else {
            sum += -0.153568f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 84) {
        if (!(data[8].missing != -1) || data[8].qvalue < 44) {
          if (!(data[7].missing != -1) || data[7].qvalue < 42) {
            sum += 0.0490414f;
          } else {
            sum += -0.208076f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 58) {
            sum += -0.0920531f;
          } else {
            sum += 0.418615f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 72) {
          if (!(data[6].missing != -1) || data[6].qvalue < 30) {
            sum += -0.00795121f;
          } else {
            sum += -0.278903f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 78) {
            sum += 0.21796f;
          } else {
            sum += -0.253324f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 34) {
    if (!(data[2].missing != -1) || data[2].qvalue < 22) {
      if (!(data[1].missing != -1) || data[1].qvalue < 14) {
        sum += 0.0602319f;
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 12) {
          sum += 0.298019f;
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 8) {
            sum += -0.0192376f;
          } else {
            sum += 0.273107f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 10) {
        if (!(data[5].missing != -1) || data[5].qvalue < 62) {
          if (!(data[7].missing != -1) || data[7].qvalue < 14) {
            sum += -0.35937f;
          } else {
            sum += 0.194144f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 8) {
            sum += -0.0315449f;
          } else {
            sum += 0.244686f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || data[1].qvalue < 24) {
          if (!(data[6].missing != -1) || data[6].qvalue < 32) {
            sum += 0.140174f;
          } else {
            sum += -0.253458f;
          }
        } else {
          sum += 0.293589f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 8) {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[2].missing != -1) || data[2].qvalue < 76) {
          if (!(data[6].missing != -1) || data[6].qvalue < 70) {
            sum += 0.147199f;
          } else {
            sum += 0.538451f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 106) {
            sum += -0.0193456f;
          } else {
            sum += -0.175498f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 40) {
          if (!(data[4].missing != -1) || data[4].qvalue < 88) {
            sum += 0.218369f;
          } else {
            sum += -0.207672f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 50) {
            sum += -0.275367f;
          } else {
            sum += 0.00427446f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || data[5].qvalue < 40) {
        if (!(data[6].missing != -1) || data[6].qvalue < 38) {
          if (!(data[1].missing != -1) || data[1].qvalue < 18) {
            sum += 0.45138f;
          } else {
            sum += 0.237193f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 46) {
            sum += -0.235425f;
          } else {
            sum += 0.106125f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 62) {
          if (!(data[2].missing != -1) || data[2].qvalue < 48) {
            sum += 0.0772895f;
          } else {
            sum += -0.0748338f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 30) {
            sum += -0.259528f;
          } else {
            sum += 0.148091f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 76) {
    if (!(data[1].missing != -1) || data[1].qvalue < 22) {
      if (!(data[5].missing != -1) || data[5].qvalue < 58) {
        if (!(data[0].missing != -1) || data[0].qvalue < 72) {
          if (!(data[3].missing != -1) || data[3].qvalue < 20) {
            sum += 0.20139f;
          } else {
            sum += 0.370285f;
          }
        } else {
          sum += -0.0342566f;
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 18) {
          if (!(data[6].missing != -1) || data[6].qvalue < 10) {
            sum += 0.100929f;
          } else {
            sum += 0.282129f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 28) {
            sum += -0.154865f;
          } else {
            sum += 0.077474f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 8) {
        if (!(data[2].missing != -1) || data[2].qvalue < 54) {
          sum += 0.2855f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 14) {
            sum += -0.0748097f;
          } else {
            sum += 0.246274f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 16) {
          if (!(data[3].missing != -1) || data[3].qvalue < 2) {
            sum += 0.100901f;
          } else {
            sum += -0.239168f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 84) {
            sum += 0.228456f;
          } else {
            sum += -0.10358f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || data[5].qvalue < 118) {
      if (!(data[7].missing != -1) || data[7].qvalue < 62) {
        if (!(data[8].missing != -1) || data[8].qvalue < 36) {
          if (!(data[1].missing != -1) || data[1].qvalue < 14) {
            sum += -0.159496f;
          } else {
            sum += 0.164506f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 90) {
            sum += 0.135312f;
          } else {
            sum += 0.556762f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 56) {
          if (!(data[5].missing != -1) || data[5].qvalue < 42) {
            sum += -0.0189972f;
          } else {
            sum += -0.271903f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 66) {
            sum += 0.0878373f;
          } else {
            sum += -0.129289f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 24) {
        if (!(data[1].missing != -1) || data[1].qvalue < 24) {
          if (!(data[5].missing != -1) || data[5].qvalue < 134) {
            sum += -0.204738f;
          } else {
            sum += 0.115611f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 40) {
            sum += -0.0304839f;
          } else {
            sum += 0.259327f;
          }
        }
      } else {
        sum += -0.294964f;
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 28) {
    if (!(data[2].missing != -1) || data[2].qvalue < 14) {
      if (!(data[1].missing != -1) || data[1].qvalue < 16) {
        sum += 0.0636507f;
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 4) {
          sum += 0.296702f;
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 0) {
            sum += -0.258321f;
          } else {
            sum += 0.274936f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || data[6].qvalue < 20) {
        if (!(data[8].missing != -1) || data[8].qvalue < 0) {
          sum += 0.268169f;
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 6) {
            sum += 0.179186f;
          } else {
            sum += -0.126405f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 4) {
          sum += -0.0252256f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 16) {
            sum += 0.0293189f;
          } else {
            sum += 0.253823f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 8) {
      if (!(data[1].missing != -1) || data[1].qvalue < 4) {
        if (!(data[2].missing != -1) || data[2].qvalue < 78) {
          if (!(data[2].missing != -1) || data[2].qvalue < 72) {
            sum += 0.0225628f;
          } else {
            sum += 0.359317f;
          }
        } else {
          if (!(data[9].missing != -1) || data[9].qvalue < 6) {
            sum += 0.0776765f;
          } else {
            sum += -0.211374f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 64) {
          if (!(data[8].missing != -1) || data[8].qvalue < 34) {
            sum += -0.160954f;
          } else {
            sum += 0.112638f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 50) {
            sum += -0.293372f;
          } else {
            sum += -0.0125392f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 28) {
        if (!(data[6].missing != -1) || data[6].qvalue < 50) {
          if (!(data[8].missing != -1) || data[8].qvalue < 50) {
            sum += -0.0224369f;
          } else {
            sum += 0.18208f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 70) {
            sum += -0.15674f;
          } else {
            sum += 0.0331406f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || data[0].qvalue < 78) {
          if (!(data[9].missing != -1) || data[9].qvalue < 10) {
            sum += 0.274966f;
          } else {
            sum += 0.0827999f;
          }
        } else {
          sum += 0.0055764f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 74) {
    if (!(data[2].missing != -1) || data[2].qvalue < 8) {
      if (!(data[0].missing != -1) || data[0].qvalue < 38) {
        if (!(data[4].missing != -1) || data[4].qvalue < 64) {
          if (!(data[1].missing != -1) || data[1].qvalue < 14) {
            sum += 0.0938865f;
          } else {
            sum += 0.288267f;
          }
        } else {
          sum += 0.0409092f;
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 44) {
          sum += 0.193198f;
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 40) {
            sum += 0.0844783f;
          } else {
            sum += -0.306454f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || data[8].qvalue < 32) {
        if (!(data[7].missing != -1) || data[7].qvalue < 52) {
          if (!(data[3].missing != -1) || data[3].qvalue < 18) {
            sum += 0.021989f;
          } else {
            sum += 0.279873f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 60) {
            sum += 0.119943f;
          } else {
            sum += -0.169697f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 76) {
          if (!(data[2].missing != -1) || data[2].qvalue < 56) {
            sum += 0.163959f;
          } else {
            sum += 0.413036f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 54) {
            sum += 0.0934867f;
          } else {
            sum += -0.186069f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || data[5].qvalue < 118) {
      if (!(data[0].missing != -1) || data[0].qvalue < 16) {
        if (!(data[2].missing != -1) || data[2].qvalue < 28) {
          if (!(data[3].missing != -1) || data[3].qvalue < 34) {
            sum += -0.150642f;
          } else {
            sum += 0.345897f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 92) {
            sum += 0.0283583f;
          } else {
            sum += -0.24968f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 116) {
          if (!(data[5].missing != -1) || data[5].qvalue < 34) {
            sum += 0.0164375f;
          } else {
            sum += -0.144989f;
          }
        } else {
          sum += 0.488441f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || data[0].qvalue < 24) {
        if (!(data[3].missing != -1) || data[3].qvalue < 38) {
          if (!(data[7].missing != -1) || data[7].qvalue < 54) {
            sum += 0.0282514f;
          } else {
            sum += -0.212381f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 104) {
            sum += 0.244776f;
          } else {
            sum += -0.173003f;
          }
        }
      } else {
        sum += -0.283359f;
      }
    }
  }
  if (!(data[1].missing != -1) || data[1].qvalue < 24) {
    if (!(data[0].missing != -1) || data[0].qvalue < 68) {
      if (!(data[6].missing != -1) || data[6].qvalue < 84) {
        if (!(data[3].missing != -1) || data[3].qvalue < 52) {
          if (!(data[6].missing != -1) || data[6].qvalue < 24) {
            sum += 0.133022f;
          } else {
            sum += -0.0385521f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 36) {
            sum += 0.0706082f;
          } else {
            sum += 0.423369f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || data[4].qvalue < 102) {
          sum += 0.030789f;
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 6) {
            sum += -0.0535781f;
          } else {
            sum += -0.291785f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || data[8].qvalue < 76) {
        if (!(data[5].missing != -1) || data[5].qvalue < 12) {
          sum += -0.0188353f;
        } else {
          if (!(data[9].missing != -1) || data[9].qvalue < 12) {
            sum += -0.291229f;
          } else {
            sum += -0.0682718f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 86) {
          if (!(data[3].missing != -1) || data[3].qvalue < 54) {
            sum += 0.611519f;
          } else {
            sum += 0.0278141f;
          }
        } else {
          sum += -0.188007f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || data[0].qvalue < 10) {
      if (!(data[1].missing != -1) || data[1].qvalue < 26) {
        if (!(data[2].missing != -1) || data[2].qvalue < 24) {
          if (!(data[7].missing != -1) || data[7].qvalue < 58) {
            sum += 0.248814f;
          } else {
            sum += 0.0213674f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 12) {
            sum += -0.419435f;
          } else {
            sum += 0.108164f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 2) {
          if (!(data[5].missing != -1) || data[5].qvalue < 24) {
            sum += -0.137418f;
          } else {
            sum += 0.22827f;
          }
        } else {
          sum += 0.283045f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 10) {
        if (!(data[9].missing != -1) || data[9].qvalue < 8) {
          if (!(data[8].missing != -1) || data[8].qvalue < 8) {
            sum += -0.39634f;
          } else {
            sum += 0.0053278f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 6) {
            sum += -0.0406485f;
          } else {
            sum += 0.240479f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 78) {
          if (!(data[0].missing != -1) || data[0].qvalue < 14) {
            sum += 0.00596758f;
          } else {
            sum += 0.301647f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 46) {
            sum += -0.117439f;
          } else {
            sum += 0.231245f;
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || data[7].qvalue < 68) {
    if (!(data[2].missing != -1) || data[2].qvalue < 12) {
      if (!(data[0].missing != -1) || data[0].qvalue < 38) {
        if (!(data[2].missing != -1) || data[2].qvalue < 4) {
          if (!(data[5].missing != -1) || data[5].qvalue < 128) {
            sum += 0.288756f;
          } else {
            sum += 0.0806224f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 0) {
            sum += -0.21637f;
          } else {
            sum += 0.237574f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 42) {
          sum += 0.198143f;
        } else {
          sum += -0.224344f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || data[8].qvalue < 48) {
        if (!(data[2].missing != -1) || data[2].qvalue < 68) {
          if (!(data[2].missing != -1) || data[2].qvalue < 52) {
            sum += 0.0503899f;
          } else {
            sum += -0.0915364f;
          }
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 50) {
            sum += 0.198499f;
          } else {
            sum += -0.0406724f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 36) {
          if (!(data[1].missing != -1) || data[1].qvalue < 10) {
            sum += 0.810563f;
          } else {
            sum += 0.227937f;
          }
        } else {
          if (!(data[8].missing != -1) || data[8].qvalue < 62) {
            sum += -0.13955f;
          } else {
            sum += 0.236821f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || data[5].qvalue < 124) {
      if (!(data[4].missing != -1) || data[4].qvalue < 78) {
        if (!(data[6].missing != -1) || data[6].qvalue < 46) {
          if (!(data[8].missing != -1) || data[8].qvalue < 42) {
            sum += -0.0469188f;
          } else {
            sum += 0.397476f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 48) {
            sum += 0.234511f;
          } else {
            sum += -0.0692485f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || data[8].qvalue < 54) {
          if (!(data[1].missing != -1) || data[1].qvalue < 22) {
            sum += -0.245467f;
          } else {
            sum += 0.0652524f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 26) {
            sum += 0.618564f;
          } else {
            sum += -0.029119f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 22) {
        if (!(data[5].missing != -1) || data[5].qvalue < 140) {
          if (!(data[5].missing != -1) || data[5].qvalue < 126) {
            sum += -0.135945f;
          } else {
            sum += -0.270072f;
          }
        } else {
          sum += 0.102765f;
        }
      } else {
        if (!(data[6].missing != -1) || data[6].qvalue < 58) {
          if (!(data[2].missing != -1) || data[2].qvalue < 64) {
            sum += -0.258724f;
          } else {
            sum += 0.0567355f;
          }
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 100) {
            sum += 0.251154f;
          } else {
            sum += -0.126683f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || data[1].qvalue < 24) {
    if (!(data[0].missing != -1) || data[0].qvalue < 68) {
      if (!(data[6].missing != -1) || data[6].qvalue < 86) {
        if (!(data[5].missing != -1) || data[5].qvalue < 114) {
          if (!(data[6].missing != -1) || data[6].qvalue < 26) {
            sum += 0.187536f;
          } else {
            sum += 0.0230358f;
          }
        } else {
          if (!(data[5].missing != -1) || data[5].qvalue < 136) {
            sum += -0.0810992f;
          } else {
            sum += 0.251098f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 18) {
          sum += -0.0785744f;
        } else {
          sum += -0.285496f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || data[8].qvalue < 76) {
        if (!(data[5].missing != -1) || data[5].qvalue < 12) {
          sum += -0.0168528f;
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 22) {
            sum += -0.0599471f;
          } else {
            sum += -0.279708f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 86) {
          sum += 0.348976f;
        } else {
          sum += -0.169162f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || data[0].qvalue < 12) {
      if (!(data[1].missing != -1) || data[1].qvalue < 26) {
        if (!(data[2].missing != -1) || data[2].qvalue < 20) {
          if (!(data[5].missing != -1) || data[5].qvalue < 88) {
            sum += 0.223979f;
          } else {
            sum += 0.0200113f;
          }
        } else {
          if (!(data[2].missing != -1) || data[2].qvalue < 34) {
            sum += -0.369662f;
          } else {
            sum += 0.0516102f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 2) {
          if (!(data[5].missing != -1) || data[5].qvalue < 28) {
            sum += -0.136048f;
          } else {
            sum += 0.204371f;
          }
        } else {
          if (!(data[1].missing != -1) || data[1].qvalue < 32) {
            sum += 0.280941f;
          } else {
            sum += 0.0834819f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || data[4].qvalue < 10) {
        if (!(data[5].missing != -1) || data[5].qvalue < 110) {
          if (!(data[2].missing != -1) || data[2].qvalue < 10) {
            sum += 0.171668f;
          } else {
            sum += -0.328718f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 8) {
            sum += 0.233503f;
          } else {
            sum += 0.00594178f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || data[7].qvalue < 80) {
          if (!(data[2].missing != -1) || data[2].qvalue < 0) {
            sum += 0.00434904f;
          } else {
            sum += 0.253924f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 32) {
            sum += -0.195817f;
          } else {
            sum += 0.102154f;
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || data[2].qvalue < 2) {
    if (!(data[0].missing != -1) || data[0].qvalue < 36) {
      sum += 0.28206f;
    } else {
      if (!(data[3].missing != -1) || data[3].qvalue < 44) {
        if (!(data[4].missing != -1) || data[4].qvalue < 52) {
          sum += 0.0660803f;
        } else {
          sum += -0.214142f;
        }
      } else {
        sum += 0.163795f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || data[1].qvalue < 8) {
      if (!(data[1].missing != -1) || data[1].qvalue < 2) {
        if (!(data[0].missing != -1) || data[0].qvalue < 4) {
          sum += -0.126155f;
        } else {
          if (!(data[7].missing != -1) || data[7].qvalue < 70) {
            sum += 0.378355f;
          } else {
            sum += -0.0406053f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || data[3].qvalue < 50) {
          if (!(data[7].missing != -1) || data[7].qvalue < 64) {
            sum += -0.0648222f;
          } else {
            sum += -0.276659f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 60) {
            sum += 0.297746f;
          } else {
            sum += -0.125894f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || data[7].qvalue < 88) {
        if (!(data[8].missing != -1) || data[8].qvalue < 68) {
          if (!(data[3].missing != -1) || data[3].qvalue < 30) {
            sum += 0.033357f;
          } else {
            sum += -0.0998888f;
          }
        } else {
          if (!(data[6].missing != -1) || data[6].qvalue < 82) {
            sum += 0.276806f;
          } else {
            sum += -0.0852383f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || data[2].qvalue < 26) {
          if (!(data[6].missing != -1) || data[6].qvalue < 80) {
            sum += 0.206455f;
          } else {
            sum += -0.0391692f;
          }
        } else {
          if (!(data[0].missing != -1) || data[0].qvalue < 66) {
            sum += -0.287801f;
          } else {
            sum += -0.0800644f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || data[4].qvalue < 0) {
    if (!(data[8].missing != -1) || data[8].qvalue < 4) {
      if (!(data[0].missing != -1) || data[0].qvalue < 28) {
        sum += 0.2786f;
      } else {
        sum += 0.0119113f;
      }
    } else {
      sum += -0.0532238f;
    }
  } else {
    if (!(data[4].missing != -1) || data[4].qvalue < 6) {
      if (!(data[6].missing != -1) || data[6].qvalue < 0) {
        sum += -0.667238f;
      } else {
        sum += 0.0110665f;
      }
    } else {
      if (!(data[1].missing != -1) || data[1].qvalue < 28) {
        if (!(data[0].missing != -1) || data[0].qvalue < 52) {
          if (!(data[8].missing != -1) || data[8].qvalue < 52) {
            sum += -0.0334239f;
          } else {
            sum += 0.0547873f;
          }
        } else {
          if (!(data[3].missing != -1) || data[3].qvalue < 24) {
            sum += 0.132098f;
          } else {
            sum += -0.173849f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || data[5].qvalue < 2) {
          sum += -0.0694379f;
        } else {
          if (!(data[4].missing != -1) || data[4].qvalue < 68) {
            sum += 0.251512f;
          } else {
            sum += 0.07819f;
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}
