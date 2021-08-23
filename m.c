static const int th_len[] = {
  14, 3, 34, 36, 83, 50, 20, 4, 63, 30, 32, 19, 49, 16, 12, 43, 48, 56, 
};
static const int th_begin[] = {
  0, 14, 17, 51, 87, 170, 220, 240, 244, 307, 337, 369, 388, 437, 453, 465, 
  508, 556, 
};
static const float threshold[] = {
  5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 
  18.5, 2.5, 3.5, 4.5, -0.07726676, 0.01196653, 0.17538208, 0.18401957, 
  0.39565444, 0.41367358, 0.43571144, 0.4744826, 0.48399532, 0.50400865, 
  0.50827575, 0.52846742, 0.53389567, 0.53995991, 0.54709375, 0.56213546, 
  0.58840442, 0.60242939, 0.60301524, 0.60762703, 0.60840666, 0.63753903, 
  0.68028122, 0.71595836, 0.92362422, 0.93162465, 0.9464227, 0.94747674, 
  0.94802201, 0.97091627, 0.97331661, 0.97731704, 0.98171359, 0.98764658, 
  0.08984375, 0.11328125, 0.16015625, 0.18359375, 0.19140625, 0.21484375, 
  0.34375, 0.34765625, 0.3984375, 0.50390625, 0.55078125, 0.57421875, 
  0.58203125, 0.58984375, 0.60546875, 0.609375, 0.61328125, 0.62109375, 
  0.6484375, 0.66015625, 0.66796875, 0.67578125, 0.703125, 0.71484375, 0.71875, 
  0.73046875, 0.734375, 0.73828125, 0.78515625, 0.80078125, 0.81640625, 
  0.84765625, 0.85546875, 0.87890625, 0.88671875, 0.90234375, 34643.582, 
  38447.75, 38467.5, 39593.75, 39882.332, 39953.664, 39959.414, 40042.414, 
  40233.664, 40410.75, 40434.164, 40590.75, 40608, 40613.914, 40657.414, 
  40691.75, 41930.914, 41940.586, 41948.332, 42205.668, 42295, 42312.836, 
  42377.25, 42385.5, 42508.25, 42514.836, 42584.082, 42947.918, 42973, 
  42991.414, 42995.414, 43014.832, 43021, 43073.086, 43143.336, 43393.918, 
  44606.168, 46106, 46674.336, 48072.586, 48286.25, 48421.75, 49115.836, 
  49196.5, 49240.664, 49243.5, 49887.164, 50451.582, 50486.25, 51957.414, 
  52025.25, 52028.5, 52067.336, 52264.25, 52355.418, 52430.082, 52511.664, 
  52549.414, 52614.914, 52733.668, 52778, 52798.836, 52995.668, 53957.75, 
  54528.664, 54821.336, 55391.836, 55482.582, 55783.836, 55910.336, 55918, 
  57729.336, 57762.668, 57864.168, 57886, 58039.75, 58062, 58595.582, 
  58675.164, 58941.75, 59443.5, 59549.25, 60132.336, 0.12318092, 0.23768204, 
  0.2977204, 0.31728804, 0.40578794, 0.45188668, 0.45782596, 0.49665886, 
  0.50523138, 0.56509477, 0.57022727, 0.58068728, 0.6169368, 0.75006342, 
  0.75014985, 0.75480759, 0.7746408, 0.89476633, 0.89756459, 0.97937381, 
  0.97938871, 1.0132246, 1.0221617, 1.0576433, 1.097749, 1.1004905, 1.1351502, 
  1.1509182, 1.2131, 1.254575, 1.9684777, 2.0283475, 2.2424922, 2.2496157, 
  2.5124083, 2.7662849, 3.1362109, 3.3563333, 3.4166379, 3.6122532, 4.0726652, 
  4.5256777, 5.4473429, 7.027523, 13.155851, 14.6278, 21.335348, 71.786156, 
  74.782318, 180.55643, 0.36381966, 0.65197217, 0.71216726, 1.0732398, 
  1.8114218, 2.2290802, 2.3567371, 2.5402603, 3.2690687, 3.5834281, 5.8128028, 
  6.3872647, 8.2877789, 13.729689, 15.291656, 15.605924, 21.073444, 87.530525, 
  198.2778, 425.65878, 0.4309155, 0.92078543, 3.2354183, 21.805208, 
  -0.29281884, 0.029192956, 0.044279251, 0.082712471, 0.094917312, 0.096229546, 
  0.12516433, 0.13892627, 0.15650678, 0.16801992, 0.18788239, 0.22293563, 
  0.30706578, 0.34330955, 0.46465939, 0.50940597, 0.58012819, 0.58127272, 
  0.63851714, 0.67989641, 0.70896691, 0.73753929, 0.73814088, 0.73933733, 
  0.7500971, 0.75695467, 0.77988887, 0.78004557, 0.7816565, 0.78464699, 
  0.82874632, 0.84303904, 0.84317064, 0.8528775, 0.8717978, 0.91109896, 
  0.94621122, 0.95235425, 0.95948601, 0.99097359, 1.0000803, 1.0273918, 
  1.0655074, 1.0700331, 1.0703526, 1.1193798, 1.1705723, 1.2129314, 1.2195235, 
  1.2415314, 1.2444949, 1.2461989, 1.2515639, 1.3421199, 1.3495256, 1.3537767, 
  1.3860667, 1.4229428, 1.4243488, 1.4244479, 1.7055013, 1.7463195, 2.3778195, 
  0.36328125, 0.40234375, 0.42578125, 0.4296875, 0.43359375, 0.44140625, 
  0.45703125, 0.46875, 0.48046875, 0.48828125, 0.49609375, 0.50390625, 
  0.52734375, 0.53515625, 0.54296875, 0.55078125, 0.55859375, 0.58203125, 
  0.58984375, 0.59765625, 0.60546875, 0.61328125, 0.62109375, 0.62890625, 
  0.63671875, 0.64453125, 0.66015625, 0.66796875, 0.67578125, 0.68359375, 11.5, 
  13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22, 22.5, 23.5, 24.5, 
  25.5, 26.5, 28.5, 30.5, 31.5, 32.5, 33, 34.5, 35.5, 36.5, 37.5, 38.5, 40.5, 
  42.5, 43.5, 46.5, 47, 47.5, 7.5, 8.5, 9.5, 10.5, 19.5, 23.5, 24.5, 25.5, 
  31.5, 33.5, 36, 36.5, 39, 44.5, 52.5, 54.5, 56.5, 58.5, 82.5, 0.63423312, 
  1.284579, 1.4151607, 1.4251547, 1.4469798, 1.5938398, 1.6782629, 1.6836812, 
  1.6912355, 1.7102381, 1.7627941, 1.7744632, 1.792556, 1.8069855, 1.8416117, 
  1.847137, 1.8529687, 1.8587637, 1.8673677, 1.867655, 1.8720009, 1.8855101, 
  1.8869442, 1.8971574, 1.9098234, 1.9287667, 1.9289045, 1.940316, 1.9489263, 
  1.9564786, 1.9604049, 1.9662604, 1.9687066, 1.9751127, 1.9856753, 1.9902046, 
  1.9927046, 2.008014, 2.0102143, 2.0110621, 2.0168624, 2.0201144, 2.0632148, 
  2.0691881, 2.1301663, 2.1422801, 2.1516833, 2.1592617, 2.1784081, 19.386642, 
  41.331871, 114.35247, 160.92258, 319.67648, 418.25943, 425.53876, 664.02893, 
  684.47815, 741.2168, 845.73608, 870.46429, 881.76611, 4536.6274, 4727.3477, 
  25756.266, 1.4542208, 15.94846, 21.236355, 26.084591, 68.878082, 76.74543, 
  101.90022, 174.34875, 193.95618, 206.14981, 279.38654, 1336.1166, 1.1290144, 
  1.1341574, 1.3521463, 1.65625, 2.2360742, 2.3169856, 2.6373308, 2.8172331, 
  2.9083624, 3.9209979, 3.947973, 4.1201296, 4.2722535, 4.5111113, 4.5174417, 
  4.8290033, 4.9368353, 5.438262, 5.4421539, 5.4486842, 5.4733896, 5.9080338, 
  5.9293237, 6.1414285, 7.6576576, 7.8047619, 8.6046906, 8.7489262, 8.7631922, 
  9.4030275, 11.577381, 13.37586, 13.789726, 13.833498, 15.209303, 16.673759, 
  18.184452, 18.506098, 20.647869, 21.14819, 21.258013, 23.627777, 38.268257, 
  1.0942351, 1.2784238, 1.7245834, 1.8065015, 1.8382354, 1.8900967, 1.9126984, 
  2.2642705, 2.3985562, 2.4042859, 2.6099072, 3.244071, 3.2991991, 3.3436852, 
  3.5030065, 3.5159121, 3.7158537, 3.7935605, 4.2367148, 4.5347695, 4.6814013, 
  4.8937502, 5.6116962, 5.9749999, 6.3961239, 6.602273, 6.65625, 6.9761772, 
  8.2113628, 8.7084637, 8.9666328, 9.5905924, 9.8557644, 10.476732, 11.047269, 
  11.879021, 12.230159, 12.295454, 12.878676, 12.905506, 13.562039, 13.637769, 
  15.086081, 16.888405, 21.813469, 28.17742, 39.948215, 98.070786, 38612.5, 
  39295, 39303.5, 40343, 40364, 40501, 40730.5, 42248, 42656.5, 42969, 43127, 
  43143.5, 43146, 43166, 43172, 46771, 48962.5, 49043.5, 49137.5, 49285, 
  49322.5, 50374.5, 51051, 51390.5, 54679.5, 54831, 54913.5, 54917.5, 54989.5, 
  55014.5, 55044.5, 55099, 55331, 55418.5, 55579, 55609, 55734, 55825, 55911.5, 
  56089, 56347, 56877.5, 57737, 57876, 57877.5, 57991.5, 58098.5, 58232.5, 
  58451.5, 58589.5, 58590.5, 58621, 58640.5, 58942, 59530.5, 59839, 
};

