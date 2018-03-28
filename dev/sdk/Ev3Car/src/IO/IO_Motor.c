/**
 *  motor_logic
 *
 *  Program to rotate motor.
 */
#include "ev3api.h"
#include "ev3portconf.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int left_motor_config = -1;
int right_motor_config = -1;
int left_motor_power_current;
int right_motor_power_current;
int32_t left_motor_count;
int32_t right_motor_count;

/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/
extern int left_motor_power;
extern int right_motor_power;

/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/
const motor_port_t left_motor_port = LEFT_MOTOR_PORT;
const motor_port_t right_motor_port = RIGHT_MOTOR_PORT;

/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/
/**
 *  �Z�o���ꂽ���[�^�[�o�͂ŁA���[�^�[�𓮍삳����B
 */
void motor_set_power(void) {
#if 0
    ev3_motor_steer(left_motor_port, right_motor_port,
        left_motor_power, turn_ratio);
#else
    ev3_motor_set_power(left_motor_port, left_motor_power);
    ev3_motor_set_power(right_motor_port, right_motor_power);
#endif
}

/**
 *  ���[�^�[�̓���o�͂��擾����B
 */
void motor_get_power(void) {
    left_motor_power_current = ev3_motor_get_power(left_motor_port);
    right_motor_power_current = ev3_motor_get_power(right_motor_port);
}

/**
 * Read motor count in degree unit.
 */
void motor_get_count(void) {
    left_motor_count = ev3_motor_get_counts(left_motor_port);
    right_motor_count = ev3_motor_get_counts(right_motor_port);
}

/**
 *  ���[�^�[�̐ݒ�̏�����
 */
void init_motor_config(void) {
    ER ret;

    ret = ev3_motor_config(left_motor_port, MEDIUM_MOTOR);
    if (E_OK == ret) {
        left_motor_config = 0;
    } else if (E_ID == ret) {
        left_motor_config = 1;
    } else if (E_PAR == ret) {
        left_motor_config = 2;
    } else {
        left_motor_config = 3;
    }

    ret = ev3_motor_config(right_motor_port, MEDIUM_MOTOR);
    if (E_OK == ret) {
        right_motor_config = 0;
    } else if (E_ID == ret) {
        right_motor_config = 1;
    } else if (E_PAR == ret) {
        right_motor_config = 2;
    } else {
        right_motor_config = 3;
    }

    if (0  == left_motor_config) {
        ev3_motor_reset_counts(left_motor_port);
    }
    if (0 == right_motor_config) {
        ev3_motor_reset_counts(right_motor_port);
    }

    left_motor_power_current = 0;
    right_motor_power_current = 0;
    right_motor_count = 0;
    left_motor_count = 0;
}
