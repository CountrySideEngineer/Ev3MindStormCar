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

int32_t left_motor_count;
int32_t right_motor_count;

extern int32_t left_motor_trav_dist;           //Unit:mm LSB:1.0
extern int32_t right_motor_trav_dist;          //Unit:mm LSB:1.0
extern int32_t left_motor_trav_dist_hi_acc;    //Unit:mm LSB:0.01
extern int32_t right_motor_trav_dist_hi_acc;   //Unit:mm LSB:0.01
extern uint32_t left_motor_trav_dist_abs;      //Unit:mm LSB:1.0
extern uint32_t right_motor_trav_dista_abs;    //Unit:mm LSB:1.0
extern int32_t left_motor_count_prev;
extern int32_t right_motor_count_prev;

extern void init_motor_distance(void);
extern void calc_trav_distance(void);

#ifdef __cplusplus
}
#endif

class CLC_Module_TravelDistance_UnitTest: public ::testing::Test {
	virtual void SetUp(void) {
		left_motor_count = 0;
		right_motor_count = 0;

		left_motor_trav_dist = 0;
		right_motor_trav_dist = 0;
		left_motor_trav_dist_hi_acc = 0;
		right_motor_trav_dist_hi_acc = 0;
		left_motor_trav_dist_abs = 0;
		right_motor_trav_dista_abs = 0;
		left_motor_count_prev = 0;
		right_motor_count_prev = 0;
	}

	virtual void TearDown(void) {}
};

