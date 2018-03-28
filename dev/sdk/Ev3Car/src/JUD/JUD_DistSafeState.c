/**
 *  judge_dist_safe_state
 *
 *  Judge whether MyCar has safe distance between distance and obstacle in
 *  front.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int8_t distance_safe_state;
int8_t distance_safe_state_prev;
bool_t distance_safe_state_change;

/*****************************************************************************/
/*                               �ÓI�ϐ���`                                */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int16_t distance_average_value;

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
const int8_t CAR_SAFE_STATE_SAFE = 0;
const int8_t CAR_SAFE_STATE_ATTN = 1;
const int8_t CAR_SAFE_STATE_DANG = 2;
const int8_t CAR_SAFE_STATE_STOP = 3;

/*****************************************************************************/
/*                               �ÓI�萔��`                                */
/*****************************************************************************/
static const int16_t CAR_SAFE_STATE_SAFE_ATTN_BORDER = 45;  //���S���x��
static const int16_t CAR_SAFE_STATE_ATTN_DANG_BORDER = 35;  //�x�����댯
static const int16_t CAR_SAFE_STATE_DANG_STOP_BORDER = 25;  //�댯����~
static const int16_t CAR_SAFE_STATE_ATTN_SAFE_BORDER = 40;  //�x�������S
static const int16_t CAR_SAFE_STATE_DANG_ATTN_BORDER = 30;  //�댯���x��
static const int16_t CAR_SAFE_STATE_STOP_DANG_BORDER = 20;  //��~���댯

/*****************************************************************************/
/*                                  �֐�����                                 */
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
    if (distance_safe_state == distance_safe_state_prev) {
        distance_safe_state_change = false;
    } else {
        distance_safe_state_change = true;
    }

    distance_safe_state_prev = distance_safe_state;
}

/**
 *  @brief  Initialize the safe state.
 */
void init_dist_safe(void) {
    distance_safe_state = CAR_SAFE_STATE_SAFE;
    distance_safe_state_prev = CAR_SAFE_STATE_SAFE;
    distance_safe_state_change = false;

}
