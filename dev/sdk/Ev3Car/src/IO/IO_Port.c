/**
 *  IO_Port.c
 *
 *  Control I/O port, open, close, read and write.
 */
#include "ev3api.h"
#include <syssvc/serial.h>
#include "UTIL/util.h"

#define BT_MESSAGE_BUF_SIZE        (32)

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
bool_t is_connect_bt;
uint8_t bt_rcv_msg_buf[BT_MESSAGE_BUF_SIZE];
uint8_t bt_rcv_msg_len = 0;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern uint8_t snd_msg_buf[];
extern uint8_t snd_msg_len;

/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  @brief  �|�[�g�̐ڑ���Ԃ��m�F����B
 */
void port_check_connectoin() {
    is_connect_bt = ev3_bluetooth_is_connected();
}

/**
 *  @brief  �|�[�g�Ƃ̐ڑ���Ԃ��m�F�̏�A�f�[�^��ǂݍ��ށB
 *          �|�[�g�Ɛڑ�����Ă��Ȃ��ꍇ�ɂ́A�ǂݍ��񂾃f�[�^���́u0�v�Ƃ��Ĉ����B
 */
void port_read_data() {
    if (true == is_connect_bt) {
        INIT_BUF(BT_MESSAGE_BUF_SIZE, (char *)(&bt_rcv_msg_buf[0]));
        bt_rcv_msg_len = serial_rea_dat(SIO_PORT_BT, 
            (char *)(&bt_rcv_msg_buf[0]),
            BT_MESSAGE_BUF_SIZE);
    } else {
        bt_rcv_msg_len = 0;
    }
}

/**
 *  @brief  Bluetooth�̑��M�f�[�^���A�|�[�g�ɏ������ށB
 *          �������ލۂ�Bluetooth���ڑ�����Ă��Ȃ��ꍇ�ɂ́A�������Ȃ��B
 *          �܂��A�������ރf�[�^���ݒ肳��Ă��Ȃ��ꍇ�ɂ��A�������Ȃ��B
 */
void port_write_data() {
    if ((true == is_connect_bt) && (snd_msg_len > 0)) {
        /*
         *  Bluetooth�|�[�g���ڑ�����A�����ȏ�̑��M�f�[�^���Z�b�g
         *  ����Ă����ꍇ�ɁA�f�[�^�𑗐M����B
         */
        serial_wri_dat(SIO_PORT_BT,
            (char *)(&snd_msg_buf[0]),
            snd_msg_len);
    }
}

/**
 *  @brief  IO�|�[�g������������B
 *          �|�[�g�̐ڑ����(�������t���O)�A�����Bluetooth�f�[�^��M�o�b�t�@��
 *          ���������s���B
 */
void init_io_port() {
    INIT_BUF(BT_MESSAGE_BUF_SIZE, (char *)(&bt_rcv_msg_buf[0]));

    bt_rcv_msg_len = 0;
    is_connect_bt = false;
}

/**
 *  @brief  IO�|�[�g�A��M�f�[�^�̗L��(��M�f�[�^�̒���)������������B
 *          (��M�f�[�^�̓��e�́A���������Ȃ��B)
 */
void port_reset() { bt_rcv_msg_len = 0; }