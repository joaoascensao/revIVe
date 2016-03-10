

float calibrateBubbleDetection() {
  float cc=0;
  float cnt=0;
  while(tictoc(2000)) {
    cc += analogRead(bubblePin);
    ++cnt;
    Serial.println(analogRead(bubblePin));
  }
  Serial.println(cc/cnt);
  return (cc/cnt);
}

