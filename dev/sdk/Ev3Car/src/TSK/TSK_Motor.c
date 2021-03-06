/**
 *  motor_task.c
 *
 *  Run motor.
 */
#include "ev3api.h"
#include "target_test.h"
#include "TSK_Motor.h"

/*****************************************************************************/
/*                               グローバル変数                              */
/*****************************************************************************/
int left_motor_status;
int right_motor_status;
int motor_task_count = 0;
bool_t motor_task_running;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                    定数                                   */
/*****************************************************************************/

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/
extern void init_motor_config(void);
extern void init_motor_output_limit(void);
extern void init_motor_output(void);
extern void init_motor_power(void);
extern void init_target_motor_outputLR(void);
extern void init_motor_output_failure(void);
extern void init_motor_hysteresis(void);
extern void init_motor_distance(void);
extern void judge_motor_output_limit(void);
extern void judge_motor_output_failure(void);
extern void calc_motor_power(void);
extern void motor_set_power(void);
extern void motor_get_power(void);
extern void motor_get_count(void);
extern void update_drive_direction(void);
extern void judge_target_motor_output(void);
extern void calc_target_motor_outputLR(void);
extern void get_distance(void);
extern void calc_distance_average(void);
extern void calc_trav_distance(void);
extern void judge_dist_safe(void);
extern void hysteresis_motor_power(void);

/*****************************************************************************/
/*                                   関数                                    */
/*****************************************************************************/
/**
 *  @brief  Task to read sensor value, calcurate motor power output, and
 *          set it to motor.
 */
void motor_task(intptr_t unused) {
    while (motor_task_running) {
        //Read current, actual motor output.
        motor_get_power();
        motor_get_count();
        hysteresis_motor_power();

        //Calcurate motor output.
        judge_motor_output_limit();
        judge_target_motor_output();
        calc_target_motor_outputLR();
        judge_motor_output_failure();
        calc_motor_power();

        calc_trav_distance();

        //Set motor output data.
        motor_set_power();

        motor_task_count++;
        dly_tsk(MOTOR_TASK_INTERVAL);
    }
}

/**
 *  @brief  Initialize motor task.
 */
void init_motor_task() {
    init_motor_config();
    init_motor_output();
    init_motor_output_limit();
    init_motor_power();
    init_target_motor_outputLR();
    init_motor_output_failure();
    init_motor_hysteresis();
    init_motor_distance();

    motor_task_count = 0;
    
    motor_task_running = false;
}

/**
 *  @brief  Start motor control task.
 */
void start_motor_task() {
    ER ercd;

    if (false == motor_task_running) {
        ercd = act_tsk(MOTOR_TASK);
        if (E_OK == ercd) {
            motor_task_running = true;
        } else {
            motor_task_running = false;
        }
    }
}

/**
 *  @brief  Stop motor control task.
 */
void stop_motor_task() {
    if (true == motor_task_running) {
        motor_task_running = false;
    }
}