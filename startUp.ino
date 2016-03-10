void screen1(int *allUserInputs) {
  lcd.clear();
  lcd.print("Type of fluid:");
  lcd.setCursor(0, 1);
  lcd.print("1. Saline-based");
  lcd.setCursor(0, 2);
  lcd.print("2. Blood-based");
  
  char key = keypad.getKey();
  while (key!='1' && key!='2') {
    key = keypad.getKey();
    if (key!=NO_KEY) {
     Serial.println(key) ;
    }
  }
  
  
  
  screen2(key,&allUserInputs[0]);
}

void screen2(char typeFluid, int *allUserInputs) {
  lcd.clear();

  lcd.print("Confirm?");

  lcd.setCursor(10, 2);
  lcd.print("A.Continue");
  lcd.setCursor(10, 3);
  lcd.print("B.Back");

  if (typeFluid == '1') {
    lcd.setCursor(0, 1);
    lcd.print("1. Saline-based");
    allUserInputs[0] = 1;
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("2. Blood-based");
    allUserInputs[0] = 2;
  }

  char key = NO_KEY;
  while (key!='A' && key!='B'){
    key = keypad.getKey();
  }

  if (key=='B') {
    screen1(&allUserInputs[0]); 
  }
  if (key=='A') {
    screen3(&allUserInputs[0]); 
  }
}

void screen3(int *allUserInputs) {
  lcd.clear();
  lcd.print("Input Volume:");
  lcd.setCursor(4, 1);
  lcd.print("mL");

  lcd.setCursor(0, 2);
  lcd.print("*Clear");
  lcd.setCursor(10, 2);
  lcd.print("A.Continue");
  lcd.setCursor(10, 3);
  lcd.print("B.Back");

  char key = keypad.getKey();

  lcd.setCursor(0, 1);
  int no = 0;

  int userVal[4] = {0, 0, 0, 0};
  int totVol = 0;
  while (key!='A' && key!='B' && key!='*') {

    //lcd.setCursor(0, 0);
    if (key != NO_KEY && no!=4 && key != 'C' && key != 'D' && key != '#'){
      //Serial.println(key);

      lcd.print(key);
      appendValue(key,&userVal[0]);
      ++no;
      totVol = arrayToNum(&userVal[0]);
      Serial.println(totVol);
    }
    key = keypad.getKey();
  }

  if (key=='A') {
    allUserInputs[1] = totVol;
    screen4(&allUserInputs[0]);
  }

  else if (key=='B') {
    screen1(&allUserInputs[0]);
  }

  else {
    screen3(&allUserInputs[0]);
  }
}

void screen4(int *allUserInputs) {
  lcd.clear();
  lcd.print("Input Flow Rate:");
  lcd.setCursor(4, 1);
  lcd.print("mL/hr");

  lcd.setCursor(0, 2);
  lcd.print("*Clear");
  lcd.setCursor(10, 2);
  lcd.print("A.Continue");
  lcd.setCursor(10, 3);
  lcd.print("B.Back");

  char key = keypad.getKey();

  lcd.setCursor(0, 1);
  int no = 0;

  int userVal[4] = {0, 0, 0, 0};
  int totFlow = 0;
  while (key!='A' && key!='B' && key!='*') {

    //lcd.setCursor(0, 0);
    if (key != NO_KEY && no!=4 && key != 'C' && key != 'D' && key != '#'){
      //Serial.println(key);

      lcd.print(key);
      appendValue(key,&userVal[0]);
      ++no;
      totFlow = arrayToNum(&userVal[0]);
      Serial.println(totFlow);
    }
    key = keypad.getKey();
  }

  if (key=='A') {
    allUserInputs[2] = totFlow;
    screen5(&allUserInputs[0]);
  }

  else if (key=='B') {
    screen3(&allUserInputs[0]);
  }

  else {
    screen4(&allUserInputs[0]);
  }
}

void screen5(int *allUserInputs) {
  lcd.clear();
  if (allUserInputs[0]==1) {
    lcd.print("Fluid: Saline-based");
  }
  else {
    lcd.print("Fluid: Blood-based");
  }
  lcd.setCursor(0, 1);
  lcd.print("Volume: ");
  lcd.print(String(allUserInputs[1]));
  lcd.print("mL");
  
  lcd.setCursor(0, 2);
  lcd.print("Flow Rate: ");
  lcd.print(String(allUserInputs[2]));
  lcd.print("mL/hr");
  
  lcd.setCursor(0, 3);
  lcd.print("Begin?  A.Yes B.No");
  
  
  char key = keypad.getKey();
  while (key!='A' && key!='B'){
    key = keypad.getKey();
  }

  if (key=='B') {
    screen4(&allUserInputs[0]); 
  }
  if (key=='A') {
    screen6(&allUserInputs[0]); 
  }
}

void screen6(int *allUserInputs) {
  lcd.clear();
  lcd.print("Beginning Treatment");
  lcd.setCursor(4, 1);
  unsigned int Vol = allUserInputs[1];
  unsigned int flowRate = allUserInputs[2];
  lcd.print(String(Vol/flowRate));
  lcd.print(" hrs ");
  int mins = ((Vol*60)/flowRate) % 60;
  lcd.print(String(mins));
  lcd.print(" mins");
  
  lcd.setCursor(3, 2);
  lcd.print("until complete");
  delay(10000);
  screen7(&allUserInputs[0]); 
}

void screen7(int *allUserInputs) {
  lcd.clear();
  unsigned int Vol = allUserInputs[1];
  unsigned int flowRate = allUserInputs[2];
  lcd.print(String(Vol/flowRate));
  lcd.print(" hrs ");
  int mins = ((Vol*60)/flowRate) % 60;
  lcd.print(String(mins));
  lcd.print(" mins left");
  lcd.setCursor(0, 1);
  lcd.print("350mL delivered");
  
  lcd.setCursor(0, 2);
  lcd.print("Treatment Settings:");
  
  lcd.setCursor(0, 3);
  lcd.print(String(Vol));
  lcd.print("mL at ");
  lcd.print(String(flowRate));
  lcd.print("mL/hr");
  
}

