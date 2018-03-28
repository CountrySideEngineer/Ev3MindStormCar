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
extern int8_t distance_safe_state;
extern const int8_t CAR_SAFE_STATE_SAFE;
extern const int8_t CAR_SAFE_STATE_ATTN;
extern const int8_t CAR_SAFE_STATE_DANG;
extern const int8_t CAR_SAFE_STATE_STOP;

#ifdef __cplusplus
extern "C" {
#endif
extern void judge_dist_safe(void);
extern void judge_distance_safe_change(void);
extern void init_dist_safe(void);
#ifdef __cplusplus
}
#endif

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
