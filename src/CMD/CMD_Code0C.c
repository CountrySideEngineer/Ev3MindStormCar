/**
 *  CMD_Code0C.c
 *
 *  Command to get motor type connected to each input port.
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
extern const motor_port_t motor_port[];

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
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetMotors, code 0x0C command.
 *          This function send type of connected motor device.
 */
void cmd_code0C(void) {
    uint8_t res = 0x00;
    uint8_t cmd_data_len = 0x00;
    uint8_t res_data_len = 0x00;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t *snd_buf;
    int idx;
    
    motor_type_t type = TNUM_MOTOR_TYPE;
    motor_port_t port = TNUM_MOTOR_PORT;
    
    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];

    //Check length of received command data.
    if (0x00 != cmd_data_len) {
        res = CMD_ERROR_CMD_DATA_LEN;
    }

    sub_res_code = sub_cmd_code;
    if ((CMD_ERROR_OK == res) && (0x00 != sub_cmd_code)) {
        res = CMD_ERROR_INVALID_SUB_CODE;
    }

    //Setup the data part of response data.
    snd_buf = (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]);
    if (0x00 == res) {
        for (idx = 0; idx < (int)TNUM_MOTOR_PORT; idx++) {
            port = motor_port[idx];
            type = ev3_motor_get_type(port);
            *snd_buf = (uint8_t)type;
            snd_buf++;
        }
        res_data_len = 4;
    } else {
        res_data_len = 0;
    }
    
    //Setup the header part of response data.
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x0D;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
