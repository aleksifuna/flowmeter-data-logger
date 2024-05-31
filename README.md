# Flow Rate Logger
This project is designed to log the flow rate of a liquid over time, displaying real-time data on an LCD and storing the data on an SD card. The system utilizes an Arduino, a flow sensor, an LCD, an RTC (Real Time Clock), and an SD card module.

## Components
* Arduino (e.g., Arduino Mega 2560)
* Hall effect flow sensor
* LiquidCrystal_I2C display
* DS3231 RTC module
* SD card module
* Push button (for recording control)
* Connecting wires
## Libraries Used
* Wire.h
* LiquidCrystal_I2C.h
* DS3231.h
* SPI.h (Pre-loaded with Arduino)
* SD.h (Pre-loaded with Arduino)
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
```Global Variables
const int chipSelect = 53; - Chip select pin for SD card.
int flowPin = 2; - Pin connected to the flow sensor.
int recBtn = 3; - Pin connected to the recording control button.
double flowRate; - Variable to store the calculated flow rate.
volatile int count; - Counter for the flow sensor pulses.
unsigned long currentTime, cloopTime; - Time variables for calculating flow rate.
volatile byte state = 0; - State variable to control recording.
LiquidCrystal_I2C lcd(0x27, 16, 2); - LCD object.
DS3231 rtc(SDA, SCL); - RTC object.
Setup Function
Initialize pins for flow sensor and button.
Set up interrupts for flow sensor and button.
Initialize LCD and RTC.
Initialize SD card.
Loop Function
Read flow sensor data and calculate flow rate.
Write data to SD card if recording is enabled.
Display data on the LCD.
Function Descriptions
void readFls(): Reads the flow sensor data and calculates the flow rate.
void flow(): ISR for flow sensor to count pulses.
void lcdPrint(): Updates the LCD with current time and flow rate.
void Initialize_SDcard(): Initializes the SD card and creates the log file.
void writeSDcard(): Writes the flow rate data to the SD card if recording is enabled.
void rec(): ISR for the recording control button to toggle the recording state.```

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
