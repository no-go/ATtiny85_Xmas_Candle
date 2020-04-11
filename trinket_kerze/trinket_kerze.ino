
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
  if (analogRead(A1) > 200) {
    alloff = false;
    flame[2] = flame[1];
    flame[1] = flame[0];
    flame[0] = random(80, 254);
    delay(random(30, 150));
    for (int i=0; i<3; ++i) analogWrite(pins[i], flame[i]);    
  } else {
    delay(200);
    if (alloff == false) {
      for (int i=0; i<3; ++i) digitalWrite(pins[i], LOW);
      alloff = true;
    }
  }
  

}

