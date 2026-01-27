#include "DFRobot_FRN20.h"
DFRobot_FRN20 frN20;
void          setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.print("FRN20 init...");
  while (frN20.begin() != 0) {
    Serial.println("failed,Not found FRN20!");
  }
  Serial.println("successed");
}

void loop()
{
  frN20.readMassFlowData();
  Serial.print("Flow Value: ");
  Serial.print(frN20.massFlowData);
  Serial.println(" SLM");

  delay(500);
}