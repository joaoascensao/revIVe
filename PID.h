#ifndef PID_h
#define PID_h

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
  
  PID(double _kP, double _kI, double _kD) {
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

#endif

