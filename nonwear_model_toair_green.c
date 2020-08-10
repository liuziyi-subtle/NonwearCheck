#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

float PredictGreenAir(union NonwearEntry* data) {
  float sum = 0.0f;
  // unsigned int tmp;
  if (!(data[0].missing != -1) || (data[0].fvalue < 0.67209923)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < 1231.5667)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < -4259.7231)) {
        sum += (float)0.59916496;
      } else {
        sum += (float)0.46233502;
      }
    } else {
      sum += (float)-0.57837844;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].fvalue < -4249.7539)) {
      sum += (float)0.59220779;
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < -2067.0735)) {
        sum += (float)-0.54250222;
      } else {
        sum += (float)-0.59670961;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < 0.67209923)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < 1231.5667)) {
      if (!(data[0].missing != -1) || (data[0].fvalue < 0.47561854)) {
        sum += (float)0.45002547;
      } else {
        sum += (float)0.23963501;
      }
    } else {
      sum += (float)-0.44997427;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].fvalue < -4249.7539)) {
      sum += (float)0.45934191;
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < -2402.9102)) {
        sum += (float)-0.40951529;
      } else {
        sum += (float)-0.46085042;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < 0.65745008)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < 1231.5667)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < -4259.7231)) {
        sum += (float)0.40637055;
      } else {
        sum += (float)0.26543957;
      }
    } else {
      sum += (float)-0.38692912;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].fvalue < -4249.7539)) {
      sum += (float)0.40038767;
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < -2067.0735)) {
        sum += (float)-0.34640157;
      } else {
        sum += (float)-0.40067038;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < 0.61521512)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < 1231.5667)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < -4260.7505)) {
        sum += (float)0.3702296;
      } else {
        sum += (float)0.23560536;
      }
    } else {
      sum += (float)-0.34440771;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].fvalue < -4249.7539)) {
      sum += (float)0.36747366;
    } else {
      if (!(data[1].missing != -1) || (data[1].fvalue < -2067.0735)) {
        sum += (float)-0.30749041;
      } else {
        sum += (float)-0.36446184;
      }
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < 0.53856802)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < 1575.5)) {
      if (!(data[1].missing != -1) || (data[1].fvalue < -4258.0234)) {
        sum += (float)0.34766379;
      } else {
        sum += (float)0.22812618;
      }
    } else {
      sum += (float)-0.30775887;
    }
  } else {
    if (!(data[1].missing != -1) || (data[1].fvalue < -4249.7539)) {
      sum += (float)0.34680972;
    } else {
      if (!(data[0].missing != -1) || (data[0].fvalue < 0.62959903)) {
        sum += (float)-0.59450001;
      } else {
        sum += (float)-0.3210547;
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}