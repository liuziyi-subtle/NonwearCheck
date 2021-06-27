#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  3.5f, 4.5f, 6.5f, 7.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 
  18.5f, 0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 0.061142161f, 0.20827982f, 0.23493654f, 
  0.23559244f, 0.33981395f, 0.34208447f, 0.51294136f, 0.5773434f, 0.58207119f, 
  0.66731995f, 0.68232501f, 0.71799791f, 0.73572701f, 0.74431586f, 0.75388747f, 
  0.77761602f, 0.77931976f, 0.81147408f, 0.82101148f, 0.83031166f, 0.84876561f, 
  0.8572253f, 0.85953963f, 0.86948234f, 0.87001181f, 0.87233627f, 0.87329841f, 
  0.87639183f, 0.88191998f, 0.88810736f, 0.89020026f, 0.89270389f, 0.89562774f, 
  0.90014523f, 0.90047741f, 0.90214896f, 0.9072603f, 0.91475409f, 0.92379093f, 
  0.92463863f, 0.92630041f, 0.93210649f, 0.93675661f, 0.94373679f, 0.95011103f, 
  0.95256823f, 0.95756227f, 0.96618021f, 0.96794039f, 0.96932602f, 0.97732902f, 
  0.97755629f, 0.97945917f, 0.97959834f, 0.97967386f, 0.98964572f, 0.99275303f, 
  4121.8618f, 4152.1074f, 4196.6523f, 4452.3945f, 4464.5391f, 4795.9678f, 4808.1128f, 
  5038.4434f, 5046.4336f, 6170.916f, 7327.104f, 7389.7334f, 7471.127f, 7473.041f, 
  7487.4092f, 7676.749f, 7754.2773f, 7757.8037f, 7842.8535f, 7911.2783f, 7943.248f, 
  8196.3281f, 8377.0645f, 8378.0547f, 8387.5234f, 8389.957f, 8429.2188f, 8436.5859f, 
  8440.3379f, 8477.3672f, 8525.8086f, 8537.5771f, 8562.2646f, 8564.1113f, 8605.5859f, 
  8645.6973f, 8647.084f, 8662.5332f, 8890.4629f, 8911.3848f, 8990.5869f, 9112.9473f, 
  9464.1143f, 9577.3398f, 9578.2148f, 9580.9502f, 9592.4707f, 9778.8809f, 9826.0596f, 
  10403.541f, 11585.999f, 11674.281f, 11693.526f, 12072.092f, 12395.878f, 12406.064f, 
  12483.741f, 12614.244f, 12627.342f, 12632.123f, 13517.706f, 13548.955f, 13881.498f, 
  14217.494f, 14238.717f, 15295.666f, 15549.14f, 15605.926f, 16082.97f, 17584.021f, 
  17608.189f, 17807.996f, 17830.793f, 17904.77f, 17910.057f, 17929.867f, 17946.436f, 
  17950.613f, 17957.234f, 17970.977f, 17975.299f, 17976.129f, 17991.945f, 17995.121f, 
  18025.674f, 18046.926f, 18056.055f, 18063.662f, 18067.439f, 18120.543f, 18124.207f, 
  18135.328f, 18139.055f, 18148.273f, 18154.598f, 18159.232f, 18208.086f, 18252.953f, 
  18389.895f, 18542.402f, 18850.766f, 19621.51f, 20331.512f, 20746.479f, 20751.57f, 
  20778.922f, 20920.309f, 20942.789f, 21282.516f, 22040.223f, 22132.307f, 22170.795f, 
  22232.695f, 22378.934f, 22394.963f, 22395.992f, 22398.074f, 22553.84f, 22560.885f, 
  22637.297f, 22859.875f, 23213.906f, 23284.982f, 24337.562f, 24557.512f, 25248.742f, 
  25267.703f, 25375.889f, 25378.447f, 25506.363f, 26250.654f, 26705.77f, 27146.346f, 
  27161.93f, 27322.566f, 27687.488f, 27748.195f, 27768.68f, 28097.906f, 28111.621f, 
  28283.59f, 29075.07f, 29088.59f, 29103.324f, 29332.385f, 29361.895f, 29437.082f, 
  32321.945f, 32322.043f, 32492.24f, 32578.848f, 32901.836f, 32906.426f, 33059.176f, 
  33103.359f, 33222.938f, 33226.527f, 33633.473f, 33666.953f, 33724.773f, 33782.609f, 
  33817.758f, 33834.109f, 33856.945f, 33871.992f, 34011.445f, 34027.07f, 34205.953f, 
  34569.57f, 34646.133f, 34655.742f, 34657.367f, 34771.68f, 34862.281f, 34938.82f, 
  35239.547f, 35669.055f, 35672.508f, 35689.461f, 35764.379f, 35768.969f, 35802.836f, 
  36081.438f, 40060.57f, 40475.453f, 40675.641f, 43112.641f, 43497.469f, 43577.23f, 
  43595.93f, 45309.102f, 0.090672836f, 0.091401026f, 0.097278073f, 0.11073734f, 
  0.11109956f, 0.11429767f, 0.11597086f, 0.12272927f, 0.15256712f, 0.15287068f, 
  0.15525742f, 0.15563726f, 0.18166542f, 0.1943607f, 0.19732821f, 0.20315292f, 
  0.20644617f, 0.20933199f, 0.22661361f, 0.26342601f, 0.26392764f, 0.26798686f, 
  0.27041858f, 0.27336848f, 0.2734226f, 0.27740073f, 0.29538494f, 0.3072542f, 
  0.3185631f, 0.36274296f, 0.42768747f, 0.48550633f, 0.48893952f, 0.48907396f, 
  0.5163421f, 0.56700861f, 0.56943524f, 0.61114877f, 0.7082715f, 0.71063721f, 
  0.77013731f, 0.78207779f, 0.7976138f, 0.82701099f, 0.83946455f, 0.86610746f, 
  0.89079523f, 0.93556201f, 0.95139664f, 1.3671944f, 1.4471937f, 1.6072547f, 
  1.699896f, 1.9852427f, 2.0824316f, 2.4585524f, 3.3412519f, 5.1497846f, 5.4945364f, 
  6.1242676f, 6.4241886f, 9.5990067f, 15.517994f, 16.718523f, 17.948275f, 18.214405f, 
  25.377758f, 27.582161f, 48.715794f, 57.762417f, 0.10544622f, 0.14557159f, 
  0.15136677f, 0.15252417f, 0.16089121f, 0.16143674f, 0.18616921f, 0.19787171f, 
  0.20205395f, 0.22113661f, 0.26748163f, 0.27992171f, 0.30536395f, 0.40348774f, 
  0.40517342f, 2.3500478f, 5.973485f, 20.526682f, 23.35635f, 28.286926f, 34.297054f, 
  46.780952f, 51.932533f, 0.39125603f, 0.77646911f, 0.90970027f, 0.91293508f, 
  1.1037583f, 1.1068969f, 1.1143324f, 1.1344337f, 1.1545048f, 1.2760487f, 1.3143113f, 
  1.3251801f, 1.3318331f, 1.3398174f, 1.3495235f, 1.4011885f, 1.4100171f, 1.4207594f, 
  1.5182519f, 1.5920787f, 1.6593375f, 1.6675937f, 1.6898289f, 1.7074056f, 1.7103798f, 
  1.7180579f, 1.7741001f, 1.7847637f, 1.7940514f, 1.8171303f, 1.8220359f, 1.8249896f, 
  1.8256776f, 1.8267727f, 1.8289812f, 1.8440378f, 1.8457155f, 1.8789947f, 1.8790412f, 
  1.8865496f, 1.893975f, 1.9133643f, 1.9241742f, 1.924445f, 1.9260368f, 1.9345915f, 
  1.9645412f, 1.9696749f, 1.9778806f, 1.9793737f, 1.9859133f, 1.988313f, 1.9885612f, 
  2.0079584f, 2.0136867f, 2.0332484f, 2.0339539f, 2.0402355f, 2.0418203f, 2.0495787f, 
  2.0497632f, 2.057523f, 2.0579169f, 2.0630765f, 2.0715609f, 2.0811663f, 2.0929694f, 
  2.0991392f, 2.1086764f, 2.1118124f, 2.1181192f, 2.1183758f, 2.1210294f, 2.1356325f, 
  2.1474152f, 2.1523778f, 2.1575294f, 2.1587489f, 2.1587539f, 2.1613154f, 2.1616855f, 
  2.1685505f, 2.1705644f, 2.1814799f, 2.1884317f, 2.1977284f, 2.2106423f, 2.2387667f, 
  2.2614157f, 0.57366192f, 0.57393539f, 0.6157223f, 0.62009537f, 0.62250638f, 
  0.6646204f, 0.96301085f, 1.0322144f, 1.2910268f, 1.3916299f, 1.4762337f, 1.4896045f, 
  1.8645527f, 1.8960943f, 1.9106541f, 2.1309292f, 2.4610949f, 2.5340402f, 3.1687722f, 
  3.2441316f, 3.5679827f, 5.0064888f, 5.2364321f, 5.8043146f, 5.9274378f, 6.2178373f, 
  10.052574f, 10.308762f, 10.856131f, 12.469914f, 12.741134f, 16.964588f, 23.916901f, 
  24.29664f, 39.756836f, 82.570114f, 82.622208f, 84.903717f, 144.61469f, 158.19917f, 
  170.34483f, 193.96774f, 308.72931f, 354.63522f, 451.06116f, 491.11542f, 696.91528f, 
  818.31927f, 1009.6494f, 2509.7876f, 3027.812f, 5778.0005f, 29497.734f, 29993.289f, 
  166079.0f, 175328.11f, 275908.94f, 0.22449347f, 0.27414912f, 0.31376189f, 0.35047919f, 
  0.42493567f, 0.43500239f, 0.44827086f, 0.47416413f, 0.49782559f, 0.53246325f, 
  0.54257751f, 0.7210778f, 0.76922923f, 0.79371405f, 0.79715145f, 0.8009479f, 
  0.80229837f, 0.95869648f, 1.2236476f, 1.3239484f, 1.9840028f, 2.315758f, 4.7132459f, 
  7.582644f, 8.7053013f, 10.158951f, 10.1736f, 11.509941f, 12.873912f, 16.889742f, 
  49.979828f, 56.927505f, 63.412457f, 159.84491f, 187.20476f, 556.18835f, 704.58423f, 
  1812.6853f, 2264.4705f, 2940.1807f, 4404.6533f, 
};

