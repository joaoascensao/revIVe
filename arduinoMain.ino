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
