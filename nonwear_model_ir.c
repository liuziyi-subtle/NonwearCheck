#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

static const unsigned char is_categorical[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static const float threshold[] = {
  3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f, 
  0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 0.39157057f, 0.54693246f, 0.55168152f, 0.61856925f, 
  0.63196492f, 0.64115441f, 0.67867756f, 0.69037479f, 0.75434387f, 0.77270555f, 
  0.77456135f, 0.79839426f, 0.82001889f, 0.82634848f, 0.83902848f, 0.84044456f, 
  0.85405368f, 0.85624039f, 0.86113822f, 0.86625719f, 0.87328374f, 0.8764925f, 
  0.87707174f, 0.88070941f, 0.88850516f, 0.88862753f, 0.88881898f, 0.89285362f, 
  0.90322459f, 0.92309976f, 0.92579973f, 0.93222964f, 0.93366098f, 0.93893832f, 
  0.93928838f, 0.93937188f, 0.9409734f, 0.94277453f, 0.94344866f, 0.94358051f, 
  0.94862628f, 0.95173526f, 0.95505267f, 0.95638049f, 0.95773464f, 0.95774239f, 
  0.96157134f, 0.96235478f, 0.96681458f, 0.96912086f, 0.96952903f, 0.96959639f, 
  0.97079921f, 0.97271395f, 0.97717416f, 0.97749949f, 0.97964859f, 0.99198908f, 
  0.99275303f, 0.99344409f, 3961.2537f, 3973.3984f, 4121.8618f, 4134.9004f, 4141.312f, 
  4330.2837f, 4344.5439f, 4452.3945f, 4464.5391f, 4618.2373f, 4795.9678f, 5356.9873f, 
  5567.251f, 6878.0596f, 6878.8467f, 6901.4229f, 6986.4575f, 7141.3125f, 7265.7583f, 
  7619.9395f, 7622.167f, 7685.9443f, 7692.5488f, 7709.4062f, 7755.6426f, 7822.9131f, 
  8143.0791f, 8148.1885f, 8148.8047f, 8251.1484f, 8324.2734f, 8374.6152f, 8389.9795f, 
  8396.1836f, 8401.7197f, 8419.3838f, 8441.9971f, 8446.7598f, 8517.959f, 8560.1406f, 
  8605.5859f, 8623.9766f, 8628.1055f, 8645.6973f, 8647.084f, 8662.5332f, 8962.9893f, 
  9219.6543f, 9228.9961f, 9434.9883f, 9500.1113f, 9599.75f, 9844.2461f, 10082.895f, 
  10099.27f, 11362.195f, 11593.897f, 11694.699f, 11699.046f, 12232.556f, 12369.262f, 
  12426.389f, 12431.904f, 12434.705f, 12450.56f, 12627.342f, 12635.777f, 13330.254f, 
  13368.172f, 13433.893f, 13517.706f, 13839.705f, 13846.189f, 13895.907f, 14190.656f, 
  14190.811f, 14229.719f, 14777.639f, 14860.963f, 15342.273f, 15583.071f, 17606.279f, 
  17805.461f, 17807.996f, 17832.449f, 17837.582f, 17839.5f, 17851.824f, 17932.668f, 
  17954.578f, 17974.018f, 17991.945f, 18007.078f, 18025.951f, 18046.793f, 18056.055f, 
  18056.176f, 18071.439f, 18121.627f, 18135.246f, 18136.566f, 18139.055f, 18215.908f, 
  18298.641f, 18407.074f, 18719.523f, 18745.363f, 19338.523f, 19799.801f, 19845.035f, 
  20072.57f, 20526.26f, 20633.408f, 20757.332f, 20916.77f, 21432.465f, 21711.973f, 
  21766.508f, 21850.311f, 21852.523f, 21928.211f, 21969.191f, 21984.965f, 22007.133f, 
  22044.518f, 22117.973f, 22354.137f, 22638.207f, 22665.074f, 22683.771f, 22738.742f, 
  22745.633f, 22890.461f, 23060.961f, 23322.102f, 23419.141f, 23851.516f, 23851.602f, 
  24337.562f, 24497.141f, 24688.43f, 25024.008f, 25106.01f, 25132.191f, 25201.02f, 
  25238.199f, 25369.914f, 25391.984f, 25557.77f, 25935.93f, 25974.754f, 25990.154f, 
  26009.688f, 26028.531f, 26029.621f, 26034.863f, 26036.242f, 26061.023f, 26144.859f, 
  26251.469f, 26402.695f, 27152.551f, 27215.16f, 27554.992f, 27823.424f, 27895.982f, 
  28094.242f, 28096.762f, 28262.178f, 28283.59f, 28632.195f, 28728.238f, 28752.141f, 
  28881.07f, 28960.582f, 28962.043f, 28964.256f, 29080.93f, 29112.441f, 29361.895f, 
  29362.424f, 29371.605f, 29387.238f, 29419.344f, 29437.082f, 32318.816f, 32373.613f, 
  32612.465f, 32766.9f, 32901.836f, 32910.188f, 32919.852f, 33038.512f, 33144.367f, 
  33177.848f, 33484.152f, 33510.961f, 33624.148f, 33625.359f, 33628.758f, 33630.543f, 
  33676.383f, 33778.414f, 34027.07f, 34188.867f, 34335.055f, 34404.789f, 34438.605f, 
  34468.617f, 34488.938f, 34556.332f, 34602.648f, 34655.742f, 34687.555f, 34747.562f, 
  34782.508f, 34785.406f, 34785.602f, 34833.844f, 34897.586f, 35115.125f, 35123.316f, 
  35452.98f, 35598.93f, 35672.508f, 35686.023f, 35764.48f, 35787.883f, 35877.855f, 
  35890.602f, 36183.461f, 38660.438f, 40675.641f, 42021.516f, 42214.719f, 42333.617f, 
  43112.641f, 43216.469f, 43447.602f, 43497.469f, 43550.238f, 43569.836f, 43577.23f, 
  45309.102f, 0.090723671f, 0.11429767f, 0.11748931f, 0.1255687f, 0.15376067f, 
  0.15563726f, 0.15571807f, 0.15636f, 0.15985315f, 0.18437272f, 0.20315292f, 
  0.20462322f, 0.21263552f, 0.22708929f, 0.25776941f, 0.28323865f, 0.29898992f, 
  0.31289521f, 0.35182711f, 0.42515934f, 0.43269446f, 0.43306243f, 0.53216231f, 
  0.5460248f, 0.58819008f, 0.60829568f, 0.88092339f, 0.88462126f, 1.0222572f, 
  1.1361983f, 1.2070246f, 1.5636075f, 2.2051122f, 2.2642221f, 2.3260779f, 2.6064849f, 
  4.0513458f, 6.2078428f, 6.6071224f, 6.9030228f, 7.9879427f, 16.723423f, 17.193205f, 
  22.284485f, 24.652798f, 37.040092f, 57.45488f, 173.0094f, 0.1522022f, 0.16902635f, 
  0.19514894f, 0.22094485f, 0.22831103f, 0.24936536f, 0.33845168f, 0.35080969f, 
  0.35718882f, 0.37166744f, 0.61422443f, 0.64142531f, 0.95834059f, 1.2863177f, 
  1.3150526f, 1.6217268f, 1.6941491f, 1.9060659f, 1.9744451f, 2.3797474f, 2.8066795f, 
  2.9802737f, 3.1089873f, 4.0084381f, 5.128952f, 5.2232437f, 5.224216f, 5.6115532f, 
  17.498802f, 18.239237f, 27.148054f, 27.381935f, 27.669857f, 35.273849f, 43.037392f, 
  50.537468f, 79.364639f, 90.602005f, 0.054686267f, 0.065217704f, 0.075780198f, 
  0.11747594f, 0.13450813f, 0.15214303f, 0.18494049f, 0.21726245f, 0.22159585f, 
  0.35310999f, 0.62354237f, 0.81175381f, 2.0232902f, 7.7388916f, 27.530222f, 
  0.33001286f, 0.4345541f, 0.46211487f, 0.49560285f, 0.51146561f, 0.53980935f, 
  0.58274901f, 0.59422219f, 0.5968895f, 0.61569226f, 0.6205374f, 0.62111735f, 
  0.64114928f, 0.64717776f, 0.68181717f, 0.70075971f, 0.71784234f, 0.74015617f, 
  0.76004481f, 0.76466906f, 0.7689836f, 0.78066164f, 0.82747459f, 0.83959961f, 
  0.85187638f, 0.85486567f, 0.85598159f, 0.85731292f, 0.88641739f, 0.90358901f, 
  0.93451732f, 0.93922269f, 0.9675734f, 0.99362516f, 0.99996138f, 1.03838f, 
  1.0610232f, 1.0705147f, 1.082078f, 1.1024969f, 1.1246119f, 1.1246514f, 1.1406565f, 
  1.1425761f, 1.1454029f, 1.1523383f, 1.1660163f, 1.1773078f, 1.2293491f, 1.2313559f, 
  1.2349513f, 1.25393f, 1.265538f, 1.3249125f, 1.3489096f, 1.3566902f, 1.3635988f, 
  1.3731529f, 1.3881037f, 1.3911157f, 1.3929391f, 1.4040229f, 1.4382691f, 1.4544092f, 
  1.4763417f, 1.4763902f, 1.4896363f, 1.4957315f, 1.5025094f, 1.5027506f, 1.503636f, 
  1.5064676f, 1.53267f, 1.5496192f, 1.5554011f, 1.5704057f, 1.6202767f, 1.6234488f, 
  1.635312f, 1.6415542f, 1.6695434f, 1.6717091f, 1.6946833f, 1.7037655f, 1.7058446f, 
  1.8101287f, 1.9302353f, 1.9845974f, 0.47265625f, 0.5078125f, 0.51171875f, 
  0.52734375f, 0.54296875f, 0.55078125f, 0.59765625f, 0.62109375f, 0.625f, 
  0.62890625f, 0.64453125f, 0.65234375f, 0.66015625f, 0.66796875f, 0.67578125f, 
  0.68359375f, 0.69140625f, 0.69921875f, 0.70703125f, 0.72265625f, 11.5f, 12.5f, 13.5f, 
  14.0f, 14.5f, 16.5f, 17.5f, 18.0f, 18.5f, 19.5f, 20.5f, 21.5f, 22.5f, 23.5f, 24.5f, 25.5f, 
  26.5f, 27.5f, 28.5f, 29.5f, 30.0f, 30.5f, 31.5f, 32.5f, 33.5f, 36.5f, 37.5f, 39.5f, 40.5f, 
  41.5f, 15.5f, 16.5f, 18.5f, 20.5f, 21.5f, 22.5f, 27.5f, 30.5f, 31.5f, 33.5f, 35.5f, 37.0f, 
  41.5f, 48.5f, 49.5f, 55.5f, 57.5f, 58.5f, 62.5f, 64.0f, 72.5f, 73.0f, 80.5f, 82.0f, 87.5f, 
  0.60490775f, 1.2049626f, 1.3325269f, 1.3842165f, 1.4282311f, 1.467849f, 1.6034765f, 
  1.6171157f, 1.6313143f, 1.6899897f, 1.700711f, 1.7100582f, 1.7558014f, 1.7825199f, 
  1.8009611f, 1.8364582f, 1.8402499f, 1.8438225f, 1.8507959f, 1.8519877f, 1.8520781f, 
  1.8774881f, 1.8861368f, 1.920969f, 1.9224935f, 1.9225091f, 1.9225335f, 1.922857f, 
  1.9235156f, 1.9251472f, 1.9331679f, 1.9465442f, 1.9569542f, 1.9600945f, 1.9655715f, 
  1.9827992f, 2.007199f, 2.007488f, 2.0078821f, 2.014549f, 2.0253115f, 2.0646384f, 
  2.0773098f, 2.0773993f, 2.0779002f, 2.0791039f, 2.0843973f, 2.0853462f, 2.0917516f, 
  2.0942316f, 2.1075478f, 2.1117172f, 2.1119173f, 2.113039f, 2.1130462f, 2.1139193f, 
  2.1210294f, 2.1271701f, 2.1358013f, 2.1359351f, 2.1452456f, 2.1525159f, 2.1550212f, 
  2.1587679f, 2.1623702f, 2.1624403f, 2.1689725f, 2.1711409f, 2.1804688f, 2.1865273f, 
  2.1918144f, 2.1974101f, 2.1999412f, 2.2489467f, 0.57393539f, 0.6027f, 0.61234623f, 
  1.1903799f, 1.1997092f, 1.2015152f, 1.2496508f, 1.4765749f, 1.5588101f, 1.5726013f, 
  1.628341f, 1.6459904f, 1.8326274f, 2.0127158f, 2.0405769f, 2.3601713f, 3.3689203f, 
  4.959816f, 5.744257f, 6.1948709f, 6.8540335f, 7.2949972f, 7.8514776f, 7.8733006f, 
  7.9925203f, 8.6093597f, 9.4090576f, 11.814915f, 12.000687f, 17.769062f, 23.327393f, 
  55.056866f, 169.63116f, 285.9057f, 286.04312f, 286.44943f, 408.2695f, 514.28265f, 
  649.52502f, 913.73608f, 2456.4976f, 2509.7876f, 3403.8735f, 5666.9961f, 20440.703f, 
  20602.129f, 101962.5f, 145274.7f, 0.22449347f, 0.29382217f, 0.33963048f, 
  0.37319511f, 0.38290805f, 0.41820034f, 0.48230606f, 0.50537026f, 0.53789651f, 
  0.57923234f, 0.6892091f, 0.85824561f, 0.89846301f, 0.91334093f, 0.91404653f, 
  1.0088068f, 1.4551833f, 1.5776098f, 1.6573343f, 1.8045458f, 2.1138897f, 2.3028626f, 
  2.6694031f, 3.7089782f, 4.0845814f, 6.0170135f, 10.386604f, 12.864658f, 26.502651f, 
  147.73071f, 219.18301f, 422.42865f, 437.14117f, 2073.8096f, 20799.266f, 0.57209378f, 
  0.59074998f, 0.59950417f, 0.59988236f, 0.61203289f, 0.64270878f, 0.64601684f, 
  0.768664f, 0.7737143f, 0.77649176f, 0.81365335f, 0.86844194f, 0.88407147f, 
  0.8972494f, 0.90578824f, 0.95123088f, 1.0181432f, 1.068346f, 1.1764596f, 1.1848428f, 
  1.3065264f, 1.4333507f, 1.4359925f, 1.4361821f, 1.4398222f, 1.5655638f, 1.6289625f, 
  1.6693316f, 1.6728303f, 1.8176935f, 1.882405f, 2.090663f, 2.1268015f, 2.164669f, 
  2.1873119f, 2.3276076f, 2.5035152f, 2.5050039f, 2.5183365f, 2.6810765f, 2.9976249f, 
  3.191081f, 3.3210659f, 3.394094f, 3.4882319f, 3.5003648f, 3.528338f, 3.8832221f, 
  3.9398639f, 4.3205843f, 4.4624014f, 5.2012982f, 10.522747f, 10.680906f, 10.731224f, 
  15.442841f, 26.707933f, 27.501308f, 29.163643f, 31.183624f, 34.439934f, 34.611141f, 
  36.409195f, 57.236488f, 0.64075673f, 0.64848912f, 0.69399267f, 0.70288122f, 
  0.7213375f, 0.72944564f, 0.7583499f, 0.75847381f, 0.77419436f, 0.77529186f, 
  0.77534521f, 0.77661252f, 0.79285038f, 0.79671884f, 0.82964754f, 0.83706307f, 
  0.84625995f, 0.92468762f, 0.92675483f, 0.93193817f, 0.96614897f, 1.0303822f, 
  1.1035125f, 1.1057818f, 1.1988409f, 1.2891848f, 1.3154812f, 1.4817792f, 1.5206749f, 
  1.5499067f, 1.5698833f, 1.6506703f, 1.683161f, 1.7056198f, 1.7260284f, 1.7730534f, 
  1.7816681f, 1.9319246f, 2.05985f, 2.1389806f, 2.1482563f, 2.2402143f, 2.6043353f, 
  2.8577838f, 3.0502191f, 3.0659306f, 3.7205868f, 3.9357309f, 4.2970061f, 4.3286114f, 
  4.4141397f, 4.490715f, 4.8765192f, 5.3179317f, 7.9720097f, 8.4512806f, 9.0455132f, 
  9.0803146f, 13.859507f, 17.265976f, 17.658554f, 18.607994f, 25.179478f, 28.32616f, 
  34.847153f, 42.7967f, 53.624718f, 54.679199f, 101.4332f, 145.51093f, 
};

static const int th_len[] = {
  14, 5, 60, 244, 48, 38, 15, 88, 20, 30, 25, 74, 48, 35, 64, 70, 
};
static const int th_begin[] = {
  0, 14, 19, 79, 323, 371, 409, 424, 512, 532, 562, 587, 661, 709, 744, 808, 
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
  if (offset == 878 || val < array[0]) {
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
  
  for (int i = 0; i < 16; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }

  if (!(data[7].missing != -1) || (data[7].qvalue < 56)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 44)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 12)) {
        sum += 0.5980810523f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 114)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.57999998331f;
            } else {
              sum += 0.12000000477f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 202)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 8)) {
                sum += -0.16363637149f;
              } else {
                sum += -0.55200004578f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 62)) {
                sum += 0.41538465023f;
              } else {
                sum += -0.37297296524f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 48)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 58)) {
                sum += 0.51951223612f;
              } else {
                sum += 0.033333335072f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 14)) {
                sum += 0.15000000596f;
              } else {
                sum += 0.57254904509f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 262)) {
              sum += 0.46666669846f;
            } else {
              if (!(data[10].missing != -1) || (data[10].qvalue < 16)) {
                sum += -0.40000003576f;
              } else {
                sum += 0.20000001788f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 192)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          sum += -0.066666670144f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 84)) {
              sum += 0.51111114025f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 38)) {
                sum += -0.33333337307f;
              } else {
                sum += 0.20000001788f;
              }
            }
          } else {
            sum += 0.59151947498f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 382)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 118)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 28)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 86)) {
                sum += 0.4769231081f;
              } else {
                sum += -0.25714287162f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
                sum += -0.0f;
              } else {
                sum += -0.54710745811f;
              }
            }
          } else {
            sum += 0.52941179276f;
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += 0.36000001431f;
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 74)) {
                sum += -0.40000003576f;
              } else {
                sum += -0.0f;
              }
            }
          } else {
            sum += 0.57251912355f;
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 26)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 122)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 20)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 0)) {
            sum += 0.15000000596f;
          } else {
            sum += 0.58542513847f;
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 108)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 24)) {
              sum += -0.054545458406f;
            } else {
              sum += 0.48000001907f;
            }
          } else {
            sum += -0.36000001431f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 142)) {
          sum += -0.56571429968f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 50)) {
              sum += -0.45882356167f;
            } else {
              sum += 0.24000000954f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 16)) {
              sum += 0.56727272272f;
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
                sum += -0.15000000596f;
              } else {
                sum += 0.39130437374f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 66)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 424)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 70)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 164)) {
                sum += 0.39402985573f;
              } else {
                sum += -0.16800001264f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 16)) {
                sum += 0.52727276087f;
              } else {
                sum += -0.45301645994f;
              }
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
                sum += 0.057142861187f;
              } else {
                sum += -0.57668691874f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
                sum += 0.31343284249f;
              } else {
                sum += -0.42047247291f;
              }
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 92)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
              sum += -0.054545458406f;
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 26)) {
                sum += 0.23076924682f;
              } else {
                sum += 0.56129032373f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 482)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
                sum += 0.28235295415f;
              } else {
                sum += -0.54970061779f;
              }
            } else {
              sum += 0.55714285374f;
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 92)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 464)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 138)) {
                sum += -0.25467628241f;
              } else {
                sum += 0.30000001192f;
              }
            } else {
              sum += 0.42000001669f;
            }
          } else {
            sum += 0.50769233704f;
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 56)) {
            sum += 0.58048778772f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 148)) {
              sum += -0.12000000477f;
            } else {
              sum += 0.38181820512f;
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 38)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
        sum += 0.46332141757f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 26)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 2)) {
            sum += 0.46749281883f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 16)) {
              sum += 0.034697297961f;
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 86)) {
                sum += 0.43496447802f;
              } else {
                sum += 0.28148031235f;
              }
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 24)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 46)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 4)) {
                sum += 0.051938641816f;
              } else {
                sum += 0.43672931194f;
              }
            } else {
              sum += 0.022030701861f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 50)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 10)) {
                sum += 0.0080939000472f;
              } else {
                sum += 0.37845233083f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
                sum += -0.3782761097f;
              } else {
                sum += 0.052384797484f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 196)) {
        if (!(data[4].missing != -1) || (data[4].qvalue < 42)) {
          sum += -0.07494931668f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 84)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
                sum += 0.4287379086f;
              } else {
                sum += 0.11312214285f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 64)) {
                sum += -0.31174376607f;
              } else {
                sum += 0.2628005743f;
              }
            }
          } else {
            sum += 0.46302950382f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 388)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 66)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 122)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 56)) {
                sum += 0.38479450345f;
              } else {
                sum += 0.10373578221f;
              }
            } else {
              sum += -0.24654383957f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 120)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
                sum += 0.29148682952f;
              } else {
                sum += -0.40264350176f;
              }
            } else {
              sum += 0.40416905284f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 448)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              sum += 0.10183468461f;
            } else {
              sum += 0.4424880445f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
                sum += -0.17520001531f;
              } else {
                sum += 0.35094195604f;
              }
            } else {
              sum += -0.31826117635f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].qvalue < 28)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 16)) {
            sum += 0.45284327865f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 34)) {
              sum += 0.31219694018f;
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 48)) {
                sum += -0.33562779427f;
              } else {
                sum += 0.057121135294f;
              }
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 16)) {
            sum += 0.2756896019f;
          } else {
            sum += -0.42961254716f;
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 24)) {
          sum += 0.47031155229f;
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 28)) {
            sum += 0.33229419589f;
          } else {
            sum += -0.15905919671f;
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 86)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 98)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
                sum += 0.115030922f;
              } else {
                sum += -0.32634329796f;
              }
            } else {
              sum += 0.47501266003f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 416)) {
                sum += -0.32123234868f;
              } else {
                sum += 0.22238066792f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 30)) {
                sum += 0.090648919344f;
              } else {
                sum += 0.48379436135f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 478)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 10)) {
              sum += 0.45583173633f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 86)) {
                sum += -0.30879765749f;
              } else {
                sum += -0.44581699371f;
              }
            }
          } else {
            sum += 0.43812558055f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 126)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 466)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 350)) {
                sum += -0.09286762774f;
              } else {
                sum += -0.43585976958f;
              }
            } else {
              sum += 0.30035310984f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 2)) {
              sum += 0.40694159269f;
            } else {
              sum += 0.014808484353f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 94)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 92)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 222)) {
                sum += 0.37593740225f;
              } else {
                sum += -0.078379847109f;
              }
            } else {
              sum += 0.45110365748f;
            }
          } else {
            sum += 0.10162097216f;
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 62)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 36)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 8)) {
        sum += 0.40178826451f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 16)) {
              sum += 0.180013448f;
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 6)) {
                sum += 0.014495916665f;
              } else {
                sum += -0.40092843771f;
              }
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 24)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 28)) {
                sum += 0.38550576568f;
              } else {
                sum += 0.096308805048f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 114)) {
                sum += 0.14006851614f;
              } else {
                sum += -0.30821278691f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            sum += 0.40206262469f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 266)) {
              if (!(data[6].missing != -1) || (data[6].qvalue < 0)) {
                sum += 0.060776367784f;
              } else {
                sum += 0.36857628822f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 282)) {
                sum += -0.55120313168f;
              } else {
                sum += 0.32650414109f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 208)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 2)) {
          sum += -0.068181857467f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              sum += 0.38296431303f;
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 72)) {
                sum += -0.24602694809f;
              } else {
                sum += 0.29605507851f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 134)) {
                sum += 0.40183538198f;
              } else {
                sum += 0.21261590719f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 40)) {
                sum += -0.071088798344f;
              } else {
                sum += 0.3456979394f;
              }
            }
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 58)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 90)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 50)) {
                sum += 0.31877958775f;
              } else {
                sum += -0.070329844952f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 332)) {
                sum += -0.35996520519f;
              } else {
                sum += 0.067715808749f;
              }
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 48)) {
                sum += -0.0075996639207f;
              } else {
                sum += 0.31038036942f;
              }
            } else {
              sum += 0.4098392725f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 48)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 60)) {
                sum += 0.34473121166f;
              } else {
                sum += -0.015888432041f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 396)) {
                sum += -0.37822198868f;
              } else {
                sum += 0.010285845958f;
              }
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 20)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 40)) {
                sum += -0.1259368211f;
              } else {
                sum += 0.37304222584f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 108)) {
                sum += -0.27148333192f;
              } else {
                sum += -0.049527551979f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 30)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 12)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 8)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 80)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              sum += 0.027112690732f;
            } else {
              sum += 0.37434098125f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 26)) {
              sum += -0.076524063945f;
            } else {
              sum += -0.26272621751f;
            }
          }
        } else {
          sum += 0.40235629678f;
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 34)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 110)) {
              sum += 0.28349083662f;
            } else {
              sum += -0.2441842258f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 18)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 18)) {
                sum += -0.053516436368f;
              } else {
                sum += 0.28328251839f;
              }
            } else {
              sum += 0.43976598978f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 16)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 2)) {
              sum += 0.39480191469f;
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 12)) {
                sum += 0.24292574823f;
              } else {
                sum += -0.10393544286f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 22)) {
              sum += 0.23709027469f;
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
                sum += -0.37414285541f;
              } else {
                sum += 0.024000499398f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 60)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 424)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 80)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 22)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
                sum += 0.38268017769f;
              } else {
                sum += -0.31710517406f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 138)) {
                sum += 0.48315837979f;
              } else {
                sum += -0.11113714427f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
              if (!(data[6].missing != -1) || (data[6].qvalue < 4)) {
                sum += 0.30536603928f;
              } else {
                sum += -0.3881880939f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 168)) {
                sum += 0.5579328537f;
              } else {
                sum += -0.27869951725f;
              }
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 92)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 456)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 152)) {
                sum += 0.52100664377f;
              } else {
                sum += 0.17351317406f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
                sum += -0.16027158499f;
              } else {
                sum += 0.29201236367f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 482)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 20)) {
                sum += 0.27773150802f;
              } else {
                sum += -0.35554715991f;
              }
            } else {
              sum += 0.37232449651f;
            }
          }
        }
      } else {
        if (!(data[10].missing != -1) || (data[10].qvalue < 10)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 0)) {
            sum += -0.0073863263242f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 356)) {
              sum += 0.41228070855f;
            } else {
              sum += 0.12066456676f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 464)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 34)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 354)) {
                sum += -0.034651827067f;
              } else {
                sum += -0.3633633256f;
              }
            } else {
              sum += 0.3506282568f;
            }
          } else {
            sum += 0.36993473768f;
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 34)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.36856472492f;
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 6)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 50)) {
                sum += 0.34793543816f;
              } else {
                sum += 0.089276053011f;
              }
            } else {
              sum += 0.022019091994f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 116)) {
              sum += 0.29383572936f;
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 188)) {
                sum += -0.39152529836f;
              } else {
                sum += 0.014222646132f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 6)) {
            sum += 0.36430847645f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 86)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 8)) {
                sum += 0.058428354561f;
              } else {
                sum += 0.3328332603f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 92)) {
                sum += -0.19050553441f;
              } else {
                sum += 0.22046923637f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 78)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 32)) {
              sum += 0.084720641375f;
            } else {
              sum += 0.32491633296f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 40)) {
              sum += -0.31269201636f;
            } else {
              sum += 0.099510684609f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
            sum += 0.36179342866f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 220)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
                sum += 0.29774913192f;
              } else {
                sum += -0.26794543862f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 228)) {
                sum += 0.43791982532f;
              } else {
                sum += 0.19614204764f;
              }
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 380)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 22)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 304)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 68)) {
                sum += 0.23499169946f;
              } else {
                sum += -0.30666461587f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 366)) {
                sum += 0.38883543015f;
              } else {
                sum += 0.044525966048f;
              }
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 116)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 0)) {
                sum += 0.12664796412f;
              } else {
                sum += -0.35062372684f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
                sum += 0.40178948641f;
              } else {
                sum += 0.0225222148f;
              }
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
            sum += -0.18351396918f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              sum += 0.051195185632f;
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 450)) {
                sum += 0.36217072606f;
              } else {
                sum += 0.086137354374f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].qvalue < 32)) {
      if (!(data[15].missing != -1) || (data[15].qvalue < 14)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 28)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
            sum += 0.34456431866f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 216)) {
              sum += -0.30288487673f;
            } else {
              sum += 0.00078019400826f;
            }
          }
        } else {
          sum += 0.36766907573f;
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 98)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 14)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 26)) {
              sum += -0.20317995548f;
            } else {
              sum += 0.060357667506f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 18)) {
              sum += 0.090030044317f;
            } else {
              sum += 0.38005742431f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 36)) {
            sum += 0.23240117729f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 32)) {
              sum += 0.025310752913f;
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 30)) {
                sum += -0.35537013412f;
              } else {
                sum += -0.080930456519f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 84)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 22)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
                sum += 0.18184325099f;
              } else {
                sum += -0.33046394587f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 74)) {
                sum += 0.39458438754f;
              } else {
                sum += -0.041464626789f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 440)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 20)) {
                sum += -0.26046139002f;
              } else {
                sum += 0.077882431448f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 120)) {
                sum += -0.18037299812f;
              } else {
                sum += 0.3562579751f;
              }
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 10)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 48)) {
                sum += 0.3287229538f;
              } else {
                sum += -0.15271709859f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 14)) {
                sum += -0.15006577969f;
              } else {
                sum += 0.25469106436f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 62)) {
                sum += 0.38949564099f;
              } else {
                sum += -0.11211492866f;
              }
            } else {
              sum += 0.43517720699f;
            }
          }
        }
      } else {
        if (!(data[15].missing != -1) || (data[15].qvalue < 134)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 422)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
              sum += 0.36742383242f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 80)) {
                sum += -0.21953465044f;
              } else {
                sum += -0.34830516577f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 90)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 114)) {
                sum += 0.39910390973f;
              } else {
                sum += -0.057581298053f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 470)) {
                sum += -0.29154750705f;
              } else {
                sum += 0.33966293931f;
              }
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 84)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 30)) {
              sum += -0.2571669817f;
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 66)) {
                sum += -0.11508056521f;
              } else {
                sum += 0.24373693764f;
              }
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 90)) {
              sum += 0.3696795404f;
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 94)) {
                sum += -0.2312092185f;
              } else {
                sum += 0.25829428434f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 54)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.34693056345f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 14)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
            sum += 0.33014628291f;
          } else {
            sum += 0.098939932883f;
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 0)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 14)) {
              sum += 0.34411203861f;
            } else {
              sum += 0.099275998771f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
                sum += 0.1666059792f;
              } else {
                sum += -0.35619747639f;
              }
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 0)) {
                sum += -0.20628760755f;
              } else {
                sum += 0.22467084229f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 242)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 78)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 56)) {
              sum += 0.06705609709f;
            } else {
              sum += 0.29313734174f;
            }
          } else {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.089483134449f;
            } else {
              sum += -0.25677549839f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 120)) {
            sum += 0.32793310285f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 112)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 36)) {
                sum += 0.30590188503f;
              } else {
                sum += 0.040473569185f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 224)) {
                sum += -0.2096901387f;
              } else {
                sum += 0.10676819831f;
              }
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 380)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 290)) {
              sum += 0.069611862302f;
            } else {
              sum += 0.33729186654f;
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 68)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 46)) {
                sum += 0.12989977002f;
              } else {
                sum += -0.30696082115f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
                sum += -0.094148650765f;
              } else {
                sum += 0.35915076733f;
              }
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
              sum += 0.26715388894f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 42)) {
                sum += -0.31114447117f;
              } else {
                sum += -0.032563984394f;
              }
            }
          } else {
            if (!(data[6].missing != -1) || (data[6].qvalue < 8)) {
              sum += 0.064655251801f;
            } else {
              sum += 0.33447769284f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].qvalue < 42)) {
      if (!(data[15].missing != -1) || (data[15].qvalue < 14)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 128)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              sum += 0.33964759111f;
            } else {
              sum += 0.10447202623f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
              sum += 0.16241244972f;
            } else {
              sum += -0.32105216384f;
            }
          }
        } else {
          sum += 0.34726020694f;
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 72)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 34)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 24)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 22)) {
                sum += 0.25817736983f;
              } else {
                sum += -0.04315765202f;
              }
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 14)) {
                sum += -0.046809561551f;
              } else {
                sum += -0.22727775574f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 24)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 146)) {
                sum += 0.20549727976f;
              } else {
                sum += -0.11989542842f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 22)) {
                sum += 0.09460516274f;
              } else {
                sum += 0.40630751848f;
              }
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 4)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 40)) {
              sum += 0.38503620028f;
            } else {
              sum += 0.065055638552f;
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 46)) {
                sum += 0.13903330266f;
              } else {
                sum += -0.3321172595f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
                sum += -0.25681084394f;
              } else {
                sum += 0.26997262239f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 80)) {
        if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 82)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 76)) {
                sum += 0.0025378181599f;
              } else {
                sum += 0.34081998467f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 414)) {
                sum += -0.2361420244f;
              } else {
                sum += 0.19095619023f;
              }
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 66)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 38)) {
                sum += 0.19341705739f;
              } else {
                sum += 0.49383068085f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 4)) {
                sum += 0.28115978837f;
              } else {
                sum += -0.21190562844f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 62)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 112)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 102)) {
                sum += 0.10328852385f;
              } else {
                sum += -0.27928110957f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 150)) {
                sum += 0.66667425632f;
              } else {
                sum += -0.08074735105f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 422)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
                sum += -0.32735544443f;
              } else {
                sum += -0.053713340312f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 100)) {
                sum += 0.2336973995f;
              } else {
                sum += -0.19078934193f;
              }
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 116)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 158)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
                sum += -0.26450702548f;
              } else {
                sum += 0.065957888961f;
              }
            } else {
              if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
                sum += 0.50527536869f;
              } else {
                sum += 0.12623345852f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 38)) {
              sum += 0.26290819049f;
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 64)) {
                sum += -0.30100885034f;
              } else {
                sum += -0.082704529166f;
              }
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 40)) {
            sum += 0.36978247762f;
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 20)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
                sum += -0.2692514956f;
              } else {
                sum += 0.29781410098f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 110)) {
                sum += 0.28925660253f;
              } else {
                sum += -0.16610941291f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 52)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 30)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.33253395557f;
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 10)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 98)) {
            sum += 0.31889137626f;
          } else {
            sum += 0.085157714784f;
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 8)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 0)) {
              sum += 0.038563601673f;
            } else {
              sum += 0.31689557433f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 120)) {
              sum += 0.30057495832f;
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 200)) {
                sum += -0.52206003666f;
              } else {
                sum += 0.1324018389f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 248)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              sum += 0.27105283737f;
            } else {
              sum += -0.094141945243f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 46)) {
              sum += 0.33002567291f;
            } else {
              sum += 0.11995165795f;
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 82)) {
                sum += 0.062636084855f;
              } else {
                sum += -0.22512964904f;
              }
            } else {
              sum += 0.30746799707f;
            }
          } else {
            sum += 0.31196141243f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 376)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
            sum += 0.30210572481f;
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 116)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 26)) {
                sum += -0.27917301655f;
              } else {
                sum += 0.088668547571f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 72)) {
                sum += 0.36484917998f;
              } else {
                sum += 0.039249613881f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 34)) {
            sum += 0.32147270441f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 46)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 76)) {
                sum += -0.28524127603f;
              } else {
                sum += 0.12967126071f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 102)) {
                sum += 0.24669659138f;
              } else {
                sum += -0.027342904359f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 34)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 2)) {
        sum += 0.31926003098f;
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 26)) {
          if (!(data[10].missing != -1) || (data[10].qvalue < 6)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 2)) {
              sum += 0.1421649754f;
            } else {
              sum += -0.057059828192f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 336)) {
              sum += 0.34919586778f;
            } else {
              sum += 0.11338943243f;
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 14)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 14)) {
              sum += -0.13035689294f;
            } else {
              if (!(data[10].missing != -1) || (data[10].qvalue < 42)) {
                sum += 0.33305668831f;
              } else {
                sum += 0.019794736058f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 24)) {
                sum += 0.19182753563f;
              } else {
                sum += -0.27552652359f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 24)) {
                sum += -0.14353071153f;
              } else {
                sum += 0.16353817284f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 92)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 6)) {
                sum += -0.087352871895f;
              } else {
                sum += 0.3631413281f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 52)) {
                sum += 0.32224646211f;
              } else {
                sum += -0.17482224107f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 442)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 126)) {
                sum += -0.23627991974f;
              } else {
                sum += 0.030400497839f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 112)) {
                sum += -0.15522170067f;
              } else {
                sum += 0.30906802416f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 172)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 36)) {
              sum += 0.083266310394f;
            } else {
              sum += 0.45682299137f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 286)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 46)) {
                sum += 0.17041869462f;
              } else {
                sum += -0.2625169754f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
                sum += 0.13171951473f;
              } else {
                sum += 0.43125724792f;
              }
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 118)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 484)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 18)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 106)) {
                sum += 0.44779732823f;
              } else {
                sum += -0.10308352113f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 68)) {
                sum += -0.12861309946f;
              } else {
                sum += -0.30610179901f;
              }
            }
          } else {
            sum += 0.3135510385f;
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 134)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 156)) {
              sum += 0.44194981456f;
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 42)) {
                sum += 0.30173355341f;
              } else {
                sum += -0.23210546374f;
              }
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 108)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 52)) {
                sum += 0.1175872609f;
              } else {
                sum += -0.16782209277f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 78)) {
                sum += -0.17084987462f;
              } else {
                sum += 0.33735060692f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 72)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 22)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 6)) {
        sum += 0.32336738706f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
          sum += 0.32630354166f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 136)) {
            sum += -0.38140133023f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 32)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
                sum += 0.052151836455f;
              } else {
                sum += 0.30427139997f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 10)) {
                sum += -0.29463431239f;
              } else {
                sum += 0.21812726557f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 84)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
            sum += -0.11408361793f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 66)) {
              if (!(data[4].missing != -1) || (data[4].qvalue < 24)) {
                sum += -0.0058761001565f;
              } else {
                sum += 0.30560004711f;
              }
            } else {
              if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
                sum += 0.56786340475f;
              } else {
                sum += 0.084515377879f;
              }
            }
          }
        } else {
          if (!(data[15].missing != -1) || (data[15].qvalue < 58)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              sum += 0.2435733825f;
            } else {
              if (!(data[13].missing != -1) || (data[13].qvalue < 18)) {
                sum += 0.078043721616f;
              } else {
                sum += -0.33372116089f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
                sum += 0.22984056175f;
              } else {
                sum += -0.17518265545f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 82)) {
                sum += 0.064360395074f;
              } else {
                sum += 0.34284582734f;
              }
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 74)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 52)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 212)) {
                sum += -0.33446976542f;
              } else {
                sum += 0.080354906619f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 16)) {
                sum += -0.11127898097f;
              } else {
                sum += 0.39368280768f;
              }
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 28)) {
              sum += 0.42277723551f;
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 94)) {
                sum += -0.2606844902f;
              } else {
                sum += 0.22940167785f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 378)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 352)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 116)) {
                sum += 0.25680372119f;
              } else {
                sum += -0.062433384359f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 70)) {
                sum += 0.091307036579f;
              } else {
                sum += -0.29446318746f;
              }
            }
          } else {
            sum += 0.32879978418f;
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 18)) {
      if (!(data[12].missing != -1) || (data[12].qvalue < 50)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 334)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 34)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 64)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 60)) {
                sum += 0.32964769006f;
              } else {
                sum += -0.052689418197f;
              }
            } else {
              sum += 0.56542217731f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 144)) {
              sum += 0.25544959307f;
            } else {
              sum += -0.11793621629f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 390)) {
            sum += -0.16773560643f;
          } else {
            sum += 0.1952522397f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 12)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 68)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
                sum += 0.15571010113f;
              } else {
                sum += -0.30702698231f;
              }
            } else {
              if (!(data[6].missing != -1) || (data[6].qvalue < 28)) {
                sum += 0.39803335071f;
              } else {
                sum += -0.10662762076f;
              }
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 80)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 42)) {
                sum += 0.11918656528f;
              } else {
                sum += 0.38311466575f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 108)) {
                sum += 0.0088396836072f;
              } else {
                sum += 0.29867908359f;
              }
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 12)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 70)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 24)) {
                sum += 0.20610544086f;
              } else {
                sum += -0.26064813137f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 66)) {
                sum += 0.40425282717f;
              } else {
                sum += 0.021202802658f;
              }
            }
          } else {
            if (!(data[10].missing != -1) || (data[10].qvalue < 28)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 16)) {
                sum += 0.11801923066f;
              } else {
                sum += -0.23643220961f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 104)) {
                sum += -0.027321649715f;
              } else {
                sum += 0.37335002422f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 20)) {
        sum += 0.33600175381f;
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 82)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 38)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 114)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 434)) {
                sum += -0.29361656308f;
              } else {
                sum += 0.0019075459568f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 76)) {
                sum += 0.51689440012f;
              } else {
                sum += -0.1643165946f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 174)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 96)) {
                sum += 0.17101563513f;
              } else {
                sum += 0.88681262732f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 54)) {
                sum += 0.32537314296f;
              } else {
                sum += -0.23990471661f;
              }
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 44)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 270)) {
              sum += 0.40820273757f;
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 18)) {
                sum += 0.27974808216f;
              } else {
                sum += -0.13964700699f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 8)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 68)) {
                sum += -0.09738522023f;
              } else {
                sum += 0.21798162162f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 96)) {
                sum += 0.36730453372f;
              } else {
                sum += -0.21129232645f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 82)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 20)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 4)) {
        sum += 0.31614649296f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 130)) {
          sum += 0.31341531873f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 140)) {
            sum += -0.40463855863f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 2)) {
              if (!(data[6].missing != -1) || (data[6].qvalue < 2)) {
                sum += 0.19007945061f;
              } else {
                sum += -0.28944030404f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 128)) {
                sum += 0.29792165756f;
              } else {
                sum += 0.10078042001f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 180)) {
        if (!(data[6].missing != -1) || (data[6].qvalue < 10)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 108)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 142)) {
                sum += 0.29463878274f;
              } else {
                sum += 0.015418475494f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
                sum += -0.24903924763f;
              } else {
                sum += 0.2153865397f;
              }
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 22)) {
                sum += 0.080551967025f;
              } else {
                sum += -0.31694066525f;
              }
            } else {
              sum += 0.23457103968f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
                sum += 0.37705698609f;
              } else {
                sum += -0.05607284233f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 98)) {
                sum += 0.023531507701f;
              } else {
                sum += -0.21664875746f;
              }
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 140)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 68)) {
                sum += 0.31586560607f;
              } else {
                sum += 0.52720981836f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 92)) {
                sum += 0.18707412481f;
              } else {
                sum += -0.16571089625f;
              }
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 42)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 198)) {
            sum += -0.30854284763f;
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 296)) {
                sum += 0.23508293927f;
              } else {
                sum += -0.20821253955f;
              }
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 22)) {
                sum += 0.19363838434f;
              } else {
                sum += 0.46273371577f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 386)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 20)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
                sum += -0.075567416847f;
              } else {
                sum += 0.26941341162f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 122)) {
                sum += -0.23482894897f;
              } else {
                sum += 0.17458546162f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
              if (!(data[4].missing != -1) || (data[4].qvalue < 62)) {
                sum += 0.12765529752f;
              } else {
                sum += -0.27840542793f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 446)) {
                sum += 0.31896114349f;
              } else {
                sum += -0.07862085849f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 94)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 58)) {
              sum += 0.32458347082f;
            } else {
              sum += -0.03534855321f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 94)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 46)) {
                sum += -0.13896970451f;
              } else {
                sum += 0.085319057107f;
              }
            } else {
              sum += -0.29383438826f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 42)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 92)) {
              sum += 0.063178062439f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 168)) {
                sum += 0.36149394512f;
              } else {
                sum += 0.15510950983f;
              }
            }
          } else {
            sum += 0.018048863858f;
          }
        }
      } else {
        if (!(data[8].missing != -1) || (data[8].qvalue < 8)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 22)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 230)) {
                sum += -0.11200116575f;
              } else {
                sum += 0.38076415658f;
              }
            } else {
              if (!(data[13].missing != -1) || (data[13].qvalue < 66)) {
                sum += -0.24934130907f;
              } else {
                sum += 0.06461879611f;
              }
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 46)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 294)) {
                sum += -0.079523406923f;
              } else {
                sum += 0.21647548676f;
              }
            } else {
              sum += 0.37133833766f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 412)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 124)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 32)) {
                sum += 0.14411889017f;
              } else {
                sum += -0.23184646666f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 82)) {
                sum += 0.46465575695f;
              } else {
                sum += -0.18261989951f;
              }
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 110)) {
              sum += 0.3317143023f;
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 62)) {
                sum += -0.11134190857f;
              } else {
                sum += 0.26016479731f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].qvalue < 82)) {
        if (!(data[13].missing != -1) || (data[13].qvalue < 12)) {
          if (!(data[9].missing != -1) || (data[9].qvalue < 16)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 12)) {
              sum += 0.12720151246f;
            } else {
              sum += -0.20718851686f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 38)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 8)) {
                sum += 0.25866320729f;
              } else {
                sum += -0.015499000438f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 96)) {
                sum += 0.71082103252f;
              } else {
                sum += 0.14989858866f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 476)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 40)) {
                sum += -0.21259994805f;
              } else {
                sum += 0.21415100992f;
              }
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
                sum += -0.29369786382f;
              } else {
                sum += -0.17866206169f;
              }
            }
          } else {
            sum += 0.29788407683f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 252)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 146)) {
              sum += 0.24805504084f;
            } else {
              sum += -0.16847597063f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 136)) {
              sum += 0.41550156474f;
            } else {
              sum += 0.11961631477f;
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 84)) {
            sum += -0.21190886199f;
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 124)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 348)) {
                sum += 0.46978923678f;
              } else {
                sum += 0.024260727689f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 22)) {
                sum += 0.21206443012f;
              } else {
                sum += -0.095961906016f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
    if (!(data[12].missing != -1) || (data[12].qvalue < 14)) {
      if (!(data[7].missing != -1) || (data[7].qvalue < 118)) {
        if (!(data[12].missing != -1) || (data[12].qvalue < 10)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 48)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 40)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 6)) {
                sum += 0.30686807632f;
              } else {
                sum += 0.18331891298f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 186)) {
                sum += -0.20466709137f;
              } else {
                sum += 0.13239401579f;
              }
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 28)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 32)) {
                sum += 0.041647329926f;
              } else {
                sum += 0.19188468158f;
              }
            } else {
              sum += 0.58612400293f;
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 60)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
              sum += -0.24903212488f;
            } else {
              sum += 0.12494092435f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 88)) {
              sum += 0.26046416163f;
            } else {
              sum += 0.042927414179f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 78)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 98)) {
            sum += 0.25878363848f;
          } else {
            sum += 0.015518837608f;
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 12)) {
            sum += -0.25532323122f;
          } else {
            sum += 0.13430567086f;
          }
        }
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 126)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 170)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 134)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
                sum += 0.25151720643f;
              } else {
                sum += -0.089648924768f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 80)) {
                sum += 0.062048245221f;
              } else {
                sum += 0.91646921635f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 426)) {
                sum += -0.2234081775f;
              } else {
                sum += -0.0017667209031f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 312)) {
                sum += -0.12323532999f;
              } else {
                sum += 0.30437490344f;
              }
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 90)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 60)) {
                sum += 0.080284930766f;
              } else {
                sum += 0.46418079734f;
              }
            } else {
              sum += -0.047305289656f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 56)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 0)) {
                sum += 0.28082340956f;
              } else {
                sum += -0.21481889486f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 68)) {
                sum += 0.22967599332f;
              } else {
                sum += -0.117858693f;
              }
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 74)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 424)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 12)) {
              sum += 0.28117033839f;
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
                sum += -0.26689118147f;
              } else {
                sum += 0.19534344971f;
              }
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 52)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 458)) {
                sum += 0.39231646061f;
              } else {
                sum += -0.053744558245f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 484)) {
                sum += -0.26458013058f;
              } else {
                sum += 0.19931457937f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 72)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 128)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 50)) {
                sum += 0.12455201149f;
              } else {
                sum += 0.44994780421f;
              }
            } else {
              sum += -0.054013673216f;
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 132)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 474)) {
                sum += -0.18436074257f;
              } else {
                sum += 0.245097965f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 36)) {
                sum += 0.021771971136f;
              } else {
                sum += 0.32296532393f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
      if (!(data[13].missing != -1) || (data[13].qvalue < 36)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 178)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 108)) {
            sum += 0.45593097806f;
          } else {
            sum += 0.11986947805f;
          }
        } else {
          sum += -0.088526576757f;
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 90)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 56)) {
            sum += -0.045805748552f;
          } else {
            sum += -0.28570413589f;
          }
        } else {
          sum += 0.18158303201f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 58)) {
          sum += 0.31012889743f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 132)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 32)) {
              sum += 0.29004496336f;
            } else {
              if (!(data[5].missing != -1) || (data[5].qvalue < 44)) {
                sum += 0.53876799345f;
              } else {
                sum += 0.16398963332f;
              }
            }
          } else {
            sum += 0.001352832769f;
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 24)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 32)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 18)) {
              sum += 0.30843481421f;
            } else {
              sum += 0.11379986256f;
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 2)) {
              sum += 0.31406503916f;
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 54)) {
                sum += 0.24566400051f;
              } else {
                sum += -0.027514699847f;
              }
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 62)) {
            if (!(data[4].missing != -1) || (data[4].qvalue < 60)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 218)) {
                sum += 0.019818004221f;
              } else {
                sum += 0.37298950553f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 370)) {
                sum += -0.076840728521f;
              } else {
                sum += 0.29525226355f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 384)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 8)) {
                sum += 0.17115156353f;
              } else {
                sum += -0.20560674369f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 54)) {
                sum += 0.25040081143f;
              } else {
                sum += 0.017993312329f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 30)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
      if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
        sum += 0.043024294078f;
      } else {
        if (!(data[2].missing != -1) || (data[2].qvalue < 104)) {
          sum += 0.30810874701f;
        } else {
          sum += 0.069345720112f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
        sum += 0.29880961776f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
          sum += -0.36083704233f;
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
            if (!(data[14].missing != -1) || (data[14].qvalue < 72)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 2)) {
                sum += -0.072055056691f;
              } else {
                sum += 0.24788865447f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 0)) {
                sum += 0.15552943945f;
              } else {
                sum += -0.21223124862f;
              }
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 4)) {
              sum += -0.007791464217f;
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 8)) {
                sum += 0.30168163776f;
              } else {
                sum += 0.13703525066f;
              }
            }
          }
        }
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].qvalue < 44)) {
      if (!(data[14].missing != -1) || (data[14].qvalue < 0)) {
        sum += 0.29667043686f;
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 64)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 100)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 58)) {
                sum += 0.4234559238f;
              } else {
                sum += 0.15063451231f;
              }
            } else {
              if (!(data[13].missing != -1) || (data[13].qvalue < 20)) {
                sum += 0.27313581109f;
              } else {
                sum += -0.20893642306f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 206)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 26)) {
                sum += 0.16756470501f;
              } else {
                sum += -0.18860317767f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 264)) {
                sum += 0.37874948978f;
              } else {
                sum += 0.023529103026f;
              }
            }
          }
        } else {
          if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 346)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 24)) {
                sum += -0.2889688611f;
              } else {
                sum += -0.018099213019f;
              }
            } else {
              sum += 0.051911477f;
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 36)) {
              sum += -0.25884190202f;
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 42)) {
                sum += 0.067971721292f;
              } else {
                sum += 0.27575471997f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[5].missing != -1) || (data[5].qvalue < 54)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 110)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 176)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 44)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 30)) {
                sum += 0.006580893416f;
              } else {
                sum += -0.33164075017f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 162)) {
                sum += 0.17237515748f;
              } else {
                sum += 0.64770543575f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 402)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 46)) {
                sum += -0.039592601359f;
              } else {
                sum += -0.25799113512f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 88)) {
                sum += 0.36873060465f;
              } else {
                sum += -0.082528106868f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 6)) {
            sum += 0.25624027848f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 444)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 30)) {
                sum += 0.038939885795f;
              } else {
                sum += -0.28552058339f;
              }
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 18)) {
                sum += -0.010053760372f;
              } else {
                sum += 0.2792956531f;
              }
            }
          }
        }
      } else {
        if (!(data[7].missing != -1) || (data[7].qvalue < 132)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 214)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 10)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 2)) {
                sum += 0.21797782183f;
              } else {
                sum += -0.23379552364f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 86)) {
                sum += 0.51326012611f;
              } else {
                sum += 0.19849592447f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 120)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 60)) {
                sum += 0.37832787633f;
              } else {
                sum += -0.18089047074f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 52)) {
                sum += 0.27794492245f;
              } else {
                sum += -0.0665012151f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 292)) {
            if (!(data[15].missing != -1) || (data[15].qvalue < 130)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 2)) {
                sum += 0.21400161088f;
              } else {
                sum += -0.24382457137f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 210)) {
                sum += -0.1125819087f;
              } else {
                sum += 0.20107755065f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 342)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 160)) {
                sum += -0.21391513944f;
              } else {
                sum += 0.27625113726f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 438)) {
                sum += -0.23798242211f;
              } else {
                sum += 0.22880510986f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
    if (!(data[15].missing != -1) || (data[15].qvalue < 36)) {
      if (!(data[3].missing != -1) || (data[3].qvalue < 126)) {
        if (!(data[15].missing != -1) || (data[15].qvalue < 18)) {
          sum += 0.29445514083f;
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 78)) {
            sum += 0.27305519581f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 100)) {
              sum += 0.14839062095f;
            } else {
              sum += -0.17470036447f;
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 144)) {
          sum += -0.33006137609f;
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 130)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 328)) {
              sum += 0.30563181639f;
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
                sum += -0.17957919836f;
              } else {
                sum += 0.22067265213f;
              }
            }
          } else {
            sum += -0.11611932516f;
          }
        }
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 156)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 42)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
                sum += 0.43145486712f;
              } else {
                sum += -0.090408399701f;
              }
            } else {
              if (!(data[6].missing != -1) || (data[6].qvalue < 12)) {
                sum += -0.090075165033f;
              } else {
                sum += 0.35815158486f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 32)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 6)) {
                sum += 0.31774193048f;
              } else {
                sum += 0.05944653973f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
                sum += 0.015810353681f;
              } else {
                sum += -0.2650219202f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 406)) {
            if (!(data[8].missing != -1) || (data[8].qvalue < 22)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 362)) {
                sum += 0.053813926876f;
              } else {
                sum += -0.27397546172f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 20)) {
                sum += 0.29312610626f;
              } else {
                sum += -0.1980663389f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 102)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 454)) {
                sum += 0.36318859458f;
              } else {
                sum += -0.075580462813f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 462)) {
                sum += -0.15470461547f;
              } else {
                sum += 0.2540461719f;
              }
            }
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 122)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 84)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
                sum += -0.037996392697f;
              } else {
                sum += -0.23320366442f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 28)) {
                sum += 0.06787379086f;
              } else {
                sum += 0.27171501517f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 4)) {
              sum += 0.21809731424f;
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
                sum += 0.048481456935f;
              } else {
                sum += -0.26873782277f;
              }
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 46)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 368)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 38)) {
                sum += 0.12737900019f;
              } else {
                sum += 0.36205169559f;
              }
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 4)) {
                sum += -0.13096992671f;
              } else {
                sum += 0.030826278031f;
              }
            }
          } else {
            sum += -0.16880387068f;
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
      if (!(data[13].missing != -1) || (data[13].qvalue < 36)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 154)) {
          sum += 0.37473833561f;
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 30)) {
            sum += -0.20833542943f;
          } else {
            sum += 0.18532900512f;
          }
        }
      } else {
        if (!(data[14].missing != -1) || (data[14].qvalue < 114)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 18)) {
            sum += -0.066770605743f;
          } else {
            sum += -0.27171117067f;
          }
        } else {
          sum += 0.12759134173f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
        sum += 0.30782991648f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
          sum += -0.44115254283f;
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
            sum += 0.30100238323f;
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 62)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 302)) {
                sum += 0.059254173189f;
              } else {
                sum += 0.30413991213f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 60)) {
                sum += 0.079636782408f;
              } else {
                sum += -0.19532604516f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[7].missing != -1) || (data[7].qvalue < 28)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 10)) {
      if (!(data[2].missing != -1) || (data[2].qvalue < 100)) {
        sum += 0.30263191462f;
      } else {
        sum += 0.06379879266f;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 132)) {
        sum += 0.28221049905f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 310)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 258)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 138)) {
              sum += -0.32795542479f;
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 74)) {
                sum += 0.2495727092f;
              } else {
                sum += -0.028983253986f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 106)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 288)) {
                sum += -0.36622458696f;
              } else {
                sum += -0.11061849445f;
              }
            } else {
              sum += 0.29776757956f;
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 56)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 22)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 136)) {
                sum += 0.3102208972f;
              } else {
                sum += 0.086634926498f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
                sum += 0.11116278917f;
              } else {
                sum += 0.0045490385965f;
              }
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 54)) {
              sum += 0.17673927546f;
            } else {
              sum += -0.15665744245f;
            }
          }
        }
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
      if (!(data[6].missing != -1) || (data[6].qvalue < 24)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 90)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 40)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 102)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 50)) {
                sum += 0.20621058345f;
              } else {
                sum += 0.50363975763f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 6)) {
                sum += 0.1757735461f;
              } else {
                sum += -0.19777593017f;
              }
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 34)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 8)) {
                sum += 0.17938201129f;
              } else {
                sum += -0.26341986656f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 52)) {
                sum += 0.38787969947f;
              } else {
                sum += 0.017270630226f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 430)) {
            if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 32)) {
                sum += 0.43343579769f;
              } else {
                sum += -0.13161075115f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 78)) {
                sum += -0.06379416585f;
              } else {
                sum += -0.26884546876f;
              }
            }
          } else {
            if (!(data[13].missing != -1) || (data[13].qvalue < 54)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
                sum += 0.35655620694f;
              } else {
                sum += -0.057308804244f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 480)) {
                sum += -0.19590477645f;
              } else {
                sum += 0.17054627836f;
              }
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 360)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 324)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 142)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 234)) {
                sum += 0.23671154678f;
              } else {
                sum += -0.055305998772f;
              }
            } else {
              if (!(data[15].missing != -1) || (data[15].qvalue < 70)) {
                sum += 0.23904700577f;
              } else {
                sum += -0.13722628355f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 330)) {
              if (!(data[6].missing != -1) || (data[6].qvalue < 26)) {
                sum += 0.72423017025f;
              } else {
                sum += 0.21161006391f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 172)) {
                sum += 0.007024242077f;
              } else {
                sum += 0.51845496893f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 472)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 408)) {
              sum += -0.2995750308f;
            } else {
              if (!(data[1].missing != -1) || (data[1].qvalue < 4)) {
                sum += 0.14377756417f;
              } else {
                sum += -0.2325771302f;
              }
            }
          } else {
            sum += 0.27301317453f;
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 166)) {
        if (!(data[11].missing != -1) || (data[11].qvalue < 126)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[5].missing != -1) || (data[5].qvalue < 38)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 22)) {
                sum += 0.24478556216f;
              } else {
                sum += -0.092118650675f;
              }
            } else {
              sum += 0.39142268896f;
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 38)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 106)) {
                sum += 0.27092128992f;
              } else {
                sum += 0.081226445735f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 40)) {
                sum += 0.014108763076f;
              } else {
                sum += 0.4607013464f;
              }
            }
          }
        } else {
          if (!(data[5].missing != -1) || (data[5].qvalue < 6)) {
            sum += 0.23567198217f;
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 52)) {
              sum += -0.31127947569f;
            } else {
              sum += 0.20492760837f;
            }
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 54)) {
          if (!(data[12].missing != -1) || (data[12].qvalue < 38)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 40)) {
              if (!(data[4].missing != -1) || (data[4].qvalue < 46)) {
                sum += 0.19850665331f;
              } else {
                sum += 0.56172412634f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 104)) {
                sum += -0.115912579f;
              } else {
                sum += 0.037821061909f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 372)) {
              if (!(data[4].missing != -1) || (data[4].qvalue < 58)) {
                sum += 0.092104442418f;
              } else {
                sum += -0.15436670184f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 30)) {
                sum += 0.27927082777f;
              } else {
                sum += -0.00044954536133f;
              }
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 64)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 48)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 10)) {
                sum += 0.23159988225f;
              } else {
                sum += -0.11533555388f;
              }
            } else {
              if (!(data[6].missing != -1) || (data[6].qvalue < 16)) {
                sum += -0.13351646066f;
              } else {
                sum += 0.64340937138f;
              }
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 12)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 112)) {
                sum += -0.12350892276f;
              } else {
                sum += 0.37831327319f;
              }
            } else {
              if (!(data[13].missing != -1) || (data[13].qvalue < 34)) {
                sum += 0.12177053839f;
              } else {
                sum += -0.25915786624f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].qvalue < 10)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        sum += 0.23679324985f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 124)) {
          sum += 0.08115568012f;
        } else {
          sum += -0.19890016317f;
        }
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
        sum += 0.10173482448f;
      } else {
        sum += 0.29545021057f;
      }
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
      if (!(data[11].missing != -1) || (data[11].qvalue < 76)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
          if (!(data[14].missing != -1) || (data[14].qvalue < 112)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 98)) {
                sum += 0.34198498726f;
              } else {
                sum += -0.044624045491f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 2)) {
                sum += 0.14277052879f;
              } else {
                sum += -0.15279208124f;
              }
            }
          } else {
            if (!(data[2].missing != -1) || (data[2].qvalue < 72)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 0)) {
                sum += -0.14276485145f;
              } else {
                sum += 0.29164347053f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 4)) {
                sum += 0.24897350371f;
              } else {
                sum += -0.083039373159f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 164)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 80)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 52)) {
                sum += -0.064630649984f;
              } else {
                sum += 0.21503281593f;
              }
            } else {
              if (!(data[6].missing != -1) || (data[6].qvalue < 14)) {
                sum += 0.13788431883f;
              } else {
                sum += 0.49113234878f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 394)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 42)) {
                sum += 0.17668581009f;
              } else {
                sum += -0.12424972653f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 452)) {
                sum += 0.35304576159f;
              } else {
                sum += -0.025064341724f;
              }
            }
          }
        }
      } else {
        if (!(data[4].missing != -1) || (data[4].qvalue < 78)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 76)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 246)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
                sum += 0.15560466051f;
              } else {
                sum += -0.19362145662f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 36)) {
                sum += 0.010652380995f;
              } else {
                sum += -0.24703393877f;
              }
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 16)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 160)) {
                sum += -0.13971251249f;
              } else {
                sum += 0.30942648649f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 118)) {
                sum += -0.24094575644f;
              } else {
                sum += 0.15410608053f;
              }
            }
          }
        } else {
          if (!(data[10].missing != -1) || (data[10].qvalue < 32)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 50)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 104)) {
                sum += 0.085990525782f;
              } else {
                sum += 0.41701969504f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 104)) {
                sum += 0.15321005881f;
              } else {
                sum += -0.17809075117f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 344)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 72)) {
                sum += 0.072118446231f;
              } else {
                sum += 0.45922327042f;
              }
            } else {
              sum += -0.13339398801f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 122)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 20)) {
            sum += 0.01366186887f;
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 144)) {
                sum += 0.33493113518f;
              } else {
                sum += 0.1295658499f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 82)) {
                sum += -0.033573444933f;
              } else {
                sum += 0.17378906906f;
              }
            }
          }
        } else {
          if (!(data[2].missing != -1) || (data[2].qvalue < 62)) {
            sum += 0.0020210095681f;
          } else {
            sum += 0.04175612703f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
          sum += -0.36162301898f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 376)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 320)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
                sum += 0.022721093148f;
              } else {
                sum += 0.47034713626f;
              }
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 62)) {
                sum += 0.17226968706f;
              } else {
                sum += -0.25401651859f;
              }
            }
          } else {
            sum += 0.26786786318f;
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.29982966185f;
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 112)) {
        sum += 0.24469210207f;
      } else {
        sum += -0.035787396133f;
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 86)) {
              sum += 0.60832953453f;
            } else {
              sum += 0.13329139352f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += 0.24360863864f;
            } else {
              sum += -0.21582467854f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 84)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 40)) {
                sum += 0.012378161773f;
              } else {
                sum += -0.24352191389f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 74)) {
                sum += 0.20743475854f;
              } else {
                sum += -0.023179519922f;
              }
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 88)) {
                sum += -0.11817711592f;
              } else {
                sum += 0.27917331457f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 460)) {
                sum += -0.27665355802f;
              } else {
                sum += 0.10310319811f;
              }
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 272)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 154)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 58)) {
                sum += 0.27652016282f;
              } else {
                sum += -0.081934168935f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 8)) {
                sum += 0.0091624297202f;
              } else {
                sum += -0.21601329744f;
              }
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 160)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 58)) {
                sum += 0.13648425043f;
              } else {
                sum += -0.19557406008f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 364)) {
                sum += 0.34701997042f;
              } else {
                sum += 0.026815360412f;
              }
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 88)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 42)) {
              sum += 0.28762283921f;
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 486)) {
                sum += -0.11735153198f;
              } else {
                sum += 0.21210570633f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 338)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 68)) {
                sum += 0.025195056573f;
              } else {
                sum += 0.26213034987f;
              }
            } else {
              sum += -0.095272004604f;
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 60)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 90)) {
              sum += 0.28132545948f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 116)) {
                sum += -0.054300479591f;
              } else {
                sum += 0.1763061583f;
              }
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 44)) {
              sum += 0.25508534908f;
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
                sum += -0.23210178316f;
              } else {
                sum += 0.16359007359f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 94)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 4)) {
              sum += -0.023881278932f;
            } else {
              sum += 0.30769431591f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 30)) {
              sum += 0.1805601269f;
            } else {
              sum += 1.1435207129f;
            }
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 48)) {
          if (!(data[4].missing != -1) || (data[4].qvalue < 68)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 36)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 306)) {
                sum += -0.074114963412f;
              } else {
                sum += 0.18978451192f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
                sum += 0.14786821604f;
              } else {
                sum += 0.36573821306f;
              }
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 4)) {
              if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
                sum += -0.012372412719f;
              } else {
                sum += 0.28604504466f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 374)) {
                sum += -0.16816939414f;
              } else {
                sum += 0.085489220917f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 400)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 250)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 226)) {
                sum += -0.087309956551f;
              } else {
                sum += 0.31761181355f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 70)) {
                sum += -0.22313398123f;
              } else {
                sum += 0.11206915975f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 446)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
                sum += -0.017166180536f;
              } else {
                sum += 0.27558857203f;
              }
            } else {
              sum += -0.20931966603f;
            }
          }
        }
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].qvalue < 4)) {
    if (!(data[14].missing != -1) || (data[14].qvalue < 4)) {
      sum += 0.29325884581f;
    } else {
      if (!(data[14].missing != -1) || (data[14].qvalue < 10)) {
        sum += -0.021550711244f;
      } else {
        if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
          sum += 0.038075610995f;
        } else {
          sum += 0.24708794057f;
        }
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
      if (!(data[4].missing != -1) || (data[4].qvalue < 70)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
          sum += 0.29176706076f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 298)) {
            sum += -0.22296531498f;
          } else {
            sum += 0.26784959435f;
          }
        }
      } else {
        sum += 0.037857204676f;
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 124)) {
        if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 404)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 342)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 300)) {
                sum += -0.08814393729f;
              } else {
                sum += 0.0676580742f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 4)) {
                sum += 0.065496452153f;
              } else {
                sum += -0.28037044406f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 84)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
                sum += -0.10859134048f;
              } else {
                sum += 0.23242761195f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 468)) {
                sum += -0.10750285536f;
              } else {
                sum += 0.22910873592f;
              }
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
            if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 36)) {
                sum += -0.16739299893f;
              } else {
                sum += 0.16265419126f;
              }
            } else {
              if (!(data[13].missing != -1) || (data[13].qvalue < 58)) {
                sum += -0.11646356434f;
              } else {
                sum += 0.05786447227f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 238)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 20)) {
                sum += 0.0067766834982f;
              } else {
                sum += 0.28902667761f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 392)) {
                sum += -0.049989260733f;
              } else {
                sum += 0.2764454186f;
              }
            }
          }
        }
      } else {
        if (!(data[12].missing != -1) || (data[12].qvalue < 8)) {
          if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 102)) {
              sum += 0.3559435308f;
            } else {
              sum += 0.018354719505f;
            }
          } else {
            sum += -0.1481602639f;
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 62)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 116)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
                sum += -0.11038332433f;
              } else {
                sum += -0.26333513856f;
              }
            } else {
              sum += 0.12605722249f;
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 138)) {
              sum += -0.0016623809934f;
            } else {
              sum += 0.18509069085f;
            }
          }
        }
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].qvalue < 2)) {
    if (!(data[4].missing != -1) || (data[4].qvalue < 0)) {
      sum += 0.29566395283f;
    } else {
      if (!(data[8].missing != -1) || (data[8].qvalue < 38)) {
        sum += 0.22036889195f;
      } else {
        sum += -0.056349985301f;
      }
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 32)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 48)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 94)) {
              sum += 0.50927329063f;
            } else {
              sum += 0.098690368235f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 14)) {
              sum += 0.23279550672f;
            } else {
              sum += -0.19056548178f;
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 140)) {
            if (!(data[10].missing != -1) || (data[10].qvalue < 34)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 428)) {
                sum += -0.14510589838f;
              } else {
                sum += 0.13333909214f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 146)) {
                sum += 0.012743143365f;
              } else {
                sum += 0.42306020856f;
              }
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 14)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 90)) {
                sum += -0.16995409131f;
              } else {
                sum += 0.27318894863f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 444)) {
                sum += -0.26510074735f;
              } else {
                sum += 0.051688797772f;
              }
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 472)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 360)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 322)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 136)) {
                sum += 0.1009055227f;
              } else {
                sum += -0.06929654628f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
                sum += -0.04419638589f;
              } else {
                sum += 0.26286494732f;
              }
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 106)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 96)) {
                sum += -0.073232494295f;
              } else {
                sum += 0.19302015007f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
                sum += -0.068753279746f;
              } else {
                sum += -0.27973479033f;
              }
            }
          }
        } else {
          sum += 0.25527262688f;
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 106)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 54)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 34)) {
            sum += 0.22427508235f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 44)) {
              sum += 0.16890643537f;
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 36)) {
                sum += 0.077437266707f;
              } else {
                sum += -0.23535063863f;
              }
            }
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 2)) {
            sum += 0.040726862848f;
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 12)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 26)) {
                sum += -0.00094556610566f;
              } else {
                sum += 0.22587476671f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 64)) {
                sum += 0.23669157922f;
              } else {
                sum += 0.51550805569f;
              }
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 18)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 398)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 6)) {
                sum += 0.17653027177f;
              } else {
                sum += -0.11967138201f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 244)) {
                sum += 0.2709608078f;
              } else {
                sum += 0.068829774857f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 448)) {
              if (!(data[5].missing != -1) || (data[5].qvalue < 16)) {
                sum += -0.042681023479f;
              } else {
                sum += 0.27421885729f;
              }
            } else {
              if (!(data[11].missing != -1) || (data[11].qvalue < 70)) {
                sum += 0.0065825874917f;
              } else {
                sum += -0.21716012061f;
              }
            }
          }
        } else {
          if (!(data[8].missing != -1) || (data[8].qvalue < 32)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 184)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 44)) {
                sum += 0.035670187324f;
              } else {
                sum += 0.38295859098f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 314)) {
                sum += -0.012491939589f;
              } else {
                sum += 0.20369674265f;
              }
            }
          } else {
            if (!(data[12].missing != -1) || (data[12].qvalue < 66)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 152)) {
                sum += -0.2599388361f;
              } else {
                sum += 0.0012861506548f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 280)) {
                sum += 0.40665835142f;
              } else {
                sum += 0.045323774219f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      sum += 0.091035045683f;
    } else {
      sum += 0.29854878783f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 24)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 6)) {
        if (!(data[14].missing != -1) || (data[14].qvalue < 68)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 44)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 96)) {
              if (!(data[1].missing != -1) || (data[1].qvalue < 2)) {
                sum += 0.18002036214f;
              } else {
                sum += -0.11456365138f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 106)) {
                sum += 0.3741530776f;
              } else {
                sum += 0.079539231956f;
              }
            }
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 166)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
                sum += 0.071344435215f;
              } else {
                sum += 0.3195952177f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 104)) {
                sum += 0.09339903295f;
              } else {
                sum += -0.14258432388f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 88)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 24)) {
              if (!(data[8].missing != -1) || (data[8].qvalue < 6)) {
                sum += 0.11932773143f;
              } else {
                sum += -0.14758887887f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 64)) {
                sum += -0.061792936176f;
              } else {
                sum += 0.24913294613f;
              }
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 50)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 38)) {
                sum += 0.13223494589f;
              } else {
                sum += -0.15760703385f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 74)) {
                sum += 0.10138849914f;
              } else {
                sum += -0.038195122033f;
              }
            }
          }
        }
      } else {
        if (!(data[11].missing != -1) || (data[11].qvalue < 88)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 16)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 110)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 18)) {
                sum += 0.089240916073f;
              } else {
                sum += -0.1642973274f;
              }
            } else {
              if (!(data[8].missing != -1) || (data[8].qvalue < 28)) {
                sum += 0.21734648943f;
              } else {
                sum += -0.096214808524f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 76)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 76)) {
                sum += 0.077772423625f;
              } else {
                sum += 0.32302296162f;
              }
            } else {
              if (!(data[12].missing != -1) || (data[12].qvalue < 44)) {
                sum += 0.21921958029f;
              } else {
                sum += -0.11229773611f;
              }
            }
          }
        } else {
          if (!(data[4].missing != -1) || (data[4].qvalue < 80)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 420)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 58)) {
                sum += -0.24294808507f;
              } else {
                sum += 0.11567005515f;
              }
            } else {
              if (!(data[6].missing != -1) || (data[6].qvalue < 18)) {
                sum += 0.17727947235f;
              } else {
                sum += -0.10624199361f;
              }
            }
          } else {
            if (!(data[11].missing != -1) || (data[11].qvalue < 118)) {
              sum += -0.11619850248f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 170)) {
                sum += 0.23172186315f;
              } else {
                sum += 0.045119792223f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 260)) {
        if (!(data[5].missing != -1) || (data[5].qvalue < 30)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 130)) {
            sum += 0.29529169202f;
          } else {
            if (!(data[7].missing != -1) || (data[7].qvalue < 12)) {
              sum += 0.17159864306f;
            } else {
              sum += -0.09543954581f;
            }
          }
        } else {
          sum += 0.018442858011f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
          sum += -0.36553499103f;
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
            if (!(data[13].missing != -1) || (data[13].qvalue < 56)) {
              sum += -0.15889570117f;
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 36)) {
                sum += -0.078505955637f;
              } else {
                sum += 0.19802190363f;
              }
            }
          } else {
            if (!(data[9].missing != -1) || (data[9].qvalue < 54)) {
              if (!(data[9].missing != -1) || (data[9].qvalue < 46)) {
                sum += 0.087081819773f;
              } else {
                sum += 0.28525280952f;
              }
            } else {
              sum += -0.065826497972f;
            }
          }
        }
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].qvalue < 2)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 8)) {
      sum += 0.068938419223f;
    } else {
      if (!(data[9].missing != -1) || (data[9].qvalue < 30)) {
        sum += 0.04577133432f;
      } else {
        sum += 0.28667327762f;
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].qvalue < 4)) {
      if (!(data[0].missing != -1) || (data[0].qvalue < 14)) {
        sum += 0.047944735736f;
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 278)) {
          sum += 0.26589816809f;
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 316)) {
            sum += -0.15098948777f;
          } else {
            sum += 0.23562155664f;
          }
        }
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].qvalue < 124)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 28)) {
          if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
            sum += 0.35846036673f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 18)) {
              sum += 0.24886862934f;
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 124)) {
                sum += 0.089041359723f;
              } else {
                sum += -0.17285887897f;
              }
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 432)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 358)) {
              if (!(data[10].missing != -1) || (data[10].qvalue < 26)) {
                sum += -0.044110126793f;
              } else {
                sum += 0.047576073557f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 404)) {
                sum += -0.25089123845f;
              } else {
                sum += 0.036012161523f;
              }
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 0)) {
              if (!(data[2].missing != -1) || (data[2].qvalue < 54)) {
                sum += -0.0030867652968f;
              } else {
                sum += -0.16093789041f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 78)) {
                sum += 0.086685448885f;
              } else {
                sum += 0.26867437363f;
              }
            }
          }
        }
      } else {
        if (!(data[1].missing != -1) || (data[1].qvalue < 0)) {
          if (!(data[13].missing != -1) || (data[13].qvalue < 26)) {
            sum += 0.26039865613f;
          } else {
            sum += -0.047619845718f;
          }
        } else {
          if (!(data[13].missing != -1) || (data[13].qvalue < 64)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 74)) {
              if (!(data[7].missing != -1) || (data[7].qvalue < 70)) {
                sum += 0.17431969941f;
              } else {
                sum += -0.11320302635f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 418)) {
                sum += -0.2129868716f;
              } else {
                sum += 0.014912300743f;
              }
            }
          } else {
            sum += 0.082718223333f;
          }
        }
      }
    }
  }
  if (!(data[12].missing != -1) || (data[12].qvalue < 0)) {
    if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
      sum += 0.07614222914f;
    } else {
      sum += 0.29036477208f;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].qvalue < 22)) {
      if (!(data[1].missing != -1) || (data[1].qvalue < 8)) {
        if (!(data[9].missing != -1) || (data[9].qvalue < 50)) {
          if (!(data[3].missing != -1) || (data[3].qvalue < 102)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 100)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 86)) {
                sum += 0.077937282622f;
              } else {
                sum += -0.14862176776f;
              }
            } else {
              sum += 0.59994214773f;
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 150)) {
              if (!(data[4].missing != -1) || (data[4].qvalue < 88)) {
                sum += -0.23263119161f;
              } else {
                sum += 0.027853270993f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 236)) {
                sum += 0.06357396394f;
              } else {
                sum += -0.051266219467f;
              }
            }
          }
        } else {
          if (!(data[14].missing != -1) || (data[14].qvalue < 78)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 204)) {
              sum += -0.01624796167f;
            } else {
              if (!(data[10].missing != -1) || (data[10].qvalue < 12)) {
                sum += 0.080668345094f;
              } else {
                sum += 0.39588966966f;
              }
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 26)) {
              sum += 0.10324718803f;
            } else {
              sum += -0.16072639823f;
            }
          }
        }
      } else {
        if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
          if (!(data[11].missing != -1) || (data[11].qvalue < 56)) {
            if (!(data[11].missing != -1) || (data[11].qvalue < 38)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 40)) {
                sum += 0.14763842523f;
              } else {
                sum += -0.17660430074f;
              }
            } else {
              if (!(data[9].missing != -1) || (data[9].qvalue < 20)) {
                sum += 0.46836057305f;
              } else {
                sum += -0.10743656009f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 436)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 66)) {
                sum += -0.093444138765f;
              } else {
                sum += -0.26142656803f;
              }
            } else {
              sum += 0.044618278742f;
            }
          }
        } else {
          if (!(data[12].missing != -1) || (data[12].qvalue < 48)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 268)) {
              sum += 0.25040066242f;
            } else {
              sum += 0.043583318591f;
            }
          } else {
            if (!(data[5].missing != -1) || (data[5].qvalue < 28)) {
              sum += -0.16144669056f;
            } else {
              sum += 0.07949552685f;
            }
          }
        }
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].qvalue < 0)) {
        if (!(data[2].missing != -1) || (data[2].qvalue < 14)) {
          sum += 0.25817033648f;
        } else {
          sum += 0.031814023852f;
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 182)) {
          if (!(data[8].missing != -1) || (data[8].qvalue < 34)) {
            if (!(data[6].missing != -1) || (data[6].qvalue < 20)) {
              sum += 0.28826728463f;
            } else {
              sum += 0.076222680509f;
            }
          } else {
            if (!(data[4].missing != -1) || (data[4].qvalue < 26)) {
              sum += 0.22976590693f;
            } else {
              sum += -0.13061274588f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 190)) {
            sum += -0.35610640049f;
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 256)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 56)) {
                sum += 0.32554996014f;
              } else {
                sum += -0.072437919676f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 276)) {
                sum += -0.30434572697f;
              } else {
                sum += 0.060579713434f;
              }
            }
          }
        }
      }
    }
  }
  if (!(data[13].missing != -1) || (data[13].qvalue < 0)) {
    if (!(data[0].missing != -1) || (data[0].qvalue < 6)) {
      sum += 0.061997611076f;
    } else {
      sum += 0.28591507673f;
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].qvalue < 26)) {
      if (!(data[5].missing != -1) || (data[5].qvalue < 52)) {
        if (!(data[7].missing != -1) || (data[7].qvalue < 96)) {
          if (!(data[2].missing != -1) || (data[2].qvalue < 70)) {
            if (!(data[12].missing != -1) || (data[12].qvalue < 46)) {
              sum += 0.1062431857f;
            } else {
              if (!(data[14].missing != -1) || (data[14].qvalue < 66)) {
                sum += -0.024234725162f;
              } else {
                sum += -0.18947640061f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 94)) {
              if (!(data[13].missing != -1) || (data[13].qvalue < 50)) {
                sum += 0.064478337765f;
              } else {
                sum += 0.46680924296f;
              }
            } else {
              sum += -0.026428181678f;
            }
          }
        } else {
          if (!(data[3].missing != -1) || (data[3].qvalue < 26)) {
            if (!(data[9].missing != -1) || (data[9].qvalue < 10)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 88)) {
                sum += 0.31690192223f;
              } else {
                sum += 0.036312181503f;
              }
            } else {
              sum += -0.062874369323f;
            }
          } else {
            if (!(data[8].missing != -1) || (data[8].qvalue < 12)) {
              sum += 0.17859555781f;
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 430)) {
                sum += -0.22081767023f;
              } else {
                sum += 0.078540027142f;
              }
            }
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 274)) {
          if (!(data[7].missing != -1) || (data[7].qvalue < 158)) {
            if (!(data[7].missing != -1) || (data[7].qvalue < 74)) {
              if (!(data[12].missing != -1) || (data[12].qvalue < 64)) {
                sum += 0.0020088609308f;
              } else {
                sum += -0.24909715354f;
              }
            } else {
              if (!(data[10].missing != -1) || (data[10].qvalue < 28)) {
                sum += -0.021367838606f;
              } else {
                sum += 0.23971091211f;
              }
            }
          } else {
            if (!(data[15].missing != -1) || (data[15].qvalue < 128)) {
              if (!(data[14].missing != -1) || (data[14].qvalue < 52)) {
                sum += 0.083090245724f;
              } else {
                sum += -0.23837007582f;
              }
            } else {
              if (!(data[7].missing != -1) || (data[7].qvalue < 174)) {
                sum += -0.07285001874f;
              } else {
                sum += 0.26265269518f;
              }
            }
          }
        } else {
          if (!(data[7].missing != -1) || (data[7].qvalue < 162)) {
            if (!(data[2].missing != -1) || (data[2].qvalue < 48)) {
              if (!(data[11].missing != -1) || (data[11].qvalue < 64)) {
                sum += 0.029782608151f;
              } else {
                sum += 0.2901045382f;
              }
            } else {
              if (!(data[10].missing != -1) || (data[10].qvalue < 44)) {
                sum += -0.21932260692f;
              } else {
                sum += 0.013760951348f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 110)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 340)) {
                sum += 0.48702222109f;
              } else {
                sum += -0.02662124671f;
              }
            } else {
              if (!(data[0].missing != -1) || (data[0].qvalue < 10)) {
                sum += 0.1025563553f;
              } else {
                sum += -0.19262948632f;
              }
            }
          }
        }
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].qvalue < 240)) {
        if (!(data[3].missing != -1) || (data[3].qvalue < 232)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 100)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 118)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 48)) {
                sum += -0.04659229517f;
              } else {
                sum += 0.20677663386f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 148)) {
                sum += -0.29679340124f;
              } else {
                sum += 0.020116565749f;
              }
            }
          } else {
            if (!(data[3].missing != -1) || (data[3].qvalue < 194)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 56)) {
                sum += 0.035591196269f;
              } else {
                sum += 0.48533797264f;
              }
            } else {
              if (!(data[4].missing != -1) || (data[4].qvalue < 76)) {
                sum += -0.20272488892f;
              } else {
                sum += 0.096587345004f;
              }
            }
          }
        } else {
          if (!(data[9].missing != -1) || (data[9].qvalue < 44)) {
            sum += 0.69204884768f;
          } else {
            sum += 0.11401107907f;
          }
        }
      } else {
        if (!(data[3].missing != -1) || (data[3].qvalue < 284)) {
          if (!(data[15].missing != -1) || (data[15].qvalue < 114)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 254)) {
              if (!(data[15].missing != -1) || (data[15].qvalue < 72)) {
                sum += 0.17004528642f;
              } else {
                sum += -0.22466640174f;
              }
            } else {
              sum += -0.32144725323f;
            }
          } else {
            if (!(data[0].missing != -1) || (data[0].qvalue < 20)) {
              sum += -0.19647783041f;
            } else {
              sum += 0.28286466002f;
            }
          }
        } else {
          if (!(data[11].missing != -1) || (data[11].qvalue < 60)) {
            if (!(data[3].missing != -1) || (data[3].qvalue < 318)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 308)) {
                sum += 0.010643198155f;
              } else {
                sum += 0.45483583212f;
              }
            } else {
              if (!(data[3].missing != -1) || (data[3].qvalue < 326)) {
                sum += -0.22873486578f;
              } else {
                sum += 0.091466657817f;
              }
            }
          } else {
            if (!(data[14].missing != -1) || (data[14].qvalue < 86)) {
              if (!(data[3].missing != -1) || (data[3].qvalue < 410)) {
                sum += -0.028948893771f;
              } else {
                sum += 0.22496159375f;
              }
            } else {
              if (!(data[2].missing != -1) || (data[2].qvalue < 6)) {
                sum += 0.14454098046f;
              } else {
                sum += -0.24466428161f;
              }
            }
          }
        }
      }
    }
  }
  
  return 1.0f / (1 + expf(-sum));
  // return sum;
}