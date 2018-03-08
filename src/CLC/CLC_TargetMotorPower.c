/**
 *  @file   CLC_TargetMotorPower.c
 *
 *  @detail 指定された目標出力に、ターン比を反映する。
 */
#include "ev3api.h"
#include "util.h"

#define TARGET_MOTOR_OUTPUT_MAX     (45)
#define TARGET_MOTOR_OUTPUT_MIN     (-45)


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int target_motor_output_left;
int target_motor_output_right;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int turn_ratio;
extern uint8_t cmd_target_motor_output;
extern uint8_t cmd_target_motor_direction;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Reflect the turn ration into calcurated value.
 */
void calc_target_motor_outputLR(void) {

    int16_t target_motor_output_tmp;

    target_motor_output_tmp = (int16_t)(cmd_target_motor_output);
    if (0x00 == cmd_target_motor_direction) {
        /**
         * Commmand data means the motor rotate in reverse direction.
         */
        target_motor_output_tmp *= (-1);
    }

    if (0 < turn_ratio) {
        target_motor_output_right = target_motor_output_tmp;
        target_motor_output_left = target_motor_output_tmp * (100 + turn_ratio);
        target_motor_output_left /= 100;

        if ((TARGET_MOTOR_OUTPUT_MAX < target_motor_output_left) || 
            (target_motor_output_left < TARGET_MOTOR_OUTPUT_MIN))
        {
            if (TARGET_MOTOR_OUTPUT_MAX < target_motor_output_left) {
                target_motor_output_left = TARGET_MOTOR_OUTPUT_MAX;
            } else {
                target_motor_output_left = TARGET_MOTOR_OUTPUT_MIN;
            }
            target_motor_output_right = target_motor_output_left * 100;
            target_motor_output_right /= (100 + turn_ratio);
        }
    } else if (turn_ratio < 0) {
        target_motor_output_right = target_motor_output_tmp * (100 - turn_ratio);
        target_motor_output_right /= 100;
        target_motor_output_left = target_motor_output_tmp;

        if (TARGET_MOTOR_OUTPUT_MAX < target_motor_output_right) {
            target_motor_output_right = TARGET_MOTOR_OUTPUT_MAX;
        } else {
            target_motor_output_right = TARGET_MOTOR_OUTPUT_MIN;
        }
        target_motor_output_left = target_motor_output_right * 100;
        target_motor_output_left /= (100 + turn_ratio);
    } else {
        target_motor_output_left = target_motor_output_tmp;
        target_motor_output_right = target_motor_output_tmp;
    }
}

/**
 *  @brief  Initialize target motor output.
 */
void init_target_motor_outputLR(void)
{
    target_motor_output_left = 0;
    target_motor_output_right = 0;
}
