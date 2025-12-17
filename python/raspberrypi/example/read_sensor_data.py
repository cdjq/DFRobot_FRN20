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
    print(f"Unit: {frn20.params.unit}  L/min")
    print(f"Range: {hex(frn20.params.range)}  L/min")
    print(f"Offset: {frn20.params.offset}")
    print(f"Medium Coefficient: {frn20.params.mediumCoeff}")
    print(f"Output Voltage Lower Limit: {frn20.params.voutMinmV}  mV")
    print(f"Output Voltage Upper Limit: {frn20.params.voutMaxmV}  mV")
    product_id = ''.join([chr(b) for b in frn20.params.productId if b != 0])
    print(f"Product ID: {product_id}")
    print(f"CRC: {hex(frn20.params.crc)}")
  else:
    print("Failed, readParams error!")


def loop():
  frn20.read_raw_flow_data()
  frn20.read_mass_flow_data()
  print(f"Raw Value: {frn20.rawFlowData} SLM")
  print(f"Flow Value: {frn20.massFlowData} SLM")
  time.sleep(2)


setup()

loop()