#include <stdlib.h>

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

#include "header.h"

const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

size_t get_num_output_group(void) {
  return 1;
}

size_t get_num_feature(void) {
  return 18;
}

const char* get_pred_transform(void) {
  return "sigmoid";
}

float get_sigmoid_alpha(void) {
  return 1.0;
}

float get_global_bias(void) {
  return -0.0;
}

static inline float pred_transform(float margin) {
  const float alpha = (float)1.0;
  return 1.0f / (1 + expf(-alpha * margin));
}
float predict(union Entry* data, int pred_margin) {

  for (int i = 0; i < 18; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;
  unsigned int tmp;
  int nid, cond, fid;  /* used for folded subtrees */
  if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          sum += (float)0.33333337307;
        } else {
          sum += (float)-0.54000002146;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
              sum += (float)0.59733897448;
            } else {
              sum += (float)0.48776981235;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 84)) {
              sum += (float)0.52450335026;
            } else {
              sum += (float)-0.019354838878;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += (float)0.53846156597;
            } else {
              sum += (float)0.12000000477;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 16)) {
              sum += (float)-0.40800002217;
            } else {
              sum += (float)0.30000001192;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 2)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
            sum += (float)-0.44347828627;
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 60)) {
              sum += (float)0.49473688006;
            } else {
              sum += (float)-0.076923087239;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += (float)0.41538465023;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += (float)-0.024000000209;
            } else {
              sum += (float)-0.53605020046;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += (float)0.57230770588;
            } else {
              sum += (float)0.15000000596;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += (float)0.10000000894;
            } else {
              sum += (float)0.36000001431;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)0.054545458406;
            } else {
              sum += (float)0.50769233704;
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 16)) {
              sum += (float)0.17142859101;
            } else {
              sum += (float)-0.43529415131;
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
            sum += (float)-0;
          } else {
            sum += (float)0.46666669846;
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 26)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 12)) {
              sum += (float)-0.38181820512;
            } else {
              sum += (float)0.33333337307;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
              sum += (float)0.33333337307;
            } else {
              sum += (float)-0.48438540101;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 50)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
            sum += (float)0.59428572655;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 72)) {
              sum += (float)0.48847582936;
            } else {
              sum += (float)-0.26399999857;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0;
            } else {
              sum += (float)0.54418605566;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
              sum += (float)0.30000001192;
            } else {
              sum += (float)-0.43200004101;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
        sum += (float)0.57037043571;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 28)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += (float)-0;
            } else {
              sum += (float)0.49811324477;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 58)) {
              sum += (float)-0.52258068323;
            } else {
              sum += (float)0.42857146263;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += (float)-0.54858934879;
            } else {
              sum += (float)-0.33494704962;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
              sum += (float)-0.53575617075;
            } else {
              sum += (float)-0.58402431011;
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
          sum += (float)0.28256765008;
        } else {
          sum += (float)-0.42152893543;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
            sum += (float)0.46248143911;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
              sum += (float)0.41932231188;
            } else {
              sum += (float)-0.33114099503;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += (float)0.42178705335;
            } else {
              sum += (float)0.098638445139;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.3782106638;
            } else {
              sum += (float)0.039038814604;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
            sum += (float)-0.2812962532;
          } else {
            sum += (float)0.4732850492;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            sum += (float)0.38429662585;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              sum += (float)0.12044741958;
            } else {
              sum += (float)-0.43022191525;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += (float)0.12349229306;
            } else {
              sum += (float)0.45200824738;
            }
          } else {
            sum += (float)0.014694055542;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += (float)-0.3441811502;
            } else {
              sum += (float)0.34349066019;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += (float)-0.39711901546;
            } else {
              sum += (float)0.12538248301;
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
              sum += (float)0.36293870211;
            } else {
              sum += (float)-0.12472197413;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += (float)-0.063118822873;
            } else {
              sum += (float)-0.43179151416;
            }
          }
        } else {
          if (!(data[16].missing != -1) || (data[16].qvalue < 40)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 42)) {
              sum += (float)0.32960429788;
            } else {
              sum += (float)-0.13649515808;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += (float)-0.41581383348;
            } else {
              sum += (float)-0.00066691776738;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 48)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
            sum += (float)0.46539998055;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 78)) {
              sum += (float)0.38476115465;
            } else {
              sum += (float)-0.15070039034;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += (float)-0.26770871878;
            } else {
              sum += (float)0.39068222046;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += (float)-0.35487440228;
            } else {
              sum += (float)0.47333487868;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
        sum += (float)0.4406567812;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 58)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              sum += (float)-0.23646038771;
            } else {
              sum += (float)0.3075787425;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 62)) {
              sum += (float)-0.44101762772;
            } else {
              sum += (float)0.36729249358;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
              sum += (float)-0.031881153584;
            } else {
              sum += (float)-0.39483916759;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += (float)-0.44316241145;
            } else {
              sum += (float)-0.0029902490787;
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
          sum += (float)0.24599228799;
        } else {
          sum += (float)-0.33496963978;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
            sum += (float)0.40239670873;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += (float)-0.054696619511;
            } else {
              sum += (float)0.33049765229;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += (float)0.38581833243;
            } else {
              sum += (float)0.026081021875;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 32)) {
              sum += (float)0.29544639587;
            } else {
              sum += (float)-0.45779198408;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += (float)0.1449842751;
            } else {
              sum += (float)-0.35621625185;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 60)) {
              sum += (float)0.36742997169;
            } else {
              sum += (float)-0.03342731297;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            sum += (float)0.09459657222;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += (float)0.14081224799;
            } else {
              sum += (float)-0.39873385429;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += (float)0.10163195431;
            } else {
              sum += (float)0.38533166051;
            }
          } else {
            sum += (float)0.012315335684;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
              sum += (float)-0.13063083589;
            } else {
              sum += (float)0.35174319148;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += (float)0.27920281887;
            } else {
              sum += (float)-0.28421670198;
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
              sum += (float)-0.067123822868;
            } else {
              sum += (float)0.26629582047;
            }
          } else {
            sum += (float)0.40252262354;
          }
        } else {
          sum += (float)-0.029388871044;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += (float)0.36538505554;
            } else {
              sum += (float)-0.012470074929;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 16)) {
              sum += (float)0.15112408996;
            } else {
              sum += (float)-0.29787793756;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 76)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
              sum += (float)-0.075730681419;
            } else {
              sum += (float)0.39036527276;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 36)) {
              sum += (float)0.34053963423;
            } else {
              sum += (float)-0.19773751497;
            }
          }
        }
      }
    } else {
      if (!(data[17].missing != -1) || (data[17].qvalue < 12)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 10)) {
            sum += (float)-0.38420438766;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += (float)-0.22998984158;
            } else {
              sum += (float)0.26514065266;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 70)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 0)) {
              sum += (float)0.34901025891;
            } else {
              sum += (float)0.74395424128;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
              sum += (float)-0.16394692659;
            } else {
              sum += (float)0.36652618647;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 42)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 58)) {
              sum += (float)0.32352373004;
            } else {
              sum += (float)-0.073191732168;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 62)) {
              sum += (float)-0.37073078752;
            } else {
              sum += (float)0.35516315699;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 48)) {
              sum += (float)-0.19689168036;
            } else {
              sum += (float)-0.36692464352;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 0)) {
              sum += (float)0.046417012811;
            } else {
              sum += (float)-0.39374193549;
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
          sum += (float)0.21793077886;
        } else {
          sum += (float)-0.2911709547;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += (float)0.36728397012;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += (float)0.35333138704;
            } else {
              sum += (float)-0.11207612604;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 34)) {
              sum += (float)0.30774119496;
            } else {
              sum += (float)-0.33049660921;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 26)) {
              sum += (float)0.17634250224;
            } else {
              sum += (float)-0.25119122863;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
              sum += (float)0.27499583364;
            } else {
              sum += (float)-0.26429435611;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 80)) {
              sum += (float)0.32106015086;
            } else {
              sum += (float)-0.12279824913;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 30)) {
              sum += (float)-0.15998266637;
            } else {
              sum += (float)-0.37779703736;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += (float)0.11337772757;
            } else {
              sum += (float)0.36534261703;
            }
          } else {
            sum += (float)0.048560291529;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 40)) {
              sum += (float)0.33626753092;
            } else {
              sum += (float)0.025918271393;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += (float)-0.31982630491;
            } else {
              sum += (float)0.00026029054425;
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
            sum += (float)0.37468650937;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
              sum += (float)0.081432521343;
            } else {
              sum += (float)0.37096944451;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
              sum += (float)0.28520676494;
            } else {
              sum += (float)0.075940206647;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
              sum += (float)-0.31225159764;
            } else {
              sum += (float)0.054481532425;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
              sum += (float)-0.18616563082;
            } else {
              sum += (float)0.25959166884;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.3088079989;
            } else {
              sum += (float)-0.063353046775;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 74)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 50)) {
              sum += (float)0.28752163053;
            } else {
              sum += (float)-0.17142599821;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += (float)0.23170460761;
            } else {
              sum += (float)-0.25887769461;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 38)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += (float)-0.32751178741;
            } else {
              sum += (float)0.21644605696;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += (float)0.47596722841;
            } else {
              sum += (float)-0.10211931169;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 18)) {
              sum += (float)-0.13745805621;
            } else {
              sum += (float)0.56180334091;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 32)) {
              sum += (float)-0.26203280687;
            } else {
              sum += (float)-0.36571505666;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 44)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              sum += (float)0.11614735425;
            } else {
              sum += (float)0.44576734304;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 62)) {
              sum += (float)0.34026807547;
            } else {
              sum += (float)-0.28206285834;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 38)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 86)) {
              sum += (float)0.37770017982;
            } else {
              sum += (float)-0.28192019463;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 46)) {
              sum += (float)-0.060850117356;
            } else {
              sum += (float)-0.32179138064;
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
          sum += (float)0.15781721473;
        } else {
          sum += (float)-0.25914797187;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
            sum += (float)0.34531539679;
          } else {
            sum += (float)0.13784271479;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              sum += (float)0.33650392294;
            } else {
              sum += (float)-0.054010182619;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 54)) {
              sum += (float)0.25322678685;
            } else {
              sum += (float)-0.39762398601;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
          sum += (float)0.33903872967;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += (float)0.22900688648;
            } else {
              sum += (float)-0.069869175553;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 60)) {
              sum += (float)-0.25376406312;
            } else {
              sum += (float)0.25074872375;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += (float)0.063677467406;
            } else {
              sum += (float)0.33729737997;
            }
          } else {
            sum += (float)0.044877465814;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 54)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 78)) {
              sum += (float)0.28496825695;
            } else {
              sum += (float)-0.011580144055;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
              sum += (float)0.11898716539;
            } else {
              sum += (float)-0.27711233497;
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
            sum += (float)0.34537366033;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += (float)-0.13594676554;
            } else {
              sum += (float)0.25512167811;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
            sum += (float)0.23886916041;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += (float)0.08171608299;
            } else {
              sum += (float)-0.27986508608;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
              sum += (float)-0.32224148512;
            } else {
              sum += (float)0.22354714572;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += (float)0.019421830773;
            } else {
              sum += (float)-0.31066590548;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 78)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += (float)-0.23155373335;
            } else {
              sum += (float)0.21284069121;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 18)) {
              sum += (float)0.33088260889;
            } else {
              sum += (float)-0.22197124362;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 60)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 52)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += (float)0.31253027916;
            } else {
              sum += (float)-0.12710468471;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += (float)-0.045122835785;
            } else {
              sum += (float)-0.23779739439;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += (float)0.070138216019;
            } else {
              sum += (float)0.38611224294;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += (float)-0.32306152582;
            } else {
              sum += (float)-0.01152191218;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 14)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += (float)-0.3125641942;
            } else {
              sum += (float)0.35312104225;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
              sum += (float)-0.041531022638;
            } else {
              sum += (float)0.60141932964;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
              sum += (float)-0.32839563489;
            } else {
              sum += (float)-0.0026619108394;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 62)) {
              sum += (float)0.10950165242;
            } else {
              sum += (float)-0.32578623295;
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
          sum += (float)0.13778747618;
        } else {
          sum += (float)-0.21003425121;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          sum += (float)0.33030700684;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 28)) {
              sum += (float)0.046204119921;
            } else {
              sum += (float)0.3171865344;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += (float)-0.25346267223;
            } else {
              sum += (float)0.25409013033;
            }
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
            sum += (float)0.0091095641255;
          } else {
            sum += (float)-0.21856671572;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
              sum += (float)0.052239123732;
            } else {
              sum += (float)0.33360630274;
            }
          } else {
            sum += (float)0.049995809793;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
          sum += (float)0.33031243086;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += (float)-0.19976437092;
            } else {
              sum += (float)0.20373563468;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += (float)-0.11243911088;
            } else {
              sum += (float)0.28597143292;
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
              sum += (float)0.30264669657;
            } else {
              sum += (float)0.033031310886;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += (float)0.10118538141;
            } else {
              sum += (float)-0.21390987933;
            }
          }
        } else {
          sum += (float)0.45547148585;
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 8)) {
              sum += (float)0.21742065251;
            } else {
              sum += (float)-0.19526569545;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
              sum += (float)0.32708072662;
            } else {
              sum += (float)0.082675807178;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.21355827153;
            } else {
              sum += (float)0.24940873682;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 102)) {
              sum += (float)0.36287474632;
            } else {
              sum += (float)0.013167697005;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 40)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
              sum += (float)0.13788591325;
            } else {
              sum += (float)0.40729436278;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += (float)0.12947626412;
            } else {
              sum += (float)-0.18954847753;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 40)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += (float)-0.14728215337;
            } else {
              sum += (float)0.53141659498;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)-0.31191903353;
            } else {
              sum += (float)0.014139898121;
            }
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += (float)-0.31842914224;
            } else {
              sum += (float)0.14068588614;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 66)) {
              sum += (float)0.40664428473;
            } else {
              sum += (float)-0.077162452042;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
              sum += (float)-0.26635524631;
            } else {
              sum += (float)-0.31862056255;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 70)) {
              sum += (float)0.093894943595;
            } else {
              sum += (float)-0.30684614182;
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
          sum += (float)0.31947287917;
        } else {
          sum += (float)0.0503616184;
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += (float)0.2364436537;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
              sum += (float)-0.45640230179;
            } else {
              sum += (float)0.085940115154;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            sum += (float)0.3031218648;
          } else {
            sum += (float)-0.079565741122;
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 12)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
              sum += (float)-0.084736593068;
            } else {
              sum += (float)0.27475321293;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 28)) {
              sum += (float)-0.033979460597;
            } else {
              sum += (float)-0.32469755411;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
              sum += (float)0.30853030086;
            } else {
              sum += (float)-0.009003739804;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
              sum += (float)-0.2261710614;
            } else {
              sum += (float)0.18381141126;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
              sum += (float)0.21351660788;
            } else {
              sum += (float)-0.35827493668;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += (float)-0.19223158062;
            } else {
              sum += (float)0.23409105837;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            sum += (float)-0.30472123623;
          } else {
            sum += (float)-0.084688767791;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 80)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 48)) {
            sum += (float)0.32260388136;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += (float)-0.20963329077;
            } else {
              sum += (float)0.31490167975;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 8)) {
              sum += (float)-0.041997566819;
            } else {
              sum += (float)-0.20851649344;
            }
          } else {
            sum += (float)0.23560544848;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += (float)0.28671911359;
            } else {
              sum += (float)-0.19872890413;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += (float)0.11229535937;
            } else {
              sum += (float)-0.2257014662;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 52)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 80)) {
              sum += (float)0.24142748117;
            } else {
              sum += (float)-0.097526401281;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += (float)-0.26181223989;
            } else {
              sum += (float)0.051095116884;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 62)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 90)) {
              sum += (float)-0.07049716264;
            } else {
              sum += (float)-0.25693830848;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 36)) {
              sum += (float)-0.12425224483;
            } else {
              sum += (float)-0.31733268499;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 20)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += (float)-0.27433785796;
            } else {
              sum += (float)0.22112004459;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += (float)-0.30450257659;
            } else {
              sum += (float)-0.041054625064;
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 6)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
              sum += (float)0.45761555433;
            } else {
              sum += (float)0.19757010043;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 30)) {
              sum += (float)0.41822814941;
            } else {
              sum += (float)-0.17511898279;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 36)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 84)) {
              sum += (float)0.34431493282;
            } else {
              sum += (float)-0.2559543848;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += (float)-0.24311983585;
            } else {
              sum += (float)0.065449111164;
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
          sum += (float)0.31643736362;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += (float)0.013106036;
            } else {
              sum += (float)0.28416401148;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 10)) {
              sum += (float)0.21950185299;
            } else {
              sum += (float)-0.28721317649;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
            sum += (float)0.20385509729;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += (float)-0.48151025176;
            } else {
              sum += (float)-0.044732771814;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += (float)0.071515984833;
            } else {
              sum += (float)0.29655149579;
            }
          } else {
            sum += (float)-0.041348174214;
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          sum += (float)-0.099169820547;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            sum += (float)0.30556342006;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
              sum += (float)-0.15708942711;
            } else {
              sum += (float)0.20943079889;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 56)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += (float)-0.24800738692;
            } else {
              sum += (float)0.11560993642;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 0)) {
              sum += (float)-0.062377169728;
            } else {
              sum += (float)0.29793584347;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 20)) {
              sum += (float)-0.2256539613;
            } else {
              sum += (float)0.088598027825;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
              sum += (float)0.2580525279;
            } else {
              sum += (float)-0.065890274942;
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
              sum += (float)0.32366651297;
            } else {
              sum += (float)0.15020704269;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += (float)-0.061154041439;
            } else {
              sum += (float)0.24160833657;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 54)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
              sum += (float)0.11179368943;
            } else {
              sum += (float)-0.30392509699;
            }
          } else {
            sum += (float)0.29192981124;
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 26)) {
              sum += (float)-0.12738868594;
            } else {
              sum += (float)0.29772543907;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 6)) {
              sum += (float)-0.29551953077;
            } else {
              sum += (float)-0.17143067718;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += (float)-0.074366800487;
            } else {
              sum += (float)0.37467238307;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += (float)-0.097130589187;
            } else {
              sum += (float)0.16338917613;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 72)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 54)) {
              sum += (float)-0.011983100325;
            } else {
              sum += (float)-0.22455118597;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
              sum += (float)-0.27167236805;
            } else {
              sum += (float)0.098123975098;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 76)) {
              sum += (float)-0.2042734772;
            } else {
              sum += (float)0.2470291853;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
              sum += (float)0.057343021035;
            } else {
              sum += (float)-0.30805885792;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += (float)0.23009981215;
            } else {
              sum += (float)-0.12791584432;
            }
          } else {
            sum += (float)0.38274315;
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 52)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 68)) {
              sum += (float)0.018219910562;
            } else {
              sum += (float)-0.32194060087;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 96)) {
              sum += (float)0.28040897846;
            } else {
              sum += (float)-0.20866748691;
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
            sum += (float)0.31121122837;
          } else {
            sum += (float)0.074890874326;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
              sum += (float)0.29118698835;
            } else {
              sum += (float)0.099211454391;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
              sum += (float)-0.27726727724;
            } else {
              sum += (float)0.1929667294;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
          sum += (float)0.29972916842;
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += (float)-0.040229745209;
            } else {
              sum += (float)0.26481547952;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += (float)-0.42678904533;
            } else {
              sum += (float)0.15755410492;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 56)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += (float)-0.25641006231;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
              sum += (float)-0.20549632609;
            } else {
              sum += (float)0.18537828326;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
            sum += (float)0.20879238844;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 2)) {
              sum += (float)0.051701024175;
            } else {
              sum += (float)-0.24052120745;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 88)) {
            sum += (float)0.29399552941;
          } else {
            sum += (float)0.10157489032;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 82)) {
              sum += (float)-0.10939176381;
            } else {
              sum += (float)0.33047381043;
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 20)) {
              sum += (float)0.20082773268;
            } else {
              sum += (float)-0.22145117819;
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
              sum += (float)-0.12155405432;
            } else {
              sum += (float)0.3480335176;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.28045451641;
            } else {
              sum += (float)0.25244620442;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += (float)-0.1518702507;
            } else {
              sum += (float)0.18205034733;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
              sum += (float)-0.27506056428;
            } else {
              sum += (float)-0.1272135675;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 20)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 92)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)-0.027020437643;
            } else {
              sum += (float)0.26894050837;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += (float)0.22622351348;
            } else {
              sum += (float)-0.30104342103;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 58)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
              sum += (float)0.0021355096251;
            } else {
              sum += (float)0.24727658927;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += (float)-0.26460278034;
            } else {
              sum += (float)0.16707992554;
            }
          }
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 28)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 34)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 26)) {
              sum += (float)-0.21548427641;
            } else {
              sum += (float)-0.0085989627987;
            }
          } else {
            sum += (float)0.39913243055;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 8)) {
              sum += (float)-0.037010800093;
            } else {
              sum += (float)-0.2881359458;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 80)) {
              sum += (float)-0.18674580753;
            } else {
              sum += (float)0.13713060319;
            }
          }
        }
      } else {
        if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 30)) {
              sum += (float)-0.044954776764;
            } else {
              sum += (float)0.50190192461;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
              sum += (float)-0.012989006005;
            } else {
              sum += (float)-0.17234063148;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
              sum += (float)-0.10412351042;
            } else {
              sum += (float)0.77013206482;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)-0.30053466558;
            } else {
              sum += (float)-0.084900304675;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
        sum += (float)0.30824625492;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
          sum += (float)-0.2779045403;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 96)) {
              sum += (float)0.29423543811;
            } else {
              sum += (float)0.076840132475;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 18)) {
              sum += (float)0.27083772421;
            } else {
              sum += (float)-0.024962095544;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
        sum += (float)0.27056238055;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 20)) {
              sum += (float)-0.19453333318;
            } else {
              sum += (float)0.16349390149;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              sum += (float)-0.39206266403;
            } else {
              sum += (float)-0.085982523859;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
              sum += (float)0.34506911039;
            } else {
              sum += (float)-0.06215653941;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 62)) {
              sum += (float)0.31744837761;
            } else {
              sum += (float)-0.098841510713;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 16)) {
          sum += (float)0.30586060882;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += (float)0.23915244639;
            } else {
              sum += (float)-0.49332728982;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += (float)-0.31398651004;
            } else {
              sum += (float)0.18330425024;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 44)) {
              sum += (float)0.039747111499;
            } else {
              sum += (float)-0.16325117648;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += (float)0.0049931271933;
            } else {
              sum += (float)-0.25129079819;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 68)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += (float)0.083643600345;
            } else {
              sum += (float)0.37525349855;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += (float)0.3087631464;
            } else {
              sum += (float)-0.12774497271;
            }
          }
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 8)) {
            sum += (float)0.0070170816034;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += (float)-0.068259932101;
            } else {
              sum += (float)-0.27974849939;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            sum += (float)0.25203123689;
          } else {
            sum += (float)-0.190307796;
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 52)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 48)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
              sum += (float)0.19116678834;
            } else {
              sum += (float)-0.1332231611;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 64)) {
              sum += (float)0.87591427565;
            } else {
              sum += (float)-0.18509294093;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 34)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 92)) {
              sum += (float)-0.14443001151;
            } else {
              sum += (float)0.14374537766;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += (float)-0.28128638864;
            } else {
              sum += (float)0.15762661397;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
        sum += (float)0.30229324102;
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 20)) {
          sum += (float)0.28630173206;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
              sum += (float)-0.58440852165;
            } else {
              sum += (float)0.072840057313;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 46)) {
              sum += (float)-0.034439820796;
            } else {
              sum += (float)0.26372539997;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
            sum += (float)-0.0034223126713;
          } else {
            sum += (float)0.24215950072;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 42)) {
              sum += (float)-0.19142314792;
            } else {
              sum += (float)0.12733228505;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
              sum += (float)-0.35331234336;
            } else {
              sum += (float)0.020492099226;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              sum += (float)-0.12575829029;
            } else {
              sum += (float)0.2059930861;
            }
          } else {
            sum += (float)0.29464226961;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += (float)0.22381289303;
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 14)) {
              sum += (float)0.10175216198;
            } else {
              sum += (float)-0.15951687098;
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
            sum += (float)-0.070397056639;
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 6)) {
              sum += (float)-0.072970755398;
            } else {
              sum += (float)-0.29406479001;
            }
          }
        } else {
          sum += (float)0.34249839187;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += (float)-0.24659982324;
            } else {
              sum += (float)0.19872580469;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 86)) {
              sum += (float)0.47818517685;
            } else {
              sum += (float)-0.067639403045;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 36)) {
              sum += (float)-0.29104691744;
            } else {
              sum += (float)0.1452973485;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 54)) {
              sum += (float)-0.0029407269321;
            } else {
              sum += (float)-0.25309547782;
            }
          }
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 22)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 44)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += (float)0.30514258146;
            } else {
              sum += (float)0.0056497827172;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += (float)0.24539034069;
            } else {
              sum += (float)-0.22992087901;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += (float)0.14526534081;
            } else {
              sum += (float)0.41227337718;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += (float)-0.091237343848;
            } else {
              sum += (float)0.26812592149;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 8)) {
              sum += (float)0.31305125356;
            } else {
              sum += (float)-0.1729452014;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 82)) {
              sum += (float)0.43769815564;
            } else {
              sum += (float)-0.20105861127;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += (float)-0.14331170917;
            } else {
              sum += (float)0.34124517441;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)-0.22439694405;
            } else {
              sum += (float)0.07101970911;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
        sum += (float)0.3009506166;
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          sum += (float)0.26472076774;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
            sum += (float)-0.43786996603;
          } else {
            sum += (float)0.21113395691;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            sum += (float)-0.1327830106;
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 28)) {
              sum += (float)0.23348496854;
            } else {
              sum += (float)-0.029257196933;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += (float)0.012271196581;
            } else {
              sum += (float)-0.29072272778;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
              sum += (float)0.20753845572;
            } else {
              sum += (float)-0.18628180027;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          sum += (float)0.26480519772;
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 22)) {
            sum += (float)0.16151562333;
          } else {
            sum += (float)-0.053682867438;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 108)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 8)) {
            sum += (float)0.29682508111;
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 14)) {
              sum += (float)-0.1408329457;
            } else {
              sum += (float)0.25210830569;
            }
          }
        } else {
          sum += (float)-0.039298266172;
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
          sum += (float)0.34008958936;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 68)) {
              sum += (float)0.19113962352;
            } else {
              sum += (float)-0.18464826047;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 92)) {
              sum += (float)-0.20017530024;
            } else {
              sum += (float)0.14138866961;
            }
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 78)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 88)) {
              sum += (float)0.039581593126;
            } else {
              sum += (float)-0.14816258848;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 60)) {
              sum += (float)-0.053977388889;
            } else {
              sum += (float)-0.24005693197;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += (float)0.13893397152;
            } else {
              sum += (float)0.37843549252;
            }
          } else {
            sum += (float)-0.33361724019;
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 24)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += (float)-0.12116011232;
            } else {
              sum += (float)0.40264058113;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += (float)0.073481082916;
            } else {
              sum += (float)-0.25265899301;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 90)) {
              sum += (float)0.32034745812;
            } else {
              sum += (float)0.049399200827;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.27392143011;
            } else {
              sum += (float)-0.14305207133;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
        sum += (float)0.29810765386;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            sum += (float)-0.42251420021;
          } else {
            sum += (float)0.20122158527;
          }
        } else {
          sum += (float)0.25540548563;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
            sum += (float)0.19260597229;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += (float)0.1605322957;
            } else {
              sum += (float)-0.12993036211;
            }
          }
        } else {
          sum += (float)0.16904510558;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          sum += (float)0.24573159218;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
            sum += (float)-0.0508688353;
          } else {
            sum += (float)0.12821666896;
          }
        }
      }
    }
  } else {
    if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 4)) {
            sum += (float)-0.056836605072;
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 4)) {
              sum += (float)-0.069990880787;
            } else {
              sum += (float)-0.28096026182;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
              sum += (float)0.17840486765;
            } else {
              sum += (float)-0.068046204746;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
              sum += (float)-0.24451453984;
            } else {
              sum += (float)-0.0052292859182;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
          sum += (float)-0.017667753622;
        } else {
          sum += (float)0.3841201067;
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 66)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 12)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 74)) {
              sum += (float)0.22787113488;
            } else {
              sum += (float)-0.021547155455;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
              sum += (float)0.092038393021;
            } else {
              sum += (float)-0.098534725606;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 104)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 32)) {
              sum += (float)0.4064194262;
            } else {
              sum += (float)0.1718327105;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 24)) {
              sum += (float)0.14730158448;
            } else {
              sum += (float)-0.23401144147;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += (float)-0.15967026353;
            } else {
              sum += (float)0.10873898119;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 6)) {
              sum += (float)0.35373300314;
            } else {
              sum += (float)-0.13493731618;
            }
          }
        } else {
          if (!(data[17].missing != -1) || (data[17].qvalue < 28)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
              sum += (float)0.32355859876;
            } else {
              sum += (float)-0.089662656188;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              sum += (float)0.18874563277;
            } else {
              sum += (float)-0.22365142405;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
      sum += (float)0.29458677769;
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
        sum += (float)0.25016984344;
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 88)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += (float)-0.063703067601;
            } else {
              sum += (float)0.24819402397;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)-0.15312279761;
            } else {
              sum += (float)0.13126525283;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 14)) {
              sum += (float)-0.47343194485;
            } else {
              sum += (float)-0.090710163116;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += (float)0.24261178076;
            } else {
              sum += (float)-0.15860070288;
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
            sum += (float)-0.12723988295;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
              sum += (float)0.31332859397;
            } else {
              sum += (float)0.044398240745;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += (float)-0.31183445454;
            } else {
              sum += (float)-0.052725844085;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 24)) {
              sum += (float)-0.10601634532;
            } else {
              sum += (float)0.23546741903;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
              sum += (float)-0.11797583848;
            } else {
              sum += (float)0.046824119985;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += (float)-0.020240079612;
            } else {
              sum += (float)-0.26336354017;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += (float)-0.084216199815;
            } else {
              sum += (float)-0.23540973663;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += (float)0.34673923254;
            } else {
              sum += (float)-0.2038167268;
            }
          }
        }
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].qvalue < 18)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 46)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += (float)0.30829757452;
            } else {
              sum += (float)0.00083383865422;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
              sum += (float)0.15961517394;
            } else {
              sum += (float)0.33807250857;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 6)) {
              sum += (float)0.22443333268;
            } else {
              sum += (float)-0.2311617583;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 42)) {
              sum += (float)0.34207192063;
            } else {
              sum += (float)-8.2389757154e-05;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 56)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 56)) {
              sum += (float)-0.016271442175;
            } else {
              sum += (float)0.34104123712;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)-0.22805765271;
            } else {
              sum += (float)0.04616555199;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 72)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 70)) {
              sum += (float)0.15732839704;
            } else {
              sum += (float)0.60219293833;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += (float)0.26648926735;
            } else {
              sum += (float)-0.083006314933;
            }
          }
        }
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].qvalue < 4)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
      sum += (float)0.29858720303;
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 22)) {
        sum += (float)0.33472204208;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
          sum += (float)-0.28018456697;
        } else {
          sum += (float)0.0059531121515;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
      if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 2)) {
            sum += (float)-0.28604459763;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
              sum += (float)-0.25476381183;
            } else {
              sum += (float)0.035523965955;
            }
          }
        } else {
          sum += (float)0.24590776861;
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 64)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
              sum += (float)-0.1648709923;
            } else {
              sum += (float)0.00015953411639;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 52)) {
              sum += (float)0.49101039767;
            } else {
              sum += (float)0.032279625535;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 36)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += (float)-0.098402254283;
            } else {
              sum += (float)0.22815079987;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
              sum += (float)-0.23589171469;
            } else {
              sum += (float)0.17132604122;
            }
          }
        }
      }
    } else {
      if (!(data[17].missing != -1) || (data[17].qvalue < 6)) {
        sum += (float)0.31713068485;
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 18)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 34)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += (float)-0.0024914839305;
            } else {
              sum += (float)0.35635396838;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
              sum += (float)0.14433002472;
            } else {
              sum += (float)-0.4272890985;
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 74)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
              sum += (float)0.25797054172;
            } else {
              sum += (float)0.05129962787;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += (float)0.21343784034;
            } else {
              sum += (float)-0.15114851296;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
        sum += (float)0.29462391138;
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 12)) {
          sum += (float)-0.02272833325;
        } else {
          sum += (float)0.1805010885;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 50)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += (float)0.0024260228965;
            } else {
              sum += (float)0.2164631635;
            }
          } else {
            sum += (float)-0.11924818158;
          }
        } else {
          sum += (float)-0.45278093219;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
            sum += (float)0.28123870492;
          } else {
            sum += (float)0.00077589513967;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += (float)0.11655846983;
            } else {
              sum += (float)-0.17406772077;
            }
          } else {
            sum += (float)0.1968460083;
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
              sum += (float)0.28359547257;
            } else {
              sum += (float)0.053198408335;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 84)) {
              sum += (float)0.34856170416;
            } else {
              sum += (float)-0.13990230858;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 94)) {
              sum += (float)0.0094566550106;
            } else {
              sum += (float)-0.13245084882;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 30)) {
              sum += (float)0.42724880576;
            } else {
              sum += (float)-0.057563047856;
            }
          }
        }
      } else {
        if (!(data[16].missing != -1) || (data[16].qvalue < 20)) {
          sum += (float)0.32876291871;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += (float)0.022987909615;
            } else {
              sum += (float)-0.30768024921;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 94)) {
              sum += (float)0.24504365027;
            } else {
              sum += (float)-0.097943708301;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 4)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
              sum += (float)-0.21597702801;
            } else {
              sum += (float)0.05506914109;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += (float)0.31829082966;
            } else {
              sum += (float)-0.067704088986;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += (float)-0.21805845201;
            } else {
              sum += (float)-0.10373158753;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 50)) {
              sum += (float)0.4019035995;
            } else {
              sum += (float)-0.043489348143;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 76)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 34)) {
              sum += (float)-0.063303992152;
            } else {
              sum += (float)0.47147753835;
            }
          } else {
            sum += (float)-0.17288967967;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
              sum += (float)0.23191830516;
            } else {
              sum += (float)-0.12878778577;
            }
          } else {
            sum += (float)-0.23503807187;
          }
        }
      }
    }
  }
  if (!(data[16].missing != -1) || (data[16].qvalue < 2)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[16].missing != -1) || (data[16].qvalue < 0)) {
        sum += (float)0.17855605483;
      } else {
        sum += (float)-0.18723513186;
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
        sum += (float)0.027755327523;
      } else {
        sum += (float)0.30348777771;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[17].missing != -1) || (data[17].qvalue < 66)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 46)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 14)) {
              sum += (float)0.10045398772;
            } else {
              sum += (float)-0.18641200662;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += (float)0.13263474405;
            } else {
              sum += (float)-0.2627620399;
            }
          }
        } else {
          if (!(data[16].missing != -1) || (data[16].qvalue < 54)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 28)) {
              sum += (float)0.37201577425;
            } else {
              sum += (float)0.087851934135;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += (float)-0.21988292038;
            } else {
              sum += (float)0.14413627982;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 32)) {
          if (!(data[17].missing != -1) || (data[17].qvalue < 86)) {
            if (!(data[16].missing != -1) || (data[16].qvalue < 48)) {
              sum += (float)-0.15667556226;
            } else {
              sum += (float)0.53470957279;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 94)) {
              sum += (float)0.30569821596;
            } else {
              sum += (float)-0.033508051187;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 18)) {
              sum += (float)-0.27966508269;
            } else {
              sum += (float)-0.14945179224;
            }
          } else {
            sum += (float)0.24166713655;
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 84)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 32)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 58)) {
              sum += (float)0.021368272603;
            } else {
              sum += (float)0.31790953875;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += (float)0.14154182374;
            } else {
              sum += (float)0.32879835367;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += (float)0.2687523067;
            } else {
              sum += (float)-0.0050522489473;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += (float)0.15251123905;
            } else {
              sum += (float)-0.20186378062;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 52)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 38)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
              sum += (float)-0.084606163204;
            } else {
              sum += (float)0.24355690181;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += (float)-0.2755446136;
            } else {
              sum += (float)0.086600057781;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
              sum += (float)0.19645449519;
            } else {
              sum += (float)-0.20200304687;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 82)) {
              sum += (float)0.092714712024;
            } else {
              sum += (float)0.39611598849;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
        sum += (float)0.026803134009;
      } else {
        sum += (float)0.29224768281;
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
          sum += (float)-0.10267566144;
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 6)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 22)) {
              sum += (float)-0.12070509791;
            } else {
              sum += (float)0.18836130202;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
              sum += (float)0.079557359219;
            } else {
              sum += (float)0.36191108823;
            }
          }
        }
      } else {
        if (!(data[17].missing != -1) || (data[17].qvalue < 106)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += (float)-0.2288903892;
            } else {
              sum += (float)-0.047669991851;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += (float)0.045419026166;
            } else {
              sum += (float)0.34187468886;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 4)) {
            sum += (float)-0.27824124694;
          } else {
            sum += (float)-0.035352766514;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
      if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 76)) {
          sum += (float)0.27212241292;
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 60)) {
            sum += (float)-0.15537847579;
          } else {
            sum += (float)0.18798391521;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 66)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
              sum += (float)-0.044104650617;
            } else {
              sum += (float)0.091626226902;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += (float)-0.022449381649;
            } else {
              sum += (float)-0.2098031193;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += (float)-0.29772502184;
            } else {
              sum += (float)-0.11017179489;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 44)) {
              sum += (float)0.2100328058;
            } else {
              sum += (float)-0.068997502327;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
            sum += (float)0.089166097343;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
              sum += (float)-0.30708035827;
            } else {
              sum += (float)-0.17455348372;
            }
          }
        } else {
          sum += (float)0.12734414637;
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 20)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += (float)-0.075515337288;
            } else {
              sum += (float)0.30978110433;
            }
          } else {
            if (!(data[16].missing != -1) || (data[16].qvalue < 74)) {
              sum += (float)0.79399979115;
            } else {
              sum += (float)0.072295866907;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
            if (!(data[17].missing != -1) || (data[17].qvalue < 22)) {
              sum += (float)0.095393203199;
            } else {
              sum += (float)-0.24112045765;
            }
          } else {
            sum += (float)0.28711545467;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
    sum += (float)0.27994558215;
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
          if (!(data[16].missing != -1) || (data[16].qvalue < 22)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
              sum += (float)-0.038561627269;
            } else {
              sum += (float)0.3052277863;
            }
          } else {
            sum += (float)-0.22729380429;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
              sum += (float)-0.16861408949;
            } else {
              sum += (float)0.23084911704;
            }
          } else {
            if (!(data[17].missing != -1) || (data[17].qvalue < 90)) {
              sum += (float)-0.29018676281;
            } else {
              sum += (float)-0.099776178598;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 0)) {
          sum += (float)-0.26847043633;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
              sum += (float)-0.18503832817;
            } else {
              sum += (float)-0.0011118581751;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += (float)0.34364873171;
            } else {
              sum += (float)-0.10961853713;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
        if (!(data[16].missing != -1) || (data[16].qvalue < 50)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += (float)0.2275300473;
            } else {
              sum += (float)-0.030768861994;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
              sum += (float)0.3214610219;
            } else {
              sum += (float)0.07978527993;
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 42)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += (float)0.21147678792;
            } else {
              sum += (float)-0.01334508881;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += (float)0.064134582877;
            } else {
              sum += (float)-0.2289314419;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 56)) {
            sum += (float)-0.41728594899;
          } else {
            sum += (float)0.23830072582;
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 70)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
              sum += (float)0.14394249022;
            } else {
              sum += (float)0.004239231348;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += (float)-0.14646650851;
            } else {
              sum += (float)0.066642709076;
            }
          }
        }
      }
    }
  }
  if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
    if (!(data[16].missing != -1) || (data[16].qvalue < 10)) {
      sum += (float)0.28288927674;
    } else {
      if (!(data[13].missing != -1) || (data[13].qvalue < 24)) {
        if (!(data[17].missing != -1) || (data[17].qvalue < 82)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
              sum += (float)0.10941775143;
            } else {
              sum += (float)-0.12699851394;
            }
          } else {
            sum += (float)0.4031457603;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
            sum += (float)-0.018666028976;
          } else {
            sum += (float)-0.26814737916;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            sum += (float)-0.25222700834;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
              sum += (float)0.18591016531;
            } else {
              sum += (float)-0.048422466964;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += (float)0.11705862731;
            } else {
              sum += (float)0.41175550222;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += (float)0.2413457334;
            } else {
              sum += (float)-0.15224593878;
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
              sum += (float)-0.16073480248;
            } else {
              sum += (float)0.20438404381;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 44)) {
              sum += (float)-0.1093024984;
            } else {
              sum += (float)-0.28622379899;
            }
          }
        } else {
          sum += (float)0.35946506262;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
              sum += (float)0.010374758393;
            } else {
              sum += (float)0.13960270584;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += (float)-0.12793271244;
            } else {
              sum += (float)0.095044516027;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
              sum += (float)0.32474690676;
            } else {
              sum += (float)0.057313811034;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += (float)-0.18547989428;
            } else {
              sum += (float)0.050659187138;
            }
          }
        }
      }
    } else {
      if (!(data[16].missing != -1) || (data[16].qvalue < 16)) {
        sum += (float)0.29447552562;
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 22)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            sum += (float)0.082422405481;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += (float)-0.027137512341;
            } else {
              sum += (float)-0.30598402023;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += (float)-0.2126852721;
            } else {
              sum += (float)0.020003817976;
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
              sum += (float)0.48221203685;
            } else {
              sum += (float)-0.081879734993;
            }
          }
        }
      }
    }
  }

  sum = sum + (float)(-0);
  if (!pred_margin) {
    return pred_transform(sum);
  } else {
    return sum;
  }
}
