void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Initialize all pins
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  // get load cell voltage
  float flowRate;
  flowRate = loadCellFlowRate();
  // call PID
  // figure out how much to move the motor
}
