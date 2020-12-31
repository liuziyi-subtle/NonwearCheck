#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  50, 30, 13, 166, 28, 32, 45, 95, 74, 53, 
};
static const int th_begin[] = {
  0, 50, 80, 93, 259, 287, 319, 364, 459, 533, 
};
static const float threshold[] = {
  1.0133762f, 1.3857973f, 1.4269438f, 1.4819334f, 1.4831469f, 1.7455714f, 1.8719811f, 
  1.9040995f, 1.9985417f, 2.0501423f, 2.0724814f, 2.7220669f, 2.7612932f, 2.8236852f, 
  2.8961425f, 3.534771f, 3.6537354f, 3.8416142f, 4.1242771f, 4.3392076f, 4.4799981f, 
  5.2143683f, 5.256906f, 6.0529432f, 6.0734386f, 6.3864751f, 6.4018564f, 6.6726718f, 
  6.7193065f, 6.7556982f, 6.9504814f, 7.0894871f, 7.2389922f, 7.4374428f, 7.4496298f, 
  7.6566401f, 7.7818065f, 7.7833424f, 9.0385056f, 10.116214f, 10.598005f, 10.59855f, 
  13.429989f, 14.150509f, 14.188652f, 14.916195f, 14.982363f, 14.990356f, 16.556215f, 
  16.663128f, 11.5f, 15.5f, 16.5f, 17.5f, 18.5f, 19.5f, 20.5f, 21.5f, 22.5f, 23.5f, 24.5f, 
  25.5f, 26.0f, 26.5f, 27.5f, 28.5f, 29.5f, 30.5f, 33.5f, 34.5f, 35.5f, 36.5f, 38.0f, 39.5f, 
  40.5f, 41.5f, 43.5f, 44.5f, 45.5f, 46.5f, 4.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 
  12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 38223.664f, 38427.918f, 38436.25f, 
  38444.836f, 38476.168f, 38519.336f, 38629.75f, 38744.414f, 39266.5f, 39572.664f, 
  39601.586f, 39696.0f, 39820.086f, 40030.914f, 40054.918f, 40102.25f, 40110.668f, 
  40190.664f, 40291.25f, 40512.914f, 40542.75f, 40573.5f, 40581.086f, 40638.664f, 
  40662.164f, 40705.086f, 42004.164f, 42110.164f, 42144.586f, 42193.75f, 42315.836f, 
  42338.5f, 42342.332f, 42347.336f, 42378.168f, 42378.914f, 42386.664f, 42593.5f, 
  42597.25f, 42890.5f, 42909.164f, 42919.25f, 42928.418f, 42960.5f, 42962.664f, 
  42965.086f, 42967.75f, 42973.0f, 42978.414f, 42983.5f, 42999.414f, 43020.25f, 
  43032.082f, 43089.164f, 43121.086f, 43130.25f, 43142.664f, 43579.086f, 43811.168f, 
  43988.418f, 46165.5f, 46168.75f, 46674.668f, 46675.836f, 48385.5f, 48412.75f, 
  48488.336f, 48488.75f, 48506.836f, 48536.25f, 48538.914f, 48869.164f, 48926.914f, 
  49033.75f, 49077.914f, 49091.5f, 49114.75f, 49174.25f, 49175.75f, 49211.25f, 
  49315.414f, 49367.0f, 49380.0f, 50361.5f, 50829.914f, 51040.832f, 51041.25f, 51158.664f, 
  51237.336f, 51257.25f, 52218.332f, 52374.418f, 52425.668f, 52494.336f, 52509.5f, 
  52705.836f, 52979.75f, 52986.5f, 53032.332f, 53041.164f, 53226.086f, 53459.414f, 
  53522.918f, 53681.164f, 53982.586f, 54153.336f, 54658.414f, 54777.414f, 54936.0f, 
  54944.664f, 54989.75f, 55006.5f, 55034.164f, 55215.914f, 55228.0f, 55247.75f, 
  55252.75f, 55438.582f, 55463.5f, 55467.582f, 55469.75f, 55471.414f, 55571.336f, 
  55693.168f, 55739.25f, 56156.914f, 56221.664f, 56575.086f, 56884.168f, 57010.668f, 
  57109.664f, 57171.586f, 57387.086f, 57434.164f, 57512.0f, 57609.75f, 57618.75f, 
  57715.414f, 57858.164f, 57858.75f, 57860.25f, 57863.75f, 57867.664f, 57869.25f, 
  57892.582f, 57904.0f, 57907.5f, 57908.332f, 58053.0f, 58080.668f, 58106.25f, 58213.082f, 
  58371.25f, 58422.418f, 58427.0f, 58589.164f, 58975.086f, 59092.086f, 59649.5f, 
  59799.918f, 60107.836f, 61624.164f, 61638.75f, 63247.75f, 63564.582f, 64980.75f, 
  0.08203125f, 0.09765625f, 0.13671875f, 0.48828125f, 0.5390625f, 0.56640625f, 
  0.57421875f, 0.58203125f, 0.58984375f, 0.61328125f, 0.62109375f, 0.62890625f, 
  0.64453125f, 0.65625f, 0.66015625f, 0.68359375f, 0.73828125f, 0.75390625f, 
  0.76171875f, 0.76953125f, 0.78515625f, 0.80078125f, 0.81640625f, 0.83984375f, 
  0.84375f, 0.87109375f, 0.87890625f, 0.91015625f, -0.48442966f, -0.10097416f, 
  8.0514263e-05f, 0.12402178f, 0.34150475f, 0.41337216f, 0.41340184f, 0.41567713f, 
  0.43360233f, 0.47131458f, 0.56734669f, 0.58185899f, 0.62864703f, 0.70401257f, 
  0.70973194f, 0.71608543f, 0.76401591f, 0.7661218f, 0.81129378f, 0.82867074f, 
  0.87512326f, 0.89075083f, 0.90350568f, 0.90580904f, 0.9149735f, 0.93217611f, 
  0.933599f, 0.93582463f, 0.95368659f, 0.95442021f, 0.97933555f, 0.98412246f, 
  0.026881585f, 0.06037489f, 0.17098659f, 0.2994284f, 0.32727331f, 0.3292231f, 
  0.34817049f, 0.3598029f, 0.3618004f, 0.38221502f, 0.39393532f, 0.42228758f, 
  0.42952609f, 0.47350454f, 0.49330762f, 0.51276547f, 0.5707078f, 0.57873166f, 
  0.59175217f, 0.60564721f, 0.61664677f, 0.62923443f, 0.65276605f, 0.65633094f, 
  0.65828425f, 0.67313194f, 0.67759407f, 0.67857659f, 0.67932439f, 0.6816659f, 
  0.69496322f, 0.70433736f, 0.70769101f, 0.72092324f, 0.73229623f, 0.73983908f, 
  0.74634176f, 0.77473974f, 0.79429287f, 0.82564437f, 0.83258814f, 0.8661983f, 
  0.88233954f, 0.89323485f, 0.93844271f, 0.52452803f, 0.61206067f, 0.69835722f, 
  0.69891709f, 0.69988704f, 0.87344176f, 0.88730133f, 0.91340744f, 1.0746858f, 
  1.1182585f, 1.1207601f, 1.1240551f, 1.1762288f, 1.1987727f, 1.208467f, 1.2641263f, 
  1.267345f, 1.343154f, 1.3460705f, 1.4159675f, 1.4215848f, 1.4239693f, 1.4241045f, 
  1.4481304f, 1.45837f, 1.5356817f, 1.5622704f, 1.5646319f, 1.5658594f, 1.5765674f, 
  1.5831909f, 1.5856602f, 1.6029475f, 1.6077334f, 1.6132669f, 1.6493546f, 1.7289193f, 
  1.7298434f, 1.7331947f, 1.7358749f, 1.7444521f, 1.7490606f, 1.7499223f, 1.7660329f, 
  1.7915938f, 1.7962813f, 1.8165548f, 1.8193693f, 1.8199024f, 1.8420799f, 1.8425919f, 
  1.8438309f, 1.8606105f, 1.8702013f, 1.8710251f, 1.8713291f, 1.8721454f, 1.8736832f, 
  1.8851622f, 1.8858354f, 1.889482f, 1.8954086f, 1.8960409f, 1.9224164f, 1.927876f, 
  1.9281662f, 1.9395951f, 1.9412969f, 1.9415832f, 1.9481568f, 1.9499364f, 1.9552248f, 
  1.9751372f, 1.980921f, 1.9834358f, 2.0074396f, 2.0094342f, 2.0124784f, 2.0222645f, 
  2.0241079f, 2.0382149f, 2.0466995f, 2.0520449f, 2.0538778f, 2.0649133f, 2.0700319f, 
  2.0990455f, 2.1101437f, 2.1166947f, 2.1173041f, 2.137228f, 2.1698403f, 2.1790295f, 
  2.2240114f, 2.237201f, 0.92118788f, 1.1207027f, 1.1438389f, 1.1494443f, 1.2544897f, 
  1.3902445f, 1.4174745f, 1.4814873f, 1.531518f, 1.5581944f, 1.5599304f, 1.575822f, 
  1.6655328f, 1.755f, 1.8525789f, 2.0260885f, 2.1210494f, 2.1729412f, 2.1757691f, 
  2.218533f, 2.5057392f, 2.7748542f, 3.16992f, 3.1935287f, 3.5433674f, 4.0550532f, 
  4.9191332f, 5.2445745f, 5.2526388f, 5.3596878f, 5.3738775f, 5.7931366f, 5.8343191f, 
  7.2542439f, 7.3427587f, 7.4773722f, 7.6437287f, 7.6471052f, 7.7297506f, 9.2592831f, 
  9.5952206f, 10.846271f, 11.594856f, 11.951736f, 12.588888f, 12.626787f, 14.053047f, 
  16.371529f, 18.243557f, 18.297127f, 19.849491f, 21.697777f, 22.047527f, 25.585985f, 
  33.012756f, 39.409687f, 44.430161f, 44.46875f, 45.68998f, 46.98f, 55.696327f, 
  64.876419f, 69.893677f, 96.092896f, 101.54973f, 167.77431f, 292.73871f, 317.29428f, 
  415.02307f, 420.28278f, 462.02802f, 190833.16f, 195103.72f, 271457.53f, 0.08984375f, 
  0.11328125f, 0.16015625f, 0.2265625f, 0.27734375f, 0.28515625f, 0.2890625f, 
  0.32421875f, 0.33203125f, 0.34765625f, 0.3515625f, 0.37890625f, 0.41015625f, 
  0.41796875f, 0.42578125f, 0.43359375f, 0.44921875f, 0.48828125f, 0.51171875f, 
  0.52734375f, 0.56640625f, 0.58984375f, 0.6015625f, 0.63671875f, 0.64453125f, 
  0.66796875f, 0.67578125f, 0.69140625f, 0.70703125f, 0.72265625f, 0.73828125f, 
  0.74609375f, 0.75390625f, 0.76171875f, 0.78515625f, 0.79296875f, 0.80078125f, 
  0.80859375f, 0.81640625f, 0.82421875f, 0.83984375f, 0.85546875f, 0.86328125f, 
  0.87109375f, 0.87890625f, 0.88671875f, 0.89453125f, 0.91796875f, 0.94140625f, 
  0.94921875f, 0.95703125f, 0.96484375f, 0.97265625f, 
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
  if (offset == 586 || val < array[0]) {
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
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};


float PredictIr(union NonwearEntry* data) {

  for (int i = 0; i < 10; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            sum += (float)0.49565216899f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += (float)-0.32307696342f;
            } else {
              sum += (float)0.33333337307f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 288)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += (float)-0.22666667402f;
            } else {
              sum += (float)-0.54339623451f;
            }
          } else {
            sum += (float)0.20000001788f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 148)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += (float)0.52941179276f;
            } else {
              sum += (float)0.30000001192f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 104)) {
              sum += (float)-0.27804878354f;
            } else {
              sum += (float)0.40800002217f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
              sum += (float)-.0f;
            } else {
              sum += (float)0.30000001192f;
            }
          } else {
            sum += (float)0.57530868053f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
        sum += (float)0.57391309738f;
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 68)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              sum += (float)-0.44842106104f;
            } else {
              sum += (float)0.047482017428f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
              sum += (float)-0.37777778506f;
            } else {
              sum += (float)-0.56589502096f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
              sum += (float)-0.51978611946f;
            } else {
              sum += (float)0.44000002742f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
              sum += (float)-0.045783132315f;
            } else {
              sum += (float)0.49615386128f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 142)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 272)) {
              sum += (float)0.31200000644f;
            } else {
              sum += (float)-0.36923080683f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 54)) {
              sum += (float)-0.51724141836f;
            } else {
              sum += (float)-0.24705883861f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            sum += (float)0.57037043571f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += (float)-0.085714295506f;
            } else {
              sum += (float)0.40000003576f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)-0.15000000596f;
            } else {
              sum += (float)0.52542376518f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
              sum += (float)-0.30000001192f;
            } else {
              sum += (float)0.066666670144f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
            sum += (float)0.59318959713f;
          } else {
            sum += (float)0.15000000596f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += (float)0.49565216899f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)-0.54766356945f;
            } else {
              sum += (float)0.13846154511f;
            }
          } else {
            sum += (float)0.40000003576f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 92)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 180)) {
            sum += (float)-0.054545458406f;
          } else {
            sum += (float)0.27272728086f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
            sum += (float)0.15000000596f;
          } else {
            sum += (float)0.54782611132f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
            sum += (float)0.38145047426f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += (float)-0.3285921514f;
            } else {
              sum += (float)0.21072563529f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += (float)-0.42796519399f;
            } else {
              sum += (float)-0.044163879007f;
            }
          } else {
            sum += (float)0.13839039207f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
              sum += (float)0.094490900636f;
            } else {
              sum += (float)0.42560124397f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 158)) {
              sum += (float)0.16448009014f;
            } else {
              sum += (float)-0.28367471695f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 186)) {
            sum += (float)0.43233910203f;
          } else {
            sum += (float)0.13181173801f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
        sum += (float)0.44054171443f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 80)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
              sum += (float)-0.33508783579f;
            } else {
              sum += (float)-0.43886774778f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += (float)-0.3833090663f;
            } else {
              sum += (float)0.17529965937f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
              sum += (float)0.15858179331f;
            } else {
              sum += (float)-0.37335035205f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += (float)-0.29848018289f;
            } else {
              sum += (float)0.4463429451f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 62)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 262)) {
              sum += (float)0.3805449605f;
            } else {
              sum += (float)-0.17631575465f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += (float)0.090284027159f;
            } else {
              sum += (float)-0.38175961375f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 166)) {
              sum += (float)0.44234496355f;
            } else {
              sum += (float)0.1273342669f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.38622406125f;
            } else {
              sum += (float)-0.12751117349f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)-0.043966073543f;
            } else {
              sum += (float)0.42626214027f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += (float)-0.04455191642f;
            } else {
              sum += (float)0.27627429366f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
            sum += (float)0.46142607927f;
          } else {
            sum += (float)0.14339630306f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += (float)0.40661433339f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 56)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)-0.40757057071f;
            } else {
              sum += (float)0.11011419445f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += (float)0.064682580531f;
            } else {
              sum += (float)0.32548210025f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 90)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
            sum += (float)0.2664937675f;
          } else {
            sum += (float)-0.10655981302f;
          }
        } else {
          sum += (float)0.42479851842f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 60)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += (float)-0.027664167807f;
          } else {
            sum += (float)-0.39668276906f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
              sum += (float)0.061390761286f;
            } else {
              sum += (float)0.36813461781f;
            }
          } else {
            sum += (float)0.71614176035f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += (float)0.028741041198f;
            } else {
              sum += (float)0.45728126168f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
              sum += (float)-0.30958545208f;
            } else {
              sum += (float)0.084119014442f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 230)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += (float)-0.3913551271f;
            } else {
              sum += (float)-0.27689445019f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
              sum += (float)-0.17981955409f;
            } else {
              sum += (float)-0.39728587866f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += (float)0.23556345701f;
            } else {
              sum += (float)-0.29539054632f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += (float)-0.15695235133f;
            } else {
              sum += (float)0.46741491556f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += (float)-0.40863281488f;
            } else {
              sum += (float)-0.06543391943f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
              sum += (float)0.11834177375f;
            } else {
              sum += (float)-0.31501507759f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 126)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += (float)-0.15220604837f;
            } else {
              sum += (float)0.37580442429f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
              sum += (float)0.32510226965f;
            } else {
              sum += (float)0.44805178046f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 94)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
              sum += (float)0.39385709167f;
            } else {
              sum += (float)-0.18208603561f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
              sum += (float)-0.1366186589f;
            } else {
              sum += (float)0.35356476903f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
            sum += (float)0.11391591281f;
          } else {
            sum += (float)0.39993530512f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 120)) {
              sum += (float)0.22273531556f;
            } else {
              sum += (float)-0.25544336438f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += (float)0.056615907699f;
            } else {
              sum += (float)0.36552938819f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 226)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.23978820443f;
            } else {
              sum += (float)-0.23185744882f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += (float)-0.43843394518f;
            } else {
              sum += (float)-0.10586383194f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += (float)0.38994604349f;
            } else {
              sum += (float)0.25430676341f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 56)) {
              sum += (float)-0.034492123872f;
            } else {
              sum += (float)0.3523862958f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += (float)0.33564814925f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)-0.3510633707f;
            } else {
              sum += (float)0.088030278683f;
            }
          } else {
            sum += (float)0.29772475362f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 50)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 46)) {
              sum += (float)0.33278551698f;
            } else {
              sum += (float)0.010863559321f;
            }
          } else {
            sum += (float)-0.20986768603f;
          }
        } else {
          sum += (float)0.38022130728f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 60)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 162)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += (float)0.29481160641f;
            } else {
              sum += (float)-0.28020036221f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += (float)-0.19248448312f;
            } else {
              sum += (float)0.53469961882f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += (float)-0.30854770541f;
            } else {
              sum += (float)0.40378856659f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
              sum += (float)-0.15643301606f;
            } else {
              sum += (float)0.50338858366f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
              sum += (float)0.12654276192f;
            } else {
              sum += (float)-0.35596713424f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
              sum += (float)-0.10707647353f;
            } else {
              sum += (float)0.45745313168f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 148)) {
              sum += (float)-0.28710541129f;
            } else {
              sum += (float)-0.35870432854f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += (float)-0.32784205675f;
            } else {
              sum += (float)-0.11582245678f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 134)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += (float)0.13859431446f;
            } else {
              sum += (float)-0.34191760421f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += (float)0.42247000337f;
            } else {
              sum += (float)0.00017521927657f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
            sum += (float)0.090498566628f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 194)) {
              sum += (float)-0.36199784279f;
            } else {
              sum += (float)-0.25556412339f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
              sum += (float)0.15914903581f;
            } else {
              sum += (float)-0.44973108172f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
              sum += (float)0.34692782164f;
            } else {
              sum += (float)0.15694998205f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 100)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
              sum += (float)-0.23873659968f;
            } else {
              sum += (float)0.043838277459f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
              sum += (float)0.037531860173f;
            } else {
              sum += (float)0.37981292605f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 46)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 250)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
              sum += (float)0.2478621155f;
            } else {
              sum += (float)-0.094149924815f;
            }
          } else {
            sum += (float)-0.33214756846f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
            sum += (float)0.024826889858f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
              sum += (float)0.086354523897f;
            } else {
              sum += (float)0.41748002172f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 94)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
              sum += (float)0.13100421429f;
            } else {
              sum += (float)-0.3331682384f;
            }
          } else {
            sum += (float)0.26434645057f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
            sum += (float)0.043665193021f;
          } else {
            sum += (float)0.31813192368f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          sum += (float)0.10934084654f;
        } else {
          sum += (float)0.36527776718f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 312)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 172)) {
              sum += (float)0.33583426476f;
            } else {
              sum += (float)0.041775800288f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += (float)-0.0032326334622f;
            } else {
              sum += (float)0.32839256525f;
            }
          }
        } else {
          sum += (float)-0.42842537165f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 82)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 158)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += (float)-0.18628913164f;
            } else {
              sum += (float)0.32839912176f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 144)) {
              sum += (float)-0.3244510591f;
            } else {
              sum += (float)0.27204295993f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += (float)0.061510819942f;
            } else {
              sum += (float)-0.31474113464f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
              sum += (float)0.27471292019f;
            } else {
              sum += (float)-0.12863007188f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
          sum += (float)0.2883054018f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
              sum += (float)-0.035454448313f;
            } else {
              sum += (float)-0.33953535557f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
              sum += (float)-0.30714166164f;
            } else {
              sum += (float)-0.19538164139f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            sum += (float)-0.010078351945f;
          } else {
            sum += (float)0.30382299423f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += (float)0.047444425523f;
            } else {
              sum += (float)-0.32084834576f;
            }
          } else {
            sum += (float)0.069820605218f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 178)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
              sum += (float)-0.084654800594f;
            } else {
              sum += (float)0.23440770805f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += (float)0.21654237807f;
            } else {
              sum += (float)0.40013003349f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 174)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
              sum += (float)0.10409548879f;
            } else {
              sum += (float)-0.45776364207f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += (float)0.36053824425f;
            } else {
              sum += (float)-0.085023649037f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
              sum += (float)0.18362398446f;
            } else {
              sum += (float)-0.25483807921f;
            }
          } else {
            sum += (float)0.40117257833f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += (float)0.083953857422f;
            } else {
              sum += (float)-0.33290719986f;
            }
          } else {
            sum += (float)0.23478342593f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
          sum += (float)0.31245115399f;
        } else {
          sum += (float)0.034991767257f;
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 70)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += (float)-0.33102801442f;
            } else {
              sum += (float)0.12625488639f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 48)) {
              sum += (float)0.34364560246f;
            } else {
              sum += (float)0.18254062533f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += (float)-0.45297569036f;
            } else {
              sum += (float)-0.096865102649f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
              sum += (float)0.33901655674f;
            } else {
              sum += (float)0.084842644632f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += (float)-0.13300070167f;
            } else {
              sum += (float)0.3121534884f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += (float)-0.13306158781f;
            } else {
              sum += (float)0.30284899473f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
            sum += (float)0.34346434474f;
          } else {
            sum += (float)0.089023172855f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += (float)-0.26010069251f;
            } else {
              sum += (float)0.36747506261f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
              sum += (float)0.050387967378f;
            } else {
              sum += (float)-0.30581885576f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
              sum += (float)0.12534120679f;
            } else {
              sum += (float)-0.25626096129f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
              sum += (float)0.030191946775f;
            } else {
              sum += (float)0.416041255f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += (float)-0.25657686591f;
            } else {
              sum += (float)0.0013856443111f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
              sum += (float)-0.022342793643f;
            } else {
              sum += (float)-0.30621930957f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 128)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += (float)0.04518340528f;
            } else {
              sum += (float)0.56236201525f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += (float)0.21535077691f;
            } else {
              sum += (float)-0.27682065964f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
              sum += (float)-0.010995094664f;
            } else {
              sum += (float)-0.29322907329f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += (float)0.009811937809f;
            } else {
              sum += (float)0.37431618571f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            sum += (float)0.32640016079f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += (float)-0.32683482766f;
            } else {
              sum += (float)-0.19425596297f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
              sum += (float)0.27805832028f;
            } else {
              sum += (float)-0.22717607021f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += (float)0.36679205298f;
            } else {
              sum += (float)0.16383431852f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 98)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += (float)0.33867821097f;
            } else {
              sum += (float)-0.12778431177f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
              sum += (float)-0.098776809871f;
            } else {
              sum += (float)0.28121650219f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          sum += (float)0.07251804322f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 64)) {
              sum += (float)0.09698074311f;
            } else {
              sum += (float)0.332028687f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += (float)-0.074160814285f;
            } else {
              sum += (float)0.29572552443f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
              sum += (float)-0.13991516829f;
            } else {
              sum += (float)0.29428428411f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += (float)-0.15876111388f;
            } else {
              sum += (float)0.24435459077f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
            sum += (float)0.036335080862f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
              sum += (float)0.10596742481f;
            } else {
              sum += (float)0.31796884537f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 280)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += (float)-0.079226702452f;
            } else {
              sum += (float)0.27517619729f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += (float)0.28199660778f;
            } else {
              sum += (float)-0.21196205914f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
            sum += (float)-0.060578465462f;
          } else {
            sum += (float)-0.33715322614f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 138)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += (float)0.33413779736f;
            } else {
              sum += (float)0.014436398633f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 52)) {
              sum += (float)-0.079368971288f;
            } else {
              sum += (float)0.31783288717f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 214)) {
            sum += (float)-0.033739246428f;
          } else {
            sum += (float)-0.2719334662f;
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 160)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += (float)0.081672638655f;
            } else {
              sum += (float)-0.25689223409f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += (float)-0.32499438524f;
            } else {
              sum += (float)-0.051578465849f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 144)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              sum += (float)-0.16436111927f;
            } else {
              sum += (float)0.25293567777f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
              sum += (float)-0.17909607291f;
            } else {
              sum += (float)0.31986665726f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
              sum += (float)0.080479472876f;
            } else {
              sum += (float)-0.25631651282f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += (float)-0.11325259507f;
            } else {
              sum += (float)0.29248550534f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 146)) {
              sum += (float)-0.30219390988f;
            } else {
              sum += (float)0.077969826758f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += (float)-0.27209383249f;
            } else {
              sum += (float)-0.122345604f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            sum += (float)0.05236691609f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += (float)-0.31352967024f;
            } else {
              sum += (float)-0.044006008655f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
              sum += (float)0.0026218248531f;
            } else {
              sum += (float)0.33784127235f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 170)) {
              sum += (float)-0.31902649999f;
            } else {
              sum += (float)-0.0085293864831f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 132)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 76)) {
              sum += (float)0.016924904659f;
            } else {
              sum += (float)0.31638592482f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
              sum += (float)0.20469580591f;
            } else {
              sum += (float)0.39174479246f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
            sum += (float)-0.39287409186f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 90)) {
              sum += (float)-0.010012623854f;
            } else {
              sum += (float)0.22915749252f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 64)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 274)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
              sum += (float)-0.082925245166f;
            } else {
              sum += (float)0.25490748882f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += (float)-0.29162201285f;
            } else {
              sum += (float)0.11132474244f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += (float)0.22270227969f;
            } else {
              sum += (float)-0.24382331967f;
            }
          } else {
            sum += (float)0.28655433655f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 132)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
              sum += (float)0.036126196384f;
            } else {
              sum += (float)0.32672309875f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += (float)-0.18230713904f;
            } else {
              sum += (float)0.20356141031f;
            }
          }
        } else {
          sum += (float)-0.16421309114f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
        sum += (float)0.31866189837f;
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 130)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
              sum += (float)-0.1247170791f;
            } else {
              sum += (float)0.25298374891f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
              sum += (float)-0.36089617014f;
            } else {
              sum += (float)0.14839178324f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            sum += (float)0.02473895438f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
              sum += (float)0.10990658402f;
            } else {
              sum += (float)0.29559502006f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
        sum += (float)0.11635296047f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
              sum += (float)-0.099424161017f;
            } else {
              sum += (float)0.40635511279f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
              sum += (float)0.099791176617f;
            } else {
              sum += (float)-0.2740856111f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 330)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 146)) {
              sum += (float)-0.2618381381f;
            } else {
              sum += (float)-0.30325266719f;
            }
          } else {
            sum += (float)-0.016936015338f;
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += (float)0.16113075614f;
            } else {
              sum += (float)-0.21221585572f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += (float)-0.17462061346f;
            } else {
              sum += (float)0.50965607166f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += (float)-0.045879822224f;
            } else {
              sum += (float)-0.29841792583f;
            }
          } else {
            sum += (float)0.30188646913f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 156)) {
              sum += (float)0.31950268149f;
            } else {
              sum += (float)0.023180639371f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += (float)-0.12387565523f;
            } else {
              sum += (float)0.200831756f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += (float)0.16962793469f;
            } else {
              sum += (float)0.41231071949f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 48)) {
              sum += (float)-0.16105590761f;
            } else {
              sum += (float)0.27898684144f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
        sum += (float)0.31274276972f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          sum += (float)-0.23795072734f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 80)) {
              sum += (float)0.18876372278f;
            } else {
              sum += (float)0.29494541883f;
            }
          } else {
            sum += (float)-0.25255766511f;
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          sum += (float)0.27689927816f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
              sum += (float)-0.10051258653f;
            } else {
              sum += (float)-0.53599399328f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 224)) {
              sum += (float)0.025753378868f;
            } else {
              sum += (float)-0.2435413748f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
              sum += (float)0.18299718201f;
            } else {
              sum += (float)-0.21188041568f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += (float)0.31467565894f;
            } else {
              sum += (float)0.6399499774f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 86)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 54)) {
              sum += (float)-0.2063382566f;
            } else {
              sum += (float)0.23082922399f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 96)) {
              sum += (float)0.085799299181f;
            } else {
              sum += (float)0.29183506966f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 150)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += (float)-0.20242904127f;
            } else {
              sum += (float)0.21372081339f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += (float)-0.011727632023f;
            } else {
              sum += (float)-0.2559979856f;
            }
          }
        } else {
          sum += (float)0.22539812326f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
              sum += (float)-0.18796226382f;
            } else {
              sum += (float)0.28941902518f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              sum += (float)0.12480515987f;
            } else {
              sum += (float)-0.29123592377f;
            }
          }
        } else {
          sum += (float)-0.29616841674f;
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += (float)0.1126485467f;
            } else {
              sum += (float)-0.1754988879f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)-0.08107175678f;
            } else {
              sum += (float)0.49430713058f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += (float)-0.28996375203f;
            } else {
              sum += (float)-0.13407668471f;
            }
          } else {
            sum += (float)0.22228223085f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 118)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
              sum += (float)0.31173783541f;
            } else {
              sum += (float)-0.031122026965f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 244)) {
              sum += (float)0.33661729097f;
            } else {
              sum += (float)0.13490313292f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
              sum += (float)-0.15285523236f;
            } else {
              sum += (float)0.19519791007f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
              sum += (float)-0.088439293206f;
            } else {
              sum += (float)0.13067416847f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 64)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 270)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += (float)0.21860559285f;
            } else {
              sum += (float)0.022383227944f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += (float)-0.24839167297f;
            } else {
              sum += (float)0.01477844175f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
              sum += (float)0.1864335835f;
            } else {
              sum += (float)-0.25813472271f;
            }
          } else {
            sum += (float)0.25689890981f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 132)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            sum += (float)0.30465126038f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 44)) {
              sum += (float)0.19139444828f;
            } else {
              sum += (float)-0.15884900093f;
            }
          }
        } else {
          sum += (float)-0.12756358087f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
            sum += (float)-0.075782969594f;
          } else {
            sum += (float)0.24493616819f;
          }
        } else {
          sum += (float)0.3100913465f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 258)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += (float)-0.12693105638f;
            } else {
              sum += (float)0.24502760172f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += (float)-0.41063827276f;
            } else {
              sum += (float)0.096229754388f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            sum += (float)0.019349634647f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
              sum += (float)0.26977169514f;
            } else {
              sum += (float)0.056580737233f;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 80)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 138)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 206)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
              sum += (float)0.17311605811f;
            } else {
              sum += (float)-0.11765045673f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += (float)-0.21865737438f;
            } else {
              sum += (float)0.33553645015f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
              sum += (float)-0.11207630485f;
            } else {
              sum += (float)0.20876042545f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
              sum += (float)-0.25864166021f;
            } else {
              sum += (float)0.08792758733f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += (float)-0.16759049892f;
            } else {
              sum += (float)-0.28348374367f;
            }
          } else {
            sum += (float)0.037535723299f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += (float)-0.24656783044f;
            } else {
              sum += (float)-0.05860183388f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 146)) {
              sum += (float)-0.080336809158f;
            } else {
              sum += (float)-0.27288517356f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 282)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            sum += (float)-0.13281007111f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += (float)0.19742955267f;
            } else {
              sum += (float)0.41101810336f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
              sum += (float)-0.24476422369f;
            } else {
              sum += (float)0.040297258645f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += (float)-0.14690163732f;
            } else {
              sum += (float)0.25781941414f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 128)) {
            sum += (float)0.13427245617f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 52)) {
              sum += (float)-0.26069843769f;
            } else {
              sum += (float)0.080993205309f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 268)) {
              sum += (float)0.25376978517f;
            } else {
              sum += (float)-0.20036394894f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
              sum += (float)-0.39076605439f;
            } else {
              sum += (float)0.0018992727855f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 186)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
              sum += (float)-0.24834395945f;
            } else {
              sum += (float)0.22778567672f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += (float)0.18074125051f;
            } else {
              sum += (float)0.42833903432f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
              sum += (float)0.11671478301f;
            } else {
              sum += (float)-0.30894392729f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
              sum += (float)-0.48274204135f;
            } else {
              sum += (float)0.24947954714f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 236)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 192)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
              sum += (float)-0.063819274306f;
            } else {
              sum += (float)0.17783546448f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += (float)0.18165542185f;
            } else {
              sum += (float)0.4742616713f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 264)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
              sum += (float)-0.24277538061f;
            } else {
              sum += (float)0.15765666962f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += (float)0.2891767323f;
            } else {
              sum += (float)-0.028411095962f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
          sum += (float)0.047792132944f;
        } else {
          sum += (float)0.30548197031f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 254)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += (float)0.23525635898f;
            } else {
              sum += (float)-0.057749405503f;
            }
          } else {
            sum += (float)-0.29326871037f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += (float)0.28016290069f;
            } else {
              sum += (float)-0.57291942835f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 174)) {
              sum += (float)0.30006277561f;
            } else {
              sum += (float)0.060825780034f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
        sum += (float)0.22056061029f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 170)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 168)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 326)) {
              sum += (float)-0.22581586242f;
            } else {
              sum += (float)0.130623281f;
            }
          } else {
            sum += (float)0.1483720392f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
            sum += (float)-0.031718548387f;
          } else {
            sum += (float)-0.28382751346f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 238)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 210)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += (float)-0.021972863004f;
            } else {
              sum += (float)0.25138348341f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 116)) {
              sum += (float)0.019484536722f;
            } else {
              sum += (float)-0.14950639009f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 140)) {
              sum += (float)-0.27060067654f;
            } else {
              sum += (float)0.08387157321f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += (float)0.19430656731f;
            } else {
              sum += (float)0.59654927254f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 266)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += (float)-0.15393212438f;
            } else {
              sum += (float)0.22099123895f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
              sum += (float)-0.060114409775f;
            } else {
              sum += (float)0.22273014486f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
              sum += (float)-0.15603204072f;
            } else {
              sum += (float)0.18496914208f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
              sum += (float)-0.24801768363f;
            } else {
              sum += (float)-0.049054238945f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 66)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 98)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
              sum += (float)-0.16989529133f;
            } else {
              sum += (float)0.16386158764f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += (float)-0.30825185776f;
            } else {
              sum += (float)0.20570228994f;
            }
          }
        } else {
          sum += (float)0.25637453794f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 286)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 176)) {
            sum += (float)0.27879887819f;
          } else {
            sum += (float)-0.015260030515f;
          }
        } else {
          sum += (float)-0.014639129862f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
        sum += (float)0.30432480574f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += (float)0.28225362301f;
            } else {
              sum += (float)-0.53700000048f;
            }
          } else {
            sum += (float)0.29922753572f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 252)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 84)) {
              sum += (float)-0.016164042056f;
            } else {
              sum += (float)0.25516372919f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += (float)-0.50967460871f;
            } else {
              sum += (float)0.1698141098f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            sum += (float)0.053059782833f;
          } else {
            sum += (float)0.31601214409f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 204)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += (float)-0.45959019661f;
            } else {
              sum += (float)-0.055625308305f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += (float)0.21165473759f;
            } else {
              sum += (float)-0.14551278949f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
          sum += (float)0.29545646906f;
        } else {
          sum += (float)0.03447990492f;
        }
      }
    } else {
      sum += (float)0.29978612065f;
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 170)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 168)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 328)) {
              sum += (float)-0.19488634169f;
            } else {
              sum += (float)0.1296210736f;
            }
          } else {
            sum += (float)0.10933516175f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
            sum += (float)-0.018900569528f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 92)) {
              sum += (float)-0.27783173323f;
            } else {
              sum += (float)-0.070671416819f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 82)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 180)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
              sum += (float)-0.12566035986f;
            } else {
              sum += (float)0.029649889097f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 316)) {
              sum += (float)-0.21672350168f;
            } else {
              sum += (float)0.25131192803f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 178)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
              sum += (float)0.0439613536f;
            } else {
              sum += (float)-0.29089516401f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 240)) {
              sum += (float)0.30656570196f;
            } else {
              sum += (float)0.033690586686f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
            sum += (float)-0.1019751057f;
          } else {
            sum += (float)0.25641879439f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 222)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
              sum += (float)-0.22594711185f;
            } else {
              sum += (float)0.14417466521f;
            }
          } else {
            sum += (float)-0.28168767691f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
            sum += (float)0.30090263486f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
              sum += (float)-0.42015630007f;
            } else {
              sum += (float)0.091519191861f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += (float)-0.089720770717f;
            } else {
              sum += (float)0.10915099829f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 134)) {
              sum += (float)0.31791311502f;
            } else {
              sum += (float)0.62879276276f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
        sum += (float)0.22072185576f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
          sum += (float)0.064330846071f;
        } else {
          sum += (float)-0.25501441956f;
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 184)) {
          sum += (float)0.29011961818f;
        } else {
          sum += (float)0.086534947157f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
          sum += (float)-0.026594165713f;
        } else {
          sum += (float)0.16039738059f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 126)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += (float)-0.10911176354f;
            } else {
              sum += (float)0.26281806827f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 76)) {
              sum += (float)-0.29064121842f;
            } else {
              sum += (float)-0.035592164844f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            sum += (float)-0.17141081393f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += (float)0.11816267669f;
            } else {
              sum += (float)0.58824145794f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 198)) {
              sum += (float)-0.23821729422f;
            } else {
              sum += (float)0.056465100497f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += (float)-0.27817234397f;
            } else {
              sum += (float)-0.088394761086f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
            sum += (float)0.58231252432f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
              sum += (float)0.11332101375f;
            } else {
              sum += (float)-0.22225101292f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 290)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
              sum += (float)0.10038923472f;
            } else {
              sum += (float)0.4172424376f;
            }
          } else {
            sum += (float)-0.16785809398f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += (float)-0.27804148197f;
            } else {
              sum += (float)-0.032551895827f;
            }
          } else {
            sum += (float)-0.29866272211f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
              sum += (float)0.21462900937f;
            } else {
              sum += (float)-0.20731630921f;
            }
          } else {
            sum += (float)0.32993030548f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
              sum += (float)-0.066032342613f;
            } else {
              sum += (float)-0.4819881618f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 142)) {
              sum += (float)0.23275302351f;
            } else {
              sum += (float)-0.0046810959466f;
            }
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
            sum += (float)0.19118511677f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
              sum += (float)0.068432606757f;
            } else {
              sum += (float)-0.19166053832f;
            }
          }
        } else {
          sum += (float)-0.39793294668f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          sum += (float)-0.18182520568f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 130)) {
            sum += (float)0.31143063307f;
          } else {
            sum += (float)0.0094127198681f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
          sum += (float)0.21890649199f;
        } else {
          sum += (float)-0.15234650671f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
          sum += (float)0.28719303012f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
            sum += (float)0.17065787315f;
          } else {
            sum += (float)-0.10855287313f;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += (float)0.19665639102f;
            } else {
              sum += (float)-0.12285394222f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
              sum += (float)-0.043460201472f;
            } else {
              sum += (float)0.59944349527f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
            sum += (float)0.01555744186f;
          } else {
            sum += (float)-0.27042073011f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 136)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
              sum += (float)-0.23223353922f;
            } else {
              sum += (float)-0.018422879279f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += (float)0.32757520676f;
            } else {
              sum += (float)-0.032102417201f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 48)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
              sum += (float)-0.26990005374f;
            } else {
              sum += (float)0.059660337865f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 232)) {
              sum += (float)0.26593357325f;
            } else {
              sum += (float)-0.17419454455f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 136)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 74)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += (float)-0.18833760917f;
            } else {
              sum += (float)0.010838214308f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += (float)0.036843642592f;
            } else {
              sum += (float)0.21523223817f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            sum += (float)-0.19091890752f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += (float)0.13390786946f;
            } else {
              sum += (float)0.32427331805f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 196)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
              sum += (float)-0.25150930882f;
            } else {
              sum += (float)0.11663290113f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 202)) {
              sum += (float)0.68447071314f;
            } else {
              sum += (float)-0.14361396432f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 96)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += (float)-0.19517041743f;
            } else {
              sum += (float)-0.012872596271f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)-0.15571446717f;
            } else {
              sum += (float)0.19451007247f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          sum += (float)0.26402536035f;
        } else {
          sum += (float)0.010428101756f;
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 102)) {
          sum += (float)-0.35391491652f;
        } else {
          sum += (float)0.25003480911f;
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 72)) {
        sum += (float)0.086264126003f;
      } else {
        sum += (float)0.29405093193f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
          sum += (float)-0.028228199109f;
        } else {
          sum += (float)-0.29209160805f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 284)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += (float)-0.14571101964f;
            } else {
              sum += (float)0.11620717496f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += (float)0.057321362197f;
            } else {
              sum += (float)-0.21779640019f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 294)) {
            sum += (float)0.5377022624f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
              sum += (float)-0.12307693064f;
            } else {
              sum += (float)0.48850485682f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 306)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
              sum += (float)0.18225693703f;
            } else {
              sum += (float)-0.16879457235f;
            }
          } else {
            sum += (float)0.32031366229f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.14430525899f;
            } else {
              sum += (float)0.0059424177743f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)0.043028529733f;
            } else {
              sum += (float)0.24184001982f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += (float)0.025668995455f;
            } else {
              sum += (float)-0.32163506746f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
              sum += (float)0.60747730732f;
            } else {
              sum += (float)0.21552540362f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += (float)0.16571334004f;
            } else {
              sum += (float)-0.18623439968f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += (float)-0.076798789203f;
            } else {
              sum += (float)-0.29804220796f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 102)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 160)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += (float)0.15335807204f;
            } else {
              sum += (float)-0.18671391904f;
            }
          } else {
            sum += (float)0.26491871476f;
          }
        } else {
          sum += (float)-0.33594033122f;
        }
      } else {
        sum += (float)0.25854122639f;
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 72)) {
        sum += (float)0.075178056955f;
      } else {
        sum += (float)0.29028847814f;
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 218)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 212)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 150)) {
              sum += (float)-0.0038284368347f;
            } else {
              sum += (float)-0.21930615604f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
              sum += (float)-0.16474564373f;
            } else {
              sum += (float)0.17971724272f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
            sum += (float)-0.19605402648f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += (float)0.046029493213f;
            } else {
              sum += (float)0.49252343178f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
              sum += (float)-0.046284481883f;
            } else {
              sum += (float)0.34388381243f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += (float)-0.17458432913f;
            } else {
              sum += (float)0.090284429491f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += (float)-0.16788262129f;
            } else {
              sum += (float)0.090177722275f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += (float)-0.24806201458f;
            } else {
              sum += (float)-0.12574499846f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
        sum += (float)0.28999230266f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 162)) {
              sum += (float)0.15026435256f;
            } else {
              sum += (float)-0.32271283865f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
              sum += (float)-0.050157703459f;
            } else {
              sum += (float)0.25043740869f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 52)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
              sum += (float)-0.15913455188f;
            } else {
              sum += (float)0.18355894089f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += (float)0.051458816975f;
            } else {
              sum += (float)0.28283107281f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            sum += (float)-0.069612979889f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
              sum += (float)0.33447480202f;
            } else {
              sum += (float)0.076290182769f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
            sum += (float)0.16878974438f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += (float)-0.2249057591f;
            } else {
              sum += (float)0.17426158488f;
            }
          }
        }
      } else {
        sum += (float)0.46716022491f;
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
            sum += (float)0.047884691507f;
          } else {
            sum += (float)0.34074896574f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += (float)0.21369887888f;
            } else {
              sum += (float)-0.034400656819f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
              sum += (float)-0.31815513968f;
            } else {
              sum += (float)-0.13802906871f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 182)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += (float)-0.12473969162f;
            } else {
              sum += (float)0.01352425199f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += (float)-0.21163895726f;
            } else {
              sum += (float)-0.019390195608f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
              sum += (float)0.075240716338f;
            } else {
              sum += (float)0.33200219274f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 86)) {
              sum += (float)-0.14727266133f;
            } else {
              sum += (float)0.22812752426f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 78)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 98)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            sum += (float)0.19749863446f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
              sum += (float)0.09172154963f;
            } else {
              sum += (float)-0.29689279199f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 298)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
              sum += (float)0.24880947173f;
            } else {
              sum += (float)0.014986512251f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += (float)-0.032466631383f;
            } else {
              sum += (float)-0.17544311285f;
            }
          }
        }
      } else {
        sum += (float)0.247973755f;
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 82)) {
        sum += (float)0.063351392746f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
          sum += (float)0.046534087509f;
        } else {
          sum += (float)0.29260078073f;
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
          sum += (float)0.093776039779f;
        } else {
          sum += (float)0.25703701377f;
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 102)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 200)) {
            sum += (float)-0.26297938824f;
          } else {
            sum += (float)-0.04698157683f;
          }
        } else {
          sum += (float)0.1558291465f;
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 88)) {
        sum += (float)0.085430569947f;
      } else {
        sum += (float)0.28101652861f;
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += (float)-0.14540995657f;
            } else {
              sum += (float)0.25052946806f;
            }
          } else {
            sum += (float)-0.24611125886f;
          }
        } else {
          sum += (float)0.52091270685f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 48)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += (float)0.038927789778f;
            } else {
              sum += (float)-0.26137265563f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
              sum += (float)0.23641078174f;
            } else {
              sum += (float)-0.20977331698f;
            }
          }
        } else {
          sum += (float)0.15327328444f;
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 152)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)-0.32036921382f;
            } else {
              sum += (float)0.0091358022764f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += (float)-0.091258890927f;
            } else {
              sum += (float)0.23019810021f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += (float)0.230952546f;
            } else {
              sum += (float)-0.20093102753f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
              sum += (float)0.21443559229f;
            } else {
              sum += (float)-0.075141005218f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 172)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += (float)0.10397827625f;
            } else {
              sum += (float)-0.27844548225f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += (float)0.44226363301f;
            } else {
              sum += (float)-0.063261367381f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 302)) {
              sum += (float)-0.0020319900941f;
            } else {
              sum += (float)-0.24521267414f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
              sum += (float)0.44541564584f;
            } else {
              sum += (float)-0.069294728339f;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 100)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
      sum += (float)0.2886287272f;
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          sum += (float)-0.0069172312506f;
        } else {
          sum += (float)-0.27900156379f;
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 114)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
              sum += (float)0.35155719519f;
            } else {
              sum += (float)0.097871921957f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += (float)-0.15954776108f;
            } else {
              sum += (float)0.09286300838f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 304)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
              sum += (float)-0.026842013001f;
            } else {
              sum += (float)0.19799768925f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 188)) {
              sum += (float)-0.22631286085f;
            } else {
              sum += (float)0.30483311415f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
        sum += (float)-0.21981754899f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
          sum += (float)0.21833822131f;
        } else {
          sum += (float)0.04938371107f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
        sum += (float)0.26464986801f;
      } else {
        sum += (float)-0.01244406309f;
      }
    }
  }
  if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
    sum += (float)0.28020939231f;
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += (float)0.33307486773f;
            } else {
              sum += (float)-0.099754460156f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += (float)0.055628202856f;
            } else {
              sum += (float)-0.27676320076f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 164)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              sum += (float)0.64341717958f;
            } else {
              sum += (float)-0.034598920494f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += (float)-0.16307282448f;
            } else {
              sum += (float)-0.0023845578544f;
            }
          }
        }
      } else {
        sum += (float)-0.27537819743f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 234)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 208)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 144)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
              sum += (float)-0.054759215564f;
            } else {
              sum += (float)0.18069817126f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
              sum += (float)-0.17721152306f;
            } else {
              sum += (float)0.040033683181f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
              sum += (float)-0.085017889738f;
            } else {
              sum += (float)0.31198370457f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 216)) {
              sum += (float)0.29429790378f;
            } else {
              sum += (float)0.034224111587f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 296)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += (float)-0.14686356485f;
            } else {
              sum += (float)0.10662041605f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 308)) {
              sum += (float)0.37984752655f;
            } else {
              sum += (float)-0.0077416035347f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 256)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
              sum += (float)-0.068975590169f;
            } else {
              sum += (float)-0.28502440453f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 260)) {
              sum += (float)0.3777897656f;
            } else {
              sum += (float)-0.09290920198f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}
