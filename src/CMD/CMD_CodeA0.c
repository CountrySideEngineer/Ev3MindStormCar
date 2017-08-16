/**
 *  CMD_CodeA0.c
 *
 *  Source code of 0xA0 command, to get status of safety.
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
extern int8_t distance_safe_state;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/
extern const int COMMAND_RECV_DATA_BUF_SIZE;
extern const int COMMAND_SEND_DATA_BUF_SIZE;

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
 *  @brief  Main function of GetSafetyState command.
 *          The response data of command is setup in this function.
 */
void cmd_codeA0(void) {
    uint8_t sub_cmd_code = 0x00;
    uint8_t res_code = CMD_ERROR_OK;
    uint8_t cmd_data_len = 0x00;
    uint8_t res_data_len = 0x00;

    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];

    //Check received command data length.
    if (0 != cmd_data_len) {
        res_code = CMD_ERROR_CMD_DATA_LEN;
        res_data_len = 0x00;
    } else {
        if (0x00 != sub_cmd_code) {
            res_code = CMD_ERROR_INVALID_SUB_CODE;
            res_data_len = 0x00;
        } else {
            snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP] = distance_safe_state;
            res_data_len = 0x01;
        }
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0xA1;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = 0x00;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
