#define LED_YELOW  0
#define LED_ORANGE 1
#define LED_RED    2
#define LED_WARM   3
#define LED_WHITE  4

#define ENDARR     55
#define RAND_LED   33
int i = 0;
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

void loop() {
  if (mov[i] == ENDARR) i=0;
  if (mov[i] == RAND_LED) {
    uint8_t x = getRandom()%5;
    digitalWrite(x, HIGH);
    delay(getRandom()%250 + 50);
    digitalWrite(x, LOW);    
  } else {
    digitalWrite(mov[i], HIGH);
    delay(getRandom()%120 + 30);
    digitalWrite(mov[i], LOW);
  }
  i++;
}
