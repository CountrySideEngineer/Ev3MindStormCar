//============================================================================
// Name        : UTEST_CLC_MotorHysteresis.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "gtest/gtest.h"

#ifdef __cplusplus
extern "C" {
#endif

int turn_ratio;
int target_motor_output;

extern int target_motor_output_left;
extern int target_motor_output_right;

extern void init_target_motor_outputLR(void);
extern void calc_target_motor_outputLR(void);

#ifdef __cplusplus
}
#endif

class CLC_Module_TargetMotorPower_UnitTest: public ::testing::Test {
	virtual void SetUp(void) {
		turn_ratio = 0;
		target_motor_output = 0;
		target_motor_output_left = 0;
		target_motor_output_right = 0;
	}

	virtual void TearDown(void) {}
};

TEST_F(CLC_Module_TargetMotorPower_UnitTest, init_target_motor_outputLR_001) {
	target_motor_output_left = 1;
	target_motor_output_right = 1;

	init_target_motor_outputLR();

	EXPECT_EQ(0, target_motor_output_left);
	EXPECT_EQ(0, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, init_target_motor_outputLR_002) {
	target_motor_output_left = 1;
	target_motor_output_right = 1;

	init_target_motor_outputLR();

	EXPECT_EQ(0, target_motor_output_left);
	EXPECT_EQ(0, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_001) {
	turn_ratio = 1;
	target_motor_output = 10;

	calc_target_motor_outputLR();

	EXPECT_EQ(10, target_motor_output_left);
	EXPECT_EQ(10, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_002) {
	turn_ratio = 1;
	target_motor_output = 46;

	calc_target_motor_outputLR();

	EXPECT_EQ(45, target_motor_output_left);
	EXPECT_EQ(44, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_003) {
	turn_ratio = 1;
	target_motor_output = -46;

	calc_target_motor_outputLR();

	EXPECT_EQ(-45, target_motor_output_left);
	EXPECT_EQ(-44, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_004) {
	turn_ratio = -1;
	target_motor_output = 46;

	calc_target_motor_outputLR();

	EXPECT_EQ(44, target_motor_output_left);
	EXPECT_EQ(45, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_005) {
	turn_ratio = -1;
	target_motor_output = -46;

	calc_target_motor_outputLR();

	EXPECT_EQ(-44, target_motor_output_left);
	EXPECT_EQ(-45, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_006) {
	turn_ratio = 0;
	target_motor_output = 46;

	calc_target_motor_outputLR();

	EXPECT_EQ(46, target_motor_output_left);
	EXPECT_EQ(46, target_motor_output_right);
}

TEST_F(CLC_Module_TargetMotorPower_UnitTest, calc_target_motor_outputLR_007) {
	turn_ratio = 0;
	target_motor_output = -46;

	calc_target_motor_outputLR();

	EXPECT_EQ(-46, target_motor_output_left);
	EXPECT_EQ(-46, target_motor_output_right);
}
