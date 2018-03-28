/**
 *  CMD_Code40.c
 *
 *  GetTouchSensor command source code file.
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


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetTouchSensor command.
 *          The response data of the command is setup in this function.
 */
void cmd_code40(void) {
    uint8_t res = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0;
    uint8_t res_data_len = 0;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t sensor_num = 0;
    int sensor_index = 0;
    uint8_t *res_data_dev_num = NULL;
    uint8_t *res_data_ptr = NULL;
    bool_t is_press = false;
    sensor_port_t port = TNUM_SENSOR_PORT;
    sensor_type_t type = TNUM_SENSOR_TYPE;
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    
    //Check received command data length.
    if (0x00 != cmd_data_len) {
        res = CMD_ERROR_CMD_DATA_LEN;
    }
    //Check sub command code.
    if ((CMD_ERROR_OK == res) && (0x00 != sub_cmd_code)) {
        res = CMD_ERROR_INVALID_SUB_CODE;
        res_data_len = 0;
    } else {
        //If the command data is appropriate, handle received command.
        res_data_dev_num = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]);
        res_data_ptr = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP + 1]);
        res_data_len = 1;//Set the data size to represent the number of connected port.
        for (sensor_index = 0;
            sensor_index < (int)TNUM_SENSOR_PORT;
            sensor_index++)
        {
            port = sensor_port[sensor_index];
            type = ev3_sensor_get_type(port);
            if (E_ID == type) {
                res = 0xFF;
            } else if (TOUCH_SENSOR == type) {
                is_press = ev3_touch_sensor_is_pressed(port);
                
                *res_data_ptr = port;
                res_data_ptr++;
                if (false == is_press) {
                    *res_data_ptr = 0;
                } else {
                    *res_data_ptr = 1;
                }
                res_data_ptr++;
                sensor_num++;
                res_data_len += 2;
            }
        }
        *res_data_dev_num = sensor_num;
    }
    
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x41;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
