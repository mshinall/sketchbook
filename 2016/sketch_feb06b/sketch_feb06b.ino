/*
 * LED Die Roller
 * ATTiny85 & 595 shift register
 * matt.shinall@gmail.com
 * 20160131
*/
#include "avr/sleep.h"
#include "avr/interrupt.h"

int DDLAY = 0; //display row interval delay
int BDLAY = 10; //blink delay
int SDLAY = 5; //spin delay
int MAX_ROLL = 6;

int DATA_PIN = 0;
int LATCH_PIN = 1;
int CLOCK_PIN = 2;
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

long sleepTime = 30000;

volatile long lastButtonPress = 0;
volatile int buttonPressCount = 0;

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
  blink(2);
}

void loop() {
  if(rolling == 0) {
    if(millis() > (lastButtonPress + sleepTime)) {
      buttonPressCount = 0; 
      sleep();
    }
    if(buttonPressCount >= 1) {
      doRoll();      
      buttonPressCount = 0;
    }
    draw(roll);
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
      delay(DDLAY);
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
  spinner(3);
  //blink(1);
  roll = random(1, MAX_ROLL+1);
  rolling = 0;
}

void latch() {
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void blink(int c) {
  for(int i = 0; i < c; i++) {
    draw(9, BDLAY);
    draw(0, BDLAY);
  }
}

void spinner(int c) {
  for(int i = 0; i < c; i++) {
    for(int k = 0; k < 8; k++) {
      for(int j = 0; j < 3; j++) {
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, genData(j, spins[k][j]));
        latch();
        delay(SDLAY);
      }
    }
  }
}

void sleep() {
  blink(3);
  ADCSRA &= ~(1<<ADEN); //disable ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  ADCSRA |= (1<<ADEN); //enable ADC
  blink(1);
}

ISR(PCINT0_vect) {
  lastButtonPress = millis();
  if((millis() - lastButtonPress) < 100) {
    buttonPressCount = 1;
  }
}


