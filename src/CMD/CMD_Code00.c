/**
 *  template.c
 *
 *  this is template file.
 */
#include "ev3api.h"

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
 *  @brief  EchoBackコマンド本体
 */
void cmd_code00(void) {
    uint8_t res = 0x00;
    uint8_t cmd_data_len = 0x00;
    uint8_t res_data_len = 0x00;
    uint8_t sub_cmd_code = 0x00;
    uint8_t sub_res_code = 0x00;
    uint8_t *rcv_buf;
    uint8_t *snd_buf;
    int idx = 0;

    rcv_buf = (uint8_t *)(&rcv_msg_buf[3]);
    snd_buf = (uint8_t *)(&snd_msg_buf[4]);
    
    sub_cmd_code = rcv_msg_buf[1];
    cmd_data_len = rcv_msg_buf[2];

    sub_res_code = sub_cmd_code;
    if ((!(0 < cmd_data_len)) || (!(cmd_data_len < 30))) {
        res = 0xFE;
    }
    if (0x00 != sub_cmd_code) {
        res = 0xFD;
        sub_res_code = 0xFF;
    }
    if (0x00 == res) {
        for (idx = 0; idx < (int)cmd_data_len; idx++) {
            *snd_buf = *rcv_buf;
            snd_buf++;
            rcv_buf++;
        }
        res_data_len = cmd_data_len;
    } else {
        res_data_len = 0;
    }
    
    snd_msg_buf[0] = 0x01;
    snd_msg_buf[1] = sub_res_code;
    snd_msg_buf[2] = res;
    snd_msg_buf[3] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}
