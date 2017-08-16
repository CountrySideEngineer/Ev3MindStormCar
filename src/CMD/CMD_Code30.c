/**
 *  CMD_Code30.c
 *
 *  GetColorSensor command source code file.
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
DECLARE_SUB_CMD_CODE_FUNC(cmd_code30_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code30_01);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code30_02);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetColorSensor command.
 *          The response data of the command is setup in this functoin.
 */
void cmd_code30(void) {
    uint8_t res = 0x00;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_data_len = 0;
    uint8_t (*cmd_code30_sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    
    //Check length of received command data.
    if (0x00 != cmd_data_len) {
        res = CMD_ERROR_CMD_DATA_LEN;
        res_data_len = 0;
    } else {
        /**
         *  If the command data length is available value, call function
         *  corresponding to sub command code.
         */
        sub_res_code = sub_cmd_code;
        switch (sub_cmd_code) {
        case 0x00: cmd_code30_sub = cmd_code30_00; break;
        case 0x01: cmd_code30_sub = cmd_code30_01; break;
        case 0x02: cmd_code30_sub = cmd_code30_02; break;
        default:
            cmd_code30_sub = NULL;
            break;
        }
        if (NULL != cmd_code30_sub) {
            res = cmd_code30_sub(
                (uint8_t *)(&(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP])),
                (uint8_t)rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN], 
                (uint8_t *)(&(snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP])),
                (uint8_t *)(&res_data_len));
        } else {
            res = CMD_ERROR_INVALID_SUB_CODE;
            sub_res_code = 0xFF;
            res_data_len = 0;
        }
    }
    
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x31;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  Function to handle command:0x30/Sub command code:0x00.
 *          This function sets ambient data to response data buffer.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code30_00(
    uint8_t *cmd, uint8_t cmd_len, 
    uint8_t *res, uint8_t *res_len)
{
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    uint8_t ambient = 0x00;
    int sensor_index = 0;
    uint8_t *sensor_num_ptr = NULL;
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sensor_num_ptr = res;
    res++;
    
    sensor_num = 0;
    data_len = 1;//Set the data size to represent the number of connected port.
    for (sensor_index = 0; sensor_index < (int)TNUM_SENSOR_PORT; sensor_index++) {
        port = sensor_port[sensor_index];
        type = ev3_sensor_get_type(port);
        if (COLOR_SENSOR  == type) {
            ambient = ev3_color_sensor_get_ambient(port);
            *res = (uint8_t)port;
            res++;
            *res = ambient;
            res++;
            sensor_num++;
            data_len += 2;
        }
    }
    
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    
    return 0;
}

/**
 *  @brief  Function to handle command:0x30/Sub command code:0x01.
 *          This function sets color that the color sensor read.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code30_01(
    uint8_t *cmd, uint8_t cmd_len, 
    uint8_t *res, uint8_t *res_len)
{
    uint8_t ret = 0;
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    uint8_t color = 0x00;
    int sensor_index = 0;
    uint8_t *sensor_num_ptr = NULL;
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sensor_num_ptr = res;
    res++;
    
    sensor_num = 0;
    data_len = 1;//Set the data size to represent the number of connected port.
    for (sensor_index = 0; sensor_index < (int)TNUM_SENSOR_PORT; sensor_index++) {
        port = sensor_port[sensor_index];
        type = ev3_sensor_get_type(port);
        if (COLOR_SENSOR == type) {
            color = ev3_color_sensor_get_color(port);
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)color;
            res++;
            sensor_num++;
            data_len += 2;
            
            if (COLOR_NONE == color) {
                //The value to show error is set to return variable.
                ret = -1;
            }
        }
    }
    
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    
    return ret;
}

/**
 *  @brief  Function to handle command:0x30/Sub command code:0x02.
 *          This function sets reflection read from color sensor.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code30_02(
    uint8_t *cmd, uint8_t cmd_len, 
    uint8_t *res, uint8_t *res_len)
{
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t sensor_num = 0x00;
    uint8_t data_len = 0x00;
    uint8_t reflect = 0x00;
    int sensor_index = 0;
    uint8_t *sensor_num_ptr;
    sensor_port_t port = TNUM_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;

    sensor_num_ptr = res;
    res++;

    data_len = 1;//Set the data size to represent the number of connected port.
    for (sensor_index = 0; sensor_index < (int)TNUM_SENSOR_PORT; sensor_index++) {
        port = sensor_port[sensor_index];
        type = ev3_sensor_get_type(port);
        if (COLOR_SENSOR == type) {
            reflect = ev3_color_sensor_get_ambient(sensor_index);
            *res = (uint8_t)port;
            res++;
            *res = reflect;
            res++;
            sensor_num++;
            data_len += 2;
        }
    }
    
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;

    return res_code;
}


