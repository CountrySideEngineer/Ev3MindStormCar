/**
 *  @file   CLC_TargetMotorPower.c
 *
 *  @detail �w�肳�ꂽ�ڕW�o�͂ɁA�^�[����𔽉f����B
 */
#include "ev3api.h"
#include "util.h"

#define TARGET_MOTOR_OUTPUT_MAX     (45)
#define TARGET_MOTOR_OUTPUT_MIN     (-45)


/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int target_motor_output_left;
int target_motor_output_right;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int turn_ratio;
extern int target_motor_output;
//extern uint8_t cmd_target_motor_output;
//extern uint8_t cmd_target_motor_direction;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  Reflect the turn ration into calcurated value.
 */
void calc_target_motor_outputLR(void) {

    if (0 < turn_ratio) {
        target_motor_output_right = target_motor_output;
        target_motor_output_left = target_motor_output * (100 + turn_ratio);
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
        target_motor_output_right = target_motor_output * (100 - turn_ratio);
        target_motor_output_right /= 100;
        target_motor_output_left = target_motor_output;

        if ((TARGET_MOTOR_OUTPUT_MAX < target_motor_output_right) ||
        		(target_motor_output_right < TARGET_MOTOR_OUTPUT_MIN))
        {
            if (TARGET_MOTOR_OUTPUT_MAX < target_motor_output_right) {
                target_motor_output_right = TARGET_MOTOR_OUTPUT_MAX;
            } else {
                target_motor_output_right = TARGET_MOTOR_OUTPUT_MIN;
            }
        }
        target_motor_output_left = target_motor_output_right * 100;
        target_motor_output_left /= (100 - turn_ratio);
    } else {
        target_motor_output_left = target_motor_output;
        target_motor_output_right = target_motor_output;
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
