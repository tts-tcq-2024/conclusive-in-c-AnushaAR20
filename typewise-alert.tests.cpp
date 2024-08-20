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
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachForHiActiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreachForMedActiveCooling) {
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 30), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40), NORMAL);
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, SendsCorrectEmailForTooLowBreach) {
  // Capturing the standard output to check the output
  testing::internal::CaptureStdout();
  sendToEmail(TOO_LOW);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("To: a.b@c.com"), std::string::npos);
  EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos);
}

TEST(TypeWiseAlertTestSuite, SendsCorrectEmailForTooHighBreach) {
  // Capturing the standard output to check the output
  testing::internal::CaptureStdout();
  sendToEmail(TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("To: a.b@c.com"), std::string::npos);
  EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos);
}
