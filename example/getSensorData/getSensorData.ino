/*!
 * @file getSensorData.ino
 * @brief Example of reading sensor data from DFRobot_FRN20.
 * @copyright  Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PLELES] (feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2026-1-21
 * @url https://github.com/DFRobot/DFRobot_FRN20
 */
#include "DFRobot_FRN20.h"
DFRobot_FRN20 frN20;
void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("");
  Serial.print("FRN20 init...");
  while (frN20.begin() != 0) {
    
    Serial.println("failed,Not found FRN20!");
    delay(500);
  }
  Serial.println("");
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