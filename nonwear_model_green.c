#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  28, 14, 46, 59, 80, 52, 
};

static const int th_begin[] = {
  0, 28, 42, 88, 147, 227, 
};

static const float threshold[] = {
  10, 12, 14, 15, 18, 19, 20, 21, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 
  35, 36, 37, 39, 40, 41, 43, 44, 46, 1, 3, 4, 6, 8, 10, 11, 12, 13, 14, 15, 
  16, 17, 18, 0.23868805f, 0.25562599f, 0.35739666f, 0.36614487f, 0.48530245f, 
  0.50754082f, 0.55923325f, 0.62257731f, 0.63396227f, 0.68587011f, 0.70069957f, 
  0.75139272f, 0.76288474f, 0.77260196f, 0.78482693f, 0.80511862f, 0.85717118f, 
  0.86446571f, 0.87145001f, 0.88384044f, 0.89339179f, 0.9304648f, 0.9441359f, 
  0.94915056f, 0.95814401f, 0.96953923f, 0.97207254f, 0.97445041f, 0.9761374f, 
  0.9778018f, 0.97842497f, 0.97906977f, 0.98180187f, 0.98296309f, 0.98347503f, 
  0.98478663f, 0.98539889f, 0.98584062f, 0.98695898f, 0.98832434f, 0.98902816f, 
  0.99203241f, 0.99307877f, 0.99382585f, 0.99494356f, 0.99804097f, 0.017264763f, 
  0.020642765f, 0.03045374f, 0.039232224f, 0.051052451f, 0.059495732f, 0.062049072f, 
  0.06443473f, 0.067365877f, 0.07041996f, 0.073506363f, 0.076241218f, 0.090900563f, 
  0.10307521f, 0.12676117f, 0.13373509f, 0.14101849f, 0.14836055f, 0.15128575f, 
  0.15781701f, 0.16463235f, 0.17490105f, 0.20573507f, 0.22292088f, 0.22674525f, 
  0.23526689f, 0.24437651f, 0.26264021f, 0.26798245f, 0.27373818f, 0.27863267f, 
  0.28894106f, 0.30352938f, 0.32474414f, 0.33118802f, 0.33781308f, 0.37445262f, 
  0.45062551f, 0.45780763f, 0.47897261f, 0.54785365f, 0.56959337f, 0.64022243f, 
  0.79027623f, 0.85290593f, 0.87422252f, 1.0417496f, 1.1777458f, 1.3058333f, 
  1.4154671f, 1.7371787f, 1.8327094f, 1.923643f, 2.1674769f, 3.9645576f, 6.345489f, 
  8.4843187f, 13.91188f, 27.931576f, -4698.7568f, -4480.187f, -4352.395f, -3866.8513f, 
  -1321.2f, -1052.3951f, -1006.728f, -821.60162f, -720.16638f, -291.7728f, 
  -136.36639f, 131.96001f, 149.5152f, 218.7888f, 236.35201f, 254.7552f, 310.75201f, 
  358.18399f, 394.776f, 456.68481f, 499.78561f, 509.14081f, 554.40961f, 578.58881f, 
  632.90082f, 643.14563f, 662.01923f, 709.69922f, 724.7168f, 731.0368f, 740.57123f, 
  794.52161f, 814.36963f, 826.14563f, 866.74719f, 964.98077f, 1120.5984f, 1161.0496f, 
  1265.2544f, 1651.6096f, 1809.9008f, 1862.8416f, 1955.6608f, 1990.5216f, 2138.1985f, 
  2704.7295f, 3028.1392f, 3355.8591f, 3916.4065f, 3986.0591f, 4038.856f, 4358.2319f, 
  4472.3281f, 4956.7759f, 5001.7778f, 5197.6318f, 5322.6704f, 5952.9902f, 6082.5713f, 
  6677.1392f, 6714.8735f, 6768.5454f, 7028.2178f, 7366.4497f, 7635.0542f, 7704.8384f, 
  7733.085f, 8425.2236f, 8740.1904f, 8847.0996f, 8952.7217f, 9185.9775f, 9250.8174f, 
  9339.6621f, 9531.2559f, 9783.9775f, 9985.7871f, 10188.945f, 10531.28f, 15318.481f, 
  0.16056338f, 0.17075862f, 0.20027587f, 0.60766667f, 0.61942858f, 0.63266665f, 
  0.64700001f, 0.69764704f, 0.71117646f, 0.73904002f, 0.7984314f, 0.81397182f, 
  0.86253524f, 0.89361703f, 0.91187876f, 0.94075364f, 0.95505881f, 0.98853731f, 
  1.0061177f, 1.1295342f, 1.14656f, 1.2851111f, 1.3025231f, 1.4202985f, 1.4548292f, 
  1.5144789f, 1.6071233f, 1.6279403f, 1.7092121f, 1.7358667f, 1.7596619f, 1.7814153f, 
  1.9161644f, 2.1583283f, 2.1815653f, 2.2593622f, 2.4621713f, 2.5491693f, 2.5813715f, 
  2.9324286f, 3.0326576f, 3.1440001f, 3.7957101f, 4.3281145f, 4.6527123f, 4.7564573f, 
  5.2731428f, 5.771451f, 6.0372224f, 16.472849f, 19.340754f, 24.408438f, 
};


