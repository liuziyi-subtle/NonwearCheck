#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  -0.5920707f, -0.59022146f, -0.4741351f, -0.30517694f, -0.25545317f, -0.15823656f, 
  -0.15060097f, -0.13659811f, -0.12604396f, -0.099689767f, -0.092208117f, 
  -0.067855991f, -0.063115202f, -0.057530567f, -0.033761673f, -0.024916232f, 
  -0.024397168f, -0.01881095f, -0.0090021286f, 0.0012119275f, 0.017585374f, 
  0.019743707f, 0.0198365f, 0.01997862f, 0.028084934f, 0.0285316f, 0.05164104f, 
  0.051729411f, 0.052079402f, 0.055163965f, 0.055298395f, 0.069479324f, 0.072118752f, 
  0.074999072f, 0.13963532f, 0.15916479f, 0.18711673f, 0.1946657f, 0.20863527f, 
  0.21462122f, 0.22635964f, 0.25035584f, 0.27916652f, 0.29952517f, 0.31804368f, 
  0.35153916f, 0.35605496f, 0.36677963f, 0.36808378f, 0.37625575f, 0.39523178f, 
  0.39578205f, 0.40345469f, 0.40705895f, 0.43228957f, 0.47213352f, 0.5345906f, 
  0.55411929f, 0.56457299f, 0.61353058f, 0.61820972f, 0.6350199f, 0.64256144f, 
  0.66035736f, 0.66363919f, 0.67671061f, 0.67908394f, 0.71623147f, 0.72236913f, 
  0.76276815f, 0.79428852f, 0.94243956f, 1.5f, 3.0f, 3.5f, 5.5f, 7.5f, 8.5f, 9.5f, 10.5f, 
  11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, -0.03557837f, -0.00029116235f, 
  0.00034249458f, 0.0013539194f, 0.011521328f, 0.024784226f, 0.031057753f, 
  0.04427065f, 0.050989982f, 0.082287595f, 0.085477859f, 0.1138467f, 0.12403307f, 
  0.20829925f, 0.23125802f, 0.40083891f, 0.44276297f, 0.45181459f, 0.47760302f, 
  0.49918303f, 0.50674498f, 0.52816665f, 0.55296171f, 0.58439219f, 0.58903956f, 
  0.59799564f, 0.62352955f, 0.62632906f, 0.64047307f, 0.65340698f, 0.65347642f, 
  0.65647674f, 0.65917945f, 0.66188335f, 0.6783222f, 0.68073666f, 0.6831634f, 
  0.69070196f, 0.70559376f, 0.71127498f, 0.71525109f, 0.76065409f, 0.77783769f, 
  0.78630888f, 0.79971039f, 0.80205923f, 0.80832267f, 0.81257963f, 0.81281352f, 
  0.81380486f, 0.81626701f, 0.81748569f, 0.82721269f, 0.8297888f, 0.84057456f, 
  0.84322447f, 0.85068148f, 0.85171926f, 0.85189116f, 0.87065321f, 0.87208366f, 
  0.8739661f, 0.87496603f, 0.87730592f, 0.87979162f, 0.8822304f, 0.88499081f, 
  0.88978028f, 0.89219964f, 0.90000957f, 0.9031691f, 0.90964329f, 0.91839242f, 
  0.93368924f, 0.93391132f, 0.94355786f, 0.94364667f, 0.94863594f, 0.95151269f, 
  0.95949471f, 0.96050143f, 0.96139276f, 0.96648586f, 0.00017078838f, 0.00017207125f, 
  0.00017271016f, 0.00017724886f, 0.00017743747f, 0.00023493383f, 0.00023497347f, 
  0.0091952141f, 0.0091994926f, 0.0094969179f, 0.0096492842f, 0.0097311493f, 
  0.010248853f, 0.010374708f, 0.010455832f, 0.012144376f, 0.012749009f, 0.012776142f, 
  0.013082648f, 0.01559051f, 0.01569166f, 0.016091987f, 0.016213238f, 0.016725611f, 
  0.017466689f, 0.017864754f, 0.019477915f, 0.019523196f, 0.019560507f, 0.020546373f, 
  0.020675767f, 0.020977257f, 0.020998362f, 0.021579713f, 0.023572652f, 0.032399781f, 
  0.033317212f, 0.033446133f, 0.034551732f, 0.034732923f, 0.039849646f, 0.042142123f, 
  0.042154629f, 0.042197213f, 0.047838159f, 0.050835699f, 0.063237861f, 0.064800397f, 
  0.067369416f, 0.091395415f, 0.16185944f, 0.2206285f, 0.31380576f, 0.61178958f, 
  1.7097274f, 3.6093431f, 3.7686448f, 4.0103841f, 4.6695065f, 8.7753677f, 23.898022f, 
  30.569565f, 33.704216f, 59.993355f, 92.397491f, 38858.641f, 355587.84f, 371815.62f, 
  0.0030325344f, 0.0037502686f, 0.0039755227f, 0.0041357419f, 0.0041474062f, 
  0.0043730279f, 0.004698419f, 0.0049125706f, 0.0087940488f, 0.011605622f, 
  0.011748294f, 0.013062446f, 0.014113523f, 0.014317608f, 0.015247554f, 0.015897438f, 
  0.041517735f, 0.041843496f, 0.045129366f, 0.045603834f, 0.047468185f, 0.05303736f, 
  0.05582248f, 0.056599252f, 0.07863877f, 0.080556653f, 0.081967987f, 0.096764177f, 
  0.10693511f, 0.11274308f, 0.12001036f, 0.12055002f, 0.12478262f, 0.14037523f, 
  0.14432901f, 0.1451464f, 0.15639621f, 0.16137016f, 0.16994831f, 0.19075418f, 
  0.19842193f, 0.20253205f, 0.20257227f, 0.20836556f, 0.21293548f, 0.21948263f, 
  0.22083239f, 0.22229604f, 0.26754725f, 0.27938056f, 0.29532388f, 0.31177539f, 
  0.31286752f, 0.32214668f, 0.3377403f, 0.37099004f, 0.37147075f, 0.37152404f, 
  0.38247567f, 0.38695335f, 0.43340722f, 0.43933177f, 0.44689435f, 0.47242349f, 
  0.49055332f, 0.50796562f, 0.51609069f, 0.53907657f, 0.61303902f, 0.61505467f, 
  0.68186963f, 0.7394495f, 0.76700187f, 0.78554142f, 0.79768574f, 0.86372209f, 
  1.0255756f, 1.2707442f, 1.9383241f, 1.9433945f, 2.1024716f, 2.1223595f, 2.2560761f, 
  2.3782959f, 2.4777565f, 2.5329387f, 2.9311385f, 4.1476641f, 4.3608465f, 4.7538395f, 
  4.7810826f, 4.8283129f, 4.9249229f, 5.0249038f, 5.5194197f, 5.6522312f, 31.652496f, 
  50.229744f, 56.818279f, 82.668152f, 85.427994f, 105.18284f, 130.68945f, 0.44780773f, 
  0.78347003f, 0.86563981f, 0.99953276f, 1.0157146f, 1.018357f, 1.0496181f, 
  1.0768335f, 1.1170703f, 1.1240079f, 1.1372225f, 1.2812703f, 1.3053484f, 1.3515832f, 
  1.4407353f, 1.4537795f, 1.5643578f, 1.5745587f, 1.5939875f, 1.5967069f, 1.6057444f, 
  1.6059847f, 1.6418872f, 1.6686752f, 1.679445f, 1.6860161f, 1.7018288f, 1.7075551f, 
  1.7606047f, 1.7611082f, 1.7718825f, 1.7730869f, 1.7782512f, 1.7883644f, 1.7889158f, 
  1.7923114f, 1.8011335f, 1.8032792f, 1.8052369f, 1.8101617f, 1.8158873f, 1.8237517f, 
  1.8512628f, 1.8536968f, 1.8555691f, 1.8556812f, 1.855919f, 1.8619549f, 1.8757732f, 
  1.8793278f, 1.8799736f, 1.8848147f, 1.9047358f, 1.9053397f, 1.907004f, 1.9275842f, 
  1.9316301f, 1.9540207f, 1.9546635f, 1.954793f, 1.9584572f, 1.9619052f, 1.9645002f, 
  1.9650354f, 1.9692082f, 1.9724039f, 1.9740523f, 1.9760468f, 1.9771683f, 1.9788053f, 
  1.9800289f, 1.9849932f, 1.9878182f, 2.004642f, 2.0050082f, 2.0097427f, 2.0144601f, 
  2.0174325f, 2.0200515f, 2.0237644f, 2.0242698f, 2.0285053f, 2.0347877f, 2.0350823f, 
  2.038775f, 2.0672317f, 2.0676222f, 2.1087925f, 2.1156998f, 2.1178164f, 2.118221f, 
  2.1201396f, 2.1219096f, 2.1220474f, 2.1367683f, 2.1381698f, 2.141712f, 2.1421158f, 
  2.1484931f, 2.1499467f, 2.1504192f, 2.1556993f, 2.1574759f, 2.1764488f, 2.2209201f, 
  2.2265611f, 2.2269511f, 2.265712f, 2.2660596f, 2.2680986f, 2.269496f, 2.2695291f, 
  2.2751298f, 2.2808166f, 2.2831941f, 0.035777777f, 0.040944446f, 0.050000001f, 
  0.053285714f, 0.070311114f, 0.072733335f, 0.073688895f, 0.08019048f, 0.091314286f, 
  0.091600001f, 0.095600002f, 0.09725f, 0.36636364f, 0.37264889f, 0.37271655f, 
  0.39137256f, 0.44776347f, 0.46659648f, 0.47252381f, 0.477f, 0.4813152f, 0.4829697f, 
  0.49186087f, 0.49671221f, 0.50358772f, 0.51630771f, 0.51749527f, 0.52050722f, 
  0.55392313f, 0.6352222f, 0.67566007f, 0.71023911f, 0.78957582f, 0.82256037f, 
  0.83286953f, 0.9063285f, 0.91546851f, 0.93775237f, 1.0372947f, 1.2148333f, 
  1.2746364f, 1.3808765f, 1.433913f, 1.6581428f, 1.7086799f, 1.8269176f, 1.9036691f, 
  1.9115965f, 1.9307778f, 1.9869151f, 1.9886854f, 2.3350868f, 2.8543811f, 2.9036155f, 
  2.927238f, 3.2885239f, 4.4597645f, 5.2042532f, 6.619f, 7.9495316f, 8.011137f, 
  11.584757f, 11.8425f, 13.375867f, 14.467455f, 15.752167f, 24.492804f, 24.890869f, 
  87.187607f, 0.042933334f, 0.056944445f, 0.066142857f, 0.10623376f, 0.11294444f, 
  0.11621429f, 0.11807692f, 0.16317788f, 0.32733834f, 0.32853091f, 0.33603334f, 
  0.35816666f, 0.39168423f, 0.4116888f, 0.4417091f, 0.44311905f, 0.44352001f, 
  0.44624001f, 0.44640887f, 0.45891178f, 0.45949209f, 0.46857893f, 0.48358154f, 
  0.50705796f, 0.51804f, 0.53499997f, 0.53546429f, 0.53557563f, 0.53820002f, 
  0.54671013f, 0.5517f, 0.56873739f, 0.56921744f, 0.60386264f, 0.61120635f, 
  0.62452966f, 0.63024759f, 0.63421863f, 0.6349203f, 0.63498485f, 0.67141819f, 
  0.67652178f, 0.6770435f, 0.68917644f, 0.72809523f, 0.74469697f, 0.79583156f, 
  0.84032393f, 0.88004744f, 0.8811f, 0.95684004f, 0.97855794f, 0.97977537f, 
  0.98458093f, 1.0083214f, 1.0343399f, 1.0464032f, 1.04694f, 1.0599556f, 1.1257806f, 
  1.1418245f, 1.2444727f, 1.3306363f, 1.3380696f, 1.3717667f, 1.4092814f, 1.4093571f, 
  1.4368596f, 1.4443352f, 1.4918637f, 1.6954546f, 1.7344762f, 1.7369372f, 1.7392381f, 
  1.7740834f, 1.8568312f, 2.5740399f, 3.5827932f, 3.6667752f, 3.9387369f, 4.3713331f, 
  4.8474545f, 5.0681667f, 6.6941967f, 6.7348242f, 7.138998f, 8.7349529f, 8.7578335f, 
  9.0577526f, 11.312687f, 16.5336f, 17.545921f, 19.040405f, 20.47967f, 28.918568f, 
  32.526382f, 47.113503f, 51.958244f, 54.377411f, 99.399673f, 281.2876f, 861.30457f, 
  0.0092558507f, 0.010230549f, 0.010570761f, 0.010573789f, 0.011359407f, 
  0.011387056f, 0.011388635f, 0.012108671f, 0.012361884f, 0.013040867f, 0.013193686f, 
  0.014051808f, 0.015966173f, 0.017401258f, 0.023759654f, 0.025530953f, 0.057365201f, 
  0.18906736f, 0.19096097f, 0.19267611f, 0.19349191f, 0.20253828f, 0.21686561f, 
  0.22622362f, 0.25955275f, 0.28046247f, 0.36196858f, 0.36243618f, 0.44052738f, 
  0.4757157f, 0.54585385f, 0.59331787f, 0.63555121f, 0.63803399f, 0.64041984f, 
  0.64778572f, 0.66349959f, 0.66520011f, 0.69591892f, 0.71282816f, 0.7687813f, 
  0.77035892f, 0.87985015f, 0.93613577f, 0.94076443f, 0.97834134f, 0.97897947f, 
  0.98795664f, 1.1682298f, 1.4120955f, 1.8128006f, 1.9046037f, 1.9324945f, 2.0781012f, 
  2.1999695f, 2.2203617f, 2.2420397f, 2.3196955f, 2.7359972f, 4.800106f, 5.4386878f, 
  6.8765073f, 8.0935745f, 8.799305f, 8.942544f, 9.0537643f, 10.451971f, 10.68358f, 
  10.694213f, 11.008839f, 14.343018f, 14.726028f, 15.70392f, 16.022963f, 16.246418f, 
  16.795532f, 19.878075f, 23.267584f, 28.692488f, 31.658348f, 33.523857f, 35.319736f, 
  35.42609f, 43.91893f, 44.337471f, 44.350922f, 44.366619f, 47.080753f, 50.495445f, 
  52.062096f, 52.088356f, 65.194496f, 81.360596f, 88.944016f, 111.16003f, 122.82116f, 
  202.93213f, 275.51709f, 276.05444f, 397.02777f, 463.41425f, 684.95819f, 1249.4846f, 
  1515.6404f, 2033.0591f, 4485.9526f, 4568.4507f, 19366.633f, 73882.438f, 1845494.8f, 
  0.02734375f, 0.03515625f, 0.04296875f, 0.05859375f, 0.07421875f, 0.08984375f, 
  0.10546875f, 0.11328125f, 0.12109375f, 0.12890625f, 0.13671875f, 0.14453125f, 
  0.15234375f, 0.16015625f, 0.17578125f, 
};

