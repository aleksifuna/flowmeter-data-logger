# Flow Rate Logger
This project is designed to log the flow rate of a liquid over time, displaying real-time data on an LCD and storing the data on an SD card. The system utilizes an Arduino, a flow sensor, an LCD, an RTC (Real Time Clock), and an SD card module.

## Components
1. Arduino (e.g., Arduino Mega 2560)
2. Hall effect flow sensor
3. LiquidCrystal_I2C display
4. DS3231 RTC module
5. SD card module
6. Push button (for recording control)
7. Connecting wires
## Libraries Used
1. Wire.h
2. LiquidCrystal_I2C.h
3. DS3231.h
4. SPI.h (Pre-loaded with Arduino)
5. SD.h (Pre-loaded with Arduino)
## Circuit Connections
1. Flow sensor:
* Signal pin to Arduino digital pin 2
* VCC and GND to Arduino 5V and GND respectively
2. LCD (I2C):
* SDA to Arduino SDA
* SCL to Arduino SCL
* VCC and GND to Arduino 5V and GND respectively
3. RTC (DS3231):
* SDA to Arduino SDA
* SCL to Arduino SCL
* VCC and GND to Arduino 5V and GND respectively
4. SD Card Module:
* CS pin to Arduino pin 53
* SCK, MOSI, MISO to corresponding Arduino SPI pins
* VCC and GND to Arduino 5V and GND respectively
5. Push Button:
* One side to Arduino digital pin 3
* Other side to GND
## Installation
* Connect the components as described in the circuit connections section.
* Install the required libraries (Wire.h, LiquidCrystal_I2C.h, DS3231.h, SPI.h, and SD.h) if they are not already available in your Arduino IDE.
## Code Overview
```
Global Variables
int flowrate_sensor_pin = 2; - Pin connected to the flow sensor.
volatile int count; - Counter for the flow sensor pulses.
unsigned long cloopTime; - Time variable for calculating flow rate.
volatile byte state = 0; - State variable to control recording.
LiquidCrystal_I2C lcd(0x27, 16, 2); - LCD object.
DS3231 rtc(SDA, SCL); - RTC object.
Setup Function
void setup(): 
Sets up necessary resources.
Initializes pins for flow sensor and button.
Sets up interrupts for flow sensor and button.
Initializes LCD and RTC.
Initializes SD card.

Loop Function
void loop():
Main program that runs in a loop.
Reads flow sensor data and calculates flow rate.
Writes data to SD card if recording is enabled.
Displays data on the LCD.

Function Descriptions
int read_flowrate():
Reads the flow sensor data and calculates the flow rate.
Returns the flow rate.
void flow():
ISR for flow sensor to count pulses.
void lcd_print(int flowrate):
Updates the LCD with current time and flow rate.
Takes flowrate as a parameter.
void Initialize_SDcard():
Initializes the SD card and creates the log file.
void write_SDcard(int flowrate):
Writes the flow rate data to the SD card if recording is enabled.
Takes flowrate as a parameter.
void rec():
ISR for the recording control button to toggle the recording state.

```

## Usage
1. Connect all components as per the circuit connections.
2. Upload the code to the Arduino.
3. Ensure the SD card is inserted properly.
4. The system will display the current time and flow rate on the LCD.
5. Press the button to start or stop recording data to the SD card. The letter "L" will appear on the LCD when recording is active.
## Notes
1. The flow rate is displayed in liters per minute (LPM).
2. Data is logged in the "LoggerCD.txt" file on the SD card with the format "Time, Flowrate(LPM)".
3. Make sure the SD card is properly formatted and inserted before powering up the system.

Acknowledgments
Arduino
Libraries: Wire, LiquidCrystal_I2C, DS3231, SPI, SD
For any issues or contributions, feel free to open an issue or pull request on the project's repository.
