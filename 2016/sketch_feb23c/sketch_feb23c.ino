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

volatile int layer = 0;
int rdm[100];

void setup() {
  for(int i = 0; i < 100; i++) {
    rdm[i] = random(0,9);
  }
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  randomSeed(analogRead(A3));
  initTimerCounter1();  
}

void loop() {
  //patternBlink();
  //patternRandom();
  patternOne();
}

void patternOne() {
  setBytes(oneOn[0][0]);
}

void setBytes(bytes d) {
  memcpy(bytes d, sizeof(byte)*3*2);
}

void initTimerCounter1() {    // initialize Timer1
  cli();  // disable global interrupts
  TCCR1A = (1 << WGM01);             //CTC mode
  TCCR0B = (2 << CS00);              //div8
  OCR1A = 1;    // 50us compare value
  //OCR1A = F_CPU / 8 - 1;
  TIMSK |= (1<<OCIE1A);              //if you want interrupt
  sei();
}

ISR(TIMER1_COMPA_vect) {
  if(layer > 2) {
    layer = 0;
  }
  for(int z = 0; z < 3; z++) {
    if(layer == z) {
      bitWrite(bytes[layer][0], z, LOW);
    } else {
      bitWrite(bytes[layer][0], z, HIGH);
    }
  }
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, bytes[layer][0]);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, bytes[layer][1]);
  digitalWrite(LCH_PIN, HIGH);
  digitalWrite(LCH_PIN, LOW);
  layer++;
}


