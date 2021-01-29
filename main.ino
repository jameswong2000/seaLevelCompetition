#include <SPI.h>
#include <SD.h>
const int chipSelect = 10;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C lcd(0x27, 16, 2);
int datanum = 0;
int numfile = 0;
char fname[12];
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //syn.Slaveboudset(19200);
  //Serial.begin(19200);
  lcd.init();
  lcd.backlight();
  lcd.setBacklight(HIGH);
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  pinMode (2, OUTPUT); //attach pin 2 to vcc
  pinMode (5, OUTPUT); //attach pin 5 to GND
  // initialize serial communication:
  Serial.begin(9600);
  

  Serial.print("Initializing SD card...");

  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("Card initialized.");
}

void loop()
{
  /* ******************** Start of Ultrasonic Part ********************* */

  delay(1000);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
float d = uS / US_ROUNDTRIP_CM;
  /* ******************** End of Ultrasonic Part ********************* */


  /* ******************** Start of Printing Result (both LCD and SD File) ********************* */

  Serial.print("Sea Level: ");
  if((d) < 300) {
    if (28 - (d) >0) {
    Serial.print(28 - (d)); // Convert ping time to distance in cm and print result
    Serial.println("cm");
    
      lcd.clear();
      lcd.print("Sea Level: ");
      lcd.print(28 - (d));
      lcd.print("cm");
  }
  else {
    Serial.println("0cm");
    lcd.clear();
     lcd.print("Sea Level: ");
     lcd.print("0");
     lcd.print("cm");
      }
  if (d >300) {
    Serial.println("OUT");
     lcd.clear();
     lcd.print("Sea Level: ");
     lcd.print("OUT");
  }
  Serial.print("");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(fname, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    if(28-d>0 ){
    dataFile.print(28 - d);
    //dataFile.print("cm");
    dataFile.println("");
    Serial.println("One data was written.");
    Serial.print("Number of data: ");
    Serial.println(datanum++);
    sprintf(fname, "data%d.csv",numfile);
    Serial.println(fname);
    Serial.println("");
    SD.open(fname, FILE_WRITE);
    if (datanum == 10) {numfile++;datanum = 0;}
    dataFile.flush();
    dataFile.close();
    
  }

  // if the file isn't open, pop up an error:
  else {
   Serial.println();
    Serial.println("error opening datalog.csv");
    Serial.println("");
  }

  /* ******************** End of Printing Result (both LCD and SD File) ********************* */

  
}
}
}

