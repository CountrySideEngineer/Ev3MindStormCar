/**
 *  CMD_COdeF0.c
 *
 *  Source code of 0xF0 command, to get sensor parameters.
 */
#include "ev3api.h"
#include "CMD.h"

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern bool_t touch_sensor_state;
extern uint8_t rcv_msg_buf[];
extern uint8_t snd_msg_buf[];
extern uint8_t rcv_msg_len;
extern uint8_t snd_msg_len;
extern uint8_t is_listen;
extern uint8_t ambient_sensor_value;
extern uint8_t reflect_sensor_value;
extern int16_t distance_sensor_value;
extern int16_t angle_sensor_value;
extern int16_t rate_sensor_value;
extern colorid_t color_id;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/
extern const sensor_port_t sensor_port[];
extern const int COMMAND_RECV_DATA_BUF_SIZE;
extern const int COMMAND_SEND_DATA_BUF_SIZE;

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
static void cmd_set_no_sensor(uint8_t *data, uint8_t *data_len);
static void cmd_set_ultrasonic_sensor(uint8_t *data, uint8_t *data_len);
static void cmd_set_color_sensor(uint8_t *data, uint8_t *data_len);
static void cmd_set_touch_sensor(uint8_t *data, uint8_t *data_len);
static void cmd_set_gyro_sensor(uint8_t *data, uint8_t *data_len);

/**
 * @brief   Main function of GetSensorParameter command.
 *          This function, and command, returns sensor parameter connected
 *          to brcik device.
 */
void cmd_codeF0(void) {
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0x00;
    uint8_t res_data_len = 0x00;
    uint8_t data_len = 0x00;

    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;

    int port_index = 0;
    int data_start_index = 0;
    int total_data_len = 0;

    void (*cmd_codeF0_get_sensor)(uint8_t *data, uint8_t *data_len);
    
    //Check sub command code in received command data.
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    
    //Check received command_data_length.
    if (0x00 != sub_cmd_code) {
        res_code = CMD_ERROR_INVALID_SUB_CODE;
        res_data_len = 0x00;
    }
    if (0x00 != cmd_data_len) {
        res_code = CMD_ERROR_CMD_DATA_LEN;
        res_data_len = 0x00;
    }
    
    if (CMD_ERROR_OK == res_code) {
        data_start_index = RES_DATA_FORMAT_INDEX_RES_DATA_TOP;
        for (port_index = 0; port_index < 4; port_index++) {
            port = sensor_port[port_index];
            type = ev3_sensor_get_type(port);
            switch (type) {
                case NONE_SENSOR:
                    cmd_codeF0_get_sensor = cmd_set_no_sensor;
                    break;

                case ULTRASONIC_SENSOR:
                    cmd_codeF0_get_sensor = cmd_set_ultrasonic_sensor;
                    break;

                case COLOR_SENSOR:
                    cmd_codeF0_get_sensor = cmd_set_color_sensor;
                    break;

                case TOUCH_SENSOR:
                    cmd_codeF0_get_sensor = cmd_set_touch_sensor;
                    break;

                case GYRO_SENSOR:
                    cmd_codeF0_get_sensor = cmd_set_gyro_sensor;
                    break;

                default:
                    cmd_codeF0_get_sensor = NULL;
                    break;
            }
            if (NULL != cmd_codeF0_get_sensor) {
                cmd_codeF0_get_sensor(
                    (uint8_t *)(&(snd_msg_buf[data_start_index])),
                    (uint8_t *)(&data_len));
                data_start_index += data_len;
                total_data_len += data_len;
            } else {
                res_code = CMD_ERROR_INVALID_CMD_DATA;
                res_data_len = 0x00;
                data_len = 0x00;

                break;//Exit "for" loop because an error occurred.
            }
        }
        res_data_len = total_data_len;
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0xF1;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + total_data_len;
}

/**
 * @brief   A function to read and set no sensor is connected to a port
 *          specified by 1st argument "port".
 * 
 * @param   Port ultrasonic sensor is connected.
 * @param[out]  Pointer to data to set sensor data.
 * @param[out]  Pointet to length of data set in this function.
 */
static void cmd_set_no_sensor(uint8_t *data, uint8_t *data_len) {
    *data = 0x00;
    data++;
    *data = 0x00;
    *data_len = 0x02;
}

/**
 * @brief   A function to read and set ultrasonic sensor value into
 *          response data buffer.
 * 
 * @param   Port ultrasonic sensor is connected.
 * @param[out]  Pointer to data to set sensor data.
 * @param[out]  Pointet to length of data set in this function.
 */
static void cmd_set_ultrasonic_sensor(uint8_t *data, uint8_t *data_len) {
    int16_t distance = 0x00;
    bool_t listen = 0x00;

    distance = distance_sensor_value;
    listen = is_listen;

    *data = 0x20;
    data++;
    *data = 0x03;
    data++;
    *data = (uint8_t)(distance & 0x00FF);//Lower byte.
    data++;
    *data = (uint8_t)((((uint16_t)distance) & 0xFF00) >> 8);
    data++;
    if (true == listen) {
        *data = 0x01;
    } else {
        *data = 0x00;
    }
    *data_len = 0x05;
}

/**
 * @brief   A function to read and set color sensor value into
 *          response data buffer.
 * 
 * @param   Port ultrasonic sensor is connected.
 * @param[out]  Pointer to data to set sensor data.
 * @param[out]  Pointet to length of data set in this function.
 */
static void cmd_set_color_sensor(uint8_t *data, uint8_t *data_len) {
    *data = 0x30;
    data++;
    *data = 0x03;
    data++;
    *data = ambient_sensor_value;
    data++;
    *data = (uint8_t)color_id;
    data++;
    *data = reflect_sensor_value;
    *data_len = 0x05;
}

/**
 * @brief   A function to read and set touch sensor value into
 *          response data buffer.
 * 
 * @param   Port ultrasonic sensor is connected.
 * @param[out]  Pointer to data to set sensor data.
 * @param[out]  Pointet to length of data set in this function.
 */
static void cmd_set_touch_sensor(uint8_t *data, uint8_t *data_len) {

    bool_t is_pressed = touch_sensor_state;

    *data = 0x40;
    data++;
    *data = 0x01;
    data++;
    if (true == is_pressed) {
        *data = 0x01;
    } else {
        *data = 0x02;
    }
    *data_len = 0x03;
}

/**
 * @brief   A function to read and set gyro sensor value into
 *          response data buffer.
 * 
 * @param   Port ultrasonic sensor is connected.
 * @param[out]  Pointer to data to set sensor data.
 * @param[out]  Pointet to length of data set in this function.
 */
static void cmd_set_gyro_sensor(uint8_t *data, uint8_t *data_len) {
    int16_t angle = angle_sensor_value;
    int16_t rate = rate_sensor_value;

    *data = 0x50;
    data++;
    *data = 0x04;
    data++;
    *data = (uint8_t)(angle & 0x00FF);
    data++;
    *data = (uint8_t)((((uint16_t)angle) & 0xFF00) >> 8);
    data++;
    *data = (uint8_t)(rate & 0x00FF);
    data++;
    *data = (uint8_t)((((uint16_t)rate) & 0xFF00) >> 8);
    *data_len = 0x06;
}