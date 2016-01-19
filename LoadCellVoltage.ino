// Started Jan 16 2016

// Constants
// Example densities
const float dens1 = 1.0046; // Saline density @ 22C g/mL
const int calib = 10000; // Predetermined calibration factor from curve (weight = voltage*calib)

// Analog values for calibration
int loadA = 0; // Lower bound weight kg
int analogvalA = 0; // analog reading taken with load A on the load cell

float loadB = 2; // Upper bound weight kg
int analogvalB = 10; // analog reading taken with load B on the load cell

float sumRate = 0;
float lenRate = 0;
float avRate1 = 0;
float avRate2 = 0;
float flowrate = 0;
const int settime = 5000; // Time between readings in ms
boolean set1 = true;

// Loop
float loadCellFlowRate () {
  while (tictoc(1000) {
  int analogval = analogRead(A0); // Reading load cell voltage at A0 pin
    // Calculating weight in 2 ways (To see which one is more accurate)
    // Method 1 using map for smooth linear calibration
    float load = map(analogval, analogvalA, analogvalB, loadA, loadB); // Mapping calibration between loadA -> loadB
    float rate1 = load / dens1;  // Mass -> Volume

    sumRate += rate1;
    ++ lenRate;

    // Method 2, multiplying by predetermined calibration factor
    float voltage = analogval * (10.0 / 1023.0); // Assuming 0 - 10V output
    float rate2 = voltage * calib / dens1;
    }
  // Calculate on first run
    if (set1) { 
      avRate1 = sumRate / lenRate;
      sumRate = 0;
      lenRate = 0;
      set1 = false;
      delay(settime); // Delays by time set above
    }
  // After 1st loop, runs this every other time
    else {
      avRate2 = sumRate / lenRate;
      sumRate = 0;
      lenRate = 0;
      flowrate = (avRate2 - avRate1) / settime / 3600000; // Flowrate mL / hr
      avRate1 = avRate2; // Sets avRate1 to avRate2 for next cycle of flow rate calculation
      avRate2 = 0; // Resets avRate2
      Serial.Println(flowrate)
      delay(settime);
}
return avRate1;
}
