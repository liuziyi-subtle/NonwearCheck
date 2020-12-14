#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  38, 23, 49, 
};
static const int th_begin[] = {
  0, 38, 61, 
};

static const float threshold[] = {
  -0.48998308f, -0.31895161f, -0.22914788f, -0.19958925f, -0.13426775f, 0.13294336f, 
  0.17490628f, 0.18829681f, 0.19766745f, 0.22367245f, 0.27451199f, 0.27453083f, 
  0.2941277f, 0.30404258f, 0.31666833f, 0.35069716f, 0.35074413f, 0.39717644f, 
  0.40565243f, 0.40640911f, 0.49029529f, 0.50744057f, 0.51196039f, 0.5910688f, 
  0.62122977f, 0.63491881f, 0.66588151f, 0.69638526f, 0.71566379f, 0.77152699f, 
  0.77228248f, 0.8484807f, 0.86440104f, 0.87144637f, 0.87500727f, 0.89341855f, 
  0.89464939f, 0.96981549f, -0.23474532f, -0.17407721f, -0.17024156f, -0.12853628f, 
  -0.11454752f, -0.040892087f, -0.018570125f, -0.018481543f, -0.008762382f, 
  -0.0085188998f, 0.082658805f, 0.15389498f, 0.16702354f, 0.24844967f, 0.28165686f, 
  0.29874879f, 0.33011943f, 0.35054794f, 0.39939719f, 0.42589253f, 0.45443162f, 
  0.48274922f, 0.65433609f, 17.100561f, 20.442892f, 52.836441f, 53.655075f, 
  53.990768f, 60.824352f, 61.380779f, 61.931694f, 62.36982f, 79.752777f, 114.95081f, 
  134.91403f, 134.92896f, 160.25343f, 191.44254f, 201.88608f, 202.21297f, 246.85986f, 
  247.4808f, 260.04089f, 268.17368f, 317.62396f, 350.16745f, 369.50763f, 377.43341f, 
  410.55737f, 474.92627f, 538.94421f, 559.50879f, 658.4671f, 660.51672f, 683.25598f, 
  882.87537f, 980.72644f, 1159.1063f, 1249.5728f, 1297.8093f, 1300.9852f, 1378.7324f, 
  1611.8135f, 2388.1982f, 3191.1128f, 3622.552f, 3906.1099f, 5219.8828f, 7335.9004f, 
  7888.2461f, 14006.525f, 18556.023f
};

// #include <stdlib.h>

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
  if (offset == 110 || val < array[0]) {
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
  0, 0, 0, 
};


