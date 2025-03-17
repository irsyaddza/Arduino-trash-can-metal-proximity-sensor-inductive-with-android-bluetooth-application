# 🤖 Arduino-trash-can-metal-proximity-sensor-inductive-with-android-bluetooth-application

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

## 📋 Overview

This project implements an automated metal detection system using Arduino. When metal is detected, a servo motor activates and a counter increments. The system features a digital display to show the count, LED indicators, and Bluetooth connectivity for remote control and monitoring.

## ✨ Features

- **Real-time Metal Detection**: Automatically detects when metal objects come near the proximity sensor
- **Servo Activation**: Servo motor automatically opens and closes when metal is detected
- **Digital Counter**: TM1637 display shows the number of metal objects detected
- **LED Indicators**: Visual indications for metal detection and servo status
- **Bluetooth Control**: Remote operation via Bluetooth with commands to:
  - Open the servo
  - Close the servo
  - Reset the counter
- **Serial Monitoring**: Live status updates through the serial monitor

## 🔌 Hardware Requirements

- Arduino board (Uno or similar)
- Proximity Sensor Inductive
- Servo motor
- TM1637 4-digit 7-segment display
- HC-05/HC-06 Bluetooth module
- 2 LEDs (for metal and servo indicators)
- Resistors for LEDs
- Power supply 12V 5A

## 📲 Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| Servo Motor | 9 |
| Proximity Sensor | 2 |
| TM1637 Clock | 5 |
| TM1637 Data | 4 |
| Metal Indicator LED | 6 |
| Servo Indicator LED | 7 |
| Bluetooth RX | 10 |
| Bluetooth TX | 11 |

## 📚 Libraries Used

- **Servo.h**: For controlling the servo motor
- **TM1637Display.h**: For interfacing with the 7-segment display
- **SoftwareSerial.h**: For Bluetooth communication

## 📡 Bluetooth Commands

| Command | Action |
|---------|--------|
| '1' | Open the servo |
| '2' | Close the servo |
| 'R' or 'r' | Reset the counter |

## 💻 Installation

1. Connect the hardware components according to the pin configuration
2. Install the required libraries via Arduino Library Manager:
   - Servo
   - TM1637Display
   - SoftwareSerial (included with Arduino IDE)
3. Upload the code to your Arduino board
4. Connect to the Bluetooth module using a terminal app or custom mobile application

## 🚀 How It Works

1. When a metal object is detected by the proximity sensor, the system:
   - Turns on the metal indicator LED
   - Opens the servo (rotates to 90 degrees)
   - Increments the counter on the display
   - Sends status updates via Serial and Bluetooth
   
2. When the metal object is removed:
   - The metal indicator LED turns off
   - The servo closes (returns to 0 degrees)
   - Status updates are sent via Serial and Bluetooth

3. The counter keeps track of the total number of detections since power-on or last reset

## 📱 Mobile Control

You can control the system remotely using any Bluetooth terminal app:

## 🛠️ Customization

The code can be easily modified for various applications:
- Adjust the servo angle by changing the values in the `openServo()` and `closeServo()` functions
- Modify the delay time after metal detection by changing the value in the `delay()` function
- Adjust the display brightness by changing the value in `display.setBrightness()`

## 🔍 Troubleshooting

- **Servo not moving**: Check power supply and servo connections
- **No detection**: Verify proximity sensor wiring and sensitivity
- **Display issues**: Ensure proper connections to CLK and DIO pins
- **Bluetooth not connecting**: Check baud rate settings and module power

## 👨‍💻 Author

irsyaddza - [Github](https://github.com/irsyaddza)

## 🙏 Acknowledgements

- Thanks to all contributors and testers
- Libraries used in this project
- Inspiration for the design

---

⭐️ If you found this project helpful, please give it a star on GitHub! ⭐️
