//============================================================================
// Name        : UTEST_JUD.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
int16_t distance_average_value;

#ifdef __cplusplus
extern "C" {
#endif

//To build unit test, variables below need to be defined.
int left_motor_power_hys;
int right_motor_power_hys;
int target_motor_output_left;
int target_motor_output_right;

extern int8_t distance_safe_state;
extern int8_t distance_safe_state_prev;
extern bool_t distance_safe_state_change;
extern int8_t motor_failure_left;
extern int8_t motor_failure_right;
extern int16_t motor_failure_left_count;
extern int16_t motor_failure_right_count;
extern uint8_t motor_output_diff_left;
extern uint8_t motor_output_diff_right;

extern const int8_t CAR_SAFE_STATE_SAFE;
extern const int8_t CAR_SAFE_STATE_ATTN;
extern const int8_t CAR_SAFE_STATE_DANG;
extern const int8_t CAR_SAFE_STATE_STOP;
extern const int16_t MOTOR_FAILURE_COUNT;
extern const int8_t MOTOR_FAILURE_OUTPUT;

extern void judge_dist_safe(void);
extern void judge_distance_safe_change(void);
extern void init_dist_safe(void);
extern void init_motor_output_failure(void);
extern void judge_motor_output_failure(void);
#ifdef __cplusplus
}
#endif

TEST(judge_dist_safe_state, init_dist_safe) {
	init_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_SAFE, distance_safe_state);
	EXPECT_EQ(CAR_SAFE_STATE_SAFE, distance_safe_state_prev);
	EXPECT_FALSE(distance_safe_state_change);
}

TEST(judge_dist_safe_state, judge_distance_safe_change_001) {
	distance_safe_state_prev = false;
	distance_safe_state = false;
	distance_safe_state_change = true;

	judge_distance_safe_change();

	EXPECT_FALSE(distance_safe_state_change);
}

TEST(judge_dist_safe_state, judge_distance_safe_change_002) {
	distance_safe_state_prev = true;
	distance_safe_state = true;
	distance_safe_state_change = true;

	judge_distance_safe_change();

	EXPECT_FALSE(distance_safe_state_change);
}

TEST(judge_dist_safe_state, judge_distance_safe_change_003) {
	distance_safe_state_prev = false;
	distance_safe_state = true;
	distance_safe_state_change = false;

	judge_distance_safe_change();

	EXPECT_TRUE(distance_safe_state_change);
}

TEST(judge_dist_safe_state, judge_distance_safe_change_004) {
	distance_safe_state_prev = true;
	distance_safe_state = false;
	distance_safe_state_change = false;

	judge_distance_safe_change();

	EXPECT_TRUE(distance_safe_state_change);
}

TEST(judge_dist_safe_state, judge_dist_safe_001) {
	distance_average_value = 44;
	distance_safe_state = CAR_SAFE_STATE_SAFE;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_ATTN, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_002) {
	distance_average_value = 45;
	distance_safe_state = CAR_SAFE_STATE_SAFE;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_SAFE, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_003) {
	distance_average_value = 34;
	distance_safe_state = CAR_SAFE_STATE_ATTN;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_DANG, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_004) {
	distance_average_value = 41;
	distance_safe_state = CAR_SAFE_STATE_ATTN;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_SAFE, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_005) {
	distance_average_value = 35;
	distance_safe_state = CAR_SAFE_STATE_ATTN;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_ATTN, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_006) {
	distance_average_value = 40;
	distance_safe_state = CAR_SAFE_STATE_ATTN;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_ATTN, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_007) {
	distance_average_value = 24;
	distance_safe_state = CAR_SAFE_STATE_DANG;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_STOP, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_008) {
	distance_average_value = 31;
	distance_safe_state = CAR_SAFE_STATE_DANG;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_ATTN, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_009) {
	distance_average_value = 25;
	distance_safe_state = CAR_SAFE_STATE_DANG;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_DANG, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_010) {
	distance_average_value = 30;
	distance_safe_state = CAR_SAFE_STATE_DANG;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_DANG, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_011) {
	distance_average_value = 21;
	distance_safe_state = CAR_SAFE_STATE_STOP;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_DANG, distance_safe_state);
}

TEST(judge_dist_safe_state, judge_dist_safe_012) {
	distance_average_value = 20;
	distance_safe_state = CAR_SAFE_STATE_STOP;

	judge_dist_safe();

	EXPECT_EQ(CAR_SAFE_STATE_STOP, distance_safe_state);
}

TEST(judge_dist_safe_state, init_motor_output_failure_001) {
	motor_failure_left = 1;
	motor_failure_right = 1;
	motor_failure_left_count = MOTOR_FAILURE_COUNT - 1;
	motor_failure_right_count = MOTOR_FAILURE_COUNT -1;
	motor_output_diff_left = 1;
	motor_output_diff_right = 1;

	init_motor_output_failure();

	EXPECT_EQ(0, motor_failure_left);
	EXPECT_EQ(0, motor_failure_right);
	EXPECT_EQ(MOTOR_FAILURE_COUNT, motor_failure_left_count);
	EXPECT_EQ(MOTOR_FAILURE_COUNT, motor_failure_right_count);
}

TEST(judge_dist_safe_state, judge_motor_output_failure_001) {
	left_motor_power_hys = 5;
	target_motor_output_left = 1;
	right_motor_power_hys = 5;
	target_motor_output_right = 0;
	motor_failure_left = 1;
	motor_failure_right = 1;
	motor_failure_left_count = 0;
	motor_failure_right_count = 0;

	judge_motor_output_failure();

	EXPECT_EQ(MOTOR_FAILURE_COUNT, motor_failure_left_count);
}
