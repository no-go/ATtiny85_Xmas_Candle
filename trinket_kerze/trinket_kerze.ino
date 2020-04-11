
int pins[4]  = {0,1,4};
int flame[4] = {0,0,0};
bool alloff  = true;

void setup() {
  pinMode(A1, INPUT);
  for(int i=0; i<3; ++i) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  // is it dark ? ----------------------
  if (analogRead(A1) > 200) {
    
    // fade on !! ----------------------
    if (alloff == true) {
      for (int j=0; j<255; ++j) {
        for (int i=0; i<3; ++i) analogWrite(pins[i], j); 
        delay(40+(64-j/4));
      }
    }
    
    alloff = false;
    // flame effect! -------------------
    flame[2] = flame[1];
    flame[1] = flame[0];
    flame[0] = random(80, 254);
    delay(random(30, 150));
    for (int i=0; i<3; ++i) analogWrite(pins[i], flame[i]);
      
  } else {
    
    delay(200);
    if (alloff == false) {
      
      // fade off !! ------------------
      for (int j=0; j<255; ++j) {
        for (int i=0; i<3; ++i) analogWrite(pins[i], 255-j); 
        delay(40+(j/4));
      }

      // off -------------------------
      for (int i=0; i<3; ++i) digitalWrite(pins[i], LOW);
      alloff = true;
    }
  }
  

}

