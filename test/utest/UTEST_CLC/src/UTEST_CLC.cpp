//============================================================================
// Name        : UTEST_CLC.cpp
// Author      : CountrySideEngineer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "gtest/gtest.h"
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

int16_t distance_sensor_value;

extern int16_t distance_average_value;

extern void init_distance_average(void);
extern void calc_distance_average(void);

#ifndef DISTANCE_AVERAGE_BUF_SIZE
#define DISTANCE_AVERAGE_BUF_SIZE	(3)
#endif

#ifdef __cplusplus
}
#endif

class CLC_Module_UnitTes: public ::testing::Test {
	virtual void SetUp(void) {
		init_distance_average();
		distance_sensor_value = 0;
		distance_average_value = 0;
	}

	virtual void TearDown(void) {}
};

TEST_F(CLC_Module_UnitTes, init_distance_averate_001) {
	distance_sensor_value = 1;
	calc_distance_average();

	distance_sensor_value = 2;
	calc_distance_average();

	distance_sensor_value = 3;
	calc_distance_average();

	init_distance_average();

	EXPECT_EQ(0, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_001) {
	distance_sensor_value = 3;

	calc_distance_average();

	EXPECT_EQ(1, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_002) {
	distance_sensor_value = 3;
	calc_distance_average();

	distance_sensor_value = 6;
	calc_distance_average();

	EXPECT_EQ(3, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_003) {
	distance_sensor_value = 3;
	calc_distance_average();

	distance_sensor_value = 6;
	calc_distance_average();

	distance_sensor_value = 9;
	calc_distance_average();

	EXPECT_EQ(6, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_004) {
	calc_distance_average();
	calc_distance_average();
	calc_distance_average();

	EXPECT_EQ(0, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_005) {
	distance_sensor_value = 1;
	calc_distance_average();

	EXPECT_EQ(0, distance_average_value);
}

TEST_F(CLC_Module_UnitTes, calc_distance_average_006) {
	distance_sensor_value = 2;
	calc_distance_average();

	EXPECT_EQ(0, distance_average_value);
}
