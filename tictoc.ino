boolean b
b = false;

boolean tictoc (float tMil) {
float tIni

if (!b){
  tIni = millis();
}

boolean tElapse
if ((millis() - tIni) < tMil) {
  tElapse = false;
  b=true;
}
else {
  tElapse = true;
  b=false;
}

return tElapse;

}

