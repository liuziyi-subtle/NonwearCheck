#include <math.h>
#include <stdlib.h>

#include "nonwear_model.h"

int8_t replace = 1;

float PredictGreenAir(union NonwearEntry* data) {
  float sum = 0.0f;
  // unsigned int tmp;
  if (!(data[0].missing != -replace) || (data[0].fvalue < 0.67209923f)) {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < 1231.5667f)) {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -4259.7231f)) {
        sum += 0.59916496f;
      } else {
        sum += 0.46233502f;
      }
    } else {
      sum += -0.57837844f;
    }
  } else {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < -4249.7539f)) {
      sum += 0.59220779f;
    } else {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -2067.0735f)) {
        sum += -0.54250222f;
      } else {
        sum += -0.59670961f;
      }
    }
  }
  if (!(data[0].missing != -replace) || (data[0].fvalue < 0.67209923f)) {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < 1231.5667f)) {
      if (!(data[0].missing != -replace) || (data[0].fvalue < 0.47561854f)) {
        sum += 0.45002547f;
      } else {
        sum += 0.23963501f;
      }
    } else {
      sum += -0.44997427f;
    }
  } else {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < -4249.7539f)) {
      sum += 0.45934191f;
    } else {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -2402.9102f)) {
        sum += -0.40951529f;
      } else {
        sum += -0.46085042f;
      }
    }
  }
  if (!(data[0].missing != -replace) || (data[0].fvalue < 0.65745008f)) {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < 1231.5667f)) {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -4259.7231f)) {
        sum += 0.40637055f;
      } else {
        sum += 0.26543957f;
      }
    } else {
      sum += -0.38692912f;
    }
  } else {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < -4249.7539f)) {
      sum += 0.40038767f;
    } else {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -2067.0735f)) {
        sum += -0.34640157f;
      } else {
        sum += -0.40067038f;
      }
    }
  }
  if (!(data[0].missing != -replace) || (data[0].fvalue < 0.61521512f)) {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < 1231.5667f)) {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -4260.7505f)) {
        sum += 0.3702296f;
      } else {
        sum += 0.23560536f;
      }
    } else {
      sum += -0.34440771f;
    }
  } else {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < -4249.7539f)) {
      sum += 0.36747366f;
    } else {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -2067.0735f)) {
        sum += -0.30749041f;
      } else {
        sum += -0.36446184f;
      }
    }
  }
  if (!(data[0].missing != -replace) || (data[0].fvalue < 0.53856802f)) {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < 1575.5f)) {
      if (!(data[replace].missing != -replace) ||
          (data[replace].fvalue < -4258.0234f)) {
        sum += 0.34766379f;
      } else {
        sum += 0.22812618f;
      }
    } else {
      sum += -0.30775887f;
    }
  } else {
    if (!(data[replace].missing != -replace) ||
        (data[replace].fvalue < -4249.7539f)) {
      sum += 0.34680972f;
    } else {
      if (!(data[0].missing != -replace) || (data[0].fvalue < 0.62959903f)) {
        sum += -0.59450001f;
      } else {
        sum += -0.3210547f;
      }
    }
  }

  return 1.0f / (1 + expf(-sum));
}