float PredictGreenAir(union NonwearEntry* data) {

  for (int i = 0; i < 3; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          sum += 0.56586128473f;
        } else {
          sum += 0.41707319021f;
        }
      } else {
        sum += -0.15000000596f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
          sum += 0.064615391195f;
        } else {
          sum += 0.46229508519f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
          sum += -0.29142859578f;
        } else {
          sum += 0.031578950584f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          sum += -0.20000001788f;
        } else {
          sum += 0.17391304672f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
          sum += -0.50123459101f;
        } else {
          sum += -0.19793814421f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
          sum += -0.3405405581f;
        } else {
          sum += 0.058064516634f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
          sum += -0.4894502461f;
        } else {
          sum += -0.56137627363f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
          sum += 0.097941294312f;
        } else {
          sum += 0.45222765207f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
          sum += 0.3169863224f;
        } else {
          sum += 0.42081922293f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
          sum += 0.055785693228f;
        } else {
          sum += 0.37939727306f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
          sum += 0.093945227563f;
        } else {
          sum += -0.24647973478f;
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          sum += -0.11372067034f;
        } else {
          sum += 0.35362583399f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 44)) {
          sum += -0.27722746134f;
        } else {
          sum += 0.17649072409f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
          sum += 0.3236207962f;
        } else {
          sum += -0.17814539373f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
          sum += -0.37261798978f;
        } else {
          sum += -0.43679997325f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
          sum += 0.37530991435f;
        } else {
          sum += -0.28483358026f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          sum += -0.1588652581f;
        } else {
          sum += 0.26130056381f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
          sum += -0.43870866299f;
        } else {
          sum += 0.098753608763f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 40)) {
          sum += 0.29461550713f;
        } else {
          sum += -0.16950070858f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
          sum += -0.055921025574f;
        } else {
          sum += -0.35145887733f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
          sum += 0.15401463211f;
        } else {
          sum += -0.14122889936f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          sum += -0.34463810921f;
        } else {
          sum += -0.15165133774f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          sum += -0.3959249258f;
        } else {
          sum += -0.35157960653f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          sum += 0.36295926571f;
        } else {
          sum += 0.28542482853f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
          sum += 0.27860683203f;
        } else {
          sum += 0.067752927542f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
          sum += -0.33217096329f;
        } else {
          sum += 0.0477351062f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
          sum += 0.25876706839f;
        } else {
          sum += -0.086390256882f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
          sum += -0.094539545476f;
        } else {
          sum += -0.33812990785f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
          sum += 0.1061976999f;
        } else {
          sum += -0.15285107493f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 42)) {
          sum += -0.24323551357f;
        } else {
          sum += -0.011542260647f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
          sum += -0.29299753904f;
        } else {
          sum += -0.34089165926f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          sum += 0.33684724569f;
        } else {
          sum += 0.25034594536f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
          sum += 0.13466410339f;
        } else {
          sum += 0.27973249555f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
          sum += -0.034141041338f;
        } else {
          sum += 0.26054164767f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
          sum += -0.13023839891f;
        } else {
          sum += 0.23008923233f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
          sum += -0.16198574007f;
        } else {
          sum += -0.30762290955f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
          sum += 0.0020982667338f;
        } else {
          sum += -0.1902551204f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
          sum += -0.18876378238f;
        } else {
          sum += -0.29839339852f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          sum += -0.33909451962f;
        } else {
          sum += -0.28938362002f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
          sum += 0.24742776155f;
        } else {
          sum += -0.057573121041f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
          sum += 0.28072801232f;
        } else {
          sum += -0.22075597942f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          sum += 0.030529789627f;
        } else {
          sum += -0.25552180409f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
          sum += 0.1656087935f;
        } else {
          sum += -0.13134926558f;
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
          sum += 0.18190659583f;
        } else {
          sum += -0.25424474478f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          sum += 0.20210671425f;
        } else {
          sum += -0.078055948019f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          sum += -0.29295390844f;
        } else {
          sum += -0.12189947814f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
          sum += -0.31184321642f;
        } else {
          sum += -0.26821869612f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          sum += 0.013577993028f;
        } else {
          sum += 0.31390693784f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          sum += 0.0460716784f;
        } else {
          sum += 0.29229846597f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          sum += 0.17360059917f;
        } else {
          sum += -0.21747331321f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          sum += 0.28270623088f;
        } else {
          sum += -0.039221625775f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
          sum += -0.059537291527f;
        } else {
          sum += -0.27864035964f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
          sum += 0.075244314969f;
        } else {
          sum += -0.068581044674f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
          sum += -0.045714959502f;
        } else {
          sum += -0.22222813964f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          sum += -0.29951322079f;
        } else {
          sum += -0.22340857983f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
          sum += 0.025596765801f;
        } else {
          sum += 0.2764595449f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
          sum += -0.1054558605f;
        } else {
          sum += 0.25641986728f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
          sum += 0.13035333157f;
        } else {
          sum += -0.21692924201f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
          sum += 0.26503190398f;
        } else {
          sum += -0.018603602424f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
          sum += -0.047693479806f;
        } else {
          sum += -0.22714008391f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
          sum += 0.053517673165f;
        } else {
          sum += -0.11304025352f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
          sum += -0.19949023426f;
        } else {
          sum += 0.088860377669f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
          sum += -0.25732591748f;
        } else {
          sum += -0.10013604909f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          sum += 0.0045757465996f;
        } else {
          sum += 0.29251080751f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          sum += -0.020609600469f;
        } else {
          sum += 0.25462028384f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
          sum += -0.27999570966f;
        } else {
          sum += 0.25474286079f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
          sum += 0.14645640552f;
        } else {
          sum += -0.17174308002f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
          sum += -0.060749255121f;
        } else {
          sum += -0.23160074651f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
          sum += 0.3473726809f;
        } else {
          sum += 0.0014359491179f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
          sum += -0.050918508321f;
        } else {
          sum += -0.19350664318f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          sum += -0.28449311852f;
        } else {
          sum += -0.18329298496f;
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          sum += 0.0035144430585f;
        } else {
          sum += 0.25754931569f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
          sum += -0.019235255197f;
        } else {
          sum += 0.21690574288f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
          sum += -0.025113224983f;
        } else {
          sum += -0.30174195766f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
          sum += 0.066420294344f;
        } else {
          sum += -0.089824646711f;
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
          sum += 0.054289370775f;
        } else {
          sum += -0.25857299566f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
          sum += 0.045380629599f;
        } else {
          sum += -0.16041339934f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
          sum += -0.27637729049f;
        } else {
          sum += -0.152767241f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
          sum += -0.047431390733f;
        } else {
          sum += -0.24611060321f;
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}