/*
 * \brief function to convert a feature value into bin index.
 * \param val feature value, in floating-point
 * \param fid feature identifier
 * \return bin index corresponding to given feature value
 */
static inline int quantize(float val, unsigned fid) {
  const size_t offset = th_begin[fid];
  const float* array = &threshold[offset];
  int len = th_len[fid];
  int low = 0;
  int high = len;
  int mid;
  float mval;
  // It is possible th_begin[i] == [total_num_threshold]. This means that
  // all features i, (i+1), ... are not used for any of the splits in the model.
  // So in this case, just return something
  if (offset == 279 || val < array[0]) {
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


const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 
};

float PredictGreen(union NonwearEntry* data) {

  for (int i = 0; i < 6; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.58144330978f;
            } else {
              sum += (float)-0.32608696818f;
            }
          } else {
            sum += (float)-0.59411627054f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += (float)-0.26871165633f;
            } else {
              sum += (float)0.077227726579f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              sum += (float)-0.56740742922f;
            } else {
              sum += (float)-0.208695665f;
            }
          }
        }
      } else {
        sum += (float)0.53846156597f;
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          sum += (float)0.33333337307f;
        } else {
          sum += (float)-0.44347828627f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
            sum += (float)0.44000002742f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += (float)-0.31764709949f;
            } else {
              sum += (float)0.33333337307f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
            sum += (float)0.15000000596f;
          } else {
            sum += (float)0.587628901f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += (float)-0.32307696342f;
            } else {
              sum += (float)0.39130437374f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += (float)-0.32727274299f;
            } else {
              sum += (float)0.12000000477f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += (float)0.25714287162f;
            } else {
              sum += (float)0.58187311888f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)0.040000002831f;
            } else {
              sum += (float)0.3405405581f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.32307696342f;
            } else {
              sum += (float)0.32307696342f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += (float)0.27000001073f;
            } else {
              sum += (float)0.51428574324f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
              sum += (float)-0.4865090549f;
            } else {
              sum += (float)0.073684215546f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += (float)0.46666669846f;
            } else {
              sum += (float)0.11250000447f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
        sum += (float)0.59726065397f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += (float)0.54482758045f;
            } else {
              sum += (float)0.21428573132f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
              sum += (float)0.29072165489f;
            } else {
              sum += (float)-0.28181818128f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
            sum += (float)0.58444923162f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
              sum += (float)0.57377052307f;
            } else {
              sum += (float)0.31363636255f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 18)) {
              sum += (float)-0.43329712749f;
            } else {
              sum += (float)-0.016619540751f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += (float)-0.32487940788f;
            } else {
              sum += (float)-0.45923861861f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += (float)-0.35231494904f;
            } else {
              sum += (float)0.083667770028f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
              sum += (float)-0.42034101486f;
            } else {
              sum += (float)0.2914789021f;
            }
          }
        }
      } else {
        sum += (float)0.45214381814f;
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 40)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 10)) {
              sum += (float)0.0057834624313f;
            } else {
              sum += (float)0.31176108122f;
            }
          } else {
            sum += (float)0.45677301288f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
              sum += (float)-0.17882241309f;
            } else {
              sum += (float)0.33621820807f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 36)) {
              sum += (float)0.069092184305f;
            } else {
              sum += (float)0.38364055753f;
            }
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
            sum += (float)0.46323853731f;
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 66)) {
              sum += (float)-0.26057827473f;
            } else {
              sum += (float)0.42738804221f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
              sum += (float)-0.37937855721f;
            } else {
              sum += (float)0.12010701746f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += (float)0.40863749385f;
            } else {
              sum += (float)0.10767322034f;
            }
          }
        }
      }
    }
  } else {
    if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        sum += (float)0.35984295607f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
          sum += (float)-0.44740900397f;
        } else {
          sum += (float)0.30372369289f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        if ( (data[2].missing != -1) && (data[2].qvalue < 76)) {
          sum += (float)0.4636811316f;
        } else {
          sum += (float)0.14280535281f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 62)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 36)) {
              sum += (float)0.15220926702f;
            } else {
              sum += (float)0.41609367728f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 10)) {
              sum += (float)0.51147699356f;
            } else {
              sum += (float)-0.17733545601f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
            sum += (float)0.44604888558f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
              sum += (float)0.43487989902f;
            } else {
              sum += (float)0.191934973f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
    if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
            sum += (float)-0.39847102761f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += (float)0.12853658199f;
            } else {
              sum += (float)-0.34466695786f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 98)) {
              sum += (float)-0.13687409461f;
            } else {
              sum += (float)0.46739593148f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += (float)-0.38032391667f;
            } else {
              sum += (float)-0.1231347844f;
            }
          }
        }
      } else {
        sum += (float)0.34428414702f;
      }
    } else {
      if ( (data[2].missing != -1) && (data[2].qvalue < 34)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += (float)0.40985903144f;
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 38)) {
            sum += (float)0.34757560492f;
          } else {
            sum += (float)-0.049240332097f;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 142)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += (float)-0.054343044758f;
            } else {
              sum += (float)0.25938749313f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)0.029082486406f;
            } else {
              sum += (float)-0.37803563476f;
            }
          }
        } else {
          sum += (float)0.37806463242f;
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 48)) {
            sum += (float)0.076917663217f;
          } else {
            sum += (float)-0.28687265515f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 60)) {
              sum += (float)0.27865689993f;
            } else {
              sum += (float)-0.14330893755f;
            }
          } else {
            sum += (float)0.39826151729f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
          sum += (float)0.40171611309f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
            sum += (float)0.38986620307f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += (float)0.37389841676f;
            } else {
              sum += (float)-0.46302980185f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += (float)0.42847105861f;
            } else {
              sum += (float)0.12605294585f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 70)) {
              sum += (float)-0.029137333855f;
            } else {
              sum += (float)0.46421861649f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 142)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += (float)0.38724899292f;
            } else {
              sum += (float)-0.32353243232f;
            }
          } else {
            sum += (float)0.51179403067f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          sum += (float)0.38984328508f;
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 64)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
              sum += (float)0.12702994049f;
            } else {
              sum += (float)0.39608380198f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 62)) {
              sum += (float)-0.3323790431f;
            } else {
              sum += (float)0.40067726374f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 14)) {
              sum += (float)-0.29776346684f;
            } else {
              sum += (float)-0.36308285594f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += (float)0.25453752279f;
            } else {
              sum += (float)-0.28271627426f;
            }
          }
        } else {
          sum += (float)0.25843212008f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
              sum += (float)0.33768606186f;
            } else {
              sum += (float)-0.34469914436f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
              sum += (float)0.3895971477f;
            } else {
              sum += (float)0.033188901842f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 48)) {
              sum += (float)0.45476850867f;
            } else {
              sum += (float)-0.1035765484f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
              sum += (float)-0.32749477029f;
            } else {
              sum += (float)0.39953622222f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
          sum += (float)0.35867711902f;
        } else {
          sum += (float)0.084111139178f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 94)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += (float)-0.28654801846f;
            } else {
              sum += (float)0.22864799201f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += (float)-0.38146904111f;
            } else {
              sum += (float)-0.14224308729f;
            }
          }
        } else {
          sum += (float)0.33888590336f;
        }
      }
    }
  } else {
    if ( (data[3].missing != -1) && (data[3].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            sum += (float)0.29925218225f;
          } else {
            sum += (float)-0.41781848669f;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 26)) {
            sum += (float)-0.13854551315f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += (float)0.35993134975f;
            } else {
              sum += (float)0.045238688588f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
          sum += (float)0.36711993814f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
            sum += (float)0.35365721583f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += (float)0.32716596127f;
            } else {
              sum += (float)-0.38259324431f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 78)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += (float)0.35668432713f;
            } else {
              sum += (float)0.16194739938f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
              sum += (float)-0.10000918061f;
            } else {
              sum += (float)0.36312872171f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 20)) {
              sum += (float)0.31268131733f;
            } else {
              sum += (float)-0.26633471251f;
            }
          } else {
            sum += (float)0.35886752605f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 38)) {
              sum += (float)0.10411429405f;
            } else {
              sum += (float)0.35818475485f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 130)) {
              sum += (float)-0.17424581945f;
            } else {
              sum += (float)0.37373676896f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
              sum += (float)0.34730666876f;
            } else {
              sum += (float)-0.088067889214f;
            }
          } else {
            sum += (float)0.36932051182f;
          }
        }
      }
    }
  }
  if ( (data[1].missing != -1) && (data[1].qvalue < 18)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 26)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 14)) {
              sum += (float)-0.32716742158f;
            } else {
              sum += (float)0.0043754219078f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += (float)-0.15324571729f;
            } else {
              sum += (float)-0.33536151052f;
            }
          }
        } else {
          sum += (float)0.2704397738f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 20)) {
              sum += (float)0.20189489424f;
            } else {
              sum += (float)-0.12362875044f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
              sum += (float)0.12405474484f;
            } else {
              sum += (float)0.46949630976f;
            }
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 90)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 148)) {
              sum += (float)-0.29321506619f;
            } else {
              sum += (float)0.32168126106f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 60)) {
              sum += (float)-0.065149113536f;
            } else {
              sum += (float)0.26547536254f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
          sum += (float)0.34400939941f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += (float)-0.11863712966f;
            } else {
              sum += (float)0.19173680246f;
            }
          } else {
            sum += (float)0.39477068186f;
          }
        }
      } else {
        if ( (data[2].missing != -1) && (data[2].qvalue < 66)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
              sum += (float)0.13946720958f;
            } else {
              sum += (float)0.57167011499f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += (float)0.23632708192f;
            } else {
              sum += (float)-0.20066350698f;
            }
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 80)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 74)) {
              sum += (float)0.25677117705f;
            } else {
              sum += (float)-0.27769687772f;
            }
          } else {
            sum += (float)0.50161987543f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
      sum += (float)0.34608414769f;
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
            sum += (float)0.057365562767f;
          } else {
            sum += (float)-0.3404686749f;
          }
        } else {
          sum += (float)0.203549698f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            sum += (float)0.33294421434f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
              sum += (float)0.1133601144f;
            } else {
              sum += (float)0.32119297981f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 60)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 36)) {
              sum += (float)0.13975425065f;
            } else {
              sum += (float)0.31700626016f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
              sum += (float)-0.25316023827f;
            } else {
              sum += (float)0.24037148058f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
              sum += (float)-0.271404773f;
            } else {
              sum += (float)-0.32848671079f;
            }
          } else {
            sum += (float)0.17717051506f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 82)) {
              sum += (float)-0.079349860549f;
            } else {
              sum += (float)-0.28136485815f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += (float)0.51112258434f;
            } else {
              sum += (float)-0.1893517524f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 38)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += (float)-0.11480760574f;
            } else {
              sum += (float)-0.3522118628f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 8)) {
              sum += (float)0.50764364004f;
            } else {
              sum += (float)0.035901173949f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 88)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 156)) {
              sum += (float)-0.29808694124f;
            } else {
              sum += (float)0.27306982875f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 90)) {
              sum += (float)-0.0092301052064f;
            } else {
              sum += (float)0.37406381965f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
        sum += (float)0.32110542059f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            sum += (float)0.26615306735f;
          } else {
            sum += (float)-0.28102940321f;
          }
        } else {
          sum += (float)0.29037129879f;
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += (float)0.072302535176f;
            } else {
              sum += (float)0.28634494543f;
            }
          } else {
            sum += (float)-0.41086819768f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 38)) {
              sum += (float)0.17095644772f;
            } else {
              sum += (float)0.32197439671f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += (float)0.29832598567f;
            } else {
              sum += (float)-0.071455657482f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
          sum += (float)0.33161145449f;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 14)) {
            sum += (float)0.31612512469f;
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
              sum += (float)0.25470373034f;
            } else {
              sum += (float)-0.23662956059f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 32)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
              sum += (float)0.22777165473f;
            } else {
              sum += (float)-0.35187232494f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += (float)0.37292158604f;
            } else {
              sum += (float)0.079237796366f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 28)) {
              sum += (float)0.21329000592f;
            } else {
              sum += (float)0.40530529618f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 46)) {
              sum += (float)-0.19384071231f;
            } else {
              sum += (float)0.16110181808f;
            }
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 26)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)0.086920082569f;
            } else {
              sum += (float)0.33389616013f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += (float)-0.14725680649f;
            } else {
              sum += (float)0.27812513709f;
            }
          }
        } else {
          sum += (float)0.32966417074f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
    if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
              sum += (float)0.16348133981f;
            } else {
              sum += (float)-0.26227891445f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.32022988796f;
            } else {
              sum += (float)-0.27321568131f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 82)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += (float)0.032933749259f;
            } else {
              sum += (float)-0.27592983842f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 116)) {
              sum += (float)0.035412803292f;
            } else {
              sum += (float)0.28310158849f;
            }
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 48)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
              sum += (float)-0.11576421559f;
            } else {
              sum += (float)0.32127714157f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 20)) {
              sum += (float)0.67870599031f;
            } else {
              sum += (float)0.29012593627f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
              sum += (float)-0.28196084499f;
            } else {
              sum += (float)0.035569690168f;
            }
          } else {
            sum += (float)0.28700217605f;
          }
        }
      }
    } else {
      if ( (data[2].missing != -1) && (data[2].qvalue < 28)) {
        sum += (float)0.30387181044f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
            sum += (float)0.2327015996f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += (float)0.07052423805f;
            } else {
              sum += (float)-0.31778666377f;
            }
          }
        } else {
          sum += (float)0.26169171929f;
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += (float)0.060321591794f;
            } else {
              sum += (float)0.25815808773f;
            }
          } else {
            sum += (float)-0.35031586885f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            sum += (float)0.3295789361f;
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 110)) {
              sum += (float)0.035221051425f;
            } else {
              sum += (float)0.33645299077f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
          sum += (float)0.3213249445f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 46)) {
              sum += (float)0.14408610761f;
            } else {
              sum += (float)-0.14829945564f;
            }
          } else {
            sum += (float)0.28785902262f;
          }
        }
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 144)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 42)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 74)) {
              sum += (float)-0.0053248442709f;
            } else {
              sum += (float)0.48428890109f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 56)) {
              sum += (float)0.23766462505f;
            } else {
              sum += (float)0.3757673502f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 26)) {
              sum += (float)0.30604413152f;
            } else {
              sum += (float)-0.19790771604f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
              sum += (float)0.065881706774f;
            } else {
              sum += (float)0.43716067076f;
            }
          }
        }
      } else {
        sum += (float)0.36092126369f;
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if ( (data[2].missing != -1) && (data[2].qvalue < 68)) {
              sum += (float)0.19113406539f;
            } else {
              sum += (float)-0.24525244534f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.31453114748f;
            } else {
              sum += (float)-0.25163933635f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 38)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)-0.13850429654f;
            } else {
              sum += (float)0.47125306726f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += (float)-0.068835608661f;
            } else {
              sum += (float)-0.24822671711f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
              sum += (float)-0.19571825862f;
            } else {
              sum += (float)0.25094217062f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += (float)-0.072280012071f;
            } else {
              sum += (float)-0.27534458041f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)0.57914817333f;
            } else {
              sum += (float)0.14986023307f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
              sum += (float)0.16525067389f;
            } else {
              sum += (float)-0.20378786325f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
              sum += (float)0.02049645409f;
            } else {
              sum += (float)0.30336245894f;
            }
          } else {
            sum += (float)-0.29861587286f;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 62)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 38)) {
              sum += (float)0.040560811758f;
            } else {
              sum += (float)0.30875551701f;
            }
          } else {
            sum += (float)0.39085334539f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              sum += (float)0.30315071344f;
            } else {
              sum += (float)-0.028463674709f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
              sum += (float)-0.21453543007f;
            } else {
              sum += (float)0.12107164413f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += (float)0.073641069233f;
            } else {
              sum += (float)0.37119725347f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.12498734891f;
            } else {
              sum += (float)0.20344415307f;
            }
          }
        }
      }
    }
  } else {
    if ( (data[3].missing != -1) && (data[3].qvalue < 12)) {
      sum += (float)0.31367853284f;
    } else {
      if ( (data[2].missing != -1) && (data[2].qvalue < 20)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
            sum += (float)0.31109037995f;
          } else {
            sum += (float)0.080772042274f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
              sum += (float)0.27259764075f;
            } else {
              sum += (float)-0.051812510937f;
            }
          } else {
            sum += (float)0.29489293694f;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 36)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 34)) {
              sum += (float)-0.020140312612f;
            } else {
              sum += (float)0.27176809311f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
              sum += (float)0.1386346668f;
            } else {
              sum += (float)0.31800872087f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
              sum += (float)-0.17305958271f;
            } else {
              sum += (float)0.32415312529f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += (float)-0.041189108044f;
            } else {
              sum += (float)0.38404461741f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += (float)-0.26771053672f;
            } else {
              sum += (float)0.38836637139f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += (float)-0.086453676224f;
            } else {
              sum += (float)0.6639277935f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
              sum += (float)-0.10553494841f;
            } else {
              sum += (float)-0.29924115539f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 102)) {
              sum += (float)0.09474311769f;
            } else {
              sum += (float)-0.25480416417f;
            }
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 86)) {
          sum += (float)-0.21703977883f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
            sum += (float)0.56784939766f;
          } else {
            sum += (float)0.12420086563f;
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
          sum += (float)0.31202745438f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            sum += (float)0.083417654037f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += (float)-0.1182018891f;
            } else {
              sum += (float)0.057127546519f;
            }
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 94)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              sum += (float)-0.049773138016f;
            } else {
              sum += (float)0.22870013118f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 150)) {
              sum += (float)-0.23137751222f;
            } else {
              sum += (float)0.30813151598f;
            }
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 106)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 96)) {
              sum += (float)0.24604472518f;
            } else {
              sum += (float)-0.16954678297f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += (float)0.3586037755f;
            } else {
              sum += (float)-0.089307069778f;
            }
          }
        }
      }
    }
  } else {
    if ( (data[3].missing != -1) && (data[3].qvalue < 16)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 4)) {
            sum += (float)0.066821485758f;
          } else {
            sum += (float)0.27647680044f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
            sum += (float)-0.19401067495f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.13519822061f;
            } else {
              sum += (float)0.24592429399f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
          sum += (float)0.30904585123f;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 22)) {
            sum += (float)0.27723100781f;
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 46)) {
              sum += (float)0.23759675026f;
            } else {
              sum += (float)-0.29447114468f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
        if ( (data[2].missing != -1) && (data[2].qvalue < 4)) {
          sum += (float)0.3099810183f;
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
              sum += (float)0.13661266863f;
            } else {
              sum += (float)0.36027109623f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += (float)-0.11642497778f;
            } else {
              sum += (float)0.31246444583f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += (float)0.25173765421f;
            } else {
              sum += (float)0.037154290825f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
              sum += (float)0.22419366241f;
            } else {
              sum += (float)0.45611831546f;
            }
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 96)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += (float)0.22829793394f;
            } else {
              sum += (float)-0.18154904246f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += (float)0.35629165173f;
            } else {
              sum += (float)0.099567644298f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 24)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 0)) {
              sum += (float)-0.23662985861f;
            } else {
              sum += (float)0.1720906198f;
            }
          } else {
            sum += (float)-0.30066639185f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += (float)-0.17724354565f;
            } else {
              sum += (float)0.15774589777f;
            }
          } else {
            sum += (float)0.72793108225f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 58)) {
              sum += (float)0.41607543826f;
            } else {
              sum += (float)-0.16980281472f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              sum += (float)-0.29568383098f;
            } else {
              sum += (float)-0.092745408416f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
            sum += (float)-0.21325753629f;
          } else {
            sum += (float)0.36241060495f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 90)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
              sum += (float)-0.10054735094f;
            } else {
              sum += (float)0.34884086251f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.35009741783f;
            } else {
              sum += (float)0.22389428318f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 54)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += (float)-0.036415398121f;
            } else {
              sum += (float)0.31200733781f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
              sum += (float)0.96831685305f;
            } else {
              sum += (float)0.25778380036f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += (float)0.21282285452f;
            } else {
              sum += (float)-0.22449798882f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 40)) {
              sum += (float)-0.24960838258f;
            } else {
              sum += (float)-0.038339093328f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 68)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += (float)0.10787775367f;
            } else {
              sum += (float)0.376596421f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += (float)-0.12227036059f;
            } else {
              sum += (float)0.22567076981f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
      sum += (float)0.30191013217f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 100)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += (float)0.22073125839f;
            } else {
              sum += (float)-0.1117754057f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              sum += (float)-0.30630674958f;
            } else {
              sum += (float)0.1730351001f;
            }
          }
        } else {
          sum += (float)0.29687401652f;
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 48)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 76)) {
              sum += (float)0.10637257993f;
            } else {
              sum += (float)0.30491557717f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += (float)0.28713262081f;
            } else {
              sum += (float)-0.083368003368f;
            }
          }
        } else {
          sum += (float)0.33688488603f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 12)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
              sum += (float)-0.0089748892933f;
            } else {
              sum += (float)-0.28098222613f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
              sum += (float)-0.17391549051f;
            } else {
              sum += (float)0.45785501599f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 40)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              sum += (float)-0.17149657011f;
            } else {
              sum += (float)0.20244939625f;
            }
          } else {
            if ( (data[1].missing != -1) && (data[1].qvalue < 0)) {
              sum += (float)0.075406543911f;
            } else {
              sum += (float)-0.29061147571f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            sum += (float)-0.060498952866f;
          } else {
            sum += (float)0.53042644262f;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 156)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += (float)0.02746072039f;
            } else {
              sum += (float)-0.24675914645f;
            }
          } else {
            sum += (float)0.23498539627f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += (float)-0.066114977002f;
            } else {
              sum += (float)0.28456410766f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += (float)0.42325210571f;
            } else {
              sum += (float)0.16457238793f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 152)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
              sum += (float)0.074532486498f;
            } else {
              sum += (float)-0.20012079179f;
            }
          } else {
            sum += (float)0.34120899439f;
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
          sum += (float)0.10872519016f;
        } else {
          sum += (float)0.30250176787f;
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
      sum += (float)0.29968008399f;
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 132)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 82)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
              sum += (float)0.26462614536f;
            } else {
              sum += (float)0.031000966206f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += (float)0.4409095943f;
            } else {
              sum += (float)0.18478693068f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 92)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
              sum += (float)0.13406442106f;
            } else {
              sum += (float)-0.34090000391f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
              sum += (float)-0.04149851203f;
            } else {
              sum += (float)0.32651859522f;
            }
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 10)) {
          sum += (float)-0.040612787008f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            sum += (float)0.46316465735f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += (float)-0.13430485129f;
            } else {
              sum += (float)0.29341757298f;
            }
          }
        }
      }
    }
  }
  if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
              sum += (float)0.29034906626f;
            } else {
              sum += (float)-0.25673854351f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 40)) {
              sum += (float)-0.042356960475f;
            } else {
              sum += (float)-0.29618960619f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 86)) {
              sum += (float)-0.043353114277f;
            } else {
              sum += (float)0.43970248103f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
              sum += (float)-0.25310778618f;
            } else {
              sum += (float)0.13596831262f;
            }
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            sum += (float)-0.04969374463f;
          } else {
            sum += (float)0.4813939929f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += (float)-0.042844656855f;
            } else {
              sum += (float)-0.27219665051f;
            }
          } else {
            sum += (float)0.19087459147f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 0)) {
              sum += (float)-0.12791602314f;
            } else {
              sum += (float)0.27882772684f;
            }
          } else {
            if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
              sum += (float)-0.31029331684f;
            } else {
              sum += (float)-0.095392815769f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
            sum += (float)0.33928832412f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += (float)-0.22336833179f;
            } else {
              sum += (float)0.3088748455f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 32)) {
              sum += (float)0.03052825667f;
            } else {
              sum += (float)-0.16712751985f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 108)) {
              sum += (float)0.0049476046115f;
            } else {
              sum += (float)0.19833509624f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            if ( (data[2].missing != -1) && (data[2].qvalue < 84)) {
              sum += (float)-0.1799890697f;
            } else {
              sum += (float)0.20342665911f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              sum += (float)0.26376968622f;
            } else {
              sum += (float)0.078627675772f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
        sum += (float)0.30299180746f;
      } else {
        sum += (float)0.012553736567f;
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 100)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          sum += (float)-0.073053210974f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
              sum += (float)0.20492912829f;
            } else {
              sum += (float)0.31776046753f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += (float)0.22777593136f;
            } else {
              sum += (float)-0.23940165341f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += (float)0.18641331792f;
            } else {
              sum += (float)-0.30088758469f;
            }
          } else {
            sum += (float)0.2121539861f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
              sum += (float)0.10421543568f;
            } else {
              sum += (float)0.29300567508f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += (float)-0.16907852888f;
            } else {
              sum += (float)0.14508783817f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 0)) {
            sum += (float)0.032973241061f;
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 40)) {
              sum += (float)-0.0072646937333f;
            } else {
              sum += (float)-0.29232484102f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 86)) {
              sum += (float)-0.05985615775f;
            } else {
              sum += (float)0.25659951568f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
              sum += (float)-0.24714487791f;
            } else {
              sum += (float)0.23296631873f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
          sum += (float)-0.21908181906f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += (float)0.56508708f;
            } else {
              sum += (float)-0.022867025807f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.23474162817f;
            } else {
              sum += (float)0.15378217399f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 50)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
              sum += (float)-0.10662414134f;
            } else {
              sum += (float)0.068531811237f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
              sum += (float)0.26409190893f;
            } else {
              sum += (float)0.051999237388f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
              sum += (float)0.23999750614f;
            } else {
              sum += (float)-0.063173741102f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += (float)0.50173360109f;
            } else {
              sum += (float)0.13754478097f;
            }
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 92)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 36)) {
              sum += (float)-0.0015748917358f;
            } else {
              sum += (float)-0.20137517154f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
              sum += (float)0.017412994057f;
            } else {
              sum += (float)0.32542070746f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += (float)0.28280597925f;
            } else {
              sum += (float)-0.052565809339f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 140)) {
              sum += (float)-0.057486150414f;
            } else {
              sum += (float)0.25543370843f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
        sum += (float)0.30072236061f;
      } else {
        sum += (float)0.010391041636f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 100)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += (float)0.11567751318f;
            } else {
              sum += (float)0.29422214627f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.28160366416f;
            } else {
              sum += (float)0.18212535977f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
              sum += (float)-0.17568144202f;
            } else {
              sum += (float)0.17513871193f;
            }
          } else {
            sum += (float)0.25558277965f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
          sum += (float)0.27549257874f;
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 44)) {
            sum += (float)0.010886542499f;
          } else {
            sum += (float)0.19214443862f;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
      if ( (data[1].missing != -1) && (data[1].qvalue < 18)) {
        if ( (data[2].missing != -1) && (data[2].qvalue < 16)) {
          sum += (float)0.21316160262f;
        } else {
          sum += (float)-0.12194147706f;
        }
      } else {
        sum += (float)0.292540133f;
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 88)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
          sum += (float)-0.03621789068f;
        } else {
          sum += (float)0.27935385704f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
            sum += (float)0.14129048586f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
              sum += (float)-0.43079435825f;
            } else {
              sum += (float)-0.088571488857f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 40)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
              sum += (float)-0.14636468887f;
            } else {
              sum += (float)0.17851959169f;
            }
          } else {
            sum += (float)0.33538904786f;
          }
        }
      }
    }
  } else {
    if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += (float)-0.18242883682f;
            } else {
              sum += (float)0.2626568079f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
              sum += (float)-0.29322835803f;
            } else {
              sum += (float)-0.084939688444f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 90)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += (float)0.019729666412f;
            } else {
              sum += (float)-0.20488040149f;
            }
          } else {
            sum += (float)0.24969494343f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 104)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += (float)-0.086237512529f;
            } else {
              sum += (float)0.19126561284f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
              sum += (float)0.52599477768f;
            } else {
              sum += (float)0.10563770682f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
            sum += (float)-0.29797723889f;
          } else {
            sum += (float)0.24410691857f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += (float)-0.051183581352f;
            } else {
              sum += (float)0.093260094523f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += (float)0.11030437797f;
            } else {
              sum += (float)0.28010216355f;
            }
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 8)) {
            sum += (float)-0.206908077f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
              sum += (float)0.25826662779f;
            } else {
              sum += (float)0.52909833193f;
            }
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 78)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 152)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
              sum += (float)-0.22603963315f;
            } else {
              sum += (float)0.16791369021f;
            }
          } else {
            sum += (float)0.21807838976f;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 102)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
              sum += (float)0.18906858563f;
            } else {
              sum += (float)-0.11304166168f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 26)) {
              sum += (float)0.054400410503f;
            } else {
              sum += (float)0.30493569374f;
            }
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
      sum += (float)0.29668101668f;
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 86)) {
              sum += (float)0.14974321425f;
            } else {
              sum += (float)-0.10002335906f;
            }
          } else {
            sum += (float)0.31976789236f;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 2)) {
            sum += (float)0.040962509811f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
              sum += (float)-0.10600535572f;
            } else {
              sum += (float)-0.41969665885f;
            }
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 40)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 70)) {
            sum += (float)0.20814588666f;
          } else {
            sum += (float)-0.09197871387f;
          }
        } else {
          sum += (float)0.31019979715f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
        if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += (float)0.052021548152f;
            } else {
              sum += (float)-0.22132602334f;
            }
          } else {
            sum += (float)0.35228645802f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 102)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += (float)-0.29049840569f;
            } else {
              sum += (float)-0.10501128435f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += (float)0.058460470289f;
            } else {
              sum += (float)-0.19161501527f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
          sum += (float)-0.16563427448f;
        } else {
          sum += (float)0.35037791729f;
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 38)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += (float)-0.06553825736f;
            } else {
              sum += (float)0.16318237782f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 56)) {
              sum += (float)0.065035991371f;
            } else {
              sum += (float)0.41436439753f;
            }
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 14)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
              sum += (float)0.15959855914f;
            } else {
              sum += (float)-0.099385015666f;
            }
          } else {
            sum += (float)0.27120116353f;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 54)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 54)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 142)) {
              sum += (float)-0.15841639042f;
            } else {
              sum += (float)0.19681717455f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 42)) {
              sum += (float)0.022616451606f;
            } else {
              sum += (float)0.39968755841f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 66)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
              sum += (float)-0.0018997086445f;
            } else {
              sum += (float)0.22943840921f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += (float)-0.055690776557f;
            } else {
              sum += (float)0.20171712339f;
            }
          }
        }
      }
    }
  }
  
  return 1.0f / (1 + expf(-sum));
}