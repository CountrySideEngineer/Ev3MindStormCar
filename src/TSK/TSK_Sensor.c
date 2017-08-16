/**
 *  sensor_task
 *
 *  入力センサーのデータからの値を更新する。
 */
#include "ev3api.h"
#include "app.h"
#include "TSK_Sensor.h"

/*****************************************************************************/
/*                               グローバル変数                              */
/*****************************************************************************/
int SonicSensorConfig = 0;
int sensor_task_count = 0;
bool_t sensor_task_running;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                    定数                                   */
/*****************************************************************************/

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/
extern void init_color_sensor(void);
extern void init_gyro_sensor(void);
extern void init_touch_sensor(void);
extern void get_distance(void);
extern void get_color(void);
extern void get_reflect(void);
extern void get_ambient(void);
extern void get_angle(void);
extern void get_rate(void);
extern void get_touch_state(void);
extern void calc_distance_average(void);

/*****************************************************************************/
/*                                   関数                                    */
/*****************************************************************************/
/**
 *  @brief  Main funtion of sensor task, call function to read value from
 *          sensor.
 */
void sensor_task(intptr_t unused) {
    while (sensor_task_running) {
        //Read sensor data.
        get_color();
        get_reflect();
        get_ambient();
        get_angle();
        get_rate();
        get_touch_state();

        sensor_task_count++;
        dly_tsk(SENSOR_TASK_INTERVAL);
    }
}

/**
 *  @brief  Initialize sensor task.
 */
void init_sensor_task(void) {
    init_color_sensor();
    init_gyro_sensor();
    init_touch_sensor();

    sensor_task_count = 0;

    sensor_task_running = false;
}

/**
 *  @brief  Start task to get sensor value.
 */
void start_sensor_task() {
    ER ercd;

    if (false == sensor_task_running) {
        ercd = act_tsk(SENSOR_TASK);
        if (E_OK == ercd) {
            sensor_task_running = true;
        } else {
            sensor_task_running = false;
        }
    }
}

/**
 *  @brief  Stop sensor task.
 */
void stop_sensor_task() {
    if (true == sensor_task_running) {
        sensor_task_running = false;
    }
}