TEST_F(CLC_Module_TravelDistance_UnitTest, init_motor_distance_001) {
	left_motor_count = 0;
	right_motor_count = 0;

	left_motor_trav_dist = 0;
	right_motor_trav_dist = 0;
	left_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist_abs = 0;
	right_motor_trav_dista_abs = 0;
	left_motor_count_prev = 0;
	right_motor_count_prev = 0;

	init_motor_distance();

	EXPECT_EQ(0, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(0, left_motor_trav_dist_abs);
	EXPECT_EQ(0, right_motor_trav_dista_abs);
	EXPECT_EQ(0, left_motor_count_prev);
	EXPECT_EQ(0, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, init_motor_distance_002) {
	left_motor_count = 1;
	right_motor_count = 1;

	left_motor_trav_dist = 1;
	right_motor_trav_dist = 1;
	left_motor_trav_dist_hi_acc = 1;
	right_motor_trav_dist_hi_acc = 1;
	left_motor_trav_dist_abs = 1;
	right_motor_trav_dista_abs = 1;
	left_motor_count_prev = 1;
	right_motor_count_prev = 1;

	init_motor_distance();

	EXPECT_EQ(0, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(0, left_motor_trav_dist_abs);
	EXPECT_EQ(0, right_motor_trav_dista_abs);
	EXPECT_EQ(0, left_motor_count_prev);
	EXPECT_EQ(0, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_001) {
	left_motor_count = 0;
	left_motor_count_prev = 0;
	left_motor_trav_dist_hi_acc = 1;
	left_motor_trav_dist = 1;
	left_motor_trav_dist_abs = 1;

	right_motor_count = 0;
	right_motor_count_prev = 0;
	right_motor_trav_dist_hi_acc = 1;
	right_motor_trav_dist = 1;
	right_motor_trav_dista_abs = 1;

	calc_trav_distance();

	EXPECT_EQ(1, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(1, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(1, left_motor_trav_dist_abs);
	EXPECT_EQ(1, right_motor_trav_dista_abs);
	EXPECT_EQ(0, left_motor_count_prev);
	EXPECT_EQ(0, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_002) {
	left_motor_count = 2;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 0;

	right_motor_count = 2;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 0;

	calc_trav_distance();

	EXPECT_EQ(48, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(48, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(0, left_motor_trav_dist_abs);
	EXPECT_EQ(0, right_motor_trav_dista_abs);
	EXPECT_EQ(2, left_motor_count_prev);
	EXPECT_EQ(2, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_003) {
	left_motor_count = 2;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 0;

	right_motor_count = 2;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 0;

	calc_trav_distance();

	EXPECT_EQ(48, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(48, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(0, left_motor_trav_dist_abs);
	EXPECT_EQ(0, right_motor_trav_dista_abs);
	EXPECT_EQ(2, left_motor_count_prev);
	EXPECT_EQ(2, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_004) {
	left_motor_count = 4;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 0;

	right_motor_count =4;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 0;

	calc_trav_distance();

	EXPECT_EQ(146, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(146, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(1, left_motor_trav_dist);
	EXPECT_EQ(1, right_motor_trav_dist);
	EXPECT_EQ(1, left_motor_trav_dist_abs);
	EXPECT_EQ(1, right_motor_trav_dista_abs);
	EXPECT_EQ(4, left_motor_count_prev);
	EXPECT_EQ(4, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_005) {
	left_motor_count = -2;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 0;

	right_motor_count = -2;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 0;

	calc_trav_distance();

	EXPECT_EQ(-146, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(-146, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(-1, left_motor_trav_dist);
	EXPECT_EQ(-1, right_motor_trav_dist);
	EXPECT_EQ(1, left_motor_trav_dist_abs);
	EXPECT_EQ(1, right_motor_trav_dista_abs);
	EXPECT_EQ(-2, left_motor_count_prev);
	EXPECT_EQ(-2, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_006) {
	left_motor_count = -2;
	left_motor_count_prev = -1;
	left_motor_trav_dist_hi_acc = 0;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 0;

	right_motor_count = -2;
	right_motor_count_prev = -1;
	right_motor_trav_dist_hi_acc = 0;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 0;

	calc_trav_distance();

	EXPECT_EQ(-48, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(-48, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(0, left_motor_trav_dist_abs);
	EXPECT_EQ(0, right_motor_trav_dista_abs);
	EXPECT_EQ(-2, left_motor_count_prev);
	EXPECT_EQ(-2, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_007) {
	left_motor_count = 2;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 1;
	left_motor_trav_dist = 1;
	left_motor_trav_dist_abs = 1;

	right_motor_count = 2;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 1;
	right_motor_trav_dist = 1;
	right_motor_trav_dista_abs = 1;

	calc_trav_distance();

	EXPECT_EQ(49, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(49, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(0, left_motor_trav_dist);
	EXPECT_EQ(0, right_motor_trav_dist);
	EXPECT_EQ(1, left_motor_trav_dist_abs);
	EXPECT_EQ(1, right_motor_trav_dista_abs);
	EXPECT_EQ(2, left_motor_count_prev);
	EXPECT_EQ(2, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_008) {
	left_motor_count = 4;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 1;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 1;

	right_motor_count = 4;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 1;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 1;

	calc_trav_distance();

	EXPECT_EQ(147, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(147, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(1, left_motor_trav_dist);
	EXPECT_EQ(1, right_motor_trav_dist);
	EXPECT_EQ(2, left_motor_trav_dist_abs);
	EXPECT_EQ(2, right_motor_trav_dista_abs);
	EXPECT_EQ(4, left_motor_count_prev);
	EXPECT_EQ(4, right_motor_count_prev);
}

TEST_F(CLC_Module_TravelDistance_UnitTest, calc_trav_distance_009) {
	left_motor_count = 2;
	left_motor_count_prev = 1;
	left_motor_trav_dist_hi_acc = 152;
	left_motor_trav_dist = 0;
	left_motor_trav_dist_abs = 1;

	right_motor_count = 2;
	right_motor_count_prev = 1;
	right_motor_trav_dist_hi_acc = 152;
	right_motor_trav_dist = 0;
	right_motor_trav_dista_abs = 1;

	calc_trav_distance();

	EXPECT_EQ(200, left_motor_trav_dist_hi_acc);
	EXPECT_EQ(200, right_motor_trav_dist_hi_acc);
	EXPECT_EQ(2, left_motor_trav_dist);
	EXPECT_EQ(2, right_motor_trav_dist);
	EXPECT_EQ(1, left_motor_trav_dist_abs);
	EXPECT_EQ(1, right_motor_trav_dista_abs);
	EXPECT_EQ(2, left_motor_count_prev);
	EXPECT_EQ(2, right_motor_count_prev);
}