static const int th_len[] = {
  14, 6, 57, 191, 70, 23, 89, 57, 41, 
};

static const int th_begin[] = {
  0, 14, 20, 77, 268, 338, 361, 450, 507, 
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
  if (offset == 548 || val < array[0]) {
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

  if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
          sum += 0.57556009293f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += -.0f;
            } else {
              sum += 0.47142857313f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += 0.15000000596f;
            } else {
              sum += -0.30000001192f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
          sum += 0.52258068323f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.48000001907f;
            } else {
              sum += -0.11020408571f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += -0.11428572237f;
            } else {
              sum += -0.50721651316f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
        sum += 0.59627383947f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
            sum += 0.55636364222f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
              sum += 0.41250002384f;
            } else {
              sum += -0.20000001788f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 144)) {
              sum += 0.45000001788f;
            } else {
              sum += -.0f;
            }
          } else {
            sum += 0.56264591217f;
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
            sum += 0.56202536821f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
              sum += -0.30000001192f;
            } else {
              sum += 0.31463414431f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
              sum += 0.28064516187f;
            } else {
              sum += -0.079768791795f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.47368425131f;
            } else {
              sum += -0.53810888529f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 338)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += -0.026315791532f;
            } else {
              sum += -0.547313869f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
              sum += 0.42524272203f;
            } else {
              sum += -0.1260869652f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 370)) {
              sum += -0.12000000477f;
            } else {
              sum += 0.50769233704f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
              sum += 0.58048778772f;
            } else {
              sum += 0.054545458406f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
          sum += 0.55920678377f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
              sum += 0.45000001788f;
            } else {
              sum += -.0f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += -0.30000001192f;
            } else {
              sum += -.0f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
            sum += 0.54418605566f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 148)) {
              sum += 0.48000001907f;
            } else {
              sum += -0.028571430594f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 224)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
              sum += 0.45000001788f;
            } else {
              sum += -.0f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
              sum += -0.56417912245f;
            } else {
              sum += -.0f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
            sum += 0.46158406138f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
              sum += 0.41096633673f;
            } else {
              sum += -0.0013703969307f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 168)) {
              sum += 0.36465990543f;
            } else {
              sum += 0.13145974278f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
              sum += -0.30556258559f;
            } else {
              sum += 0.2190015167f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            sum += 0.41236519814f;
          } else {
            sum += 0.1081424728f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
              sum += 0.016919584945f;
            } else {
              sum += 0.39840087295f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
              sum += -0.41798910499f;
            } else {
              sum += -0.06157271564f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        sum += 0.46438491344f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
            sum += 0.4543081224f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
              sum += 0.30149450898f;
            } else {
              sum += -0.23561657965f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
            sum += 0.45616769791f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += 0.24816770852f;
            } else {
              sum += 0.40827339888f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.45191472769f;
            } else {
              sum += 0.11693051457f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
              sum += -0.35905012488f;
            } else {
              sum += 0.20361334085f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
              sum += -0.087892077863f;
            } else {
              sum += 0.34251970053f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.37975546718f;
            } else {
              sum += -0.42592093349f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
              sum += -0.27336707711f;
            } else {
              sum += -0.44145965576f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.12989403307f;
            } else {
              sum += 0.40213781595f;
            }
          }
        } else {
          sum += 0.56521707773f;
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += 0.60265529156f;
            } else {
              sum += 0.43750295043f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 196)) {
              sum += 0.48723974824f;
            } else {
              sum += 0.21604940295f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += 0.46891993284f;
            } else {
              sum += 0.29473423958f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
              sum += 0.3289436996f;
            } else {
              sum += -0.12621670961f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
            sum += -0.083245567977f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
              sum += 0.22170163691f;
            } else {
              sum += 0.45253160596f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
              sum += 0.11656472832f;
            } else {
              sum += 0.47546598315f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
              sum += 0.11535431445f;
            } else {
              sum += -0.32529607415f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
          sum += 0.40052181482f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += 0.12044525892f;
            } else {
              sum += 0.42009076476f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += 0.37475886941f;
            } else {
              sum += -0.067332878709f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
            sum += 0.43209338188f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
              sum += 0.25678244233f;
            } else {
              sum += -0.1158534959f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 214)) {
              sum += 0.16639830172f;
            } else {
              sum += -0.22053213418f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 336)) {
              sum += -0.36327040195f;
            } else {
              sum += 0.47784999013f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
        sum += 0.4016508162f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
          sum += 0.39667230844f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
              sum += 0.36941984296f;
            } else {
              sum += -0.1065658927f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += 0.040947839618f;
            } else {
              sum += 0.34797400236f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
            sum += 0.46110394597f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += 0.40850818157f;
            } else {
              sum += -0.023141568527f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 350)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.15143182874f;
            } else {
              sum += -0.31593373418f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += -0.13506199419f;
            } else {
              sum += 0.4315341115f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
            sum += 0.4182009995f;
          } else {
            sum += 0.09017174691f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 298)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += 0.32858785987f;
            } else {
              sum += -0.2221840173f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += 0.2016723901f;
            } else {
              sum += 0.43938583136f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
              sum += 0.45843148232f;
            } else {
              sum += -0.088852219284f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 374)) {
              sum += -0.35304629803f;
            } else {
              sum += 0.45147868991f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 304)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 268)) {
              sum += 0.16826251149f;
            } else {
              sum += -0.41264182329f;
            }
          } else {
            sum += 0.43390321732f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
              sum += -0.10242328793f;
            } else {
              sum += 0.46901986003f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += 0.15445804596f;
            } else {
              sum += -0.22229219973f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 280)) {
            sum += 0.43733680248f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += 0.23475188017f;
            } else {
              sum += -0.019150709733f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
      sum += 0.36816358566f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += -0.13993525505f;
            } else {
              sum += 0.30786961317f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 146)) {
              sum += 0.22043991089f;
            } else {
              sum += -0.26030671597f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.48284810781f;
            } else {
              sum += -0.087777346373f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 316)) {
              sum += -0.34740173817f;
            } else {
              sum += 0.32002031803f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
            sum += 0.37102454901f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += -0.063083454967f;
            } else {
              sum += 0.2424004674f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
            sum += -0.24255247414f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
              sum += 0.2271964848f;
            } else {
              sum += 0.36123937368f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.44408717752f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += -0.29701125622f;
            } else {
              sum += 0.22636385262f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
            sum += 0.38167631626f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              sum += 0.20775321126f;
            } else {
              sum += -0.29872906208f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
              sum += 0.23115859926f;
            } else {
              sum += -0.3335416317f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
              sum += 0.28679448366f;
            } else {
              sum += -0.019614011049f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 358)) {
              sum += 0.57859033346f;
            } else {
              sum += 0.015256644227f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
              sum += -0.16848483682f;
            } else {
              sum += 0.38841274381f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
              sum += 0.38151881099f;
            } else {
              sum += 0.20704944432f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.14934980869f;
            } else {
              sum += 0.49136865139f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.388879776f;
            } else {
              sum += 0.19359888136f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 180)) {
              sum += 0.26200702786f;
            } else {
              sum += -0.14781294763f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += -0.0081046679989f;
            } else {
              sum += 0.39348584414f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
              sum += 0.34046143293f;
            } else {
              sum += -0.17299035192f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += -0.09059240669f;
            } else {
              sum += 0.36918273568f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
              sum += -0.28092375398f;
            } else {
              sum += 0.18486058712f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
      sum += 0.34606093168f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 164)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += 0.36141887307f;
            } else {
              sum += 0.085078194737f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += 0.20700936019f;
            } else {
              sum += -0.30812323093f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
              sum += -0.42215892673f;
            } else {
              sum += -0.22512121499f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += 0.3131608367f;
            } else {
              sum += 0.072208590806f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 162)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
            sum += 0.3353882432f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
              sum += 0.20905712247f;
            } else {
              sum += -0.042949557304f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 178)) {
            sum += -0.6563231945f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
              sum += 0.17472913861f;
            } else {
              sum += 0.33416599035f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += 0.0034155428875f;
            } else {
              sum += 0.35134339333f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.10160743445f;
            } else {
              sum += 0.20185144246f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += 0.34252873063f;
            } else {
              sum += 0.67201948166f;
            }
          } else {
            sum += 0.34294462204f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.24778230488f;
            } else {
              sum += -0.087483413517f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += 0.34158423543f;
            } else {
              sum += 0.097747407854f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += 0.085343137383f;
            } else {
              sum += -0.23253127933f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 346)) {
              sum += 0.10026538372f;
            } else {
              sum += 0.39522737265f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
              sum += 0.36046651006f;
            } else {
              sum += -0.01975004375f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += -0.11251217872f;
            } else {
              sum += -0.30144190788f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 306)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 232)) {
              sum += 0.17010965943f;
            } else {
              sum += -0.20680329204f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += 0.41691383719f;
            } else {
              sum += -0.051432155073f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
            sum += 0.18380407989f;
          } else {
            sum += -0.27060684562f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 286)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += 0.48398968577f;
            } else {
              sum += 0.26251244545f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 366)) {
              sum += -0.23711405694f;
            } else {
              sum += 0.24198670685f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
      sum += 0.33135953546f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
            sum += 0.31817167997f;
          } else {
            sum += 0.12908893824f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += 0.30552065372f;
            } else {
              sum += 0.039222881198f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
              sum += -0.23177029192f;
            } else {
              sum += 0.062209952623f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
          sum += 0.32256603241f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += 0.32589656115f;
            } else {
              sum += -0.0048121255822f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
              sum += 0.038887124509f;
            } else {
              sum += 0.29947078228f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += 0.4115152061f;
            } else {
              sum += -0.2563739419f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
              sum += 0.3291772902f;
            } else {
              sum += 0.17262497544f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += 0.099871225655f;
            } else {
              sum += 0.49501273036f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += 0.32525017858f;
            } else {
              sum += 0.053737457842f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.17030362785f;
            } else {
              sum += -0.079412333667f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 330)) {
              sum += -0.20623351634f;
            } else {
              sum += 0.12446574122f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 174)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
              sum += 0.18342459202f;
            } else {
              sum += 0.3662558794f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 308)) {
              sum += -0.16537971795f;
            } else {
              sum += 0.29891774058f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
              sum += 0.44014707208f;
            } else {
              sum += -0.14587567747f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += -0.13862097263f;
            } else {
              sum += 0.51265919209f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.30125206709f;
            } else {
              sum += -0.103361018f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += 0.42077431083f;
            } else {
              sum += -0.12159949541f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 136)) {
              sum += -0.18458171189f;
            } else {
              sum += 0.083200551569f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
              sum += 0.47864794731f;
            } else {
              sum += -0.064007773995f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 270)) {
            sum += 0.35926657915f;
          } else {
            sum += 0.1074359417f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
            sum += 0.33408111334f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
              sum += 0.20943102241f;
            } else {
              sum += -0.0097302738577f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
            sum += 0.29611471295f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 170)) {
              sum += -0.49807113409f;
            } else {
              sum += 0.23565281928f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
              sum += 0.19700999558f;
            } else {
              sum += 0.51380759478f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              sum += 0.16577748954f;
            } else {
              sum += -0.20965658128f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 162)) {
              sum += 0.31297391653f;
            } else {
              sum += -0.13471621275f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
              sum += -0.31882584095f;
            } else {
              sum += -0.078311681747f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
        sum += 0.32256898284f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 142)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += 0.21086385846f;
            } else {
              sum += -0.25496891141f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 194)) {
              sum += 0.28518089652f;
            } else {
              sum += 0.47102883458f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
              sum += 0.011278767139f;
            } else {
              sum += 0.29229712486f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
              sum += -0.25469267368f;
            } else {
              sum += 0.069774806499f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += 0.13630747795f;
            } else {
              sum += 0.47757548094f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.2590264082f;
            } else {
              sum += 0.29018637538f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += -0.29398038983f;
            } else {
              sum += -0.029219150543f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += 0.030161852017f;
            } else {
              sum += 0.30401316285f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
              sum += 0.18167349696f;
            } else {
              sum += -0.062863439322f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
              sum += -0.20353420079f;
            } else {
              sum += 0.30884259939f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 296)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
              sum += 0.23710171878f;
            } else {
              sum += -0.12015847117f;
            }
          } else {
            sum += 0.34692546725f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
              sum += 0.25631031394f;
            } else {
              sum += -0.22566428781f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.49674266577f;
            } else {
              sum += 0.14385461807f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.36561727524f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
              sum += -0.21047706902f;
            } else {
              sum += 0.28001967072f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 368)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
              sum += -0.18428164721f;
            } else {
              sum += 0.34048298001f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 342)) {
              sum += -0.26682135463f;
            } else {
              sum += -0.063159830868f;
            }
          }
        } else {
          sum += 0.37950369716f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
        sum += 0.31699854136f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += -0.123686634f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 144)) {
            sum += 0.29463374615f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 148)) {
              sum += -0.12939459085f;
            } else {
              sum += 0.2439931035f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            sum += 0.20475403965f;
          } else {
            sum += -0.10608979315f;
          }
        } else {
          sum += 0.31685879827f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          sum += -0.39327034354f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 158)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += 0.12782329321f;
            } else {
              sum += 0.27907174826f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += 0.24906100333f;
            } else {
              sum += -0.11638795584f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.29353141785f;
            } else {
              sum += -0.066284708679f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += 0.24371917546f;
            } else {
              sum += -0.1535795331f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 348)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
              sum += -0.066310033202f;
            } else {
              sum += -0.25851020217f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += 0.36197993159f;
            } else {
              sum += 0.012118965387f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 284)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 264)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
              sum += -0.091211356223f;
            } else {
              sum += 0.17997282743f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += -0.1113172546f;
            } else {
              sum += 0.58428537846f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += 0.15492327511f;
            } else {
              sum += -0.20896340907f;
            }
          } else {
            sum += 0.27853110433f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 158)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.2997841239f;
            } else {
              sum += 0.11638539284f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
              sum += 0.13485552371f;
            } else {
              sum += -0.12937518954f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            sum += 0.25342914462f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
              sum += 0.34757304192f;
            } else {
              sum += 1.0008963346f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
              sum += -0.024154916406f;
            } else {
              sum += 0.35865166783f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
              sum += -0.22973208129f;
            } else {
              sum += 0.23515960574f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
              sum += 0.36686348915f;
            } else {
              sum += 0.13047961891f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
              sum += 0.20680454373f;
            } else {
              sum += -0.23367233574f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.31186589599f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
        sum += 0.31293007731f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          sum += -0.43767505884f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 160)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.14826479554f;
            } else {
              sum += 0.3116761744f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
              sum += 0.17801989615f;
            } else {
              sum += -0.16957041621f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 240)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += 0.11938434094f;
            } else {
              sum += 0.45398786664f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
              sum += -0.050673514605f;
            } else {
              sum += 0.29742953181f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += 0.24635879695f;
            } else {
              sum += -0.21849939227f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += 0.076285727322f;
            } else {
              sum += 0.26862546802f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += 0.31713965535f;
            } else {
              sum += -0.039217423648f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += 0.035199966282f;
            } else {
              sum += 0.34529164433f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 326)) {
              sum += -0.16130192578f;
            } else {
              sum += 0.12894290686f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
              sum += 0.11696182936f;
            } else {
              sum += 0.31289690733f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.2637540102f;
            } else {
              sum += -0.269610852f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.3417686522f;
            } else {
              sum += 0.033417999744f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 376)) {
              sum += -0.23118636012f;
            } else {
              sum += 0.27485281229f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
              sum += -0.068959906697f;
            } else {
              sum += 0.21553969383f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 150)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
              sum += 0.28507176042f;
            } else {
              sum += -0.030855467543f;
            }
          } else {
            sum += 0.38958376646f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
            sum += -0.061950035393f;
          } else {
            sum += 0.097085177898f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30800187588f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
        sum += 0.30098614097f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          sum += -0.41303274035f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
              sum += 0.20830641687f;
            } else {
              sum += -0.53634363413f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
              sum += 0.27474784851f;
            } else {
              sum += 0.10507614911f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 252)) {
              sum += 0.14547613263f;
            } else {
              sum += 0.49746009707f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
              sum += 0.25973188877f;
            } else {
              sum += -0.20364873111f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.29801359773f;
            } else {
              sum += 0.030464263633f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
              sum += -0.12937702239f;
            } else {
              sum += 0.16852003336f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 216)) {
              sum += -0.13428536057f;
            } else {
              sum += 0.25668022037f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += 0.28416141868f;
            } else {
              sum += -0.23461413383f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += 0.3129208982f;
            } else {
              sum += -0.12151592225f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
              sum += 0.35323423147f;
            } else {
              sum += -0.10005521774f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          sum += 0.079804472625f;
        } else {
          sum += 0.32520648837f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 208)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 150)) {
              sum += 0.16769567132f;
            } else {
              sum += -0.24792951345f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += 0.47366967797f;
            } else {
              sum += -0.058992918581f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 312)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
              sum += -0.23836679757f;
            } else {
              sum += 0.17340308428f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 356)) {
              sum += 0.27365511656f;
            } else {
              sum += -0.080776795745f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30496937037f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
        sum += 0.29023763537f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
          sum += -0.38167604804f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 160)) {
              sum += 0.18174763024f;
            } else {
              sum += -0.44433245063f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
              sum += 0.2542822361f;
            } else {
              sum += 0.085326403379f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += 0.33962816f;
            } else {
              sum += 0.12586085498f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.10873676836f;
            } else {
              sum += 0.10323980451f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 274)) {
              sum += 0.36503267288f;
            } else {
              sum += 0.12128397822f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += 0.29749125242f;
            } else {
              sum += -0.075350262225f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 256)) {
              sum += 0.14207571745f;
            } else {
              sum += 0.39512127638f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.4276034534f;
            } else {
              sum += 0.029215453193f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
              sum += -0.22980247438f;
            } else {
              sum += -0.078906998038f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
              sum += -0.11271452159f;
            } else {
              sum += 0.17668128014f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          sum += 0.29639416933f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
              sum += 0.26088443398f;
            } else {
              sum += -0.23278604448f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 262)) {
              sum += 0.32711070776f;
            } else {
              sum += 0.062291059643f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
              sum += 0.078410580754f;
            } else {
              sum += 0.35302567482f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
              sum += 0.19492483139f;
            } else {
              sum += -0.07976616919f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.21246422827f;
            } else {
              sum += -0.095556743443f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += 0.21996213496f;
            } else {
              sum += -0.048498600721f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.30245047808f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
            sum += 0.022593518719f;
          } else {
            sum += 0.25578346848f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
            sum += 0.18456922472f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.10001706332f;
            } else {
              sum += -0.26696276665f;
            }
          }
        }
      } else {
        sum += 0.26830878854f;
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 152)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
              sum += 0.44804051518f;
            } else {
              sum += 0.036223966628f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
              sum += 0.34529361129f;
            } else {
              sum += 0.01596715115f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.32284170389f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
              sum += -0.1153504923f;
            } else {
              sum += 0.31035706401f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
              sum += 0.25268268585f;
            } else {
              sum += -0.063464812934f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.35258862376f;
            } else {
              sum += 0.020229788497f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
            sum += 0.31302803755f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
              sum += -0.028427625075f;
            } else {
              sum += 0.18154400587f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
              sum += -0.27036511898f;
            } else {
              sum += 0.12833492458f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
              sum += 0.0078281769529f;
            } else {
              sum += 0.2886814177f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 378)) {
              sum += -0.2331097573f;
            } else {
              sum += 0.2284502089f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
              sum += 0.26336878538f;
            } else {
              sum += 0.028167013079f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += 0.31838473678f;
        } else {
          sum += 0.088538818061f;
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        sum += 0.019111292437f;
      } else {
        sum += 0.3095433116f;
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 166)) {
            sum += 0.29054686427f;
          } else {
            sum += -0.062540099025f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += -0.26660171151f;
            } else {
              sum += 0.10789568722f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.16962954402f;
            } else {
              sum += -0.21433390677f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
          sum += 0.28237229586f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
            sum += 0.20490367711f;
          } else {
            sum += -0.029448660091f;
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
        sum += 0.031964253634f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
          sum += 0.089045025408f;
        } else {
          sum += 0.29141044617f;
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += 0.26430574059f;
            } else {
              sum += 0.021244395524f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
              sum += 0.27009898424f;
            } else {
              sum += -0.088480785489f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 254)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 226)) {
              sum += -0.0054421038367f;
            } else {
              sum += -0.27152681351f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 260)) {
              sum += 0.42733317614f;
            } else {
              sum += 0.013981256634f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.13593617082f;
            } else {
              sum += 0.052909709513f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
              sum += -0.26113757491f;
            } else {
              sum += 0.043405558914f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 362)) {
              sum += 0.45513427258f;
            } else {
              sum += -0.22449243069f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 368)) {
              sum += -0.24383848906f;
            } else {
              sum += 0.30309408903f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.29821056128f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
          sum += 0.10066950321f;
        } else {
          sum += -0.18057619035f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
          sum += 0.0060668960214f;
        } else {
          sum += 0.25129321218f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 140)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 186)) {
              sum += 0.13297361135f;
            } else {
              sum += 0.31627094746f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.14054952562f;
            } else {
              sum += -0.13001160324f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.28319743276f;
            } else {
              sum += 0.068825848401f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
              sum += 0.050638977438f;
            } else {
              sum += -0.09581399709f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
              sum += 0.14537425339f;
            } else {
              sum += 0.40534180403f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              sum += 0.14215309918f;
            } else {
              sum += -0.081960342824f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
              sum += -0.031070714816f;
            } else {
              sum += -0.17319685221f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
              sum += 0.25147050619f;
            } else {
              sum += -0.14213716984f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 146)) {
          sum += 0.22914461792f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += -0.52364724874f;
            } else {
              sum += -0.14192001522f;
            }
          } else {
            sum += 0.16752135754f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
              sum += 0.28700149059f;
            } else {
              sum += 0.026311831549f;
            }
          } else {
            sum += 0.30714821815f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
            sum += 0.04749102518f;
          } else {
            sum += -0.0066538578831f;
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      sum += -0.0013418934541f;
    } else {
      sum += 0.30578750372f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 290)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 266)) {
              sum += -0.021974438801f;
            } else {
              sum += 0.18148121238f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
              sum += 0.22910706699f;
            } else {
              sum += -0.19646914303f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 328)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += 0.033647049218f;
            } else {
              sum += -0.31516751647f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 334)) {
              sum += 0.49453878403f;
            } else {
              sum += -0.27364724874f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 354)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 170)) {
              sum += 0.41747772694f;
            } else {
              sum += 0.11262277514f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.24812667072f;
            } else {
              sum += 0.083146356046f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += 0.10865762085f;
            } else {
              sum += -0.18702049553f;
            }
          } else {
            sum += 0.30960020423f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 302)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              sum += 0.20835267007f;
            } else {
              sum += -0.040410026908f;
            }
          } else {
            sum += 0.44848951697f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 172)) {
            sum += -0.50268369913f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 230)) {
              sum += 0.1474455446f;
            } else {
              sum += -0.06854210794f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 352)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            sum += 0.081036612391f;
          } else {
            sum += 0.30470973253f;
          }
        } else {
          sum += 0.050120886415f;
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
        sum += 0.1778357625f;
      } else {
        sum += -0.070805907249f;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
          sum += 0.30217704177f;
        } else {
          sum += 0.089588016272f;
        }
      } else {
        sum += 0.023229129612f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 154)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
          sum += 0.32661831379f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 344)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 282)) {
              sum += -0.0011155945249f;
            } else {
              sum += -0.16810891032f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 360)) {
              sum += 0.22739514709f;
            } else {
              sum += 0.011336175725f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 176)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.12618806958f;
            } else {
              sum += 0.12049751729f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.21689988673f;
            } else {
              sum += 0.21744789183f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
              sum += 0.19312120974f;
            } else {
              sum += -0.18713161349f;
            }
          } else {
            sum += 0.40246132016f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
          sum += 0.29462102056f;
        } else {
          sum += 0.068341061473f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 204)) {
              sum += -0.26912945509f;
            } else {
              sum += 0.17434921861f;
            }
          } else {
            sum += -0.59223365784f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 272)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += 0.16256569326f;
            } else {
              sum += 0.47128757834f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 294)) {
              sum += -0.26192995906f;
            } else {
              sum += 0.26835289598f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
    sum += 0.2910348475f;
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 234)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
              sum += 0.18881072104f;
            } else {
              sum += 0.46073132753f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 258)) {
              sum += -0.1711794585f;
            } else {
              sum += 0.16504314542f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 200)) {
            sum += -0.15606100857f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += 0.27315688133f;
            } else {
              sum += 0.0011454914929f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
              sum += 0.083217181265f;
            } else {
              sum += -0.21692939103f;
            }
          } else {
            sum += 0.37736907601f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 202)) {
              sum += 0.33553639054f;
            } else {
              sum += -0.10603530705f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
              sum += -0.13305352628f;
            } else {
              sum += 0.15221844614f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        sum += 0.31138759851f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 172)) {
              sum += -0.35828393698f;
            } else {
              sum += 0.016245393082f;
            }
          } else {
            sum += 0.28101196885f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 156)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += 0.10203251243f;
            } else {
              sum += -0.017280641943f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
              sum += -0.14075753093f;
            } else {
              sum += 0.25254973769f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      sum += 0.00026019715006f;
    } else {
      sum += 0.29829844832f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += 0.21441997588f;
            } else {
              sum += -0.1851811111f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
              sum += 0.14851462841f;
            } else {
              sum += 0.54897964001f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 332)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 288)) {
              sum += -0.0042598098516f;
            } else {
              sum += -0.29202583432f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += 0.30307394266f;
            } else {
              sum += 0.001706458861f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 380)) {
              sum += -0.16258987784f;
            } else {
              sum += 0.2365962714f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 236)) {
              sum += 0.25389555097f;
            } else {
              sum += -0.10997493565f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
              sum += 0.18817676604f;
            } else {
              sum += -0.23622897267f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
              sum += 0.45003786683f;
            } else {
              sum += 0.17612302303f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
          sum += 0.27837663889f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += 0.26049029827f;
            } else {
              sum += 0.053335819393f;
            }
          } else {
            sum += -0.087811872363f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 222)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 210)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 142)) {
              sum += 0.090351678431f;
            } else {
              sum += -0.12589886785f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 212)) {
              sum += 0.67589664459f;
            } else {
              sum += 0.14906132221f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 238)) {
              sum += -0.06506562978f;
            } else {
              sum += -0.41529884934f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
              sum += 0.19902029634f;
            } else {
              sum += -0.0097615327686f;
            }
          }
        }
      }
    }
  }
  if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        sum += 0.00021270148864f;
      } else {
        sum += 0.29243484139f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 192)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 138)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
              sum += 0.031302675605f;
            } else {
              sum += 0.28101474047f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
              sum += 0.20346190035f;
            } else {
              sum += -0.16267749667f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
              sum += 0.064719751477f;
            } else {
              sum += -0.30328190327f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
              sum += -0.15832565725f;
            } else {
              sum += 0.72634279728f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 198)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            sum += 0.1932798624f;
          } else {
            sum += 0.83954691887f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += 0.24876879156f;
            } else {
              sum += -0.077183783054f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += 0.098757609725f;
            } else {
              sum += 0.35351383686f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 218)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += 0.02598394081f;
            } else {
              sum += -0.22506292164f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 206)) {
              sum += 0.0046538626775f;
            } else {
              sum += 0.2914672792f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 250)) {
              sum += -0.28941762447f;
            } else {
              sum += 0.053543701768f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += 0.11541810632f;
            } else {
              sum += -0.26773950458f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 364)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
              sum += 0.3855740428f;
            } else {
              sum += 0.10862663388f;
            }
          } else {
            sum += -0.097704708576f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
              sum += -0.0092506986111f;
            } else {
              sum += 0.35910999775f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 376)) {
              sum += -0.27484148741f;
            } else {
              sum += 0.19571940601f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
            sum += 0.16479443014f;
          } else {
            sum += 0.78484398127f;
          }
        } else {
          sum += 0.11298400164f;
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              sum += 0.035484261811f;
            } else {
              sum += 0.30142939091f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
              sum += -0.21092499793f;
            } else {
              sum += 0.014889364131f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            sum += 0.31012752652f;
          } else {
            sum += 0.050720781088f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
    sum += 0.27915808558f;
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
      sum += 0.29678750038f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 174)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
              sum += -0.074208900332f;
            } else {
              sum += -0.36299234629f;
            }
          } else {
            sum += 0.065479718149f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
            sum += 0.026387715712f;
          } else {
            sum += 0.28439772129f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 244)) {
              sum += 0.32198783755f;
            } else {
              sum += 0.016066005453f;
            }
          } else {
            sum += 0.0067516160198f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.051760829985f;
            } else {
              sum += 0.02301171422f;
            }
          } else {
            sum += 0.28822526336f;
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
  // return sum;
}