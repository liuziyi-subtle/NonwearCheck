#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const int th_len[] = {
  7, 20, 14, 8, 
};
static const int th_begin[] = {
  0, 7, 27, 41, 
};
static const float threshold[] = {
  0.14973632f, 0.24984962f, 0.29465514f, 0.31353813f, 0.36875707f, 0.3780601f, 
  0.41111708f, -4937.9561f, -4937.9521f, -4937.6641f, -4937.6279f, -4937.0557f, 
  -4332.4761f, -4332.252f, -4326.7363f, -4301.8398f, -4300.8477f, -4283.3604f, 
  -4282.4678f, -4280.9443f, -4275.7759f, -4275.7197f, -4275.3838f, -4264.8198f, 
  -4107.7202f, 1200.464f, 3138.1599f, 0.22662477f, 0.24739307f, 0.2488142f, 
  0.26513475f, 0.34567547f, 0.38170576f, 0.39236313f, 0.47202241f, 0.55930245f, 
  0.63235235f, 0.72036684f, 0.78415418f, 0.79300165f, 0.802414f, -4929.8018f, 
  -4928.3506f, -4928.3281f, -4270.6357f, -4256.0361f, -4253.9492f, -4170.6816f, 
  -2402.9102f, 
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
  if (offset == 49 || val < array[0]) {
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
  0, 0, 0, 0, 
};


float PredictGreenAir(union NonwearEntry* data) {

  for (int i = 0; i < 4; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  float sum = 0.0f;

  // int nid, cond, fid;  /* used for folded subtrees */
  if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
        sum += 0.5758613348f;
      } else {
        sum += 0.26820811629f;
      }
    } else {
      sum += -0.58297878504f;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
        sum += 0.54672896862f;
      } else {
        sum += 0.018181819469f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        sum += -0.23636364937f;
      } else {
        sum += -0.58720684052f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 36)) {
        sum += 0.44539502263f;
      } else {
        sum += -0.31509113312f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
        sum += 0.35275769234f;
      } else {
        sum += -0.16109628975f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += 0.089764639735f;
      } else {
        sum += 0.39472055435f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
        sum += -0.054253302515f;
      } else {
        sum += -0.45579972863f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
        sum += 0.39326456189f;
      } else {
        sum += 0.31581577659f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
        sum += 0.33712053299f;
      } else {
        sum += -0.28241622448f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
        sum += 0.46724835038f;
      } else {
        sum += 0.11083798856f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
        sum += -0.0005784817622f;
      } else {
        sum += -0.39035239816f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
        sum += 0.35940790176f;
      } else {
        sum += 0.30378162861f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
        sum += 0.27901926637f;
      } else {
        sum += -0.21042302251f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += -0.037932924926f;
      } else {
        sum += 0.31913524866f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
        sum += -0.070262528956f;
      } else {
        sum += -0.3536939621f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
        sum += 0.34279125929f;
      } else {
        sum += 0.26615962386f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
        sum += 0.31207123399f;
      } else {
        sum += 0.01833082363f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
        sum += 0.39883828163f;
      } else {
        sum += -0.0021755255293f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
        sum += 0.10109718889f;
      } else {
        sum += -0.32426279783f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
        sum += 0.32368266582f;
      } else {
        sum += 0.23075826466f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        sum += 0.34839898348f;
      } else {
        sum += 0.028979631141f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += -0.12810260057f;
      } else {
        sum += 0.27291113138f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
        sum += 0.0018596138107f;
      } else {
        sum += -0.3067612946f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
        sum += 0.31125545502f;
      } else {
        sum += 0.2219697088f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        sum += 0.34223812819f;
      } else {
        sum += -0.080309070647f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += -0.058273475617f;
      } else {
        sum += 0.34631922841f;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
        sum += -0.11889922619f;
      } else {
        sum += -0.2999458909f;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
        sum += 0.20918171108f;
      } else {
        sum += 0.32265692949f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
        sum += -1.6700716019f;
      } else {
        sum += 0.20108088851f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
      sum += 0.37060129642f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
        sum += -0.7996532321f;
      } else {
        sum += -0.18332260847f;
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 38)) {
        sum += 0.269656986f;
      } else {
        sum += -0.37977534533f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        sum += 0.33237493038f;
      } else {
        sum += -0.063064195216f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
        sum += 0.051067959517f;
      } else {
        sum += 0.31389757991f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
        sum += -0.57237321138f;
      } else {
        sum += -0.26010629535f;
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
        sum += 0.31807222962f;
      } else {
        sum += -0.76023346186f;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        sum += 0.33198809624f;
      } else {
        sum += 0.089419931173f;
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 34)) {
        sum += -0.85116714239f;
      } else {
        sum += 0.28294548392f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
        sum += -0.15572485328f;
      } else {
        sum += -0.2864048183f;
      }
    }
  }
  
  return 1.0f / (1 + expf(-sum));
}