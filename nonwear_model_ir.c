#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  64, 25, 16, 50, 73, 57, 50, 
};
static const int th_begin[] = {
  0, 64, 89, 105, 155, 228, 285, 
};

static const float threshold[] = {
  -0.073990807f, -0.029249214f, 0.020937111f, 0.1273407f, 0.33450332f, 0.34303787f, 
  0.38686323f, 0.39648834f, 0.49935928f, 0.56043577f, 0.59320146f, 0.60565299f, 
  0.61678439f, 0.62859768f, 0.64190704f, 0.70674014f, 0.72205997f, 0.75397873f, 
  0.77677f, 0.79850185f, 0.81226367f, 0.83971918f, 0.85357249f, 0.86605471f, 
  0.96022725f, 0.97036749f, 0.99861604f, 1.0210415f, 1.0317522f, 1.0435328f, 
  1.0669736f, 1.0865496f, 1.0994638f, 1.1099194f, 1.1193507f, 1.135576f, 1.1635168f, 
  1.1887594f, 1.2278343f, 1.2368616f, 1.2446175f, 1.276584f, 1.2911215f, 1.2978632f, 
  1.3052481f, 1.3203541f, 1.3612829f, 1.3970426f, 1.470317f, 1.5049394f, 1.5244654f, 
  1.5309763f, 1.5381202f, 1.6010123f, 1.6595874f, 1.7042621f, 1.7355303f, 1.7678782f, 
  1.7921454f, 1.858025f, 1.8781821f, 1.9089903f, 1.9186411f, 2.0976808f, 14, 18, 19, 
  20, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 41, 
  43, 45, 46, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 
  0.054507717f, 0.056519099f, 0.058647525f, 0.06095792f, 0.065981686f, 0.071255773f, 
  0.073537968f, 0.076250866f, 0.07897421f, 0.082513906f, 0.088597298f, 0.092287838f, 
  0.095727868f, 0.098882176f, 0.10944387f, 0.11681036f, 0.12353799f, 0.1348066f, 
  0.13870449f, 0.1553202f, 0.15925257f, 0.16344903f, 0.17465299f, 0.25124881f, 
  0.26413265f, 0.26814082f, 0.31879607f, 0.34818941f, 0.44174969f, 0.51398921f, 
  0.58366734f, 0.62748063f, 0.75423753f, 0.81413883f, 0.90300316f, 0.92092562f, 
  0.93817103f, 1.1882348f, 1.7087911f, 2.1871934f, 2.2874968f, 3.1475315f, 3.3320563f, 
  3.5386364f, 5.0812593f, 5.6357818f, 10.929135f, 18.459688f, 32.101757f, 62.937302f, 
  0.32043505f, 0.64344293f, 0.86010528f, 1.0515928f, 1.2060616f, 1.2426062f, 
  1.3014939f, 1.3489288f, 1.3885621f, 1.4077671f, 1.5119684f, 1.5981013f, 1.6190681f, 
  1.6309668f, 1.6621168f, 1.6953005f, 1.7523128f, 1.7593262f, 1.7711903f, 1.7769766f, 
  1.7891252f, 1.8000973f, 1.8131598f, 1.8283194f, 1.8385178f, 1.8433177f, 1.8521153f, 
  1.86474f, 1.8857892f, 1.8892027f, 1.8926073f, 1.9137037f, 1.9169292f, 1.9207186f, 
  1.9236252f, 1.944749f, 1.9473876f, 1.96297f, 1.9687499f, 1.9784715f, 1.9810563f, 
  1.9851772f, 1.9874438f, 1.9897834f, 1.9970311f, 1.9997849f, 2.0019662f, 2.0041554f, 
  2.0065396f, 2.0091074f, 2.0127778f, 2.0172696f, 2.0313897f, 2.0370317f, 2.0573907f, 
  2.0617905f, 2.0654759f, 2.0689027f, 2.0759735f, 2.08476f, 2.0863757f, 2.1078002f, 
  2.1092708f, 2.1431465f, 2.1491559f, 2.1547518f, 2.1661534f, 2.1696587f, 2.1713583f, 
  2.1746464f, 2.184684f, 2.1897542f, 2.2008078f, 0.42133254f, 0.45647529f, 
  0.58899027f, 0.62090611f, 0.6603741f, 0.75309515f, 0.80143809f, 0.93103468f, 
  0.97749203f, 1.0803829f, 1.2469236f, 1.3136919f, 1.377313f, 1.573177f, 1.7666551f, 
  1.8290911f, 1.9622959f, 2.0181684f, 2.2517147f, 2.8712807f, 2.9574718f, 3.1450973f, 
  3.8183477f, 4.1331282f, 4.6018157f, 4.7141156f, 4.8233156f, 5.3831258f, 5.4975758f, 
  6.1151452f, 6.2891793f, 6.4151244f, 6.7122941f, 7.0390692f, 7.365448f, 8.2539406f, 
  10.998661f, 11.477125f, 12.249121f, 12.539635f, 14.153408f, 15.496893f, 16.141802f, 
  19.526428f, 27.590584f, 34.932194f, 43.826992f, 81.689476f, 106.443f, 121.85773f, 
  746.125f, 953.66565f, 1061.7565f, 2184.2854f, 3118.2119f, 12096.264f, 49732.102f, 
  0.61281163f, 0.90311474f, 0.94098878f, 0.98944014f, 1.0900095f, 1.2647036f, 
  1.3187093f, 1.6465805f, 1.6985402f, 1.7493283f, 1.8773569f, 2.2888999f, 2.3634269f, 
  2.50019f, 2.5743394f, 2.8712668f, 3.0193717f, 3.3410368f, 3.6043143f, 3.690187f, 
  3.7934556f, 3.8825243f, 4.0721684f, 4.3694468f, 4.4485087f, 4.6731315f, 4.8993111f, 
  5.9305301f, 6.0695205f, 6.2177873f, 6.802371f, 6.9335308f, 7.0618696f, 11.900625f, 
  12.352226f, 12.593102f, 21.752512f, 25.182884f, 27.748861f, 30.041573f, 52.801723f, 
  61.144966f, 184.88393f, 196.86011f, 324.2496f, 398.59991f, 448.45056f, 698.5296f, 
  1688.7847f, 2170.1726f, 
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
  if (offset == 335 || val < array[0]) {
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

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 
};

float PredictIr(union NonwearEntry* data) {

  for (int i = 0; i < 7; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
              sum += (float)0.47755101323f;
            } else {
              sum += (float)-0.15000000596f;
            }
          } else {
            sum += (float)0.58431375027f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
            sum += (float)0.54000002146f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
              sum += (float)-0.30000001192f;
            } else {
              sum += (float)0.05000000447f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += (float)-0.090000003576f;
            } else {
              sum += (float)0.375f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += (float)0.56190478802f;
            } else {
              sum += (float)0.31914895773f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += (float)-0.49714288116f;
            } else {
              sum += (float)0.22173914313f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += (float)0.30000001192f;
            } else {
              sum += (float)-0.35436242819f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
        sum += (float)0.59432131052f;
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += (float)0.12000000477f;
            } else {
              sum += (float)0.53684210777f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += (float)0.35454544425f;
            } else {
              sum += (float)-0.2880000174f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
            sum += (float)0.5586207509f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += (float)-.0f;
            } else {
              sum += (float)0.36000001431f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)0.07500000298f;
            } else {
              sum += (float)0.48000001907f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += (float)0.20000001788f;
            } else {
              sum += (float)-0.30000001192f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)-0.53633636236f;
            } else {
              sum += (float)-0.21290323138f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
              sum += (float)-0.50202023983f;
            } else {
              sum += (float)-0.5801898241f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += (float)0.24000000954f;
            } else {
              sum += (float)0.55384618044f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += (float)0.45517241955f;
            } else {
              sum += (float)0.0068965521641f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += (float)0.4978723824f;
            } else {
              sum += (float)0.094736844301f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += (float)0.32307696342f;
            } else {
              sum += (float)-0.48205932975f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
            sum += (float)0.30000001192f;
          } else {
            sum += (float)-0.40000003576f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
            sum += (float)0.57065218687f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
              sum += (float)0.52653062344f;
            } else {
              sum += (float)-0.058064516634f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += (float)0.10000000894f;
            } else {
              sum += (float)0.48235297203f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += (float)-0.20000001788f;
            } else {
              sum += (float)0.054545458406f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += (float)0.30000001192f;
            } else {
              sum += (float)-0.21702127159f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
              sum += (float)-0.54418605566f;
            } else {
              sum += (float)-.0f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
          sum += (float)0.46163666248f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
            sum += (float)0.38302311301f;
          } else {
            sum += (float)-0.081320434809f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
              sum += (float)0.36344891787f;
            } else {
              sum += (float)0.046636529267f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
              sum += (float)0.36254525185f;
            } else {
              sum += (float)-0.014862594195f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 88)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += (float)-0.30659776926f;
            } else {
              sum += (float)0.15955905616f;
            }
          } else {
            if ( (data[6].missing != -1) && (data[6].qvalue < 42)) {
              sum += (float)-0.023188054562f;
            } else {
              sum += (float)-0.32791870832f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          sum += (float)0.46459904313f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 86)) {
              sum += (float)0.37514033914f;
            } else {
              sum += (float)0.037942390889f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
              sum += (float)0.44888442755f;
            } else {
              sum += (float)0.05639212206f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += (float)0.42852196097f;
            } else {
              sum += (float)0.13012327254f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += (float)0.15202875435f;
            } else {
              sum += (float)-0.32729616761f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += (float)0.31003186107f;
            } else {
              sum += (float)0.43516400456f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += (float)0.32116657495f;
            } else {
              sum += (float)-0.17405548692f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
        if ( (data[1].missing != -1) && (data[1].qvalue < 18)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 44)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += (float)0.23385579884f;
            } else {
              sum += (float)-0.39854449034f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += (float)0.48497438431f;
            } else {
              sum += (float)0.11562088877f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 84)) {
            if ( (data[2].missing != -1) && (data[2].qvalue < 12)) {
              sum += (float)0.17111822963f;
            } else {
              sum += (float)0.47473815084f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += (float)0.40139809251f;
            } else {
              sum += (float)-0.0098841693252f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += (float)0.28916174173f;
            } else {
              sum += (float)-0.1572817862f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += (float)-0.2285554558f;
            } else {
              sum += (float)-0.43052026629f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 20)) {
              sum += (float)0.4169537425f;
            } else {
              sum += (float)0.14832551777f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
              sum += (float)0.11033058167f;
            } else {
              sum += (float)-0.37239211798f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
            sum += (float)-0.0365842022f;
          } else {
            sum += (float)0.44362461567f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 90)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += (float)0.40205189586f;
            } else {
              sum += (float)0.049259860069f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
              sum += (float)0.17179533839f;
            } else {
              sum += (float)-0.31901878119f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
              sum += (float)0.10216800123f;
            } else {
              sum += (float)-0.31154766679f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += (float)0.36366781592f;
            } else {
              sum += (float)-0.037117622793f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
            sum += (float)-0.44081154466f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
              sum += (float)0.040340133011f;
            } else {
              sum += (float)-0.37832251191f;
            }
          }
        }
      }
    }
  }
  if ( (data[0].missing != -1) && (data[0].qvalue < 42)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
      if ( (data[6].missing != -1) && (data[6].qvalue < 40)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += (float)0.38648205996f;
            } else {
              sum += (float)0.078392535448f;
            }
          } else {
            sum += (float)0.3943272233f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
            sum += (float)0.37208896875f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
              sum += (float)-0.2263302356f;
            } else {
              sum += (float)0.25155478716f;
            }
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 16)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            sum += (float)0.39896506071f;
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 64)) {
              sum += (float)0.37835210562f;
            } else {
              sum += (float)0.10086980462f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
              sum += (float)-0.39725348353f;
            } else {
              sum += (float)-0.025969943032f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 34)) {
              sum += (float)0.21989794075f;
            } else {
              sum += (float)-0.13543401659f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          sum += (float)0.4029251039f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 86)) {
              sum += (float)0.31387421489f;
            } else {
              sum += (float)0.028298361227f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
              sum += (float)0.38610467315f;
            } else {
              sum += (float)0.046541187912f;
            }
          }
        }
      } else {
        if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 116)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
              sum += (float)0.35375884175f;
            } else {
              sum += (float)0.1330935061f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += (float)0.30898725986f;
            } else {
              sum += (float)-0.24371473491f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 138)) {
              sum += (float)0.37740710378f;
            } else {
              sum += (float)0.14695549011f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += (float)-0.03976899758f;
            } else {
              sum += (float)0.24325487018f;
            }
          }
        }
      }
    }
  } else {
    if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
      if ( (data[2].missing != -1) && (data[2].qvalue < 26)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 2)) {
              sum += (float)0.25880202651f;
            } else {
              sum += (float)-0.20191180706f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += (float)-0.11606223881f;
            } else {
              sum += (float)0.3440926075f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 56)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
              sum += (float)-0.18716320395f;
            } else {
              sum += (float)0.37713050842f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 12)) {
              sum += (float)-0.1472376436f;
            } else {
              sum += (float)-0.3783826828f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 92)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
            sum += (float)0.39143308997f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += (float)0.24193425477f;
            } else {
              sum += (float)-0.19197355211f;
            }
          }
        } else {
          sum += (float)-0.19736996293f;
        }
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 42)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          if ( (data[6].missing != -1) && (data[6].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += (float)0.14770740271f;
            } else {
              sum += (float)0.4352620542f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 20)) {
              sum += (float)0.25235307217f;
            } else {
              sum += (float)-0.020827565342f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 94)) {
              sum += (float)0.39714339375f;
            } else {
              sum += (float)0.086716480553f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 48)) {
              sum += (float)0.37348857522f;
            } else {
              sum += (float)-0.16664600372f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 130)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += (float)0.050075117499f;
            } else {
              sum += (float)0.32517540455f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 14)) {
              sum += (float)0.32030081749f;
            } else {
              sum += (float)-0.21575583518f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
              sum += (float)-0.14246527851f;
            } else {
              sum += (float)-0.33155086637f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += (float)0.34011739492f;
            } else {
              sum += (float)-0.046120863408f;
            }
          }
        }
      }
    }
  }
  if ( (data[0].missing != -1) && (data[0].qvalue < 50)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
          sum += (float)0.38068023324f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
            sum += (float)0.29575920105f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += (float)0.27367651463f;
            } else {
              sum += (float)-0.33058923483f;
            }
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 38)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += (float)0.15301576257f;
            } else {
              sum += (float)-0.22388879955f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 8)) {
              sum += (float)0.31366088986f;
            } else {
              sum += (float)-0.21975328028f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
              sum += (float)0.33829718828f;
            } else {
              sum += (float)0.16698619723f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += (float)0.24389268458f;
            } else {
              sum += (float)-0.2307421416f;
            }
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          sum += (float)0.36817330122f;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 22)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
              sum += (float)0.26934126019f;
            } else {
              sum += (float)0.021061837673f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += (float)0.35056263208f;
            } else {
              sum += (float)0.14126165211f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 32)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 12)) {
              sum += (float)0.28168594837f;
            } else {
              sum += (float)-0.07808444649f;
            }
          } else {
            if ( (data[1].missing != -1) && (data[1].qvalue < 16)) {
              sum += (float)0.073338389397f;
            } else {
              sum += (float)0.36468815804f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += (float)0.32442235947f;
            } else {
              sum += (float)-0.031936913729f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += (float)-0.15247604251f;
            } else {
              sum += (float)0.25715890527f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 12)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += (float)-0.18663819134f;
            } else {
              sum += (float)0.18901918828f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
              sum += (float)-0.35380941629f;
            } else {
              sum += (float)-0.26419717073f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 108)) {
            sum += (float)-0.073176980019f;
          } else {
            sum += (float)0.20741583407f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 106)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 30)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 54)) {
              sum += (float)-0.062548078597f;
            } else {
              sum += (float)0.35655921698f;
            }
          } else {
            if ( (data[6].missing != -1) && (data[6].qvalue < 94)) {
              sum += (float)-0.29174497724f;
            } else {
              sum += (float)0.18926022947f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 98)) {
              sum += (float)0.313490659f;
            } else {
              sum += (float)-0.12489058822f;
            }
          } else {
            sum += (float)0.61102384329f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 52)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += (float)-0.21818076074f;
            } else {
              sum += (float)0.25898611546f;
            }
          } else {
            sum += (float)0.37096396089f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
              sum += (float)0.036236476153f;
            } else {
              sum += (float)0.34651863575f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
              sum += (float)-0.025972818956f;
            } else {
              sum += (float)0.32510489225f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
          sum += (float)0.3160302043f;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
              sum += (float)-0.28940486908f;
            } else {
              sum += (float)0.28102505207f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
              sum += (float)0.10956378281f;
            } else {
              sum += (float)-0.22911226749f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
    if ( (data[2].missing != -1) && (data[2].qvalue < 20)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
          if ( (data[6].missing != -1) && (data[6].qvalue < 6)) {
            sum += (float)0.30370399356f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += (float)-0.20431482792f;
            } else {
              sum += (float)0.18569035828f;
            }
          }
        } else {
          sum += (float)0.33323317766f;
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 10)) {
          if ( (data[6].missing != -1) && (data[6].qvalue < 76)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 78)) {
              sum += (float)0.33252829313f;
            } else {
              sum += (float)-0.026735452935f;
            }
          } else {
            sum += (float)0.35046631098f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += (float)0.0012828422477f;
            } else {
              sum += (float)-0.33116221428f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
              sum += (float)0.069133356214f;
            } else {
              sum += (float)-0.10139513761f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          sum += (float)0.34718251228f;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 26)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += (float)0.33516719937f;
            } else {
              sum += (float)0.18734510243f;
            }
          } else {
            sum += (float)0.34502309561f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
          sum += (float)0.33847776055f;
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 44)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
              sum += (float)0.017179191113f;
            } else {
              sum += (float)0.33275908232f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
              sum += (float)-0.095487184823f;
            } else {
              sum += (float)0.27813062072f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 0)) {
            sum += (float)0.42686906457f;
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 18)) {
              sum += (float)0.27373796701f;
            } else {
              sum += (float)-0.15515017509f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += (float)0.44916456938f;
            } else {
              sum += (float)-0.14519783854f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 4)) {
              sum += (float)0.071637906134f;
            } else {
              sum += (float)-0.32140892744f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 40)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
              sum += (float)0.21197788417f;
            } else {
              sum += (float)0.45056757331f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
              sum += (float)0.12213995308f;
            } else {
              sum += (float)-0.10078366846f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += (float)0.30359113216f;
            } else {
              sum += (float)-0.030526047572f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
              sum += (float)-0.19480028749f;
            } else {
              sum += (float)-0.27791064978f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 110)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
              sum += (float)0.31575551629f;
            } else {
              sum += (float)-0.0084207383916f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 4)) {
              sum += (float)0.27326571941f;
            } else {
              sum += (float)-0.077761948109f;
            }
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 42)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += (float)0.012529964559f;
            } else {
              sum += (float)0.37125551701f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
              sum += (float)-0.06112068519f;
            } else {
              sum += (float)0.3549541831f;
            }
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
          sum += (float)0.31137433648f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
              sum += (float)-0.30869433284f;
            } else {
              sum += (float)0.085457131267f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
              sum += (float)0.048266679049f;
            } else {
              sum += (float)-0.26582977176f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
      if ( (data[3].missing != -1) && (data[3].qvalue < 26)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
          sum += (float)0.33440777659f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 12)) {
              sum += (float)0.045582074672f;
            } else {
              sum += (float)0.30255806446f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)0.26324960589f;
            } else {
              sum += (float)-0.13697682321f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 24)) {
              sum += (float)0.29042753577f;
            } else {
              sum += (float)-0.036559399217f;
            }
          } else {
            if ( (data[3].missing != -1) && (data[3].qvalue < 58)) {
              sum += (float)0.14269566536f;
            } else {
              sum += (float)0.26066446304f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 10)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += (float)0.011092330329f;
            } else {
              sum += (float)0.28458800912f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += (float)0.11302680522f;
            } else {
              sum += (float)-0.1625225991f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
        sum += (float)0.32869926095f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            sum += (float)0.039141312242f;
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 48)) {
              sum += (float)0.31535214186f;
            } else {
              sum += (float)0.072151474655f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 42)) {
              sum += (float)0.32022902369f;
            } else {
              sum += (float)0.039247419685f;
            }
          } else {
            if ( (data[1].missing != -1) && (data[1].qvalue < 30)) {
              sum += (float)0.22601722181f;
            } else {
              sum += (float)-0.1000591293f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
      if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 8)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += (float)0.26907390356f;
            } else {
              sum += (float)-0.22530952096f;
            }
          } else {
            sum += (float)0.43680885434f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 6)) {
              sum += (float)-0.30425879359f;
            } else {
              sum += (float)-0.19030535221f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 108)) {
              sum += (float)-0.13948993385f;
            } else {
              sum += (float)0.35109233856f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            sum += (float)0.070072688162f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
              sum += (float)0.27750921249f;
            } else {
              sum += (float)0.40996190906f;
            }
          }
        } else {
          if ( (data[6].missing != -1) && (data[6].qvalue < 88)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += (float)-0.081591084599f;
            } else {
              sum += (float)0.14726053178f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 108)) {
              sum += (float)0.39323073626f;
            } else {
              sum += (float)0.057459570467f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += (float)-0.056983545423f;
            } else {
              sum += (float)0.22396287322f;
            }
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 92)) {
              sum += (float)-0.105607301f;
            } else {
              sum += (float)-0.24866439402f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 48)) {
            sum += (float)0.33328676224f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
              sum += (float)-0.02307835035f;
            } else {
              sum += (float)0.23818406463f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 2)) {
              sum += (float)0.13812769949f;
            } else {
              sum += (float)-0.31330960989f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 16)) {
              sum += (float)-0.26102459431f;
            } else {
              sum += (float)0.38060507178f;
            }
          }
        } else {
          if ( (data[6].missing != -1) && (data[6].qvalue < 22)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += (float)-0.044097095728f;
            } else {
              sum += (float)0.39578178525f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += (float)0.069717608392f;
            } else {
              sum += (float)-0.1802611202f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
      sum += (float)0.32152307034f;
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
              sum += (float)-0.12138616294f;
            } else {
              sum += (float)0.23758517206f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += (float)0.33792433143f;
            } else {
              sum += (float)0.17069940269f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 10)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 0)) {
              sum += (float)0.31108391285f;
            } else {
              sum += (float)0.13328482211f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
              sum += (float)-0.10366888344f;
            } else {
              sum += (float)0.089874900877f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 46)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += (float)0.31767976284f;
            } else {
              sum += (float)0.035728875548f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 48)) {
              sum += (float)-0.22683919966f;
            } else {
              sum += (float)0.26656886935f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 44)) {
            sum += (float)0.29588860273f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += (float)-0.30164149404f;
            } else {
              sum += (float)0.13251824677f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 72)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
          sum += (float)0.35545238853f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 112)) {
              sum += (float)-0.17097947001f;
            } else {
              sum += (float)0.20608626306f;
            }
          } else {
            sum += (float)0.18466231227f;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 8)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 118)) {
              sum += (float)0.010760786943f;
            } else {
              sum += (float)0.44246545434f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += (float)-0.30363625288f;
            } else {
              sum += (float)0.063182063401f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
              sum += (float)-0.26688182354f;
            } else {
              sum += (float)-0.31540000439f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += (float)-0.20149099827f;
            } else {
              sum += (float)0.29733857512f;
            }
          }
        }
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 64)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 50)) {
              sum += (float)0.069787554443f;
            } else {
              sum += (float)0.33353585005f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
              sum += (float)-0.05904847756f;
            } else {
              sum += (float)0.36886823177f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 16)) {
              sum += (float)0.030128702521f;
            } else {
              sum += (float)0.33765229583f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += (float)0.03936399892f;
            } else {
              sum += (float)0.24945521355f;
            }
          }
        }
      } else {
        if ( (data[6].missing != -1) && (data[6].qvalue < 18)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += (float)0.052700240165f;
            } else {
              sum += (float)0.29115602374f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              sum += (float)-0.29400074482f;
            } else {
              sum += (float)0.068300105631f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
              sum += (float)-0.13832518458f;
            } else {
              sum += (float)-0.23255854845f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 86)) {
              sum += (float)0.090445563197f;
            } else {
              sum += (float)-0.24851720035f;
            }
          }
        }
      }
    }
  }
  if ( (data[0].missing != -1) && (data[0].qvalue < 34)) {
    if ( (data[3].missing != -1) && (data[3].qvalue < 26)) {
      sum += (float)0.31308200955f;
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 96)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += (float)0.12485051155f;
            } else {
              sum += (float)0.32913404703f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
              sum += (float)0.21118010581f;
            } else {
              sum += (float)0.022851839662f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 8)) {
              sum += (float)0.26170885563f;
            } else {
              sum += (float)-0.1801212728f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)0.27982950211f;
            } else {
              sum += (float)0.026429472491f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
          sum += (float)0.30781894922f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
            sum += (float)0.26718392968f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += (float)-0.32664179802f;
            } else {
              sum += (float)0.23652084172f;
            }
          }
        }
      }
    }
  } else {
    if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
          sum += (float)0.37617403269f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
            sum += (float)0.39496251941f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
              sum += (float)-0.22533540428f;
            } else {
              sum += (float)-0.033993601799f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
            sum += (float)0.27950555086f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += (float)0.19595517218f;
            } else {
              sum += (float)-0.18070921302f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 34)) {
              sum += (float)-0.2454393059f;
            } else {
              sum += (float)0.1420891732f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
              sum += (float)-0.28700196743f;
            } else {
              sum += (float)-0.15334679186f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
        if ( (data[6].missing != -1) && (data[6].qvalue < 20)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
              sum += (float)0.043485056609f;
            } else {
              sum += (float)0.30909645557f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += (float)-0.13509061933f;
            } else {
              sum += (float)0.1892708391f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += (float)-0.045419864357f;
            } else {
              sum += (float)0.25356343389f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 104)) {
              sum += (float)0.40240347385f;
            } else {
              sum += (float)0.092252023518f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 14)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 0)) {
              sum += (float)0.27303746343f;
            } else {
              sum += (float)-0.16851782799f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
              sum += (float)0.29901990294f;
            } else {
              sum += (float)-0.097181342542f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
            if ( (data[3].missing != -1) && (data[3].qvalue < 62)) {
              sum += (float)-0.1300508678f;
            } else {
              sum += (float)0.14077372849f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
              sum += (float)-0.22899605334f;
            } else {
              sum += (float)0.1858022064f;
            }
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 20)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 104)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 80)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 4)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += (float)0.14208568633f;
            } else {
              sum += (float)-0.29567366838f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 70)) {
              sum += (float)0.17528794706f;
            } else {
              sum += (float)-0.055076237768f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 88)) {
              sum += (float)-0.13459633291f;
            } else {
              sum += (float)-0.24899888039f;
            }
          } else {
            sum += (float)0.30796915293f;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 14)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 80)) {
              sum += (float)-0.061066582799f;
            } else {
              sum += (float)0.24206854403f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
              sum += (float)-0.29608973861f;
            } else {
              sum += (float)-0.032644949853f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 4)) {
            sum += (float)0.27241048217f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += (float)-0.27694433928f;
            } else {
              sum += (float)0.1599676311f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        if ( (data[1].missing != -1) && (data[1].qvalue < 32)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 6)) {
              sum += (float)0.28104227781f;
            } else {
              sum += (float)-0.10260210931f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
              sum += (float)-0.089923582971f;
            } else {
              sum += (float)0.41350111365f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
            sum += (float)0.31383183599f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += (float)0.037621688098f;
            } else {
              sum += (float)0.28289362788f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += (float)0.17461740971f;
            } else {
              sum += (float)0.40709623694f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += (float)0.26048535109f;
            } else {
              sum += (float)0.036739677191f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 100)) {
              sum += (float)0.029906807467f;
            } else {
              sum += (float)-0.35227930546f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += (float)-0.17938053608f;
            } else {
              sum += (float)0.2820148766f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
      sum += (float)0.3094510138f;
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
              sum += (float)-0.04214566946f;
            } else {
              sum += (float)0.30979454517f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
              sum += (float)0.026081673801f;
            } else {
              sum += (float)0.26289364696f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 64)) {
              sum += (float)0.030223727226f;
            } else {
              sum += (float)0.24173893034f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += (float)0.13179793954f;
            } else {
              sum += (float)-0.19092197716f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)0.28511112928f;
            } else {
              sum += (float)0.12484978139f;
            }
          } else {
            sum += (float)0.30696302652f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
            sum += (float)0.25627958775f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
              sum += (float)0.021061874926f;
            } else {
              sum += (float)-0.28292346001f;
            }
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 22)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if ( (data[2].missing != -1) && (data[2].qvalue < 2)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 80)) {
            sum += (float)0.19333575666f;
          } else {
            sum += (float)-0.20944240689f;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 108)) {
            sum += (float)0.89051347971f;
          } else {
            sum += (float)-0.075020261109f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
          if ( (data[6].missing != -1) && (data[6].qvalue < 2)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += (float)-0.1977250874f;
            } else {
              sum += (float)0.37797427177f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 66)) {
              sum += (float)-0.056323695928f;
            } else {
              sum += (float)-0.27100723982f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
              sum += (float)-0.092633284628f;
            } else {
              sum += (float)-0.28103742003f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
              sum += (float)0.37986525893f;
            } else {
              sum += (float)-0.059424828738f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
          sum += (float)0.30468598008f;
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 28)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 68)) {
              sum += (float)-0.36622467637f;
            } else {
              sum += (float)-0.10684461892f;
            }
          } else {
            if ( (data[1].missing != -1) && (data[1].qvalue < 14)) {
              sum += (float)-0.06494500488f;
            } else {
              sum += (float)0.29783678055f;
            }
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 34)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
              sum += (float)0.059380035847f;
            } else {
              sum += (float)-0.13271890581f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 86)) {
              sum += (float)0.20633219182f;
            } else {
              sum += (float)-0.0074712117203f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
            sum += (float)0.28024509549f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += (float)0.095835484564f;
            } else {
              sum += (float)-0.037637911737f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
        sum += (float)0.30786806345f;
      } else {
        if ( (data[6].missing != -1) && (data[6].qvalue < 64)) {
          sum += (float)-0.19678905606f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += (float)0.20695413649f;
            } else {
              sum += (float)-0.12212411314f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 46)) {
              sum += (float)0.3035145402f;
            } else {
              sum += (float)0.13091221452f;
            }
          }
        }
      }
    } else {
      if ( (data[6].missing != -1) && (data[6].qvalue < 50)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
            sum += (float)-0.17966145277f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
              sum += (float)0.2718295455f;
            } else {
              sum += (float)-0.0077994153835f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
            sum += (float)0.26100420952f;
          } else {
            sum += (float)0.072317458689f;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 94)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 42)) {
              sum += (float)0.26616030931f;
            } else {
              sum += (float)-0.039413407445f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += (float)0.20135869086f;
            } else {
              sum += (float)-0.21231886744f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
              sum += (float)-0.08866520226f;
            } else {
              sum += (float)0.19998960197f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 102)) {
              sum += (float)0.39999696612f;
            } else {
              sum += (float)0.04584806785f;
            }
          }
        }
      }
    }
  }
  if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 68)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
        sum += (float)0.30661180615f;
      } else {
        if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
            sum += (float)-0.18783815205f;
          } else {
            sum += (float)0.20370395482f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 46)) {
              sum += (float)-0.19181600213f;
            } else {
              sum += (float)0.17475792766f;
            }
          } else {
            sum += (float)0.28632381558f;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 82)) {
        sum += (float)-0.034050989896f;
      } else {
        sum += (float)-0.17208853364f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 78)) {
        if ( (data[6].missing != -1) && (data[6].qvalue < 26)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            sum += (float)-0.010992488824f;
          } else {
            sum += (float)0.37022417784f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
              sum += (float)0.00021863629809f;
            } else {
              sum += (float)0.46551984549f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 106)) {
              sum += (float)-0.064779862761f;
            } else {
              sum += (float)-0.23606176674f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 0)) {
            if ( (data[0].missing != -1) && (data[0].qvalue < 90)) {
              sum += (float)0.29889300466f;
            } else {
              sum += (float)-0.18387538195f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
              sum += (float)-0.29288694263f;
            } else {
              sum += (float)-0.21912488341f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += (float)-0.27206158638f;
            } else {
              sum += (float)-0.051553491503f;
            }
          } else {
            sum += (float)0.53196084499f;
          }
        }
      }
    } else {
      if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 102)) {
              sum += (float)0.034897781909f;
            } else {
              sum += (float)-0.12338959426f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += (float)0.13413026929f;
            } else {
              sum += (float)0.38948994875f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 66)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)0.26088503003f;
            } else {
              sum += (float)-0.048945810646f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
              sum += (float)0.25530821085f;
            } else {
              sum += (float)-0.16437289119f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += (float)0.14824573696f;
            } else {
              sum += (float)-0.11105206609f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.30104675889f;
            } else {
              sum += (float)0.14805816114f;
            }
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
              sum += (float)-0.31033420563f;
            } else {
              sum += (float)0.05820113793f;
            }
          } else {
            if ( (data[6].missing != -1) && (data[6].qvalue < 54)) {
              sum += (float)0.023083105683f;
            } else {
              sum += (float)0.27734109759f;
            }
          }
        }
      }
    }
  }
  if ( (data[3].missing != -1) && (data[3].qvalue < 16)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
        sum += (float)0.29955354333f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
          sum += (float)0.26554045081f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            sum += (float)-0.20469307899f;
          } else {
            sum += (float)0.089787617326f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += (float)0.20165520906f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
          sum += (float)-0.20261117816f;
        } else {
          sum += (float)0.043250620365f;
        }
      }
    }
  } else {
    if ( (data[1].missing != -1) && (data[1].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 52)) {
              sum += (float)-0.071515023708f;
            } else {
              sum += (float)0.31189399958f;
            }
          } else {
            sum += (float)-0.22002899647f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
              sum += (float)-0.090241581202f;
            } else {
              sum += (float)-0.28840315342f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 100)) {
              sum += (float)0.03873507306f;
            } else {
              sum += (float)-0.23399293423f;
            }
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 114)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 10)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 72)) {
              sum += (float)0.36697202921f;
            } else {
              sum += (float)0.023225884885f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += (float)-0.20338559151f;
            } else {
              sum += (float)0.17890807986f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
              sum += (float)0.35343390703f;
            } else {
              sum += (float)-0.16952513158f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
              sum += (float)0.017891913652f;
            } else {
              sum += (float)-0.26227030158f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if ( (data[6].missing != -1) && (data[6].qvalue < 24)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
              sum += (float)0.3470595777f;
            } else {
              sum += (float)0.13278026879f;
            }
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 36)) {
              sum += (float)0.3325368762f;
            } else {
              sum += (float)0.00017361338541f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
              sum += (float)0.13380682468f;
            } else {
              sum += (float)-0.13799647987f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.28674203157f;
            } else {
              sum += (float)0.13543896377f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 54)) {
              sum += (float)0.07286670059f;
            } else {
              sum += (float)-0.060891315341f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
              sum += (float)0.16949248314f;
            } else {
              sum += (float)-0.19845589995f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 16)) {
            if ( (data[4].missing != -1) && (data[4].qvalue < 66)) {
              sum += (float)-0.00070150766987f;
            } else {
              sum += (float)0.24696482718f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
              sum += (float)-0.12644982338f;
            } else {
              sum += (float)0.3987454474f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
        sum += (float)0.30162510276f;
      } else {
        if ( (data[6].missing != -1) && (data[6].qvalue < 62)) {
          sum += (float)0.01284371689f;
        } else {
          sum += (float)0.16660647094f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
            sum += (float)0.064288727939f;
          } else {
            sum += (float)0.30674418807f;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 98)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += (float)-0.076444767416f;
            } else {
              sum += (float)0.10855161399f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += (float)0.26124703884f;
            } else {
              sum += (float)-0.049595355988f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 46)) {
          sum += (float)0.28516307473f;
        } else {
          sum += (float)0.059804927558f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 104)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 118)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 22)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
              sum += (float)-0.1766320169f;
            } else {
              sum += (float)0.13012625277f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += (float)0.31332802773f;
            } else {
              sum += (float)0.11867714673f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
              sum += (float)0.13492467999f;
            } else {
              sum += (float)-0.043303981423f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
              sum += (float)-0.22831825912f;
            } else {
              sum += (float)0.1123720184f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += (float)0.25340011716f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
            if ( (data[5].missing != -1) && (data[5].qvalue < 14)) {
              sum += (float)0.10374542326f;
            } else {
              sum += (float)-0.15581353009f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
              sum += (float)0.15549130738f;
            } else {
              sum += (float)-0.091738499701f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
            sum += (float)-0.12868969142f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
              sum += (float)-0.063997872174f;
            } else {
              sum += (float)0.26468420029f;
            }
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 16)) {
            sum += (float)-0.25840097666f;
          } else {
            sum += (float)0.099251404405f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 4)) {
            sum += (float)0.2423389703f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
              sum += (float)-0.25472736359f;
            } else {
              sum += (float)-0.12740445137f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 122)) {
              sum += (float)0.47093057632f;
            } else {
              sum += (float)-0.0060853515752f;
            }
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 16)) {
              sum += (float)-0.25340256095f;
            } else {
              sum += (float)0.11564949155f;
            }
          }
        }
      }
    }
  }
  if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
    sum += (float)0.29719600081f;
  } else {
    if ( (data[0].missing != -1) && (data[0].qvalue < 96)) {
      if ( (data[2].missing != -1) && (data[2].qvalue < 28)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 2)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += (float)0.12393690646f;
            } else {
              sum += (float)0.44715672731f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += (float)0.036586564034f;
            } else {
              sum += (float)-0.056832425296f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += (float)0.29135939479f;
            } else {
              sum += (float)0.09721660614f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
              sum += (float)0.038457658142f;
            } else {
              sum += (float)-0.37050047517f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 44)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
            sum += (float)0.28378924727f;
          } else {
            if ( (data[5].missing != -1) && (data[5].qvalue < 80)) {
              sum += (float)-0.071109250188f;
            } else {
              sum += (float)0.25522091985f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            sum += (float)-0.10514407605f;
          } else {
            sum += (float)0.18092963099f;
          }
        }
      }
    } else {
      if ( (data[4].missing != -1) && (data[4].qvalue < 78)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
            if ( (data[6].missing != -1) && (data[6].qvalue < 82)) {
              sum += (float)-0.063867866993f;
            } else {
              sum += (float)0.33381947875f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += (float)0.092415809631f;
            } else {
              sum += (float)-0.1786198169f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
              sum += (float)0.39806041121f;
            } else {
              sum += (float)0.13987541199f;
            }
          } else {
            sum += (float)0.045697566122f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 104)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
              sum += (float)0.19768968225f;
            } else {
              sum += (float)-0.26730498672f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += (float)-0.27041172981f;
            } else {
              sum += (float)-0.039175584912f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 112)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += (float)-0.11200495809f;
            } else {
              sum += (float)0.45523002744f;
            }
          } else {
            sum += (float)-0.26315686107f;
          }
        }
      }
    }
  }
  if ( (data[3].missing != -1) && (data[3].qvalue < 4)) {
    if ( (data[2].missing != -1) && (data[2].qvalue < 14)) {
      sum += (float)0.070075578988f;
    } else {
      sum += (float)0.29677549005f;
    }
  } else {
    if ( (data[1].missing != -1) && (data[1].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 110)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
              sum += (float)-0.053049318492f;
            } else {
              sum += (float)0.34112691879f;
            }
          } else {
            sum += (float)-0.1471259743f;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 64)) {
            sum += (float)-0.061926808208f;
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 74)) {
              sum += (float)-0.16626268625f;
            } else {
              sum += (float)-0.29234683514f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 120)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
            if ( (data[2].missing != -1) && (data[2].qvalue < 4)) {
              sum += (float)0.17944897711f;
            } else {
              sum += (float)-0.086707547307f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += (float)0.025518519804f;
            } else {
              sum += (float)0.44480350614f;
            }
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
            sum += (float)0.080325007439f;
          } else {
            if ( (data[2].missing != -1) && (data[2].qvalue < 2)) {
              sum += (float)0.037706382573f;
            } else {
              sum += (float)-0.27602234483f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 4)) {
            sum += (float)0.28777065873f;
          } else {
            if ( (data[4].missing != -1) && (data[4].qvalue < 122)) {
              sum += (float)-0.00048094708472f;
            } else {
              sum += (float)-0.074303127825f;
            }
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 40)) {
            sum += (float)-0.002888975665f;
          } else {
            sum += (float)0.32622426748f;
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 26)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 44)) {
            sum += (float)0.2596244216f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
              sum += (float)0.23252667487f;
            } else {
              sum += (float)-0.20675693452f;
            }
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 36)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.20035776496f;
            } else {
              sum += (float)-0.080339387059f;
            }
          } else {
            if ( (data[0].missing != -1) && (data[0].qvalue < 76)) {
              sum += (float)0.05283723399f;
            } else {
              sum += (float)-0.16003388166f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}
