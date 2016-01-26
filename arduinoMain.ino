#include <LiquidCrystal.h> // Access Arduino's built in LCD library

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
    // Implementação P ID
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
    
    // Soma tudo
    if (abs(error)>8) {
      pid = P + I + D;
    }
    
    step = round(pid);

    return (step - totSteps);
    
    totSteps = step;
  }
};

PID stepperPID(0.001,1,0);

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
  // biStepper.step(stepperPID.process())
  
  // call PID
  // figure out how much to move the motor
}
