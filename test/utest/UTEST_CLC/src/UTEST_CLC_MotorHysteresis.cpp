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

int left_motor_power_current;
int right_motor_power_current;

extern int left_motor_power_hys;
extern int right_motor_power_hys;

extern void init_motor_hysteresis(void);
extern void hysteresis_motor_power(void);

#ifdef __cplusplus
}
#endif

class CLC_Module_MotorHysteresis_UnitTest: public ::testing::Test {
	virtual void SetUp(void) {
		left_motor_power_current = 0;
		right_motor_power_current = 0;

		left_motor_power_hys = 0;
		right_motor_power_hys = 0;
	}

	virtual void TearDown(void) {}
};

TEST_F(CLC_Module_MotorHysteresis_UnitTest, init_motor_hysteresis_001) {
	left_motor_power_hys = 0xFF;
	right_motor_power_hys = 0xFF;

	init_motor_hysteresis();

	EXPECT_EQ(0, left_motor_power_hys);
	EXPECT_EQ(0, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, init_motor_hysteresis_002) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;

	init_motor_hysteresis();

	EXPECT_EQ(0, left_motor_power_hys);
	EXPECT_EQ(0, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_001) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;
	left_motor_power_current = 0;
	right_motor_power_current = 0;

	hysteresis_motor_power();

	EXPECT_EQ(0, left_motor_power_hys);
	EXPECT_EQ(0, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_002) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;
	left_motor_power_current = 3;
	right_motor_power_current = 3;

	hysteresis_motor_power();

	EXPECT_EQ(0, left_motor_power_hys);
	EXPECT_EQ(0, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_003) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;
	left_motor_power_current = 4;
	right_motor_power_current = 4;

	hysteresis_motor_power();

	EXPECT_EQ(3, left_motor_power_hys);
	EXPECT_EQ(3, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_004) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;
	left_motor_power_current = -3;
	right_motor_power_current = -3;

	hysteresis_motor_power();

	EXPECT_EQ(0, left_motor_power_hys);
	EXPECT_EQ(0, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_005) {
	left_motor_power_hys = 0;
	right_motor_power_hys = 0;
	left_motor_power_current = -4;
	right_motor_power_current = -4;

	hysteresis_motor_power();

	EXPECT_EQ(-3, left_motor_power_hys);
	EXPECT_EQ(-3, right_motor_power_hys);
}

TEST_F(CLC_Module_MotorHysteresis_UnitTest, hysteresis_motor_power_006) {
	left_motor_power_hys = 1;
	right_motor_power_hys = 1;
	left_motor_power_current = 5;
	right_motor_power_current = 5;

	hysteresis_motor_power();

	EXPECT_EQ(4, left_motor_power_hys);
	EXPECT_EQ(4, right_motor_power_hys);
}
