// Started Jan 16 2016

// Constants
// Example densities
const float dens1 = 1.0046; // Saline density @ 22C g/mL
const int calib = 10000; // Predetermined calibration factor from curve (weight = voltage*calib)
const int timeread = 5000; // Time between readings (ms) 

// Analog values for calibration
int loadA = 0; // Lower bound weight kg 
int analogvalA = 0; // analog reading taken with load A on the load cell 

float loadB = 2; // Upper bound weight kg 
int analogvalB = 10; // analog reading taken with load B on the load cell

// Setup
void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}

float sumRate = 0;
float lenRate = 0;
float avRate

// Loop
void loop() {

  while (tictoc(1000) {
      int analogval = analogRead(A0); // Reading load cell voltage at A0 pin
  // Calculating weight in 2 ways (To see which one is more accurate) 
    // Method 1 using map for smooth linear calibration
       float load = map(analogval, analogvalA, analogvalB, loadA, loadB); // Mapping calibration between loadA -> loadB
       float rate1 = load / dens1; 
       
       sumRate += rate1;
       lenRate ++;
       
    // Method 2, multiplying by predetermined calibration factor
      float voltage = analogval * (10.0 / 1023.0); // Assuming 0 - 10V output
      float rate2 = voltage * calib / dens1;
  
   // Printing every X seconds (set above at timeread)
  //if(millis() > time + timeread){
  //  Serial.print("FlowRate1: ");Serial.println(rate1);
  //  Serial.print("FlowRate2: ");Serial.println(rate2);
  //  time = millis();
  }
  avRate = sumRate / lenRate;
  }
}
