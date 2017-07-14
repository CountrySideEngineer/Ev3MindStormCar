/**
 *  judge_dist_safe_state
 *
 *  Judge whether MyCar has safe distance between distance and obstacle in 
 *  front.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int8_t distance_safe_state;
int8_t distance_safe_state_prev;
bool_t distance_safe_state_change;

/*****************************************************************************/
/*                               静的変数定義                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int16_t distance_average_value;

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const int8_t CAR_SAFE_STATE_SAFE = 0;
const int8_t CAR_SAFE_STATE_ATTN = 1;
const int8_t CAR_SAFE_STATE_DANG = 2;
const int8_t CAR_SAFE_STATE_STOP = 3;

/*****************************************************************************/
/*                               静的定数定義                                */
/*****************************************************************************/
static const int16_t CAR_SAFE_STATE_SAFE_ATTN_BORDER = 200;  //安全→警告
static const int16_t CAR_SAFE_STATE_ATTN_SAFE_BORDER = 210;  //警告→安全
static const int16_t CAR_SAFE_STATE_ATTN_DANG_BORDER = 140;  //注意→危険
static const int16_t CAR_SAFE_STATE_DANG_ATTN_BORDER = 150;  //危険→注意
static const int16_t CAR_SAFE_STATE_STOP_DANG_BORDER = 50;   //停止→危険
static const int16_t CAR_SAFE_STATE_DANG_STOP_BORDER = 60;   //危険→停止

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Judge the safe state from distance read from ultrasonic sensor.
 */
void judge_dist_safe(void) {
    int16_t distance_average_value_tmp;
    
    //Latch latest value.
    distance_average_value_tmp = distance_average_value;

    if (CAR_SAFE_STATE_SAFE == distance_safe_state) {
        if (CAR_SAFE_STATE_SAFE_ATTN_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_ATTN;
        }
    } else if (CAR_SAFE_STATE_ATTN == distance_safe_state) {
        if (CAR_SAFE_STATE_ATTN_DANG_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_DANG;
        }
        if (CAR_SAFE_STATE_ATTN_SAFE_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_SAFE;
        }
    } else if (CAR_SAFE_STATE_DANG == distance_safe_state) {
        if (CAR_SAFE_STATE_DANG_STOP_BORDER > distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_STOP;
        }
        if (CAR_SAFE_STATE_DANG_ATTN_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_ATTN;
        }
    } else if (CAR_SAFE_STATE_STOP == distance_safe_state) {
        if (CAR_SAFE_STATE_STOP_DANG_BORDER < distance_average_value_tmp) {
            distance_safe_state = CAR_SAFE_STATE_DANG;
        }
    }
}

/**
 *  @brief  Check the change and udate safe state.
 */
void judge_distance_safe_change(void) {
    int16_t distance_average_value_tmp;
    
    //Latch latest value.
    distance_average_value_tmp = distance_average_value;

    if (distance_average_value_tmp == distance_safe_state_prev) {
        distance_safe_state_change = true;
    } else {
        distance_safe_state_change = false;
    }

    distance_safe_state_prev = distance_average_value_tmp;
}

/**
 *  @brief  Initialize the safe state.
 */
void init_dist_safe(void) {
    distance_safe_state = CAR_SAFE_STATE_SAFE;
    distance_safe_state_prev = CAR_SAFE_STATE_SAFE;
    distance_safe_state_change = false;

}
