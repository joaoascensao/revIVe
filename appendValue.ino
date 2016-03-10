void appendValue(char key, int *userVal) {

  int newVal = key - '0';
  userVal[3] = userVal[2];
  userVal[2] = userVal[1];
  userVal[1] = userVal[0];
  userVal[0] = newVal;
}

int arrayToNum(int *userVal) {
  
  return 1000*userVal[3] + 100*userVal[2] + 10*userVal[1] + userVal[0];
  
}

