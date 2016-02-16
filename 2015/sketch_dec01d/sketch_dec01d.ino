/*
  using first 8 bits of EEPROM, light one of eight leds on digital pins 5 through 12
  control position using push button on digital pin 3 w/pull down resistor
*/
#include<EEPROM.h>

int on = HIGH;
int off = LOW;

int last = 8;
int ledOffset = 5;
int btn = 3;

volatile int ctr = 0;
volatile long lastPush = 0;

volatile byte eepValue;
volatile int sleep = 0;

byte eepValue2;




void setup() {
  for(int i = 0; i <= last; i++) {
    pinMode(i + ledOffset, OUTPUT);
  }
  pinMode(btn, INPUT);
  attachInterrupt(digitalPinToInterrupt(btn), btnPush, RISING);
  
  //test leds
  for(int i = 0; i <= last; i++) {
    digitalWrite(i + ledOffset, on);
    delay(10);
  }  
  delay(500);
  for(int i = 0; i <= last; i++) {
    digitalWrite(i + ledOffset, off);
    delay(10);
  }  
}

void loop() {
  if(sleep == 1) {
    return;
  }
  for(int i = 0; i <= last; i++) {
    EEPROM.get(i, eepValue2);
    if(eepValue2 == 1) {
      ctr = i;
      digitalWrite(i + ledOffset, on);
    } else {
      digitalWrite(i + ledOffset, off);
    }
  }
  if((millis() - lastPush) > 5000) {
    sleep = 1;
    for(int i = 0; i <= last; i++) {
      digitalWrite(i + ledOffset, off);
    }
  }  
  if((millis() - lastPush) > 300000) {
    exit(0);
  }
}

void btnPush() {
  if((millis() - lastPush) < 100) {
    return;
  }
  lastPush = millis();
  if(sleep == 0) {
    ctr++;
    if(ctr >= last) {
      ctr = 0;
    }
  }
  sleep = 0;
  for(int i = 0; i <= last; i++) {
    eepValue = EEPROM.read(i);
    if(i == ctr) {
      if(eepValue != 1) {
        EEPROM.put(i, 1);
      }
    } else {
      if(eepValue != 0) {
        EEPROM.put(i, 0);
      }
    }
  }  
}


