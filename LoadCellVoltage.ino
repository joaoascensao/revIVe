/*
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


// Loop
float loadCellFlowRate () {
    float analogval = analogRead(A0); // Reading load cell voltage at A0 pin
    Serial.println(analogval);
    // Calculating weight in 2 ways (To see which one is more accurate)
    // Using map for smooth linear calibration
    float load = map(analogval, analogvalA, analogvalB, loadA, loadB); // Mapping calibration between loadA -> loadB
    float rate1 = load / dens1;  // Mass -> Volume
    return rate1;
}
*/
