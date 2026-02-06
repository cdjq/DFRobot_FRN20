'''
@file read_sensor_data.py
@brief read sensor data demo - Read mass flow data from DFRobot_FRN20.
@copyright   Copyright (c) 2026 DFRobot Co.Ltd (http://www.dfrobot.com)
@license     The MIT license (MIT)
@author [PLELES] (https://github.com/PLELES)
@version  V1.0
@date  2026-01-26
'''
import time
import sys

sys.path.append("../")
from DFRobot_FRN20 import DFRobot_FRN20

frn20 = DFRobot_FRN20()


def setup():
  print("FRN20 init...")

  while frn20.begin() != 1:
    print("failed, Not found FRN20!")
  print("successed")
  # read_params is handled inside begin()
  print("readParams handled inside begin()")


def loop():
  frn20.read_mass_flow_data()
  print(f"Flow Value: {frn20.mass_flow_data} SLM")
  time.sleep(0.5)

if __name__ == "__main__":
  setup()
  try:
    while True:
      loop()
  except KeyboardInterrupt:
    print("Program stopped")
