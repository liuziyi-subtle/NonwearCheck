#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 0.5f, 2.5f, 3.5f, 4.5f, 
  5.5f, 6.5f, 0.26280659f, 0.30145776f, 0.3082124f, 0.33080837f, 0.33855149f, 
  0.38389271f, 0.40647578f, 0.44542927f, 0.4654488f, 0.4665114f, 0.4862833f, 
  0.48810303f, 0.48823622f, 0.48904812f, 0.4913379f, 0.50625491f, 0.51504451f, 
  0.5151177f, 0.55303335f, 0.55389249f, 0.5598048f, 0.57669753f, 0.58856273f, 
  0.59340847f, 0.60404992f, 0.632056f, 0.63464618f, 0.64494264f, 0.65450466f, 
  0.67883658f, 0.70607173f, 0.73592705f, 0.76163518f, 0.76695752f, 0.77069348f, 
  0.77953184f, 0.7826606f, 0.79188871f, 0.79197848f, 0.82058161f, 0.82504863f, 
  0.83091968f, 0.8399111f, 0.84877777f, 0.85227132f, 0.86007667f, 0.86658454f, 
  0.8694272f, 0.87978834f, 0.88178837f, 0.88391221f, 0.89267766f, 0.89415842f, 
  0.90019906f, 0.90713972f, 0.91069603f, 0.92023075f, 0.93633866f, 0.93740445f, 
  0.93753612f, 0.93919563f, 0.93939012f, 0.94687122f, 0.96162426f, 0.9624244f, 
  0.96391314f, 0.97452801f, -1492.7782f, -1492.5929f, -1486.9408f, -1438.9088f, 
  -999.23163f, -981.22675f, -965.42596f, -961.14685f, -951.62811f, -950.52478f, 
  -943.81189f, -17.249001f, -11.826834f, 3.6577501f, 33.0005f, 35.207249f, 39.280666f, 
  49.562164f, 56.933666f, 68.060577f, 79.16275f, 82.555916f, 95.312088f, 95.69175f, 
  123.60634f, 162.10901f, 165.79591f, 169.55092f, 182.03134f, 182.19925f, 183.32541f, 
  184.25009f, 191.17609f, 192.62991f, 195.20499f, 195.67741f, 212.6785f, 236.72484f, 
  239.65726f, 254.95432f, 255.13434f, 270.21527f, 274.38977f, 300.56598f, 321.366f, 
  321.68274f, 327.17407f, 331.02951f, 331.38275f, 337.51416f, 338.22565f, 339.74808f, 
  409.82016f, 419.82675f, 428.50323f, 430.12192f, 435.43427f, 436.48575f, 445.36615f, 
  454.80206f, 460.793f, 463.05765f, 479.68991f, 479.94348f, 492.12415f, 529.50208f, 
  565.80249f, 566.00122f, 597.37634f, 609.69092f, 655.21875f, 665.28284f, 672.00891f, 
  684.6759f, 690.57648f, 723.91425f, 797.599f, 803.0495f, 803.39484f, 803.76184f, 
  833.87317f, 834.14233f, 837.302f, 948.42395f, 973.18921f, 975.46326f, 1037.7012f, 
  1070.3599f, 1116.4377f, 1150.6405f, 1151.165f, 1151.3282f, 1152.0979f, 1165.5018f, 
  1166.2544f, 1186.985f, 1187.1089f, 1187.4435f, 1190.8079f, 1206.9915f, 1209.7529f, 
  1229.2297f, 1259.2158f, 1292.9072f, 1295.2058f, 1295.9866f, 1302.9644f, 1311.0874f, 
  1313.3351f, 1335.4336f, 1337.2859f, 1339.093f, 1341.7512f, 1344.4583f, 1352.0193f, 
  1353.054f, 1358.0034f, 1381.2488f, 1396.3114f, 1396.7883f, 1399.6267f, 1415.4343f, 
  1419.7573f, 1493.5161f, 1493.7749f, 1565.0718f, 1578.5824f, 1664.7371f, 1670.0425f, 
  1682.6553f, 1710.0203f, 1721.879f, 1771.5273f, 1788.7603f, 1823.6462f, 1837.2317f, 
  1845.5994f, 1847.3748f, 1849.1904f, 1852.4447f, 1859.6396f, 1866.3251f, 1869.3081f, 
  1872.2273f, 1885.7937f, 1894.0865f, 1899.4484f, 1903.6151f, 1936.4729f, 1959.8884f, 
  1963.6121f, 1973.5896f, 1983.8394f, 1984.7576f, 1988.3912f, 2089.0105f, 2115.043f, 
  2196.9976f, 2240.731f, 2268.1948f, 2277.2178f, 2350.5542f, 2433.9697f, 2480.1519f, 
  2482.5435f, 2483.1387f, 2520.1719f, 2522.7424f, 2524.6396f, 2548.6035f, 2744.7463f, 
  2757.3218f, 2788.1648f, 2797.1221f, 3254.2192f, 3291.6499f, 3494.0637f, 3551.998f, 
  3704.6782f, 3913.1741f, 0.014324183f, 0.014859611f, 0.0207441f, 0.024892587f, 
  0.026879404f, 0.028311737f, 0.028322214f, 0.02836925f, 0.028708555f, 0.032899693f, 
  0.033214778f, 0.036542665f, 0.036557429f, 0.038852558f, 0.039813161f, 0.040195815f, 
  0.043944892f, 0.043997079f, 0.044633716f, 0.045352865f, 0.046798684f, 0.047207884f, 
  0.048963577f, 0.049692333f, 0.050908353f, 0.058300782f, 0.060648441f, 0.060980313f, 
  0.06830129f, 0.076966926f, 0.077181384f, 0.07923691f, 0.081369407f, 0.086783916f, 
  0.092790969f, 0.093492329f, 0.094799735f, 0.096839741f, 0.097862214f, 0.10072196f, 
  0.10131152f, 0.10135812f, 0.10375054f, 0.10851949f, 0.10902482f, 0.11535632f, 
  0.12103017f, 0.12142327f, 0.12166037f, 0.12663524f, 0.14281482f, 0.15670425f, 
  0.1589565f, 0.16011781f, 0.16255033f, 0.16427287f, 0.1708293f, 0.17221677f, 
  0.17458081f, 0.17536771f, 0.17684555f, 0.18180931f, 0.18716818f, 0.20145658f, 
  0.22813648f, 0.24210703f, 0.24411996f, 0.24677005f, 0.26043266f, 0.26045457f, 
  0.26167619f, 0.26329863f, 0.27610281f, 0.39681506f, 0.42760968f, 0.46822429f, 
  0.47135231f, 0.48412341f, 0.53028953f, 0.58791196f, 0.61542535f, 0.74104714f, 
  0.75640392f, 0.76987481f, 1.2045507f, 1.8398471f, 1.8821061f, 2.0967135f, 
  2.2688556f, 9.6078262f, 14.985391f, 17.439602f, 17.447453f, 25.75672f, 31.185154f, 
  31.499981f, 65.926636f, 0.034576349f, 0.062846139f, 0.071310386f, 0.096263155f, 
  0.09637925f, 0.098636195f, 0.10353023f, 0.11328327f, 0.11603814f, 0.13015631f, 
  0.1475006f, 0.1612542f, 0.17098634f, 0.21512383f, 0.23329446f, 0.24581292f, 
  0.24889733f, 0.25190222f, 0.2520124f, 0.26982653f, 0.49342552f, 0.70000684f, 
  0.90435147f, 0.97991562f, 1.0136775f, 1.4074299f, 2.3717752f, 2.4644279f, 
  2.5119274f, 4.7064166f, 4.733078f, 14.712797f, 15.708934f, 25.026823f, 82.789993f, 
  0.28397429f, 0.42622095f, 0.54603994f, 0.55265188f, 0.5964905f, 0.59817827f, 
  0.63850641f, 0.65588659f, 0.82005095f, 0.82210016f, 0.97730267f, 1.1972058f, 
  1.2172768f, 1.3267035f, 1.3451121f, 1.4241807f, 1.4351392f, 1.4366884f, 1.4519598f, 
  1.4765853f, 1.499301f, 1.5346061f, 1.5471224f, 1.5491796f, 1.5756263f, 1.6180303f, 
  1.6313236f, 1.6375742f, 1.6484215f, 1.6531899f, 1.6608586f, 1.6791438f, 1.6804321f, 
  1.7266812f, 1.7307518f, 1.7322429f, 1.753495f, 1.763252f, 1.7710185f, 1.7757722f, 
  1.7840517f, 1.8188753f, 1.8439116f, 1.8568673f, 1.8778741f, 1.8806876f, 1.8814045f, 
  1.8825623f, 1.8861551f, 1.8861709f, 1.8874116f, 1.8879042f, 1.9222848f, 1.940284f, 
  1.9662488f, 1.9853103f, 1.9878309f, 2.0002754f, 2.0145361f, 2.0292861f, 2.0306883f, 
  2.0331173f, 2.0520253f, 2.0535395f, 2.0537448f, 2.0720932f, 2.0735283f, 2.080411f, 
  2.0931821f, 2.1484308f, 2.1848254f, 2.2610331f, 2.2652407f, 0.098033845f, 
  0.11054495f, 0.11979584f, 0.12384076f, 0.17563051f, 0.18252179f, 0.18359426f, 
  0.19367984f, 0.19409862f, 0.19837953f, 0.22136411f, 0.26636091f, 0.28572193f, 
  0.29215366f, 0.30568111f, 0.32753184f, 0.33178771f, 0.35367903f, 0.45656937f, 
  0.46486202f, 0.52597773f, 0.64334857f, 0.67097068f, 0.69292498f, 0.71890765f, 
  0.7373507f, 0.81542563f, 0.83867991f, 0.85742307f, 0.91998303f, 1.0525818f, 
  1.0902591f, 1.1649146f, 1.1696489f, 1.3879989f, 1.8396884f, 4.2330008f, 4.3226194f, 
  5.1852584f, 6.3634739f, 8.5908699f, 9.1468782f, 10.230376f, 10.489944f, 31.217422f, 
  45.216057f, 72.212906f, 194.13316f, 196.53946f, 217.29636f, 318.45105f, 321.54684f, 
  349.62085f, 389.54089f, 409.2569f, 419.81686f, 434.5672f, 452.97693f, 466.22729f, 
  479.09784f, 534.76013f, 1163.9044f, 9800.5176f, 72453.008f, 0.0056489115f, 
  0.014317604f, 0.014429994f, 0.02140291f, 0.02163814f, 0.032222584f, 0.046190057f, 
  0.069836736f, 0.077375144f, 0.082096063f, 0.091623992f, 0.095317662f, 0.10451513f, 
  0.12001619f, 0.14076698f, 0.15550995f, 0.26018789f, 0.34632093f, 0.44289938f, 
  0.63674486f, 0.64341331f, 0.70315027f, 1.2851583f, 1.3220876f, 1.6231005f, 
  1.8830404f, 4.1026073f, 7.356185f, 14.148716f, 60.897427f, 90.766212f, 123484.41f, 
};

