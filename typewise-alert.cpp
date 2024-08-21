#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, int lowerLimit, int upperLimit) {
  if (value < lowerLimit) {
    return TOO_LOW;
  }
  if (value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

struct TemperatureLimits {
  int lowerLimit;
  int upperLimit;
};

const TemperatureLimits coolingTypeLimits[] = {
    {0, 35},  // PASSIVE_COOLING
    {0, 45},  // HI_ACTIVE_COOLING
    {0, 40}   // MED_ACTIVE_COOLING
};

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  TemperatureLimits limits = coolingTypeLimits[coolingType];
  return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

struct EmailMessage {
  const char* subject;
  const char* body;
};

// Array mapping BreachType to the corresponding email message
const EmailMessage emailMessages[] = {
    {"Temperature Normal", ""},                    // NORMAL
    {"Temperature Too Low", "Hi, the temperature is too low"}, // TOO_LOW
    {"Temperature Too High", "Hi, the temperature is too high"} // TOO_HIGH
};

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType != NORMAL) { // Only send email if there's a breach
    printf("To: %s\n", recepient);
    printf("%s\n", emailMessages[breachType].body);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch (alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}
