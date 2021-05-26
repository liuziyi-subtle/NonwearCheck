#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  -0.14174989f, -0.088678226f, -0.085427016f, -0.075014152f, -0.06778349f, 
  -0.060579188f, -0.059447579f, -0.040771943f, 0.0015516158f, 0.022452153f, 
  0.048475109f, 0.048735268f, 0.063272186f, 0.080906607f, 0.12282525f, 0.12493911f, 
  0.13222396f, 0.13289297f, 0.14658155f, 0.16841048f, 0.16983783f, 0.19647273f, 
  0.20626944f, 0.2105035f, 0.21317694f, 0.21436128f, 0.22466072f, 0.22543952f, 
  0.25054601f, 0.25101158f, 0.25158334f, 0.25674146f, 0.28910139f, 0.3006846f, 
  0.31411031f, 0.34569424f, 0.38594651f, 0.38993728f, 0.39606571f, 0.43795773f, 
  0.45282084f, 0.45940316f, 0.46676588f, 0.46909082f, 0.47655487f, 0.50111824f, 
  0.53201044f, 0.54298019f, 0.56788629f, 0.57542914f, 0.58058977f, 0.68846089f, 
  0.72636867f, 0.72763062f, 0.73097181f, 0.73291755f, 0.73635542f, 0.73775542f, 
  0.74556524f, 0.75506324f, 0.76049113f, 0.77077115f, 0.79649687f, 0.82714176f, 
  0.91053402f, 0.97695053f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 
  16.5f, 0.120736f, 0.32788315f, 0.33934054f, 0.34825197f, 0.37692171f, 0.38651231f, 
  0.40312293f, 0.45103574f, 0.46394193f, 0.47230276f, 0.48593992f, 0.49553263f, 
  0.54027486f, 0.54103446f, 0.55463219f, 0.55465263f, 0.56477731f, 0.57800889f, 
  0.58732283f, 0.60692072f, 0.62827599f, 0.64564407f, 0.70525801f, 0.75838721f, 
  0.76783973f, 0.78393501f, 0.79495585f, 0.79871321f, 0.80386794f, 0.8224721f, 
  0.82873094f, 0.84578961f, 0.8553468f, 0.85547698f, 0.86538136f, 0.8716042f, 
  0.88466823f, 0.88524795f, 0.89397728f, 0.894023f, 0.89681035f, 0.89992732f, 
  0.90072572f, 0.90181357f, 0.91142243f, 0.91201174f, 0.92000741f, 0.93209857f, 
  0.95372415f, 0.0022121863f, 0.0043632039f, 0.0059650643f, 0.0061010467f, 
  0.0061357515f, 0.0093567576f, 0.012281943f, 0.012344128f, 0.013187131f, 
  0.013225337f, 0.01572305f, 0.015847061f, 0.015962396f, 0.01979975f, 0.023965795f, 
  0.028355421f, 0.028715309f, 0.033233713f, 0.040442429f, 0.043879114f, 0.044308715f, 
  0.056515113f, 0.0567973f, 0.05842495f, 0.059305862f, 0.066483147f, 0.069862202f, 
  0.070161328f, 0.074569434f, 0.075829089f, 0.19106546f, 0.21026501f, 0.36059043f, 
  0.38853377f, 0.52562451f, 0.56243312f, 0.64890385f, 0.65075636f, 0.7613126f, 
  0.81730413f, 0.94463348f, 0.94469106f, 1.2123013f, 1.2251062f, 1.4921238f, 
  1.6753838f, 1.8109593f, 2.1626782f, 2.6778359f, 2.7546959f, 3.0591111f, 3.1644459f, 
  3.2075822f, 5.0511599f, 5.5450001f, 5.6007514f, 5.6014967f, 5.7865696f, 5.966526f, 
  13.538322f, 14.016577f, 16.253834f, 17.332359f, 22.949697f, 24.186998f, 35.719997f, 
  36.868404f, 49.970291f, 50.638882f, 4066.3904f, 4270.9746f, 0.026663398f, 
  0.037803415f, 0.070177622f, 0.07170774f, 0.07861761f, 0.083248243f, 0.083566502f, 
  0.084774628f, 0.085037827f, 0.09266638f, 0.097156733f, 0.10589713f, 0.10622865f, 
  0.11446118f, 0.11514995f, 0.12417233f, 0.13194838f, 0.13275494f, 0.13508973f, 
  0.14241125f, 0.14531624f, 0.16020797f, 0.16237861f, 0.16853078f, 0.16982259f, 
  0.18972424f, 0.19019789f, 0.19782013f, 0.20557258f, 0.23595855f, 0.24790001f, 
  0.25032747f, 0.25139445f, 0.25879654f, 0.26489812f, 0.26821679f, 0.2759791f, 
  0.27607635f, 0.28990108f, 0.33016494f, 0.33622974f, 0.34786338f, 0.35961929f, 
  0.37211657f, 0.38645017f, 0.39008859f, 0.43140694f, 0.45163649f, 0.46774703f, 
  0.4721505f, 0.48298305f, 0.48324284f, 0.48662332f, 0.51779509f, 0.52607429f, 
  0.53721493f, 0.57114083f, 0.60725516f, 0.72377515f, 0.72651613f, 0.74107373f, 
  0.75634444f, 0.76351738f, 0.76866746f, 0.81029308f, 0.83590043f, 0.86163473f, 
  0.87958515f, 0.93999386f, 1.1260433f, 1.1409662f, 1.2504381f, 1.2600017f, 
  1.2626792f, 1.2812999f, 1.2827947f, 1.3076196f, 1.3302059f, 1.3421389f, 1.3579278f, 
  1.4158546f, 1.4176385f, 1.4178395f, 1.5331522f, 1.7092524f, 1.8358328f, 1.8890153f, 
  2.1892371f, 2.7448139f, 3.1094279f, 3.1383734f, 3.5449467f, 3.5545275f, 11.474058f, 
  13.517672f, 41.656834f, 46.690681f, 60.771816f, 0.86371922f, 1.0556297f, 1.1061306f, 
  1.120404f, 1.1264415f, 1.1598978f, 1.265352f, 1.2902832f, 1.3045094f, 1.3349204f, 
  1.3400115f, 1.3844155f, 1.3941818f, 1.4034047f, 1.4130166f, 1.4171658f, 1.4172429f, 
  1.4245996f, 1.4528465f, 1.4820738f, 1.487507f, 1.4933589f, 1.5563178f, 1.6331801f, 
  1.6962557f, 1.696558f, 1.7522715f, 1.7673705f, 1.8098351f, 1.8301618f, 1.843394f, 
  1.8606743f, 1.8686454f, 1.8806171f, 1.9119051f, 1.9158142f, 1.9160714f, 1.9246095f, 
  1.9436634f, 1.9444773f, 1.9720231f, 1.9780003f, 1.9806342f, 1.9815381f, 1.9909601f, 
  1.9950123f, 2.001159f, 2.0018632f, 2.0153203f, 2.0288224f, 2.0307178f, 2.0315125f, 
  2.0335491f, 2.0338945f, 2.0346422f, 2.0384622f, 2.063776f, 2.0732372f, 2.0746202f, 
  2.075002f, 2.076272f, 2.0818553f, 2.0827932f, 2.085186f, 2.1050291f, 2.1064401f, 
  2.1105199f, 2.1108584f, 2.1147838f, 2.1148682f, 2.1201041f, 2.128952f, 2.1613159f, 
  2.1810358f, 2.1832037f, 2.1853397f, 2.2049577f, 2.2106659f, 2.2134788f, 2.2323909f, 
  2.2559466f, 2.2568147f, 0.26804763f, 0.33412871f, 0.38521969f, 0.41284615f, 
  0.45695859f, 0.47190118f, 0.52698576f, 0.55192733f, 0.61579561f, 0.64686036f, 
  0.69308221f, 0.8158406f, 1.1209502f, 1.1261277f, 1.1728089f, 1.1750846f, 1.2284808f, 
  1.4158609f, 1.4192151f, 1.9417984f, 2.0450544f, 2.1573381f, 3.0645523f, 3.4254961f, 
  3.4511499f, 3.7439284f, 4.7266817f, 4.8021421f, 4.8043633f, 5.0188627f, 5.756217f, 
  5.9860525f, 5.9878139f, 6.2235899f, 6.3620872f, 7.4727874f, 7.4961443f, 7.5542498f, 
  7.696804f, 8.0575504f, 8.3370514f, 8.5507298f, 9.1113968f, 9.4432278f, 13.276316f, 
  15.356647f, 88.69278f, 0.29693371f, 0.35722861f, 0.36552274f, 0.36758333f, 
  0.44539285f, 0.45163769f, 0.45443451f, 0.46608695f, 0.48886418f, 0.51194441f, 
  0.52035356f, 0.54717648f, 0.57467496f, 0.64337873f, 0.65649366f, 0.8036077f, 
  0.8036381f, 0.80852067f, 0.82409525f, 0.84231573f, 0.94608331f, 1.219553f, 
  1.2345092f, 1.4431f, 1.8801391f, 2.1922498f, 2.2222273f, 2.8018374f, 2.8788478f, 
  4.571619f, 4.6264262f, 4.8396988f, 5.6189165f, 6.6988192f, 11.672928f, 12.038966f, 
  14.149128f, 15.039479f, 15.900272f, 19.495007f, 20.655367f, 52.670895f, 0.65041435f, 
  0.78767365f, 0.9217723f, 0.92476028f, 0.93174958f, 1.0017135f, 1.1792388f, 
  1.2511361f, 1.9849448f, 3.2152081f, 3.4851813f, 3.5421267f, 3.646503f, 3.7057958f, 
  4.4487753f, 4.5908661f, 4.6881418f, 4.7031155f, 5.3024678f, 5.9630508f, 6.0096064f, 
  6.3809772f, 6.7091846f, 6.9358339f, 7.4148731f, 7.5474157f, 9.4440918f, 10.115011f, 
  14.723837f, 15.615349f, 15.671938f, 16.288776f, 16.71611f, 16.911165f, 19.519184f, 
  29.257f, 29.744186f, 30.582615f, 37.709293f, 43.918606f, 45.613266f, 45.652454f, 
  69.922928f, 72.688705f, 72.699127f, 78.080109f, 135.92784f, 138.3801f, 138.43356f, 
  141.26463f, 141.59607f, 157.59196f, 160.12123f, 168.29582f, 229.14133f, 254.09543f, 
  272.60883f, 356.95261f, 508.21692f, 616.28369f, 684.11633f, 845.7326f, 888.53613f, 
  0.01171875f, 0.02734375f, 0.04296875f, 0.05859375f, 0.06640625f, 0.09765625f, 
  0.10546875f, 0.11328125f, 0.12890625f, 0.14453125f, 0.16796875f, 0.19140625f, 
};

