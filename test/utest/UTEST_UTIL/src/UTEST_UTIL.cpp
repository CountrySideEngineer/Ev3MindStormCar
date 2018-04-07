//============================================================================
// Name        : UTEST_UTIL.cpp
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

extern void init_buff(int size, char *buff, char val);
extern int limit_int(int value, int min, int max);
#ifdef __cplusplus
}
#endif

char buff[100];

TEST(util, init_buff_001) {
	int index = 0;

	for (index = 0; index < 100; index++) {
		buff[index] = 0;
	}

	init_buff(0, (char *)(&buff), 0xFF);

	EXPECT_EQ(0, buff[0]);
	EXPECT_EQ(0, buff[99]);
}

TEST(util, init_buff_002) {
	int index = 0;

	for (index = 0; index < 100; index++) {
		buff[index] = 0;
	}

	init_buff(100, (char *)(&buff), 0xFF);

	EXPECT_EQ((char)0xFF, buff[0]);
	EXPECT_EQ((char)0xFF, buff[99]);
}

TEST(util, limit_int_001) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 100;
	min = 99;
	max = 101;
	expected = 100;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_002) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 99;
	min = 99;
	max = 100;
	expected = 99;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_003) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 98;
	min = 99;
	max = 100;
	expected = 99;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_004) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 100;
	min = 99;
	max = 100;
	expected = 100;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_005) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 101;
	min = 99;
	max = 100;
	expected = 100;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_006) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 101;
	min = 99;
	max = 101;
	expected = 101;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_007) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 102;
	min = 99;
	max = 101;
	expected = 101;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_008) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 99;
	min = 99;
	max = 101;
	expected = 99;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_009) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 98;
	min = 99;
	max = 101;
	expected = 99;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}

TEST(util, limit_int_010) {
	int value;
	int min;
	int max;
	int expected;
	int actual;

	value = 98;
	min = 100;
	max = 100;
	expected = 0;

	actual = limit_int(value, min, max);

	EXPECT_EQ(expected, actual);
}
