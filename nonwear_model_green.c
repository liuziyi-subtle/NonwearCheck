#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  -0.5920707f, -0.58679748f, -0.26022586f, -0.22994824f, -0.21554445f, -0.21175382f, 
  -0.20690289f, -0.20341147f, -0.053015608f, -0.027869107f, -0.02520638f, 
  -0.01881095f, -0.0097244773f, -0.0088902246f, -0.00099009986f, 0.017585374f, 
  0.01997862f, 0.024575537f, 0.029894374f, 0.0330109f, 0.038741246f, 0.040260494f, 
  0.050558403f, 0.052079402f, 0.055298395f, 0.056268934f, 0.074999072f, 0.091206267f, 
  0.10173634f, 0.13814887f, 0.13902171f, 0.16965294f, 0.17420912f, 0.18934995f, 
  0.19246349f, 0.19254065f, 0.19285555f, 0.1946657f, 0.22635964f, 0.24342346f, 
  0.24420877f, 0.25035584f, 0.27601361f, 0.3030991f, 0.30322957f, 0.3463819f, 
  0.35787469f, 0.36702201f, 0.36702496f, 0.39650959f, 0.40754807f, 0.42107639f, 
  0.42122692f, 0.43546176f, 0.50564504f, 0.53979886f, 0.55411929f, 0.61016214f, 
  0.61766994f, 0.61820972f, 0.62391794f, 0.64807868f, 0.66035736f, 0.66184658f, 
  0.66373414f, 0.6664809f, 0.67671061f, 0.67908394f, 0.72236913f, 0.89377624f, 1.5f, 
  3.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 17.5f, 
  18.5f, 19.5f, -0.049318194f, 0.00034249458f, 0.024784226f, 0.030829718f, 
  0.031057753f, 0.04427065f, 0.10345902f, 0.10371101f, 0.1138467f, 0.11770795f, 
  0.12403307f, 0.12579428f, 0.1559439f, 0.17320818f, 0.18151626f, 0.20462392f, 
  0.21268831f, 0.44036108f, 0.44276297f, 0.44487712f, 0.45181459f, 0.5021466f, 
  0.50674498f, 0.50808823f, 0.51089799f, 0.55296171f, 0.64418101f, 0.652753f, 
  0.65647066f, 0.6652773f, 0.6783222f, 0.6831634f, 0.69070196f, 0.72880363f, 
  0.74318707f, 0.7460829f, 0.75874859f, 0.76430756f, 0.78549683f, 0.79258931f, 
  0.79366124f, 0.79641593f, 0.79678512f, 0.80201596f, 0.80598778f, 0.8061052f, 
  0.80917132f, 0.81000388f, 0.81257963f, 0.81282175f, 0.81380486f, 0.81849456f, 
  0.81980515f, 0.82023072f, 0.83439851f, 0.83625549f, 0.84075773f, 0.84237152f, 
  0.84276342f, 0.85684907f, 0.87221158f, 0.87544245f, 0.88308263f, 0.88350141f, 
  0.88889468f, 0.90000957f, 0.91722119f, 0.92697823f, 0.92774773f, 0.93738961f, 
  0.94111347f, 0.94364667f, 0.95081943f, 0.95327514f, 0.95470452f, 0.95607364f, 
  0.95635784f, 0.95895755f, 0.96649206f, 0.00017075929f, 0.0001709442f, 
  0.00017207125f, 0.00017693621f, 0.00017724886f, 0.00017743747f, 0.00020936872f, 
  0.00020974979f, 0.00024656072f, 0.00031511829f, 0.0004116997f, 0.0065895985f, 
  0.0091952141f, 0.0091994926f, 0.0094969179f, 0.0097311493f, 0.010248853f, 
  0.01039592f, 0.010473952f, 0.011983247f, 0.012144376f, 0.01255206f, 0.012776142f, 
  0.01343795f, 0.01559051f, 0.015630363f, 0.016213238f, 0.016463935f, 0.017466689f, 
  0.017952856f, 0.019443635f, 0.019477915f, 0.019523196f, 0.01982997f, 0.020356793f, 
  0.023515983f, 0.0235711f, 0.026198823f, 0.063086256f, 0.063572273f, 0.063779727f, 
  0.064292535f, 0.070097163f, 0.080097198f, 0.16105053f, 0.19296661f, 0.58684438f, 
  0.61178958f, 1.8729253f, 2.2214127f, 2.5898752f, 3.5917935f, 3.7548151f, 4.0103841f, 
  4.4391003f, 5.1355715f, 5.2205191f, 9.8179092f, 10.928117f, 37.728676f, 5213.8594f, 
  58868.488f, 166460.47f, 371815.62f, 539018.25f, 0.0022931392f, 0.0030313595f, 
  0.0037619644f, 0.0039755227f, 0.0039766766f, 0.0040580155f, 0.0041318443f, 
  0.0041357419f, 0.0041474062f, 0.0049125706f, 0.0053737536f, 0.0081761023f, 
  0.0087940488f, 0.011130247f, 0.011440936f, 0.011605622f, 0.011748294f, 
  0.013062446f, 0.014113523f, 0.014317608f, 0.015247554f, 0.015897438f, 0.040336382f, 
  0.041843496f, 0.044193804f, 0.045129366f, 0.045603834f, 0.047411844f, 0.047468185f, 
  0.048014525f, 0.050355956f, 0.052450139f, 0.056599252f, 0.064699709f, 0.079679117f, 
  0.080556653f, 0.080639109f, 0.10559021f, 0.11274308f, 0.12512481f, 0.127056f, 
  0.14148349f, 0.14415304f, 0.14429417f, 0.15639621f, 0.16750771f, 0.16872853f, 
  0.16994831f, 0.1732119f, 0.17392659f, 0.17503718f, 0.17853835f, 0.19286355f, 
  0.21295342f, 0.25468874f, 0.27375191f, 0.27811271f, 0.30176556f, 0.30936047f, 
  0.32015526f, 0.34623921f, 0.37099004f, 0.37155402f, 0.37472373f, 0.3868475f, 
  0.38880986f, 0.38993829f, 0.40782553f, 0.42178583f, 0.4382388f, 0.44677454f, 
  0.4807182f, 0.49165776f, 0.4938589f, 0.51609069f, 0.51610923f, 0.53084493f, 
  0.53907657f, 0.58068812f, 0.61505467f, 0.73887819f, 0.75612426f, 0.76734281f, 
  0.78197443f, 0.80595315f, 1.2314328f, 1.2806777f, 1.5040174f, 1.9433945f, 
  2.0957727f, 2.1077282f, 2.4777565f, 2.5329387f, 2.6772566f, 2.8346267f, 3.0945187f, 
  3.6790423f, 4.791791f, 4.8011246f, 5.5416908f, 5.6468654f, 8.8136015f, 56.818279f, 
  105.18284f, 109.97208f, 0.43204579f, 0.78347003f, 0.7850672f, 0.85081697f, 
  0.86201835f, 0.86457169f, 0.86563981f, 0.94141972f, 0.96472949f, 1.0157146f, 
  1.0496181f, 1.0768335f, 1.1465752f, 1.2390172f, 1.2556725f, 1.2758449f, 1.4331362f, 
  1.4363415f, 1.545306f, 1.54532f, 1.5574533f, 1.5745587f, 1.6068373f, 1.6071541f, 
  1.6566203f, 1.6686752f, 1.6810493f, 1.6860161f, 1.686262f, 1.6885318f, 1.7060041f, 
  1.7263122f, 1.754473f, 1.7606084f, 1.7611082f, 1.7737751f, 1.7909677f, 1.7937152f, 
  1.7938917f, 1.7980802f, 1.7991784f, 1.8085256f, 1.8237517f, 1.8433805f, 1.8467042f, 
  1.8512628f, 1.8523641f, 1.8556118f, 1.8557842f, 1.8790598f, 1.8793278f, 1.8799736f, 
  1.8823869f, 1.8848147f, 1.9037023f, 1.9053397f, 1.9250138f, 1.9275842f, 1.9277837f, 
  1.9279586f, 1.9459709f, 1.9480958f, 1.9540207f, 1.9571805f, 1.9619052f, 1.9637897f, 
  1.9645002f, 1.9650354f, 1.9724039f, 1.9771683f, 1.9776518f, 1.9778758f, 1.9800289f, 
  1.9848533f, 1.9855607f, 1.9898933f, 1.9901485f, 2.0144601f, 2.0147924f, 2.0174325f, 
  2.0208747f, 2.0237644f, 2.0280509f, 2.0516081f, 2.0532691f, 2.0575981f, 2.0644877f, 
  2.0672317f, 2.0676224f, 2.073863f, 2.0899079f, 2.0983446f, 2.1087441f, 2.1117115f, 
  2.1167679f, 2.119303f, 2.1193795f, 2.1200452f, 2.1219096f, 2.1224308f, 2.1285858f, 
  2.1410851f, 2.1421158f, 2.1484931f, 2.1487663f, 2.1506925f, 2.1556993f, 2.158453f, 
  2.15974f, 2.1633868f, 2.1764488f, 2.1804194f, 2.1833904f, 2.2128148f, 2.2589893f, 
  2.2626355f, 2.2680986f, 2.2695291f, 2.2703509f, 2.2727904f, 2.2751298f, 2.2829528f, 
  2.2854199f, 0.031333335f, 0.035777777f, 0.041890912f, 0.047136363f, 0.047428571f, 
  0.052685715f, 0.059866667f, 0.06305556f, 0.072733335f, 0.073688895f, 0.091314286f, 
  0.091600001f, 0.095600002f, 0.09725f, 0.1035f, 0.15107894f, 0.3348158f, 0.37264889f, 
  0.45474511f, 0.45490181f, 0.46916667f, 0.48524639f, 0.49584264f, 0.50272f, 
  0.51388597f, 0.51630771f, 0.54265499f, 0.55388892f, 0.55596191f, 0.69814742f, 
  0.70009482f, 0.71023911f, 0.7302925f, 0.77323639f, 0.78957582f, 0.82486951f, 
  0.89252633f, 0.9063285f, 0.90876329f, 0.93789089f, 0.99636436f, 1.0118333f, 
  1.06416f, 1.2206349f, 1.2535238f, 1.41536f, 1.433913f, 1.6581428f, 1.6768334f, 
  1.7673376f, 1.9807754f, 1.9869151f, 1.9886854f, 2.1996632f, 2.2694702f, 2.4817595f, 
  2.8543811f, 3.3048697f, 4.1888037f, 5.2881517f, 5.3252144f, 6.4471922f, 6.6111908f, 
  7.9555655f, 8.7637863f, 8.9483814f, 11.841f, 14.281273f, 14.319636f, 14.413454f, 
  15.752167f, 23.900095f, 31.260382f, 86.509171f, 88.639755f, 152.86063f, 
  0.043047618f, 0.056944445f, 0.057015873f, 0.10623376f, 0.11105555f, 0.11571428f, 
  0.11807692f, 0.1365f, 0.15439999f, 0.32733834f, 0.33325264f, 0.33603334f, 
  0.35038385f, 0.3538788f, 0.35816666f, 0.39168423f, 0.39200002f, 0.39488423f, 
  0.44167101f, 0.4417091f, 0.44311905f, 0.44352001f, 0.44624001f, 0.45891178f, 
  0.4637273f, 0.46630621f, 0.49662858f, 0.51651514f, 0.51722181f, 0.51804f, 
  0.52090478f, 0.53499997f, 0.53546429f, 0.53557563f, 0.5363667f, 0.54853332f, 
  0.55082667f, 0.57923996f, 0.59140003f, 0.59715998f, 0.63050216f, 0.63087881f, 
  0.63498485f, 0.67141819f, 0.6770435f, 0.7686947f, 0.76931012f, 0.78830957f, 
  0.78916997f, 0.82877851f, 0.88213158f, 0.89437878f, 0.90566957f, 0.90941352f, 
  0.95684004f, 0.9597019f, 1.0464032f, 1.1595647f, 1.2912298f, 1.3236363f, 1.3828285f, 
  1.3842106f, 1.4092814f, 1.4187843f, 1.4337556f, 1.4368596f, 1.4443352f, 1.5107071f, 
  1.5370909f, 1.6035869f, 1.6057091f, 1.7004492f, 1.7357461f, 1.7459674f, 1.7908044f, 
  1.7922499f, 1.903697f, 2.1646333f, 3.0370555f, 3.2823462f, 3.6423674f, 4.4284201f, 
  4.5436668f, 4.8230357f, 5.3338337f, 5.811533f, 5.9689093f, 6.5040302f, 6.6941967f, 
  6.7999783f, 7.2329192f, 8.3256092f, 8.8195362f, 9.2157383f, 16.5336f, 19.52416f, 
  28.918568f, 47.113503f, 47.775452f, 51.958244f, 60.130135f, 861.30457f, 1961.3019f, 
  0.0089479452f, 0.008951148f, 0.0092558507f, 0.009574621f, 0.010230549f, 
  0.010403795f, 0.010570761f, 0.010573789f, 0.011169248f, 0.011361407f, 0.01136191f, 
  0.011387056f, 0.011388635f, 0.012110377f, 0.012350909f, 0.012361884f, 0.013040867f, 
  0.014051808f, 0.017401258f, 0.017510977f, 0.025295999f, 0.053960554f, 0.1909532f, 
  0.19096097f, 0.19267611f, 0.19345215f, 0.19349191f, 0.20333348f, 0.23021489f, 
  0.23025683f, 0.23307934f, 0.23552704f, 0.26033646f, 0.27856946f, 0.34862763f, 
  0.3696261f, 0.42596245f, 0.51451319f, 0.53927624f, 0.64041984f, 0.69768763f, 
  0.72007966f, 0.77035892f, 0.84894264f, 1.0457764f, 1.075217f, 1.9046037f, 
  2.2133968f, 2.9891233f, 3.1710663f, 8.0969276f, 8.1200714f, 8.4402943f, 8.4672928f, 
  8.799305f, 8.9479265f, 10.694213f, 10.712626f, 14.981657f, 15.449642f, 20.784031f, 
  21.433493f, 23.267584f, 26.228611f, 28.605677f, 30.883038f, 33.556976f, 35.40535f, 
  35.42609f, 39.668541f, 41.051895f, 44.354393f, 49.901394f, 50.941727f, 51.832977f, 
  58.823746f, 71.056007f, 83.892159f, 88.944016f, 111.16003f, 122.82116f, 274.38538f, 
  314.2962f, 321.43076f, 420.09418f, 463.41425f, 785.77203f, 1249.4846f, 2023.3431f, 
  3407.2979f, 4568.4507f, 19642.281f, 51268.148f, 1814093.0f, 0.02734375f, 0.03515625f, 
  0.04296875f, 0.05859375f, 0.08203125f, 0.08984375f, 0.09765625f, 0.10546875f, 
  0.11328125f, 0.12109375f, 0.12890625f, 0.14453125f, 0.15234375f, 0.16015625f, 
  0.17578125f, 
};