static const int th_len[] = {
  66, 10, 49, 71, 98, 82, 47, 42, 63, 12, 
};

static const int th_begin[] = {
  0, 66, 76, 125, 196, 294, 376, 423, 465, 528, 
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
  if (offset == 540 || val < array[0]) {
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

  for (int i = 0; i < 10; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }

  if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
          sum += 0.46666669846f;
        } else {
          sum += -0.12000000477f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
          sum += 0.12000000477f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
            sum += -0.15000000596f;
          } else {
            sum += -0.53684210777f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
          sum += 0.59714287519f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            sum += 0.5345454812f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += -0.32307696342f;
            } else {
              sum += 0.15000000596f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 112)) {
            sum += 0.27272728086f;
          } else {
            sum += -0.375f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            sum += -.0f;
          } else {
            sum += 0.53684210777f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
              sum += 0.38181820512f;
            } else {
              sum += 0.066666670144f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 194)) {
              sum += -0.47878786922f;
            } else {
              sum += 0.15000000596f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 174)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += 0.47796612978f;
            } else {
              sum += -0.054545458406f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += -0.26153847575f;
            } else {
              sum += 0.27692309022f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
              sum += 0.1894736886f;
            } else {
              sum += -0.51111114025f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
              sum += -0.58025765419f;
            } else {
              sum += -0.48107036948f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
              sum += -0.40540543199f;
            } else {
              sum += 0.085714295506f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
              sum += -0.49206349254f;
            } else {
              sum += 0.375f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 120)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            sum += 0.12000000477f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
              sum += 0.58293843269f;
            } else {
              sum += 0.39375001192f;
            }
          }
        } else {
          sum += 0.066666670144f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
            sum += 0.48433735967f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += 0.52000004053f;
            } else {
              sum += -0.18857143819f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
              sum += -0.10909091681f;
            } else {
              sum += 0.39428573847f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
              sum += -0.45985403657f;
            } else {
              sum += -0.066666670144f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
          sum += 0.44058540463f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
            sum += -0.088647171855f;
          } else {
            sum += 0.32814589143f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.14014182985f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += -0.059769637883f;
            } else {
              sum += -0.48411503434f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 120)) {
            sum += 0.41126194596f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += 0.15578445792f;
            } else {
              sum += -0.23856620491f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
        sum += 0.46253412962f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
            sum += 0.35382929444f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 126)) {
              sum += -0.034174036235f;
            } else {
              sum += -0.34582936764f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
              sum += 0.10931871831f;
            } else {
              sum += 0.47549661994f;
            }
          } else {
            sum += -0.018073216081f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
              sum += -0.2798062861f;
            } else {
              sum += 0.22870030999f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += 0.43471631408f;
            } else {
              sum += 0.16914057732f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 192)) {
              sum += -0.37673407793f;
            } else {
              sum += 0.071468606591f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.20343287289f;
            } else {
              sum += -0.23443906009f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
            sum += 0.24298213422f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
              sum += -0.45052328706f;
            } else {
              sum += -0.35656815767f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
              sum += -0.17472711205f;
            } else {
              sum += -0.41785821319f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 172)) {
              sum += 0.38934737444f;
            } else {
              sum += -0.20906554163f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
            sum += -0.0010713258525f;
          } else {
            sum += 0.45203241706f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
              sum += 0.063133314252f;
            } else {
              sum += 0.43062141538f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.24162493646f;
            } else {
              sum += 0.23643003404f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
              sum += 0.1236929372f;
            } else {
              sum += 0.4520740211f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += 0.37832885981f;
            } else {
              sum += -0.084486410022f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
              sum += -0.24740639329f;
            } else {
              sum += 0.40753793716f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += 0.012389661744f;
            } else {
              sum += -0.45430520177f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
          sum += 0.38245427608f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 128)) {
            sum += 0.28055244684f;
          } else {
            sum += -0.10487156361f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
            sum += 0.26864099503f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += 0.036700408906f;
            } else {
              sum += -0.41176584363f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 120)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += 0.052939757705f;
            } else {
              sum += 0.35888400674f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += 0.12780544162f;
            } else {
              sum += -0.21281807125f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
          sum += 0.40212827921f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += 0.37033507228f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 146)) {
              sum += 0.2381696254f;
            } else {
              sum += -0.41223022342f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 124)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 102)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
              sum += 0.12053584307f;
            } else {
              sum += 0.43546709418f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += 0.26700979471f;
            } else {
              sum += -0.04391245544f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 156)) {
              sum += -0.35021093488f;
            } else {
              sum += -0.10164618492f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += 0.30002251267f;
            } else {
              sum += -0.21662515402f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
              sum += 0.29147732258f;
            } else {
              sum += -0.1993561089f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.53587198257f;
            } else {
              sum += 0.097016133368f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
              sum += -0.097872540355f;
            } else {
              sum += 0.38330373168f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += 0.31349426508f;
            } else {
              sum += -0.30562141538f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += -0.012403843924f;
            } else {
              sum += -0.37894648314f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
              sum += -0.29975482821f;
            } else {
              sum += -0.38809242845f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 118)) {
              sum += 0.57594311237f;
            } else {
              sum += -0.29825079441f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += -0.35671964288f;
            } else {
              sum += -0.038469638675f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
          sum += -0.17556880414f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 106)) {
              sum += 0.40681675076f;
            } else {
              sum += 0.1161601916f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
              sum += -0.15565036237f;
            } else {
              sum += 0.37344303727f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
              sum += 0.37506374717f;
            } else {
              sum += 0.06566465646f;
            }
          } else {
            sum += 0.41379123926f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 132)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
              sum += 0.099364437163f;
            } else {
              sum += -0.20726130903f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += -0.34537142515f;
            } else {
              sum += 0.050316527486f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 150)) {
          sum += 0.34886604548f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
            sum += 0.24181954563f;
          } else {
            sum += -0.11885095388f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.094678856432f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += -0.031482189894f;
            } else {
              sum += -0.3642052412f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
            sum += 0.29762968421f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
              sum += -0.1409226656f;
            } else {
              sum += 0.20169119537f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          sum += 0.36730375886f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 126)) {
              sum += 0.20495784283f;
            } else {
              sum += -0.258746773f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 144)) {
              sum += 0.3644964695f;
            } else {
              sum += 0.0083397766575f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
          sum += 0.33695417643f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 140)) {
            sum += 0.23200033605f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
              sum += -0.27970099449f;
            } else {
              sum += -0.072449319065f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
          sum += 0.27431079745f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
              sum += -0.20380027592f;
            } else {
              sum += -0.35482737422f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
              sum += 0.58202129602f;
            } else {
              sum += -0.30219581723f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 108)) {
              sum += 0.42115014791f;
            } else {
              sum += -0.28749957681f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += -0.010119223967f;
            } else {
              sum += -0.30207356811f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
              sum += 0.38249877095f;
            } else {
              sum += -0.27368086576f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
              sum += -0.16384424269f;
            } else {
              sum += 0.37967839837f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
          sum += -0.082453891635f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
            sum += 0.38016992807f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
              sum += -0.3069010973f;
            } else {
              sum += 0.29540133476f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += 0.42325422168f;
            } else {
              sum += 0.2041195482f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += 0.30084380507f;
            } else {
              sum += -0.15978893638f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += -0.034640073776f;
            } else {
              sum += -0.34218725562f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
              sum += 0.32337933779f;
            } else {
              sum += -0.17821405828f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
        sum += 0.26190793514f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
          sum += -0.30258524418f;
        } else {
          sum += 0.18055477738f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
          sum += 0.34657239914f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
            sum += 0.29468470812f;
          } else {
            sum += -0.12669056654f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            sum += 0.26628834009f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += -0.45725688338f;
            } else {
              sum += 0.025040071458f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
            sum += 0.33324658871f;
          } else {
            sum += 0.014020401053f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += 0.41542956233f;
            } else {
              sum += 0.014567933977f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
              sum += 0.12149448693f;
            } else {
              sum += -0.32123222947f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += 0.46522814035f;
            } else {
              sum += -0.24988786876f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
              sum += -0.18345794082f;
            } else {
              sum += -0.32568415999f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 166)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
              sum += -0.059665083885f;
            } else {
              sum += -0.26275345683f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += 0.64743161201f;
            } else {
              sum += 0.0096530020237f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 104)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += -0.28480100632f;
            } else {
              sum += 0.0042309914716f;
            }
          } else {
            sum += -0.35864308476f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
            sum += 0.13067351282f;
          } else {
            sum += 0.35799521208f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
              sum += 0.12615022063f;
            } else {
              sum += -0.32561263442f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
              sum += 0.31408038735f;
            } else {
              sum += 0.03716475144f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
              sum += 0.12370746583f;
            } else {
              sum += -0.25522595644f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
              sum += 0.29527661204f;
            } else {
              sum += -0.035499505699f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += -0.17979605496f;
            } else {
              sum += 0.37842744589f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
              sum += -0.28044998646f;
            } else {
              sum += -0.097828693688f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
        sum += 0.23560474813f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 122)) {
            sum += -0.074671044946f;
          } else {
            sum += -0.29513901472f;
          }
        } else {
          sum += 0.15604175627f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
          sum += 0.33191663027f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
            sum += 0.27111017704f;
          } else {
            sum += -0.10652128607f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            sum += 0.24208267033f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += -0.39303529263f;
            } else {
              sum += 0.018872955814f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
            sum += 0.31546440721f;
          } else {
            sum += 0.0117943082f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
              sum += 0.36647903919f;
            } else {
              sum += -0.024363471195f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += -0.027854971588f;
            } else {
              sum += -0.27067893744f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 82)) {
              sum += -0.24852369726f;
            } else {
              sum += 0.14426846802f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
              sum += -0.11987110227f;
            } else {
              sum += -0.32171142101f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
              sum += 0.10571823269f;
            } else {
              sum += -0.27156853676f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 114)) {
              sum += 0.70789039135f;
            } else {
              sum += -0.13584516943f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 104)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += -0.25671517849f;
            } else {
              sum += 0.0012644883245f;
            }
          } else {
            sum += -0.33832749724f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 114)) {
              sum += 0.11957176775f;
            } else {
              sum += -0.21160031855f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += -0.0096437167376f;
            } else {
              sum += 0.39320600033f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
              sum += 0.25915580988f;
            } else {
              sum += -0.15830610693f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.28568565845f;
            } else {
              sum += -0.11682796478f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 100)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 182)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
              sum += 0.15864895284f;
            } else {
              sum += 0.37383657694f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += -0.36905309558f;
            } else {
              sum += 0.1949981302f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            sum += 0.25307866931f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
              sum += 0.093839906156f;
            } else {
              sum += -0.35238927603f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
        sum += 0.22763887048f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
            sum += -0.070211537182f;
          } else {
            sum += -0.27018249035f;
          }
        } else {
          sum += 0.13452075422f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 160)) {
          sum += 0.32097709179f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
            sum += 0.17413720489f;
          } else {
            sum += -0.032052852213f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
              sum += 0.089182987809f;
            } else {
              sum += -0.25963884592f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += -0.060896571726f;
            } else {
              sum += 0.23546436429f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
            sum += 0.30098953843f;
          } else {
            sum += 0.009921467863f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += -0.29193094373f;
            } else {
              sum += 0.14698143303f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
              sum += 0.58608561754f;
            } else {
              sum += 0.07487706095f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
              sum += -0.18857760727f;
            } else {
              sum += -0.30587723851f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
              sum += -0.15319177508f;
            } else {
              sum += 0.40483176708f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 96)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
              sum += -0.30981969833f;
            } else {
              sum += 0.58584755659f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
              sum += -0.028234260157f;
            } else {
              sum += -0.31513422728f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
            sum += 0.086361564696f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += -0.3109177947f;
            } else {
              sum += -0.24525991082f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
              sum += 0.34212702513f;
            } else {
              sum += -0.11217911541f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
              sum += -0.03766541183f;
            } else {
              sum += -0.25986903906f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 108)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
              sum += 0.34076631069f;
            } else {
              sum += 0.031742684543f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
              sum += -0.3331155777f;
            } else {
              sum += -0.0061117992736f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
              sum += 0.19939136505f;
            } else {
              sum += -0.18627893925f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += 0.0070044179447f;
            } else {
              sum += 0.32179531455f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
            sum += 0.30636504292f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
              sum += -0.0027753533795f;
            } else {
              sum += -0.36174729466f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
        sum += 0.1600381434f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
          sum += -0.2297745049f;
        } else {
          sum += 0.037427607924f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
        sum += 0.31520920992f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            sum += 0.24823918939f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += -0.24838656187f;
            } else {
              sum += 0.1039249897f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 148)) {
            sum += 0.30005276203f;
          } else {
            sum += 0.038822844625f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
              sum += 0.23076029122f;
            } else {
              sum += -0.26551678777f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
              sum += 0.30325198174f;
            } else {
              sum += -0.084626533091f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
              sum += 0.015860589221f;
            } else {
              sum += -0.26390215755f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += -0.1289459914f;
            } else {
              sum += 0.22030007839f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 86)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += -0.29106411338f;
            } else {
              sum += 0.43289133906f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 138)) {
              sum += -0.098739676178f;
            } else {
              sum += -0.31372132897f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 92)) {
              sum += -0.2654505372f;
            } else {
              sum += 0.32708349824f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += -0.30840605497f;
            } else {
              sum += -0.21556282043f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              sum += 0.32582783699f;
            } else {
              sum += -0.11694207042f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
              sum += 0.38448736072f;
            } else {
              sum += -0.052364423871f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
              sum += 0.034932274371f;
            } else {
              sum += 0.32254528999f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
              sum += -0.2431217581f;
            } else {
              sum += -0.091225974262f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 170)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += 0.30071011186f;
            } else {
              sum += 0.63258808851f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
              sum += -0.095527909696f;
            } else {
              sum += 0.32226276398f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
              sum += -0.045667950064f;
            } else {
              sum += -0.30520510674f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
              sum += 0.31563353539f;
            } else {
              sum += -0.080642983317f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
        sum += 0.28867974877f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
          sum += 0.22426770627f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += 0.0008256334113f;
            } else {
              sum += -0.30946159363f;
            }
          } else {
            sum += 0.1931258142f;
          }
        }
      }
    } else {
      sum += 0.30891937017f;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 112)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
              sum += -0.21020941436f;
            } else {
              sum += 0.21870595217f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              sum += -0.095842815936f;
            } else {
              sum += -0.26529347897f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
            sum += 0.78221541643f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
              sum += -0.19325070083f;
            } else {
              sum += 0.071421787143f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
          sum += 0.20508542657f;
        } else {
          sum += -0.3093854785f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += 0.3525775969f;
            } else {
              sum += -0.049838263541f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
              sum += -0.049699213356f;
            } else {
              sum += -0.23548349738f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 98)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
              sum += -0.14331266284f;
            } else {
              sum += 0.17549812794f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 110)) {
              sum += -0.071347974241f;
            } else {
              sum += -0.29292330146f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
              sum += 0.25107294321f;
            } else {
              sum += -0.10476300865f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 122)) {
              sum += 0.30542868376f;
            } else {
              sum += -0.094195537269f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
              sum += 0.16048948467f;
            } else {
              sum += -0.25496336818f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              sum += 0.0027411193587f;
            } else {
              sum += 0.24095854163f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
      sum += 0.30363321304f;
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
            sum += 0.027671372518f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
              sum += -0.049039047211f;
            } else {
              sum += -0.3554751277f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
            sum += -0.016867080703f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += 0.061054613441f;
            } else {
              sum += 0.22941499949f;
            }
          }
        }
      } else {
        sum += 0.27641823888f;
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += 0.39970698953f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
              sum += 0.048873912543f;
            } else {
              sum += 0.2554101944f;
            }
          } else {
            sum += -0.21077641845f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 114)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += -0.24360652268f;
            } else {
              sum += -0.10942783207f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
              sum += -0.018625715747f;
            } else {
              sum += -0.3078443408f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
              sum += 0.66382014751f;
            } else {
              sum += -0.038098074496f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += -0.24008768797f;
            } else {
              sum += 0.20156750083f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
              sum += 0.21150615811f;
            } else {
              sum += -0.22297854722f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += 0.186782673f;
            } else {
              sum += -0.078513801098f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += -0.014122803695f;
            } else {
              sum += 0.33645063639f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
              sum += -0.18249613047f;
            } else {
              sum += 0.097709439695f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
          sum += 0.14588607848f;
        } else {
          sum += -0.29090389609f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
    if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
        sum += 0.30411198735f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
          sum += 0.19125239551f;
        } else {
          sum += 0.0042814542539f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
        sum += 0.26139575243f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
          sum += 0.042912691832f;
        } else {
          sum += -0.23901955783f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
              sum += -0.24301047623f;
            } else {
              sum += 0.14664202929f;
            }
          } else {
            sum += 0.39607080817f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += 0.023380838335f;
            } else {
              sum += -0.23100231588f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
              sum += 0.25090518594f;
            } else {
              sum += -0.098614193499f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += 0.21422979236f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += 0.35494467616f;
            } else {
              sum += -0.2504234314f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
              sum += -0.28379136324f;
            } else {
              sum += -0.17290860415f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 176)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += 0.3188958168f;
            } else {
              sum += -0.23036231101f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 116)) {
              sum += 0.43574377894f;
            } else {
              sum += -0.015117964707f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += -0.058718089014f;
            } else {
              sum += 0.50448846817f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
              sum += -0.28537124395f;
            } else {
              sum += -0.03692593053f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 186)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 158)) {
              sum += -0.24022035301f;
            } else {
              sum += 0.12424580008f;
            }
          } else {
            sum += 0.23808695376f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += 0.2633356154f;
            } else {
              sum += -0.019376635551f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.053205050528f;
            } else {
              sum += -0.26970395446f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
      sum += 0.30102154613f;
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
        sum += 0.26522454619f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
          sum += -0.29365241528f;
        } else {
          sum += 0.094522915781f;
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += 0.23075181246f;
            } else {
              sum += 0.0089961672202f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
              sum += 0.17629265785f;
            } else {
              sum += -0.19553433359f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
              sum += -0.16144667566f;
            } else {
              sum += 0.1742246151f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
              sum += 0.068901903927f;
            } else {
              sum += -0.25204569101f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += 0.78633701801f;
            } else {
              sum += 0.071653530002f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
              sum += 0.023132428527f;
            } else {
              sum += 0.36268272996f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
              sum += -0.015495426953f;
            } else {
              sum += -0.26652598381f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
              sum += 0.52568632364f;
            } else {
              sum += -0.032253857702f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
        sum += 0.2558952868f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
          sum += 0.067685544491f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
              sum += -0.21901530027f;
            } else {
              sum += 0.13189525902f;
            }
          } else {
            sum += -0.2956238091f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              sum += 0.075711734593f;
            } else {
              sum += -0.13273772597f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
              sum += 0.38541594148f;
            } else {
              sum += -0.095772497356f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
            sum += 0.32102072239f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += -0.27476131916f;
            } else {
              sum += -0.073508642614f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += 0.16894891858f;
            } else {
              sum += -0.1216820702f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += 0.65490943193f;
            } else {
              sum += 0.20637269318f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
              sum += -0.30193442106f;
            } else {
              sum += -0.0099609680474f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
              sum += 0.34466466308f;
            } else {
              sum += -0.065631978214f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
        sum += -0.0065892222337f;
      } else {
        sum += -0.29018494487f;
      }
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
        sum += 0.29811242223f;
      } else {
        sum += -0.010540395975f;
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 168)) {
          sum += 0.32637512684f;
        } else {
          sum += 0.055361717939f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 130)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
              sum += 0.023738706484f;
            } else {
              sum += 0.31880366802f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
              sum += -0.24359987676f;
            } else {
              sum += 0.25254309177f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += -0.21058136225f;
            } else {
              sum += -0.047152023762f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += 0.19921310246f;
            } else {
              sum += -0.08094047755f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
      sum += 0.29608270526f;
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 136)) {
        sum += 0.24892967939f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
          sum += -0.27677026391f;
        } else {
          sum += 0.077835820615f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
              sum += 0.013866465539f;
            } else {
              sum += -0.17304396629f;
            }
          } else {
            sum += 0.56247323751f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += -0.0092599326745f;
            } else {
              sum += -0.27275705338f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
              sum += 0.30343872309f;
            } else {
              sum += -0.13785642385f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += 0.31631654501f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
              sum += -0.034261818975f;
            } else {
              sum += -0.25202837586f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
              sum += 0.35207727551f;
            } else {
              sum += -0.11817645282f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
              sum += 0.030949173495f;
            } else {
              sum += -0.10754032433f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
              sum += 0.076184786856f;
            } else {
              sum += 0.42405164242f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
              sum += 0.11041425914f;
            } else {
              sum += -0.28152143955f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
              sum += 0.1404042542f;
            } else {
              sum += -0.26521268487f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 94)) {
              sum += 0.39000293612f;
            } else {
              sum += 0.00054990558419f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
              sum += -0.24127620459f;
            } else {
              sum += 0.088887378573f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 188)) {
            sum += 0.61819005013f;
          } else {
            sum += 0.091997027397f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
    sum += 0.29294198751f;
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
              sum += 0.011711582541f;
            } else {
              sum += 0.35225445032f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
              sum += 0.19199074805f;
            } else {
              sum += -0.12359566242f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
              sum += -0.31858682632f;
            } else {
              sum += -0.14619092643f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 118)) {
              sum += 0.14202569425f;
            } else {
              sum += -0.17608557642f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
              sum += 0.0087854359299f;
            } else {
              sum += -0.15442807972f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
              sum += 0.14199230075f;
            } else {
              sum += -0.037044648081f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 154)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += 0.31852668524f;
            } else {
              sum += 0.11749178171f;
            }
          } else {
            sum += -0.17232584953f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
          sum += -0.17457589507f;
        } else {
          sum += 0.18613195419f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
          sum += -0.010734041221f;
        } else {
          sum += -0.28348827362f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
    sum += 0.28931537271f;
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 128)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 104)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
              sum += -0.048040501773f;
            } else {
              sum += 0.35621824861f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
              sum += 0.13225898147f;
            } else {
              sum += 0.44965049624f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += -0.035707056522f;
            } else {
              sum += 0.17420139909f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
              sum += -0.11099407077f;
            } else {
              sum += 0.025623101741f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += -0.1398383081f;
            } else {
              sum += 0.80112785101f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.25939536095f;
            } else {
              sum += -0.026498444378f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
              sum += 0.013132282533f;
            } else {
              sum += 0.44682317972f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 90)) {
              sum += 0.014197352342f;
            } else {
              sum += -0.20531220734f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
        sum += -0.033644556999f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 130)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
            sum += -0.16952183843f;
          } else {
            sum += -0.0025323000737f;
          }
        } else {
          sum += -0.28775566816f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
    sum += 0.28497421741f;
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 130)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 134)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              sum += 0.12797689438f;
            } else {
              sum += -0.064219176769f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += 0.42960596085f;
            } else {
              sum += 0.08034016192f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
              sum += -0.06911739707f;
            } else {
              sum += -0.28159457445f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
              sum += 0.20875844359f;
            } else {
              sum += -0.0076091340743f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.14835783839f;
            } else {
              sum += -0.20921243727f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
              sum += 0.51127576828f;
            } else {
              sum += -0.0023101619445f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
              sum += -0.096802614629f;
            } else {
              sum += 0.38023418188f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 162)) {
              sum += -0.23916092515f;
            } else {
              sum += 0.10001607984f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
        sum += -0.071823850274f;
      } else {
        sum += -0.28080880642f;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
        sum += -0.24476034939f;
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
            sum += 0.215222314f;
          } else {
            sum += 0.042731456459f;
          }
        } else {
          sum += -0.024612804875f;
        }
      }
    } else {
      sum += 0.28258797526f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 80)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
              sum += -0.074235625565f;
            } else {
              sum += 0.20939932764f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += 0.059353824705f;
            } else {
              sum += -0.19219599664f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += 0.05365947634f;
            } else {
              sum += 0.58103942871f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
              sum += -0.25639545918f;
            } else {
              sum += 0.12913417816f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
              sum += 0.20475694537f;
            } else {
              sum += -0.11277514696f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 142)) {
              sum += 0.23474681377f;
            } else {
              sum += 0.60783392191f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += 0.0049430746585f;
            } else {
              sum += -0.25655084848f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              sum += 0.26082193851f;
            } else {
              sum += -0.017296073958f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
        sum += 0.11557092518f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 90)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
              sum += -0.076740309596f;
            } else {
              sum += 0.41116610169f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
              sum += -0.031974762678f;
            } else {
              sum += -0.23959971964f;
            }
          }
        } else {
          sum += -0.2897952795f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 106)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
            sum += 0.27667954564f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += -0.14560075104f;
            } else {
              sum += 0.19168624282f;
            }
          }
        } else {
          sum += -0.13095843792f;
        }
      } else {
        sum += 0.29458022118f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
          sum += 0.30447900295f;
        } else {
          sum += -0.065586313605f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 152)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += -0.081696853042f;
            } else {
              sum += -0.29410466552f;
            }
          } else {
            sum += -0.070116437972f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
            sum += 0.28934678435f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
              sum += -0.2447912246f;
            } else {
              sum += 0.22815841436f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 102)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
              sum += 0.10541111976f;
            } else {
              sum += 0.63550955057f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.2490580827f;
            } else {
              sum += 0.078463375568f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += -0.078013688326f;
            } else {
              sum += 0.19889070094f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += -0.23813821375f;
            } else {
              sum += -0.065434582531f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 190)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += 0.16194416583f;
            } else {
              sum += -0.13856334984f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += 0.51498353481f;
            } else {
              sum += -0.023029318079f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += -0.25310629606f;
            } else {
              sum += 0.093508183956f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
              sum += 0.35252213478f;
            } else {
              sum += -0.039238583297f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
        sum += 0.25857424736f;
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
          sum += 0.088602080941f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += -0.10747198015f;
            } else {
              sum += -0.29061064124f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
              sum += 0.21265433729f;
            } else {
              sum += -0.19299955666f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.26647916436f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
              sum += -0.11021758616f;
            } else {
              sum += 0.32990819216f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += 0.24568548799f;
            } else {
              sum += -0.17356690764f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
              sum += 0.11046616733f;
            } else {
              sum += 0.50671231747f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += -0.089187085629f;
            } else {
              sum += 0.22726753354f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          sum += -0.091628059745f;
        } else {
          sum += 0.20489756763f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
          sum += 0.52349001169f;
        } else {
          sum += 0.11346493661f;
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
          sum += -0.15224349499f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += 0.08681089431f;
            } else {
              sum += 0.59785723686f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.27552393079f;
            } else {
              sum += -0.15993258357f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
              sum += -0.030568325892f;
            } else {
              sum += 0.23894304037f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
              sum += -0.17419070005f;
            } else {
              sum += -0.013866762631f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
              sum += -0.23559659719f;
            } else {
              sum += 0.068177223206f;
            }
          } else {
            sum += 0.086535707116f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
          sum += 0.36059626937f;
        } else {
          sum += 0.021878894418f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += 0.3018873632f;
            } else {
              sum += -0.12123091519f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
              sum += -0.31065511703f;
            } else {
              sum += -0.040255930275f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
              sum += 0.022760137916f;
            } else {
              sum += 0.37880295515f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
              sum += -0.24670137465f;
            } else {
              sum += 0.048373673111f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}