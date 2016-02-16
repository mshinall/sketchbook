
#include "avr/sleep.h"
#include "avr/interrupt.h"

int DLAY = 1;

int CLOCK_PIN = 0;
int DATA_PIN = 1;
int LATCH_PIN = 2;
int BUTTON_PIN = 3;
int RAND_PIN = A2;

int roll = 0;
int rolling = 0;
int seed = 0;

int pinModeInit[4] = {OUTPUT, OUTPUT, OUTPUT, INPUT};
int pinStateInit[4] = {LOW, LOW, LOW, LOW};

byte faces[10][3] = {{
    B00000111,
    B00000111,
    B00000111
  },{
    B00000111,
    B01000111,
    B00000111
  },{
    B01000111,
    B00000111,
    B01000111
  },{
    B10000111,
    B01000111,
    B00100111
  },{
    B10100111,
    B00000111,
    B10100111
  },{
    B10100111,
    B01000111,
    B10100111
  },{
    B10100111,
    B10100111,
    B10100111
  },{
    B10100111,
    B11100111,
    B10100111
  },{
    B11100111,
    B10100111,
    B11100111
  },{
    B11100111,
    B11100111,
    B11100111
}};

int spin = 0;
byte spins[8][3] = {{
    B01000111,
    B00000111,
    B00000111
  },{
    B10000111,
    B00000111,
    B00000111
  },{
    B00000111,
    B10000111,
    B00000111
  },{
    B00000111,
    B00000111,
    B10000111
  },{
    B00000111,
    B00000111,
    B01000111
  },{
    B00000111,
    B00000111,
    B00100111
  },{
    B00000111,
    B00100111,
    B00000111
  },{
    B00100111,
    B00000111,
    B00000111
}};



long lastButtonPress = 0;
long sleepTime = 30000;

void setup() {
  GIMSK |= _BV(PCIE); //enable pin change interrupt
  PCMSK |= _BV(PCINT3); //use PB3 as interrupt pin
  sei(); // enable interrupts
  for(int i = 0; i < 4; i++) {
    pinMode(i, pinModeInit[i]);
    digitalWrite(i, pinStateInit[i]);
  }
  lastButtonPress = millis();
  roll = 0;
  blink(5);
}

void loop() {
  
  if(millis() > (lastButtonPress + sleepTime)) {
    sleep();
  }
  if(rolling == 0) {
    draw(roll);
  }
  if(digitalRead(BUTTON_PIN) == HIGH) {
    lastButtonPress = millis();
    doRoll();
  }
}

void draw(int r) {
  draw(r, 1);
}

void draw(int r, int c) {
  if(c < 1) {
    c = 1;
  }
  for(int i = 0; i < c; i++) {
    for(int j = 0; j < 3; j++) {
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, genData(j, faces[r][j]));
      latch();
      delay(DLAY);
    }
  }
}

byte genData(int row, byte data) {
  bitWrite(data, row, 0);
  return data;
}

void doRoll() {
  rolling = 1;
  seed = analogRead(RAND_PIN);
  randomSeed(seed);  
  int mult = 64;
  for(int i = 0; i < 64; i++) {
    spinner(1);
  }
  roll = random(1, 7);
  rolling = 0;
}

void latch() {
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void blink(int c) {
  for(int i = 0; i < c; i++) {
    draw(9, 10);
    draw(0, 10);
  }
}

void spinner(int c) {
  if(spin > 7) {
    spin = 0;
  }
  for(int i = 0; i < c; i++) {
    for(int j = 0; j < 3; j++) {
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, genData(j, spins[spin][j]));
      latch();
      delay(DLAY);
    }
    spin++;
  }
}

void sleep() {
  blink(5);
  ADCSRA &= ~(1<<ADEN); //disable ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  ADCSRA |= (1<<ADEN); //enable ADC
  lastButtonPress = millis();
}

ISR(PCINT0_vect) {
  //nothing needed here
}

