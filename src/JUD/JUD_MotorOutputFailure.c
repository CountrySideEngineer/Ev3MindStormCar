/**
 *  JUD_MotorOutputFailure.c
 *
 *  Judge whether the motor oputput is OK or not by difference of current
 *  and target motor output.
 */
#include "ev3api.h"
#include "util.h"
#include <stdlib.h>

/*****************************************************************************/
/*                               gloval varible                              */
/*****************************************************************************/
int8_t motor_failure_left;
int8_t motor_failure_right;
uint8_t motor_failure_left_count;
uint8_t motor_failure_right_count;
uint8_t motor_output_diff_left;
uint8_t motor_output_diff_right;

/*****************************************************************************/
/*                               static variable                             */
/*****************************************************************************/


/*****************************************************************************/
/*                                 constant                                  */
/*****************************************************************************/
const int8_t MOTOR_FAILURE_COUNT = 30;
const int8_t MOTOR_FAILURE_OUTPUT = 3;

/*****************************************************************************/
/*                              External variable                            */
/*****************************************************************************/
extern int left_motor_power_current;
extern int right_motor_power_current;
extern int target_motor_output_left;
extern int target_motor_output_right;

/*****************************************************************************/
/*                              External constant                            */
/*****************************************************************************/


/*****************************************************************************/
/*                               External function                           */
/*****************************************************************************/


/*****************************************************************************/
/*                           Implement of function                           */
/*****************************************************************************/

/**
 * @brief   Judge the motor is in failure or not.
 *          If the difference of motor output of target and current is larger
 *          than a border value, the counter is up. And when it is over the
 *          counter border value, motor is in failure.
 */
void jud_motor_output_failure(void)
{
    //Check left motor failure.
    uint8_t motor_output_diff;
    int motor_output_delta;

    //Check left motor failure.
    motor_output_diff =
        abs(left_motor_power_current - target_motor_output_left);
    motor_output_delta = abs(motor_output_diff_left - motor_output_diff);
    if (motor_output_delta < MOTOR_FAILURE_OUTPUT) {
        motor_failure_left_count = MOTOR_FAILURE_COUNT;
        motor_failure_left = 0;
    } else {
        if (0 < motor_failure_left_count) {
            motor_failure_left_count--;
            if (0 == motor_failure_left_count) {
                motor_failure_left = 1;
            }
        }
    }
    motor_output_diff_left = motor_output_diff;

    //Check right motor failure.
    motor_output_diff =
        abs(right_motor_power_current - target_motor_output_right);
    motor_output_delta = abs(motor_output_diff_right - motor_output_diff);
    if (motor_output_delta < MOTOR_FAILURE_OUTPUT) {
        motor_failure_right_count = MOTOR_FAILURE_COUNT;
        motor_failure_right = 0;
    } else {
        if (0 < motor_failure_right_count) {
            motor_failure_right_count--;
            if (0 == motor_failure_right_count) {
                motor_failure_right = 1;
            }
        }
    }
    motor_output_diff_right = motor_output_diff;
}

/**
 * @brief   Initialize motor failure information.
 */
void init_motor_output_failure(void)
{
    motor_failure_left = 0;
    motor_failure_right = 0;
    motor_failure_left_count = 0;
    motor_failure_right_count = 0;
    motor_output_diff_left = 0;
    motor_output_diff_right = 0;
}