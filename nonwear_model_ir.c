#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 
  17.5f, 18.5f, 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 0.061142161f, 0.2123111f, 0.21644583f, 
  0.27667719f, 0.34110421f, 0.34208447f, 0.34579301f, 0.36120266f, 0.43918574f, 
  0.44369352f, 0.52785075f, 0.56551117f, 0.58151007f, 0.68232501f, 0.71808392f, 
  0.75116158f, 0.75730211f, 0.77931976f, 0.7800529f, 0.78089452f, 0.81295252f, 
  0.81769842f, 0.82092476f, 0.82321513f, 0.83097517f, 0.84442341f, 0.85559821f, 
  0.85676777f, 0.8572253f, 0.86463237f, 0.8697505f, 0.87326431f, 0.87611806f, 
  0.87977386f, 0.88320804f, 0.88520628f, 0.88810736f, 0.88860434f, 0.88862753f, 
  0.888686f, 0.89270389f, 0.89525938f, 0.89541513f, 0.89879954f, 0.90047741f, 
  0.90179729f, 0.90861392f, 0.91775322f, 0.9323386f, 0.94373679f, 0.95256823f, 
  0.95384324f, 0.96436119f, 0.96720546f, 0.96951783f, 0.97304255f, 0.97603321f, 
  0.97741437f, 0.97748709f, 0.97755629f, 0.97898299f, 0.98115206f, 0.987378f, 
  0.99125099f, 0.99152178f, 0.99275303f, 4196.6523f, 4452.3945f, 4464.5391f, 
  4643.4619f, 4795.9678f, 5038.4434f, 5046.4336f, 5104.2251f, 6227.1279f, 6775.0352f, 
  7328.6899f, 7676.749f, 7912.7192f, 7929.3623f, 8377.0645f, 8389.0615f, 8401.7197f, 
  8435.9727f, 8436.5859f, 8440.3379f, 8484.3291f, 8562.2646f, 8562.3984f, 8563.6738f, 
  8564.2451f, 8610.9316f, 8637.2305f, 8747.3945f, 8758.668f, 9389.7012f, 9422.1367f, 
  9424.6953f, 9561.7832f, 9567.5371f, 9580.9502f, 9600.2734f, 9778.7852f, 9779.125f, 
  9840.8105f, 10024.605f, 10544.961f, 10714.199f, 11607.885f, 11830.957f, 11846.491f, 
  12081.874f, 12395.878f, 12482.59f, 12613.979f, 12627.342f, 12632.123f, 13320.779f, 
  13508.229f, 13517.706f, 13517.894f, 13793.635f, 14191.439f, 14867.099f, 15583.071f, 
  16348.267f, 17608.189f, 17826.236f, 17830.793f, 17895.949f, 17903.947f, 17908.293f, 
  17908.59f, 17922.078f, 17970.787f, 17970.977f, 17977.752f, 17991.945f, 18022.445f, 
  18056.055f, 18067.439f, 18085.213f, 18139.055f, 18196.293f, 18305.07f, 18953.215f, 
  20315.436f, 20608.16f, 20719.586f, 20751.57f, 20942.789f, 22040.365f, 22161.141f, 
  22392.01f, 22394.963f, 22636.834f, 22667.98f, 22737.875f, 23061.922f, 23069.945f, 
  23859.445f, 24306.143f, 24385.984f, 24557.512f, 25220.662f, 25892.086f, 25946.781f, 
  25968.387f, 26068.215f, 26173.258f, 27163.148f, 27748.195f, 27768.988f, 28097.906f, 
  28283.59f, 28318.719f, 28738.123f, 28863.27f, 29135.584f, 29135.805f, 29398.27f, 
  29436.234f, 29444.207f, 32404.645f, 32494.004f, 32504.293f, 32769.949f, 32901.836f, 
  32904.633f, 33059.176f, 33103.359f, 33204.898f, 33224.68f, 33284.891f, 33414.129f, 
  33424.453f, 33578.203f, 33632.57f, 33724.773f, 33761.137f, 33816.785f, 33833.891f, 
  33870.125f, 34047.305f, 34205.953f, 34438.414f, 34440.289f, 34468.617f, 34476.289f, 
  34569.57f, 34602.648f, 34646.133f, 34655.742f, 34767.352f, 34859.328f, 34862.281f, 
  35435.418f, 35663.949f, 35672.508f, 35689.359f, 35764.379f, 35890.297f, 36160.312f, 
  37223.461f, 40060.57f, 40675.641f, 43112.641f, 43497.469f, 43577.23f, 45309.102f, 
  0.090723671f, 0.11073734f, 0.11109956f, 0.11597086f, 0.11884287f, 0.12272927f, 
  0.1255687f, 0.1359396f, 0.15563726f, 0.1943607f, 0.20315292f, 0.20471258f, 
  0.20725089f, 0.20808357f, 0.20933199f, 0.22661361f, 0.26392764f, 0.26824015f, 
  0.27317053f, 0.27336848f, 0.3072542f, 0.3185631f, 0.32216871f, 0.34257525f, 
  0.35942936f, 0.36394721f, 0.44686413f, 0.48893952f, 0.48907396f, 0.50122583f, 
  0.52046537f, 0.53525871f, 0.56943524f, 0.58810461f, 0.66747892f, 0.7082715f, 
  0.7097373f, 0.77013731f, 0.78644371f, 0.79053044f, 0.82642519f, 0.82701099f, 
  0.93220484f, 0.93556201f, 1.0134717f, 1.1817471f, 1.2502372f, 1.3671944f, 
  1.8576022f, 1.903964f, 1.9852427f, 2.0824316f, 2.2456911f, 2.5825849f, 2.6581285f, 
  3.3143916f, 5.3388691f, 6.1242676f, 6.4294257f, 6.7538986f, 15.517994f, 16.723423f, 
  16.877569f, 18.214405f, 35.315231f, 38.96434f, 57.762417f, 0.10851243f, 0.13489638f, 
  0.13886034f, 0.15297833f, 0.16143674f, 0.18465395f, 0.18616921f, 0.19827712f, 
  0.20394233f, 0.20616888f, 0.22056171f, 0.22113661f, 0.23406672f, 0.23672324f, 
  0.33321083f, 0.3623358f, 0.40564406f, 0.40805545f, 0.50210333f, 0.68856502f, 
  0.94682539f, 1.8179333f, 2.0349648f, 2.2656181f, 2.4574842f, 2.6028843f, 2.6816721f, 
  5.9259443f, 6.3816938f, 23.35635f, 27.670515f, 28.198708f, 35.273849f, 42.23278f, 
  86.127777f, 0.86000502f, 0.90970027f, 1.0683886f, 1.1037583f, 1.1125358f, 
  1.1303189f, 1.1337547f, 1.3012383f, 1.3042848f, 1.3143113f, 1.3237696f, 1.3251801f, 
  1.4011885f, 1.4207594f, 1.513351f, 1.5182519f, 1.5877903f, 1.5885384f, 1.5889752f, 
  1.6675937f, 1.6724412f, 1.6727939f, 1.7023456f, 1.7123022f, 1.718276f, 1.7559266f, 
  1.7688251f, 1.7856445f, 1.825013f, 1.8267727f, 1.8289812f, 1.8323578f, 1.8348476f, 
  1.835259f, 1.836664f, 1.8427513f, 1.8470649f, 1.8472219f, 1.8534768f, 1.8779252f, 
  1.8865496f, 1.9241742f, 1.924445f, 1.9260368f, 1.9342816f, 1.9344537f, 1.9345915f, 
  1.9521947f, 1.953464f, 1.9778806f, 1.9786904f, 1.9793737f, 1.9806025f, 1.9870276f, 
  1.9888356f, 1.9895951f, 1.9958665f, 2.0279846f, 2.0329528f, 2.0357807f, 2.0401063f, 
  2.0421765f, 2.0486255f, 2.0586138f, 2.0630765f, 2.0776849f, 2.0779066f, 2.0792294f, 
  2.0991392f, 2.1015654f, 2.1070926f, 2.1113167f, 2.111691f, 2.1132443f, 2.1181521f, 
  2.1210294f, 2.1422763f, 2.1471639f, 2.1473439f, 2.1550212f, 2.1554184f, 2.1563413f, 
  2.1587503f, 2.1638093f, 2.1694968f, 2.1705644f, 2.1757474f, 2.1895318f, 2.1970077f, 
  2.2074308f, 2.2443819f, 2.2614157f, 0.54539156f, 0.54551816f, 0.58420753f, 
  0.62250638f, 0.64837003f, 0.6646204f, 0.84151256f, 1.0386398f, 1.2910268f, 
  1.3806248f, 1.4762337f, 1.5238035f, 1.6268783f, 1.7468501f, 1.8482418f, 1.86145f, 
  1.8745422f, 1.9106541f, 2.4860458f, 2.8513465f, 2.9370761f, 2.9556451f, 3.2308245f, 
  3.2893562f, 3.3699312f, 4.5457749f, 5.0415974f, 5.0690088f, 5.2685733f, 7.5770655f, 
  10.308762f, 11.164842f, 12.469914f, 12.637712f, 22.853554f, 24.29664f, 31.261585f, 
  39.537003f, 71.407333f, 75.355438f, 210.34129f, 285.9057f, 423.92413f, 425.00705f, 
  769.99103f, 1011.1619f, 2305.5554f, 2509.7876f, 4268.5459f, 5778.0005f, 7569.709f, 
  8104.6997f, 13097.248f, 14593.271f, 27353.43f, 101962.5f, 275908.94f, 0.22449347f, 
  0.23816338f, 0.25888264f, 0.27414912f, 0.30562931f, 0.35047919f, 0.35979348f, 
  0.39422363f, 0.39787647f, 0.40279803f, 0.41445887f, 0.54257751f, 0.57334828f, 
  0.58091331f, 0.7210778f, 0.77049482f, 0.97423184f, 1.1294391f, 1.218817f, 
  1.2866766f, 1.3134547f, 1.6055461f, 1.9044127f, 1.911571f, 2.1319761f, 8.6722355f, 
  10.158951f, 17.206388f, 17.426476f, 59.447845f, 69.824966f, 77.641434f, 139.41f, 
  175.13928f, 314.45978f, 447.52859f, 1270.3025f, 1306.6968f, 1933.0928f, 2921.5908f, 
  3789.3408f, 20302.223f, 1292369.1f, 
};

