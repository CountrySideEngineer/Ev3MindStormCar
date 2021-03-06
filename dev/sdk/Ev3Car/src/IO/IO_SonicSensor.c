#include "ev3api.h"
#include "ev3portconf.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int16_t distance_sensor_value;
int sonic_sensor_config = -1;
uint8_t is_listen;

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int motor_power;


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const sensor_port_t sonic_sensor_port = SONIC_SENSOR_PORT;


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Update ultrasonic sensor value.
 */
void get_distance(void) {
    distance_sensor_value = 
        ev3_ultrasonic_sensor_get_distance(sonic_sensor_port);
}

/**
 *  @brief  Initialize configuration of ultrasonic sensor.
 */
void init_sonic_sensor(void) {
    ER ret;
    
    ret = ev3_sensor_config(sonic_sensor_port, ULTRASONIC_SENSOR);
    if (E_OK == ret) {
        sonic_sensor_config = 0;
    } else if (E_ID == ret) {
        sonic_sensor_config = 1;
    } else if (E_PAR == ret) {
        sonic_sensor_config = 2;
    } else {
        sonic_sensor_config = 3;
    }
    is_listen = 0x00;
}
