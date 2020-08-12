#include "nonwear_process.h"

#define NWC_REQUEST_PPG (0)
#define NWC_REQUEST_ACC (1)

#define NWC_TIMER_TO_AIR (0)

static uint16_t k_timer_to_air_delay;

/* TODO: 参数配置. */

/* TODO: 切灯处理. */
什么时候不能切 / 切什么灯 void _Request(uint8_t state) {
  if (k_to_air) {
    /* 对空情况下 */
  }
}

/* TODO: 运动状态判断. */
static void _ACCCheck(nwc_bioSignal_t* sig) {
  if ("运动") { /* 运动判断需要封装连续运动次数判断和抬腕亮屏. */
    /* 静止计时器清零. */
    _TimerEnd(STATIC);
    _TimerStart(MOTION);
    if (k_nonwear_state == NWC_DETERM_NONWEAR) {
      /*<< NWC_DETERM_NONWEAR下灯已经关闭，必须置为NWC_NONWEAR. */
      // k_nonwear_state = NWC_NONWEAR;
      // k_switch_led = true;
      _Request(NWC_NONWEAR);
    } else if (k_nonwear_state == NWC_DETERM_WEAR) {
      /*<< 非连续心率且NWC_DETERM_WEAR时，. */
      _Request(NWC_WEAR);
    }
  } else {
    /* 运动计时器清零. */
    _TimerEnd(MOTION);
    _TimerStart(STATIC);
    if (k_nonwear_state == NWC_WEAR) {
      _Request(NWC_WEAR);
    }
  }
}

/* TODO: 对空判断. */
static void _PPGCheck(nwc_bioSignal_t* sig) {
  static uint8_t nonwear_check_init = 0u;

  /* 对空判断阶段. */
  NonwearToAirCheck(sig); /*<< 改写自ToAirCheck. */
  if (k_to_air) {
    if (k_nonwear_state != NWC_NONWEAR) {
      _Request(NWC_REQUEST_PPG);                        /*<< NWC_NONWEAR. */
      _TimerStart(eTIMER_TO_AIR, k_timer_to_air_delay); /*<< 开始对空计时. */
    } else {
      if (_TimerGetStatus(eTIMER_TO_AIR)) {
        _Request(NWC_REQUEST_PPG); /*<< NWC_DETERM_NONWEAR. */
        _TimerEnd(eTIMER_TO_AIR);  /*<< 结束对空计时. */
      }
    }
    return;
  } else {
    if (k_nonwear_state == NWC_NONWEAR) {
      _Request(NWC_REQUEST_PPG); /*<< NWC_WEAR. */
      return;
    }
  }

  /* 活体检测. */
  if (k_nonwear_state == NWC_WEAR) {
    if (!) {
      NonWearCheck(NULL, true);
      _TimerStart("活体", 0);
    }

    uint8_t nonwear_state = NonWearCheck(sig, false);
    if (nonwear_state) {
      _Request(NWC_REQUEST_PPG); /*<< NWC_DETERM_NONWEAR. */
      _TimerStart("活体", 0);
    } else if (_TimerGetStatus("活体")) {
      _Request(NWC_REQUEST_PPG); /*<< NWC_DETERM_WEAR. */
      _TimerStart("活体", 0);
    }

    return;
  }

  return;
}

/* main process */
uint8_t NonWearProcess(uint8_t run_mode, nwc_bioSignal_t* const psignal[],
                       const uint8_t count) {
  /* 参数配置 */
  _ConfigParams(run_mode);

  /* 计时器. */

  /* 运动状态判断/(对空+活体检测) */
  for (uint8_t i = 0; i < count; i++) {
    if (psignal[i]->mtk_sig.sensor_type == check_type) {
      /* 对空+活体检测 */
      _PPGCheck(&psignal[i]);
    }

    if () {
    }
  }

  /* 睡眠状态封装 */
}