
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SPI.h> //Library for SPI communication (Pre-Loaded into Arduino)
#include <SD.h> //Library for SD card (Pre-Loaded into Arduino)


int flowrate_sensor_pin = 2;
volatile int count;
unsigned long cloopTime;
volatile byte state = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  rtc(SDA, SCL);

/**
 * setup - sets the the necessary resources needed.
*/
void setup()
{
  int record_button = 3;

  pinMode(flowrate_sensor_pin,INPUT);
  digitalWrite(flowrate_sensor_pin, HIGH);
  pinMode(record_button,INPUT);
  attachInterrupt(digitalPinToInterrupt(flowrate_sensor_pin), flow, RISING);
  attachInterrupt(digitalPinToInterrupt(record_button), rec, RISING);
  lcd.begin();
  lcd.backlight();
  rtc.begin();
  Initialize_SDcard();


  }
/**
 * loop - main program that runs on a loop
*/
void loop()
{
  int flow_rate;

  flow_rate = read_flowrate();
  write_SDcard(flow_rate);
  lcd_print(flow_rate);

}

/**
 * read_flowrate - reads the flowrate from the hall sensor
 *
 * Return: flowrate
*/
int read_flowrate()
{
  int flow_rate;
  unsigned long current_time;

  current_time = millis();
   // Every second, calculate and print litres/hour
   if (current_time >= (cloopTime + 1000))
   {
      detachInterrupt(digitalPinToInterrupt(flowrate_sensor_pin));
      flow_rate = (((1000.0/(current_time-cloopTime))*count) / 0.2)/1.2;
      cloopTime = current_time; // Updates cloopTime
      count = 0; // Reset Counter
      attachInterrupt(digitalPinToInterrupt(flowrate_sensor_pin), flow, RISING);

   }

   return flow_rate;
}

/**
 * flow - increases value of count on each interrupt
*/
void flow()
{
   count++;
}

/**
 * lcd_print - prints flowrate and logging status on the lcd
 * @flowrate: flowrate
*/
void lcd_print(int flowrate)
{
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Time:");
   lcd.print(rtc.getTimeStr());
   if (state == 1)
   {
    lcd.print("L");
   }
   lcd.setCursor(0, 1);
   lcd.print("Flow:");
   lcd.print(flowrate);
   lcd.print(" LPM");
   delay(1000);
}

/**
 * Initialize_SDcard - initializes the SD card
*/
void Initialize_SDcard()
{
  const int chipSelect = 53; //SD card CS pin connected to pin 53 of Arduino

  if (!SD.begin(chipSelect))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Insert SD Card");
    delay(4000);
    lcd.clear();
    return;
  }

  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);
  if (dataFile)
  {
      dataFile.println("Time, Flowrate(LPM)");
      dataFile.close();
  }
}
/**
 * write_SDcard - logs the flowrate and time to the SDcard
 * @flowrate: flowrate
*/
void write_SDcard(int flowrate)
{

  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);

  if (dataFile && state==1)
  {
      dataFile.print(rtc.getDateStr()); //Store date on SD card
      dataFile.print(" ");
      dataFile.print(rtc.getTimeStr());
      dataFile.print(","); //Move to next column using a ","
      dataFile.print(flowrate);
      dataFile.println(); //End of Row move to next row
      dataFile.close(); //Close the file
  }

}
/**
 * rec - starts and stops logging on iterrupt button
*/
void rec()
{
  state=!state;
}