boolean b = false;

boolean tictoc (float tMil) {
  float tIni;

  if (!b){
    tIni = millis();
  }

  boolean tElapse = false;
  if ((millis() - tIni) < tMil) {
    tElapse = true;
    b=true;
  }
  else {
    tElapse = false;
    b =false;
  }

  return tElapse;
}

