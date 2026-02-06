# DFRobot_FRN20

- [English Version](./README.md)

## 概述
FRn20系列流量传感器采用MEMS热式原理对管路气体介质进行流量监测。本产品基于FR20系列升级，产品零点稳定性和全量程信号稳定性显著提高，适用于工业过程检测。 

# 产品链接: https://www.dfrobot.com.cn/

```text
SKU: SEN0630
```

## 目录
* [概要](#概要)
* [安装](#安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概要
本 Python 库为 FRN20 在 Raspberry Pi 上的驱动实现，提供 I2C 通信、参数读取与流量数据读取接口，便于快速集成到上层应用。

## 安装
1. 克隆仓库到树莓派：
```bash
git clone https://github.com/DFRobot/DFRobot_FRN20.git
```

2. 进入 Python 示例目录：
```bash
cd DFRobot_FRN20/python/raspberrypi
```

3. 安装依赖：
```bash
pip install smbus2
```

4.例如，要执行getSensorData.py例程，你需要输入:

```bash
python getSensorData.py
```

## 方法
```python
def begin(self):
    """
    初始化 I2C 并阻塞直到成功读取设备参数
    @return 1 成功，-1 I2C 初始化失败
    """

def read_mass_flow_data(self):
    """
    读取质量流量，结果存储在 `self.mass_flow_data`
    @return 1 成功，0 失败
    """
```

## 兼容性
| 主板型号           | 运行良好 | 未测试 |
|-------------------|:-------:|:-----:|
| Raspberry Pi 2    |         |   √   |
| Raspberry Pi 3    |         |   √   |
| Raspberry Pi 4    |    √    |       |

## 历史
- 2026/01/26 - 1.0.0 版本


## 创作者
Written by PLELES (PLELES@dfrobot.com),2026.(Welcome to our [website](https://www.dfrobot.com/))