#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  -0.52648652f, -0.2146204f, -0.10128386f, -0.097543418f, -0.095409214f, 
  -0.027150793f, -0.0058837128f, -0.0038916003f, -0.0017034251f, 0.037431918f, 
  0.069449984f, 0.074999072f, 0.10042246f, 0.1588143f, 0.19183803f, 0.19318861f, 
  0.43851173f, 0.61062729f, 0.63582671f, 0.77108848f, 2.5f, 3.5f, 5.5f, 8.5f, 11.5f, 
  12.5f, 13.5f, 14.5f, 15.5f, 16.0f, 16.5f, 17.5f, 18.5f, 19.5f, 20.5f, 22.5f, 23.0f, 
  -0.056768321f, 0.38987774f, 0.51611912f, 0.52133441f, 0.57896918f, 0.58773905f, 
  0.65109146f, 0.69222248f, 0.70158327f, 0.74904341f, 0.75019586f, 0.78271127f, 
  0.78296602f, 0.80738527f, 0.81519103f, 0.82123363f, 0.82610333f, 0.84714699f, 
  0.86189038f, 0.87643623f, 0.88666368f, 0.89477623f, 0.0075410353f, 0.0084997592f, 
  0.0092710834f, 0.0096492842f, 0.01559051f, 0.016025122f, 0.016213238f, 0.01698618f, 
  0.017466689f, 0.019523196f, 0.03483288f, 0.040716205f, 0.07866843f, 0.16033831f, 
  0.21126342f, 6.2279844f, 102.47742f, 211.12714f, 1509.8938f, 1728.9646f, 5684.6792f, 
  0.0029608253f, 0.0030534789f, 0.003963307f, 0.010960404f, 0.033579633f, 
  0.041517735f, 0.045129366f, 0.047468185f, 0.049083497f, 0.080730699f, 0.11314723f, 
  0.13563651f, 0.15639621f, 0.16994831f, 0.19684446f, 0.19993994f, 0.29532388f, 
  0.35195398f, 0.43444234f, 0.5143261f, 0.55208594f, 0.79768574f, 1.4350078f, 
  1.5244744f, 1.7023578f, 1.715358f, 4.3985796f, 4.6091614f, 5.639905f, 8.2637043f, 
  10.730305f, 14.290804f, 51.143433f, 69.150948f, 0.049370795f, 0.062906995f, 
  0.075490907f, 0.07592538f, 0.076496996f, 0.081060678f, 0.081870101f, 0.082254007f, 
  0.085235409f, 0.086156681f, 0.099252485f, 0.1264095f, 0.14403298f, 0.1496771f, 
  0.15535735f, 0.16320671f, 0.18174186f, 0.21220532f, 0.9013254f, 1.2843988f, 
  1.419394f, 3.3355f, 6.4197598f, 23.429592f, 31.518074f, 31.536121f, 41.615143f, 
  2.7246296f, 2.7247336f, 2.8381343f, 2.9546919f, 3.0478616f, 3.0570331f, 3.124187f, 
  3.1376684f, 3.1384788f, 3.1405683f, 3.1476948f, 3.1656976f, 3.2628736f, 3.2839317f, 
  3.2997131f, 3.3139019f, 3.3180056f, 3.3371816f, 3.3488708f, 3.360486f, 3.3691688f, 
  3.3723619f, 3.4324951f, 3.4461646f, 3.4588864f, 3.4608521f, 3.4735236f, 3.4958408f, 
  3.5019603f, 3.5609956f, 3.5801539f, 3.5871916f, 3.5976896f, 3.605217f, 3.6093688f, 
  3.6123567f, 3.6395168f, 3.6531591f, 3.6680698f, 3.6752608f, 3.6786466f, 3.6791835f, 
  3.6862981f, 3.7256594f, 3.7773447f, 3.7840705f, 3.8468978f, 3.8495858f, 3.8643782f, 
  3.8721638f, 3.8725481f, 3.8729033f, 3.8735495f, 3.920435f, 3.9230835f, 3.9303951f, 
  3.9306021f, 3.9695892f, 3.9740429f, 3.9949608f, 4.0203915f, 4.0548973f, 4.0744343f, 
  4.0770674f, 4.0803933f, 4.0804653f, 4.0884891f, 4.185276f, 0.22265625f, 0.49609375f, 
  0.55078125f, 0.60546875f, 0.62109375f, 0.62890625f, 0.64453125f, 0.65234375f, 
  0.66796875f, 0.67578125f, 0.68359375f, 0.69140625f, 0.70703125f, 0.71484375f, 
  0.76171875f, 0.45255834f, 0.76963794f, 0.8244909f, 0.99278814f, 1.0141706f, 
  1.0256101f, 1.0289781f, 1.5669631f, 1.7215471f, 1.7671435f, 1.7809937f, 1.7937927f, 
  1.8418679f, 1.8579857f, 1.8834668f, 1.9080186f, 1.9151177f, 1.9266007f, 1.9292543f, 
  1.9586391f, 1.9587033f, 1.9685948f, 1.9773952f, 1.9776518f, 1.9788053f, 1.9794477f, 
  2.0144601f, 2.0190086f, 2.0400612f, 2.0406408f, 2.0537703f, 2.0571685f, 2.0668216f, 
  2.0717573f, 2.073863f, 2.0868468f, 2.0875335f, 2.0877512f, 2.0931971f, 2.1073999f, 
  2.1216836f, 2.1488659f, 2.1513476f, 2.1563373f, 2.1603673f, 2.2436607f, 2.259475f, 
  2.265712f, 2.2660596f, 2.2751298f, 2.2831941f, 2.2855225f, 0.46026191f, 0.47665071f, 
  0.50438094f, 0.51388597f, 0.55388892f, 0.5548985f, 0.59768182f, 0.60690475f, 
  0.65334332f, 0.80919445f, 0.89243108f, 0.92055142f, 1.1166439f, 1.1202228f, 
  1.1926095f, 1.2307818f, 1.2562144f, 1.2643809f, 1.3317158f, 1.4593391f, 1.6024506f, 
  1.7837433f, 2.1376762f, 2.5461659f, 2.625802f, 2.8208485f, 2.861105f, 2.915f, 
  3.7601738f, 6.129283f, 12.250261f, 22.170197f, 88.398224f, 0.32733834f, 0.33603334f, 
  0.35047275f, 0.35694546f, 0.37394783f, 0.39200002f, 0.40226316f, 0.4417091f, 
  0.4443205f, 0.46946153f, 0.47436363f, 0.50011432f, 0.5088762f, 0.51922226f, 
  0.53546429f, 0.5514667f, 0.57620001f, 0.62986666f, 0.63024759f, 0.63498485f, 
  0.63569045f, 0.69021332f, 0.76006663f, 0.9284969f, 0.95470583f, 0.95565218f, 
  0.9890942f, 0.99948335f, 1.26256f, 1.3671112f, 1.4021897f, 1.4108572f, 1.4368596f, 
  1.4455f, 1.5780545f, 1.848262f, 1.9623067f, 1.9663463f, 2.5303078f, 4.6259212f, 
  8.8834095f, 11.399145f, 12.583366f, 15.046667f, 20.997566f, 21.555573f, 29.501318f, 
  106.90692f, 184.21445f, 861.30457f, 0.010504039f, 0.1909532f, 0.19096097f, 
  0.20333348f, 0.22320066f, 0.2261593f, 0.23998f, 0.24465667f, 0.5929786f, 
  0.63626164f, 0.64041984f, 0.65473843f, 1.0260218f, 1.0741284f, 1.1701391f, 
  1.4433666f, 1.4437153f, 1.5931647f, 1.8128006f, 1.9102308f, 2.2316911f, 2.8179247f, 
  20.667294f, 28.223679f, 35.580101f, 43.426785f, 44.949158f, 54.597618f, 55.054333f, 
  60.015907f, 79.233543f, 271.75201f, 19322.676f, 19449.992f, 19642.281f, 29673.223f, 
  40252.555f, 43532.164f, 51268.148f, 0.03873292f, 0.25496927f, 0.27573264f, 
  0.50496972f, 0.6253314f, 0.62950593f, 0.69428992f, 0.71593088f, 0.72082263f, 
  0.75413334f, 0.7671783f, 0.85601908f, 0.89674616f, 0.93251729f, 0.93591833f, 
  0.93614286f, 0.9717778f, 1.0018826f, 1.0923555f, 1.1869166f, 1.1925616f, 1.3781333f, 
  1.4089391f, 1.4207618f, 1.4285042f, 1.4286225f, 1.4824545f, 1.5589714f, 1.5602515f, 
  1.6568f, 1.713616f, 2.148031f, 2.3143525f, 2.4331574f, 3.1896191f, 3.4932666f, 
  4.723568f, 6.6004262f, 6.6722989f, 9.364316f, 19.925665f, 42.980751f, 52.610596f, 
  63.470268f, 66.698883f, 87.178345f, 0.00390625f, 0.03515625f, 0.04296875f, 
  0.06640625f, 0.15234375f, 0.16015625f, -4981.1797f, -4981.0679f, -4980.7041f, 
  -4980.6963f, -4980.3516f, -4980.2676f, -4980.0996f, -4977.1123f, -4977.04f, 
  -4976.8604f, -4955.6079f, -3769.772f, -3591.5161f, -2271.6519f, -2064.7959f, 
  -2043.9399f, -1735.264f, -1641.644f, -1078.048f, -1015.9041f, -878.97998f, 
  -862.31598f, -811.716f, -636.58398f, -630.43201f, -609.90802f, -597.71198f, 
  -430.59198f, -408.34799f, -400.52802f, -394.64398f, -390.09198f, -388.31201f, 
  -367.90399f, -183.328f, -159.45999f, -71.596001f, -68.400002f, -13.144001f, 12.648f, 
  26.456001f, 49.739998f, 92.968002f, 102.696f, 129.20801f, 139.44f, 170.36401f, 
  179.03601f, 181.14799f, 181.2f, 187.856f, 192.388f, 192.76401f, 194.104f, 194.68399f, 
  194.82001f, 195.34f, 196.88f, 197.992f, 198.76801f, 201.94f, 204.46399f, 325.82397f, 
  331.444f, 341.82397f, 391.69202f, 396.0f, 397.276f, 467.92798f, 482.952f, 490.34003f, 
  514.77197f, 521.93604f, 531.388f, 534.28796f, 537.75201f, 541.32397f, 543.45203f, 
  556.20801f, 559.88403f, 578.67603f, 578.98401f, 586.91199f, 587.03198f, 598.24799f, 
  639.508f, 639.57605f, 642.57202f, 654.41199f, 673.58801f, 869.25201f, 953.47601f, 
  1056.5959f, 1223.02f, 1303.032f, 1777.3879f, 1840.304f, 1883.1f, 1917.672f, 
  1928.564f, 2264.6719f, 2390.8398f, 2391.0601f, 2552.46f, 2555.064f, 2773.0281f, 
  3777.26f, 3789.532f, 3806.8599f, 3845.4561f, 3846.6401f, 4247.668f, 4373.1919f, 
  5008.6318f, 5049.8438f, 5144.5039f, 5468.4443f, 6168.7881f, 6476.7002f, 6491.7842f, 
  6501.936f, 6514.1357f, 6527.7202f, 6593.688f, 6821.5439f, 6879.6841f, 6889.8281f, 
  6972.6318f, 8075.2959f, 8301.0996f, 9042.832f, 9044.9639f, 9238.7402f, 9256.0684f, 
  9408.4688f, 9748.6318f, 10117.08f, 10117.22f, 
};

