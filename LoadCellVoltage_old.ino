// Started Jan 16 2016

// Constants
// Example densities
const float dens1 = 1.0046; // Saline density @ 22C g/mL
//const float calib = 10000; // Predetermined calibration factor from curve (weight = voltage*calib)

// Analog values for calibration
float loadA = 0; // Lower bound weight g
float analogvalA = 11; // analog reading taken with load A on the load cell

float loadB = 1262.5; // Upper bound weight g
float analogvalB = 167; // analog reading taken with load B on the load cell

float sumRate = 0;
float lenRate = 0;
float avRate1 = 0;
float avRate2 = 0;
float flowrate = 0;
const int settime = 3000; // Time between readings in ms
boolean set1 = true;

// Loop
float loadCellFlowRate () {
  while (tictoc(1000)) {
    float analogval = analogRead(A0); // Reading load cell voltage at A0 pin
    Serial.println(analogval);
    // Calculating weight in 2 ways (To see which one is more accurate)
    // Using map for smooth linear calibration
    float load = map(analogval, analogvalA, analogvalB, loadA, loadB); // Mapping calibration between loadA -> loadB
    float rate1 = load / dens1;  // Mass -> Volume

    sumRate += rate1;
    lenRate++;

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
      flowrate = (avRate2 - avRate1) / settime * 3600000; // Flowrate mL / hr
      avRate1 = avRate2; // Sets avRate1 to avRate2 for next cycle of flow rate calculation
      avRate2 = 0; // Resets avRate2
      Serial.println(flowrate);
      delay(settime);
    }
    return flowrate;
  }
}
