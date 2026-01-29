# DFRobot_FRN20

- [English Version](./README.md)

## 概述
FRN20 是一款高精度流量传感器，适用于精确测量气体或液体流速。该模块通过 I2C 接口通信，具有出厂校准与温度补偿，能在多种环境下保持测量稳定性。


##
产品链接: https://www.dfrobot.com/
```text
SKU: SEN0630
```


## 目录
## 目录
- [概要](#概要)
- [安装](#安装)
- [方法](#方法)
- [兼容性](#兼容性)
- [硬件连接](#硬件连接)
- [常见问题](#常见问题)
- [历史](#历史)
- [创作者](#创作者)

## 概要
本 Arduino/C++ 库为 FRN20 传感器提供驱动支持，包含读取原始/转换后流量数据以及加载设备参数（量程、偏移、转换系数）等功能。

## 安装
1. 将本库复制到 Arduino 的 `libraries` 目录。
2. 在工程中包含头文件：

```cpp
#include <DFRobot_FRN20.h>
```

## 方法（Arduino C++ API）
```cpp
/**
 * @fn DFRobot_FRN20
 * @brief 构造函数，传入 I2C 总线对象（缺省 &Wire）
 */
DFRobot_FRN20(TwoWire *pWire = &Wire);

/**
 * @fn begin
 * @brief 初始化 I2C 并检测设备
 * @return byte 返回 `Wire.endTransmission()` 的结果（0 表示成功）
 */
byte begin(void);
/**
 * @fn readMassFlowData
 * @brief 使用加载的参数将原始值转换为质量流量
 * @return uint8_t 1 = 成功，0 = 失败
 */
uint8_t readMassFlowData(void);
```

## 兼容性
| Platform | Work Well | Work Wrong | Untested | Remarks |
|----------|:---------:|:----------:|:--------:|---------|
| Arduino UNO |  |√| | |
| Arduino MEGA2560 |  | |√| |
| Arduino Leonardo |  | | √ | |
| FireBeeetle-M0 |  | | √ | |
| FireBeeetle-ESP32-E |  √| |  | |
| ESP8266 |  |√  | | |
| Micro:bit |  | | √ | |

## 历史
- 2026/01/26 - 1.0.0 版本

## 创作者
作者：PLELES (PLELES@dfrobot.com)，2026-01-26
[DFRobot 官网](https://www.dfrobot.com/)