static const int th_len[] = {
  72, 15, 83, 68, 103, 115, 69, 102, 110, 15, 
};
static const int th_begin[] = {
  0, 72, 87, 170, 238, 341, 456, 525, 627, 737, 
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
  if (offset == 752 || val < array[0]) {
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

  if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
          sum += 0.5731343627f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
              sum += 0.40000003576f;
            } else {
              sum += -0.36000001431f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
              sum += 0.44000002742f;
            } else {
              sum += 0.066666670144f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
          sum += 0.30000001192f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            sum += 0.15000000596f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 114)) {
              sum += -0.15000000596f;
            } else {
              sum += -0.55307269096f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
            sum += 0.58416885138f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += -0.20000001788f;
            } else {
              sum += 0.38181820512f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 152)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 102)) {
              sum += 0.5f;
            } else {
              sum += 0.066666670144f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.52173912525f;
            } else {
              sum += -0.18620689213f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += -0.51724141836f;
            } else {
              sum += -0.054545458406f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += 0.13846154511f;
            } else {
              sum += 0.57818180323f;
            }
          }
        } else {
          sum += 0.59094876051f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 196)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
              sum += 0.15000000596f;
            } else {
              sum += 0.5625f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 204)) {
              sum += -0.33333337307f;
            } else {
              sum += 0.13846154511f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += -0.0f;
            } else {
              sum += 0.45882356167f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += -0.32727274299f;
            } else {
              sum += 0.20000001788f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 194)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
              sum += -0.38517180085f;
            } else {
              sum += 0.16738197207f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
              sum += 0.10000000894f;
            } else {
              sum += -0.56529784203f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 192)) {
              sum += -0.36000001431f;
            } else {
              sum += -0.014634146355f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 196)) {
              sum += 0.52941179276f;
            } else {
              sum += -0.13846154511f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
          sum += 0.56625002623f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += 0.15000000596f;
            } else {
              sum += 0.53333336115f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 90)) {
              sum += 0.20000001788f;
            } else {
              sum += -0.30000001192f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 188)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += 0.24545454979f;
            } else {
              sum += -0.47118645906f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
              sum += 0.5f;
            } else {
              sum += -0.0f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
              sum += 0.54000002146f;
            } else {
              sum += 0.23076924682f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 178)) {
              sum += 0.16363637149f;
            } else {
              sum += -0.36000001431f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
          sum += 0.45689728856f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += -0.3580147028f;
            } else {
              sum += 0.00033325538971f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 134)) {
              sum += 0.10892787576f;
            } else {
              sum += 0.37466233969f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
          sum += 0.28724235296f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 216)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
              sum += 0.022542117164f;
            } else {
              sum += -0.42496663332f;
            }
          } else {
            sum += 0.1381469816f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
            sum += 0.45154696703f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
              sum += -0.066502608359f;
            } else {
              sum += 0.3751295507f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 152)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
              sum += 0.43017944694f;
            } else {
              sum += 0.11880668253f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              sum += 0.074432261288f;
            } else {
              sum += -0.36845514178f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += -0.40082266927f;
            } else {
              sum += 0.3523889184f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += 0.082915768027f;
            } else {
              sum += 0.45446178317f;
            }
          }
        } else {
          sum += 0.45748513937f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 200)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
            sum += 0.41933628917f;
          } else {
            sum += -0.011660040356f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
            sum += -0.29979339242f;
          } else {
            sum += 0.16379329562f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += 0.14819730818f;
            } else {
              sum += 0.50082564354f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += -0.28524005413f;
            } else {
              sum += 0.12308910489f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 196)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 172)) {
              sum += -0.44684568048f;
            } else {
              sum += -0.37789168954f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
              sum += 0.42974004149f;
            } else {
              sum += -0.25951433182f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
            sum += 0.44773468375f;
          } else {
            sum += 0.01095579192f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
            sum += 0.44501623511f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 92)) {
              sum += 0.081111460924f;
            } else {
              sum += -0.41266289353f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 186)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 118)) {
              sum += 0.33984777331f;
            } else {
              sum += -0.095933169127f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += -0.34165692329f;
            } else {
              sum += 0.13588914275f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += 0.46568438411f;
            } else {
              sum += 0.12144444138f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 188)) {
              sum += 0.27140784264f;
            } else {
              sum += -0.20375272632f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
            sum += 0.39477849007f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
              sum += -0.011074952781f;
            } else {
              sum += 0.24221014977f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += -0.25087696314f;
            } else {
              sum += 0.16261970997f;
            }
          } else {
            sum += 0.26784312725f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
            sum += -0.069773703814f;
          } else {
            sum += 0.34684669971f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 222)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += 0.18606606126f;
            } else {
              sum += -0.37226200104f;
            }
          } else {
            sum += 0.32528787851f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
          sum += 0.38872733712f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 138)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
              sum += 0.13281866908f;
            } else {
              sum += 0.44384974241f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
              sum += -0.3309392333f;
            } else {
              sum += 0.021359810606f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
              sum += -0.30477321148f;
            } else {
              sum += 0.31290623546f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
              sum += 0.12064087391f;
            } else {
              sum += 0.39356333017f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
              sum += 0.38449338078f;
            } else {
              sum += -0.013772011735f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.4002609551f;
            } else {
              sum += 0.34418970346f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
              sum += 0.3344001174f;
            } else {
              sum += -0.084636718035f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 154)) {
              sum += 0.44188299775f;
            } else {
              sum += 0.11525547504f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 150)) {
              sum += 0.10496006161f;
            } else {
              sum += 0.46859574318f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
              sum += 0.022444531322f;
            } else {
              sum += -0.26567557454f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 208)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              sum += 0.3383679986f;
            } else {
              sum += -0.088392578065f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += 0.22951987386f;
            } else {
              sum += -0.37559360266f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            sum += 0.4064669311f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 200)) {
              sum += -0.23574602604f;
            } else {
              sum += 0.30811229348f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.39637002349f;
            } else {
              sum += 0.28472396731f;
            }
          } else {
            sum += 0.0091803269461f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += 0.0012903750176f;
            } else {
              sum += 0.35674569011f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 178)) {
              sum += -0.14670330286f;
            } else {
              sum += 0.26541528106f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 184)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
              sum += -0.23665641248f;
            } else {
              sum += 0.37367907166f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.35297706723f;
            } else {
              sum += -0.0038836533204f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
              sum += 0.39660683274f;
            } else {
              sum += 0.15478798747f;
            }
          } else {
            sum += -0.15006190538f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
          sum += 0.36762228608f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
            sum += -0.12235181779f;
          } else {
            sum += 0.29486507177f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
            sum += 0.098362229764f;
          } else {
            sum += 0.36532124877f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += -0.12173689902f;
            } else {
              sum += 0.38143885136f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
              sum += 0.25747531652f;
            } else {
              sum += -0.28445389867f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              sum += -0.36384662986f;
            } else {
              sum += 0.12347704917f;
            }
          } else {
            sum += 0.30553907156f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            sum += 0.076694659889f;
          } else {
            sum += 0.36254787445f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
              sum += 0.35505095124f;
            } else {
              sum += 0.15871801972f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 134)) {
              sum += 0.29898780584f;
            } else {
              sum += -0.24729982018f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.34553000331f;
            } else {
              sum += -0.12431883067f;
            }
          } else {
            sum += 0.36544585228f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
              sum += 0.019909149036f;
            } else {
              sum += 0.34677302837f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
              sum += 0.32733678818f;
            } else {
              sum += -0.21541690826f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 186)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
              sum += 0.23465883732f;
            } else {
              sum += -0.23079253733f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 182)) {
              sum += 0.57355386019f;
            } else {
              sum += 0.02611803636f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
            sum += 0.31346577406f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
              sum += 0.12369274348f;
            } else {
              sum += -0.2771897614f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 202)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
              sum += 0.10856742412f;
            } else {
              sum += -0.34022003412f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
              sum += 0.34942048788f;
            } else {
              sum += -0.14490607381f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
              sum += 0.086170628667f;
            } else {
              sum += 0.39199063182f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += 0.38253116608f;
            } else {
              sum += -0.15429799259f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 154)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
              sum += 0.17689391971f;
            } else {
              sum += -0.31954717636f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 168)) {
              sum += 0.33637744188f;
            } else {
              sum += 0.049339581281f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 176)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
              sum += -0.18980932236f;
            } else {
              sum += 0.2685752809f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.32163757086f;
            } else {
              sum += -0.025231519714f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 120)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 124)) {
              sum += 0.33707845211f;
            } else {
              sum += -0.15547026694f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
              sum += -0.31312349439f;
            } else {
              sum += -0.014415036887f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
          sum += 0.34170427918f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
              sum += -0.20114253461f;
            } else {
              sum += 0.15218570828f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += 0.039352588356f;
            } else {
              sum += 0.33365103602f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 126)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
              sum += -0.20035223663f;
            } else {
              sum += 0.20369592309f;
            }
          } else {
            sum += 0.3755659759f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
              sum += -0.14413577318f;
            } else {
              sum += 0.38547587395f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
              sum += -0.31568986177f;
            } else {
              sum += 0.032329361886f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              sum += -0.30983752012f;
            } else {
              sum += 0.10156517476f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += 0.30468732119f;
            } else {
              sum += 0.080011799932f;
            }
          }
        } else {
          sum += 0.33851993084f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
              sum += 0.32388135791f;
            } else {
              sum += 0.012121504173f;
            }
          } else {
            sum += 0.34514659643f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 206)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += 0.19916136563f;
            } else {
              sum += 0.32929176092f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += -0.19047649205f;
            } else {
              sum += 0.26107734442f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 106)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 148)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
              sum += 0.33891528845f;
            } else {
              sum += -0.099609367549f;
            }
          } else {
            sum += 0.43014064431f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 180)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += 0.19191986322f;
            } else {
              sum += -0.22765648365f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
              sum += 0.36362785101f;
            } else {
              sum += -0.016256846488f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 128)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 152)) {
              sum += 0.37684240937f;
            } else {
              sum += 0.14609116316f;
            }
          } else {
            sum += -0.099588572979f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 176)) {
              sum += -0.10723397881f;
            } else {
              sum += 0.19398440421f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
              sum += 0.33225163817f;
            } else {
              sum += 0.06272765249f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 210)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
              sum += 0.22861099243f;
            } else {
              sum += -0.090777501464f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 170)) {
              sum += -0.32222425938f;
            } else {
              sum += -0.23460806906f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
            sum += 0.32191324234f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 200)) {
              sum += -0.31532567739f;
            } else {
              sum += 0.16566327214f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 176)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
              sum += -0.12954808772f;
            } else {
              sum += 0.18590137362f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
              sum += 0.18880879879f;
            } else {
              sum += -0.28128451109f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 114)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.3147367835f;
            } else {
              sum += -0.050072424114f;
            }
          } else {
            sum += -0.22642740607f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
          sum += 0.32473513484f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
            sum += -0.19242241979f;
          } else {
            sum += 0.27186983824f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 168)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
              sum += 0.32311570644f;
            } else {
              sum += 0.088830664754f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
              sum += -0.22511571646f;
            } else {
              sum += 0.17929133773f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 138)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
              sum += -0.31216433644f;
            } else {
              sum += -0.045143757015f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
              sum += 0.16244387627f;
            } else {
              sum += -0.14141395688f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
            sum += -0.12800107896f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
              sum += 0.31439509988f;
            } else {
              sum += -0.060013469309f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 112)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
              sum += 0.30084869266f;
            } else {
              sum += 0.071821637452f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += -0.38194307685f;
            } else {
              sum += 0.02106814459f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
              sum += -0.22927726805f;
            } else {
              sum += 0.24436672032f;
            }
          } else {
            sum += 0.32424107194f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
              sum += 0.30040580034f;
            } else {
              sum += -0.072142608464f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.32838514447f;
            } else {
              sum += 0.23649901152f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 122)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 160)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 150)) {
              sum += -0.15825299919f;
            } else {
              sum += 0.18407194316f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 166)) {
              sum += 0.68334746361f;
            } else {
              sum += 0.025604251772f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 192)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 132)) {
              sum += -0.00076399574755f;
            } else {
              sum += -0.23578295112f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
              sum += -0.14822137356f;
            } else {
              sum += 0.49733671546f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
              sum += 0.30185824633f;
            } else {
              sum += -0.032976005226f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
              sum += 0.12031102926f;
            } else {
              sum += 0.4216581285f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
              sum += 0.23948705196f;
            } else {
              sum += -0.13458067179f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 198)) {
              sum += -0.13179340959f;
            } else {
              sum += 0.27408087254f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 212)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += -0.034606207162f;
            } else {
              sum += 0.49224200845f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += -0.011109802872f;
            } else {
              sum += -0.29275396466f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
            sum += 0.32199069858f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 160)) {
              sum += 0.1635222584f;
            } else {
              sum += -0.27576360106f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
              sum += 0.25708055496f;
            } else {
              sum += -0.080235995352f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
              sum += 0.069192580879f;
            } else {
              sum += 0.35236489773f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 174)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
              sum += 0.13179002702f;
            } else {
              sum += -0.30270454288f;
            }
          } else {
            sum += 0.25135722756f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
          sum += 0.069600999355f;
        } else {
          sum += 0.31558418274f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
          sum += 0.24931637943f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
            sum += 0.22776082158f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 218)) {
              sum += -0.25457900763f;
            } else {
              sum += 0.17687550187f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
            sum += -0.10228987038f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
              sum += 0.075370907784f;
            } else {
              sum += 0.31136992574f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 164)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
              sum += 0.12878644466f;
            } else {
              sum += 0.35069674253f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
              sum += -0.27724432945f;
            } else {
              sum += 0.01182802394f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += -0.22000180185f;
            } else {
              sum += 0.18019118905f;
            }
          } else {
            sum += 0.31128102541f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
              sum += 0.29392018914f;
            } else {
              sum += -0.0094821620733f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.31919071078f;
            } else {
              sum += 0.22190074623f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 116)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 140)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
              sum += -0.01877325587f;
            } else {
              sum += 0.33620893955f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += 0.14649495482f;
            } else {
              sum += 0.4222342968f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
              sum += 0.033430598676f;
            } else {
              sum += -0.3116004169f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
              sum += -0.058295670897f;
            } else {
              sum += -0.21774928272f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
              sum += 0.26324680448f;
            } else {
              sum += -0.11080364138f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 98)) {
              sum += 0.37616181374f;
            } else {
              sum += 0.10946605355f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 152)) {
              sum += -0.23429630697f;
            } else {
              sum += 0.055936522782f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 132)) {
              sum += 0.28893432021f;
            } else {
              sum += -0.076170511544f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 170)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
              sum += -0.096993722022f;
            } else {
              sum += 0.3963624239f;
            }
          } else {
            sum += 0.45073911548f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
              sum += 0.062129084021f;
            } else {
              sum += -0.2905792594f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += 0.0083236657083f;
            } else {
              sum += -0.25614851713f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 96)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 178)) {
              sum += -0.0058978777379f;
            } else {
              sum += 0.60323363543f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 200)) {
              sum += -0.14861382544f;
            } else {
              sum += 0.20768490434f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 214)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
              sum += 0.07561378181f;
            } else {
              sum += -0.25917184353f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 108)) {
              sum += 0.073662638664f;
            } else {
              sum += 0.27052810788f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
              sum += -0.040233284235f;
            } else {
              sum += -0.32684084773f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += -0.17764277756f;
            } else {
              sum += 0.30157783628f;
            }
          }
        } else {
          sum += 0.28680673242f;
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 176)) {
              sum += 0.29353791475f;
            } else {
              sum += -0.038306452334f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              sum += -0.30175024271f;
            } else {
              sum += 0.11376463622f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
            sum += 0.31261122227f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
              sum += -0.041441041976f;
            } else {
              sum += 0.24005828798f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
              sum += 0.21365559101f;
            } else {
              sum += -0.17645831406f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 210)) {
              sum += 0.30256846547f;
            } else {
              sum += 0.0063140979037f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 120)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
              sum += 0.068475089967f;
            } else {
              sum += 0.30825853348f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
              sum += -0.30652713776f;
            } else {
              sum += -0.012071299367f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 212)) {
            sum += 0.29783758521f;
          } else {
            sum += 0.049211446196f;
          }
        } else {
          sum += 0.0478262119f;
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 124)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
              sum += -0.032767131925f;
            } else {
              sum += 0.27098187804f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
              sum += -0.071955949068f;
            } else {
              sum += 0.25018340349f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              sum += 0.24439041317f;
            } else {
              sum += -0.27229192853f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 152)) {
              sum += 0.3232447803f;
            } else {
              sum += 0.099516421556f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 172)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
              sum += 0.17678010464f;
            } else {
              sum += -0.15435022116f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
              sum += 0.42982962728f;
            } else {
              sum += -0.0040163365193f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 132)) {
              sum += 0.044687367976f;
            } else {
              sum += 0.31956148148f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 148)) {
              sum += 0.31908887625f;
            } else {
              sum += -0.094563931227f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 180)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 114)) {
              sum += -0.1166921556f;
            } else {
              sum += 0.2931881249f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
              sum += 0.14650824666f;
            } else {
              sum += -0.28150424361f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
              sum += 0.049216337502f;
            } else {
              sum += 0.81631106138f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 94)) {
              sum += -0.047630392015f;
            } else {
              sum += -0.21688766778f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 180)) {
              sum += 0.12522783875f;
            } else {
              sum += -0.11171207577f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.26485073566f;
            } else {
              sum += -0.036559667438f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 148)) {
              sum += -0.053468614817f;
            } else {
              sum += 0.35686016083f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 206)) {
              sum += -0.2372996062f;
            } else {
              sum += 0.20827953517f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
        sum += 0.22388127446f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
            sum += -0.079275839031f;
          } else {
            sum += -0.29579222202f;
          }
        } else {
          sum += 0.087075844407f;
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += -0.23621447384f;
            } else {
              sum += 0.085835687816f;
            }
          } else {
            sum += 0.27020427585f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
              sum += 0.25774413347f;
            } else {
              sum += -0.0023527115118f;
            }
          } else {
            sum += 0.30692261457f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 156)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
              sum += -0.073224432766f;
            } else {
              sum += 0.31810101867f;
            }
          } else {
            sum += 0.30501699448f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
              sum += 0.27132615447f;
            } else {
              sum += -0.070613592863f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
              sum += -0.4505392909f;
            } else {
              sum += 0.20277734101f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 158)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += 0.30303677917f;
            } else {
              sum += 0.050238799304f;
            }
          } else {
            sum += 0.36339634657f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.18622845411f;
            } else {
              sum += 0.24063542485f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.10401073843f;
            } else {
              sum += 0.18683756888f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 156)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 130)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
              sum += 0.13415057957f;
            } else {
              sum += -0.085140101612f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
              sum += -0.13036821783f;
            } else {
              sum += -0.26228296757f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 110)) {
              sum += 0.31366664171f;
            } else {
              sum += -0.10285231471f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 194)) {
              sum += -0.13150669634f;
            } else {
              sum += 0.051007624716f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 116)) {
              sum += -0.18491628766f;
            } else {
              sum += 0.43764355779f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
              sum += 0.067698135972f;
            } else {
              sum += -0.2765854001f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
              sum += 0.25534725189f;
            } else {
              sum += 0.85428315401f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
              sum += 0.25516477227f;
            } else {
              sum += -0.18152996898f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
              sum += -0.0064753624611f;
            } else {
              sum += -0.25017410517f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
              sum += 0.23582549393f;
            } else {
              sum += -0.10576757789f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
              sum += -0.26867589355f;
            } else {
              sum += -0.063336357474f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
              sum += 0.24771365523f;
            } else {
              sum += -0.050612229854f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
        sum += 0.23106689751f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
            sum += -0.26091104746f;
          } else {
            sum += -0.063441701233f;
          }
        } else {
          sum += 0.10125023872f;
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 176)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += 0.30150336027f;
            } else {
              sum += 0.017778277397f;
            }
          } else {
            sum += -0.042237356305f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
            sum += -0.36841496825f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += -0.07429805398f;
            } else {
              sum += 0.28576916456f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += -0.1777895689f;
            } else {
              sum += 0.19946749508f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
              sum += 0.23274086416f;
            } else {
              sum += 0.30693715811f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
              sum += 0.26895296574f;
            } else {
              sum += -0.20012165606f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 122)) {
              sum += 0.29849740863f;
            } else {
              sum += -0.020025145262f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 170)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
              sum += 0.08109754324f;
            } else {
              sum += 0.29490548372f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 138)) {
              sum += -0.2518812716f;
            } else {
              sum += 0.18942387402f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
              sum += 0.24179320037f;
            } else {
              sum += -0.0065292250365f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
              sum += 0.43632149696f;
            } else {
              sum += 0.13949072361f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 158)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 134)) {
              sum += -0.0023408129346f;
            } else {
              sum += -0.18391534686f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
              sum += 0.18714696169f;
            } else {
              sum += -0.057480033487f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 128)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 130)) {
              sum += 0.20009447634f;
            } else {
              sum += -0.11496206373f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += -0.24460576475f;
            } else {
              sum += 0.040003597736f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
              sum += 0.1297378093f;
            } else {
              sum += -0.18343099952f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
              sum += 0.52083265781f;
            } else {
              sum += 0.13691341877f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 170)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.31402778625f;
            } else {
              sum += -0.2599773407f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 166)) {
              sum += 0.34212818742f;
            } else {
              sum += -0.15060473979f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
              sum += -0.067809283733f;
            } else {
              sum += 0.30620768666f;
            }
          } else {
            sum += -0.12891286612f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 198)) {
              sum += -0.062426816672f;
            } else {
              sum += 0.25705528259f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
              sum += -0.28680846095f;
            } else {
              sum += -0.024700826034f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 184)) {
              sum += 0.29218658805f;
            } else {
              sum += 0.048293482512f;
            }
          } else {
            sum += 0.020667700097f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 144)) {
              sum += 0.026209773496f;
            } else {
              sum += 0.27779012918f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
              sum += -0.45013585687f;
            } else {
              sum += -0.0070504387841f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
            sum += -0.47339266539f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += 0.001213978976f;
            } else {
              sum += 0.27539569139f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 108)) {
              sum += -0.13899546862f;
            } else {
              sum += 0.25562486053f;
            }
          } else {
            sum += 0.30066004395f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 202)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
            sum += 0.36633619666f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
              sum += -0.10823119432f;
            } else {
              sum += 0.10404681414f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 214)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
              sum += -0.35906079412f;
            } else {
              sum += -0.09158988297f;
            }
          } else {
            sum += 0.30925491452f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 130)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += -0.17414331436f;
            } else {
              sum += 0.15378767252f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 208)) {
              sum += 0.28241708875f;
            } else {
              sum += 0.077451393008f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += 0.013666435145f;
            } else {
              sum += -0.30953025818f;
            }
          } else {
            sum += 0.23634693027f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 162)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 146)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
              sum += 0.083358705044f;
            } else {
              sum += -0.19470089674f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
              sum += -0.041754294187f;
            } else {
              sum += 0.55834168196f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
            sum += 0.2682005167f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 142)) {
              sum += -0.15309798717f;
            } else {
              sum += -0.26557707787f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 162)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 202)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += 0.17432484031f;
            } else {
              sum += -0.11596591026f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 204)) {
              sum += 0.60310554504f;
            } else {
              sum += 0.013571259566f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 150)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.56465089321f;
            } else {
              sum += 0.026275472715f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 170)) {
              sum += 0.13292869925f;
            } else {
              sum += -0.21720968187f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
              sum += 0.25264245272f;
            } else {
              sum += -0.0090946601704f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
              sum += -0.0016686184099f;
            } else {
              sum += -0.16517415643f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 100)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 176)) {
              sum += 0.46016430855f;
            } else {
              sum += -0.02060880512f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 198)) {
              sum += -0.28657740355f;
            } else {
              sum += 0.26114287972f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 174)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
              sum += 0.22449307144f;
            } else {
              sum += -0.18030254543f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += 0.29538917542f;
            } else {
              sum += 0.11381997913f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += 0.050504419953f;
            } else {
              sum += 0.2735183537f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += 0.060071770102f;
            } else {
              sum += -0.2561994195f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 176)) {
            sum += 0.28697890043f;
          } else {
            sum += 0.098909057677f;
          }
        } else {
          sum += -0.093958429992f;
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
              sum += -0.13373927772f;
            } else {
              sum += 0.20830608904f;
            }
          } else {
            sum += -0.64245903492f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += 0.27533715963f;
            } else {
              sum += -0.17654807866f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += -0.34059423208f;
            } else {
              sum += 0.17892281711f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += -0.27848529816f;
            } else {
              sum += 0.080934032798f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += 0.23848518729f;
            } else {
              sum += -0.084730386734f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
            sum += 0.2660472095f;
          } else {
            sum += -0.0068317973055f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
              sum += -0.38492834568f;
            } else {
              sum += 0.2814142406f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 160)) {
              sum += 0.29085499048f;
            } else {
              sum += 0.057578571141f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
              sum += -0.12982212007f;
            } else {
              sum += 0.12257594615f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
              sum += -0.072678141296f;
            } else {
              sum += 0.25066366792f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 172)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
              sum += 0.075916588306f;
            } else {
              sum += 0.33262711763f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
              sum += -0.25592601299f;
            } else {
              sum += 0.10473240167f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 132)) {
              sum += 0.24510838091f;
            } else {
              sum += 0.7864074707f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += 0.28665831685f;
            } else {
              sum += -0.027234707028f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 188)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += -0.097084373236f;
            } else {
              sum += 0.054874639958f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
              sum += -0.017106071115f;
            } else {
              sum += -0.15372249484f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 142)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 202)) {
              sum += 0.23197133839f;
            } else {
              sum += -0.20582892001f;
            }
          } else {
            sum += -0.21093806624f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 228)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 112)) {
              sum += -0.16349972785f;
            } else {
              sum += -0.28814700246f;
            }
          } else {
            sum += 0.38395762444f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.09960039705f;
            } else {
              sum += 0.37398174405f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 168)) {
              sum += 0.4369289279f;
            } else {
              sum += -0.15105430782f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 114)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
              sum += 0.10525277257f;
            } else {
              sum += 0.32712644339f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 144)) {
              sum += -0.11167164147f;
            } else {
              sum += 0.21262775362f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 116)) {
            sum += 0.087981760502f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += -0.29889398813f;
            } else {
              sum += -0.06912714988f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
        sum += 0.26828846335f;
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            sum += 0.21416324377f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              sum += 0.044104870409f;
            } else {
              sum += -0.20566119254f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
              sum += 0.10754076391f;
            } else {
              sum += -0.14498960972f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 142)) {
              sum += 0.32905596495f;
            } else {
              sum += 0.009439907968f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += 0.1415040791f;
            } else {
              sum += -0.0038207736798f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
              sum += -0.45213839412f;
            } else {
              sum += -0.061245687306f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += 0.2498934716f;
            } else {
              sum += -0.038712576032f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
              sum += 0.041543930769f;
            } else {
              sum += 0.28563040495f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 136)) {
            sum += 0.19256395102f;
          } else {
            sum += -0.21851193905f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              sum += -0.071190275252f;
            } else {
              sum += 0.19429306686f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
              sum += 0.11216522008f;
            } else {
              sum += 0.28591382504f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 194)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 122)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 174)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
              sum += -0.079917736351f;
            } else {
              sum += 0.027185751125f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
              sum += 0.31523144245f;
            } else {
              sum += 0.044504594058f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
              sum += 0.089081205428f;
            } else {
              sum += 0.30541661382f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 182)) {
              sum += -0.1889821291f;
            } else {
              sum += 0.20142604411f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 140)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 134)) {
              sum += 0.16076993942f;
            } else {
              sum += -0.098601691425f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
              sum += 0.38370370865f;
            } else {
              sum += 0.11251807213f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 146)) {
              sum += 0.075946770608f;
            } else {
              sum += -0.2777800858f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += 0.077870264649f;
            } else {
              sum += -0.27700316906f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 132)) {
          sum += -0.0054249628447f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
            sum += 0.061197225004f;
          } else {
            sum += 0.4270196259f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 168)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.21607112885f;
            } else {
              sum += -0.2534711659f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
              sum += 0.35679128766f;
            } else {
              sum += -0.10387571156f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 162)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += 0.10871840268f;
            } else {
              sum += 0.54144835472f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 138)) {
              sum += 0.005697327666f;
            } else {
              sum += -0.26657235622f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.21998952329f;
            } else {
              sum += -0.24046812952f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
              sum += 0.25007677078f;
            } else {
              sum += 0.06131163612f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 120)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
              sum += -0.31676718593f;
            } else {
              sum += 0.050422430038f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
              sum += 0.263117522f;
            } else {
              sum += -0.19326481223f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 164)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
              sum += 0.26401114464f;
            } else {
              sum += 0.51538336277f;
            }
          } else {
            sum += 0.083200775087f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 106)) {
              sum += -0.30834415555f;
            } else {
              sum += 0.025680953637f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += 0.065929114819f;
            } else {
              sum += 0.28421750665f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
            sum += 0.028793277219f;
          } else {
            sum += -0.38183125854f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 130)) {
              sum += 0.091802015901f;
            } else {
              sum += 0.25244641304f;
            }
          } else {
            sum += -0.17817036808f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
          sum += -0.12418600172f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += 0.047784995288f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 144)) {
              sum += 0.28450512886f;
            } else {
              sum += 0.060457956046f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 122)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 128)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.42522361875f;
            } else {
              sum += -0.08621942997f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 126)) {
              sum += 0.14828787744f;
            } else {
              sum += -0.087226077914f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
              sum += 0.30408877134f;
            } else {
              sum += -0.26698771119f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
              sum += -0.22980801761f;
            } else {
              sum += 0.09994032234f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 130)) {
          sum += 0.73825347424f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 134)) {
              sum += -0.11463517696f;
            } else {
              sum += 0.22773210704f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 218)) {
              sum += 0.010860475712f;
            } else {
              sum += -0.28197035193f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 140)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
            sum += 0.13673779368f;
          } else {
            sum += -0.086425639689f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
            sum += 0.32945501804f;
          } else {
            sum += 0.091170333326f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 144)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
              sum += -0.033683154732f;
            } else {
              sum += 0.54365295172f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 118)) {
              sum += 0.047525763512f;
            } else {
              sum += -0.20635305345f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 190)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
              sum += -0.27809539437f;
            } else {
              sum += -0.015724759549f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 184)) {
              sum += 0.07560300827f;
            } else {
              sum += -0.16562259197f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
    if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          sum += -0.015514199622f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 186)) {
            sum += 0.27737760544f;
          } else {
            sum += 0.0070015364327f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 104)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
            sum += 0.19809424877f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
              sum += -0.56963557005f;
            } else {
              sum += -0.057909872383f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += 0.24379065633f;
            } else {
              sum += -0.12842769921f;
            }
          } else {
            sum += 0.26531708241f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 146)) {
          sum += 0.076528385282f;
        } else {
          sum += -0.15745541453f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
            sum += -0.21192531288f;
          } else {
            sum += 0.21885623038f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
              sum += -0.10160284489f;
            } else {
              sum += 0.19972038269f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += 0.081996493042f;
            } else {
              sum += 0.29927673936f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 192)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
              sum += 0.03412823379f;
            } else {
              sum += 0.41345012188f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += 0.10597383976f;
            } else {
              sum += -0.14706765115f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 150)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
              sum += 0.47862848639f;
            } else {
              sum += 0.068454541266f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += -0.10238230973f;
            } else {
              sum += 0.16021490097f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
              sum += 0.091934449971f;
            } else {
              sum += 0.32253104448f;
            }
          } else {
            sum += 0.014965551905f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
              sum += 0.016639111564f;
            } else {
              sum += -0.11512475461f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
              sum += 0.24311579764f;
            } else {
              sum += -0.0055489982478f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
        sum += 0.38350325823f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 168)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 226)) {
              sum += -0.20891317725f;
            } else {
              sum += 0.3291246891f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 166)) {
              sum += 0.2699239254f;
            } else {
              sum += -0.10143660009f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
            sum += 0.31505304575f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += 0.09389360249f;
            } else {
              sum += -0.20434823632f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
    if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
          sum += -0.38588327169f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += -0.0084050698206f;
            } else {
              sum += -0.20390416682f;
            }
          } else {
            sum += 0.18940675259f;
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
              sum += 0.16480579972f;
            } else {
              sum += -0.14464826882f;
            }
          } else {
            sum += 0.28585469723f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
              sum += 0.23480831087f;
            } else {
              sum += -0.14998300374f;
            }
          } else {
            sum += 0.24088120461f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
            sum += -0.27193716168f;
          } else {
            sum += 0.054902750999f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
            sum += -0.12844017148f;
          } else {
            sum += 0.26726493239f;
          }
        }
      } else {
        sum += 0.2921782732f;
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 192)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
          sum += 0.045998334885f;
        } else {
          sum += 0.26377522945f;
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += -0.0011117564281f;
            } else {
              sum += 0.65117371082f;
            }
          } else {
            sum += -0.054844748229f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 136)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
              sum += -0.0073127178475f;
            } else {
              sum += 0.19717565179f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += 0.19386968017f;
            } else {
              sum += -0.18158623576f;
            }
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          sum += 0.31457784772f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 174)) {
              sum += -0.22248606384f;
            } else {
              sum += 0.073140390217f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += 0.22236014903f;
            } else {
              sum += -0.08427901566f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 136)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
              sum += 0.62084126472f;
            } else {
              sum += 0.0071667772718f;
            }
          } else {
            sum += -0.06179908663f;
          }
        } else {
          sum += -0.19127079844f;
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 136)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += -0.091829560697f;
            } else {
              sum += 0.26099416614f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 220)) {
              sum += -0.086449444294f;
            } else {
              sum += 0.35858106613f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += 0.23072360456f;
            } else {
              sum += -0.04904454574f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
              sum += 0.17446504533f;
            } else {
              sum += 0.59973710775f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 158)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 156)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 162)) {
              sum += 0.065083697438f;
            } else {
              sum += 0.34366881847f;
            }
          } else {
            sum += 0.75986212492f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
            sum += 0.050313018262f;
          } else {
            sum += -0.25295174122f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 136)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
              sum += 0.074149243534f;
            } else {
              sum += -0.17023395002f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
              sum += 0.44689300656f;
            } else {
              sum += 0.063313022256f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 170)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
              sum += 0.35711225867f;
            } else {
              sum += -0.24200558662f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 160)) {
              sum += -0.23446048796f;
            } else {
              sum += 0.76197236776f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
            sum += 0.81009155512f;
          } else {
            sum += 0.10784269869f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 128)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
              sum += -0.26874083281f;
            } else {
              sum += 0.019100321457f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
              sum += -0.21095655859f;
            } else {
              sum += 0.07038345933f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 120)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            sum += 0.25139400363f;
          } else {
            sum += 0.046393848956f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 90)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
              sum += 0.072698123753f;
            } else {
              sum += -0.35862141848f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += -0.047677725554f;
            } else {
              sum += 0.1942024529f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
          sum += -0.071790061891f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += -0.010652408004f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 148)) {
              sum += 0.25422164798f;
            } else {
              sum += 0.025685887784f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 154)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
          sum += 0.26299843192f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 82)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
              sum += 0.076227366924f;
            } else {
              sum += 0.25505486131f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += -0.24158088863f;
            } else {
              sum += 0.013212871738f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 80)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 126)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += -0.36574137211f;
            } else {
              sum += -0.095858827233f;
            }
          } else {
            sum += 0.079667761922f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 158)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.26189735532f;
            } else {
              sum += -0.097111217678f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
              sum += -0.19088996947f;
            } else {
              sum += 0.020947190002f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += -0.054851364344f;
            } else {
              sum += -0.40119314194f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
              sum += -0.038646616042f;
            } else {
              sum += 0.17680670321f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += 0.12025607377f;
            } else {
              sum += -0.12792733312f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += 0.064733617008f;
            } else {
              sum += 0.29035031796f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 120)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
            sum += 0.17221833766f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
              sum += -0.33675301075f;
            } else {
              sum += -0.10417487472f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
              sum += 0.3189009726f;
            } else {
              sum += 0.0073875184171f;
            }
          } else {
            sum += -0.070067636669f;
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 156)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
            sum += 0.23578073084f;
          } else {
            sum += -0.094491906464f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 188)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 166)) {
              sum += 0.26045787334f;
            } else {
              sum += 0.61770051718f;
            }
          } else {
            sum += 0.041290789843f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 140)) {
          sum += -0.1760135293f;
        } else {
          sum += 0.23264746368f;
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 192)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
              sum += -0.0090228300542f;
            } else {
              sum += 0.26810833812f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += 0.29652026296f;
            } else {
              sum += -0.13213245571f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
              sum += 0.57796007395f;
            } else {
              sum += 0.057123009115f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.35060831904f;
            } else {
              sum += -0.019776144996f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
              sum += 0.09066401422f;
            } else {
              sum += -0.10559799522f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
              sum += 0.30579024553f;
            } else {
              sum += 0.033241197467f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 132)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 126)) {
              sum += -0.010206256993f;
            } else {
              sum += 0.39875930548f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
              sum += 0.16006632149f;
            } else {
              sum += -0.13931821287f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 190)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 190)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              sum += 0.11565319449f;
            } else {
              sum += 0.61631345749f;
            }
          } else {
            sum += -0.016471024603f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
            sum += -0.20043678582f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 182)) {
              sum += 0.00076627696399f;
            } else {
              sum += 0.29553443193f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 136)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 216)) {
              sum += 0.090004488826f;
            } else {
              sum += -0.23077200353f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 190)) {
              sum += -0.3159109354f;
            } else {
              sum += 0.032685473561f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 198)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 194)) {
              sum += 0.21541957557f;
            } else {
              sum += -0.16913092136f;
            }
          } else {
            sum += 0.42918613553f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 192)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
            sum += 0.20257987082f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
              sum += -0.052142865956f;
            } else {
              sum += -0.19803513587f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += -0.018949737772f;
            } else {
              sum += 0.1385923326f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += 0.28809261322f;
            } else {
              sum += -0.070469461381f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 164)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
              sum += -0.002351801144f;
            } else {
              sum += 0.2884632647f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
              sum += 0.12168694288f;
            } else {
              sum += -0.11558318883f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 104)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 146)) {
              sum += -0.1696190238f;
            } else {
              sum += 0.45411857963f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 152)) {
              sum += 0.064122438431f;
            } else {
              sum += -0.17618969083f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += -0.23530553281f;
            } else {
              sum += -0.025828829035f;
            }
          } else {
            sum += 0.084485471249f;
          }
        } else {
          sum += 0.17945475876f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 128)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 166)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 138)) {
              sum += 0.13717840612f;
            } else {
              sum += -0.18166065216f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
              sum += 0.070609427989f;
            } else {
              sum += 0.54412215948f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += 0.017506767064f;
            } else {
              sum += 0.28627127409f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 224)) {
              sum += -0.16832897067f;
            } else {
              sum += 0.28268307447f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
      sum += 0.25216278434f;
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 140)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              sum += -0.06865683198f;
            } else {
              sum += 0.17654433846f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              sum += -0.34638291597f;
            } else {
              sum += -0.02064804174f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += 0.14488252997f;
            } else {
              sum += -0.21471150219f;
            }
          } else {
            sum += 0.22543132305f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
              sum += -0.12598291039f;
            } else {
              sum += 0.18525153399f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
              sum += 0.066916555166f;
            } else {
              sum += 0.28372573853f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 154)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
              sum += 0.22706143558f;
            } else {
              sum += 0.01777339913f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
              sum += -0.24478685856f;
            } else {
              sum += 0.037656039f;
            }
          }
        }
      }
    }
  }
  if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
              sum += -0.34222048521f;
            } else {
              sum += -0.071741111577f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
              sum += -0.036904405802f;
            } else {
              sum += 0.18734434247f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
              sum += 0.17260468006f;
            } else {
              sum += -0.055125825107f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
              sum += 0.28925901651f;
            } else {
              sum += 0.055494766682f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
              sum += 0.15810270607f;
            } else {
              sum += -0.11865147203f;
            }
          } else {
            sum += -0.2879422605f;
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 182)) {
              sum += 0.26090300083f;
            } else {
              sum += -0.011086600833f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += -0.13445648551f;
            } else {
              sum += 0.14551353455f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 164)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
              sum += -0.049392458051f;
            } else {
              sum += 0.24530614913f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
              sum += 0.20629251003f;
            } else {
              sum += 0.45771887898f;
            }
          }
        } else {
          sum += 0.02323709242f;
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 102)) {
            sum += -0.23404420912f;
          } else {
            sum += 0.014844245277f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            sum += 0.044219560921f;
          } else {
            sum += 0.2549790442f;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 164)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 142)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
              sum += -0.11929207295f;
            } else {
              sum += 0.23852397501f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
              sum += 0.086480744183f;
            } else {
              sum += -0.24232755601f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 86)) {
              sum += 0.48287725449f;
            } else {
              sum += 0.11639954895f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += -0.11978592724f;
            } else {
              sum += 0.267950207f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
          sum += 0.34651076794f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
              sum += 0.030284803361f;
            } else {
              sum += -0.16330042481f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
              sum += -0.3001408577f;
            } else {
              sum += -0.018824987113f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 172)) {
              sum += 0.16614985466f;
            } else {
              sum += -0.10509318858f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
              sum += -0.058531206101f;
            } else {
              sum += -0.25669670105f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 186)) {
            sum += 0.89240789413f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 118)) {
              sum += 0.38274270296f;
            } else {
              sum += -0.21331165731f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 196)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
              sum += -0.091826982796f;
            } else {
              sum += 0.45957887173f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
              sum += 0.11717116833f;
            } else {
              sum += -0.18973277509f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 118)) {
              sum += 0.41188451648f;
            } else {
              sum += -0.063308149576f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 204)) {
              sum += -0.11767788976f;
            } else {
              sum += 0.067256487906f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}