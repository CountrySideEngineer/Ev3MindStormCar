/*
 * UTEST_IO_Stub.cpp
 *
 *  Created on: 2018/03/28
 *      Author: CountrySideEngineer
 */
#include <stdio.h>

#define UTEST_IO_STUB_BUFF_SIZE		(100)

/**
 * @brief	Stub of function ev3_motor_set_power
 *
 * @param	Motor device connected port.
 * @param	Type of motor device.
 * @return	Result of this function.
 */
int ev3_motor_config_count;
motor_port_t ev3_motor_config_port_args[UTEST_IO_STUB_BUFF_SIZE];
motor_type_t ev3_motor_config_type_args[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_config_res[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_config(motor_port_t port, motor_type_t type) {
	ER stub_ret = ev3_motor_config_res[ev3_motor_config_count];

	ev3_motor_config_port_args[ev3_motor_config_count] = port;
	ev3_motor_config_type_args[ev3_motor_config_count] = type;

	ev3_motor_config_count++;

	return stub_ret;
}

/**
 * @brief	Stub of function ev3_motor_get_type.
 *
 * @param	Motor device connected port.
 * @return	Result of this function.
 */
int ev3_motor_get_type_count;
motor_port_t ev3_motor_get_type_port_args[UTEST_IO_STUB_BUFF_SIZE];
ER_UINT ev3_motor_get_type_count_res[UTEST_IO_STUB_BUFF_SIZE];
ER_UINT ev3_motor_get_type(motor_port_t port) {
	ER_UINT stub_ret = ev3_motor_get_type_count_res[ev3_motor_get_type_count];

	ev3_motor_get_type_port_args[ev3_motor_get_type_count] = port;

	ev3_motor_get_type_count++;

	return stub_ret;
}

/**
 * @brief	Stub of function ev3_motro_get_counts
 *
 * @param	Motor device connected port.
 * @param	Result of this function.
 */
int ev3_motro_get_counts_count;
motor_port_t ev3_motor_get_counts_res_port_args[100];
int32_t ev3_motor_get_counts_res[100];
int32_t ev3_motor_get_counts(motor_port_t port) {
	ER stub_ret = ev3_motor_get_counts_res[ev3_motro_get_counts_count];

	ev3_motor_get_counts_res_port_args[ev3_motro_get_counts_count] = port;

	ev3_motro_get_counts_count++;

	return stub_ret;
}

/**
 * @brief	Stub of function ev3_motro_reset_counts
 *
 * @param	Motor device connected port.
 * @param	Result of this function.
 */
int ev3_motor_reset_counts_count;
motor_port_t ev3_motor_reset_counts_port_args[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_reset_counts_res[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_reset_counts(motor_port_t port) {
	ER stub_res = ev3_motor_reset_counts_res[ev3_motor_reset_counts_count];

	ev3_motor_reset_counts_port_args[ev3_motor_reset_counts_count] = port;

	ev3_motor_reset_counts_count++;

	return stub_res;
}

/**
 * @brief	Stub of function ev3_motro_set_power.
 *
 * @param	Motor device connect port.
 * @return	Result of this function.
 */
int ev3_motor_set_power_count;
motor_port_t ev3_motor_set_power_port_args[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_set_power_res[UTEST_IO_STUB_BUFF_SIZE];
ER ev3_motor_set_power(motor_port_t port, int power) {
	ER stub_res = ev3_motor_set_power_res[ev3_motor_set_power_count];

	ev3_motor_set_power_port_args[ev3_motor_set_power_count] = port;

	ev3_motor_set_power_count++;

	return stub_res;
}

int ev3_motor_get_power_count;
motor_port_t ev3_motor_get_power_port_args[UTEST_IO_STUB_BUFF_SIZE];
int ev3_motor_get_power_res[UTEST_IO_STUB_BUFF_SIZE];
int ev3_motor_get_power(motor_port_t port) {
	int stub_res = ev3_motor_get_power_res[ev3_motor_get_power_count];

	ev3_motor_get_power_port_args[ev3_motor_get_power_count] = port;

	ev3_motor_get_power_count++;

	return stub_res;
}