static const int th_len[] = {
  70, 17, 79, 65, 105, 123, 76, 103, 94, 15, 
};
static const int th_begin[] = {
  0, 70, 87, 166, 231, 336, 459, 535, 638, 732, 
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
  if (offset == 747 || val < array[0]) {
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

  if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
            sum += 0.15000000596f;
          } else {
            sum += 0.57293236256f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 80)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
              sum += 0.33333337307f;
            } else {
              sum += -0.22105263174f;
            }
          } else {
            sum += 0.41538465023f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
          sum += 0.27272728086f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 84)) {
            sum += 0.054545458406f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 232)) {
              sum += -0.55918371677f;
            } else {
              sum += 0.15000000596f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
          sum += 0.58373987675f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 160)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += 0.53846156597f;
            } else {
              sum += 0.16000001132f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
              sum += -0.52653062344f;
            } else {
              sum += 0.02222222276f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += -0.51724141836f;
            } else {
              sum += -0.054545458406f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += 0.13846154511f;
            } else {
              sum += 0.57798165083f;
            }
          }
        } else {
          sum += 0.59119158983f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 208)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
            sum += 0.55774652958f;
          } else {
            sum += 0.12000000477f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 214)) {
            sum += -0.36000001431f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 106)) {
              sum += 0.27272728086f;
            } else {
              sum += -.0f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 62)) {
              sum += 0.26153847575f;
            } else {
              sum += -0.37083336711f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 104)) {
              sum += 0.43809527159f;
            } else {
              sum += -0.02222222276f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 198)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 34)) {
              sum += 0.24000000954f;
            } else {
              sum += -0.55875575542f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
              sum += 0.54482758045f;
            } else {
              sum += -0.24000000954f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 114)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 132)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 80)) {
            sum += 0.57316297293f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 158)) {
              sum += 0.46363636851f;
            } else {
              sum += 0.12000000477f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
            sum += 0.45882356167f;
          } else {
            sum += -0.27272728086f;
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 158)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 102)) {
              sum += 0.38823533058f;
            } else {
              sum += -0.44250002503f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += 0.5f;
            } else {
              sum += -.0f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 126)) {
              sum += 0.56417912245f;
            } else {
              sum += 0.15000000596f;
            }
          } else {
            sum += -0.054545458406f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
          sum += 0.46125560999f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += -0.37601274252f;
            } else {
              sum += -0.0071934289299f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += 0.39336779714f;
            } else {
              sum += 0.12875087559f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
          sum += 0.29112911224f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
            sum += 0.11735180765f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 124)) {
              sum += -0.047019328922f;
            } else {
              sum += -0.42936688662f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              sum += 0.45427510142f;
            } else {
              sum += 0.28982281685f;
            }
          } else {
            sum += 0.022516541183f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 154)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 106)) {
              sum += 0.39205622673f;
            } else {
              sum += 0.037828978151f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              sum += 0.062076020986f;
            } else {
              sum += -0.38819369674f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
              sum += -0.40084043145f;
            } else {
              sum += 0.35237127542f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
              sum += 0.082909539342f;
            } else {
              sum += 0.45447325706f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.4452803731f;
            } else {
              sum += 0.098626025021f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
              sum += 0.46143788099f;
            } else {
              sum += 0.35715931654f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 142)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
            sum += 0.46327719092f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
              sum += -0.041573852301f;
            } else {
              sum += 0.3226532042f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 210)) {
              sum += 0.35805732012f;
            } else {
              sum += -0.062849976122f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 144)) {
              sum += -0.35072591901f;
            } else {
              sum += 0.025145789608f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 196)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 60)) {
              sum += 0.3166449666f;
            } else {
              sum += -0.258115381f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 138)) {
              sum += -0.44606882334f;
            } else {
              sum += -0.36817252636f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 152)) {
              sum += 0.073130145669f;
            } else {
              sum += -0.38197734952f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 204)) {
              sum += 0.4102922976f;
            } else {
              sum += -0.075424723327f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 98)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
            sum += 0.44643682241f;
          } else {
            sum += 0.013162012212f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 154)) {
            sum += 0.46600416303f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 90)) {
              sum += 0.10931140929f;
            } else {
              sum += -0.42411255836f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 156)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
              sum += 0.12670776248f;
            } else {
              sum += -0.37107598782f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += 0.43652257323f;
            } else {
              sum += -0.068274267018f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 110)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
              sum += 0.4646768868f;
            } else {
              sum += 0.10937272012f;
            }
          } else {
            sum += -0.050309043378f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 46)) {
          sum += 0.39654156566f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 52)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
              sum += 0.015915315598f;
            } else {
              sum += -0.33020457625f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
              sum += 0.34542289376f;
            } else {
              sum += 0.099590137601f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              sum += 0.12522955239f;
            } else {
              sum += -0.26350331306f;
            }
          } else {
            sum += 0.38273504376f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 124)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              sum += -0.21806393564f;
            } else {
              sum += 0.31358107924f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 230)) {
              sum += -0.3990893364f;
            } else {
              sum += 0.023339385167f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 70)) {
            sum += 0.393191576f;
          } else {
            sum += 0.14832346141f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 112)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
              sum += 0.23403476179f;
            } else {
              sum += 0.48276466131f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 78)) {
              sum += -0.30346813798f;
            } else {
              sum += 0.0047201984562f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              sum += -0.30478513241f;
            } else {
              sum += 0.31289234757f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
              sum += 0.12063035369f;
            } else {
              sum += 0.39367046952f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.38525548577f;
            } else {
              sum += 0.12827606499f;
            }
          } else {
            sum += 0.39840683341f;
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 178)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 108)) {
              sum += 0.38756719232f;
            } else {
              sum += 0.08491487056f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
              sum += -0.13569608331f;
            } else {
              sum += 0.42178574204f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 66)) {
              sum += 0.2992528677f;
            } else {
              sum += 0.019476894289f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += -0.27612313628f;
            } else {
              sum += 0.091381266713f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 76)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += -0.11696622521f;
            } else {
              sum += 0.24897350371f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.016781004146f;
            } else {
              sum += -0.26785072684f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 182)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 44)) {
              sum += 0.014309709892f;
            } else {
              sum += -0.37179937959f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 184)) {
              sum += 0.029413981363f;
            } else {
              sum += 0.39459645748f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 100)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 150)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 96)) {
            sum += 0.10932215303f;
          } else {
            sum += 0.41600397229f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
              sum += 0.38551172614f;
            } else {
              sum += -0.039795316756f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 152)) {
              sum += -0.16532716155f;
            } else {
              sum += 0.23270092905f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 144)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
              sum += -0.05115640536f;
            } else {
              sum += -0.34901061654f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 126)) {
              sum += 0.34799900651f;
            } else {
              sum += -0.054076500237f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 118)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 116)) {
              sum += 0.35320720077f;
            } else {
              sum += -0.12750732899f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 202)) {
              sum += -0.33159929514f;
            } else {
              sum += 0.039806608111f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 48)) {
          sum += 0.36361664534f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 42)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              sum += 0.06058331579f;
            } else {
              sum += -0.3345477581f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 58)) {
              sum += 0.021613754332f;
            } else {
              sum += 0.3028871119f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 134)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 58)) {
              sum += -0.23154623806f;
            } else {
              sum += 0.23709531128f;
            }
          } else {
            sum += 0.38090625405f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 234)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
              sum += 0.012001395226f;
            } else {
              sum += -0.33526054025f;
            }
          } else {
            sum += 0.24276581407f;
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += -0.36177188158f;
            } else {
              sum += 0.12344378233f;
            }
          } else {
            sum += 0.30545455217f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
            sum += 0.074786707759f;
          } else {
            sum += 0.3619543612f;
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
              sum += 0.34149610996f;
            } else {
              sum += 0.024128634483f;
            }
          } else {
            sum += 0.36688321829f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
              sum += 0.32928201556f;
            } else {
              sum += -0.062856733799f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 124)) {
              sum += 0.35725352168f;
            } else {
              sum += 0.1070940271f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 82)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
              sum += 0.11633729935f;
            } else {
              sum += 0.37862452865f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 98)) {
              sum += 0.26521620154f;
            } else {
              sum += -0.22768379748f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 190)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 140)) {
              sum += 0.054658308625f;
            } else {
              sum += -0.24769546092f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 116)) {
              sum += 0.36909490824f;
            } else {
              sum += -0.02036912553f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 130)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 98)) {
              sum += 0.075686201453f;
            } else {
              sum += 0.39797869325f;
            }
          } else {
            sum += -0.0061475639232f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              sum += 0.36941435933f;
            } else {
              sum += -0.058056805283f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
              sum += 0.34227597713f;
            } else {
              sum += 0.1714656055f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 178)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 206)) {
              sum += 0.28566229343f;
            } else {
              sum += -0.075250290334f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 132)) {
              sum += -0.23382799327f;
            } else {
              sum += -0.33714497089f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            sum += -0.15224181116f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 102)) {
              sum += 0.11122875661f;
            } else {
              sum += 0.36316680908f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
          sum += 0.37637406588f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 148)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 146)) {
              sum += -0.29812890291f;
            } else {
              sum += 0.11092285067f;
            }
          } else {
            sum += 0.21783255041f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
            sum += 0.10936190188f;
          } else {
            sum += 0.34368655086f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 30)) {
            sum += -0.21488434076f;
          } else {
            sum += 0.27725869417f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 200)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
              sum += 0.39599093795f;
            } else {
              sum += -0.00734081259f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 222)) {
              sum += -0.0054240226746f;
            } else {
              sum += -0.23225046694f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 130)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += 0.22787739336f;
            } else {
              sum += -0.29744258523f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
              sum += 0.22105292976f;
            } else {
              sum += -0.16865603626f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
              sum += -0.30807179213f;
            } else {
              sum += 0.10153979063f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 50)) {
              sum += 0.30409002304f;
            } else {
              sum += 0.080011129379f;
            }
          }
        } else {
          sum += 0.33766180277f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.32028967142f;
            } else {
              sum += 0.06931848824f;
            }
          } else {
            sum += 0.34550631046f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 220)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
              sum += 0.2021856457f;
            } else {
              sum += 0.33195900917f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += -0.19020837545f;
            } else {
              sum += 0.25772479177f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 110)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              sum += 0.098198153079f;
            } else {
              sum += 0.34755501151f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 46)) {
              sum += 0.26628756523f;
            } else {
              sum += -0.22151276469f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 188)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 48)) {
              sum += 0.14247514307f;
            } else {
              sum += -0.22269295156f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 112)) {
              sum += 0.323138237f;
            } else {
              sum += -0.0079907635227f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 142)) {
              sum += 0.38486778736f;
            } else {
              sum += 0.12301089615f;
            }
          } else {
            sum += -0.023606292903f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 130)) {
              sum += -0.14480137825f;
            } else {
              sum += 0.12027091533f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.32886698842f;
            } else {
              sum += 0.087184287608f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 176)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
              sum += 0.25444063544f;
            } else {
              sum += -0.047205004841f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
              sum += -0.31583571434f;
            } else {
              sum += -0.21111768484f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
            sum += 0.37248745561f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 134)) {
              sum += -0.26167729497f;
            } else {
              sum += 0.23134638369f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 140)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 64)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 116)) {
              sum += 0.14435195923f;
            } else {
              sum += -0.28316894174f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 116)) {
              sum += 0.29958736897f;
            } else {
              sum += -0.058429986238f;
            }
          }
        } else {
          sum += 0.33633202314f;
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 54)) {
        sum += 0.32124912739f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
          sum += 0.28293630481f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 130)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
              sum += -0.16609610617f;
            } else {
              sum += 0.23662282526f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 238)) {
              sum += -0.23060017824f;
            } else {
              sum += 0.17173670232f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
            sum += -0.1281260401f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
              sum += 0.10674428195f;
            } else {
              sum += 0.32494860888f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 140)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
              sum += 0.092899531126f;
            } else {
              sum += 0.33841103315f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
              sum += 0.224850595f;
            } else {
              sum += -0.36468204856f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
              sum += -0.22761374712f;
            } else {
              sum += 0.24400900304f;
            }
          } else {
            sum += 0.3245818615f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
              sum += 0.2909116745f;
            } else {
              sum += -0.1039429009f;
            }
          } else {
            sum += 0.32715135813f;
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 118)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 38)) {
            sum += 0.34727820754f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 78)) {
              sum += 0.16717328131f;
            } else {
              sum += -0.064677298069f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 180)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 108)) {
              sum += 0.28315255046f;
            } else {
              sum += -0.20991821587f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 94)) {
              sum += 0.062428776175f;
            } else {
              sum += -0.14692996442f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 102)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
            sum += 0.03301467374f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 130)) {
              sum += 0.36891171336f;
            } else {
              sum += 0.25213474035f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 124)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 126)) {
              sum += 0.1814005971f;
            } else {
              sum += -0.24584496021f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 182)) {
              sum += 0.28312343359f;
            } else {
              sum += -0.026353612542f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 170)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 64)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 118)) {
              sum += -0.20912268758f;
            } else {
              sum += 0.53042423725f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
              sum += -0.0055866837502f;
            } else {
              sum += -0.28830125928f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
              sum += 0.17127241194f;
            } else {
              sum += -0.18221452832f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 142)) {
              sum += 0.27440989017f;
            } else {
              sum += -0.10633741319f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 142)) {
            sum += 0.17024058104f;
          } else {
            sum += 0.71959841251f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
            sum += 0.34018471837f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
              sum += 0.26355588436f;
            } else {
              sum += -0.24251078069f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
          sum += -0.012603601441f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
            sum += 0.31071984768f;
          } else {
            sum += 0.084059290588f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
          sum += 0.19861826301f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 236)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 62)) {
              sum += 0.12475904822f;
            } else {
              sum += -0.25521421432f;
            }
          } else {
            sum += 0.1765383929f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
            sum += -0.11071179062f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
              sum += 0.29612666368f;
            } else {
              sum += 0.13869065046f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 104)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
              sum += 0.32022410631f;
            } else {
              sum += 0.081443488598f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              sum += -0.41688549519f;
            } else {
              sum += -0.10181532055f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
              sum += -0.22068463266f;
            } else {
              sum += 0.18260937929f;
            }
          } else {
            sum += 0.30949088931f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.27528548241f;
            } else {
              sum += -0.06039403379f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 126)) {
              sum += 0.31686967611f;
            } else {
              sum += 0.23225058615f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 128)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 150)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
              sum += -0.14397794008f;
            } else {
              sum += 0.090293005109f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 114)) {
              sum += 0.59962743521f;
            } else {
              sum += 0.058529112488f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 194)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 130)) {
              sum += 0.0074916551821f;
            } else {
              sum += -0.20509901643f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 140)) {
              sum += -0.14776912332f;
            } else {
              sum += 0.49315959215f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 124)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 138)) {
              sum += 0.33458891511f;
            } else {
              sum += 0.081903487444f;
            }
          } else {
            sum += -0.055090669543f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 186)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 72)) {
              sum += 0.27916389704f;
            } else {
              sum += -0.090057604015f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
              sum += 0.24528394639f;
            } else {
              sum += -0.24397660792f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 94)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 60)) {
              sum += 0.28993108869f;
            } else {
              sum += -0.17582671344f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
              sum += -0.093413248658f;
            } else {
              sum += 0.62997096777f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.18712896109f;
            } else {
              sum += -0.29032078385f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 74)) {
              sum += -0.26062738895f;
            } else {
              sum += 0.10205321014f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 118)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 150)) {
              sum += -0.16060100496f;
            } else {
              sum += 0.28436803818f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              sum += 0.96301859617f;
            } else {
              sum += 0.1812273562f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 180)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 96)) {
              sum += -0.038816943765f;
            } else {
              sum += -0.24842657149f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
              sum += 0.3105558753f;
            } else {
              sum += -0.10931196064f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
        sum += 0.25923803449f;
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 68)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
            sum += -0.035656198859f;
          } else {
            sum += -0.30998799205f;
          }
        } else {
          sum += 0.12906607985f;
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
              sum += 0.24356144667f;
            } else {
              sum += -0.25566834211f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
              sum += 0.0094777848572f;
            } else {
              sum += 0.29423770308f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 82)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              sum += 0.19623503089f;
            } else {
              sum += -0.31784999371f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
              sum += 0.28189283609f;
            } else {
              sum += -0.087690398097f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
              sum += 0.14141742885f;
            } else {
              sum += -0.2081245333f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
              sum += -0.030739499256f;
            } else {
              sum += 0.32313475013f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += 0.27321776748f;
            } else {
              sum += -0.016746424139f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += 0.31207096577f;
            } else {
              sum += 0.21479587257f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 150)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 128)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
              sum += 0.2473628521f;
            } else {
              sum += -0.21620449424f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 112)) {
              sum += 0.33661615849f;
            } else {
              sum += 0.010415114462f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 76)) {
              sum += 0.3131596148f;
            } else {
              sum += 0.067040890455f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 28)) {
              sum += 0.16717259586f;
            } else {
              sum += 0.43701604009f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 186)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += 0.18211863935f;
            } else {
              sum += 0.041074741632f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 88)) {
              sum += 0.0097262728959f;
            } else {
              sum += -0.33497709036f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 48)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 132)) {
              sum += -0.12124592066f;
            } else {
              sum += 0.13906998932f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 154)) {
              sum += -0.20252580941f;
            } else {
              sum += 0.10915970057f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 190)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 132)) {
              sum += 0.20704457164f;
            } else {
              sum += -0.10040739179f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 228)) {
              sum += -0.1740822345f;
            } else {
              sum += 0.25769257545f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.16148203611f;
            } else {
              sum += -0.27208563685f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
              sum += 0.21746264398f;
            } else {
              sum += -0.11763492972f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 78)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 148)) {
              sum += 0.0053522968665f;
            } else {
              sum += 0.57352793217f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
              sum += 0.29536190629f;
            } else {
              sum += -0.11219001561f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 164)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 178)) {
              sum += 0.0047890646383f;
            } else {
              sum += -0.26534092426f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.12962548435f;
            } else {
              sum += 0.18448187411f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
    if (!(data[6].missing != -1) || (data[6].qvalue < 56)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 50)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
            sum += 0.019340680912f;
          } else {
            sum += 0.31840980053f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 120)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
              sum += 0.15023827553f;
            } else {
              sum += -0.24092310667f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 42)) {
              sum += 0.16814927757f;
            } else {
              sum += -0.1191182211f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 118)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 160)) {
              sum += 0.18822164834f;
            } else {
              sum += -0.24956403673f;
            }
          } else {
            sum += 0.34715265036f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
            sum += 0.17226991057f;
          } else {
            sum += 0.61458539963f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 162)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
            sum += 0.28741782904f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
              sum += -0.23746319115f;
            } else {
              sum += 0.095443472266f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 128)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 164)) {
              sum += -0.085892908275f;
            } else {
              sum += -0.21535879374f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 178)) {
              sum += 0.24845631421f;
            } else {
              sum += -0.070954844356f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 244)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
              sum += 0.34359017015f;
            } else {
              sum += -0.25559028983f;
            }
          } else {
            sum += 0.3598639369f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 176)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
              sum += 0.24006004632f;
            } else {
              sum += -0.13699923456f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 172)) {
              sum += -0.22015915811f;
            } else {
              sum += 0.0052046226338f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 196)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
              sum += 0.30496028066f;
            } else {
              sum += 0.026997990906f;
            }
          } else {
            sum += 0.010112731718f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
              sum += 0.023507440463f;
            } else {
              sum += 0.28521803021f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += -0.42171254754f;
            } else {
              sum += 0.032335326076f;
            }
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += -0.24369376898f;
            } else {
              sum += 0.087316535413f;
            }
          } else {
            sum += 0.28587985039f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
            sum += 0.30550315976f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 180)) {
              sum += 0.29682046175f;
            } else {
              sum += 0.036569666117f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 158)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 70)) {
              sum += 0.0073790564202f;
            } else {
              sum += 0.33433446288f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 114)) {
              sum += 0.060882627964f;
            } else {
              sum += -0.25340569019f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 134)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 132)) {
              sum += 0.29433164001f;
            } else {
              sum += 0.06082649529f;
            }
          } else {
            sum += 0.034295871854f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 126)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 138)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 88)) {
              sum += -0.13720162213f;
            } else {
              sum += 0.17176216841f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 106)) {
              sum += -0.071658983827f;
            } else {
              sum += -0.2723916769f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 112)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.3137755096f;
            } else {
              sum += -0.12058830261f;
            }
          } else {
            sum += -0.1775970757f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
            sum += -0.50453084707f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              sum += -0.153108567f;
            } else {
              sum += 0.20968934894f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.23632866144f;
            } else {
              sum += -0.10016858578f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 90)) {
              sum += 0.13173955679f;
            } else {
              sum += 0.30104827881f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 138)) {
            sum += 0.20660604537f;
          } else {
            sum += -0.12395545095f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
              sum += -0.19322811067f;
            } else {
              sum += 0.20422266424f;
            }
          } else {
            sum += 0.30619364977f;
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 126)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 16)) {
          sum += 0.034230906516f;
        } else {
          sum += 0.28385296464f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 52)) {
            sum += 0.28718811274f;
          } else {
            sum += 0.0560891442f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 80)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
              sum += 0.0047418493778f;
            } else {
              sum += -0.36909213662f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 122)) {
              sum += 0.25267070532f;
            } else {
              sum += -0.11799608171f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 174)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 124)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
              sum += 0.08802010864f;
            } else {
              sum += -0.24928599596f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
              sum += 0.036949988455f;
            } else {
              sum += 0.24845451117f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 88)) {
              sum += 0.2601543963f;
            } else {
              sum += -0.032487474382f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 146)) {
              sum += 0.70013713837f;
            } else {
              sum += 0.1650018543f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 120)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 120)) {
              sum += -0.0194362849f;
            } else {
              sum += 0.42875403166f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 66)) {
              sum += -0.11198726296f;
            } else {
              sum += -0.24349416792f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 90)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
              sum += 0.38060715795f;
            } else {
              sum += -0.0025517274626f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 172)) {
              sum += 0.19144389033f;
            } else {
              sum += -0.054325766861f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
              sum += 0.12525288761f;
            } else {
              sum += -0.15671792626f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 76)) {
              sum += 0.020069113001f;
            } else {
              sum += 0.58781504631f;
            }
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
              sum += 0.28142631054f;
            } else {
              sum += -0.2610733211f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 72)) {
              sum += -0.16716325283f;
            } else {
              sum += 0.15153671801f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 176)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 128)) {
              sum += 0.065541625023f;
            } else {
              sum += 0.75612407923f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              sum += 0.20532503724f;
            } else {
              sum += -0.15746533871f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 138)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
              sum += 0.21880242229f;
            } else {
              sum += -0.25068485737f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
              sum += 0.28733387589f;
            } else {
              sum += -0.12963590026f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 146)) {
          sum += 0.20585353673f;
        } else {
          sum += -0.28224423528f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
          sum += 0.071015812457f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
              sum += 0.080863371491f;
            } else {
              sum += 0.29974156618f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 32)) {
              sum += 0.010154360905f;
            } else {
              sum += 0.24420453608f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 172)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 78)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 90)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 72)) {
              sum += 0.18865574896f;
            } else {
              sum += -0.12586948276f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 136)) {
              sum += 0.41249617934f;
            } else {
              sum += 0.053216688335f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 192)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 60)) {
              sum += -0.021037053317f;
            } else {
              sum += -0.143591851f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 202)) {
              sum += 0.1897688061f;
            } else {
              sum += -0.29885664582f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
            sum += 0.44757443666f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 82)) {
              sum += -0.098731771111f;
            } else {
              sum += -0.24715477228f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 122)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 176)) {
              sum += 0.17176944017f;
            } else {
              sum += -0.036532979459f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 136)) {
              sum += -0.26671499014f;
            } else {
              sum += 0.035264786333f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 142)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
            sum += 0.051361773163f;
          } else {
            sum += -0.44976010919f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 54)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
              sum += 0.27925279737f;
            } else {
              sum += 0.1545599401f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
              sum += -0.2877407372f;
            } else {
              sum += 0.21972115338f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
          sum += -0.051869209856f;
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 126)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
              sum += 0.16606134176f;
            } else {
              sum += 0.29314103723f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
              sum += -0.11472236365f;
            } else {
              sum += 0.27611687779f;
            }
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 116)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 100)) {
              sum += 0.025311755016f;
            } else {
              sum += 0.35083699226f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 152)) {
              sum += 0.018232807517f;
            } else {
              sum += 0.29277649522f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
            sum += 0.072428584099f;
          } else {
            sum += -0.24310733378f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 86)) {
          sum += 0.10475618392f;
        } else {
          sum += -0.31085792184f;
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 194)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
            sum += 0.29056605697f;
          } else {
            sum += 0.011982351542f;
          }
        } else {
          sum += 0.010309403762f;
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += 0.2411685288f;
            } else {
              sum += -0.19897551835f;
            }
          } else {
            sum += -0.43703818321f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 40)) {
              sum += 0.1915987581f;
            } else {
              sum += -0.37551560998f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 108)) {
              sum += -0.10814177245f;
            } else {
              sum += 0.21733413637f;
            }
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
              sum += -0.27746278048f;
            } else {
              sum += -0.0082194749266f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
              sum += 0.24638839066f;
            } else {
              sum += -0.068326726556f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
            sum += 0.2618880868f;
          } else {
            sum += -0.016151890159f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
              sum += -0.44242867827f;
            } else {
              sum += 0.27769008279f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += 0.14418445528f;
            } else {
              sum += 0.2952952981f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
              sum += 0.083825647831f;
            } else {
              sum += -0.25388729572f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 12)) {
              sum += -0.087543174624f;
            } else {
              sum += 0.23163384199f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 176)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 168)) {
              sum += 0.23749919236f;
            } else {
              sum += 0.059437852353f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 134)) {
              sum += -0.0015263904352f;
            } else {
              sum += -0.30492129922f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 136)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 126)) {
              sum += -0.06679648906f;
            } else {
              sum += 0.078497558832f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 128)) {
              sum += 0.16518263519f;
            } else {
              sum += -0.235700652f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 132)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 240)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 38)) {
              sum += -0.099539384246f;
            } else {
              sum += -0.21863497794f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.37319654226f;
            } else {
              sum += 0.085091151297f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 200)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 198)) {
              sum += -0.15881507099f;
            } else {
              sum += 0.41460198164f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              sum += 0.2552357614f;
            } else {
              sum += -0.12674941123f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 226)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              sum += 0.08035106957f;
            } else {
              sum += 0.30401027203f;
            }
          } else {
            sum += 0.064650610089f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
            sum += 0.16787399352f;
          } else {
            sum += -0.091018110514f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 186)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 86)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 156)) {
              sum += 0.089367829263f;
            } else {
              sum += 0.34018296003f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 160)) {
              sum += 0.22949501872f;
            } else {
              sum += -0.12240538746f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
            sum += -0.0089090652764f;
          } else {
            sum += -0.27198919654f;
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
    if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 212)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 130)) {
              sum += 0.24130503833f;
            } else {
              sum += 0.03493142128f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
              sum += 0.089320003986f;
            } else {
              sum += -0.19565655291f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 136)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
              sum += 0.073267750442f;
            } else {
              sum += 0.37279456854f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 36)) {
              sum += 0.19559933245f;
            } else {
              sum += -0.18619430065f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 44)) {
          sum += 0.18907572329f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 68)) {
            sum += -0.27495107055f;
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
              sum += -0.13247326016f;
            } else {
              sum += 0.18529419601f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
              sum += 0.19977857172f;
            } else {
              sum += -0.19921581447f;
            }
          } else {
            sum += 0.28754228354f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
              sum += -0.19420222938f;
            } else {
              sum += 0.12830273807f;
            }
          } else {
            sum += -0.42717602849f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += -0.22316715121f;
            } else {
              sum += 0.053201694041f;
            }
          } else {
            sum += 0.2537791431f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              sum += 0.10425036401f;
            } else {
              sum += 0.30027574301f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 170)) {
              sum += 0.27614861727f;
            } else {
              sum += 0.01025544852f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 14)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 134)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
          sum += 0.43639028072f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 136)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
              sum += -0.22905772924f;
            } else {
              sum += 0.046741355211f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 190)) {
              sum += -0.21266250312f;
            } else {
              sum += -0.048541095108f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 216)) {
              sum += 0.29575026035f;
            } else {
              sum += -0.17747451365f;
            }
          } else {
            sum += -0.24873898923f;
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
              sum += 0.48974534869f;
            } else {
              sum += 0.052320659161f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 208)) {
              sum += -0.098399274051f;
            } else {
              sum += 0.36438500881f;
            }
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 120)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 146)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 100)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 114)) {
              sum += 0.036114539951f;
            } else {
              sum += 0.30334153771f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 130)) {
              sum += -0.1121083498f;
            } else {
              sum += 0.30417010188f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 180)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 120)) {
              sum += 0.11565691233f;
            } else {
              sum += 0.50543600321f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 166)) {
              sum += -0.16837614775f;
            } else {
              sum += 0.16928675771f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 86)) {
            sum += 0.22229009867f;
          } else {
            sum += 0.042797740549f;
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 144)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 118)) {
              sum += 0.022020164877f;
            } else {
              sum += -0.28676638007f;
            }
          } else {
            sum += 0.038581062108f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
    if (!(data[6].missing != -1) || (data[6].qvalue < 54)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 84)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
              sum += 0.2302082032f;
            } else {
              sum += -0.1958451122f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
              sum += -0.15412127972f;
            } else {
              sum += 0.22078955173f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 102)) {
              sum += -0.032789800316f;
            } else {
              sum += -0.37252283096f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 192)) {
              sum += 0.13557843864f;
            } else {
              sum += -0.06463265419f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
            sum += 0.2297077328f;
          } else {
            sum += -0.21944560111f;
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
            sum += 0.049398571253f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              sum += 0.21158103645f;
            } else {
              sum += 0.45527738333f;
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 202)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 110)) {
              sum += 0.050149220973f;
            } else {
              sum += -0.14970307052f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 144)) {
              sum += 0.37432613969f;
            } else {
              sum += 0.027652883902f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 110)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
              sum += 0.12536653876f;
            } else {
              sum += -0.19487582147f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
              sum += 0.48279088736f;
            } else {
              sum += -0.031292717904f;
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          sum += 0.37911865115f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 142)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 242)) {
              sum += -0.23548315465f;
            } else {
              sum += 0.2873814702f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 138)) {
              sum += 0.070265285671f;
            } else {
              sum += -0.24633856118f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 94)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
          sum += 0.19733546674f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
            sum += -0.46069294214f;
          } else {
            sum += -0.00104857923f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
              sum += 0.19256260991f;
            } else {
              sum += -0.061675779521f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              sum += 0.097833365202f;
            } else {
              sum += 0.27840441465f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
            sum += -0.24551869929f;
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
              sum += 0.21102707088f;
            } else {
              sum += 0.0089789740741f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 104)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += -0.13596823812f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
            sum += 0.062103584409f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
              sum += 0.28552356362f;
            } else {
              sum += 0.18023633957f;
            }
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 98)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
            sum += 0.098576307297f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 70)) {
              sum += -0.063530042768f;
            } else {
              sum += -0.29448750615f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 150)) {
            sum += 0.34478738904f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 106)) {
              sum += -0.074949577451f;
            } else {
              sum += 0.15737193823f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 188)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
              sum += 0.28519567847f;
            } else {
              sum += 0.006613466423f;
            }
          } else {
            sum += -0.13694526255f;
          }
        } else {
          sum += -0.22633571923f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 148)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
            sum += 0.030428595841f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 34)) {
              sum += -0.061653103679f;
            } else {
              sum += -0.46339842677f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 44)) {
              sum += -0.012761517428f;
            } else {
              sum += 0.21487115324f;
            }
          } else {
            sum += -0.11120510846f;
          }
        }
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 28)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
              sum += -0.27773725986f;
            } else {
              sum += 0.0058752647601f;
            }
          } else {
            sum += 0.048399854451f;
          }
        } else {
          sum += 0.20522907376f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
            sum += -0.14072269201f;
          } else {
            sum += 0.23514790833f;
          }
        } else {
          sum += 0.29447865486f;
        }
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].qvalue < 204)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          sum += 0.036781217903f;
        } else {
          sum += 0.26208946109f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 186)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 166)) {
              sum += 0.2152274698f;
            } else {
              sum += 0.048882044852f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 204)) {
              sum += -0.29673051834f;
            } else {
              sum += -0.016737403348f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 136)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 174)) {
              sum += -0.025692759082f;
            } else {
              sum += 0.15036731958f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 194)) {
              sum += -0.24169661105f;
            } else {
              sum += 0.023926751688f;
            }
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          sum += 0.30781254172f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 116)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
              sum += -0.050532672554f;
            } else {
              sum += -0.23436361551f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 168)) {
              sum += 0.15986399353f;
            } else {
              sum += -0.13335821033f;
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 118)) {
          sum += 0.35689148307f;
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
              sum += -0.26996469498f;
            } else {
              sum += 0.024742431939f;
            }
          } else {
            sum += 0.16197784245f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 132)) {
      if (!(data[8].missing != -1) || (data[8].qvalue < 92)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 56)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 32)) {
              sum += 0.19533605874f;
            } else {
              sum += -0.18176802993f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
              sum += -0.07389266789f;
            } else {
              sum += 0.24634066224f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
              sum += 0.18573430181f;
            } else {
              sum += -0.093561768532f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 224)) {
              sum += 0.1868172586f;
            } else {
              sum += -0.16630363464f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 164)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += -0.2436466068f;
            } else {
              sum += 0.16113817692f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 122)) {
              sum += 0.068848952651f;
            } else {
              sum += 0.32183241844f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 182)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
              sum += 0.10290909559f;
            } else {
              sum += 0.89573431015f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 108)) {
              sum += -0.072607286274f;
            } else {
              sum += 0.32491502166f;
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 112)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 184)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 20)) {
              sum += 0.038491033018f;
            } else {
              sum += 0.55525785685f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 92)) {
              sum += -0.044362034649f;
            } else {
              sum += -0.24606259167f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            sum += 1.0166264772f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 162)) {
              sum += -0.23065553606f;
            } else {
              sum += 0.29015898705f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 120)) {
            sum += 0.72136044502f;
          } else {
            sum += 0.11853116006f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 128)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 156)) {
              sum += -0.0049683498219f;
            } else {
              sum += 0.29510805011f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 160)) {
              sum += -0.25467044115f;
            } else {
              sum += 0.010259822011f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 40)) {
          sum += 0.25782498717f;
        } else {
          sum += 0.059369388968f;
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 136)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
              sum += 0.025018731132f;
            } else {
              sum += -0.40976387262f;
            }
          } else {
            sum += 0.077546611428f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 168)) {
            sum += 0.23839351535f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
              sum += -0.19392153621f;
            } else {
              sum += 0.18208117783f;
            }
          }
        }
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
          sum += -0.12448640168f;
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
            sum += 0.032553762197f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
              sum += 0.17083828151f;
            } else {
              sum += 0.28831100464f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 158)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 148)) {
            sum += 0.26917812228f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 82)) {
              sum += 0.21281841397f;
            } else {
              sum += -0.1371974349f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 76)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 108)) {
              sum += -0.28091588616f;
            } else {
              sum += 0.1179144159f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 166)) {
              sum += -0.16890394688f;
            } else {
              sum += 0.16496169567f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
    if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          sum += 0.12638480961f;
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 30)) {
            sum += -0.46360519528f;
          } else {
            sum += -0.025806618854f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
              sum += 0.063911914825f;
            } else {
              sum += 0.24451197684f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 122)) {
              sum += 0.1316241473f;
            } else {
              sum += -0.18103942275f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 92)) {
            sum += 0.0093576619402f;
          } else {
            sum += 0.27487364411f;
          }
        }
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
            sum += 0.057405427098f;
          } else {
            sum += 0.22073300183f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
            sum += 0.12499392778f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
              sum += -0.36029443145f;
            } else {
              sum += 0.014570933767f;
            }
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
          sum += 0.012413687073f;
        } else {
          sum += 0.29247647524f;
        }
      }
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].qvalue < 10)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 172)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 138)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
            sum += 0.45537286997f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 134)) {
              sum += -0.1871650368f;
            } else {
              sum += 0.062199503183f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 164)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 64)) {
              sum += 0.16186833382f;
            } else {
              sum += -0.22709426284f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 188)) {
              sum += -0.21189872921f;
            } else {
              sum += 0.13521149755f;
            }
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 152)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 186)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
              sum += 0.074860878289f;
            } else {
              sum += -0.24470801651f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 184)) {
              sum += 0.17736642063f;
            } else {
              sum += -0.021506905556f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 156)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 104)) {
              sum += 0.54495900869f;
            } else {
              sum += 0.090062022209f;
            }
          } else {
            sum += -0.2151927799f;
          }
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 50)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 96)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 84)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 86)) {
              sum += -0.034671187401f;
            } else {
              sum += 0.22202263772f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 116)) {
              sum += 0.022912988439f;
            } else {
              sum += -0.26063466072f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 196)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 162)) {
              sum += 0.13529169559f;
            } else {
              sum += 0.53006291389f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
              sum += 0.17080897093f;
            } else {
              sum += -0.15607278049f;
            }
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 74)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 88)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
              sum += 0.19760887325f;
            } else {
              sum += -0.094547525048f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 158)) {
              sum += 0.35975125432f;
            } else {
              sum += 0.01065137051f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 168)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 170)) {
              sum += -0.017999064177f;
            } else {
              sum += -0.16420920193f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 114)) {
              sum += 0.21637003124f;
            } else {
              sum += -0.16914205253f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 24)) {
    if (!(data[5].missing != -1) || (data[5].qvalue < 204)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 94)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 182)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 122)) {
              sum += 0.018826490268f;
            } else {
              sum += -0.18584913015f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 192)) {
              sum += 0.082898654044f;
            } else {
              sum += 0.45740655065f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
              sum += 0.13641147316f;
            } else {
              sum += 0.5622202754f;
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 80)) {
              sum += 0.12384627759f;
            } else {
              sum += -0.17211282253f;
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 206)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
              sum += -0.010751464404f;
            } else {
              sum += 0.28161871433f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 140)) {
              sum += -0.12149707228f;
            } else {
              sum += 0.045845389366f;
            }
          }
        } else {
          if (!(data[6].missing != -1) || (data[6].qvalue < 148)) {
            sum += 0.046132929623f;
          } else {
            sum += 0.42203426361f;
          }
        }
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 134)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
              sum += -0.034490849823f;
            } else {
              sum += -0.2559248209f;
            }
          } else {
            sum += 0.094953760505f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 218)) {
            sum += -0.10270329565f;
          } else {
            sum += 0.18580053747f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 128)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 154)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 92)) {
              sum += 0.089541450143f;
            } else {
              sum += -0.20410293341f;
            }
          } else {
            sum += 0.46577519178f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 240)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 40)) {
              sum += 0.12610602379f;
            } else {
              sum += -0.18489155173f;
            }
          } else {
            sum += 0.20216539502f;
          }
        }
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
      sum += 0.26275697351f;
    } else {
      if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 144)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
              sum += 0.07770062238f;
            } else {
              sum += -0.35580053926f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
              sum += -0.052162699401f;
            } else {
              sum += 0.16049286723f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              sum += 0.12104929239f;
            } else {
              sum += -0.23139457405f;
            }
          } else {
            sum += 0.2392039448f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 46)) {
              sum += -0.1273175329f;
            } else {
              sum += 0.17765381932f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 84)) {
              sum += 0.27899113297f;
            } else {
              sum += 0.079824656248f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 104)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 30)) {
              sum += -0.097412079573f;
            } else {
              sum += 0.16201083362f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 152)) {
              sum += 0.27275690436f;
            } else {
              sum += 0.038430619985f;
            }
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 26)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 52)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 56)) {
            sum += -0.068771071732f;
          } else {
            sum += -0.29979357123f;
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
              sum += 0.15638051927f;
            } else {
              sum += -0.13362017274f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
              sum += 0.25406864285f;
            } else {
              sum += 0.0030679397751f;
            }
          }
        }
      } else {
        sum += 0.28428050876f;
      }
    } else {
      if (!(data[6].missing != -1) || (data[6].qvalue < 150)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
          if (!(data[6].missing != -1) || (data[6].qvalue < 66)) {
            sum += 0.10816732794f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
              sum += -0.12165891379f;
            } else {
              sum += -0.29480102658f;
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
              sum += 0.039961628616f;
            } else {
              sum += 0.33775082231f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 36)) {
              sum += 0.013685910963f;
            } else {
              sum += -0.052493184805f;
            }
          }
        }
      } else {
        sum += 0.26182052493f;
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 96)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
          sum += 0.11273944378f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 42)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              sum += -0.085692241788f;
            } else {
              sum += -0.37814092636f;
            }
          } else {
            sum += -0.00030947523192f;
          }
        }
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
            sum += 0.0052502411418f;
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
              sum += 0.064237289131f;
            } else {
              sum += 0.23681844771f;
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
            sum += -0.23118688166f;
          } else {
            sum += 0.16280922294f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 100)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
          sum += 0.035459011793f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
            sum += 0.038839049637f;
          } else {
            sum += 0.28735584021f;
          }
        }
      } else {
        if (!(data[5].missing != -1) || (data[5].qvalue < 184)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
              sum += 0.22022624314f;
            } else {
              sum += -0.16621483862f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 156)) {
              sum += 0.31421712041f;
            } else {
              sum += 0.061910767108f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 114)) {
            sum += 0.096295267344f;
          } else {
            sum += -0.1913061738f;
          }
        }
      }
    }
  }
  if (!(data[1].missing != -1) || (data[1].qvalue < 18)) {
    if (!(data[8].missing != -1) || (data[8].qvalue < 136)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
          sum += 0.37164917588f;
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 74)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 130)) {
              sum += 0.26085540652f;
            } else {
              sum += -0.084351569414f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
              sum += -0.066507399082f;
            } else {
              sum += -0.22967535257f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 100)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 148)) {
              sum += 0.017682055011f;
            } else {
              sum += -0.13570849597f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 58)) {
              sum += 0.28532356024f;
            } else {
              sum += -0.029414437711f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
            sum += 0.2660150528f;
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 146)) {
              sum += -0.22839985788f;
            } else {
              sum += 0.036214455962f;
            }
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 176)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 122)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 106)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 170)) {
              sum += -0.21472428739f;
            } else {
              sum += 0.052067507058f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
              sum += -0.013527928852f;
            } else {
              sum += 0.47807958722f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 98)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
              sum += 0.5499625206f;
            } else {
              sum += -0.0084707699716f;
            }
          } else {
            sum += -0.10804056376f;
          }
        }
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 96)) {
              sum += 0.28159314394f;
            } else {
              sum += 0.006227822043f;
            }
          } else {
            sum += -0.25613406301f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 174)) {
              sum += -0.19031046331f;
            } else {
              sum += 0.15078219771f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
              sum += 0.12413667887f;
            } else {
              sum += -0.20761464536f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].qvalue < 110)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 144)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 32)) {
              sum += 0.051589265466f;
            } else {
              sum += 0.22129131854f;
            }
          } else {
            sum += 0.31290480494f;
          }
        } else {
          if (!(data[1].missing != -1) || (data[1].qvalue < 22)) {
            sum += -0.29039618373f;
          } else {
            sum += -0.027274843305f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 166)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 174)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 146)) {
              sum += 0.082972817123f;
            } else {
              sum += 0.52815300226f;
            }
          } else {
            sum += -0.0075036017224f;
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
            sum += 0.25024160743f;
          } else {
            sum += -0.13169573247f;
          }
        }
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].qvalue < 120)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 114)) {
          sum += 0.27457085252f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 62)) {
            sum += -0.073987185955f;
          } else {
            sum += 0.14986145496f;
          }
        }
      } else {
        if (!(data[6].missing != -1) || (data[6].qvalue < 124)) {
          if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 68)) {
              sum += 0.22711136937f;
            } else {
              sum += 0.0084598176181f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 162)) {
              sum += -0.063146539032f;
            } else {
              sum += -0.27520036697f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 198)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 102)) {
              sum += 0.22115649283f;
            } else {
              sum += -0.15308725834f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 200)) {
              sum += -0.32727894187f;
            } else {
              sum += 0.20215763152f;
            }
          }
        }
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}