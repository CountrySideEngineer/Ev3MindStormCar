/**
 *  CMD_Code0E.c
 *
 *  Command for 0x0E, GetSensors.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/
extern const int COMMAND_RECV_DATA_BUF_SIZE;
extern const int COMMAND_SEND_DATA_BUF_SIZE;
extern const sensor_port_t sensor_port[];

/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数宣言                                 */
/*****************************************************************************/
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_10);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_11);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_20);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_21);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_30);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_40);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_41);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code0E_42);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetSensors, code 0x0E command.
 *          This function send type of connected sensors.
 */
void cmd_code0E(void) {
    uint8_t res_code = 0x00;
    uint8_t res_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t (*cmd_code0E_Sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);
    
    //Check sub command code in received command data.
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    res_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    sub_res_code = sub_cmd_code;

    //Check command data length.
    if (0x00 != res_data_len) {
        //Avoid being overwritten the data length error by other one.
        res_code = CMD_ERROR_CMD_DATA_LEN;
    } else {
        switch (sub_res_code) {
        case 0x00: cmd_code0E_Sub = cmd_code0E_00; break;
        case 0x10: cmd_code0E_Sub = cmd_code0E_10; break;
        case 0x11: cmd_code0E_Sub = cmd_code0E_11; break;
        case 0x20: cmd_code0E_Sub = cmd_code0E_20; break;
        case 0x21: cmd_code0E_Sub = cmd_code0E_21; break;
        case 0x30: cmd_code0E_Sub = cmd_code0E_30; break;
        case 0x40: cmd_code0E_Sub = cmd_code0E_40; break;
        case 0x41: cmd_code0E_Sub = cmd_code0E_41; break;
        case 0x42: cmd_code0E_Sub = cmd_code0E_42; break;
        default: cmd_code0E_Sub = NULL; break;
        }
        
        if (NULL != cmd_code0E_Sub) {
            res_code = cmd_code0E_Sub(
                (uint8_t *)(&rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]),
                (uint8_t)(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN]),
                (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]),
                (uint8_t *)(&res_data_len));
        } else {
            sub_res_code = 0xFF;
            res_code = CMD_ERROR_INVALID_SUB_CODE;
            res_data_len = 0;
        }
    }
    
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x0F;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x00.
 *          This functoin send whether a sensor device is connected to port and
 *          and, if a device is connected, type of connected sensor.
 */
static uint8_t cmd_code0E_00(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int8_t result = CMD_ERROR_OK;
    int index = 0;
    
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        port = sensor_port[index];
        type = ev3_sensor_get_type(port);
        if (E_ID == type) {
            *res = 0xFF;
            result = CMD_ERROR_FATAL;
        } else {
            *res = (uint8_t)type;
        }
        res++;
    }
    *res_len = 4;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x10.
 *          This function send the state of ultra sonic sensor, whether the sensor
 *          is listening the ultra sonic or not.
 */
static uint8_t cmd_code0E_10(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    bool_t is_listen = false;
    int8_t result = CMD_ERROR_OK;
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    int index = 0;
    uint8_t *sensor_num_ptr;

    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sensor_num_ptr = res;
    res++;
    
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        port = sensor_port[index];
        type = ev3_sensor_get_type(port);
        if (ULTRASONIC_SENSOR == type) {
            is_listen = ev3_ultrasonic_sensor_listen(port);
            
            *res = (uint8_t)port;
            res++;
            if (true == is_listen) {
                *res = 0x01;
            } else if (false == is_listen) {
                *res = 0x00;
            } else {
                *res = 0xFF;
                result = CMD_ERROR_FATAL;
            }
            res++;
            data_len += 2;
            sensor_num++;
        }
    }
    
    *sensor_num_ptr = sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x11.
 *          This function send the distance read from the device, the unit is
 *          milli meter.
 */
static uint8_t cmd_code0E_11(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int8_t result = 0xFF;
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    int16_t distance = 0x0000;
    int index = 0;
    uint8_t *sensor_num_ptr;

    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sensor_num_ptr = res;
    res++;
    
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        port = sensor_port[index];
        type = ev3_sensor_get_type(port);
        if (ULTRASONIC_SENSOR == type) {
            distance = ev3_ultrasonic_sensor_get_distance(port);
            
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)(((uint16_t)distance) & 0x00FF);
            res++;
            *res = (uint8_t)((((uint16_t)distance) & 0xFF00) >> 8);
            res++;
        }
        data_len += 3;
    }
    
    *sensor_num_ptr = sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x20.
 *          This function send the angle position reade from gyro sensor, the unit of the value
 *          is degree.
 */
static uint8_t cmd_code0E_20(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int8_t result = 0xFF;
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    int16_t pos = 0x0000;
    uint8_t *sensor_num_ptr;
    
    sensor_type_t type = TNUM_SENSOR_TYPE;
    sensor_port_t port = TNUM_SENSOR_PORT;

    sensor_num_ptr = res;
    res++;
    
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        port = sensor_port[index];
        type = ev3_sensor_get_type(port);
        if (GYRO_SENSOR == type) {
            pos = ev3_gyro_sensor_get_angle(port);
            
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)((((uint16_t)pos) & 0xFF00) >> 8);
            res++;
            *res = (uint8_t)(((uint16_t)pos) & 0x00FF);
            res++;
            
            data_len += 3;
            sensor_num++;
        }
    }
    
    *sensor_num_ptr = sensor_num;
    *res_len = data_len;
    
    result = 0x00;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x21.
 *          This function send the angle velocity read from gyro sensor, the unit
 *          of value is rotate per milli second, maybe.
 */
