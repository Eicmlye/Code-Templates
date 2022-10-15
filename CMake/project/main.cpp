#include <iostream>
#include "config.h"
#include <gtest/gtest.h>

#ifdef USE_func
    #include "func.hpp"
#endif

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}