static const int th_begin[] = {
  0, 10, 16, 83, 263, 360, 395, 468, 532, 
};

static const int th_len[] = {
  10, 6, 67, 180, 97, 35, 73, 64, 32, 
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
  if (offset == 564 || val < array[0]) {
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

  if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 172)) {
              sum += 0.58636367321f;
            } else {
              sum += 0.15000000596f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += -0.066666670144f;
            } else {
              sum += 0.34736841917f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            sum += -0.51111114025f;
          } else {
            sum += 0.47368425131f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 348)) {
          sum += -0.15000000596f;
        } else {
          sum += -0.5428571701f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        sum += 0.56883120537f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
              sum += -0.57931035757f;
            } else {
              sum += 0.12000000477f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
              sum += 0.52000004053f;
            } else {
              sum += 0.23076924682f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
              sum += -0.44262298942f;
            } else {
              sum += -0.57904791832f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += -0.087567575276f;
            } else {
              sum += -0.46834531426f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 352)) {
            sum += 0.59894865751f;
          } else {
            sum += 0.15000000596f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
              sum += 0.17647060752f;
            } else {
              sum += 0.57033711672f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 274)) {
              sum += 0.39428573847f;
            } else {
              sum += -.0f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += -0.41538465023f;
            } else {
              sum += 0.30000001192f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += 0.54495418072f;
            } else {
              sum += 0.31034481525f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 198)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
              sum += 0.53513514996f;
            } else {
              sum += 0.10000000894f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += 0.38181820512f;
            } else {
              sum += -0.23571428657f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            sum += -0.12000000477f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
              sum += -.0f;
            } else {
              sum += 0.5f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += -0.48571431637f;
            } else {
              sum += 0.44347828627f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
              sum += -0.25161290169f;
            } else {
              sum += -0.48091605306f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
            sum += -0.52000004053f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
              sum += 0.42857146263f;
            } else {
              sum += -0.26666668057f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += 0.55167788267f;
            } else {
              sum += 0.28301888704f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
              sum += 0.35593223572f;
            } else {
              sum += -0.15728156269f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 308)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              sum += 0.4490711987f;
            } else {
              sum += 0.22184351087f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
              sum += -0.2090484798f;
            } else {
              sum += 0.36450856924f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            sum += 0.37975546718f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
              sum += -0.0088691227138f;
            } else {
              sum += -0.44181120396f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
          sum += -0.14049044251f;
        } else {
          sum += -0.44891571999f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        sum += 0.4391682148f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 192)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
              sum += -0.37769457698f;
            } else {
              sum += -0.45134720206f;
            }
          } else {
            sum += 0.33603495359f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
              sum += -0.4191300571f;
            } else {
              sum += 0.23635293543f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
              sum += -0.35698050261f;
            } else {
              sum += 0.239101246f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
        sum += 0.46130394936f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
              sum += -0.21829561889f;
            } else {
              sum += 0.31442695856f;
            }
          } else {
            sum += 0.43368026614f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += 0.40258485079f;
            } else {
              sum += 0.16253548861f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 272)) {
              sum += 0.17958277464f;
            } else {
              sum += -0.31252092123f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 290)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
              sum += 0.041200861335f;
            } else {
              sum += 0.42012953758f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
              sum += 0.19057260454f;
            } else {
              sum += -0.32700878382f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += -0.39127606153f;
            } else {
              sum += 0.35034161806f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
              sum += -0.078230887651f;
            } else {
              sum += -0.33792361617f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
              sum += -0.36127728224f;
            } else {
              sum += 0.26965197921f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 118)) {
              sum += 0.42487326264f;
            } else {
              sum += -0.037403549999f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.098334856331f;
            } else {
              sum += 0.39623758197f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 116)) {
              sum += -0.35909730196f;
            } else {
              sum += 0.09314506501f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
            sum += 0.39619353414f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += 0.28409209847f;
            } else {
              sum += -0.081356421113f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 148)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += 0.13872686028f;
            } else {
              sum += -0.37431544065f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.46952092648f;
            } else {
              sum += -0.084910526872f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 238)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
              sum += 0.45669978857f;
            } else {
              sum += 0.047898050398f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
              sum += -0.3748344779f;
            } else {
              sum += 0.36923652887f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
            sum += -0.4100432694f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
              sum += -0.260858953f;
            } else {
              sum += 0.43718782067f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
            sum += 0.40304100513f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              sum += -0.03961096704f;
            } else {
              sum += 0.35077548027f;
            }
          }
        } else {
          sum += -0.16267579794f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 286)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += -0.18651074171f;
            } else {
              sum += 0.26544940472f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
              sum += -0.25914162397f;
            } else {
              sum += 0.28213912249f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += -0.0074058398604f;
            } else {
              sum += 0.36452946067f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 204)) {
              sum += 0.36166971922f;
            } else {
              sum += 0.027074543759f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
          sum += 0.36510622501f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
              sum += 0.26179274917f;
            } else {
              sum += -0.2767804563f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += 0.048805132508f;
            } else {
              sum += -0.38361415267f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += -0.37892481685f;
            } else {
              sum += 0.53110092878f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 172)) {
              sum += 0.26250457764f;
            } else {
              sum += -0.26742973924f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
              sum += -0.32522302866f;
            } else {
              sum += 0.29309371114f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
              sum += -0.18722014129f;
            } else {
              sum += -0.36539453268f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
            sum += -0.37417966127f;
          } else {
            sum += 0.34640040994f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 114)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += 0.39604946971f;
            } else {
              sum += 0.23626700044f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
              sum += 0.29303908348f;
            } else {
              sum += -0.40249171853f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
            sum += 0.35862624645f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 252)) {
              sum += 0.32531306148f;
            } else {
              sum += -0.25475516915f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 174)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
              sum += -0.37787941098f;
            } else {
              sum += 0.37325507402f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
              sum += -0.36375212669f;
            } else {
              sum += 0.0058861700818f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 298)) {
              sum += 0.36317053437f;
            } else {
              sum += 0.19173786044f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
              sum += 0.030047496781f;
            } else {
              sum += 0.40143573284f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            sum += 0.25818565488f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
              sum += -0.34022557735f;
            } else {
              sum += -0.07661447674f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
          sum += -0.075404539704f;
        } else {
          sum += -0.35004609823f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
          sum += 0.3275411129f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.27080997825f;
            } else {
              sum += -0.2256064564f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += 0.27748629451f;
            } else {
              sum += -0.34708830714f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
              sum += -0.25771057606f;
            } else {
              sum += 0.4661732018f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
              sum += 0.30519157648f;
            } else {
              sum += -0.22504608333f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
              sum += -0.067830316722f;
            } else {
              sum += 0.51941525936f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += -0.13451081514f;
            } else {
              sum += -0.30886170268f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 354)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
            sum += 0.36816179752f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += 0.33273088932f;
            } else {
              sum += 0.081266708672f;
            }
          }
        } else {
          sum += 0.089056424797f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
              sum += -0.37394475937f;
            } else {
              sum += 0.21389238536f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += 0.3642925024f;
            } else {
              sum += 0.2743678391f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 282)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 136)) {
              sum += 0.29668110609f;
            } else {
              sum += -0.042852658778f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
              sum += -0.31414121389f;
            } else {
              sum += 0.1222634688f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
          sum += -0.39416703582f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.18034699559f;
            } else {
              sum += 0.26131302118f;
            }
          } else {
            sum += -0.27912211418f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 122)) {
            sum += 0.34807667136f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += 0.23283685744f;
            } else {
              sum += -0.23864513636f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
            sum += 0.41914913058f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
              sum += 0.13083998859f;
            } else {
              sum += -0.20637305081f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
          sum += 0.34588336945f;
        } else {
          sum += -0.25294604897f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 138)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 266)) {
              sum += 0.0768205598f;
            } else {
              sum += -0.33647087216f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += 0.24520464242f;
            } else {
              sum += -0.15712840855f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
            sum += 0.026401197538f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
              sum += -0.33580100536f;
            } else {
              sum += -0.0025941496715f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        sum += 0.34384262562f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
              sum += -0.23564204574f;
            } else {
              sum += 0.60364663601f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += 0.054529204965f;
            } else {
              sum += -0.26908692718f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 240)) {
              sum += -0.22548121214f;
            } else {
              sum += 0.47366318107f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 116)) {
              sum += -0.32253757119f;
            } else {
              sum += 0.096172399819f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
          sum += 0.34686949849f;
        } else {
          sum += -0.099122047424f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
              sum += -0.33510121703f;
            } else {
              sum += 0.39160659909f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
              sum += 0.31239581108f;
            } else {
              sum += 0.14297635853f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 200)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
              sum += 0.083199396729f;
            } else {
              sum += 0.3730737865f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
              sum += 0.24019999802f;
            } else {
              sum += -0.19620013237f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 304)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 174)) {
              sum += 0.37328013778f;
            } else {
              sum += 0.12129545212f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
              sum += 0.23947446048f;
            } else {
              sum += -0.067816488445f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
              sum += -0.19380073249f;
            } else {
              sum += 0.30915030837f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 192)) {
              sum += -0.059705641121f;
            } else {
              sum += -0.23879078031f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
              sum += -0.19650602341f;
            } else {
              sum += 0.053056124598f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
              sum += 0.33234149218f;
            } else {
              sum += 0.11655076593f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += -0.016145722941f;
            } else {
              sum += 0.29511255026f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
              sum += -0.27327758074f;
            } else {
              sum += 0.079055592418f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
          sum += 0.3274038434f;
        } else {
          sum += -0.22843356431f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.18800674379f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += 0.057683311403f;
            } else {
              sum += -0.30932348967f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 302)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
              sum += -0.02780370228f;
            } else {
              sum += 0.23298594356f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
              sum += -0.31081703305f;
            } else {
              sum += 0.066991053522f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
            sum += -0.32448896766f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 260)) {
              sum += 0.65494644642f;
            } else {
              sum += 0.063135616481f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 188)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += 0.25479623675f;
            } else {
              sum += -0.23733220994f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
              sum += 0.47493216395f;
            } else {
              sum += -0.16832154989f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
          sum += 0.27446657419f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
            sum += 0.34027349949f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += -0.31888651848f;
            } else {
              sum += -0.24812369049f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
          sum += 0.33229520917f;
        } else {
          sum += -0.084058716893f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
            sum += -0.037614647299f;
          } else {
            sum += 0.32709369063f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.38713371754f;
            } else {
              sum += 0.17374238372f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
              sum += 0.2788387537f;
            } else {
              sum += 0.05306256935f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
          sum += -0.35850447416f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
              sum += 0.011309231631f;
            } else {
              sum += 0.28854238987f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.24946773052f;
            } else {
              sum += -0.37243878841f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 194)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
              sum += 0.47470036149f;
            } else {
              sum += 0.066417120397f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
              sum += 0.22470091283f;
            } else {
              sum += -0.29923501611f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 222)) {
              sum += -0.08777102828f;
            } else {
              sum += 0.28868553042f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 342)) {
              sum += -0.21117928624f;
            } else {
              sum += 0.2088547945f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
            sum += -0.2752558589f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += 0.22487518191f;
            } else {
              sum += 0.0091033186764f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
            sum += 0.33889612556f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
              sum += -0.19388569891f;
            } else {
              sum += 0.23272393644f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 214)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.32546269894f;
            } else {
              sum += 0.088864147663f;
            }
          } else {
            sum += -0.24857482314f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
              sum += -0.058097667992f;
            } else {
              sum += -0.33962854743f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
              sum += 0.22853843868f;
            } else {
              sum += -0.25375455618f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
          sum += 0.32206973433f;
        } else {
          sum += -0.071316711605f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
              sum += -0.26438111067f;
            } else {
              sum += 0.26281511784f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
              sum += 0.29752472043f;
            } else {
              sum += 0.15272456408f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 202)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
              sum += 0.061282787472f;
            } else {
              sum += 0.30087321997f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 258)) {
              sum += -0.47830733657f;
            } else {
              sum += 0.04329188168f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += -0.035120107234f;
            } else {
              sum += -0.1850361973f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 306)) {
              sum += 0.58010709286f;
            } else {
              sum += -0.016690833494f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += -0.21094891429f;
            } else {
              sum += 0.43888804317f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += -0.0084053836763f;
            } else {
              sum += -0.28955224156f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 144)) {
            sum += -0.2543489933f;
          } else {
            sum += 0.38036230206f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
            sum += 0.18077470362f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += -0.31636235118f;
            } else {
              sum += -0.26110571623f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 280)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
              sum += -0.32714378834f;
            } else {
              sum += 0.017637306824f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
              sum += 0.60001957417f;
            } else {
              sum += 0.0079633165151f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 296)) {
              sum += -0.40105807781f;
            } else {
              sum += 0.1869417429f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
              sum += -0.29577878118f;
            } else {
              sum += 0.16474767029f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
              sum += 0.34691902995f;
            } else {
              sum += 0.066749751568f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
              sum += 0.018742583692f;
            } else {
              sum += 0.29609134793f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
              sum += 0.29766273499f;
            } else {
              sum += 0.11012366414f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += 0.14343982935f;
            } else {
              sum += -0.15681533515f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
        sum += 0.31478151679f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
            sum += -0.33387598395f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.058943454176f;
            } else {
              sum += 0.26186573505f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
            sum += 0.30156117678f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
              sum += -0.079086564481f;
            } else {
              sum += 0.34245046973f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
          sum += 0.17746196687f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
            sum += -0.29276928306f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
              sum += -0.2592856288f;
            } else {
              sum += 0.2841052711f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 236)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
            sum += 0.025873713195f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 140)) {
              sum += 0.30766180158f;
            } else {
              sum += 0.027941584587f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 254)) {
            sum += -0.31415763497f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 270)) {
              sum += 0.31693488359f;
            } else {
              sum += -0.03903997317f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
        sum += 0.27784883976f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
              sum += -0.28715571761f;
            } else {
              sum += 0.4359267652f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 190)) {
              sum += -0.23262473941f;
            } else {
              sum += 0.13172599673f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.35477232933f;
            } else {
              sum += -0.24124075472f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.017324293032f;
            } else {
              sum += -0.28831747174f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
            sum += -0.28591555357f;
          } else {
            sum += 0.24786201119f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 120)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += 0.1226760447f;
            } else {
              sum += 0.31001701951f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
              sum += -0.33305156231f;
            } else {
              sum += 0.21702741086f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
              sum += -0.1610455215f;
            } else {
              sum += 0.25449287891f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += 0.1919734627f;
            } else {
              sum += -0.10603538156f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 212)) {
              sum += 0.120175533f;
            } else {
              sum += -0.15432235599f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
              sum += -0.25540825725f;
            } else {
              sum += 0.0455827564f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
        sum += 0.22143796086f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
            sum += 0.3357937336f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += -0.045916143805f;
            } else {
              sum += -0.28859707713f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
            sum += 0.11988610774f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              sum += 0.020295660943f;
            } else {
              sum += -0.29840317369f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.32118320465f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += 0.25170877576f;
            } else {
              sum += -0.25920322537f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.75617432594f;
            } else {
              sum += 0.374756217f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.24526791275f;
            } else {
              sum += -0.086590401828f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 336)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += 0.30992010236f;
            } else {
              sum += -0.18558888137f;
            }
          } else {
            sum += 0.43278715014f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 358)) {
              sum += -0.29694473743f;
            } else {
              sum += 0.22178128362f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 356)) {
              sum += 0.22690077126f;
            } else {
              sum += -0.20723602176f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
        sum += 0.050317429006f;
      } else {
        sum += 0.30875888467f;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
            sum += -0.2401175499f;
          } else {
            sum += 0.19595560431f;
          }
        } else {
          sum += 0.3083088398f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += 0.0087659014389f;
            } else {
              sum += 0.28645539284f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += -0.17516575754f;
            } else {
              sum += 0.16263112426f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 328)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 206)) {
              sum += 0.061595175415f;
            } else {
              sum += -0.12707053125f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 346)) {
              sum += 0.28314256668f;
            } else {
              sum += -0.32475620508f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
          sum += 0.20119842887f;
        } else {
          sum += -0.16600766778f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
          sum += 0.076809406281f;
        } else {
          sum += 0.30309316516f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 182)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
          sum += -0.079906433821f;
        } else {
          sum += 0.087109275162f;
        }
      } else {
        sum += -0.23582531512f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 142)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
              sum += -0.01753683202f;
            } else {
              sum += -0.24404156208f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
              sum += 0.19722366333f;
            } else {
              sum += 0.90730321407f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.16342690587f;
            } else {
              sum += -0.11053225398f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += 0.039314288646f;
            } else {
              sum += -0.28698551655f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += 0.19454829395f;
            } else {
              sum += -0.22887085378f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += -0.1707046628f;
            } else {
              sum += 0.55598533154f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 130)) {
              sum += 0.23255725205f;
            } else {
              sum += -0.19012144208f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 144)) {
              sum += -0.28505825996f;
            } else {
              sum += -0.099771015346f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
          sum += -0.21916045249f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
            sum += 0.29748719931f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 224)) {
              sum += -0.13904765248f;
            } else {
              sum += 0.23763373494f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 288)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += -0.098355919123f;
            } else {
              sum += 0.15006384254f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
              sum += 0.16796375811f;
            } else {
              sum += -0.15098105371f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
              sum += -0.17866179347f;
            } else {
              sum += 0.055569522083f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              sum += 0.10778661072f;
            } else {
              sum += -0.26244741678f;
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
            sum += -0.10322983563f;
          } else {
            sum += 0.35119277239f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 234)) {
              sum += 0.27181434631f;
            } else {
              sum += -0.20904667675f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
              sum += 0.14738112688f;
            } else {
              sum += -0.26415160298f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            sum += 0.24532115459f;
          } else {
            sum += -0.18415769935f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 128)) {
              sum += 0.18141297996f;
            } else {
              sum += -0.16649264097f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += -0.07089060545f;
            } else {
              sum += -0.28547620773f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.30462291837f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
              sum += -0.27405127883f;
            } else {
              sum += -0.025902077556f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 158)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.47210964561f;
            } else {
              sum += 0.22604669631f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += 0.14883580804f;
            } else {
              sum += -0.071002341807f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 334)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
              sum += 0.26938170195f;
            } else {
              sum += -0.1893440932f;
            }
          } else {
            sum += 0.4416076839f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += 0.065560556948f;
            } else {
              sum += -0.27502590418f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
              sum += 0.21193380654f;
            } else {
              sum += -0.17429946363f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
      sum += 0.29882591963f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
              sum += -0.061317298561f;
            } else {
              sum += 0.29097774625f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
              sum += 0.20314089954f;
            } else {
              sum += 0.023445801809f;
            }
          }
        } else {
          sum += 0.3813996613f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 186)) {
              sum += 0.27521449327f;
            } else {
              sum += 0.085708990693f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += -0.077072173357f;
            } else {
              sum += 0.22108739614f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
            sum += 0.25724253058f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 186)) {
              sum += 0.066606603563f;
            } else {
              sum += -0.22277991474f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
          sum += 0.18845717609f;
        } else {
          sum += -0.13313987851f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
          sum += 0.050036270171f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
            sum += 0.29781913757f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 250)) {
              sum += 0.16147612035f;
            } else {
              sum += 0.015160684474f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 182)) {
        sum += 0.00062244728906f;
      } else {
        sum += -0.21277238429f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 244)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += -0.075736492872f;
            } else {
              sum += 0.36009824276f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              sum += 0.12194217741f;
            } else {
              sum += -0.2395260185f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            sum += 0.1875898838f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += 0.10674131662f;
            } else {
              sum += -0.24212373793f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
            sum += -0.1049753353f;
          } else {
            sum += 0.1324134022f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
            sum += -0.032262492925f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += -0.060756068677f;
            } else {
              sum += -0.27559602261f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.11747658253f;
            } else {
              sum += -0.041953854263f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
              sum += 0.20015606284f;
            } else {
              sum += -0.26549237967f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
            sum += 0.5004580617f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.11584167182f;
            } else {
              sum += 0.28901919723f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              sum += -0.22532819211f;
            } else {
              sum += 0.35128825903f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
              sum += 0.13701175153f;
            } else {
              sum += -0.092603877187f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += -0.15617209673f;
            } else {
              sum += 0.40437820554f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
              sum += -0.066027373075f;
            } else {
              sum += -0.28438201547f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
    if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
          sum += 0.060606669635f;
        } else {
          sum += -0.29464516044f;
        }
      } else {
        sum += 0.31984892488f;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.30226311088f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 230)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 208)) {
              sum += 0.1862500608f;
            } else {
              sum += -0.59290552139f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              sum += 0.32530087233f;
            } else {
              sum += -0.10058582574f;
            }
          }
        } else {
          sum += 0.30095505714f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 188)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += 0.24257832766f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
              sum += -0.2674446106f;
            } else {
              sum += -0.04935169965f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += 0.13823513687f;
            } else {
              sum += -0.26992553473f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
          sum += -0.17699061334f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
            sum += 0.43610212207f;
          } else {
            sum += 0.11528731138f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 166)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
              sum += -0.14514644444f;
            } else {
              sum += 0.11132221669f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 294)) {
              sum += 0.3173147738f;
            } else {
              sum += 0.058299817145f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
              sum += -0.031777925789f;
            } else {
              sum += 0.33116364479f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += 0.08595187217f;
            } else {
              sum += -0.16067063808f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 196)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += -0.19631503522f;
            } else {
              sum += 0.21960292757f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += 0.39942350984f;
            } else {
              sum += 0.026033243164f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 332)) {
              sum += -0.042121127248f;
            } else {
              sum += 0.29042932391f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
              sum += -0.19929789007f;
            } else {
              sum += 0.16256420314f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
      sum += 0.28629389405f;
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
        sum += -0.16826164722f;
      } else {
        sum += 0.0073289885186f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
            sum += -0.064272962511f;
          } else {
            sum += 0.31333565712f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
              sum += 0.10966116935f;
            } else {
              sum += -0.13829730451f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
              sum += 0.0030040882993f;
            } else {
              sum += -0.25790831447f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
            sum += -0.083188697696f;
          } else {
            sum += 0.13616143167f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.28121876717f;
            } else {
              sum += -0.24634890258f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += -0.0049755135551f;
            } else {
              sum += -0.26575943828f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
          sum += 0.28481480479f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += -0.29635986686f;
            } else {
              sum += -0.1694188416f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              sum += -0.2598310411f;
            } else {
              sum += 0.145127967f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 180)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += 0.44168156385f;
            } else {
              sum += 0.052688788623f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
              sum += 0.17557328939f;
            } else {
              sum += -0.12451650947f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
              sum += -0.12562169135f;
            } else {
              sum += 0.25392979383f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
              sum += 0.082632035017f;
            } else {
              sum += -0.10716357082f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
        sum += 0.026767158881f;
      } else {
        sum += 0.27805677056f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
          sum += 0.07381593436f;
        } else {
          sum += -0.22414776683f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
          sum += 0.012270186096f;
        } else {
          sum += 0.25016114116f;
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
              sum += 0.14113563299f;
            } else {
              sum += -0.084313675761f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
              sum += -0.1785915345f;
            } else {
              sum += 0.24598051608f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 268)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
              sum += 0.41141268611f;
            } else {
              sum += 0.17799921334f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
              sum += -0.31495839357f;
            } else {
              sum += 0.32434692979f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += -0.21007621288f;
            } else {
              sum += 0.28017398715f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 162)) {
              sum += 0.22839106619f;
            } else {
              sum += -0.0066944113933f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 350)) {
              sum += 0.12766522169f;
            } else {
              sum += -0.096462033689f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
              sum += -0.25888434052f;
            } else {
              sum += 0.058814059943f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 232)) {
              sum += -0.26792496443f;
            } else {
              sum += -0.021338868886f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
              sum += 0.25797894597f;
            } else {
              sum += -0.021614782512f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
            sum += 0.16877682507f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += -0.27532699704f;
            } else {
              sum += 0.0762129426f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
              sum += -0.13931576908f;
            } else {
              sum += 0.41454187036f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += -0.2942956686f;
            } else {
              sum += -0.060787614435f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 132)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 142)) {
              sum += -0.30416727066f;
            } else {
              sum += -0.089808627963f;
            }
          } else {
            sum += -0.097126461565f;
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
        sum += 0.2883938849f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          sum += 0.22670121491f;
        } else {
          sum += -0.060387309641f;
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
        sum += 0.013509661891f;
      } else {
        sum += -0.13073946536f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
              sum += 0.052379511297f;
            } else {
              sum += -0.22979314625f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 170)) {
              sum += 0.5017940402f;
            } else {
              sum += -0.12588432431f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
            sum += 0.12846456468f;
          } else {
            sum += -0.24789944291f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 146)) {
            sum += -0.21195472777f;
          } else {
            sum += 0.32635390759f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
            sum += 0.17623415589f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += 0.035617120564f;
            } else {
              sum += -0.25125044584f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 284)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
              sum += -0.27724730968f;
            } else {
              sum += -0.01138834469f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.072829589248f;
            } else {
              sum += -0.15982539952f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 338)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
              sum += 0.084032349288f;
            } else {
              sum += -0.22577609122f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += 0.2432448566f;
            } else {
              sum += -0.068178936839f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += 0.076342277229f;
            } else {
              sum += 0.35708743334f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
              sum += -0.33265131712f;
            } else {
              sum += 0.12284683436f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
              sum += -0.27714559436f;
            } else {
              sum += 0.12435726076f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
              sum += 0.25284573436f;
            } else {
              sum += -0.16615512967f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 226)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          sum += 0.26412370801f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 210)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
              sum += -0.24422812462f;
            } else {
              sum += 0.058952044696f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
              sum += -0.060130953789f;
            } else {
              sum += -0.42440676689f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 316)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
              sum += 0.19524414837f;
            } else {
              sum += -0.39502897859f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
              sum += 0.43515312672f;
            } else {
              sum += 0.18732094765f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
            sum += 0.23875802755f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 326)) {
              sum += -0.38672593236f;
            } else {
              sum += 0.094250015914f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
        sum += 0.41231545806f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
          sum += 0.20166166127f;
        } else {
          sum += -0.094568550587f;
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 264)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 126)) {
              sum += 0.01787869446f;
            } else {
              sum += 0.26500359178f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 256)) {
              sum += 0.22603926063f;
            } else {
              sum += 0.53163415194f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 330)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 124)) {
              sum += -0.16263392568f;
            } else {
              sum += 0.084967568517f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 344)) {
              sum += 0.24562720954f;
            } else {
              sum += -0.2228846252f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
              sum += 0.20942421257f;
            } else {
              sum += -0.19735650718f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 262)) {
              sum += 0.58464074135f;
            } else {
              sum += 0.051126286387f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
              sum += 0.14951370656f;
            } else {
              sum += -0.14984150231f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
              sum += 0.17423549294f;
            } else {
              sum += -0.13319808245f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
              sum += 0.0028966402169f;
            } else {
              sum += -0.25387454033f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.13762052357f;
            } else {
              sum += -0.22911736369f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 170)) {
              sum += 0.048191335052f;
            } else {
              sum += 0.77217882872f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 118)) {
              sum += -0.1545150429f;
            } else {
              sum += 0.21474692225f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              sum += -0.096386581659f;
            } else {
              sum += -0.26119950414f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 312)) {
              sum += -0.20281884074f;
            } else {
              sum += 0.15664795041f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 176)) {
            sum += 0.46403473616f;
          } else {
            sum += -0.17581146955f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
        sum += 0.081420078874f;
      } else {
        sum += 0.27783367038f;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
        sum += 0.20352400839f;
      } else {
        sum += -0.092056691647f;
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
      sum += 0.2829131186f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
              sum += -0.092987172306f;
            } else {
              sum += 0.12930102646f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.2784050405f;
            } else {
              sum += -0.15344415605f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += -0.011916178279f;
            } else {
              sum += 0.39710411429f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += -0.21561856568f;
            } else {
              sum += -0.010937217623f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 178)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
              sum += 0.34479576349f;
            } else {
              sum += 0.11751836538f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += -0.10615184158f;
            } else {
              sum += 0.15763501823f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
              sum += -0.019391393289f;
            } else {
              sum += 0.21822190285f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += -0.1791908294f;
            } else {
              sum += -0.032086070627f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
      sum += 0.27773764729f;
    } else {
      sum += -0.01008127816f;
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
              sum += 0.096997916698f;
            } else {
              sum += -0.059616625309f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
              sum += 0.0050684716552f;
            } else {
              sum += 0.36637532711f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.041100382805f;
            } else {
              sum += -0.23130232096f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 126)) {
              sum += 0.15328703821f;
            } else {
              sum += -0.086770817637f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 216)) {
              sum += -0.093383289874f;
            } else {
              sum += 0.22671064734f;
            }
          } else {
            sum += 0.61648178101f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              sum += 0.26668018103f;
            } else {
              sum += -0.09503249079f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 168)) {
              sum += 0.046200890094f;
            } else {
              sum += -0.16586348414f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 120)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
              sum += 0.1059621349f;
            } else {
              sum += -0.16392454505f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
              sum += 0.20562656224f;
            } else {
              sum += -0.12520372868f;
            }
          }
        } else {
          sum += 0.35522860289f;
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
              sum += -0.038034945726f;
            } else {
              sum += 0.24869756401f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += -0.24894657731f;
            } else {
              sum += -0.013399553485f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
            sum += -0.035763252527f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
              sum += -0.095282964408f;
            } else {
              sum += -0.27300596237f;
            }
          }
        }
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
      sum += 0.27032256126f;
    } else {
      sum += -0.0085636842996f;
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
      sum += 0.26636230946f;
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
          sum += -0.29609364271f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += -0.12683956325f;
            } else {
              sum += 0.15423211455f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
              sum += -0.26269057393f;
            } else {
              sum += 0.24259419739f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 160)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
            sum += 0.39350470901f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 150)) {
              sum += -0.029767831787f;
            } else {
              sum += 0.24721337855f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 218)) {
              sum += 0.023567965254f;
            } else {
              sum += 0.27003020048f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.014169129543f;
            } else {
              sum += -0.17460016906f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
  // return sum;
}