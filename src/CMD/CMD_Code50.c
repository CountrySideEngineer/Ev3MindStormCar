/**
 *  CMD_Code50.c
 *
 *  GetGyroSensor command source code file.
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
DECLARE_SUB_CMD_CODE_FUNC(cmd_code50_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code50_01);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetGyroSensor command.
 *          The response data of command is setup in this function.
 */
void cmd_code50(void) {
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t res_data_len = 0;
    uint8_t (*cmd_code50_sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    
    //Check received command data length.
    if (0x00 != cmd_data_len) {
        res_code = CMD_ERROR_CMD_DATA_LEN;
        res_data_len = 0;
    } else {
        //If the command data is appropriate, handle received command.
        sub_res_code = sub_cmd_code;
        switch (sub_cmd_code) {
        case 0x00: cmd_code50_sub = cmd_code50_00; break;
        case 0x01: cmd_code50_sub = cmd_code50_01; break;
        default:
            cmd_code50_sub = NULL;
            break;
        }
        if (NULL != cmd_code50_sub) {
            res_code = cmd_code50_sub(
                (uint8_t *)(&(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP])),
                (uint8_t)rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN], 
                (uint8_t *)(&(snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP])),
                (uint8_t *)(&res_data_len));
        } else {
            res_code = CMD_ERROR_INVALID_SUB_CODE;
            sub_res_code = 0xFF;
            res_data_len = 0;
        }
    }
    
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x51;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  Function to handle command:0x50/Sub command code:0x00.
 *          This function sets angle pos read from gyro sensor.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code50_00(
    uint8_t *cmd, uint8_t cmd_len, 
    uint8_t *res, uint8_t *res_len)
{
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    int sensor_index;
    int16_t angle = 0;
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
        if (GYRO_SENSOR == type) {
            angle = ev3_gyro_sensor_get_angle(port);
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)(((uint16_t)angle) & 0x00FF);//lower byte
            res++;
            *res = (uint8_t)(((uint16_t)angle) >> 8);//upper byte
            res++;
            
            sensor_num++;
            data_len += 3;
        }
    }
    
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    
    return 0;
}
    
/**
 *  @brief  Function to handle command:0x50/Sub command code:0x01.
 *          This function sets angle speed read from gyro sensor.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code50_01(
    uint8_t *cmd, uint8_t cmd_len, 
    uint8_t *res, uint8_t *res_len)
{
    uint8_t sensor_num = 0;
    uint8_t data_len = 0;
    int sensor_index;
    int16_t rate = 0;
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
        if (GYRO_SENSOR == type) {
            rate = ev3_gyro_sensor_get_rate(port);
            *res = (uint8_t)port;
            res++;
            *res = (uint8_t)(((uint16_t)rate) & 0x00FF);//lower byte
            res++;
            *res = (uint8_t)(((uint16_t)rate) >> 8);//upper byte
            res++;
            
            sensor_num++;
            data_len += 3;
        }
    }
    
    *res_len = data_len;
    *sensor_num_ptr = sensor_num;
    
    return 0;
}
