#pragma once

extern ER ev3_motor_config(motor_port_t port, motor_type_t type);
extern ER_UINT ev3_motor_get_type(motor_port_t port);
extern int32_t ev3_motor_get_counts(motor_port_t port);
extern ER ev3_motor_reset_counts(motor_port_t port);
extern ER ev3_motor_set_power(motor_port_t port, int power);
extern int ev3_motor_get_power(motor_port_t port);
extern ER ev3_motor_stop(motor_port_t port, bool_t brake);
extern ER ev3_motor_rotate(motor_port_t port, int degrees, uint32_t speed_abs, bool_t blocking);
extern ER ev3_motor_steer(motor_port_t left_motor, motor_port_t right_motor, int power, int turn_ratio);
