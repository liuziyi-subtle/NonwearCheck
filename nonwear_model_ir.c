#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

float PredictIr(union NonwearEntry* data) {
  double sum = .0;
  unsigned int tmp;
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.78904903)) {
    if (!(data[12].missing != -1) || (data[12].fvalue < 3.2643203e+11)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.70008117)) {
        sum += (float)-0.59602851;
      } else {
        sum += (float)-0.39574468;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59526.148)) {
        sum += (float)0.59036148;
      } else {
        sum += (float)-0.5819549;
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < -1.0587235e+09)) {
      sum += (float)-0.5865922;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 1.5694733)) {
        sum += (float)-0.19120881;
      } else {
        sum += (float)0.56097347;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.81601894)) {
    if (!(data[12].missing != -1) || (data[12].fvalue < 3.2643203e+11)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.75206935)) {
        sum += (float)-0.45727292;
      } else {
        sum += (float)-0.21378143;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59526.148)) {
        sum += (float)0.46002975;
      } else {
        sum += (float)-0.44895288;
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < -1.0587235e+09)) {
      sum += (float)-0.45418915;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 1.3650131)) {
        sum += (float)-0.25057918;
      } else {
        sum += (float)0.43478298;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.76618528)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4758.4824)) {
      if (!(data[18].missing != -1) || (data[18].fvalue < 8.5460815)) {
        sum += (float)-0.39577168;
      } else {
        sum += (float)-0.030248363;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59526.148)) {
        sum += (float)0.39527443;
      } else {
        sum += (float)-0.39893198;
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < -1.0587235e+09)) {
      sum += (float)-0.40317717;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 2.9219971)) {
        sum += (float)0.079378814;
      } else {
        sum += (float)0.38245806;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.81914282)) {
    if (!(data[12].missing != -1) || (data[12].fvalue < 3.2643203e+11)) {
      if (!(data[18].missing != -1) || (data[18].fvalue < 8.0600586)) {
        sum += (float)-0.35258597;
      } else {
        sum += (float)0.078620769;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59526.148)) {
        sum += (float)0.36347553;
      } else {
        sum += (float)-0.35249206;
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].fvalue < -1047.5161)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 3.5002858e+08)) {
        sum += (float)-0.36175627;
      } else {
        sum += (float)-0.085733749;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 70866.875)) {
        sum += (float)0.32648107;
      } else {
        sum += (float)-0.98157376;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.850124)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4758.4824)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.66456592)) {
        sum += (float)-0.34611955;
      } else {
        sum += (float)-0.15370646;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59564.867)) {
        sum += (float)0.34384161;
      } else {
        sum += (float)-0.32313156;
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].fvalue < -1047.5161)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 3.5002858e+08)) {
        sum += (float)-0.33586144;
      } else {
        sum += (float)-0.071102045;
      }
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 1.5269494)) {
        sum += (float)-0.1767121;
      } else {
        sum += (float)0.31210861;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.69872385)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4758.4824)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.65684342)) {
        sum += (float)-0.3311637;
      } else {
        sum += (float)-0.19661671;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59305.156)) {
        sum += (float)0.31101185;
      } else {
        sum += (float)-0.32291794;
      }
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].fvalue < 0.89083785)) {
      if (!(data[9].missing != -1) || (data[9].fvalue < 0.394921)) {
        sum += (float)0.18391602;
      } else {
        sum += (float)-0.28533006;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < -803.02026)) {
        sum += (float)-0.29677698;
      } else {
        sum += (float)0.30370519;
      }
    }
  }
  if (!(data[5].missing != -1) || (data[5].fvalue < 0.46926904)) {
    if (!(data[18].missing != -1) || (data[18].fvalue < 8.1621876)) {
      if (!(data[2].missing != -1) || (data[2].fvalue < 4925.0581)) {
        sum += (float)-0.31589884;
      } else {
        sum += (float)-0.16071668;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.68672782)) {
        sum += (float)-0.23300749;
      } else {
        sum += (float)0.42248952;
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < -1.0498841e+09)) {
      sum += (float)-0.32960334;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 3.3196869)) {
        sum += (float)-0.034549855;
      } else {
        sum += (float)0.28222418;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.85853732)) {
    if (!(data[4].missing != -1) || (data[4].fvalue < 0.65684342)) {
      if (!(data[2].missing != -1) || (data[2].fvalue < 4758.4824)) {
        sum += (float)-0.31170842;
      } else {
        sum += (float)-0.089591302;
      }
    } else {
      if (!(data[9].missing != -1) || (data[9].fvalue < 0.3314983)) {
        sum += (float)0.10385957;
      } else {
        sum += (float)-0.22780795;
      }
    }
  } else {
    if (!(data[2].missing != -1) || (data[2].fvalue < 70881.047)) {
      if (!(data[12].missing != -1) || (data[12].fvalue < -1.0671533e+09)) {
        sum += (float)-0.28465292;
      } else {
        sum += (float)0.24885871;
      }
    } else {
      sum += (float)-0.81269598;
    }
  }
  if (!(data[5].missing != -1) || (data[5].fvalue < 0.46926904)) {
    if (!(data[18].missing != -1) || (data[18].fvalue < 8.1621876)) {
      if (!(data[2].missing != -1) || (data[2].fvalue < 4925.0581)) {
        sum += (float)-0.2963407;
      } else {
        sum += (float)-0.10353287;
      }
    } else {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.50769079)) {
        sum += (float)-0.24014816;
      } else {
        sum += (float)0.27119815;
      }
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].fvalue < 0.90074241)) {
      if (!(data[8].missing != -1) || (data[8].fvalue < 0.49903381)) {
        sum += (float)0.15236431;
      } else {
        sum += (float)-0.25773561;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 70885.594)) {
        sum += (float)0.25334907;
      } else {
        sum += (float)-0.48950523;
      }
    }
  }
  if (!(data[18].missing != -1) || (data[18].fvalue < 3.3240051)) {
    if (!(data[8].missing != -1) || (data[8].fvalue < 0.70105916)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.88549745)) {
        sum += (float)-0.22397958;
      } else {
        sum += (float)0.24316837;
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].fvalue < 44.914528)) {
        sum += (float)-0.17448136;
      } else {
        sum += (float)-1.2940134;
      }
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < -1.0498841e+09)) {
      sum += (float)-0.31276068;
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59669.48)) {
        sum += (float)0.24911346;
      } else {
        sum += (float)-0.24247791;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.65684342)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4758.4824)) {
      if (!(data[4].missing != -1) || (data[4].fvalue < 0.51535845)) {
        sum += (float)-0.30554113;
      } else {
        sum += (float)-0.21956736;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59305.156)) {
        sum += (float)0.29833719;
      } else {
        sum += (float)-0.28850073;
      }
    }
  } else {
    if (!(data[18].missing != -1) || (data[18].fvalue < 4.3305969)) {
      if (!(data[12].missing != -1) || (data[12].fvalue < 1.0241931e+10)) {
        sum += (float)0.20840149;
      } else {
        sum += (float)-0.32391778;
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < -1.0613848e+09)) {
        sum += (float)-0.29752645;
      } else {
        sum += (float)0.23541631;
      }
    }
  }
  if (!(data[18].missing != -1) || (data[18].fvalue < 1.2284832)) {
    if (!(data[18].missing != -1) || (data[18].fvalue < 1.1125336)) {
      sum += (float)-0.31634015;
    } else {
      if (!(data[10].missing != -1) || (data[10].fvalue < -0.05758822)) {
        sum += (float)0.10593455;
      } else {
        sum += (float)-0.26687422;
      }
    }
  } else {
    if (!(data[6].missing != -1) || (data[6].fvalue < 0.10096021)) {
      if (!(data[18].missing != -1) || (data[18].fvalue < 8.5460815)) {
        sum += (float)-0.28455794;
      } else {
        sum += (float)0.040507231;
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].fvalue < -0.050618716)) {
        sum += (float)0.32578126;
      } else {
        sum += (float)0.039202936;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.6175673)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4810.1025)) {
      if (!(data[18].missing != -1) || (data[18].fvalue < 8.5460815)) {
        sum += (float)-0.29021406;
      } else {
        sum += (float)-0.038221207;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59305.156)) {
        sum += (float)0.27125609;
      } else {
        sum += (float)-0.27295437;
      }
    }
  } else {
    if (!(data[18].missing != -1) || (data[18].fvalue < 3.8535156)) {
      if (!(data[8].missing != -1) || (data[8].fvalue < 0.5135138)) {
        sum += (float)0.091464922;
      } else {
        sum += (float)-0.42227253;
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < -1.0587235e+09)) {
        sum += (float)-0.29169145;
      } else {
        sum += (float)0.18838297;
      }
    }
  }
  if (!(data[18].missing != -1) || (data[18].fvalue < 1.2284832)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < -1347831.8)) {
      sum += (float)-0.06886626;
    } else {
      sum += (float)-0.30665386;
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].fvalue < -1045.9156)) {
      sum += (float)-0.2948994;
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < 9.2578601e+09)) {
        sum += (float)0.27165967;
      } else {
        sum += (float)-0.013908476;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.90074241)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < 4753.5029)) {
      if (!(data[11].missing != -1) || (data[11].fvalue < 0.2823121)) {
        sum += (float)-0.077398494;
      } else {
        sum += (float)-0.387808;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 59564.867)) {
        sum += (float)0.31496689;
      } else {
        sum += (float)-0.30879679;
      }
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].fvalue < 0.78840876)) {
      if (!(data[2].missing != -1) || (data[2].fvalue < 69956.898)) {
        sum += (float)0.2510463;
      } else {
        sum += (float)-0.33285129;
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < 1.484356e+11)) {
        sum += (float)-0.47818184;
      } else {
        sum += (float)0.15542139;
      }
    }
  }
  // sum = sum + (float)(0.5);

  return 1.0 / (1 + expf(-sum));
}
