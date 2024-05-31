
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SPI.h> //Library for SPI communication (Pre-Loaded into Arduino)
#include <SD.h> //Library for SD card (Pre-Loaded into Arduino)


const int chipSelect = 53; //SD card CS pin connected to pin 53 of Arduino
int flowPin=2;
double flowRate;
volatile int count;
unsigned long currentTime;
unsigned long cloopTime;
volatile byte state=0;
int recBtn=3;


LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  rtc(SDA, SCL);

void setup()
{
  pinMode(flowPin,INPUT);
  digitalWrite(flowPin, HIGH);
  pinMode(recBtn,INPUT);
  attachInterrupt(digitalPinToInterrupt(flowPin), flow, RISING);
  attachInterrupt(digitalPinToInterrupt(recBtn), rec, RISING);
  lcd.begin();
  lcd.backlight();
  rtc.begin();
  Initialize_SDcard();
 
  
  }

void loop()
{
  readFls();
  writeSDcard();
  lcdPrint();

}


void readFls()
{  
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      detachInterrupt(digitalPinToInterrupt(flowPin));
      flowRate = (((1000.0/(currentTime-cloopTime))*count) / 0.2)/1.2;
      cloopTime = currentTime; // Updates cloopTime
      count = 0; // Reset Counter
      attachInterrupt(digitalPinToInterrupt(flowPin), flow, RISING);

   }
}

void flow(){
   count++;
}

void lcdPrint(){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Time:");
   lcd.print(rtc.getTimeStr());
   if(state==1){
    lcd.print("L");
   }

   lcd.setCursor(0,1);
   lcd.print("Flow:");
   lcd.print(flowRate);
   lcd.print(" LPM");
   delay(1000);
    
   
}



void Initialize_SDcard()
{
  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert SD Card");
    delay(4000);
    lcd.clear();
    return;
  }

  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);
  if (dataFile) {
      dataFile.println("Time, Flowrate(LPM)"); 
      dataFile.close();
  }
}
void writeSDcard()
{

  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);

  if (dataFile &&state==1) {
      dataFile.print(rtc.getDateStr()); //Store date on SD card
      dataFile.print(" ");
      dataFile.print(rtc.getTimeStr());
      dataFile.print(","); //Move to next column using a ","
      dataFile.print(flowRate);
      dataFile.println(); //End of Row move to next row
      dataFile.close(); //Close the file
  }

}

void rec(){
  state=!state;
    }
