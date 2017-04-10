/*
 * 8x8x8 led cube
 * matt.shinall@gmail.com
 * 20160223
*/


#include <avr/io.h>
#include <avr/interrupt.h>

const int CLK_PIN = 0;
const int LCH_PIN = 1;
const int SER_PIN = 2;
const int Z_BITS[3] = {0, 1, 2};
const int XY_BITS[3][3] = {
  {12, 13,  0},
  { 1,  2,  3},
  { 6,  5,  4},
};

const int P = 1;

byte BYTES_OFF[3][2] = {
  { B00000111, B00000000 },
  { B00000111, B00000000 },
  { B00000111, B00000000 }
};

byte BYTES_ON[3][2] = {
  { B11111000, B11111111 },
  { B11111000, B11111111 },
  { B11111000, B11111111 }
};

byte BYTES_SINGLE[9][2] = {
  { B00000000, B00000001 },
  { B00000000, B00000010 },
  { B00000000, B00000100 },
  { B00000000, B00001000 },
  { B00000000, B00010000 },
  { B00000000, B00100000 },
  { B00000000, B01000000 },
  { B00100000, B00000000 },
  { B01000000, B00000000 }
};

byte bytes[3][2];

volatile int layer = 0;

void setup() {
  setBytes(BYTES_OFF);
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  randomSeed(analogRead(A3));
  initTimerCounter1();  
}

void loop() {
  //patternBlink();
  patternRandom();
  //patternX();
}

void patternBlink() {
  setBytes(BYTES_ON);
  delay(10);
  setBytes(BYTES_OFF);
  delay(10);
}

void patternRandom() {
  setBytes(BYTES_SINGLE[8]);
}

void patternX() {
  byte b[3][2] = {
    {},
    {},
    {}
  };
}

int getBit(int x, int y) {
  return XY_BITS[x][y];
}

void setBytes(byte b[3][2]) {
  memcpy(bytes, b, sizeof(byte)*3*2);
}

void initTimerCounter1() {    // initialize Timer1
  cli();  // disable global interrupts
  TCCR0A = (1 << WGM01);             //CTC mode
  TCCR0B = (2 << CS00);              //div8
  OCR0A = 255;    // 50us compare value
  TIMSK |= (1<<OCIE0A);              //if you want interrupt
  sei();
}

ISR(TIMER0_COMPA_vect) {
  if(layer > 2) {
    layer = 0;
  }
  for(int z = 0; z < 3; z++) {
    if(layer == z) {
      bitWrite(bytes[z][0], Z_BITS[z], LOW);
    } else {
      bitWrite(bytes[z][0], Z_BITS[z], HIGH);
    }
  }
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, bytes[layer][0]);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, bytes[layer][1]);
  digitalWrite(LCH_PIN, HIGH);
  digitalWrite(LCH_PIN, LOW);
  layer++;
}