static uint8_t cmd_code0E_21(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int sensor_num = 0;
    int8_t result = CMD_ERROR_OK;
    uint8_t data_len = 0;
    int16_t gyro_veloc = 0;
    uint8_t *res_top;
    
    sensor_port_t target_port = TNUM_SENSOR_PORT;
    
    res_top = res;
    res++;
    data_len = 1;//Set the data size to represent the number of connected port.
    for (index = 0; index < (int)TNUM_MOTOR_PORT; index++) {
        target_port = sensor_port[index];
        if (GYRO_SENSOR == ev3_sensor_get_type(target_port)) {
            gyro_veloc = ev3_gyro_sensor_get_rate(target_port);
            
            *res = (uint8_t)target_port;
            res++;
            *res = (uint8_t)(((uint16_t)gyro_veloc) & 0x00FF);//angle speed:lower byte
            res++;
            *res = (uint8_t)((((uint16_t)gyro_veloc) & 0xFF00) >> 8);//angle speed:upper byte
            res++;
            
            sensor_num++;
            data_len += 3;//3byte
        }
    }
    
    *res_top = (uint8_t)sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x30.
 *          This function send whether the touch sensor is pushed or not.
 */
static uint8_t cmd_code0E_30(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int sensor_num = 0;
    int8_t result = CMD_ERROR_OK;
    uint8_t data_len = 0;
    bool_t touch_level = false;
    uint8_t *res_top;
    
    sensor_port_t target_port = TNUM_SENSOR_PORT;

    res_top = res;
    res++;
    data_len = 1;//Set the data size to represent the number of connected port.
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        target_port = sensor_port[index];
        if (TOUCH_SENSOR == ev3_sensor_get_type(target_port)) {
            touch_level = ev3_touch_sensor_is_pressed(target_port);
            *res = (uint8_t)target_port;
            res++;
            *res = (uint8_t)touch_level;
            res++;
            
            sensor_num++;
            data_len += 2;//2バイト
        }
    }
    
    *res_top = (uint8_t)sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x40.
 *          This function send the ambient read from color sensor.
 */
static uint8_t cmd_code0E_40(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int sensor_num = 0;
    int8_t result = CMD_ERROR_OK;
    uint8_t data_len = 0;
    uint8_t ambient = 0x00;
    uint8_t* res_top;
    
    sensor_port_t target_port = TNUM_SENSOR_PORT;
    
    res_top = res;
    res++;
    data_len = 1;//Set the data size to represent the number of connected port.
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        target_port = sensor_port[index];
        if (COLOR_SENSOR == ev3_sensor_get_type(target_port)) {
            ambient = ev3_color_sensor_get_ambient(target_port);
            
            *res = (uint8_t)target_port;
            res++;
            *res = (uint8_t)ambient;
            res++;
            
            sensor_num++;
            data_len += 2;
        }
    }
    
    *res_top = sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x41.
 *          This function send the color reade from color sensor value.
 */
static uint8_t cmd_code0E_41(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int sensor_num = 0;
    int8_t result = CMD_ERROR_OK;
    uint8_t data_len = 0;
    colorid_t colorid = TNUM_COLOR;
    uint8_t *res_top;
    
    sensor_port_t target_port = TNUM_SENSOR_PORT;
    
    res_top = res;
    res++;
    
    data_len = 1;//Set the data size to represent the number of connected port.
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        target_port = sensor_port[index];
        if (COLOR_SENSOR == ev3_sensor_get_type(target_port)) {
            colorid = ev3_color_sensor_get_color(target_port);
            
            *res = (uint8_t)target_port;
            res++;
            *res = (uint8_t)colorid;
            res++;
            
            sensor_num++;
            data_len += 2;
        }
    }
    
    *res_top = sensor_num;
    *res_len = data_len;
    
    return result;
}

/**
 *  @brief  A function called by cmd_code0E. sub code 0x42.
 *          This function send the ref;ected color value.
 */
static uint8_t cmd_code0E_42(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    int index = 0;
    int sensor_num = 0;
    int8_t result = CMD_ERROR_OK;
    uint8_t reflect = 0x00;
    uint8_t data_len = 0;
    uint8_t *res_top;
    
    sensor_port_t target_port = TNUM_SENSOR_PORT;
    res_top = res;
    res++;
    
    data_len = 1;//Set the data size to represent the number of connected port.
    for (index = 0; index < (int)TNUM_SENSOR_PORT; index++) {
        target_port = sensor_port[index];
        if (COLOR_SENSOR == ev3_sensor_get_type(target_port)) {
            reflect = ev3_color_sensor_get_reflect(target_port);
            
            *res = (uint8_t)target_port;
            res++;
            *res = (uint8_t)reflect;
            res++;
            
            sensor_num++;
            data_len += 2;//2 byte
        }
    }
    
    *res_top = sensor_num;
    *res_len = data_len;
    
    return result;
}