static const int th_len[] = {
  20, 17, 22, 21, 34, 27, 68, 15, 52, 33, 50, 39, 46, 6, 138, 
};
static const int th_begin[] = {
  0, 20, 37, 59, 80, 114, 141, 209, 224, 276, 309, 359, 398, 444, 450, 
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
  if (offset == 588 || val < array[0]) {
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

  for (int i = 0; i < 15; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }

  if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
          sum += 0.5731343627f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 136)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
              sum += 0.33333337307f;
            } else {
              sum += -0.375f;
            }
          } else {
            sum += 0.43636366725f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 50)) {
          sum += 0.38181820512f;
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 2)) {
            sum += 0.27272728086f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += 0.15000000596f;
            } else {
              sum += -0.5675675869f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            sum += -0.36000001431f;
          } else {
            sum += 0.59347826242f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += -0.15000000596f;
          } else {
            sum += -0.56417912245f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
              sum += 0.58706200123f;
            } else {
              sum += 0.24444444478f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
              sum += 0.40327867866f;
            } else {
              sum += -0.41408452392f;
            }
          }
        } else {
          sum += 0.59634327888f;
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 42)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        sum += 0.59475982189f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            sum += -0.0f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += -0.54418605566f;
            } else {
              sum += -0.15000000596f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 28)) {
              sum += 0.24000000954f;
            } else {
              sum += -0.30000001192f;
            }
          } else {
            sum += 0.53333336115f;
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 248)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 6)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
            sum += -0.27272728086f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
              sum += 0.30731707811f;
            } else {
              sum += 0.56210529804f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 86)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
              sum += -0.019354838878f;
            } else {
              sum += -0.57637798786f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              sum += 0.55263161659f;
            } else {
              sum += -0.22500000894f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 266)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += -0.56896555424f;
            } else {
              sum += 0.30000001192f;
            }
          } else {
            sum += 0.57142859697f;
          }
        } else {
          sum += 0.58831173182f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
          sum += 0.45599451661f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 130)) {
              sum += -0.35859262943f;
            } else {
              sum += 0.017967395484f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
              sum += 0.40247043967f;
            } else {
              sum += 0.084429100156f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 50)) {
          sum += 0.31697505713f;
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 0)) {
            sum += 0.29112911224f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
              sum += -0.43696585298f;
            } else {
              sum += 0.14023253322f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            sum += -0.30163022876f;
          } else {
            sum += 0.46020504832f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            sum += -0.12602870166f;
          } else {
            sum += -0.44429567456f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.45427793264f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
              sum += -0.26075324416f;
            } else {
              sum += 0.33864587545f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
            sum += 0.46318247914f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
              sum += -0.17119134963f;
            } else {
              sum += 0.40750929713f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 42)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        sum += 0.46107622981f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            sum += 0.09800811857f;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 60)) {
              sum += -0.024807339534f;
            } else {
              sum += -0.43829238415f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            sum += 0.045142393559f;
          } else {
            sum += 0.41811522841f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 126)) {
              sum += 0.25987645984f;
            } else {
              sum += -0.38302403688f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
              sum += 0.41005814075f;
            } else {
              sum += -0.07994183898f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 262)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 94)) {
              sum += -0.44372305274f;
            } else {
              sum += 0.27989852428f;
            }
          } else {
            sum += 0.43658202887f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
            sum += -0.11137831956f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 210)) {
              sum += 0.61690318584f;
            } else {
              sum += 0.45487174392f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 202)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 60)) {
              sum += -0.36571973562f;
            } else {
              sum += 0.55073493719f;
            }
          } else {
            sum += 0.44126054645f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
          sum += 0.39323538542f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 134)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
              sum += 0.25144374371f;
            } else {
              sum += -0.33591476083f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
              sum += -0.010952714831f;
            } else {
              sum += 0.36100554466f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 78)) {
          sum += 0.3062928021f;
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 122)) {
              sum += -0.21430498362f;
            } else {
              sum += 0.38019877672f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += -0.38727208972f;
            } else {
              sum += 0.1407263875f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
              sum += 0.23283530772f;
            } else {
              sum += 0.39837434888f;
            }
          } else {
            sum += 0.017823897302f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
              sum += 0.02747050114f;
            } else {
              sum += 0.40681356192f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
              sum += -0.31946331263f;
            } else {
              sum += 0.22528375685f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
              sum += -0.23738564551f;
            } else {
              sum += 0.39983662963f;
            }
          } else {
            sum += -0.3847476244f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            sum += 0.063617736101f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 22)) {
              sum += 0.40201339126f;
            } else {
              sum += 0.34677091241f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 48)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 44)) {
          sum += 0.39964857697f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
            sum += 0.32951846719f;
          } else {
            sum += -0.1041989252f;
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 36)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 32)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += 0.38077306747f;
            } else {
              sum += 0.079589098692f;
            }
          } else {
            sum += -0.05099677667f;
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 88)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 60)) {
              sum += -0.096621610224f;
            } else {
              sum += -0.38085219264f;
            }
          } else {
            sum += 0.13725581765f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 260)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 90)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.39333918691f;
            } else {
              sum += 0.32288011909f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 76)) {
              sum += -0.16336098313f;
            } else {
              sum += 0.40829437971f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 264)) {
            sum += 0.094139516354f;
          } else {
            sum += 0.38537171483f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 58)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 8)) {
              sum += 0.3798352778f;
            } else {
              sum += 0.64298218489f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += 0.12015447766f;
            } else {
              sum += 0.44381383061f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 238)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 58)) {
              sum += -0.31861308217f;
            } else {
              sum += 0.47785499692f;
            }
          } else {
            sum += 0.41213083267f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
        sum += 0.36376851797f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            sum += 0.29549461603f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 50)) {
              sum += 0.26302796602f;
            } else {
              sum += -0.32419025898f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
            sum += 0.37922695279f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
              sum += 0.24104996026f;
            } else {
              sum += -0.24680021405f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            sum += -0.20153750479f;
          } else {
            sum += 0.36458131671f;
          }
        } else {
          sum += -0.3475073278f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
          sum += 0.36921563745f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += 0.19857382774f;
            } else {
              sum += 0.36109793186f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
              sum += -0.14711669087f;
            } else {
              sum += 0.30935373902f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 48)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            sum += 0.36550468206f;
          } else {
            sum += 0.12405896932f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 22)) {
            sum += 0.16593459249f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 28)) {
              sum += 0.030497493222f;
            } else {
              sum += -0.33695173264f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 260)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 64)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.35375857353f;
            } else {
              sum += 0.25620052218f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 74)) {
              sum += -0.15793761611f;
            } else {
              sum += 0.37713578343f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 264)) {
            sum += 0.081217817962f;
          } else {
            sum += 0.3477614522f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 42)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
              sum += 0.38024634123f;
            } else {
              sum += 0.040535192937f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
              sum += 0.43380361795f;
            } else {
              sum += 0.28673651814f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += 0.41172653437f;
            } else {
              sum += -0.026806348935f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 228)) {
              sum += -0.18970304728f;
            } else {
              sum += 0.35826790333f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 120)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 46)) {
              sum += 0.46236887574f;
            } else {
              sum += 0.13342492282f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 244)) {
              sum += -0.31162324548f;
            } else {
              sum += 0.35132962465f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 162)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 38)) {
              sum += 0.27546161413f;
            } else {
              sum += 0.60184383392f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += -0.19230170548f;
            } else {
              sum += 0.20516964793f;
            }
          }
        }
      }
    }
  }
  if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 116)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 86)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 82)) {
              sum += 0.32195454836f;
            } else {
              sum += 0.073451071978f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 8)) {
              sum += 0.19913052022f;
            } else {
              sum += -0.27486509085f;
            }
          }
        } else {
          sum += 0.40754446387f;
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 24)) {
              sum += -0.22418953478f;
            } else {
              sum += 0.13740858436f;
            }
          } else {
            sum += 0.37598127127f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 34)) {
              sum += -0.31884238124f;
            } else {
              sum += -0.0014887591824f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 188)) {
              sum += -0.13286326826f;
            } else {
              sum += 0.32968783379f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
            sum += -0.1463713944f;
          } else {
            sum += 0.33948388696f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 0)) {
              sum += -0.089669808745f;
            } else {
              sum += -0.31502246857f;
            }
          } else {
            sum += 0.0086248163134f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += 0.38403204083f;
            } else {
              sum += -0.16125249863f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 92)) {
              sum += 0.17472702265f;
            } else {
              sum += 0.35660460591f;
            }
          }
        } else {
          sum += 0.34611392021f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 40)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 64)) {
          sum += 0.34251198173f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 72)) {
              sum += -0.090062081814f;
            } else {
              sum += -0.31946778297f;
            }
          } else {
            sum += 0.060706891119f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += 0.5058785677f;
            } else {
              sum += -0.20256440341f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 46)) {
              sum += 0.48567271233f;
            } else {
              sum += 0.019999209791f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 68)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 272)) {
              sum += -0.32821565866f;
            } else {
              sum += 0.31248027086f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += 0.34438556433f;
            } else {
              sum += 0.030488688499f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
            sum += -0.31988739967f;
          } else {
            sum += 0.20607194304f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
              sum += 0.36212313175f;
            } else {
              sum += 0.13347414136f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 68)) {
              sum += 0.21820014715f;
            } else {
              sum += -0.15415132046f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
            sum += -0.32362884283f;
          } else {
            sum += 0.31244918704f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
              sum += -0.097076371312f;
            } else {
              sum += 0.27712321281f;
            }
          } else {
            sum += 0.35496386886f;
          }
        }
      }
    }
  }
  if (!(data[12].missing != -1) || (data[12].qvalue < 20)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 2)) {
              sum += 0.2378679961f;
            } else {
              sum += -0.07062599808f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
              sum += 0.23785088956f;
            } else {
              sum += 0.42797973752f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 2)) {
            sum += 0.2828848362f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
              sum += -0.28363388777f;
            } else {
              sum += 0.046931110322f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += -0.30526354909f;
            } else {
              sum += 0.12222804874f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 40)) {
              sum += 0.4063616693f;
            } else {
              sum += 0.093762718141f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 76)) {
            sum += 0.2927095592f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += 0.21094292402f;
            } else {
              sum += -0.30055212975f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 6)) {
          sum += 0.33160540462f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 20)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 14)) {
              sum += 0.29873299599f;
            } else {
              sum += -0.18291787803f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += -0.15511362255f;
            } else {
              sum += 0.38606950641f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
              sum += -0.15052904189f;
            } else {
              sum += 0.32476580143f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += -0.2956507504f;
            } else {
              sum += 0.018405891955f;
            }
          }
        } else {
          sum += 0.33071151376f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 40)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 64)) {
          sum += 0.3245343864f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
              sum += -0.081757374108f;
            } else {
              sum += -0.29234790802f;
            }
          } else {
            sum += 0.048834647983f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 252)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
              sum += 0.54744923115f;
            } else {
              sum += -0.097745992243f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 62)) {
              sum += -0.31096351147f;
            } else {
              sum += 0.01546222996f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 270)) {
              sum += -0.27461698651f;
            } else {
              sum += 0.31048420072f;
            }
          } else {
            sum += 0.45085796714f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 132)) {
            sum += 0.21724794805f;
          } else {
            sum += -0.31304657459f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              sum += 0.068504601717f;
            } else {
              sum += 0.3382562995f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 128)) {
              sum += 0.3284791708f;
            } else {
              sum += -0.039547257125f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
          sum += -0.11068992317f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += 0.34069731832f;
            } else {
              sum += 0.099144354463f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
              sum += 0.27710965276f;
            } else {
              sum += -0.18803781271f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 48)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
          sum += 0.32493701577f;
        } else {
          sum += 0.073917157948f;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 24)) {
          sum += 0.11172223836f;
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 28)) {
            sum += 0.019368061796f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.06987337023f;
            } else {
              sum += -0.28461426497f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 254)) {
              sum += -0.13481840491f;
            } else {
              sum += 0.29132336378f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.45044526458f;
            } else {
              sum += -0.07053578645f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 66)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 44)) {
              sum += -0.054831061512f;
            } else {
              sum += -0.30619615316f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += 0.32060742378f;
            } else {
              sum += 0.023393774405f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          sum += 0.31594964862f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
            sum += 0.21101792157f;
          } else {
            sum += -0.26895821095f;
          }
        }
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].qvalue < 40)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 4)) {
            sum += 0.29089155793f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 118)) {
              sum += -0.24813662469f;
            } else {
              sum += 0.046529367566f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += 0.22099760175f;
            } else {
              sum += 0.48100379109f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 32)) {
              sum += 0.16904845834f;
            } else {
              sum += -0.18283195794f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
              sum += -0.10494560003f;
            } else {
              sum += 0.31270977855f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += -0.259578228f;
            } else {
              sum += 0.015626793727f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
            sum += 0.32395190001f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += 0.32640692592f;
            } else {
              sum += 0.093361414969f;
            }
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 52)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 236)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 48)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 42)) {
              sum += 0.41892838478f;
            } else {
              sum += 0.046978659928f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 144)) {
              sum += 0.027967194095f;
            } else {
              sum += -0.31811451912f;
            }
          }
        } else {
          sum += 0.33276557922f;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 176)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
            sum += -0.12261018902f;
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 6)) {
              sum += 0.16045072675f;
            } else {
              sum += 0.54291397333f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 226)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 62)) {
              sum += 0.16229230165f;
            } else {
              sum += -0.27648106217f;
            }
          } else {
            sum += 0.30432617664f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
    if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 110)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 84)) {
            sum += 0.29615440965f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.17841017246f;
            } else {
              sum += -0.22439303994f;
            }
          }
        } else {
          sum += 0.36356285214f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += 0.19658200443f;
            } else {
              sum += -0.21968190372f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += 0.0021478519775f;
            } else {
              sum += 0.3515393734f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 198)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
              sum += -0.23628558218f;
            } else {
              sum += 0.33504265547f;
            }
          } else {
            sum += 0.34754067659f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 80)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.095207229257f;
            } else {
              sum += -0.20613819361f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += -0.079176865518f;
            } else {
              sum += 0.33013442159f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 158)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 90)) {
              sum += 0.037070475519f;
            } else {
              sum += 0.47246846557f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.32489106059f;
            } else {
              sum += -0.11174236983f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 54)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += 0.070389226079f;
            } else {
              sum += 0.36054188013f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 52)) {
              sum += 0.088696300983f;
            } else {
              sum += -0.22721487284f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 272)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
              sum += -0.28187969327f;
            } else {
              sum += 0.43751072884f;
            }
          } else {
            sum += 0.29000249505f;
          }
        }
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].qvalue < 30)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 4)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
            sum += 0.30294209719f;
          } else {
            sum += 0.077184334397f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
            sum += 0.10151094943f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += -0.24901103973f;
            } else {
              sum += 0.013266617432f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
          sum += 0.31697106361f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
              sum += 0.026315685362f;
            } else {
              sum += 0.31342864037f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
              sum += -0.36362051964f;
            } else {
              sum += 0.13345259428f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 230)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 154)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
            sum += -0.13290075958f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += 0.30689305067f;
            } else {
              sum += 0.070832982659f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 40)) {
              sum += 0.0038719526492f;
            } else {
              sum += 0.29768428206f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
              sum += 0.18640133739f;
            } else {
              sum += -0.28762850165f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
          sum += 0.32381263375f;
        } else {
          sum += 0.10005129874f;
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
    if (!(data[10].missing != -1) || (data[10].qvalue < 34)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 20)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
          sum += 0.015463094227f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += 0.10993495584f;
          } else {
            sum += 0.3477948308f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            sum += 0.38381364942f;
          } else {
            sum += 0.11101784557f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 28)) {
              sum += -0.25225019455f;
            } else {
              sum += 0.074093699455f;
            }
          } else {
            sum += 0.25270569324f;
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 82)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 178)) {
              sum += 0.48483327031f;
            } else {
              sum += -0.13035981357f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 256)) {
              sum += -0.1402861923f;
            } else {
              sum += 0.29398605227f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 260)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 46)) {
              sum += 0.25610676408f;
            } else {
              sum += -0.28846988082f;
            }
          } else {
            sum += 0.25299978256f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          sum += 0.33725720644f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 180)) {
              sum += -0.093462713063f;
            } else {
              sum += 0.22936104238f;
            }
          } else {
            sum += -0.22743593156f;
          }
        }
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].qvalue < 34)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 192)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 60)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
              sum += 0.036839351058f;
            } else {
              sum += 0.3201841116f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 102)) {
              sum += -0.34364545345f;
            } else {
              sum += 0.10030492395f;
            }
          }
        } else {
          sum += 0.42858669162f;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
              sum += -0.10663467646f;
            } else {
              sum += 0.29616639018f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += -0.25596487522f;
            } else {
              sum += 0.016673378646f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += 0.31226664782f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
              sum += 0.30606228113f;
            } else {
              sum += 0.11960134655f;
            }
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 56)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 214)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
              sum += 0.39131844044f;
            } else {
              sum += 0.062413200736f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 58)) {
              sum += 0.29776334763f;
            } else {
              sum += -0.25160682201f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 68)) {
            sum += 0.33229029179f;
          } else {
            sum += 0.037021685392f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 152)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 124)) {
              sum += 0.22109825909f;
            } else {
              sum += 0.69008505344f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
              sum += 0.28923374414f;
            } else {
              sum += -0.07715857029f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
            sum += -0.15302877128f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 62)) {
              sum += -0.081088788807f;
            } else {
              sum += 0.20920038223f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 156)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            sum += 0.4582709372f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 46)) {
              sum += 0.050541970879f;
            } else {
              sum += -0.29282411933f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += 0.37197291851f;
            } else {
              sum += 0.094149947166f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 44)) {
              sum += -0.16191977262f;
            } else {
              sum += 0.25113001466f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 252)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
              sum += 0.034749858081f;
            } else {
              sum += 0.40401822329f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 96)) {
              sum += -0.27463361621f;
            } else {
              sum += 0.30424076319f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 270)) {
              sum += -0.20209978521f;
            } else {
              sum += 0.2721657753f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 78)) {
              sum += 0.41319534183f;
            } else {
              sum += 0.10376755148f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            sum += 0.23355536163f;
          } else {
            sum += -0.091017112136f;
          }
        } else {
          sum += 0.30438888073f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
            sum += 0.072315551341f;
          } else {
            sum += 0.26765674353f;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 50)) {
            sum += -0.25365254283f;
          } else {
            sum += 0.080523826182f;
          }
        }
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].qvalue < 40)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 20)) {
            sum += -0.23488940299f;
          } else {
            sum += 0.18546356261f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 12)) {
              sum += 0.28585156798f;
            } else {
              sum += -0.20935533941f;
            }
          } else {
            sum += 0.30824518204f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.058493528515f;
            } else {
              sum += 0.28469884396f;
            }
          } else {
            sum += 0.33770024776f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 68)) {
            sum += 0.34577727318f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 140)) {
              sum += -0.40607169271f;
            } else {
              sum += 0.095722712576f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 222)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 146)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += -0.199883461f;
            } else {
              sum += 0.18017715216f;
            }
          } else {
            sum += 0.39199674129f;
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
            sum += 0.23792184889f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.065929189324f;
            } else {
              sum += -0.26114240289f;
            }
          }
        }
      } else {
        sum += 0.29856416583f;
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
    if (!(data[10].missing != -1) || (data[10].qvalue < 44)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 170)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 88)) {
            sum += 0.278549999f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.15496399999f;
            } else {
              sum += 0.21449716389f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
            sum += 0.55305969715f;
          } else {
            sum += 0.13076940179f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 194)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            sum += 0.11732271314f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
              sum += -0.035689137876f;
            } else {
              sum += -0.27111703157f;
            }
          }
        } else {
          sum += 0.36956512928f;
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 90)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
              sum += -0.090350188315f;
            } else {
              sum += 0.35033935308f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 254)) {
              sum += -0.16288302839f;
            } else {
              sum += 0.25473964214f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 266)) {
              sum += -0.28025338054f;
            } else {
              sum += 0.22964783013f;
            }
          } else {
            sum += 0.42301464081f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 182)) {
              sum += -0.14639085531f;
            } else {
              sum += 0.13144807518f;
            }
          } else {
            sum += -0.24157546461f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 186)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 88)) {
              sum += 0.55776977539f;
            } else {
              sum += 0.25385794044f;
            }
          } else {
            sum += 0.015843613073f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 20)) {
          sum += -0.21671275795f;
        } else {
          sum += 0.18679255247f;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 12)) {
            sum += 0.27746844292f;
          } else {
            sum += -0.1929166615f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += 0.30595541f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 108)) {
              sum += 0.005712332204f;
            } else {
              sum += 0.29340851307f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
              sum += 0.28483340144f;
            } else {
              sum += 0.038206767291f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 22)) {
              sum += 0.18075682223f;
            } else {
              sum += 0.52766954899f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 82)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 242)) {
              sum += -0.035119514912f;
            } else {
              sum += 0.31350368261f;
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 8)) {
              sum += 0.34090977907f;
            } else {
              sum += -0.081482507288f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 204)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 64)) {
            sum += 0.3377431035f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 74)) {
              sum += -0.18975204229f;
            } else {
              sum += 0.38408398628f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 48)) {
              sum += 0.44634771347f;
            } else {
              sum += 0.12435039133f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 234)) {
              sum += -0.24543751776f;
            } else {
              sum += 0.15347954631f;
            }
          }
        }
      }
    }
  }
  if (!(data[12].missing != -1) || (data[12].qvalue < 26)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[11].missing != -1) || (data[11].qvalue < 12)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          sum += 0.013260693289f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 14)) {
            sum += -0.015638457611f;
          } else {
            sum += 0.30997252464f;
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 36)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 74)) {
            sum += 0.33312246203f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 106)) {
              sum += -0.44066974521f;
            } else {
              sum += -0.02610722743f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
              sum += 0.1532728076f;
            } else {
              sum += -0.23037952185f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 168)) {
              sum += 0.4260109961f;
            } else {
              sum += 0.15218403935f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
            sum += -0.012610000558f;
          } else {
            sum += 0.2606061101f;
          }
        } else {
          sum += -0.16677589715f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
          sum += 0.29853624105f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += 0.1552131474f;
            } else {
              sum += -0.33654361963f;
            }
          } else {
            sum += 0.2806687057f;
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 90)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 46)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
            sum += 0.26203352213f;
          } else {
            sum += -0.23072431982f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += 0.54947340488f;
            } else {
              sum += -0.087427161634f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.29869100451f;
            } else {
              sum += -0.26972213387f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 268)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
              sum += 0.12333595753f;
            } else {
              sum += -0.20188885927f;
            }
          } else {
            sum += 0.171356529f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 186)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
              sum += 0.44972470403f;
            } else {
              sum += 0.064877532423f;
            }
          } else {
            sum += -0.01106778346f;
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 216)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 166)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 76)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 30)) {
              sum += 0.27477675676f;
            } else {
              sum += -0.0078008510172f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
              sum += 0.53241759539f;
            } else {
              sum += 0.10123219341f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += 0.035143174231f;
            } else {
              sum += 0.71131360531f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
              sum += 0.27973651886f;
            } else {
              sum += -0.26812067628f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 70)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 42)) {
            sum += 0.10692673177f;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 74)) {
              sum += 0.57365214825f;
            } else {
              sum += 0.24900960922f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 246)) {
            sum += -0.17549657822f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
              sum += 0.029350727797f;
            } else {
              sum += 0.23571480811f;
            }
          }
        }
      }
    }
  }
  if (!(data[10].missing != -1) || (data[10].qvalue < 28)) {
    if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
          sum += 0.25226911902f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
            sum += 0.058646786958f;
          } else {
            sum += -0.20080664754f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
            sum += -0.011353470385f;
          } else {
            sum += 0.19160474837f;
          }
        } else {
          sum += 0.29797875881f;
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 16)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 150)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 22)) {
              sum += -0.32415056229f;
            } else {
              sum += 0.032543499023f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 12)) {
              sum += 0.1898650229f;
            } else {
              sum += -0.093290984631f;
            }
          }
        } else {
          sum += 0.22835287452f;
        }
      } else {
        sum += 0.34973976016f;
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 58)) {
          sum += 0.72524780035f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
            sum += 0.12392085046f;
          } else {
            sum += -0.19743470848f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
            sum += 0.36037638783f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 142)) {
              sum += 0.072734944522f;
            } else {
              sum += -0.1310185343f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 274)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 46)) {
              sum += 0.21433377266f;
            } else {
              sum += -0.26812368631f;
            }
          } else {
            sum += 0.23976290226f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 212)) {
              sum += -0.03100088425f;
            } else {
              sum += 0.31247800589f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.047605391592f;
            } else {
              sum += 0.24723531306f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
            sum += 0.24345082045f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 54)) {
              sum += -0.20502759516f;
            } else {
              sum += 0.19006617367f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
            sum += -0.12028738111f;
          } else {
            sum += 0.22164316475f;
          }
        } else {
          sum += 0.28504574299f;
        }
      }
    }
  }
  if (!(data[10].missing != -1) || (data[10].qvalue < 54)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 0)) {
            sum += 0.22755469382f;
          } else {
            sum += 0.053185023367f;
          }
        } else {
          sum += -0.17560118437f;
        }
      } else {
        sum += 0.29936778545f;
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 38)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 196)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 80)) {
            sum += 0.33963108063f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 94)) {
              sum += -0.38148346543f;
            } else {
              sum += -0.023370174691f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
              sum += 0.24957554042f;
            } else {
              sum += 0.55739969015f;
            }
          } else {
            sum += 0.0078072356991f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 54)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 56)) {
              sum += 0.47950214148f;
            } else {
              sum += 0.1646489054f;
            }
          } else {
            sum += 0.08676584065f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 14)) {
              sum += 0.028966071084f;
            } else {
              sum += -0.13149932027f;
            }
          } else {
            sum += 0.23946706951f;
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 164)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 72)) {
          sum += 0.21032947302f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 34)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += 0.20272310078f;
            } else {
              sum += -0.18996453285f;
            }
          } else {
            sum += -0.28929680586f;
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 46)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 24)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.040233176202f;
            } else {
              sum += 0.32095399499f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += -0.12235197425f;
            } else {
              sum += 0.21635372937f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
              sum += 0.49935701489f;
            } else {
              sum += 0.073867633939f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
              sum += -0.14470659196f;
            } else {
              sum += 0.16904956102f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 250)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 208)) {
              sum += -0.14093716443f;
            } else {
              sum += 0.39992460608f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
              sum += -0.049490403384f;
            } else {
              sum += -0.29617604613f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 86)) {
            sum += -0.16719947755f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.072214901447f;
            } else {
              sum += 0.34052455425f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 270)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += 0.090989902616f;
            } else {
              sum += -0.22292761505f;
            }
          } else {
            sum += 0.24349178374f;
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 72)) {
            sum += 0.32115036249f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += -0.056041467935f;
            } else {
              sum += 0.1681406796f;
            }
          }
        }
      }
    }
  }
  if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
    if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            sum += 0.010221712291f;
          } else {
            sum += 0.22745144367f;
          }
        } else {
          sum += -0.16702450812f;
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
          sum += 0.29765310884f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 112)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 86)) {
              sum += 0.13858254254f;
            } else {
              sum += -0.17487329245f;
            }
          } else {
            sum += 0.30744853616f;
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
            sum += 0.22125892341f;
          } else {
            sum += -0.054784670472f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            sum += -0.30399465561f;
          } else {
            sum += 0.08064968884f;
          }
        }
      } else {
        sum += 0.32145994902f;
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 66)) {
          sum += 0.49156051874f;
        } else {
          sum += -0.072746038437f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 48)) {
            sum += 0.23371990025f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 220)) {
              sum += -0.27013614774f;
            } else {
              sum += -0.025465000421f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
            sum += 0.49627137184f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 84)) {
              sum += -0.10271213204f;
            } else {
              sum += 0.17455454171f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 44)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
              sum += -0.031019061804f;
            } else {
              sum += 0.24428035319f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += 0.27893534303f;
            } else {
              sum += -0.093650043011f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 80)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 56)) {
              sum += 0.29268825054f;
            } else {
              sum += -0.13569383323f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 160)) {
              sum += 0.35526198149f;
            } else {
              sum += -0.0030978003051f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 64)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
              sum += 0.21025384963f;
            } else {
              sum += -0.045162595809f;
            }
          } else {
            sum += 0.30074885488f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 224)) {
            sum += -0.09682624042f;
          } else {
            sum += 0.19962649047f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
      sum += -0.081628024578f;
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          sum += -0.073921121657f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 114)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += 0.13926909864f;
            } else {
              sum += 0.0056894649751f;
            }
          } else {
            sum += 0.25796222687f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 6)) {
            sum += 0.21782292426f;
          } else {
            sum += -0.060086615384f;
          }
        } else {
          sum += 0.2948692441f;
        }
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 26)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 104)) {
              sum += -0.15487787127f;
            } else {
              sum += 0.28873512149f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
              sum += -0.26879540086f;
            } else {
              sum += 0.14415532351f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 70)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 174)) {
              sum += 0.42890581489f;
            } else {
              sum += 0.16335277259f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.092929683626f;
            } else {
              sum += 0.18264490366f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
          sum += 0.35576117039f;
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 84)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 62)) {
              sum += 0.10656253248f;
            } else {
              sum += -0.10928912461f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 98)) {
              sum += 0.13365443051f;
            } else {
              sum += -0.18031619489f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 168)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 48)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 10)) {
              sum += 0.2409774214f;
            } else {
              sum += -0.13170221448f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
              sum += 0.32236361504f;
            } else {
              sum += -0.17005342245f;
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 258)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.1159221828f;
            } else {
              sum += -0.25495609641f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 48)) {
              sum += -0.031946819276f;
            } else {
              sum += 0.24457357824f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 204)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 66)) {
            sum += 0.27093040943f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 98)) {
              sum += -0.40866670012f;
            } else {
              sum += -0.0084642525762f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 50)) {
            sum += 0.35007330775f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 240)) {
              sum += -0.15615847707f;
            } else {
              sum += 0.18375526369f;
            }
          }
        }
      }
    }
  }
  if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
        sum += 0.19908313453f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
          sum += -0.14930264652f;
        } else {
          sum += -0.0048963767476f;
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            sum += 0.17967320979f;
          } else {
            sum += -0.12980625033f;
          }
        } else {
          sum += 0.26063171029f;
        }
      } else {
        sum += 0.28965350986f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 54)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 206)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += -0.044517688453f;
            } else {
              sum += 0.15833836794f;
            }
          } else {
            sum += 0.31449952722f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
            sum += 0.32261279225f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 252)) {
              sum += -0.10143389553f;
            } else {
              sum += 0.17359632254f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += 0.1442553997f;
            } else {
              sum += -0.24241803586f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
              sum += 0.0093561559916f;
            } else {
              sum += 0.37985691428f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 60)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 218)) {
              sum += -0.20376597345f;
            } else {
              sum += 0.049799788743f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += -0.079633235931f;
            } else {
              sum += 0.27412226796f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
          sum += 0.065853364766f;
        } else {
          sum += 0.28159356117f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
          sum += 0.17544086277f;
        } else {
          sum += -0.070574432611f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
          sum += 0.17564946413f;
        } else {
          sum += 0.032925672829f;
        }
      } else {
        sum += -0.17250829935f;
      }
    } else {
      sum += 0.28982394934f;
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 164)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 138)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 36)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 70)) {
            sum += 0.28499531746f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += -0.19495549798f;
            } else {
              sum += 0.068796917796f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 62)) {
              sum += 0.19986902177f;
            } else {
              sum += -0.18601106107f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 56)) {
              sum += 0.4323951304f;
            } else {
              sum += -0.03563137725f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
          sum += -0.22124072909f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 18)) {
              sum += 0.38943967223f;
            } else {
              sum += 0.12697306275f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += -0.046053763479f;
            } else {
              sum += 0.36358970404f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 200)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
              sum += -0.17742775381f;
            } else {
              sum += 0.070140704513f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += 0.35624811053f;
            } else {
              sum += 0.056637693197f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 92)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 52)) {
              sum += -0.048939753324f;
            } else {
              sum += -0.22949019074f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += 0.22811074555f;
            } else {
              sum += -0.086377665401f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 52)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += 0.22992326319f;
            } else {
              sum += 0.56629729271f;
            }
          } else {
            sum += -0.0678236112f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 252)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
              sum += 0.28501573205f;
            } else {
              sum += -0.23443058133f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += 0.046835184097f;
            } else {
              sum += 0.26527243853f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 172)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 26)) {
          sum += 0.053829047829f;
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 100)) {
            sum += -0.2846224308f;
          } else {
            sum += -0.053397607058f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 72)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 76)) {
              sum += 0.42340800166f;
            } else {
              sum += -0.012929977849f;
            }
          } else {
            sum += -0.26258221269f;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 30)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 66)) {
              sum += 0.23929330707f;
            } else {
              sum += -0.066139861941f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 66)) {
              sum += 0.34035632014f;
            } else {
              sum += 0.11084701866f;
            }
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 200)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
          sum += 0.20535051823f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
              sum += -0.038188621402f;
            } else {
              sum += -0.25460794568f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 184)) {
              sum += 0.25253593922f;
            } else {
              sum += -0.18689930439f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += 0.026852224022f;
            } else {
              sum += 0.44518297911f;
            }
          } else {
            sum += -0.081352502108f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 252)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 38)) {
              sum += 0.24332514405f;
            } else {
              sum += -0.19074465334f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
              sum += 0.016209207475f;
            } else {
              sum += 0.20998720825f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[10].missing != -1) || (data[10].qvalue < 32)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
          sum += 0.17617982626f;
        } else {
          sum += -0.094467632473f;
        }
      } else {
        sum += 0.28424310684f;
      }
    } else {
      if (!(data[13].missing != -1) || (data[13].qvalue < 10)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 148)) {
            sum += 0.26651868224f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 190)) {
              sum += -0.033766157925f;
            } else {
              sum += 0.21777318418f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += 0.19279994071f;
            } else {
              sum += -0.10572492331f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += 0.049883183092f;
            } else {
              sum += -0.2811267972f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += 0.12052815408f;
        } else {
          sum += 0.47393262386f;
        }
      }
    }
  }
  if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
        sum += 0.14035327733f;
      } else {
        sum += -0.105831258f;
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
        sum += 0.27747002244f;
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 112)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 90)) {
            sum += 0.058766365051f;
          } else {
            sum += -0.13446617126f;
          }
        } else {
          sum += 0.23582707345f;
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 78)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
              sum += -0.13116405904f;
            } else {
              sum += 0.079583257437f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              sum += 0.31763592362f;
            } else {
              sum += -0.024991335347f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 64)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 32)) {
              sum += 0.046578198671f;
            } else {
              sum += 0.32772275805f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
              sum += 0.1585418433f;
            } else {
              sum += -0.097222231328f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += 0.20410755277f;
            } else {
              sum += -0.066752023995f;
            }
          } else {
            sum += 0.28256070614f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            sum += 0.1230308488f;
          } else {
            sum += -0.14224596322f;
          }
        }
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 70)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
          sum += 0.49213838577f;
        } else {
          sum += -0.043261837214f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 96)) {
              sum += -0.26054081321f;
            } else {
              sum += 0.15168066323f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 232)) {
              sum += -0.20524902642f;
            } else {
              sum += 0.069549381733f;
            }
          }
        } else {
          sum += 0.35950496793f;
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}