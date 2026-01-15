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

  if (frN20.readParams()) {
    Serial.print("Unit: ");
    Serial.print(frN20.params.unit);
    Serial.println("  L/min");

    Serial.print("Range: ");
    Serial.print(frN20.params.range, HEX);
    Serial.println("  L/min");

    Serial.print("Offset: ");
    Serial.println(FRN20.params.offset);

    Serial.print("Medium Coefficient: ");
    Serial.println(FRN20.params.mediumCoeff);

    Serial.print("Output Voltage Lower Limit: ");
    Serial.print(FRN20.params.voutMinmV);
    Serial.println("  mV");

    Serial.print("Output Voltage Upper Limit: ");
    Serial.print(FRN20.params.voutMaxmV);
    Serial.println("  mV");
  } else {
    Serial.println("Failed, readParams error!");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  FRN20.readRawFlowData();
  FRN20.readMassFlowData();

  Serial.print("Raw Value: ");
  Serial.print(FRN20.rawFlowData);
  Serial.println(" SLM");

  Serial.print("Flow Value: ");
  Serial.print(FRN20.massFlowData);
  Serial.println(" SLM");

  delay(2000);
}