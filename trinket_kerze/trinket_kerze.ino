#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define POWEROK 3950

int vcc = 4290;
byte ticker = 0;
bool fadedon = true;

int pins[3]  = {0,1,4};
int flame[3] = {0,0,0};

inline void readVcc() {
  // read vcc
  power_adc_enable();
  ADMUX = (0<<REFS0) | (12<<MUX0);
  delay(10);
  ADCSRA |= (1<<ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  vcc = ADCW;
  vcc = 1125300L / vcc;
  power_adc_disable();
}

void setup() {
  for(int i=0; i<3; ++i) {
    pinMode(pins[i], OUTPUT);
  }
  
  MCUSR = MCUSR & B11110111; // Reset flag disable, WDRF bit3 of MCUSR
  WDTCR = WDTCR | B00011000; // set Bit 3+4 to set Prescaler
  WDTCR = B00100001; // Watchdog Prescaler auf 1024k setzen > ergibt ca. 8s
  WDTCR = WDTCR | B01000000; // wdt enable
}

void loop() {
  if (vcc > POWEROK) {
    flame[2] = flame[1];
    flame[1] = flame[0];
    flame[0] = random(80, 255);
    delay(random(30, 150));
    for (int i=0; i<3; ++i) analogWrite(pins[i], flame[i]);
    readVcc();
    fadedon = true;
  } else {
    if (fadedon == true) {
      // fade off !! ------------------
      for (int j=0; j<255; ++j) {
          for (int i=0; i<3; ++i) analogWrite(pins[i], 255-j); 
          delay(40+(j/4));
      }
      for (int i=0; i<3; ++i) digitalWrite(pins[i], LOW);
    }
    fadedon = false; 
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    readVcc();
    if (vcc > POWEROK) {
      // fade on !! ----------------------
      for (int j=0; j<255; ++j) {
        for (int i=0; i<3; ++i) analogWrite(pins[i], j); 
        delay(40+(64-j/4));
      }
      fadedon = true;     
    }
  }
}

ISR(WDT_vect) {
  // dummy
  ticker++;
}

