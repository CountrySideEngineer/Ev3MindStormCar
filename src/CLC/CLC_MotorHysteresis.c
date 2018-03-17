/**
 *  CLC_MotorHysteresis.c
 *
 *  Calcurate hysteresis of motor output value, remove noise from motor
 *  power output.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                             Global variables                              */
/*****************************************************************************/
int left_motor_power_hys;
int right_motor_power_hys;

/*****************************************************************************/
/*                             Static variables                              */
/*****************************************************************************/
static const int hysteresis = 3;

/*****************************************************************************/
/*                              Global constant                              */
/*****************************************************************************/


/*****************************************************************************/
/*                      External global variables.                           */
/*****************************************************************************/
extern int left_motor_power_current;
extern int right_motor_power_current;

/*****************************************************************************/
/*                        Exernal glocal constant.                           */
/*****************************************************************************/


/*****************************************************************************/
/*                            External function                              */
/*****************************************************************************/


/*****************************************************************************/
/*                            Implement function                             */
/*****************************************************************************/
static int calcurate_hysteresis(int cur_output, int prev_output, int hys);

/**
 * @brief   Calcurate hysteresis value of current motor output.
 */
void hysteresis_motor_power(void) {
    left_motor_power_hys = calcurate_hysteresis(
        left_motor_power_current, left_motor_power_hys, hysteresis);
    right_motor_power_hys = calcurate_hysteresis(
        right_motor_power_current, right_motor_power_hys, hysteresis);
}

/**
 * @brief   Body of calcuration of hysteresis value of motor output.
 * 
 * @param   cur_output      Current motor output.
 * @param   prev_output     Motor output of previous period.
 * @param   hys             Hysteresis
 */
static int calcurate_hysteresis(int cur_output, int prev_output, int hys) {
    int ret_val = 0;

    if ((prev_output + hys) < cur_output) {
        ret_val = prev_output + hys;
    } else if (cur_output < (prev_output - hys)) {
        ret_val = prev_output - hys;
    } else {
        ret_val = prev_output;
    }

    return ret_val;
}

/**
 * @brief   Initialize hysteresis value of motor output.
 */
void init_motor_hysteresis(void) {
    left_motor_power_hys = 0;
    right_motor_power_hys = 0;
}