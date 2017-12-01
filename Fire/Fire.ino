#define LED_YELOW  0
#define LED_ORANGE 1
#define LED_RED    2
#define LED_WARM   3
#define LED_WHITE  4

#define ENDARR     55
#define RAND_LED   33

int i = 0;
uint8_t x;
bool stormy = false;
int dire = +1;

uint8_t mov[] = {
   0,1,2,0,1,2,4,RAND_LED,RAND_LED,RAND_LED,
   3,3,4,2,3,0,1,RAND_LED,RAND_LED,
   2,4,2,0,1,0,1,1,0,1,2,0,3,4,RAND_LED,
   RAND_LED,RAND_LED,RAND_LED,RAND_LED,RAND_LED,
   ENDARR
};

unsigned long m_w = 1;
unsigned long m_z = 2;

unsigned long getRandom() {
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

void setup() {
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_ORANGE, OUTPUT); // Built in
  pinMode(LED_YELOW,  OUTPUT);
  pinMode(LED_WARM,   OUTPUT);
  pinMode(LED_WHITE,  OUTPUT);
}

void storm() {
  if (mov[i] == ENDARR) {
    i=0;
    if (getRandom()%4 == 1) {
      stormy = false;
      dire = 1;
    }
  }
  
  if (mov[i] == RAND_LED) {
    x = getRandom()%5;    
  } else {
    x = mov[i];
  }

  digitalWrite(x, HIGH);
  delay(getRandom()%20 + 20);
  digitalWrite(x, LOW);
  i++;
}

void normal() {
  x = getRandom()%3;
  if (x==2) x=3;
  analogWrite(x, i);
  i += dire;
  if (i==253) dire = -1;
  if (i==100) dire = 1;
  delay(40);
}

void loop() {
  if (stormy) {
    storm();
  } else {
    normal();
    if (getRandom()%1234 == 1) {
      i=0;
      stormy = true;
      digitalWrite(LED_RED,    LOW);
      digitalWrite(LED_ORANGE, LOW);
      digitalWrite(LED_YELOW,  LOW);
      digitalWrite(LED_WARM,   LOW);
      digitalWrite(LED_WHITE,  LOW); 
    }
  }
}
