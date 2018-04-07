/**
 *  @file   CLC_TargetMotorPower.c
 *
 *  @detail ?øΩw?øΩËÇ≥?øΩÍÇΩ?øΩ⁄ïW?øΩo?øΩÕÇ…ÅA?øΩ^?øΩ[?øΩ?øΩ?øΩ?øΩ?Ωâf?øΩ?øΩ?øΩ?øΩB
 */
#include "ev3api.h"
#include "util.h"

#define TARGET_MOTOR_OUTPUT_MAX     (45)
#define TARGET_MOTOR_OUTPUT_MIN     (-45)


/*****************************************************************************/
/*                                  ?øΩœêÔøΩ?øΩ?øΩ`                                 */
/*****************************************************************************/
int target_motor_output_left;
int target_motor_output_right;

/*****************************************************************************/
/*                                  ?øΩ√ìI?øΩœêÔøΩ                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  ?øΩËêîÔøΩ?øΩ`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                ?øΩO?øΩ?øΩ?øΩœêÔøΩ?øΩÈåæ                               */
/*****************************************************************************/
extern int turn_ratio;
extern int target_motor_output;

/*****************************************************************************/
/*                                ?øΩO?øΩ?øΩ?øΩËêîÔøΩ?øΩ`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  ?øΩO?øΩ?øΩ?øΩ÷êÔøΩ                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  ?øΩ÷êÔøΩ?øΩ?øΩ?øΩ?øΩ                                 */
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
