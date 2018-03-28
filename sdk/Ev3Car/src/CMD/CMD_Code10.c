/**
 *  CMD_Code10.c
 *
 *  GetMotorPower command source code file.
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
extern int target_motor_output;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/
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
/*                                  関数宣言                                 */
/*****************************************************************************/
DECLARE_SUB_CMD_CODE_FUNC(cmd_code10_00);
DECLARE_SUB_CMD_CODE_FUNC(cmd_code10_01);

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Main function of GetMotorPower.
 *          The reponse data of command is setup in this function.
 */
void cmd_code10(void) {
    uint8_t res_code;
    uint8_t cmd_data_len = 0;
    uint8_t sub_cmd_code = 0;
    uint8_t sub_res_code = 0;
    uint8_t res_data_len = 0;
    uint8_t (*cmd_code10_sub)(
        uint8_t *cmd, uint8_t cmd_len,
        uint8_t *res, uint8_t *res_len);

    sub_cmd_code = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_SUB_CODE];
    cmd_data_len = rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN];
    sub_res_code = sub_cmd_code;

    //Check received command data length.
    if (0x00 != cmd_data_len) {
        sub_res_code = 0xFE;
        res_code = 0xFF;
        res_data_len = 0;
    } else {
        switch (sub_cmd_code) {
            case 0x00: cmd_code10_sub = cmd_code10_00; break;
            case 0x01: cmd_code10_sub = cmd_code10_01; break;
            default: cmd_code10_sub = NULL; break;
        }

        if (NULL != cmd_code10_sub) {
            res_code = cmd_code10_sub(
                (uint8_t *)(&rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_TOP]),
                (uint8_t)(rcv_msg_buf[CMD_DATA_FORMAT_INDEX_CMD_DATA_LEN]),
                (uint8_t *)(&snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_TOP]),
                (uint8_t *)(&res_data_len));
        } else {
            sub_res_code = 0xFF;
            res_code = 0xFD;
            res_data_len = 0;
        }
    }

    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CODE] = 0x11;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_SUB_CODE] = sub_res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_CMD_RSLT] = res_code;
    snd_msg_buf[RES_DATA_FORMAT_INDEX_RES_DATA_LEN] = res_data_len;
    snd_msg_len = 4 + res_data_len;
}

/**
 *  @brief  Function to handle command:0x10/Sub command code:0x00.
 *          This function sets current motor output.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
uint8_t cmd_code10_00(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    *res = target_motor_output;
    *res_len = 1;

    return CMD_ERROR_OK;
}

/**
 *  @brief  Function to handle command:0x10/Sub command code:0x01.
 *          This function sets port connection and motor output value.
 *
 *  @param  cmd Pointer to head of command data in received byte data.
 *  @param  cmd_len Length of command data in received byte data.
 *  @param  res Pointer to buffer to set response data in the buffer.
 *  @param  res_len Length of response data in the response buffer.
 *  @return Result of command handling. If the operation succeeded, this
 *          function returns zero, nor none-zero value.
 */
static uint8_t cmd_code10_01(
    uint8_t *cmd, uint8_t cmd_len,
    uint8_t *res, uint8_t *res_len)
{
    ER_UINT motor_type = NONE_MOTOR;
    motor_port_t target_port = TNUM_MOTOR_PORT;
    int motor_port_index = 0;
    int motor_power = 0;
    uint8_t is_connect = 0;

    for (motor_port_index = 0;
        motor_port_index < TNUM_MOTOR_PORT;
        motor_port_index++)
    {
        target_port = motor_port[motor_port_index];
        motor_type = ev3_motor_get_type(target_port);
        if (NONE_MOTOR != motor_type) {
            is_connect = 1;
            motor_power = ev3_motor_get_power(target_port);
        } else {
            is_connect = 0;
            motor_power = 0;
        }
        *res = is_connect;
        res++;
        *res = (uint8_t)motor_power;
        res++;
    }
    *res_len = 8;

    return CMD_ERROR_OK;
}
