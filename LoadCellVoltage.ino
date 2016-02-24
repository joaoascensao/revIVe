const float dens1 = 1.00; // Saline density @ 22C g/mL

// Analog values for calibration
const float loadA = 16.99; // Lower bound weight g
const int analogvalA = 117; // analog reading taken with load A on the load cell
const float loadB = 1113.45; // Upper bound weight g
const int analogvalB = 1016; // analog reading taken with load B on the load cell
float analogValueAverage = 0;
long time = 0;
const int settime = 60000; // Time between readings in ms

// Initialize variables for calculating flowrate
boolean set1 = true;

float vo1 = 0;
float vo2 = 0;
float rate = 0;


float loadCellFlowRate() {
  // put your main code here, to run repeatedly:
  int analogValue = analogRead(A8);

  analogValueAverage = 0.99 * analogValueAverage + 0.01 * analogValue;
  
  if (millis() > time + settime) {
    float load = analogToLoad(analogValueAverage);
    float volume = load / dens1;
    Serial.print("analogValue: "); Serial.println(analogValue);
    Serial.print("load:     "); Serial.println(load);
    Serial.print("volume: "); Serial.println(volume);

    //sumRate += rate1;
    //lenRate++;
    if (set1) {
      float rate1 = volume / settime * 1000;
      vo1 = rate1;
      set1 = false;
      //delay(settime);
    }
    else  {
      vo2 = volume;
      float rate = R(vo1, vo2);
      Serial.print("rate: "); Serial.println(rate);
      vo1 = vo2;
    }
    time = millis();
  }
  return rate;
}

float R(float Vol1, float Vol2) {
  float ra = (Vol2 - Vol1) / settime * 1000;
  return ra;
}

float analogToLoad(float analogval) {
  // using a custom map-function, because the standard arduino map function only uses int
  float load = mapfloat(analogval, analogvalA, analogvalB, loadA, loadB);
  return load;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
