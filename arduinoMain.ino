#include <LiquidCrystal.h> // Access Arduino's built in LCD library
#include <Keypad.h> //Access keypad library (Download it from readme link)
#include "PID.h"

PID stepperPID = PID(0.001,1,0);

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte colPins[cols] = {7, 6, 14, 15}; //connect to the row pinouts of the keypad
byte rowPins[rows] = {13, 10, 9, 8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.print("Welcome to revIVe   Infusion Device"); 
  //stepperPID.setSetPoint(538);
  // Initialize all pins
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  // get load cell voltage
  //float flowRate;
  //flowRate = loadCellFlowRate();
  
  //stepperPID.addNewSample(flowRate);
  
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  if (key != NO_KEY){
    Serial.println(key);
    lcd.print(key);
  }
  // biStepper.step(stepperPID.process())
  
  // call PID
  // figure out how much to move the motor
}
