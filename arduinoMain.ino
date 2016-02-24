#include <Stepper.h>
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

byte colPins[cols] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte rowPins[rows] = {22, 23, 24, 25}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int allUserInputs[3] = {0, 0, 0};
Stepper biStepper(200, 32, 33, 31, 30);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20, 4);
  
  lcd.print("Welcome to revIVe   Infusion Device"); 
  delay(5000);
  
  
  //screen1(&allUserInputs[0]);
  
  //stepperPID.setSetPoint(538);
  // Initialize all pins
}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println("b");
  biStepper.step(1);
  delay(1000);
  
  // get flowrate
  float flowRate;
  flowRate = loadCellFlowRate();
  
  //stepperPID.addNewSample(flowRate);
  
  // biStepper.step(stepperPID.process())
  
  // call PID
  // figure out how much to move the motor
}
