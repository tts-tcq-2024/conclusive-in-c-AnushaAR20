#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
EXPECT_EQ(inferBreach(12, 10, 20), NORMAL);
EXPECT_EQ(inferBreach(9, 10, 20), TOO_LOW);
EXPECT_EQ(inferBreach(21, 10, 20), TOO_HIGH);
EXPECT_EQ(inferBreach(21, 10, 21), NORMAL);

}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachForPassiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 35), NORMAL);
}
