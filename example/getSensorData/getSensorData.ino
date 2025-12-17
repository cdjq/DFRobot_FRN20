#include "DFRobot_FRN20.h"
DFRobot_FRN20 frn20;
void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.print("frn20 init...");
  while (frn20.begin() != 0) {
    Serial.print("failed,Not found frn20!");
  }
  Serial.println("successed");

  if (frn20.readParams()) {
    Serial.print("Unit: ");
    Serial.print(frn20.params.unit);
    Serial.println("  L/min");

    Serial.print("Range: ");
    Serial.print(frn20.params.range, HEX);
    Serial.println("  L/min");

    Serial.print("Offset: ");
    Serial.println(frn20.params.offset);

    Serial.print("Medium Coefficient: ");
    Serial.println(frn20.params.mediumCoeff);

    Serial.print("Output Voltage Lower Limit: ");
    Serial.print(frn20.params.voutMinmV);
    Serial.println("  mV");

    Serial.print("Output Voltage Upper Limit: ");
    Serial.print(frn20.params.voutMaxmV);
    Serial.println("  mV");

    Serial.print("Product ID: ");
    Serial.println((char *)frn20.params.productId);

    Serial.print("CRC: ");
    Serial.println(frn20.params.crc, HEX);
  } else {
    Serial.println("Failed, readParams error!");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  frn20.readRawFlowData();
  frn20.readMassFlowData();

  Serial.print("Raw Value: ");
  Serial.print(frn20.rawFlowData);
  Serial.println(" SLM");

  Serial.print("Flow Value: ");
  Serial.print(frn20.massFlowData);
  Serial.println(" SLM");

  delay(2000);
}
