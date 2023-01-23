# Standing desk monitoring with Arduino and Grafana

The standing desk monitoring system helps you get insight into the usage of your standing desk.


![Image of how the system looks](imgs/grafana.jpg)

## Arduino & Grafana

To start, review and follow steps in the **[Grafana DIY IoT repo](https://github.com/grafana/diy-iot)**.

## Hardware

To build this system, you will need:

- **1 [HC-SR04](https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet)** ultrasonic distance sensor
- **1 [ESP32 DEVKIT DOIT](https://randomnerdtutorials.com/getting-started-with-esp32/)** development board
- **4 F-F Dupont cables**
- **1 micro USB cable**
- **1 USB charger**


## Libraries:

- **HCSR04** by Martin Sosic
- **Adafruit Unified Sensor** by Adafruit
- **PrometheusArduino** by Ed Welch (get all dependencies as well)
- **SnappyProto** by Ed Welch

## Software

Download this repo that includes the software for standing monitoring. Update config.h file with your names, passwords and API keys. Upload software to your board using Arduino IDE.

## Setting up 

When it comes to setting up standing desk monitoring, you have 2 options:

### Place sensor on the desk facing the ceiling
Place your [HC-SR04](https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet) ultrasonic distance sensor on standing desk and secure safely. The sensor should point to the ceiling and no code change is necessary, besides setting height of the room. 


### Place sensor under the desk facing the floor
Place your [HC-SR04](https://components101.com/sensors/ultrasonic-sensor-working-pinout-datasheet) ultrasonic distance sensor under the standing desk and secure safely. In this case, it is necessary to update the code and use the measured height directly.