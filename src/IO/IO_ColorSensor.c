/**
 *  IO_ColorSensor.c
 *
 *  Colorセンサーの初期化と取得
 */
#include "ev3api.h"
#include "ev3portconf.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
uint8_t ambient_sensor_value;
uint8_t reflect_sensor_value;
int color_sensor_config = -1;
colorid_t color_id;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
const sensor_port_t color_sensor_port = COLOR_SENSOR_PORT;

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数宣言                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Get color from color sensor.
 */
void get_color(void) {
    color_id = ev3_color_sensor_get_color(color_sensor_port);
}

/**
 *  @brief  Get reflection value from color sensor.
 */
void get_reflect(void) {
    reflect_sensor_value = ev3_color_sensor_get_reflect(color_sensor_port);
}

/**
 *  @brief  Get the intensity of the ambient light read from color sensor.
 */
void get_ambient(void) {
    ambient_sensor_value = ev3_color_sensor_get_ambient(color_sensor_port);
}

/**
 *  @brief  Initialize color sensor configuration.
 */
void init_color_sensor(void) {
    ER ret;
    
    ret = ev3_sensor_config(color_sensor_port, COLOR_SENSOR);
    if (E_OK == ret) {
        color_sensor_config = 0;
    } else if (E_ID == ret) {
        color_sensor_config = 1;
    } else if (E_PAR == ret) {
        color_sensor_config = 2;
    } else {
        color_sensor_config = 3;
    }
}
