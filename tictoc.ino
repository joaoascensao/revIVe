boolean b
b = false;

boolean tictoc (float tMil) {
float tIni

if (!b){
  tIni = millis();
}

boolean tElapse
if ((millis() - tIni) < tMil) {
  tElapse = true;
  b=true;
}
else {
  tElapse = false;
  b=false;
}

return tElapse;

}

