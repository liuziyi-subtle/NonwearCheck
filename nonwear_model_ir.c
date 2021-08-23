#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  14, 3, 34, 36, 83, 50, 20, 4, 63, 30, 32, 19, 49, 16, 12, 43, 48, 56, 
};
static const int th_begin[] = {
  0, 14, 17, 51, 87, 170, 220, 240, 244, 307, 337, 369, 388, 437, 453, 465, 
  508, 556, 
};

static const float threshold[] = {
  5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 
  18.5f, 2.5f, 3.5f, 4.5f, -0.07726676f, 0.01196653f, 0.17538208f, 0.18401957f, 
  0.39565444f, 0.41367358f, 0.43571144f, 0.4744826f, 0.48399532f, 0.50400865f, 
  0.50827575f, 0.52846742f, 0.53389567f, 0.53995991f, 0.54709375f, 0.56213546f, 
  0.58840442f, 0.60242939f, 0.60301524f, 0.60762703f, 0.60840666f, 0.63753903f, 
  0.68028122f, 0.71595836f, 0.92362422f, 0.93162465f, 0.9464227f, 0.94747674f, 
  0.94802201f, 0.97091627f, 0.97331661f, 0.97731704f, 0.98171359f, 0.98764658f, 
  0.08984375f, 0.11328125f, 0.16015625f, 0.18359375f, 0.19140625f, 0.21484375f, 
  0.34375f, 0.34765625f, 0.3984375f, 0.50390625f, 0.55078125f, 0.57421875f, 
  0.58203125f, 0.58984375f, 0.60546875f, 0.609375f, 0.61328125f, 0.62109375f, 
  0.6484375f, 0.66015625f, 0.66796875f, 0.67578125f, 0.703125f, 0.71484375f, 0.71875f, 
  0.73046875f, 0.734375f, 0.73828125f, 0.78515625f, 0.80078125f, 0.81640625f, 
  0.84765625f, 0.85546875f, 0.87890625f, 0.88671875f, 0.90234375f, 34643.582f, 
  38447.75f, 38467.5f, 39593.75f, 39882.332f, 39953.664f, 39959.414f, 40042.414f, 
  40233.664f, 40410.75f, 40434.164f, 40590.75f, 40608.0f, 40613.914f, 40657.414f, 
  40691.75f, 41930.914f, 41940.586f, 41948.332f, 42205.668f, 42295.0f, 42312.836f, 
  42377.25f, 42385.5f, 42508.25f, 42514.836f, 42584.082f, 42947.918f, 42973.0f, 
  42991.414f, 42995.414f, 43014.832f, 43021.0f, 43073.086f, 43143.336f, 43393.918f, 
  44606.168f, 46106.0f, 46674.336f, 48072.586f, 48286.25f, 48421.75f, 49115.836f, 
  49196.5f, 49240.664f, 49243.5f, 49887.164f, 50451.582f, 50486.25f, 51957.414f, 
  52025.25f, 52028.5f, 52067.336f, 52264.25f, 52355.418f, 52430.082f, 52511.664f, 
  52549.414f, 52614.914f, 52733.668f, 52778.0f, 52798.836f, 52995.668f, 53957.75f, 
  54528.664f, 54821.336f, 55391.836f, 55482.582f, 55783.836f, 55910.336f, 55918.0f, 
  57729.336f, 57762.668f, 57864.168f, 57886.0f, 58039.75f, 58062.0f, 58595.582f, 
  58675.164f, 58941.75f, 59443.5f, 59549.25f, 60132.336f, 0.12318092f, 0.23768204f, 
  0.2977204f, 0.31728804f, 0.40578794f, 0.45188668f, 0.45782596f, 0.49665886f, 
  0.50523138f, 0.56509477f, 0.57022727f, 0.58068728f, 0.6169368f, 0.75006342f, 
  0.75014985f, 0.75480759f, 0.7746408f, 0.89476633f, 0.89756459f, 0.97937381f, 
  0.97938871f, 1.0132246f, 1.0221617f, 1.0576433f, 1.097749f, 1.1004905f, 1.1351502f, 
  1.1509182f, 1.2131f, 1.254575f, 1.9684777f, 2.0283475f, 2.2424922f, 2.2496157f, 
  2.5124083f, 2.7662849f, 3.1362109f, 3.3563333f, 3.4166379f, 3.6122532f, 4.0726652f, 
  4.5256777f, 5.4473429f, 7.027523f, 13.155851f, 14.6278f, 21.335348f, 71.786156f, 
  74.782318f, 180.55643f, 0.36381966f, 0.65197217f, 0.71216726f, 1.0732398f, 
  1.8114218f, 2.2290802f, 2.3567371f, 2.5402603f, 3.2690687f, 3.5834281f, 5.8128028f, 
  6.3872647f, 8.2877789f, 13.729689f, 15.291656f, 15.605924f, 21.073444f, 87.530525f, 
  198.2778f, 425.65878f, 0.4309155f, 0.92078543f, 3.2354183f, 21.805208f, 
  -0.29281884f, 0.029192956f, 0.044279251f, 0.082712471f, 0.094917312f, 0.096229546f, 
  0.12516433f, 0.13892627f, 0.15650678f, 0.16801992f, 0.18788239f, 0.22293563f, 
  0.30706578f, 0.34330955f, 0.46465939f, 0.50940597f, 0.58012819f, 0.58127272f, 
  0.63851714f, 0.67989641f, 0.70896691f, 0.73753929f, 0.73814088f, 0.73933733f, 
  0.7500971f, 0.75695467f, 0.77988887f, 0.78004557f, 0.7816565f, 0.78464699f, 
  0.82874632f, 0.84303904f, 0.84317064f, 0.8528775f, 0.8717978f, 0.91109896f, 
  0.94621122f, 0.95235425f, 0.95948601f, 0.99097359f, 1.0000803f, 1.0273918f, 
  1.0655074f, 1.0700331f, 1.0703526f, 1.1193798f, 1.1705723f, 1.2129314f, 1.2195235f, 
  1.2415314f, 1.2444949f, 1.2461989f, 1.2515639f, 1.3421199f, 1.3495256f, 1.3537767f, 
  1.3860667f, 1.4229428f, 1.4243488f, 1.4244479f, 1.7055013f, 1.7463195f, 2.3778195f, 
  0.36328125f, 0.40234375f, 0.42578125f, 0.4296875f, 0.43359375f, 0.44140625f, 
  0.45703125f, 0.46875f, 0.48046875f, 0.48828125f, 0.49609375f, 0.50390625f, 
  0.52734375f, 0.53515625f, 0.54296875f, 0.55078125f, 0.55859375f, 0.58203125f, 
  0.58984375f, 0.59765625f, 0.60546875f, 0.61328125f, 0.62109375f, 0.62890625f, 
  0.63671875f, 0.64453125f, 0.66015625f, 0.66796875f, 0.67578125f, 0.68359375f, 11.5f, 
  13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 18.5f, 19.5f, 20.5f, 21.5f, 22.0f, 22.5f, 23.5f, 24.5f, 
  25.5f, 26.5f, 28.5f, 30.5f, 31.5f, 32.5f, 33.0f, 34.5f, 35.5f, 36.5f, 37.5f, 38.5f, 40.5f, 
  42.5f, 43.5f, 46.5f, 47.0f, 47.5f, 7.5f, 8.5f, 9.5f, 10.5f, 19.5f, 23.5f, 24.5f, 25.5f, 
  31.5f, 33.5f, 36.0f, 36.5f, 39.0f, 44.5f, 52.5f, 54.5f, 56.5f, 58.5f, 82.5f, 0.63423312f, 
  1.284579f, 1.4151607f, 1.4251547f, 1.4469798f, 1.5938398f, 1.6782629f, 1.6836812f, 
  1.6912355f, 1.7102381f, 1.7627941f, 1.7744632f, 1.792556f, 1.8069855f, 1.8416117f, 
  1.847137f, 1.8529687f, 1.8587637f, 1.8673677f, 1.867655f, 1.8720009f, 1.8855101f, 
  1.8869442f, 1.8971574f, 1.9098234f, 1.9287667f, 1.9289045f, 1.940316f, 1.9489263f, 
  1.9564786f, 1.9604049f, 1.9662604f, 1.9687066f, 1.9751127f, 1.9856753f, 1.9902046f, 
  1.9927046f, 2.008014f, 2.0102143f, 2.0110621f, 2.0168624f, 2.0201144f, 2.0632148f, 
  2.0691881f, 2.1301663f, 2.1422801f, 2.1516833f, 2.1592617f, 2.1784081f, 19.386642f, 
  41.331871f, 114.35247f, 160.92258f, 319.67648f, 418.25943f, 425.53876f, 664.02893f, 
  684.47815f, 741.2168f, 845.73608f, 870.46429f, 881.76611f, 4536.6274f, 4727.3477f, 
  25756.266f, 1.4542208f, 15.94846f, 21.236355f, 26.084591f, 68.878082f, 76.74543f, 
  101.90022f, 174.34875f, 193.95618f, 206.14981f, 279.38654f, 1336.1166f, 1.1290144f, 
  1.1341574f, 1.3521463f, 1.65625f, 2.2360742f, 2.3169856f, 2.6373308f, 2.8172331f, 
  2.9083624f, 3.9209979f, 3.947973f, 4.1201296f, 4.2722535f, 4.5111113f, 4.5174417f, 
  4.8290033f, 4.9368353f, 5.438262f, 5.4421539f, 5.4486842f, 5.4733896f, 5.9080338f, 
  5.9293237f, 6.1414285f, 7.6576576f, 7.8047619f, 8.6046906f, 8.7489262f, 8.7631922f, 
  9.4030275f, 11.577381f, 13.37586f, 13.789726f, 13.833498f, 15.209303f, 16.673759f, 
  18.184452f, 18.506098f, 20.647869f, 21.14819f, 21.258013f, 23.627777f, 38.268257f, 
  1.0942351f, 1.2784238f, 1.7245834f, 1.8065015f, 1.8382354f, 1.8900967f, 1.9126984f, 
  2.2642705f, 2.3985562f, 2.4042859f, 2.6099072f, 3.244071f, 3.2991991f, 3.3436852f, 
  3.5030065f, 3.5159121f, 3.7158537f, 3.7935605f, 4.2367148f, 4.5347695f, 4.6814013f, 
  4.8937502f, 5.6116962f, 5.9749999f, 6.3961239f, 6.602273f, 6.65625f, 6.9761772f, 
  8.2113628f, 8.7084637f, 8.9666328f, 9.5905924f, 9.8557644f, 10.476732f, 11.047269f, 
  11.879021f, 12.230159f, 12.295454f, 12.878676f, 12.905506f, 13.562039f, 13.637769f, 
  15.086081f, 16.888405f, 21.813469f, 28.17742f, 39.948215f, 98.070786f, 38612.5f, 
  39295.0f, 39303.5f, 40343.0f, 40364.0f, 40501.0f, 40730.5f, 42248.0f, 42656.5f, 42969.0f, 43127.0f, 
  43143.5f, 43146.0f, 43166.0f, 43172.0f, 46771.0f, 48962.5f, 49043.5f, 49137.5f, 49285.0f, 
  49322.5f, 50374.5f, 51051.0f, 51390.5f, 54679.5f, 54831.0f, 54913.5f, 54917.5f, 54989.5f, 
  55014.5f, 55044.5f, 55099.0f, 55331.0f, 55418.5f, 55579.0f, 55609.0f, 55734.0f, 55825.0f, 55911.5f, 
  56089.0f, 56347.0f, 56877.5f, 57737.0f, 57876.0f, 57877.5f, 57991.5f, 58098.5f, 58232.5f, 
  58451.5f, 58589.5f, 58590.5f, 58621.0f, 58640.5f, 58942.0f, 59530.5f, 59839.0f, 
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
  if (offset == 612 || val < array[0]) {
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
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};


float PredictIr(union NonwearEntry* data) {

  for (int i = 0; i < 18; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          sum += 0.33333337307f;
        } else {
          sum += -0.54000002146f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
              sum += 0.59733897448f;
            } else {
              sum += 0.48776981235f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 84)) {
              sum += 0.52450335026f;
            } else {
              sum += -0.019354838878f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += 0.53846156597f;
            } else {
              sum += 0.12000000477f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 16)) {
              sum += -0.40800002217f;
            } else {
              sum += 0.30000001192f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 2)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
            sum += -0.44347828627f;
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 60)) {
              sum += 0.49473688006f;
            } else {
              sum += -0.076923087239f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += 0.41538465023f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += -0.024000000209f;
            } else {
              sum += -0.53605020046f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += 0.57230770588f;
            } else {
              sum += 0.15000000596f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += 0.10000000894f;
            } else {
              sum += 0.36000001431f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += 0.054545458406f;
            } else {
              sum += 0.50769233704f;
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 16)) {
              sum += 0.17142859101f;
            } else {
              sum += -0.43529415131f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 0)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 12)) {
            sum += -0.0f;
          } else {
            sum += 0.46666669846f;
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 26)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 12)) {
              sum += -0.38181820512f;
            } else {
              sum += 0.33333337307f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
              sum += 0.33333337307f;
            } else {
              sum += -0.48438540101f;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 50)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
            sum += 0.59428572655f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 72)) {
              sum += 0.48847582936f;
            } else {
              sum += -0.26399999857f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.0f;
            } else {
              sum += 0.54418605566f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
              sum += 0.30000001192f;
            } else {
              sum += -0.43200004101f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
        sum += 0.57037043571f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 28)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += -0.0f;
            } else {
              sum += 0.49811324477f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 58)) {
              sum += -0.52258068323f;
            } else {
              sum += 0.42857146263f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += -0.54858934879f;
            } else {
              sum += -0.33494704962f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
              sum += -0.53575617075f;
            } else {
              sum += -0.58402431011f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          sum += 0.28256765008f;
        } else {
          sum += -0.42152893543f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
            sum += 0.46248143911f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
              sum += 0.41932231188f;
            } else {
              sum += -0.33114099503f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += 0.42178705335f;
            } else {
              sum += 0.098638445139f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.3782106638f;
            } else {
              sum += 0.039038814604f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
            sum += -0.2812962532f;
          } else {
            sum += 0.4732850492f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            sum += 0.38429662585f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += 0.12044741958f;
            } else {
              sum += -0.43022191525f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.12349229306f;
            } else {
              sum += 0.45200824738f;
            }
          } else {
            sum += 0.014694055542f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += -0.3441811502f;
            } else {
              sum += 0.34349066019f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += -0.39711901546f;
            } else {
              sum += 0.12538248301f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 22)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 26)) {
              sum += 0.36293870211f;
            } else {
              sum += -0.12472197413f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += -0.063118822873f;
            } else {
              sum += -0.43179151416f;
            }
          }
        } else {
          if (!(data[16].missing != -1) || (data[16].qvalue < 40)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 42)) {
              sum += 0.32960429788f;
            } else {
              sum += -0.13649515808f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += -0.41581383348f;
            } else {
              sum += -0.00066691776738f;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 48)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
            sum += 0.46539998055f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 78)) {
              sum += 0.38476115465f;
            } else {
              sum += -0.15070039034f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.26770871878f;
            } else {
              sum += 0.39068222046f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.35487440228f;
            } else {
              sum += 0.47333487868f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
        sum += 0.4406567812f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += -0.23646038771f;
            } else {
              sum += 0.3075787425f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 62)) {
              sum += -0.44101762772f;
            } else {
              sum += 0.36729249358f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
              sum += -0.031881153584f;
            } else {
              sum += -0.39483916759f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += -0.44316241145f;
            } else {
              sum += -0.0029902490787f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          sum += 0.24599228799f;
        } else {
          sum += -0.33496963978f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
            sum += 0.40239670873f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += -0.054696619511f;
            } else {
              sum += 0.33049765229f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.38581833243f;
            } else {
              sum += 0.026081021875f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 32)) {
              sum += 0.29544639587f;
            } else {
              sum += -0.45779198408f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += 0.1449842751f;
            } else {
              sum += -0.35621625185f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 60)) {
              sum += 0.36742997169f;
            } else {
              sum += -0.03342731297f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            sum += 0.09459657222f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += 0.14081224799f;
            } else {
              sum += -0.39873385429f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.10163195431f;
            } else {
              sum += 0.38533166051f;
            }
          } else {
            sum += 0.012315335684f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
              sum += -0.13063083589f;
            } else {
              sum += 0.35174319148f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += 0.27920281887f;
            } else {
              sum += -0.28421670198f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 110)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += -0.067123822868f;
            } else {
              sum += 0.26629582047f;
            }
          } else {
            sum += 0.40252262354f;
          }
        } else {
          sum += -0.029388871044f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.36538505554f;
            } else {
              sum += -0.012470074929f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 16)) {
              sum += 0.15112408996f;
            } else {
              sum += -0.29787793756f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 76)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
              sum += -0.075730681419f;
            } else {
              sum += 0.39036527276f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 36)) {
              sum += 0.34053963423f;
            } else {
              sum += -0.19773751497f;
            }
          }
        }
      }
    } else {
      if (!(data[17].missing != -1) || (data[17].qvalue < 12)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 10)) {
            sum += -0.38420438766f;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += -0.22998984158f;
            } else {
              sum += 0.26514065266f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 70)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 0)) {
              sum += 0.34901025891f;
            } else {
              sum += 0.74395424128f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
              sum += -0.16394692659f;
            } else {
              sum += 0.36652618647f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 42)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 58)) {
              sum += 0.32352373004f;
            } else {
              sum += -0.073191732168f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 62)) {
              sum += -0.37073078752f;
            } else {
              sum += 0.35516315699f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 48)) {
              sum += -0.19689168036f;
            } else {
              sum += -0.36692464352f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 0)) {
              sum += 0.046417012811f;
            } else {
              sum += -0.39374193549f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          sum += 0.21793077886f;
        } else {
          sum += -0.2911709547f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += 0.36728397012f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += 0.35333138704f;
            } else {
              sum += -0.11207612604f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 34)) {
              sum += 0.30774119496f;
            } else {
              sum += -0.33049660921f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 26)) {
              sum += 0.17634250224f;
            } else {
              sum += -0.25119122863f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
              sum += 0.27499583364f;
            } else {
              sum += -0.26429435611f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 80)) {
              sum += 0.32106015086f;
            } else {
              sum += -0.12279824913f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 30)) {
              sum += -0.15998266637f;
            } else {
              sum += -0.37779703736f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.11337772757f;
            } else {
              sum += 0.36534261703f;
            }
          } else {
            sum += 0.048560291529f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 40)) {
              sum += 0.33626753092f;
            } else {
              sum += 0.025918271393f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += -0.31982630491f;
            } else {
              sum += 0.00026029054425f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 46)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
        if (!(data[13].missing != -1) || (data[13].qvalue < 12)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
            sum += 0.37468650937f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
              sum += 0.081432521343f;
            } else {
              sum += 0.37096944451f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
              sum += 0.28520676494f;
            } else {
              sum += 0.075940206647f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
              sum += -0.31225159764f;
            } else {
              sum += 0.054481532425f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
              sum += -0.18616563082f;
            } else {
              sum += 0.25959166884f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.3088079989f;
            } else {
              sum += -0.063353046775f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 74)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 50)) {
              sum += 0.28752163053f;
            } else {
              sum += -0.17142599821f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.23170460761f;
            } else {
              sum += -0.25887769461f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 38)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += -0.32751178741f;
            } else {
              sum += 0.21644605696f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += 0.47596722841f;
            } else {
              sum += -0.10211931169f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 18)) {
              sum += -0.13745805621f;
            } else {
              sum += 0.56180334091f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 32)) {
              sum += -0.26203280687f;
            } else {
              sum += -0.36571505666f;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 44)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              sum += 0.11614735425f;
            } else {
              sum += 0.44576734304f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 62)) {
              sum += 0.34026807547f;
            } else {
              sum += -0.28206285834f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 38)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 86)) {
              sum += 0.37770017982f;
            } else {
              sum += -0.28192019463f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 46)) {
              sum += -0.060850117356f;
            } else {
              sum += -0.32179138064f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          sum += 0.15781721473f;
        } else {
          sum += -0.25914797187f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
            sum += 0.34531539679f;
          } else {
            sum += 0.13784271479f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += 0.33650392294f;
            } else {
              sum += -0.054010182619f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 54)) {
              sum += 0.25322678685f;
            } else {
              sum += -0.39762398601f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
          sum += 0.33903872967f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += 0.22900688648f;
            } else {
              sum += -0.069869175553f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 60)) {
              sum += -0.25376406312f;
            } else {
              sum += 0.25074872375f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += 0.063677467406f;
            } else {
              sum += 0.33729737997f;
            }
          } else {
            sum += 0.044877465814f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 54)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 78)) {
              sum += 0.28496825695f;
            } else {
              sum += -0.011580144055f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
              sum += 0.11898716539f;
            } else {
              sum += -0.27711233497f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
        if (!(data[13].missing != -1) || (data[13].qvalue < 10)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
            sum += 0.34537366033f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.13594676554f;
            } else {
              sum += 0.25512167811f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
            sum += 0.23886916041f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += 0.08171608299f;
            } else {
              sum += -0.27986508608f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
              sum += -0.32224148512f;
            } else {
              sum += 0.22354714572f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += 0.019421830773f;
            } else {
              sum += -0.31066590548f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 78)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += -0.23155373335f;
            } else {
              sum += 0.21284069121f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 18)) {
              sum += 0.33088260889f;
            } else {
              sum += -0.22197124362f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 60)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 52)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += 0.31253027916f;
            } else {
              sum += -0.12710468471f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.045122835785f;
            } else {
              sum += -0.23779739439f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += 0.070138216019f;
            } else {
              sum += 0.38611224294f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.32306152582f;
            } else {
              sum += -0.01152191218f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 14)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += -0.3125641942f;
            } else {
              sum += 0.35312104225f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += -0.041531022638f;
            } else {
              sum += 0.60141932964f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
              sum += -0.32839563489f;
            } else {
              sum += -0.0026619108394f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 62)) {
              sum += 0.10950165242f;
            } else {
              sum += -0.32578623295f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          sum += 0.13778747618f;
        } else {
          sum += -0.21003425121f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          sum += 0.33030700684f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 28)) {
              sum += 0.046204119921f;
            } else {
              sum += 0.3171865344f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += -0.25346267223f;
            } else {
              sum += 0.25409013033f;
            }
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
            sum += 0.0091095641255f;
          } else {
            sum += -0.21856671572f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
              sum += 0.052239123732f;
            } else {
              sum += 0.33360630274f;
            }
          } else {
            sum += 0.049995809793f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
          sum += 0.33031243086f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += -0.19976437092f;
            } else {
              sum += 0.20373563468f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.11243911088f;
            } else {
              sum += 0.28597143292f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 40)) {
              sum += 0.30264669657f;
            } else {
              sum += 0.033031310886f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += 0.10118538141f;
            } else {
              sum += -0.21390987933f;
            }
          }
        } else {
          sum += 0.45547148585f;
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 8)) {
              sum += 0.21742065251f;
            } else {
              sum += -0.19526569545f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
              sum += 0.32708072662f;
            } else {
              sum += 0.082675807178f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += -0.21355827153f;
            } else {
              sum += 0.24940873682f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 102)) {
              sum += 0.36287474632f;
            } else {
              sum += 0.013167697005f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 40)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
              sum += 0.13788591325f;
            } else {
              sum += 0.40729436278f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += 0.12947626412f;
            } else {
              sum += -0.18954847753f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 40)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += -0.14728215337f;
            } else {
              sum += 0.53141659498f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += -0.31191903353f;
            } else {
              sum += 0.014139898121f;
            }
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += -0.31842914224f;
            } else {
              sum += 0.14068588614f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 66)) {
              sum += 0.40664428473f;
            } else {
              sum += -0.077162452042f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
              sum += -0.26635524631f;
            } else {
              sum += -0.31862056255f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 70)) {
              sum += 0.093894943595f;
            } else {
              sum += -0.30684614182f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 114)) {
          sum += 0.31947287917f;
        } else {
          sum += 0.0503616184f;
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += 0.2364436537f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
              sum += -0.45640230179f;
            } else {
              sum += 0.085940115154f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            sum += 0.3031218648f;
          } else {
            sum += -0.079565741122f;
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 12)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
              sum += -0.084736593068f;
            } else {
              sum += 0.27475321293f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 28)) {
              sum += -0.033979460597f;
            } else {
              sum += -0.32469755411f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
              sum += 0.30853030086f;
            } else {
              sum += -0.009003739804f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
              sum += -0.2261710614f;
            } else {
              sum += 0.18381141126f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
              sum += 0.21351660788f;
            } else {
              sum += -0.35827493668f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.19223158062f;
            } else {
              sum += 0.23409105837f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            sum += -0.30472123623f;
          } else {
            sum += -0.084688767791f;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 80)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 48)) {
            sum += 0.32260388136f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += -0.20963329077f;
            } else {
              sum += 0.31490167975f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 8)) {
              sum += -0.041997566819f;
            } else {
              sum += -0.20851649344f;
            }
          } else {
            sum += 0.23560544848f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.28671911359f;
            } else {
              sum += -0.19872890413f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += 0.11229535937f;
            } else {
              sum += -0.2257014662f;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 52)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 80)) {
              sum += 0.24142748117f;
            } else {
              sum += -0.097526401281f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += -0.26181223989f;
            } else {
              sum += 0.051095116884f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 62)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 90)) {
              sum += -0.07049716264f;
            } else {
              sum += -0.25693830848f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 36)) {
              sum += -0.12425224483f;
            } else {
              sum += -0.31733268499f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 20)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += -0.27433785796f;
            } else {
              sum += 0.22112004459f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += -0.30450257659f;
            } else {
              sum += -0.041054625064f;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 6)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
              sum += 0.45761555433f;
            } else {
              sum += 0.19757010043f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 30)) {
              sum += 0.41822814941f;
            } else {
              sum += -0.17511898279f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 36)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 84)) {
              sum += 0.34431493282f;
            } else {
              sum += -0.2559543848f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += -0.24311983585f;
            } else {
              sum += 0.065449111164f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
          sum += 0.31643736362f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.013106036f;
            } else {
              sum += 0.28416401148f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 10)) {
              sum += 0.21950185299f;
            } else {
              sum += -0.28721317649f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
            sum += 0.20385509729f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += -0.48151025176f;
            } else {
              sum += -0.044732771814f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += 0.071515984833f;
            } else {
              sum += 0.29655149579f;
            }
          } else {
            sum += -0.041348174214f;
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          sum += -0.099169820547f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            sum += 0.30556342006f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
              sum += -0.15708942711f;
            } else {
              sum += 0.20943079889f;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 56)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += -0.24800738692f;
            } else {
              sum += 0.11560993642f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 0)) {
              sum += -0.062377169728f;
            } else {
              sum += 0.29793584347f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 20)) {
              sum += -0.2256539613f;
            } else {
              sum += 0.088598027825f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
              sum += 0.2580525279f;
            } else {
              sum += -0.065890274942f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 68)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
              sum += 0.32366651297f;
            } else {
              sum += 0.15020704269f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += -0.061154041439f;
            } else {
              sum += 0.24160833657f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 54)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
              sum += 0.11179368943f;
            } else {
              sum += -0.30392509699f;
            }
          } else {
            sum += 0.29192981124f;
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 26)) {
              sum += -0.12738868594f;
            } else {
              sum += 0.29772543907f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 6)) {
              sum += -0.29551953077f;
            } else {
              sum += -0.17143067718f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += -0.074366800487f;
            } else {
              sum += 0.37467238307f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += -0.097130589187f;
            } else {
              sum += 0.16338917613f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 72)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 54)) {
              sum += -0.011983100325f;
            } else {
              sum += -0.22455118597f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += -0.27167236805f;
            } else {
              sum += 0.098123975098f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 76)) {
              sum += -0.2042734772f;
            } else {
              sum += 0.2470291853f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
              sum += 0.057343021035f;
            } else {
              sum += -0.30805885792f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += 0.23009981215f;
            } else {
              sum += -0.12791584432f;
            }
          } else {
            sum += 0.38274315f;
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 52)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 68)) {
              sum += 0.018219910562f;
            } else {
              sum += -0.32194060087f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 96)) {
              sum += 0.28040897846f;
            } else {
              sum += -0.20866748691f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            sum += 0.31121122837f;
          } else {
            sum += 0.074890874326f;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
              sum += 0.29118698835f;
            } else {
              sum += 0.099211454391f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
              sum += -0.27726727724f;
            } else {
              sum += 0.1929667294f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
          sum += 0.29972916842f;
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += -0.040229745209f;
            } else {
              sum += 0.26481547952f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += -0.42678904533f;
            } else {
              sum += 0.15755410492f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 56)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += -0.25641006231f;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += -0.20549632609f;
            } else {
              sum += 0.18537828326f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
            sum += 0.20879238844f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 2)) {
              sum += 0.051701024175f;
            } else {
              sum += -0.24052120745f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 88)) {
            sum += 0.29399552941f;
          } else {
            sum += 0.10157489032f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 82)) {
              sum += -0.10939176381f;
            } else {
              sum += 0.33047381043f;
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 20)) {
              sum += 0.20082773268f;
            } else {
              sum += -0.22145117819f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += -0.12155405432f;
            } else {
              sum += 0.3480335176f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.28045451641f;
            } else {
              sum += 0.25244620442f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += -0.1518702507f;
            } else {
              sum += 0.18205034733f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
              sum += -0.27506056428f;
            } else {
              sum += -0.1272135675f;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 20)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 92)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += -0.027020437643f;
            } else {
              sum += 0.26894050837f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += 0.22622351348f;
            } else {
              sum += -0.30104342103f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 58)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
              sum += 0.0021355096251f;
            } else {
              sum += 0.24727658927f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += -0.26460278034f;
            } else {
              sum += 0.16707992554f;
            }
          }
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 28)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 34)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 26)) {
              sum += -0.21548427641f;
            } else {
              sum += -0.0085989627987f;
            }
          } else {
            sum += 0.39913243055f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 8)) {
              sum += -0.037010800093f;
            } else {
              sum += -0.2881359458f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 80)) {
              sum += -0.18674580753f;
            } else {
              sum += 0.13713060319f;
            }
          }
        }
      } else {
        if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 30)) {
              sum += -0.044954776764f;
            } else {
              sum += 0.50190192461f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
              sum += -0.012989006005f;
            } else {
              sum += -0.17234063148f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
              sum += -0.10412351042f;
            } else {
              sum += 0.77013206482f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += -0.30053466558f;
            } else {
              sum += -0.084900304675f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
        sum += 0.30824625492f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
          sum += -0.2779045403f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 96)) {
              sum += 0.29423543811f;
            } else {
              sum += 0.076840132475f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 18)) {
              sum += 0.27083772421f;
            } else {
              sum += -0.024962095544f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
        sum += 0.27056238055f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 20)) {
              sum += -0.19453333318f;
            } else {
              sum += 0.16349390149f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              sum += -0.39206266403f;
            } else {
              sum += -0.085982523859f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
              sum += 0.34506911039f;
            } else {
              sum += -0.06215653941f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 62)) {
              sum += 0.31744837761f;
            } else {
              sum += -0.098841510713f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 16)) {
          sum += 0.30586060882f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += 0.23915244639f;
            } else {
              sum += -0.49332728982f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.31398651004f;
            } else {
              sum += 0.18330425024f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 44)) {
              sum += 0.039747111499f;
            } else {
              sum += -0.16325117648f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += 0.0049931271933f;
            } else {
              sum += -0.25129079819f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 68)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += 0.083643600345f;
            } else {
              sum += 0.37525349855f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += 0.3087631464f;
            } else {
              sum += -0.12774497271f;
            }
          }
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 8)) {
            sum += 0.0070170816034f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += -0.068259932101f;
            } else {
              sum += -0.27974849939f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            sum += 0.25203123689f;
          } else {
            sum += -0.190307796f;
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 52)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 48)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
              sum += 0.19116678834f;
            } else {
              sum += -0.1332231611f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 64)) {
              sum += 0.87591427565f;
            } else {
              sum += -0.18509294093f;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 34)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 92)) {
              sum += -0.14443001151f;
            } else {
              sum += 0.14374537766f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += -0.28128638864f;
            } else {
              sum += 0.15762661397f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
        sum += 0.30229324102f;
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 20)) {
          sum += 0.28630173206f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
              sum += -0.58440852165f;
            } else {
              sum += 0.072840057313f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 46)) {
              sum += -0.034439820796f;
            } else {
              sum += 0.26372539997f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
            sum += -0.0034223126713f;
          } else {
            sum += 0.24215950072f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 42)) {
              sum += -0.19142314792f;
            } else {
              sum += 0.12733228505f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
              sum += -0.35331234336f;
            } else {
              sum += 0.020492099226f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              sum += -0.12575829029f;
            } else {
              sum += 0.2059930861f;
            }
          } else {
            sum += 0.29464226961f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += 0.22381289303f;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 14)) {
              sum += 0.10175216198f;
            } else {
              sum += -0.15951687098f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 2)) {
            sum += -0.070397056639f;
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 6)) {
              sum += -0.072970755398f;
            } else {
              sum += -0.29406479001f;
            }
          }
        } else {
          sum += 0.34249839187f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += -0.24659982324f;
            } else {
              sum += 0.19872580469f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 86)) {
              sum += 0.47818517685f;
            } else {
              sum += -0.067639403045f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 36)) {
              sum += -0.29104691744f;
            } else {
              sum += 0.1452973485f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 54)) {
              sum += -0.0029407269321f;
            } else {
              sum += -0.25309547782f;
            }
          }
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 22)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 44)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.30514258146f;
            } else {
              sum += 0.0056497827172f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += 0.24539034069f;
            } else {
              sum += -0.22992087901f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += 0.14526534081f;
            } else {
              sum += 0.41227337718f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += -0.091237343848f;
            } else {
              sum += 0.26812592149f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 8)) {
              sum += 0.31305125356f;
            } else {
              sum += -0.1729452014f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 82)) {
              sum += 0.43769815564f;
            } else {
              sum += -0.20105861127f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += -0.14331170917f;
            } else {
              sum += 0.34124517441f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += -0.22439694405f;
            } else {
              sum += 0.07101970911f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
        sum += 0.3009506166f;
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          sum += 0.26472076774f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
            sum += -0.43786996603f;
          } else {
            sum += 0.21113395691f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            sum += -0.1327830106f;
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 28)) {
              sum += 0.23348496854f;
            } else {
              sum += -0.029257196933f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += 0.012271196581f;
            } else {
              sum += -0.29072272778f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
              sum += 0.20753845572f;
            } else {
              sum += -0.18628180027f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          sum += 0.26480519772f;
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 22)) {
            sum += 0.16151562333f;
          } else {
            sum += -0.053682867438f;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 108)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 8)) {
            sum += 0.29682508111f;
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 14)) {
              sum += -0.1408329457f;
            } else {
              sum += 0.25210830569f;
            }
          }
        } else {
          sum += -0.039298266172f;
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
          sum += 0.34008958936f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 68)) {
              sum += 0.19113962352f;
            } else {
              sum += -0.18464826047f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 92)) {
              sum += -0.20017530024f;
            } else {
              sum += 0.14138866961f;
            }
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 78)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 88)) {
              sum += 0.039581593126f;
            } else {
              sum += -0.14816258848f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 60)) {
              sum += -0.053977388889f;
            } else {
              sum += -0.24005693197f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += 0.13893397152f;
            } else {
              sum += 0.37843549252f;
            }
          } else {
            sum += -0.33361724019f;
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += -0.12116011232f;
            } else {
              sum += 0.40264058113f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += 0.073481082916f;
            } else {
              sum += -0.25265899301f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 90)) {
              sum += 0.32034745812f;
            } else {
              sum += 0.049399200827f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += -0.27392143011f;
            } else {
              sum += -0.14305207133f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
        sum += 0.29810765386f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            sum += -0.42251420021f;
          } else {
            sum += 0.20122158527f;
          }
        } else {
          sum += 0.25540548563f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
            sum += 0.19260597229f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += 0.1605322957f;
            } else {
              sum += -0.12993036211f;
            }
          }
        } else {
          sum += 0.16904510558f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          sum += 0.24573159218f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
            sum += -0.0508688353f;
          } else {
            sum += 0.12821666896f;
          }
        }
      }
    }
  } else {
    if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 4)) {
            sum += -0.056836605072f;
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 4)) {
              sum += -0.069990880787f;
            } else {
              sum += -0.28096026182f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
              sum += 0.17840486765f;
            } else {
              sum += -0.068046204746f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
              sum += -0.24451453984f;
            } else {
              sum += -0.0052292859182f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
          sum += -0.017667753622f;
        } else {
          sum += 0.3841201067f;
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 66)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 12)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 74)) {
              sum += 0.22787113488f;
            } else {
              sum += -0.021547155455f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
              sum += 0.092038393021f;
            } else {
              sum += -0.098534725606f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 104)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 32)) {
              sum += 0.4064194262f;
            } else {
              sum += 0.1718327105f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 24)) {
              sum += 0.14730158448f;
            } else {
              sum += -0.23401144147f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.15967026353f;
            } else {
              sum += 0.10873898119f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 6)) {
              sum += 0.35373300314f;
            } else {
              sum += -0.13493731618f;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 28)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
              sum += 0.32355859876f;
            } else {
              sum += -0.089662656188f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              sum += 0.18874563277f;
            } else {
              sum += -0.22365142405f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
      sum += 0.29458677769f;
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
        sum += 0.25016984344f;
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 88)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += -0.063703067601f;
            } else {
              sum += 0.24819402397f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += -0.15312279761f;
            } else {
              sum += 0.13126525283f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 14)) {
              sum += -0.47343194485f;
            } else {
              sum += -0.090710163116f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += 0.24261178076f;
            } else {
              sum += -0.15860070288f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 90)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
            sum += -0.12723988295f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += 0.31332859397f;
            } else {
              sum += 0.044398240745f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += -0.31183445454f;
            } else {
              sum += -0.052725844085f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 24)) {
              sum += -0.10601634532f;
            } else {
              sum += 0.23546741903f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
              sum += -0.11797583848f;
            } else {
              sum += 0.046824119985f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += -0.020240079612f;
            } else {
              sum += -0.26336354017f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += -0.084216199815f;
            } else {
              sum += -0.23540973663f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += 0.34673923254f;
            } else {
              sum += -0.2038167268f;
            }
          }
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 18)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 46)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += 0.30829757452f;
            } else {
              sum += 0.00083383865422f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
              sum += 0.15961517394f;
            } else {
              sum += 0.33807250857f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 6)) {
              sum += 0.22443333268f;
            } else {
              sum += -0.2311617583f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 42)) {
              sum += 0.34207192063f;
            } else {
              sum += -8.2389757154e-05f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 56)) {
              sum += -0.016271442175f;
            } else {
              sum += 0.34104123712f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += -0.22805765271f;
            } else {
              sum += 0.04616555199f;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 72)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 70)) {
              sum += 0.15732839704f;
            } else {
              sum += 0.60219293833f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += 0.26648926735f;
            } else {
              sum += -0.083006314933f;
            }
          }
        }
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].qvalue < 4)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
      sum += 0.29858720303f;
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 22)) {
        sum += 0.33472204208f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
          sum += -0.28018456697f;
        } else {
          sum += 0.0059531121515f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 2)) {
            sum += -0.28604459763f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
              sum += -0.25476381183f;
            } else {
              sum += 0.035523965955f;
            }
          }
        } else {
          sum += 0.24590776861f;
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 64)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
              sum += -0.1648709923f;
            } else {
              sum += 0.00015953411639f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 52)) {
              sum += 0.49101039767f;
            } else {
              sum += 0.032279625535f;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 36)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += -0.098402254283f;
            } else {
              sum += 0.22815079987f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
              sum += -0.23589171469f;
            } else {
              sum += 0.17132604122f;
            }
          }
        }
      }
    } else {
      if (!(data[17].missing != -1) || (data[17].qvalue < 6)) {
        sum += 0.31713068485f;
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 18)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 34)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.0024914839305f;
            } else {
              sum += 0.35635396838f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
              sum += 0.14433002472f;
            } else {
              sum += -0.4272890985f;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 74)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
              sum += 0.25797054172f;
            } else {
              sum += 0.05129962787f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += 0.21343784034f;
            } else {
              sum += -0.15114851296f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
        sum += 0.29462391138f;
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 12)) {
          sum += -0.02272833325f;
        } else {
          sum += 0.1805010885f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.0024260228965f;
            } else {
              sum += 0.2164631635f;
            }
          } else {
            sum += -0.11924818158f;
          }
        } else {
          sum += -0.45278093219f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
            sum += 0.28123870492f;
          } else {
            sum += 0.00077589513967f;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += 0.11655846983f;
            } else {
              sum += -0.17406772077f;
            }
          } else {
            sum += 0.1968460083f;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
      if (!(data[17].missing != -1) || (data[17].qvalue < 100)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 24)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 10)) {
              sum += 0.28359547257f;
            } else {
              sum += 0.053198408335f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 84)) {
              sum += 0.34856170416f;
            } else {
              sum += -0.13990230858f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 94)) {
              sum += 0.0094566550106f;
            } else {
              sum += -0.13245084882f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 30)) {
              sum += 0.42724880576f;
            } else {
              sum += -0.057563047856f;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 20)) {
          sum += 0.32876291871f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += 0.022987909615f;
            } else {
              sum += -0.30768024921f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 94)) {
              sum += 0.24504365027f;
            } else {
              sum += -0.097943708301f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 4)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
              sum += -0.21597702801f;
            } else {
              sum += 0.05506914109f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += 0.31829082966f;
            } else {
              sum += -0.067704088986f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += -0.21805845201f;
            } else {
              sum += -0.10373158753f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 50)) {
              sum += 0.4019035995f;
            } else {
              sum += -0.043489348143f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 76)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 34)) {
              sum += -0.063303992152f;
            } else {
              sum += 0.47147753835f;
            }
          } else {
            sum += -0.17288967967f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
              sum += 0.23191830516f;
            } else {
              sum += -0.12878778577f;
            }
          } else {
            sum += -0.23503807187f;
          }
        }
      }
    }
  }
  if (!(data[16].missing != -1) || (data[16].qvalue < 2)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[16].missing != -1) || (data[16].qvalue < 0)) {
        sum += 0.17855605483f;
      } else {
        sum += -0.18723513186f;
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
        sum += 0.027755327523f;
      } else {
        sum += 0.30348777771f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[17].missing != -1) || (data[17].qvalue < 66)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 46)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 14)) {
              sum += 0.10045398772f;
            } else {
              sum += -0.18641200662f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += 0.13263474405f;
            } else {
              sum += -0.2627620399f;
            }
          }
        } else {
          if (!(data[16].missing != -1) || (data[16].qvalue < 54)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 28)) {
              sum += 0.37201577425f;
            } else {
              sum += 0.087851934135f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += -0.21988292038f;
            } else {
              sum += 0.14413627982f;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 32)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 86)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 48)) {
              sum += -0.15667556226f;
            } else {
              sum += 0.53470957279f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 94)) {
              sum += 0.30569821596f;
            } else {
              sum += -0.033508051187f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 18)) {
              sum += -0.27966508269f;
            } else {
              sum += -0.14945179224f;
            }
          } else {
            sum += 0.24166713655f;
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 84)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 32)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 58)) {
              sum += 0.021368272603f;
            } else {
              sum += 0.31790953875f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += 0.14154182374f;
            } else {
              sum += 0.32879835367f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += 0.2687523067f;
            } else {
              sum += -0.0050522489473f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.15251123905f;
            } else {
              sum += -0.20186378062f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 52)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 38)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
              sum += -0.084606163204f;
            } else {
              sum += 0.24355690181f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += -0.2755446136f;
            } else {
              sum += 0.086600057781f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
              sum += 0.19645449519f;
            } else {
              sum += -0.20200304687f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 82)) {
              sum += 0.092714712024f;
            } else {
              sum += 0.39611598849f;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
        sum += 0.026803134009f;
      } else {
        sum += 0.29224768281f;
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += -0.10267566144f;
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 6)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 22)) {
              sum += -0.12070509791f;
            } else {
              sum += 0.18836130202f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
              sum += 0.079557359219f;
            } else {
              sum += 0.36191108823f;
            }
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 106)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.2288903892f;
            } else {
              sum += -0.047669991851f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += 0.045419026166f;
            } else {
              sum += 0.34187468886f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 4)) {
            sum += -0.27824124694f;
          } else {
            sum += -0.035352766514f;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
      if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 76)) {
          sum += 0.27212241292f;
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 60)) {
            sum += -0.15537847579f;
          } else {
            sum += 0.18798391521f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 66)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += -0.044104650617f;
            } else {
              sum += 0.091626226902f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += -0.022449381649f;
            } else {
              sum += -0.2098031193f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += -0.29772502184f;
            } else {
              sum += -0.11017179489f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 44)) {
              sum += 0.2100328058f;
            } else {
              sum += -0.068997502327f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
            sum += 0.089166097343f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
              sum += -0.30708035827f;
            } else {
              sum += -0.17455348372f;
            }
          }
        } else {
          sum += 0.12734414637f;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 20)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += -0.075515337288f;
            } else {
              sum += 0.30978110433f;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 74)) {
              sum += 0.79399979115f;
            } else {
              sum += 0.072295866907f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 22)) {
              sum += 0.095393203199f;
            } else {
              sum += -0.24112045765f;
            }
          } else {
            sum += 0.28711545467f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
    sum += 0.27994558215f;
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 22)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
              sum += -0.038561627269f;
            } else {
              sum += 0.3052277863f;
            }
          } else {
            sum += -0.22729380429f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
              sum += -0.16861408949f;
            } else {
              sum += 0.23084911704f;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 90)) {
              sum += -0.29018676281f;
            } else {
              sum += -0.099776178598f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 0)) {
          sum += -0.26847043633f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
              sum += -0.18503832817f;
            } else {
              sum += -0.0011118581751f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += 0.34364873171f;
            } else {
              sum += -0.10961853713f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 50)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.2275300473f;
            } else {
              sum += -0.030768861994f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
              sum += 0.3214610219f;
            } else {
              sum += 0.07978527993f;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 42)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += 0.21147678792f;
            } else {
              sum += -0.01334508881f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += 0.064134582877f;
            } else {
              sum += -0.2289314419f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 56)) {
            sum += -0.41728594899f;
          } else {
            sum += 0.23830072582f;
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 70)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
              sum += 0.14394249022f;
            } else {
              sum += 0.004239231348f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.14646650851f;
            } else {
              sum += 0.066642709076f;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
    if (!(data[16].missing != -1) || (data[16].qvalue < 10)) {
      sum += 0.28288927674f;
    } else {
      if (!(data[13].missing != -1) || (data[13].qvalue < 24)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 82)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
              sum += 0.10941775143f;
            } else {
              sum += -0.12699851394f;
            }
          } else {
            sum += 0.4031457603f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
            sum += -0.018666028976f;
          } else {
            sum += -0.26814737916f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            sum += -0.25222700834f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
              sum += 0.18591016531f;
            } else {
              sum += -0.048422466964f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += 0.11705862731f;
            } else {
              sum += 0.41175550222f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.2413457334f;
            } else {
              sum += -0.15224593878f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[17].missing != -1) || (data[17].qvalue < 98)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 6)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += -0.16073480248f;
            } else {
              sum += 0.20438404381f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 44)) {
              sum += -0.1093024984f;
            } else {
              sum += -0.28622379899f;
            }
          }
        } else {
          sum += 0.35946506262f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
              sum += 0.010374758393f;
            } else {
              sum += 0.13960270584f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += -0.12793271244f;
            } else {
              sum += 0.095044516027f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
              sum += 0.32474690676f;
            } else {
              sum += 0.057313811034f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.18547989428f;
            } else {
              sum += 0.050659187138f;
            }
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 16)) {
        sum += 0.29447552562f;
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 22)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            sum += 0.082422405481f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += -0.027137512341f;
            } else {
              sum += -0.30598402023f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.2126852721f;
            } else {
              sum += 0.020003817976f;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
              sum += 0.48221203685f;
            } else {
              sum += -0.081879734993f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}
