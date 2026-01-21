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

  if frn20.read_params():
    print("readParams Successed")
  else:
    print("Failed, read_params error!")


def loop():
  frn20.read_raw_flow_data()
  frn20.read_mass_flow_data()
  print(f"Flow Value: {frn20.mass_flow_data} SLM")
  time.sleep(0.5)


setup()
loop()
