#include "LiquidCrystal.h" // Access Arduino's built in LCD library
#include "Keypad.h" //Access keypad library

class PID{
public:
  
  double error;
  double sample;
  double lastSample;
  double kP, kI, kD;      
  double P, D;
  double I = 0;
  double pid;
  int step;
  int totSteps = 0;
  
  double setPoint;
  long lastProcess;
  
  PID(double _kP, double _kI, double _kD){
    kP = _kP;
    kI = _kI;
    kD = _kD;
  }
  
  void addNewSample(double _sample){
    sample = _sample;
  }
  
  void setSetPoint(double _setPoint){
    setPoint = _setPoint;
  }
  
  double process(){
    // PID implementation
    error = setPoint - sample;
    float deltaTime = (millis() - lastProcess) / 1000.0;
    lastProcess = millis();
    
    //P
    P = error * kP;
    
    //I
    I = I + (error * kI) * deltaTime;
    
    //D
    // Use better D?
    D = (lastSample - sample) * kD / deltaTime;
    lastSample = sample;
    
    // Sum of everything
    if (abs(error)>8) {
      pid = P + I + D;
    }
    
    step = round(pid);

    return (step - totSteps);
    
    totSteps = step;
  }
};

PID stepperPID(0.001,1,0);

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte colPins[cols] = {7, 6, 1, 0}; //connect to the row pinouts of the keypad
byte rowPins[rows] = {13, 10, 9, 8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  stepperPID.setSetPoint(538);
  // Initialize all pins
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  // get load cell voltage
  float flowRate;
  flowRate = loadCellFlowRate();
  
  stepperPID.addNewSample(flowRate);
  
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
  // biStepper.step(stepperPID.process())
  
  // call PID
  // figure out how much to move the motor
}