static const int th_len[] = {
  16, 6, 66, 164, 67, 35, 92, 57, 43, 
};
static const int th_begin[] = {
  0, 16, 22, 88, 252, 319, 354, 446, 503, 
};

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
  if (offset == 546 || val < array[0]) {
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

  if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
          sum += 0.57375746965f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.0f;
            } else {
              sum += 0.47142857313f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += 0.15000000596f;
            } else {
              sum += -0.30000001192f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.52500003576f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 142)) {
              sum += 0.3789473772f;
            } else {
              sum += -0.22500000894f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 274)) {
              sum += -0.47569721937f;
            } else {
              sum += 0.38181820512f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
        sum += 0.59621798992f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
              sum += 0.54000002146f;
            } else {
              sum += 0.23636364937f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += 0.27272728086f;
            } else {
              sum += -0.2160000205f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
              sum += 0.45000001788f;
            } else {
              sum += -0.040000002831f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 176)) {
              sum += 0.56528925896f;
            } else {
              sum += 0.27272728086f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
            sum += 0.57808220387f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.34015750885f;
            } else {
              sum += -0.13186813891f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += 0.45365855098f;
            } else {
              sum += -0.10807453841f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += 0.15000000596f;
            } else {
              sum += -0.55781251192f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 290)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += -0.080672279f;
            } else {
              sum += -0.55806273222f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += 0.42524272203f;
            } else {
              sum += -0.13505534828f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
              sum += -0.16363637149f;
            } else {
              sum += 0.51428574324f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              sum += 0.58079999685f;
            } else {
              sum += 0.07500000298f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
          sum += 0.55254238844f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
              sum += 0.41379311681f;
            } else {
              sum += -0.0f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
              sum += -0.0f;
            } else {
              sum += -0.38181820512f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 200)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 158)) {
              sum += 0.47368425131f;
            } else {
              sum += -0.23478262126f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += -0.0f;
            } else {
              sum += 0.53684210777f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += 0.48000001907f;
            } else {
              sum += 0.12000000477f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
              sum += 0.24000000954f;
            } else {
              sum += -0.42857146263f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            sum += 0.46203097701f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += 0.41284695268f;
            } else {
              sum += -0.0010180898244f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
            sum += 0.4309758842f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += 0.38742518425f;
            } else {
              sum += -0.010912053287f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
            sum += 0.45519420505f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.27506515384f;
            } else {
              sum += -0.12362030894f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
              sum += 0.011117145419f;
            } else {
              sum += 0.41248345375f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += -0.079822167754f;
            } else {
              sum += -0.39867377281f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        sum += 0.4638825953f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
          sum += 0.45668315887f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
              sum += 0.39992409945f;
            } else {
              sum += -0.075575478375f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
              sum += 0.45098468661f;
            } else {
              sum += 0.31364554167f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
            sum += 0.50286501646f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += 0.43142050505f;
            } else {
              sum += 0.13489799201f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 282)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += 0.5736053586f;
            } else {
              sum += -0.34613707662f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
              sum += -0.090650469065f;
            } else {
              sum += 0.37478667498f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
          sum += 0.49383664131f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
              sum += 0.48665419221f;
            } else {
              sum += 0.21776269376f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 254)) {
              sum += -0.18550996482f;
            } else {
              sum += 0.41055652499f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
              sum += 0.39007166028f;
            } else {
              sum += 0.01389716845f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.37423822284f;
            } else {
              sum += 0.40159726143f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += -0.43347132206f;
            } else {
              sum += -0.0027175087016f;
            }
          } else {
            sum += 0.58492028713f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
              sum += 0.086880929768f;
            } else {
              sum += 0.38691774011f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
              sum += 0.19139777124f;
            } else {
              sum += -0.26792001724f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 216)) {
            sum += 0.4661949873f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
              sum += 0.036937404424f;
            } else {
              sum += 0.31585416198f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
          sum += 0.40199434757f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
              sum += 0.047705907375f;
            } else {
              sum += 0.40859621763f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += 0.35790964961f;
            } else {
              sum += -0.10582251847f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
              sum += 0.15334016085f;
            } else {
              sum += 0.39829233289f;
            }
          } else {
            sum += 0.060466367751f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
              sum += 0.16462065279f;
            } else {
              sum += -0.26590007544f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 286)) {
              sum += -0.36117085814f;
            } else {
              sum += 0.41034761071f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
          sum += 0.40317347646f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              sum += 0.35596430302f;
            } else {
              sum += -0.10216004401f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += 0.10324210674f;
            } else {
              sum += 0.37843069434f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            sum += 0.027922796085f;
          } else {
            sum += 0.39351311326f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
              sum += 0.43136289716f;
            } else {
              sum += -0.036468863487f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
              sum += 0.12181211263f;
            } else {
              sum += 0.38536757231f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.1277140975f;
            } else {
              sum += -0.26233333349f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
              sum += 0.43440976739f;
            } else {
              sum += 0.23047089577f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
              sum += 0.40065968037f;
            } else {
              sum += 0.6032537818f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
              sum += 0.38963630795f;
            } else {
              sum += -0.049130346626f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
              sum += 0.37490206957f;
            } else {
              sum += 0.023135446012f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
              sum += 0.2254512161f;
            } else {
              sum += 0.4681724906f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 256)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.3097794652f;
            } else {
              sum += 0.055718142539f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.050574336201f;
            } else {
              sum += 0.3629489243f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
          sum += 0.48372510076f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += -0.3678175807f;
            } else {
              sum += -0.089145883918f;
            }
          } else {
            sum += 0.44547018409f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          sum += 0.39774721861f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += 0.16546063125f;
            } else {
              sum += -0.25833597779f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 146)) {
              sum += 0.29450830817f;
            } else {
              sum += -0.051590338349f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
      sum += 0.36810183525f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 170)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.39002531767f;
            } else {
              sum += 0.081320531666f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
              sum += 0.27118602395f;
            } else {
              sum += -0.28148016334f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += 0.075353890657f;
            } else {
              sum += -0.43159177899f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
              sum += 0.33677148819f;
            } else {
              sum += -0.030302869156f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 162)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 186)) {
            sum += 0.3544793725f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 194)) {
              sum += -0.6676710844f;
            } else {
              sum += 0.35139635205f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += 0.23755206168f;
            } else {
              sum += -0.15942633152f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 166)) {
              sum += 0.061222597957f;
            } else {
              sum += 0.34417173266f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.33671027422f;
            } else {
              sum += 0.16928696632f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 128)) {
              sum += -0.057997509837f;
            } else {
              sum += 0.59278434515f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
            sum += 0.45127162337f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += 0.10794007033f;
            } else {
              sum += -0.32444000244f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += 0.25237432122f;
            } else {
              sum += -0.33537751436f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
              sum += -0.053543414921f;
            } else {
              sum += 0.3521809876f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 308)) {
              sum += 0.5702560544f;
            } else {
              sum += -0.056135382503f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
              sum += -0.1793615371f;
            } else {
              sum += 0.40883827209f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
              sum += 0.32995146513f;
            } else {
              sum += -0.0032994726207f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += 0.40259557962f;
            } else {
              sum += 0.6713578701f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += 0.37572610378f;
            } else {
              sum += 0.17938870192f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
              sum += 0.23411349952f;
            } else {
              sum += -0.1861435473f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
              sum += 0.31244170666f;
            } else {
              sum += -0.078446157277f;
            }
          } else {
            sum += 0.51905429363f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
              sum += -0.25665056705f;
            } else {
              sum += 0.32922539115f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += -0.033001136035f;
            } else {
              sum += 0.44995141029f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
      sum += 0.34604588151f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 170)) {
              sum += 0.36592781544f;
            } else {
              sum += 0.14979192615f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 138)) {
              sum += 0.20252226293f;
            } else {
              sum += -0.24553841352f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += 0.064815476537f;
            } else {
              sum += -0.38523697853f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
              sum += 0.28468182683f;
            } else {
              sum += -0.022002726793f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            sum += 0.34802681208f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
              sum += -0.084038227797f;
            } else {
              sum += 0.19725522399f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 218)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
              sum += 0.30423104763f;
            } else {
              sum += 0.047900471836f;
            }
          } else {
            sum += 0.35096347332f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += 0.22649662197f;
            } else {
              sum += 0.38060426712f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
              sum += 0.28860837221f;
            } else {
              sum += -0.068388476968f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.023696718737f;
            } else {
              sum += 0.39326411486f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 234)) {
              sum += -0.064389318228f;
            } else {
              sum += 0.29980820417f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.26796278358f;
            } else {
              sum += -0.09562304616f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += 0.34642612934f;
            } else {
              sum += 0.10355837643f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 298)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              sum += -0.2055092901f;
            } else {
              sum += 0.31981492043f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.43140920997f;
            } else {
              sum += 0.11561892182f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
            sum += -0.050992708653f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += 0.46264079213f;
            } else {
              sum += 0.25870805979f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            sum += -0.3216676414f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += -0.0044716070406f;
            } else {
              sum += 0.43127727509f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
              sum += 0.29299724102f;
            } else {
              sum += -0.19566442072f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += 0.39314219356f;
            } else {
              sum += 0.12285257876f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += -0.14755302668f;
            } else {
              sum += 0.36335328221f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
              sum += -0.30704551935f;
            } else {
              sum += 0.014229868539f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
          sum += 0.33045557141f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += 0.33214241266f;
            } else {
              sum += 0.12923388183f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
              sum += 0.22631016374f;
            } else {
              sum += -0.26715022326f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += 0.113369748f;
            } else {
              sum += 0.32906782627f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
              sum += 0.19279886782f;
            } else {
              sum += -0.12826614082f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += 0.26901212335f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += 0.31724083424f;
            } else {
              sum += -0.19407004118f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
        sum += 0.33221960068f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 180)) {
            sum += 0.32646998763f;
          } else {
            sum += 0.081766083837f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
              sum += 0.14792922139f;
            } else {
              sum += -0.53015089035f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 250)) {
              sum += 0.16161869466f;
            } else {
              sum += 0.33662503958f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += 0.017119206488f;
            } else {
              sum += 0.36874383688f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.18217559159f;
            } else {
              sum += 0.16515365243f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 212)) {
            sum += 0.39506867528f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 260)) {
              sum += -0.16989092529f;
            } else {
              sum += 0.26940134168f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
              sum += 0.19885919988f;
            } else {
              sum += -0.066255286336f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
              sum += 0.1824926585f;
            } else {
              sum += 0.43009209633f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 264)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
              sum += -0.20117096603f;
            } else {
              sum += 0.14983864129f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.00064152415143f;
            } else {
              sum += 0.30176350474f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += 0.33700633049f;
            } else {
              sum += -0.28486886621f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.55179530382f;
            } else {
              sum += 0.14578162134f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            sum += 0.39652869105f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += -0.21541132033f;
            } else {
              sum += 0.29497110844f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 266)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.30309909582f;
            } else {
              sum += -0.10924629122f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
              sum += 0.37307888269f;
            } else {
              sum += -0.16602577269f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
            sum += -0.26094707847f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
              sum += 0.69691085815f;
            } else {
              sum += 0.19894330204f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            sum += 0.33251395822f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += 0.024311086163f;
            } else {
              sum += 0.17798724771f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
            sum += 0.34481412172f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              sum += 0.24847757816f;
            } else {
              sum += -0.0731671229f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
              sum += 0.26552635431f;
            } else {
              sum += -0.069557830691f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.37363010645f;
            } else {
              sum += 0.076731517911f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 284)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += -0.0034724734724f;
            } else {
              sum += -0.25940510631f;
            }
          } else {
            sum += 0.33542540669f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
        sum += 0.32249671221f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
              sum += 0.277256459f;
            } else {
              sum += 0.077005624771f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
              sum += 0.29802545905f;
            } else {
              sum += 0.50419127941f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += 0.29840368032f;
            } else {
              sum += -0.11424969137f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 180)) {
              sum += 0.27864927053f;
            } else {
              sum += 0.067330725491f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
              sum += 0.29927194118f;
            } else {
              sum += -0.033611804247f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += 0.20361100137f;
            } else {
              sum += 0.67505371571f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += 0.36283940077f;
            } else {
              sum += -0.014746156521f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
              sum += -0.19542957842f;
            } else {
              sum += 0.036812435836f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 144)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
              sum += 0.20102410018f;
            } else {
              sum += 0.39302381873f;
            }
          } else {
            sum += 0.55780357122f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
              sum += 0.3715903163f;
            } else {
              sum += -0.18494470417f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += 0.093539655209f;
            } else {
              sum += 0.3671361208f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += 0.34740686417f;
            } else {
              sum += -0.13620403409f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += 0.35471230745f;
            } else {
              sum += 0.042923677713f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
              sum += -0.28143936396f;
            } else {
              sum += 0.34639295936f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              sum += 0.24899834394f;
            } else {
              sum += -0.22196337581f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 230)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 208)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
              sum += -0.038462460041f;
            } else {
              sum += 0.27735978365f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
              sum += 0.84031909704f;
            } else {
              sum += 0.16882237792f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 316)) {
            sum += -0.25726866722f;
          } else {
            sum += 0.22189757228f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
      sum += 0.31420949101f;
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 160)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += 0.057225767523f;
            } else {
              sum += -0.21875955164f;
            }
          } else {
            sum += 0.29196810722f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
            sum += 0.32700717449f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
              sum += -0.33139762282f;
            } else {
              sum += 0.25750762224f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
          sum += 0.27006241679f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
              sum += 0.14080399275f;
            } else {
              sum += -0.4061858952f;
            }
          } else {
            sum += 0.22941763699f;
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += 0.36843496561f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              sum += 0.26485791802f;
            } else {
              sum += -0.24185438454f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
              sum += -0.077298253775f;
            } else {
              sum += 0.25328055024f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
              sum += -0.0054625784978f;
            } else {
              sum += -0.25581890345f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
              sum += 0.081331849098f;
            } else {
              sum += -0.281049788f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
              sum += 0.44742047787f;
            } else {
              sum += -0.14472734928f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
              sum += -0.15594080091f;
            } else {
              sum += 0.3459393084f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 142)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
              sum += 0.19141481817f;
            } else {
              sum += 0.67799425125f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
              sum += 0.22519575059f;
            } else {
              sum += -0.29454997182f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += 0.19277252257f;
            } else {
              sum += 0.75330895185f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
              sum += 0.10758849233f;
            } else {
              sum += -0.24608439207f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.2657559216f;
            } else {
              sum += -0.26697030663f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
              sum += 0.30805969238f;
            } else {
              sum += -0.21367247403f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 312)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += -0.11956513673f;
            } else {
              sum += 0.32741504908f;
            }
          } else {
            sum += -0.13238555193f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.31199017167f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            sum += 0.20313045382f;
          } else {
            sum += -0.15317386389f;
          }
        } else {
          sum += 0.31681868434f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          sum += -0.4151366055f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 192)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
              sum += 0.17254085839f;
            } else {
              sum += -0.57149231434f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.0066630700603f;
            } else {
              sum += 0.31684178114f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += 0.33400896192f;
            } else {
              sum += 0.15019251406f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += 0.24358457327f;
            } else {
              sum += -0.067792743444f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
              sum += 0.3057141602f;
            } else {
              sum += -0.061509270221f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 174)) {
              sum += 0.57417321205f;
            } else {
              sum += 0.23566937447f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += 0.027080746368f;
            } else {
              sum += 0.33234542608f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
              sum += -0.14699368179f;
            } else {
              sum += 0.14605252445f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 262)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
              sum += -0.12993761897f;
            } else {
              sum += 0.23446406424f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += 0.0046880091541f;
            } else {
              sum += 0.23043274879f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 136)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
              sum += -0.084235727787f;
            } else {
              sum += 0.20272693038f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 122)) {
              sum += 0.60428482294f;
            } else {
              sum += 0.21384584904f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += 0.092189975083f;
            } else {
              sum += 0.28243997693f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.20773290098f;
            } else {
              sum += 0.12404184788f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
              sum += 0.21939335763f;
            } else {
              sum += -0.13440199196f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += 0.41139879823f;
            } else {
              sum += 0.14845943451f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += -0.096569292247f;
            } else {
              sum += -0.23947356641f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 114)) {
              sum += -0.016379166394f;
            } else {
              sum += 0.30020722747f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30811649561f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
        sum += 0.30929327011f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          sum += -0.39880952239f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 152)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.13258317113f;
            } else {
              sum += 0.30952823162f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += 0.2261248529f;
            } else {
              sum += -0.13636538386f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
              sum += 0.077339522541f;
            } else {
              sum += 0.40666949749f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.41466602683f;
            } else {
              sum += -0.018874909729f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 120)) {
              sum += 0.0035098914523f;
            } else {
              sum += 0.27938523889f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
              sum += -0.19348101318f;
            } else {
              sum += 0.16141979396f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.13219310343f;
            } else {
              sum += 0.50859707594f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.29691201448f;
            } else {
              sum += -0.24770905077f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
            sum += 0.3487868309f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
              sum += -0.1019724831f;
            } else {
              sum += 0.16872826219f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 172)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.089500233531f;
            } else {
              sum += 0.41268274188f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.23295609653f;
            } else {
              sum += 0.21964861453f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 168)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
              sum += 0.21028362215f;
            } else {
              sum += 0.029441285878f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
              sum += 0.0124185225f;
            } else {
              sum += -0.31485205889f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 252)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
              sum += 0.19653265178f;
            } else {
              sum += -0.20816397667f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
              sum += 0.28530797362f;
            } else {
              sum += -0.0097925644368f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 306)) {
              sum += 0.31352001429f;
            } else {
              sum += -0.064708255231f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += 0.17158770561f;
            } else {
              sum += -0.23441277444f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30508267879f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
        sum += 0.29896438122f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 148)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
            sum += 0.21520152688f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
              sum += -0.0041485507973f;
            } else {
              sum += -0.48070558906f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += 0.27777838707f;
            } else {
              sum += 0.11983198673f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += 0.16970735788f;
            } else {
              sum += -0.31763398647f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.010663358495f;
            } else {
              sum += 0.29351043701f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 258)) {
              sum += -0.036050785333f;
            } else {
              sum += 0.27321988344f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
              sum += -0.008864665404f;
            } else {
              sum += 0.34212353826f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 160)) {
              sum += 0.22358764708f;
            } else {
              sum += 0.48064267635f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += 0.15458551049f;
            } else {
              sum += 0.42858114839f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.19972871244f;
            } else {
              sum += -0.019044037908f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 296)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += 0.076750911772f;
            } else {
              sum += -0.12890906632f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.3058848083f;
            } else {
              sum += -0.016256464645f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.33351635933f;
            } else {
              sum += -0.1956743449f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += -0.073619298637f;
            } else {
              sum += 0.13857977092f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
              sum += -0.10942033678f;
            } else {
              sum += -0.25325289369f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
              sum += 0.32831424475f;
            } else {
              sum += -0.025133805349f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
            sum += 0.30996900797f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 202)) {
              sum += -0.21854276955f;
            } else {
              sum += 0.17841972411f;
            }
          }
        } else {
          sum += 0.36704659462f;
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
          sum += 0.18664632738f;
        } else {
          sum += -0.065511927009f;
        }
      } else {
        sum += 0.31191307306f;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          sum += -0.26936486363f;
        } else {
          sum += 0.15541271865f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 148)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += 0.20462597907f;
            } else {
              sum += 0.35400897264f;
            }
          } else {
            sum += 0.024733679369f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
            sum += 0.2448785454f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 178)) {
              sum += -0.27359589934f;
            } else {
              sum += 0.17406448722f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 156)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
              sum += 0.21733173728f;
            } else {
              sum += -0.19809022546f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
              sum += -0.058739092201f;
            } else {
              sum += 0.15408170223f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 130)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += 0.22025246918f;
            } else {
              sum += -0.20443916321f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += 0.22626537085f;
            } else {
              sum += -0.0018624091754f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 326)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.26660019159f;
            } else {
              sum += -0.21792337298f;
            }
          } else {
            sum += 0.29722559452f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += 0.042906597257f;
            } else {
              sum += 0.30950891972f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
              sum += -0.12920168042f;
            } else {
              sum += 0.21840567887f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.29077345133f;
            } else {
              sum += 0.14935670793f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += 0.24081678689f;
            } else {
              sum += -0.12920992076f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
            sum += 0.22652357817f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
              sum += 0.36223983765f;
            } else {
              sum += 0.91650122404f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 236)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 146)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += -0.6766885519f;
            } else {
              sum += -0.21512235701f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += 0.20854361355f;
            } else {
              sum += -0.098114281893f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
              sum += 0.14868025482f;
            } else {
              sum += -0.18834403157f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
              sum += 0.30166730285f;
            } else {
              sum += 0.11022634059f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30053955317f;
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 150)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          sum += 0.06317973882f;
        } else {
          sum += 0.25892579556f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
          sum += 0.18557581306f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            sum += -0.28653204441f;
          } else {
            sum += 0.043599348515f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            sum += 0.31274503469f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += 0.23369340599f;
            } else {
              sum += -0.056501790881f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.36825686693f;
            } else {
              sum += 0.13599985838f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
              sum += 0.10068892688f;
            } else {
              sum += 0.5236851573f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 222)) {
              sum += 0.34133139253f;
            } else {
              sum += -0.027218354866f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
              sum += -0.073330543935f;
            } else {
              sum += 0.091065317392f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
              sum += -0.009912442416f;
            } else {
              sum += -0.17700126767f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
              sum += -0.13178725541f;
            } else {
              sum += 0.19630338252f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 144)) {
              sum += 0.11253731698f;
            } else {
              sum += -0.068782441318f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 272)) {
              sum += -0.20186077058f;
            } else {
              sum += 0.027357865125f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
              sum += 0.21408988535f;
            } else {
              sum += -0.092498205602f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += 0.27379581332f;
            } else {
              sum += -0.036617081612f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 162)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
              sum += 0.15078690648f;
            } else {
              sum += -0.27882358432f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += 0.51420837641f;
            } else {
              sum += -0.065433777869f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 244)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
              sum += -0.24099731445f;
            } else {
              sum += 0.21277822554f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += 0.035836331546f;
            } else {
              sum += 0.29272270203f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
        sum += 0.18936605752f;
      } else {
        sum += -0.092901393771f;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
        sum += 0.30436828732f;
      } else {
        sum += 0.030960468575f;
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        sum += -0.013979041018f;
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
            sum += 0.30821934342f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += 0.27112621069f;
            } else {
              sum += -0.0097008114681f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
            sum += -0.11776360869f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
              sum += 0.25526431203f;
            } else {
              sum += -0.033486548811f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 170)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.33574083447f;
            } else {
              sum += -0.069050244987f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
              sum += 0.075562700629f;
            } else {
              sum += 0.41353192925f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 196)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += -0.25401833653f;
            } else {
              sum += 0.077437400818f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
              sum += 0.134279266f;
            } else {
              sum += -0.10661797971f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 270)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += -0.22375197709f;
            } else {
              sum += -0.0089620733634f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += 0.27541381121f;
            } else {
              sum += -0.035413116217f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 154)) {
              sum += 0.29828065634f;
            } else {
              sum += 0.028085550293f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 240)) {
              sum += -0.17037308216f;
            } else {
              sum += 0.22744709253f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
    sum += 0.29637292027f;
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 158)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
        sum += 0.3298664093f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 268)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 226)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.19230087101f;
            } else {
              sum += -0.0066139730625f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += -0.2671597898f;
            } else {
              sum += 0.17411914468f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 302)) {
              sum += 0.3564735055f;
            } else {
              sum += -0.043377488852f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
              sum += -0.044880922884f;
            } else {
              sum += 0.31298685074f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += -0.195489645f;
            } else {
              sum += 0.12938171625f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.31835407019f;
            } else {
              sum += -0.24589452147f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 288)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
              sum += 0.041429869831f;
            } else {
              sum += -0.23850911856f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
              sum += 0.32140746713f;
            } else {
              sum += -0.14184650779f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 172)) {
          sum += -0.010567699559f;
        } else {
          sum += 0.27495896816f;
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
        sum += 0.12893892825f;
      } else {
        sum += -0.067619867623f;
      }
    } else {
      sum += 0.30665302277f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
        sum += 0.31686788797f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += 0.042110458016f;
            } else {
              sum += 0.2966851294f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 294)) {
              sum += -0.030055005103f;
            } else {
              sum += 0.14088901877f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.20408032835f;
            } else {
              sum += -0.1048341319f;
            }
          } else {
            sum += 0.29124155641f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
        sum += 0.29354774952f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += 0.10529232025f;
            } else {
              sum += -0.29795300961f;
            }
          } else {
            sum += -0.41205593944f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 210)) {
              sum += 0.27774211764f;
            } else {
              sum += -0.23508886993f;
            }
          } else {
            sum += 0.30393701792f;
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
        sum += 0.1233605817f;
      } else {
        sum += -0.065339013934f;
      }
    } else {
      sum += 0.3024764359f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 126)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 124)) {
              sum += 0.072739072144f;
            } else {
              sum += -0.25075954199f;
            }
          } else {
            sum += 0.31037768722f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.26863235235f;
            } else {
              sum += -0.070632301271f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += 0.2773733139f;
            } else {
              sum += -0.0070568895899f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 118)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
              sum += -0.046447329223f;
            } else {
              sum += -0.19073213637f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 214)) {
              sum += 0.31253322959f;
            } else {
              sum += -0.18651382625f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
              sum += 0.47982820868f;
            } else {
              sum += 0.060683276504f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += -0.078181602061f;
            } else {
              sum += 0.19960218668f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
              sum += 0.17142336071f;
            } else {
              sum += -0.26533198357f;
            }
          } else {
            sum += 0.23929437995f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
              sum += 0.26246771216f;
            } else {
              sum += 0.55372202396f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
              sum += -0.10462453216f;
            } else {
              sum += 0.20785677433f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
            sum += 0.32080149651f;
          } else {
            sum += 0.098180316389f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 198)) {
              sum += 0.056545898318f;
            } else {
              sum += 0.30845525861f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
              sum += -0.022016573697f;
            } else {
              sum += 0.21116688848f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
    sum += 0.28820696473f;
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 164)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.29475095868f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += -0.31449195743f;
            } else {
              sum += 0.065751753747f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            sum += -0.098439469934f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
              sum += 0.16580834985f;
            } else {
              sum += 0.67890626192f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
              sum += 0.35196104646f;
            } else {
              sum += -0.096174821258f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += -0.30209422112f;
            } else {
              sum += 0.16073736548f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 150)) {
              sum += -0.14388532937f;
            } else {
              sum += 0.15463718772f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += -0.048294324428f;
            } else {
              sum += 0.064041621983f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 182)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
              sum += -0.11342134327f;
            } else {
              sum += 0.26739764214f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
              sum += -0.17027489841f;
            } else {
              sum += 0.11367891729f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 174)) {
            sum += 0.0010216155788f;
          } else {
            sum += 0.27820432186f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
            sum += 0.21550902724f;
          } else {
            sum += -0.19854110479f;
          }
        } else {
          sum += 0.46049645543f;
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
        sum += 0.16126269102f;
      } else {
        sum += -0.061077732593f;
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
        sum += 0.29167321324f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
          sum += -0.042005714029f;
        } else {
          sum += 0.24985025823f;
        }
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
              sum += 0.014041483402f;
            } else {
              sum += -0.10597609729f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += 0.058068040758f;
            } else {
              sum += -0.16517931223f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
              sum += 0.22282625735f;
            } else {
              sum += 0.040847536176f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
              sum += -0.2082542628f;
            } else {
              sum += 0.12037189305f;
            }
          }
        }
      } else {
        sum += 0.30335617065f;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
        sum += 0.30733212829f;
      } else {
        sum += 0.060871530324f;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
    sum += 0.27980899811f;
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 280)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 224)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 204)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 178)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.043157055974f;
            } else {
              sum += 0.063283003867f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
              sum += -0.34614306688f;
            } else {
              sum += -0.060513403267f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 206)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
              sum += 0.68587464094f;
            } else {
              sum += 0.14131705463f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
              sum += -0.05791676417f;
            } else {
              sum += 0.27874276042f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 238)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 116)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
              sum += -0.31173858047f;
            } else {
              sum += -0.067292489111f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 232)) {
              sum += 0.11564923078f;
            } else {
              sum += -0.21622921526f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
              sum += -0.039862044156f;
            } else {
              sum += -0.31686505675f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 140)) {
              sum += 0.28878682852f;
            } else {
              sum += 0.082666821778f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 304)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
            sum += 0.4011271596f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
              sum += 0.25941103697f;
            } else {
              sum += -0.056654702872f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            sum += -0.19497087598f;
          } else {
            sum += 0.063079863787f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += 0.22904494405f;
            } else {
              sum += -0.27036124468f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += 0.10077212006f;
            } else {
              sum += -0.2439340651f;
            }
          }
        } else {
          sum += 0.27675011754f;
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
  // return sum;
}