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

TEST(TypeWiseAlertTestSuite, ClassifyTemperatureBreachWithInvalidInputs) {
  // Assuming the CoolingType enum has valid values within 0 to 2
  //EXPECT_EQ(classifyTemperatureBreach(static_cast<CoolingType>(-1), 25), NORMAL); // Invalid cooling type
  EXPECT_EQ(classifyTemperatureBreach(static_cast<CoolingType>(3), 25), NORMAL);  // Invalid cooling type
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

TEST(TypeWiseAlertTestSuite, DoesNotSendEmailForNormalBreach) {
  // Capturing the standard output to check the output
  testing::internal::CaptureStdout();
  sendToEmail(NORMAL);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, "");  // No output expected for NORMAL
}

TEST(TypeWiseAlertTestSuite, SendsCorrectControllerMessageForTooLowBreach) {
  // Capture the standard output to check the output
  testing::internal::CaptureStdout();
  sendToController(TOO_LOW);
  std::string output = testing::internal::GetCapturedStdout();

  // Expected output format: header followed by breach type
  EXPECT_EQ(output, "feed : 1\n");
}

TEST(TypeWiseAlertTestSuite, SendsCorrectControllerMessageForTooHighBreach) {
  // Capture the standard output to check the output
  testing::internal::CaptureStdout();
  sendToController(TOO_HIGH);
  std::string output = testing::internal::GetCapturedStdout();

  // Expected output format: header followed by breach type
  EXPECT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, SendsCorrectControllerMessageForNormalBreach) {
  // Capture the standard output to check the output
  testing::internal::CaptureStdout();
  sendToController(NORMAL);
  std::string output = testing::internal::GetCapturedStdout();

  // Expected output format: header followed by breach type
  EXPECT_EQ(output, "feed : 0\n");
}

// TEST(TypeWiseAlertTestSuite, SendToEmailBoundaryCases) {
//   // No output should occur for a normal condition, even if enum value is on the boundary
//   testing::internal::CaptureStdout();
//   sendToEmail(static_cast<BreachType>(0)); // NORMAL is 0
//   std::string output = testing::internal::GetCapturedStdout();
//   EXPECT_EQ(output, ""); // No output expected for NORMAL

//   // Handling unexpected enum values
//   testing::internal::CaptureStdout();
//   sendToEmail(static_cast<BreachType>(-1)); // Invalid breach type
//   output = testing::internal::GetCapturedStdout();
//   EXPECT_EQ(output, ""); // No output expected for invalid enum values

//   testing::internal::CaptureStdout();
//   sendToEmail(static_cast<BreachType>(3)); // Invalid breach type
//   output = testing::internal::GetCapturedStdout();
//   EXPECT_EQ(output, ""); // No output expected for out-of-bound enum values
// }

