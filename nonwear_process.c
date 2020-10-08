#include "nonwear_process.h"

#define NWC_REQUEST_PPG (0)
#define NWC_REQUEST_ACC (1)

#define NWC_TIMER_TO_AIR (0)
#define NWC_NONWEAR_CHECK_DELAY (3) /*<< 3min. */

static uint16_t k_timer_to_air_delay;

/* 当前佩戴状态 - 当前测量模式 - 对空状态 - 对空计时器 - 非空 - 静止计时器 -
 * 运动计时器
 * - 活体检测计时器 */
/* 1. 连续测量模式: NWC_WEAR + 对空 + 对空计时0s + 非空计时0s + xx静止计时 +
 * xx运动计时 + xx活体计时 -> 首次对空切红外 -> NWC_NONWEAR.
 * 2. 连续测量模式: NWC_DETERM_WEAR + 对空 + 对空计时0s + 非空计时0s +
 * xx静止计时 + xx运动计时
 * + xx活体计时 -> 首次对空切红外 -> NWC_NONWEAR.
 * + 任何活体计时 -> 首次对空切红外 -> NWC_NONWEAR.
 * 3. 连续测量模式: NWC_NONWEAR + 对空 + 对空计时10s + 任何静止计时 +
 * 任何运动计时
 * + 任何活体计时 -> 对空延时关所有灯 -> NWC_DETERM_NONWEAR.
 * 4. 连续测量模式: NWC_NONWEAR + 非对空 + 非对空计时0s + 任何静止计时 +
 * 任何运动计时
 * + 任何活体计时
 */

struct decision_node decision_nodes = [

  {}, /*<< NWC_ONWEAR -> 1. 连续测量模式 - 对空 - 对空计时0 - 任何静止时间 -
         任何运动时间 - 任何活体时间 -> (首次对空)切红外 */
  {}, /*<< NWC_ONWEAR -> 1. 连续测量模式 - 对空 - 对空计时10s - 任何静止时间 -
         任何运动时间 - 任何活体时间 -> (对空延时)关所有灯 */
  {}, /*<< NWC_DETERM_ONWEAR -> 2. - 任何测量模式 - 对空- 对空计时0 -
         任何静止时间 - 任何运动时间 - 任何活体时间 -> (首次对空)切红外 */
  {},
];

struct decision_node {
  uint8_t
      status[NUM_SUPPORT]; /*<< 支持的可切灯状态: 当前佩戴状态, 模式，运动...*/
  switch_led_t sl;           /*<< 需要切换到的灯. */
  switch_nonwear_state_t sn; /*<< 需要切换到的佩戴状态. */
};

/* TODO: 参数配置. */

/* TODO: 切灯处理. */
什么时候不能切 / 切什么灯 void _Request(uint8_t state) {
  if (k_to_air) {
    /* 对空情况下 */
  }
}

/* 切灯处理&状态转换处理. */

/* TODO: 运动状态判断. */
static void _ACCCheck(nwc_bioSignal_t* sig) {
  if ("运动") { /* 运动判断需要封装连续运动次数判断和抬腕亮屏. */
    /* 静止计时器清零. */
    _TimerEnd(STATIC);
    _TimerStart(MOTION);
    if (k_nonwear_state == NWC_DETERM_NONWEAR) {
      /*<< NWC_DETERM_NONWEAR下灯已经关闭，必须置为NWC_NONWEAR. */
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
  /* 对空判断阶段. */
  NonwearToAirCheck(sig); /*<< 改写自ToAirCheck. */
  if (k_to_air) {
    if (timer_to_air->u16DelayMs == 0) {
      timer_to_air = _TimerStart(eTIMER_TO_AIR); /*<< 开始对空计时. */
      _TimerEnd(timer_not_to_air);
    }
    _Request(NWC_REQUEST_PPG);
    return;
  } else {
    if (timer_not_to_air->u16DelayMs == 0) {
      timer_not_to_air = _TimerStart(eTIMER_NOT_TO_AIR);
      _TimerEnd(timer_to_air);
      return;
    }
    _Request(NWC_REQUEST_PPG); /*<< NWC_WEAR. */
  }

  /* 活体检测. */
  if (k_nonwear_state == NWC_WEAR) {
    /* 模式切换时做各种初始化. */
    if (timer_nonwear_check_timeout->u16DelayMs == 0) {
      NonWearCheck(NULL, true);
      timer_nonwear_check_timeout = _TimerStart(eTIMER_CHECK_TIMEOUT);
    }

    uint8_t nonwear_state = NonWearCheck(sig, false);
    if (nonwear_state > 0) {
      _Request(NWC_REQUEST_PPG); /*<< NWC_DETERM_NONWEAR. */
      _TimerEnd(timer_nonwear_check_timeout);
    } else {
      if (timer_nonwear_check_timeout.u16DelayMs > NWC_NONWEAR_CHECK_DELAY) {
        _Request(NWC_REQUEST_PPG); /*<< NWC_DETERM_WEAR. */
        _TimerEnd(timer_nonwear_check_timeout);
      }
    }
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