#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
EXPECT_EQ(inferBreach(12, 10, 20), NORMAL);
EXPECT_EQ(inferBreach(9, 10, 20), TOO_LOW);
EXPECT_EQ(inferBreach(21, 10, 20), TOO_HIGH);
EXPECT_EQ(inferBreach(21, 10, 21), TOO_HIGH);

}
