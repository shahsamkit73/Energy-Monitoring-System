# Energy-Monitoring-System

Energy is the most salient part of our life nowadays. It has also been pivotal aspect for household as well as industrial usage. Managing the energy efficiently and conserving it smartly for appliances is very much essential. In addition to this, a lot of research work has been carried out in developing a robust system pertaining to save energy. Industrial Internet of Things (IIoT) has outranked all other technologies and still have been developing in leaps and bounds which gives liberty of data observation at our palm using any radio communication device. Consequently, in this growing technological epoch, industrial data acquisition and monitoring is now the major matter of concern and demand. Hence, the prime goal of this IoT enabled system is to render commercial data to be processed intelligently through wireless communication and further cloud computing. This system uses esp32 with MODBUS communication protocol and projects the data fetched by sensors on the sign up portal by furnishing ease and rapidity of data communication.

### Dependencies & Libraries ###
* #### Energy Meter - [DPM C501L](https://www.deltaww.com/Products/CategoryListT1.aspx?CID=060404&PID=4079&hl=en-US&Name=DPM-C501L)
* #### ESP32 IoT Develoment Board
* #### MODBUS coommunication module - [RS-485](https://www.amazon.in/Generic-Max485-Rs-485-Arduino-Raspberry/dp/B01EE3N83Y)
* #### Arduino Environment - [ArduinoIDE](https://www.arduino.cc/en/software)
* #### MODBUS library - [ModbusMaster](https://github.com/4-20ma/ModbusMaster)
* #### MODBUS Software - [Simply Modbus](https://www.simplymodbus.ca/RTUmaster.htm)

### How to install ESP32 in Arduino IDE :
1. In arduino IDE, go to **File > Preference**
2. Enter **https://dl.espressif.com/dl/package_esp32_index.json** into the **_Additional Board Manager URLs_** and click **OK**
3. Go to **Tools > Board > Boards Manager** and open Boards Manager
4. Search for **ESP32** and press install for the **_esp32 by Espressif Systems_**
5. To verify whether the esp32 board has been successfully installed, go to **Tools > Board** and select **_ESP32 Dev Module_**

### How to install _`ModbusMaster.h`_ in Arduino IDE :
* **Method 1**
1. Go to **Tools > Board > Boards Manager** and open Boards Manager
2. Search for **Modbus** and press install **_ModbusMaster_**

* **Method 2**
1. Go to **My Computer > Documents > Arduino > Libraries** and paste the unzipped folder named [ModbusMaster](https://github.com/4-20ma/ModbusMaster) downloaded from github 

### Circuit Connection ###

<p align="center">
  <img width="3000" height="500" src="https://user-images.githubusercontent.com/43854300/99538313-cf234c00-29d2-11eb-8581-36d8e25af3e4.PNG">
</p>

| ESP32  | RS485 | Energy  Meter |
| :-------------: | :-------------: | :-------------: |
| GPIO 3 (RX0) | RO | - |
| GPIO 1 (TX0) | DI | - |
| GPIO 4 | DE | - |
| GPIO 15 | RE | - |
| 3.3v | VCC | - |
| GND | GND | - |
| - | A | D+ |
| - | B | D- |

#### Modbus Library Function ####

Discrete Coils/Flags
* **0x01** - Read Coils 
* **0x02** - Read Discrete Inputs
* **0x05** - Write Single Coil
* **0x0F** - Write Multiple Coils 

Registers
* **0x03** - Read Holding Registers
* **0x04** - Read Input Registers
* **0x06** - Write Single Register
* **0x10** - Write Multiple Registers
* **0x16** - Mask Write Register
* **0x17** - Read Write Multiple Registers

### Output ###
~~~
For example,

Phase A Voltage = 238.45 V
Phase A Current = 5.314 A
Phase A Power = 35.44 W
Energy = 42.5 kWh
Second = 7
~~~

> **IMPORTANT: `Baud rate` and `Slave ID` of you device should be as same as mentioned in the code.**
