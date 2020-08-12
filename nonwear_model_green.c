#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

float PredictGreen(union NonwearEntry* data) {
  double sum = .0;

  if (!(data[11].missing != -1) || (data[11].fvalue < 0.59591961)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 609503)) {
      if (!(data[21].missing != -1) || (data[21].fvalue < 4252.875)) {
        sum += (float)-0.51366907;
      } else {
        sum += (float)0.58016533;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].fvalue < 985.23267)) {
        sum += (float)0.5938741;
      } else {
        sum += (float)0.27966103;
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].fvalue < 0.4140625)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 699114)) {
        sum += (float)-0.5;
      } else {
        sum += (float)0.50869566;
      }
    } else {
      if (!(data[28].missing != -1) || (data[28].fvalue < 1.9416666)) {
        sum += (float)0.16000001;
      } else {
        sum += (float)-0.57881284;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.56924218)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 591387.5)) {
      if (!(data[25].missing != -1) || (data[25].fvalue < 1159.1919)) {
        sum += (float)-0.42655432;
      } else {
        sum += (float)0.44067323;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].fvalue < 946.91254)) {
        sum += (float)0.4609445;
      } else {
        sum += (float)0.24643193;
      }
    }
  } else {
    if (!(data[14].missing != -1) || (data[14].fvalue < 0.3828125)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 534810)) {
        sum += (float)-0.34714043;
      } else {
        sum += (float)0.45584187;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 0.56762564)) {
        sum += (float)0.40474775;
      } else {
        sum += (float)-0.44293073;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.66047949)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 577594)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < 2955.5)) {
        sum += (float)-0.38498652;
      } else {
        sum += (float)0.40052781;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].fvalue < 985.23267)) {
        sum += (float)0.39748242;
      } else {
        sum += (float)0.12986763;
      }
    }
  } else {
    if (!(data[30].missing != -1) || (data[30].fvalue < 1.1742424)) {
      if (!(data[26].missing != -1) || (data[26].fvalue < 48.579857)) {
        sum += (float)-0.14200418;
      } else {
        sum += (float)0.47975817;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 0.57122195)) {
        sum += (float)0.3291012;
      } else {
        sum += (float)-0.38894102;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.5504387)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 534803.5)) {
      if (!(data[8].missing != -1) || (data[8].fvalue < 85727.57)) {
        sum += (float)-0.33053213;
      } else {
        sum += (float)0.36131895;
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < 0.42450881)) {
        sum += (float)0.35980576;
      } else {
        sum += (float)0.030618235;
      }
    }
  } else {
    if (!(data[31].missing != -1) || (data[31].fvalue < 2.0444665)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 692551.5)) {
        sum += (float)-0.2924898;
      } else {
        sum += (float)0.37742367;
      }
    } else {
      if (!(data[11].missing != -1) || (data[11].fvalue < 0.78993535)) {
        sum += (float)-0.15291473;
      } else {
        sum += (float)-0.35678816;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.51792789)) {
    if (!(data[30].missing != -1) || (data[30].fvalue < 2.9545455)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 519911.5)) {
        sum += (float)0.033513531;
      } else {
        sum += (float)0.34345362;
      }
    } else {
      if (!(data[2].missing != -1) || (data[2].fvalue < 0.72090113)) {
        sum += (float)0.27920702;
      } else {
        sum += (float)-0.30808628;
      }
    }
  } else {
    if (!(data[28].missing != -1) || (data[28].fvalue < 2.6899314)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 608498.5)) {
        sum += (float)-0.33040327;
      } else {
        sum += (float)0.40943462;
      }
    } else {
      if (!(data[21].missing != -1) || (data[21].fvalue < 6570.5322)) {
        sum += (float)-0.32691836;
      } else {
        sum += (float)-0.012132867;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.69747269)) {
    if (!(data[11].missing != -1) || (data[11].fvalue < 0.44595492)) {
      if (!(data[30].missing != -1) || (data[30].fvalue < 2.4772727)) {
        sum += (float)0.32867017;
      } else {
        sum += (float)0.17512374;
      }
    } else {
      if (!(data[28].missing != -1) || (data[28].fvalue < 3.808877)) {
        sum += (float)0.2793583;
      } else {
        sum += (float)-0.26544383;
      }
    }
  } else {
    if (!(data[30].missing != -1) || (data[30].fvalue < 1.5419581)) {
      if (!(data[21].missing != -1) || (data[21].fvalue < 133.54193)) {
        sum += (float)-0.094866402;
      } else {
        sum += (float)0.59667253;
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].fvalue < 1101076.6)) {
        sum += (float)-0.31136793;
      } else {
        sum += (float)0.52577883;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.7776829)) {
    if (!(data[12].missing != -1) || (data[12].fvalue < 0.26089779)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 577901.5)) {
        sum += (float)0.016841814;
      } else {
        sum += (float)0.30990717;
      }
    } else {
      if (!(data[34].missing != -1) || (data[34].fvalue < 3.4045455)) {
        sum += (float)0.22598661;
      } else {
        sum += (float)-0.2801348;
      }
    }
  } else {
    if (!(data[30].missing != -1) || (data[30].fvalue < 1.1742424)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 530872.5)) {
        sum += (float)-0.26137826;
      } else {
        sum += (float)0.22799388;
      }
    } else {
      if (!(data[20].missing != -1) || (data[20].fvalue < 185089.31)) {
        sum += (float)-0.30027169;
      } else {
        sum += (float)0.54032505;
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].fvalue < 0.77346539)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 552187)) {
      if (!(data[17].missing != -1) || (data[17].fvalue < 46.25)) {
        sum += (float)-0.33250466;
      } else {
        sum += (float)0.26857719;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].fvalue < 0.37950718)) {
        sum += (float)0.3214072;
      } else {
        sum += (float)0.19417454;
      }
    }
  } else {
    if (!(data[29].missing != -1) || (data[29].fvalue < 3.5472493)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 706975)) {
        sum += (float)-0.31774521;
      } else {
        sum += (float)0.36130118;
      }
    } else {
      if (!(data[21].missing != -1) || (data[21].fvalue < 6570.5322)) {
        sum += (float)-0.29426146;
      } else {
        sum += (float)0.11544066;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.78993535)) {
    if (!(data[8].missing != -1) || (data[8].fvalue < 287.74597)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 594416)) {
        sum += (float)-0.22234121;
      } else {
        sum += (float)0.30356166;
      }
    } else {
      if (!(data[22].missing != -1) || (data[22].fvalue < 319.05045)) {
        sum += (float)-0.17548178;
      } else {
        sum += (float)0.30640227;
      }
    }
  } else {
    if (!(data[33].missing != -1) || (data[33].fvalue < 2.7171428)) {
      if (!(data[19].missing != -1) || (data[19].fvalue < 60.233189)) {
        sum += (float)-0.062787928;
      } else {
        sum += (float)0.60320371;
      }
    } else {
      if (!(data[30].missing != -1) || (data[30].fvalue < 1.5227273)) {
        sum += (float)0.0082036294;
      } else {
        sum += (float)-0.28375703;
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].fvalue < 0.83105969)) {
    if (!(data[18].missing != -1) || (data[18].fvalue < 10.93424)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 534544)) {
        sum += (float)-0.22723413;
      } else {
        sum += (float)0.30345798;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].fvalue < 398085.44)) {
        sum += (float)-0.025094006;
      } else {
        sum += (float)0.47370201;
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].fvalue < 1124597.5)) {
      if (!(data[32].missing != -1) || (data[32].fvalue < 0.94444442)) {
        sum += (float)0.12999244;
      } else {
        sum += (float)-0.27379552;
      }
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < 272.5)) {
        sum += (float)0.32147741;
      } else {
        sum += (float)-0.21716203;
      }
    }
  }
  if (!(data[2].missing != -1) || (data[2].fvalue < 0.71163738)) {
    if (!(data[18].missing != -1) || (data[18].fvalue < 22.030865)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 559711)) {
        sum += (float)-0.093112253;
      } else {
        sum += (float)0.30615616;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].fvalue < 0.36662775)) {
        sum += (float)0.24161656;
      } else {
        sum += (float)-0.19324906;
      }
    }
  } else {
    if (!(data[34].missing != -1) || (data[34].fvalue < 3.1277175)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 739818.5)) {
        sum += (float)-0.29151565;
      } else {
        sum += (float)0.35894269;
      }
    } else {
      if (!(data[21].missing != -1) || (data[21].fvalue < 6570.5322)) {
        sum += (float)-0.24218689;
      } else {
        sum += (float)0.17717667;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 0.89657676)) {
    if (!(data[26].missing != -1) || (data[26].fvalue < 9.5901356)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 585725.5)) {
        sum += (float)-0.25800067;
      } else {
        sum += (float)0.32061732;
      }
    } else {
      if (!(data[25].missing != -1) || (data[25].fvalue < 334.5744)) {
        sum += (float)-0.11145727;
      } else {
        sum += (float)0.30515438;
      }
    }
  } else {
    if (!(data[31].missing != -1) || (data[31].fvalue < 3.1207728)) {
      if (!(data[22].missing != -1) || (data[22].fvalue < 30.076462)) {
        sum += (float)-0.19575964;
      } else {
        sum += (float)0.46070457;
      }
    } else {
      if (!(data[0].missing != -1) || (data[0].fvalue < -1.4235799)) {
        sum += (float)-0.00074888574;
      } else {
        sum += (float)-0.27415767;
      }
    }
  }
  if (!(data[31].missing != -1) || (data[31].fvalue < 3.4045455)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 591961.5)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < 1926)) {
        sum += (float)-0.28022495;
      } else {
        sum += (float)0.24522971;
      }
    } else {
      if (!(data[26].missing != -1) || (data[26].fvalue < 14.94809)) {
        sum += (float)0.30084831;
      } else {
        sum += (float)0.10643854;
      }
    }
  } else {
    if (!(data[21].missing != -1) || (data[21].fvalue < 585.02271)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 1661439)) {
        sum += (float)-0.28098851;
      } else {
        sum += (float)0.11168983;
      }
    } else {
      if (!(data[24].missing != -1) || (data[24].fvalue < 466.36884)) {
        sum += (float)0.30849364;
      } else {
        sum += (float)-0.22794488;
      }
    }
  }
  if (!(data[14].missing != -1) || (data[14].fvalue < 0.4140625)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 606544)) {
      sum += (float)-0.20286269;
    } else {
      if (!(data[23].missing != -1) || (data[23].fvalue < 5.8227777)) {
        sum += (float)0.28871986;
      } else {
        sum += (float)0.002095382;
      }
    }
  } else {
    if (!(data[11].missing != -1) || (data[11].fvalue < 1.3109326)) {
      if (!(data[22].missing != -1) || (data[22].fvalue < 233.27467)) {
        sum += (float)-0.13111772;
      } else {
        sum += (float)0.21756545;
      }
    } else {
      if (!(data[15].missing != -1) || (data[15].fvalue < 789706)) {
        sum += (float)-0.29435614;
      } else {
        sum += (float)-0.017070688;
      }
    }
  }
  if (!(data[28].missing != -1) || (data[28].fvalue < 3.7958333)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 536630.5)) {
      sum += (float)-0.2749607;
    } else {
      if (!(data[7].missing != -1) || (data[7].fvalue < 0.44149041)) {
        sum += (float)0.14672552;
      } else {
        sum += (float)0.33315906;
      }
    }
  } else {
    if (!(data[3].missing != -1) || (data[3].fvalue < 0.1349465)) {
      if (!(data[34].missing != -1) || (data[34].fvalue < 34.961037)) {
        sum += (float)0.29954025;
      } else {
        sum += (float)-0.19961514;
      }
    } else {
      if (!(data[8].missing != -1) || (data[8].fvalue < 162945.53)) {
        sum += (float)-0.24173251;
      } else {
        sum += (float)0.15953971;
      }
    }
  }
  if (!(data[34].missing != -1) || (data[34].fvalue < 3.3405795)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 606544)) {
      sum += (float)-0.23586513;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 51.649796)) {
        sum += (float)0.24672116;
      } else {
        sum += (float)0.70055461;
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].fvalue < 2091852.5)) {
      if (!(data[21].missing != -1) || (data[21].fvalue < 413.27307)) {
        sum += (float)-0.20879345;
      } else {
        sum += (float)0.031274535;
      }
    } else {
      sum += (float)0.33438849;
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 1.3109326)) {
    if (!(data[8].missing != -1) || (data[8].fvalue < 59592.781)) {
      if (!(data[8].missing != -1) || (data[8].fvalue < 270.39441)) {
        sum += (float)0.20277815;
      } else {
        sum += (float)-0.083278455;
      }
    } else {
      if (!(data[33].missing != -1) || (data[33].fvalue < 21.002024)) {
        sum += (float)0.57354987;
      } else {
        sum += (float)-0.13504435;
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].fvalue < 789706)) {
      sum += (float)-0.28585503;
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < 989)) {
        sum += (float)-0.16654238;
      } else {
        sum += (float)0.57698309;
      }
    }
  }
  if (!(data[26].missing != -1) || (data[26].fvalue < 6.677083)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 605475)) {
      sum += (float)-0.11372054;
    } else {
      if (!(data[6].missing != -1) || (data[6].fvalue < 0.75171053)) {
        sum += (float)0.24619843;
      } else {
        sum += (float)0.59518933;
      }
    }
  } else {
    if (!(data[27].missing != -1) || (data[27].fvalue < 2.630682)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 531817.5)) {
        sum += (float)-0.22214268;
      } else {
        sum += (float)0.21808842;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].fvalue < 0.13751352)) {
        sum += (float)0.24422203;
      } else {
        sum += (float)-0.13508138;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 1.4475591)) {
    if (!(data[19].missing != -1) || (data[19].fvalue < 1971.9485)) {
      if (!(data[28].missing != -1) || (data[28].fvalue < 4.3660288)) {
        sum += (float)0.12100186;
      } else {
        sum += (float)-0.12557235;
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].fvalue < 0.9296875)) {
        sum += (float)0.46630406;
      } else {
        sum += (float)-0.21402967;
      }
    }
  } else {
    if (!(data[15].missing != -1) || (data[15].fvalue < 818719)) {
      sum += (float)-0.27070963;
    } else {
      if (!(data[30].missing != -1) || (data[30].fvalue < 5.8874998)) {
        sum += (float)0.14918214;
      } else {
        sum += (float)-0.17395824;
      }
    }
  }
  if (!(data[26].missing != -1) || (data[26].fvalue < 10.653334)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 585725.5)) {
      sum += (float)-0.20205271;
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 51.870949)) {
        sum += (float)0.18579608;
      } else {
        sum += (float)0.51962423;
      }
    }
  } else {
    if (!(data[7].missing != -1) || (data[7].fvalue < 0.33142006)) {
      if (!(data[3].missing != -1) || (data[3].fvalue < 0.30202758)) {
        sum += (float)0.18220025;
      } else {
        sum += (float)-0.28101686;
      }
    } else {
      if (!(data[30].missing != -1) || (data[30].fvalue < 1.6833334)) {
        sum += (float)0.26080248;
      } else {
        sum += (float)-0.032752085;
      }
    }
  }
  if (!(data[15].missing != -1) || (data[15].fvalue < 2003938.5)) {
    if (!(data[21].missing != -1) || (data[21].fvalue < 267.8244)) {
      if (!(data[22].missing != -1) || (data[22].fvalue < 19.207796)) {
        sum += (float)0.15313748;
      } else {
        sum += (float)-0.18431777;
      }
    } else {
      if (!(data[14].missing != -1) || (data[14].fvalue < 0.8828125)) {
        sum += (float)0.21094973;
      } else {
        sum += (float)-0.16580996;
      }
    }
  } else {
    if (!(data[30].missing != -1) || (data[30].fvalue < 3.45)) {
      if (!(data[34].missing != -1) || (data[34].fvalue < 5.3923078)) {
        sum += (float)0.29888767;
      } else {
        sum += (float)0.084304839;
      }
    } else {
      sum += (float)0.0016014753;
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < -1.3420339)) {
    if (!(data[11].missing != -1) || (data[11].fvalue < 1.3114827)) {
      if (!(data[10].missing != -1) || (data[10].fvalue < 57.603447)) {
        sum += (float)-0.037950326;
      } else {
        sum += (float)0.60772663;
      }
    } else {
      sum += (float)-0.18103953;
    }
  } else {
    if (!(data[17].missing != -1) || (data[17].fvalue < 8.125)) {
      if (!(data[15].missing != -1) || (data[15].fvalue < 797466)) {
        sum += (float)0.031381987;
      } else {
        sum += (float)0.26974973;
      }
    } else {
      if (!(data[7].missing != -1) || (data[7].fvalue < 0.21805128)) {
        sum += (float)-0.22697324;
      } else {
        sum += (float)0.0057372767;
      }
    }
  }
  if (!(data[4].missing != -1) || (data[4].fvalue < 0.084131792)) {
    if (!(data[15].missing != -1) || (data[15].fvalue < 537315.5)) {
      sum += (float)-0.01886116;
    } else {
      sum += (float)0.27815059;
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].fvalue < 0.50992429)) {
      if (!(data[18].missing != -1) || (data[18].fvalue < 8.1306686)) {
        sum += (float)0.10955498;
      } else {
        sum += (float)-0.25704116;
      }
    } else {
      if (!(data[3].missing != -1) || (data[3].fvalue < 0.74870342)) {
        sum += (float)0.24753182;
      } else {
        sum += (float)-0.002299838;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < 1.3457468)) {
    if (!(data[9].missing != -1) || (data[9].fvalue < 33.745872)) {
      if (!(data[8].missing != -1) || (data[8].fvalue < 834.33728)) {
        sum += (float)0.21713458;
      } else {
        sum += (float)-0.20300454;
      }
    } else {
      if (!(data[10].missing != -1) || (data[10].fvalue < 116.61853)) {
        sum += (float)-0.22160557;
      } else {
        sum += (float)0.0027305624;
      }
    }
  } else {
    if (!(data[5].missing != -1) || (data[5].fvalue < 0.43484819)) {
      if (!(data[32].missing != -1) || (data[32].fvalue < 2.5833335)) {
        sum += (float)0.20851541;
      } else {
        sum += (float)-0.14329731;
      }
    } else {
      if (!(data[18].missing != -1) || (data[18].fvalue < 51.618546)) {
        sum += (float)0.15908578;
      } else {
        sum += (float)0.53031963;
      }
    }
  }
  if (!(data[11].missing != -1) || (data[11].fvalue < 1.4475591)) {
    if (!(data[13].missing != -1) || (data[13].fvalue < -0.352027)) {
      if (!(data[23].missing != -1) || (data[23].fvalue < 62.847221)) {
        sum += (float)0.028121425;
      } else {
        sum += (float)1.0110644;
      }
    } else {
      if (!(data[12].missing != -1) || (data[12].fvalue < 0.15793695)) {
        sum += (float)0.089111902;
      } else {
        sum += (float)-0.1180063;
      }
    }
  } else {
    if (!(data[22].missing != -1) || (data[22].fvalue < 3289.5513)) {
      sum += (float)-0.27040622;
    } else {
      if (!(data[29].missing != -1) || (data[29].fvalue < 71.002716)) {
        sum += (float)0.28765559;
      } else {
        sum += (float)-0.18839213;
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}