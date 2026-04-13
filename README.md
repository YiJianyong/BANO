# 软硬件系统功能

+ 本研究旨在搭建一个基于Bonsai 和Arduino 的开源行为学软硬件系统，用于小鼠声音线索观察型恐惧学习研究。
+ 平台能够实现复杂声音刺激的编程、试次随机化、视频录制、激光器和声音刺激的输出控制， 并且能够与其他外部设备进行通讯和事件同步，为后续神经电生理信号和行为分析提供了高质量的数据。

# 软硬件依赖  

+ [Bonsai](https://bonsai-rx.org/docs/articles/installation.html)：版本>= 2.7.0
+ OpenEphys：版本>= 0.6.5
+ [Arduino IDE](https://www.arduino.cc/en/software/): 版本>= 2.0.0
+ [Arduino IDE语法简介](http://www.taichi-maker.com/homepage/reference-index/arduino-code-reference/)
+ Arduino板：版本 UNO R3


# 系统设备的参考价格 

| 设备名称 (Device name) | 供应商 (Supplier) | 参考价格 (Reference price) |
| :--- | :--- | :--- |
| BASLER acA1440-220um | BASLER | ¥3,082.93 |
| Arduino UNO R3 | Italian Arduino | ¥112.00 |
| Electrical stimulator | ProBeCare | ¥1,500.00 |
| Tweeter: XT25SC50-04 | Peerless | ¥450.00 |
| Dupont line | RISYM | ¥5.00 |
| Behavioral box | Custom acrylic sheets | ¥300.00 |
| DC battery | TIANWEI | ¥33.00 |
| **总计 (Total)** | | **¥5,482.93** |



# 视频追踪相机的主要设置参数

| 参数名称 (Parameter) | 参数值 (Value) |
| :--- | :--- |
| **曝光时间 (Exposure time)** | 7000 us |
| **启用采集帧率 (Enable acquisition frame rate)** | Yes |
| **采集帧率 (Acquisition frame rate)** | 30 Hz |
| **采集猝发帧率 (Acquisition burst frame rate)** | 1 Hz |
| **线路选择器 (Line selector)** | Line 2 |
| **线路模式 (Line mode)** | Output |
| **线路源 (Line source)** | Exposure active |
| **线路反转器 (Line inverter)** | Yes |



# Arduino R3板的主要参数

| 参数项目 (Parameter) | 规格详情 (Specification) |
| :--- | :--- |
| **微控制器 (Microcontroller)** | ATmega328P |
| **工作电压 (Working voltage)** | 5 V |
| **输入电压 - 推荐 (Input voltage Recommend)** | 7 - 12 V |
| **输入电压 - 极限 (Input voltage Limit)** | 6 - 20 V |
| **数字输入/输出引脚 (Digital I/O Pins)** | 14 |
| **PWM 引脚 (PWM Pins)** | 6 |
| **模拟输入引脚 (Analog Input Pins)** | 6 |
| **I/O 引脚直流电流 (DC Current per I/O Pin)** | 20 mA |
| **3.3V 引脚电流 (3.3V Pin Current)** | 50 mA |
| **闪存 (Flash Memory)** | 32 KB (ATmega328P) |
| **静态存储器 (SRAM)** | 2 KB (ATmega328P) |
| **电可擦可编程只读存储器 (EEPROM)** | 1 KB (ATmega328P) |
| **板载 LED 引脚 (Built-in LED Pin)** | 13 |
| **时钟频率 (Clock Speed)** | 16 MHz |
| **尺寸 (Dimensions)** | 68.6 mm (长) × 53.4 mm (宽) |
| **重量 (Weight)** | 25 g |

