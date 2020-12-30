#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  41, 44, 33, 19, 58, 36, 
};
static const int th_begin[] = {
  0, 41, 85, 118, 137, 195, 
};
static const float threshold[] = {
  0.33813724f, 0.434102f, 0.47160321f, 0.48510009f, 0.48763385f, 0.49422124f, 
  0.50445914f, 0.54334676f, 0.5548563f, 0.55584383f, 0.55773896f, 0.61997473f, 
  0.63348269f, 0.68088454f, 0.68101573f, 0.76845932f, 0.82724154f, 0.84034848f, 
  0.84090757f, 0.86524117f, 0.86703897f, 0.86741155f, 0.88542187f, 0.8884933f, 
  0.90953183f, 0.91753793f, 0.91974151f, 0.9249649f, 0.92814183f, 0.94910097f, 
  0.96315539f, 0.96475756f, 0.97529978f, 0.97866821f, 0.97920632f, 0.99616367f, 
  0.99644172f, 0.99819154f, 0.99864107f, 0.99940073f, 0.99968743f, 1.2449419f, 
  1.2724141f, 2.0650768f, 2.8365886f, 3.214354f, 3.683073f, 3.8229434f, 3.860024f, 
  4.0877514f, 4.1118889f, 4.3575411f, 4.8685298f, 4.9979544f, 5.0002861f, 8.2378616f, 
  8.2609711f, 8.2669449f, 8.3051157f, 8.3386097f, 8.6837206f, 9.1037903f, 10.696224f, 
  10.730721f, 10.851654f, 11.01248f, 18.02508f, 18.575129f, 21.233706f, 21.920692f, 
  22.26012f, 56.992634f, 74.154045f, 85.522675f, 257.66187f, 268.70648f, 279.92755f, 
  7595.54f, 11751.005f, 12583.139f, 13996.582f, 14493.615f, 14579.729f, 16693.922f, 
  350196.31f, 1.2532418f, 1.2620261f, 1.2777283f, 1.4345261f, 1.8054945f, 2.3009524f, 
  2.7877765f, 3.936492f, 3.9393802f, 4.4251127f, 4.5591745f, 4.6816092f, 4.7572975f, 
  4.780138f, 5.187994f, 5.3641143f, 5.3753357f, 5.3955956f, 5.5115385f, 5.5926495f, 
  5.7060814f, 5.8355856f, 6.4642782f, 6.503623f, 7.7520924f, 9.4436722f, 10.544156f, 
  18.585178f, 18.709312f, 22.748825f, 23.263859f, 28.305035f, 158.50726f, 0.39283943f, 
  0.4784824f, 0.48374388f, 2.2374358f, 4.4652109f, 4.5315785f, 6.0595918f, 6.2516541f, 
  6.6745629f, 6.8797827f, 7.1317272f, 7.310339f, 7.3494501f, 10.564424f, 12.148163f, 
  14.535927f, 48.739182f, 104.06779f, 197533.41f, 133532, 152143, 153899, 198870, 
  200025.5f, 211532.5f, 270720, 288295, 311581.5f, 326813, 366652, 462431.5f, 
  626264, 747676, 901293, 924648.5f, 1075960.5f, 1091022.5f, 1115589, 1240538.5f, 
  1242137, 1252749.5f, 1633199.5f, 1635754, 1853090, 1892777.5f, 1894151.5f, 
  1909766, 2007044.5f, 2109241.5f, 2252383.5f, 2339791.5f, 2430256.5f, 2536365, 
  2986047, 3000860, 3191991.5f, 3211466.5f, 3233952, 3329415, 3726331.5f, 3820963, 
  3866174.5f, 3867017.5f, 5099054.5f, 6689550.5f, 6723729.5f, 6940319, 6946623.5f, 
  7030269, 7057871, 7406665, 7467714, 7532917, 7594183.5f, 7660754, 7716579, 
  8112693, 0.16015625f, 0.1875f, 0.20703125f, 0.24609375f, 0.27734375f, 0.28515625f, 
  0.30859375f, 0.33984375f, 0.35546875f, 0.37890625f, 0.38671875f, 0.39453125f, 
  0.41796875f, 0.44140625f, 0.47265625f, 0.48828125f, 0.53515625f, 0.5390625f, 
  0.54296875f, 0.55859375f, 0.58984375f, 0.59765625f, 0.60546875f, 0.63671875f, 
  0.64453125f, 0.66796875f, 0.71484375f, 0.73828125f, 0.75390625f, 0.83203125f, 
  0.8359375f, 0.84765625f, 0.85546875f, 0.87109375f, 0.89453125f, 0.91796875f, 
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
  if (offset == 231 || val < array[0]) {
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

  if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
        sum += 0.59760040045f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
          sum += 0.5586207509f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
            sum += -0.34285718203f;
          } else {
            sum += 0.30000001192f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
          sum += 0.54893618822f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += -.0f;
          } else {
            sum += -0.58222222328f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
            sum += 0.58002084494f;
          } else {
            sum += 0.17538462579f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
            sum += 0.2842105329f;
          } else {
            sum += -0.44788733125f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
            sum += -0.49090909958f;
          } else {
            sum += 0.30000001192f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
            sum += -0.50769233704f;
          } else {
            sum += -0.10000000894f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          sum += 0.56326532364f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
            sum += 0.30000001192f;
          } else {
            sum += -0.20000001788f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
            sum += -0.5341463685f;
          } else {
            sum += 0.24705883861f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
            sum += 0.43448275328f;
          } else {
            sum += -0.10000000894f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 62)) {
            sum += -0.46956524253f;
          } else {
            sum += 0.36000001431f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
            sum += -0.51293379068f;
          } else {
            sum += -0.59410727024f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
        sum += 0.4625095427f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            sum += 0.03596829623f;
          } else {
            sum += 0.442083776f;
          }
        } else {
          sum += -0.19332359731f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
          sum += 0.43016308546f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += -.0f;
          } else {
            sum += -0.45234778523f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
            sum += 0.45174333453f;
          } else {
            sum += 0.18868528306f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 74)) {
            sum += -0.31579479575f;
          } else {
            sum += 0.40604844689f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
            sum += -0.34454423189f;
          } else {
            sum += -0.11730224639f;
          }
        } else {
          sum += 0.21393895149f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
          sum += 0.45015874505f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
            sum += 0.31339225173f;
          } else {
            sum += -0.079627037048f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
            sum += 0.32101580501f;
          } else {
            sum += -0.35803097486f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
            sum += 0.10076247156f;
          } else {
            sum += 0.38877668977f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
            sum += -0.15199100971f;
          } else {
            sum += 0.19184918702f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
            sum += -0.34359532595f;
          } else {
            sum += -0.45871341228f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
        sum += 0.40243300796f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
          sum += -0.028115142137f;
        } else {
          sum += 0.26824104786f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.37366101146f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += -0.0034252607729f;
          } else {
            sum += -0.42609345913f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            sum += 0.39075505733f;
          } else {
            sum += -0.012269360013f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += 0.26371982694f;
          } else {
            sum += -0.27696993947f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 56)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
          sum += 0.024303613231f;
        } else {
          sum += -0.15688593686f;
        }
      } else {
        sum += 0.38139423728f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 50)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
            sum += -0.017988607287f;
          } else {
            sum += -0.3668577075f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
            sum += 0.41836804152f;
          } else {
            sum += -0.04417128861f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 46)) {
            sum += -0.35125541687f;
          } else {
            sum += 0.16209003329f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
            sum += -0.39707219601f;
          } else {
            sum += -0.083987243474f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            sum += 0.35738107562f;
          } else {
            sum += -0.46276131272f;
          }
        } else {
          sum += 0.36969611049f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            sum += -0.34027707577f;
          } else {
            sum += 0.19880089164f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
            sum += 0.32702988386f;
          } else {
            sum += -0.5073865056f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
          sum += 0.35994589329f;
        } else {
          sum += -0.071262523532f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            sum += -0.07880744338f;
          } else {
            sum += -0.37139314413f;
          }
        } else {
          sum += 0.079630754888f;
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
            sum += 0.10424041003f;
          } else {
            sum += -0.34755456448f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
            sum += -0.34556412697f;
          } else {
            sum += 0.066523067653f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 60)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            sum += 0.36585769057f;
          } else {
            sum += -0.1042072773f;
          }
        } else {
          sum += 0.38071876764f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
          sum += 0.36227139831f;
        } else {
          sum += -0.13968935609f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
            sum += 0.62203210592f;
          } else {
            sum += -0.27182614803f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
            sum += -0.24308530986f;
          } else {
            sum += -0.36350864172f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
        sum += 0.34805843234f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
            sum += 0.036101717502f;
          } else {
            sum += 0.3309994936f;
          }
        } else {
          sum += -0.31831794977f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.30835682154f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += 0.0082300519571f;
          } else {
            sum += -0.36972117424f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
            sum += 0.33502483368f;
          } else {
            sum += -0.1508757323f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
            sum += -0.25323858857f;
          } else {
            sum += 0.29647502303f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 50)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            sum += -0.29126170278f;
          } else {
            sum += 0.07971803844f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
            sum += -0.087185055017f;
          } else {
            sum += -0.35177963972f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
          sum += 0.34288311005f;
        } else {
          sum += -0.022386459634f;
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 44)) {
            sum += -0.058658778667f;
          } else {
            sum += 0.66320538521f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
            sum += -0.29259935021f;
          } else {
            sum += 0.32460251451f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
            sum += 0.051973160356f;
          } else {
            sum += -0.33004611731f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 86)) {
            sum += -0.34180226922f;
          } else {
            sum += -0.036329593509f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.33369788527f;
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.29325324297f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
            sum += 0.0069711552933f;
          } else {
            sum += -0.35481777787f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
            sum += 0.32852733135f;
          } else {
            sum += -0.080123946071f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
            sum += -0.1685372293f;
          } else {
            sum += 0.21802097559f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 60)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            sum += -0.25624188781f;
          } else {
            sum += 0.13889218867f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
            sum += -0.28188976645f;
          } else {
            sum += 0.12734951079f;
          }
        }
      } else {
        sum += 0.32345950603f;
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 58)) {
            sum += -0.16437205672f;
          } else {
            sum += 0.68359434605f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
            sum += -0.056699026376f;
          } else {
            sum += -0.30624657869f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
            sum += 0.19561220706f;
          } else {
            sum += -0.28517401218f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 72)) {
            sum += -0.32791301608f;
          } else {
            sum += -0.23771323264f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.32381913066f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += -0.042707413435f;
          } else {
            sum += 0.32057702541f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += 0.23490075767f;
          } else {
            sum += -0.24188880622f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
            sum += -0.20067365468f;
          } else {
            sum += 0.070259362459f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
            sum += 0.37416276336f;
          } else {
            sum += 0.078652173281f;
          }
        }
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 54)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
            sum += -0.2308511734f;
          } else {
            sum += 0.20558871329f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
            sum += -0.066330134869f;
          } else {
            sum += -0.31020700932f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
          sum += 0.31620433927f;
        } else {
          sum += -0.031762361526f;
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
            sum += -0.20084021986f;
          } else {
            sum += 0.36934900284f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
            sum += -0.055463958532f;
          } else {
            sum += -0.29096603394f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
            sum += 0.055850896984f;
          } else {
            sum += -0.30835413933f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 72)) {
            sum += -0.31608724594f;
          } else {
            sum += -0.21051287651f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.31648078561f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += -0.030946005136f;
          } else {
            sum += 0.30980104208f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
            sum += 0.22610139847f;
          } else {
            sum += -0.22062453628f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
            sum += -0.053884632885f;
          } else {
            sum += 0.18711934984f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
            sum += -0.11074481905f;
          } else {
            sum += -0.54942971468f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 66)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 52)) {
            sum += -0.20139355958f;
          } else {
            sum += 0.18526776135f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
            sum += -0.29756179452f;
          } else {
            sum += -0.10021867603f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
            sum += 0.056002106518f;
          } else {
            sum += 0.87693440914f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
            sum += 0.22603113949f;
          } else {
            sum += -0.22271156311f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 76)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          sum += -0.023365469649f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 80)) {
            sum += -0.31260570884f;
          } else {
            sum += -0.042711336166f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
          sum += 0.25534254313f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 84)) {
            sum += -0.098131082952f;
          } else {
            sum += -0.28791335225f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.31157121062f;
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            sum += 0.29339110851f;
          } else {
            sum += -0.06383612752f;
          }
        } else {
          sum += -0.3353151679f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
            sum += 0.29471424222f;
          } else {
            sum += 0.022694725543f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
            sum += 0.061396773905f;
          } else {
            sum += -0.33327555656f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            sum += 0.13670933247f;
          } else {
            sum += -0.2230656296f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
            sum += -0.27258324623f;
          } else {
            sum += 0.16807806492f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
            sum += 0.09492893517f;
          } else {
            sum += 0.5071799159f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
            sum += 0.27985194325f;
          } else {
            sum += -0.13684432209f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 68)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
            sum += 0.070657715201f;
          } else {
            sum += -0.29865401983f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
            sum += 0.38007900119f;
          } else {
            sum += -0.25382086635f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 72)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
            sum += -0.032221455127f;
          } else {
            sum += -0.29531437159f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
            sum += 0.47500807047f;
          } else {
            sum += -0.25655245781f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.30802923441f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
            sum += 0.26596641541f;
          } else {
            sum += -0.31429222226f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
            sum += 0.29750260711f;
          } else {
            sum += -0.03878043592f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
            sum += -0.26998871565f;
          } else {
            sum += -0.018209224567f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            sum += 0.31107056141f;
          } else {
            sum += 0.054304465652f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 66)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            sum += -0.14637072384f;
          } else {
            sum += 0.26327461004f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            sum += -0.11921041459f;
          } else {
            sum += -0.28783932328f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
            sum += 0.1548909992f;
          } else {
            sum += 0.63661044836f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
            sum += -0.16392797232f;
          } else {
            sum += 0.24228815734f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 76)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
            sum += -0.014641749673f;
          } else {
            sum += -0.30000835657f;
          }
        } else {
          sum += -0.0079043945298f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
          sum += 0.27026793361f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 84)) {
            sum += -0.047049891204f;
          } else {
            sum += -0.26476478577f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
        sum += 0.30479162931f;
      } else {
        sum += 0.087886109948f;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.24582241476f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            sum += -0.014121795073f;
          } else {
            sum += -0.30356571078f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
            sum += 0.27446949482f;
          } else {
            sum += -0.091269820929f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
            sum += -0.14402671158f;
          } else {
            sum += 0.23973169923f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 66)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            sum += 0.19489634037f;
          } else {
            sum += -0.25207585096f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
            sum += 0.11221659184f;
          } else {
            sum += -0.21456564963f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
          sum += 0.506118536f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
            sum += -0.16861262918f;
          } else {
            sum += 0.15886712074f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 76)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
            sum += -0.012483107857f;
          } else {
            sum += -0.29412645102f;
          }
        } else {
          sum += -0.0067416355014f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
          sum += 0.2037922442f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 84)) {
            sum += -0.038413889706f;
          } else {
            sum += -0.25099903345f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
        sum += 0.3024661839f;
      } else {
        sum += 0.03469574824f;
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += -0.035314466804f;
          } else {
            sum += 0.27598291636f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            sum += 0.19399477541f;
          } else {
            sum += -0.17030899227f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
            sum += -0.040136553347f;
          } else {
            sum += -0.40831619501f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            sum += 0.27977082133f;
          } else {
            sum += -0.0069101010449f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 64)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            sum += -0.10939674079f;
          } else {
            sum += 0.29943782091f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
            sum += -0.27972483635f;
          } else {
            sum += -0.013312813826f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
          sum += 0.77584409714f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
            sum += -0.12205248326f;
          } else {
            sum += 0.2372457087f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 78)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            sum += -0.031369000673f;
          } else {
            sum += -0.29585745931f;
          }
        } else {
          sum += -0.0075640184805f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
          sum += -0.23423728347f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            sum += 0.28001406789f;
          } else {
            sum += -0.073027200997f;
          }
        }
      }
    }
  }
  if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
      sum += 0.30003869534f;
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
          sum += 0.22849561274f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
            sum += -0.0066333939321f;
          } else {
            sum += -0.2881526351f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
            sum += 0.30218458176f;
          } else {
            sum += 0.023569105193f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
            sum += 0.063941419125f;
          } else {
            sum += -0.27982056141f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
            sum += 0.13751606643f;
          } else {
            sum += -0.18847879767f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
            sum += 0.24541290104f;
          } else {
            sum += -0.12034431845f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
            sum += -0.020326996222f;
          } else {
            sum += 0.61405903101f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            sum += 0.34952247143f;
          } else {
            sum += -0.11028090864f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 70)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
            sum += -0.15918761492f;
          } else {
            sum += 0.089294135571f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
            sum += -0.28839877248f;
          } else {
            sum += -0.0068707177415f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            sum += -0.16659624875f;
          } else {
            sum += 0.36999607086f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 80)) {
            sum += -0.26285174489f;
          } else {
            sum += -0.089350633323f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
      sum += 0.29849183559f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += -0.033741313964f;
          } else {
            sum += 0.22893239558f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
            sum += 0.083764068782f;
          } else {
            sum += -0.2515835166f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
            sum += -0.088932111859f;
          } else {
            sum += 0.10855562985f;
          }
        } else {
          sum += -0.39652308822f;
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 64)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
            sum += -0.19214463234f;
          } else {
            sum += 0.11225499213f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
            sum += -0.014525974169f;
          } else {
            sum += -0.29354122281f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
          sum += 0.47784337401f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
            sum += -0.082177005708f;
          } else {
            sum += 0.18287621439f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 76)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            sum += -0.03172699362f;
          } else {
            sum += -0.28351914883f;
          }
        } else {
          sum += -0.0058538499288f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 82)) {
          sum += 0.22165244818f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 84)) {
            sum += -0.016682378948f;
          } else {
            sum += -0.20733229816f;
          }
        }
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
      sum += 0.29562368989f;
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
            sum += 0.21715715528f;
          } else {
            sum += -0.25894251466f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            sum += -0.023534497246f;
          } else {
            sum += 0.29013115168f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
            sum += 0.077651895583f;
          } else {
            sum += -0.24514615536f;
          }
        } else {
          sum += 0.2758359611f;
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            sum += 0.066316671669f;
          } else {
            sum += -0.11100054532f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
            sum += 0.27875626087f;
          } else {
            sum += -0.034925311804f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
          sum += -0.060719478875f;
        } else {
          sum += 0.40474885702f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 70)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 48)) {
            sum += -0.073982961476f;
          } else {
            sum += 0.079148322344f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
            sum += -0.27542629838f;
          } else {
            sum += -0.0055607692339f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            sum += 0.6431338191f;
          } else {
            sum += -0.033146318048f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
            sum += -0.26351538301f;
          } else {
            sum += -0.077943056822f;
          }
        }
      }
    }
  }

    return 1.0f / (1 + expf(-sum));
}
