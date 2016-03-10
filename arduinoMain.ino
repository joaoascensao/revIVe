#include <Stepper.h>

#include <LiquidCrystal.h> // Access Arduino's built in LCD library
#include <Keypad.h> //Access keypad library (Download it from readme link)
#include "PID.h"
#include "pitches.h"

#include "Adafruit_ADS1015.h"
#include <Wire.h>

//A2D
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

PID stepperPID = PID(0.001,1,0);

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[cols] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte rowPins[rows] = {22, 23, 24, 25}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int allUserInputs[3] = {0, 0, 0};
Stepper biStepper(200, 32, 33, 31, 30);

float bubbleCalibration;

int bubblePin = A2; //the pin connected to bubble detection
int speakerPin = 8; //the pin that is connected to the speaker for alarms

//double x[16] = {0, 0.1000, 0.2000, 0.3000, 0.4000, 0.5000, 0.6000, 0.7000, 0.8000, 0.9000, 1.0000, 1.1000, 1.2000, 1.3000, 1.4000, 1.5000};
//double y[16] = {-0.0241, 0.3319, 0.6313, 0.8135, 1.1970, 1.4835, 1.8628, 2.2093, 2.5109, 2.6136, 3.0077, 3.1786, 5.4886, 3.8993, 4.3533, 4.4230};

//double stdi = standard_deviation(y,16);


void setup() {
  ads.begin();
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20, 4);
  
  lcd.print("Welcome to revIVe   Infusion Device"); 
  delay(5000);
  
  //Serial.print("std: "); Serial.println(stdi);
  //Serial.print("m: "); Serial.println(dataCollect(16));
  
  stepperPID.setSetPoint(500);

  
  bubbleCalibration = calibrateBubbleDetection();
  //screen1(&allUserInputs[0]);
  
  //stepperPID.setSetPoint(538);
  // Initialize all pins
  
  
}



void loop() {
  // put your main code here, to run repeatedly: 

  //lcd.clear();
  //lcd.print(dataCollect(200));
  
  //biStepper.step(1);
  //delay(2000);
  
  //Serial.println(analogRead(bubblePin));
  if (abs((analogRead(bubblePin) - bubbleCalibration)/bubbleCalibration)>0.3) {
    //tone(speakerPin,NOTE_C7,15000);
  }
  
  //A2D
  float m = dataCollect(100);
  
  
  stepperPID.addNewSample(m);
  
  biStepper.step(stepperPID.process());
  
  //Serial.print("flow rate:"); Serial.println(dataCollect(100));
  /*
  long adc00 = 0;
  long ssd;

  for(int index = 0; index < 200; index++) {
    ssd = ads.readADC_SingleEnded(0) + 700;
    if (index > 20) {
    adc00 += ssd;
    Serial.print("AIN0: "); Serial.println(ssd);
    }
  }
  
  Serial.println(adc00/179.0);
  Serial.println(" ");
  long adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0) + 700;
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
   Serial.println(" ");
  
  //Serial.println(adc0/5000);
  */
  
  
  // get load cell voltage
  //float flowRate;
  //flowRate = loadCellFlowRate();
  
  
  
  // call PID
  // figure out how much to move the motor
}

