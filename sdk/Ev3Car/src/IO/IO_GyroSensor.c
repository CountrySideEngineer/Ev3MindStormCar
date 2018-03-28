/**
 *  IO_GyroSensor.c
 *
 *  Get and update parameter of gyro sensor value.
 */
#include "ev3api.h"
#include "ev3portconf.h"
 
/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int16_t angle_sensor_value;
int16_t rate_sensor_value;
int gyro_sensor_config = -1;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
const sensor_port_t gyro_sensor_port = GYRO_SENSOR_PORT;

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/


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
 *  @brief  Get relative angle from gyro sensor.
 *          For more detail information, read hardware manual
 *          (Hardware Developer Kit).
 */
void get_angle(void) {
    angle_sensor_value = ev3_gyro_sensor_get_angle(gyro_sensor_port);
}

/**
 *  @brief  Get the actual rotation/second from gyro sensor.
 *          For more detail information, read hardware manual
 *          (Hardware Developer Kit).
 */
void get_rate(void) {
    rate_sensor_value = ev3_gyro_sensor_get_rate(gyro_sensor_port);
}

/**
 *  @brief  Initialize gyro sensor.
 */
void init_gyro_sensor(void) {
    ER ret;
    
    ret = ev3_sensor_config(gyro_sensor_port, GYRO_SENSOR);
    if (E_OK == ret) {
        gyro_sensor_config = 0;
    } else if (E_ID == ret) {
        gyro_sensor_config = 1;
    } else if (E_PAR == ret) {
        gyro_sensor_config = 2;
    } else {
        gyro_sensor_config = 3;
    }
}
