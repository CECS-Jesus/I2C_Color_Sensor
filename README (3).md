
# I2C Color Sensor

## Introduction
This project interfaces with the TCS34725 RGB Color Sensor via I2C communication, implemented on the Arm-Cortex M4 (TM4C123) platform for real-time color analysis. It leverages the microcontroller's capabilities to configure I2C in master mode at 100kHz, ensuring precise color detection and feedback through dynamic onboard LED adjustments and serial output.


## Requirements
- LaunchPad
- TCS34725 RGB Color Sensor
- Serial terminal application (e.g., tera term, Putty)
- R,G,B Colored Paper


## Setup & Configuration

### Bluetooth Module
- Upload the compiled program to the TM4C123 microcontroller.
- Open your Serial Terminal software and connect to the TM4C123's serial port.
- The onboard LED will change colors based on the detected color values from the TCS34725 sensor.
- Color readings and analysis results will be outputted to the Serial Terminal..




