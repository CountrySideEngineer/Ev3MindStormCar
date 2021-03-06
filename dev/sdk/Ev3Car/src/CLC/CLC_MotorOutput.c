/**
 *  calc_motor_output
 *
 *  Calc motor output power.
 */
#include "ev3api.h"
#include "util.h"
#include "CLC_MotorOutput.h"

#define MOTOR_POWER_MIN                 (-45)
#define MOTOR_POWER_MAX                 (45)

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int8_t motor_failure_left;
extern int8_t motor_failure_right;
extern int left_motor_power_hys;
extern int right_motor_power_hys;
extern int target_motor_output_left;
extern int target_motor_output_right;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
static const int Kp = 10;
static const int Ki = 5;
static const int Kd = 10;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int left_motor_power;
int right_motor_power;
//PID制御パラメータ
power_t left_power;
power_t right_power;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
static int pid_control(power_t *power);

/**
 *  @brief  Calc and determine motor output power by PID control.
 *          In the case calcurated value exceeds 50 percent or falls below
 *          -50 percent, value limitation is executed to protect.
 */
void calc_motor_power(void) {
    int left_output = 0;
    int right_output = 0;

    if ((0 == motor_failure_left) && (0 == motor_failure_right)) {
        //No failure has been detected.
        left_power.target = target_motor_output_left;
        right_power.target = target_motor_output_right;
    } else {
        if (target_motor_output_left < left_motor_power_hys) {
            left_power.target--;
        } else if (left_motor_power_hys < target_motor_output_left) {
            left_power.target++;
        }
        if (target_motor_output_right < right_motor_power_hys) {
            right_power.target--;
        } else if (right_motor_power_hys < target_motor_output_right) {
            right_power.target++;
        }
    }
    left_power.current = left_motor_power_hys;
    right_power.current = right_motor_power_hys;

    left_output = pid_control(&left_power);
    right_output = pid_control(&right_power);

    /**
     *  Calcurate Finalized motor power.
     *  Due to Hardware or OS (maybe OS), the motor can not drive with
     *  the absolute actual motor power with 50. If the power value exceeds
     *  50 is set, the motor dirve does not change.
     *  And, the case that the value exceeds 50 is set to motor, sometime
     *  the motor can not operate in a precise manner. To avoid this situation,
     *  limits motor output preliminarily.
     */
    //Motor output power(Limitation).
    //Left side motor.
    left_motor_power = limit_int(left_output,
        MOTOR_POWER_MIN, MOTOR_POWER_MAX);
    //Right side motor.
    right_motor_power = limit_int(right_output,
        MOTOR_POWER_MIN, MOTOR_POWER_MAX);
}

/**
 *  @brief  Initialize motor power and referenced value.
 */
void init_motor_power(void) {
    left_motor_power = 0;
    right_motor_power = 0;

    left_power.target = 0;
    left_power.current = 0;
    left_power.integral = 0;
    left_power.diff = 0;
    left_power.ddt = 0;
    left_power.reset_count = 0;

    right_power.target = 0;
    right_power.current = 0;
    right_power.integral = 0;
    right_power.diff = 0;
    right_power.ddt = 0;
    right_power.reset_count = 0;
}

/**
 *  @brief  Execute PID control.
 *  @param[in,out]  Value for PID control.
 *  @return Calcurated amount by PID control.
 */
static int pid_control(power_t *power) {
    int ddt = 0;    //derivative element
    int diff = 0;
    int pid = 0;
    int integral = 0;

    if (NULL != power) {//TODO:This check is not required, so must be deleted.
        diff = power->target - power->current;  //P term

        integral = power->integral + diff;      //I term
        ddt = power->diff - diff;               //D term
        pid = (Kp * diff + Ki * integral + Kd * ddt) / 100;

        power->target_prev = power->target;
        power->integral = integral;
        power->diff = diff;
        power->ddt = ddt;
    } else {
        pid = 0;
    }

    return pid;
}
