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

const int P = 1;

#define ALL_OF_0_0 B00000111, B00000000
#define ALL_ON_0_0 B11111000, B11111111
//12
#define ONE_ON_0_0 B00010111, B00000000
//1
#define ONE_ON_0_1 B00000111, B00000010
//6
#define ONE_ON_0_2 B00000111, B01000000
//13
#define ONE_ON_1_0 B00100111, B00000000
//2
#define ONE_ON_1_1 B00000111, B00000100
//5
#define ONE_ON_1_2 B00000111, B00100000
//0
#define ONE_ON_2_0 B00000111, B00000001
//3
#define ONE_ON_2_1 B00000111, B00001000
//4
#define ONE_ON_2_2 B00000111, B00010000

#define XXX_ON_0 B11111110, B11111111
#define XXX_ON_1 B11111101, B11111111
#define XXX_ON_2 B11111011, B11111111

#define ALL_OF \
  {ALL_OF_0_0}, \
  {ALL_OF_0_0}, \
  {ALL_OF_0_0}

#define ALL_ON \
  {ALL_ON_0_0}, \
  {ALL_ON_0_0}, \
  {ALL_ON_0_0}

#define ONE_ON \
  { 
    {
      {ONE_ON_0_0},
      {ALL_OF_0_0},
      {ALL_OF_0_0}
    },{
      {ALL_OF_0_0},
      {ONE_ON_0_0},
      {ALL_OF_0_0}
    },{
      {ALL_OF_0_0},
      {ALL_OF_0_0},
      {ONE_ON_0_0}
    } \
  },{ \
    {{ONE_ON_0_1},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_0_1},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_0_1}} \
  },{ \
    {{ONE_ON_0_2},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_0_2},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_0_2}} \
  },{ \
    {{ONE_ON_1_0},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_1_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_1_0}} \
  },{ \
    {{ONE_ON_1_1},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_1_1},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_1_1}} \
  },{ \
    {{ONE_ON_1_2},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_1_2},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_1_2}} \
  },{ \
    {{ONE_ON_2_0},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_2_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_2_0}} \
  },{ \
    {{ONE_ON_2_1},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_2_1},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_2_1}} \
  },{ \
    {{ONE_ON_2_2},{ALL_OF_0_0},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ONE_ON_2_2},{ALL_OF_0_0}}, \
    {{ALL_OF_0_0},{ALL_OF_0_0},{ONE_ON_2_2}} \
  }

#define XXX_ON \
  {XXX_ON_0}, \
  {XXX_ON_1}, \
  {XXX_ON_2}
  
byte oneOn[9][3][3][2] = {ONE_ON};
byte allOn[3][2] = {ALL_ON};
byte allOf[3][2] = {ALL_OF};
byte xxxOn[3][2] = {XXX_ON};

byte bytes[3][2] = {ALL_OF};
volatile int layer = 0;

int rdm[100];

int blinkCtr = 0;
int randomCtr = 0;
int xCtr = 0;

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

void patternBlink() {
  if(blinkCtr >= 40) {
    blinkCtr = 0;
  }
  if(blinkCtr < 20) {
    setBytes(allOn);
  } else {
    setBytes(allOf);
  }
  blinkCtr++;
}

void patternRandom() {
  if(randomCtr >= 100) {
    randomCtr = 0;
  }
  setBytes(oneOn[rdm[randomCtr]]);
  randomCtr++;
}

void patternX() {
  setBytes(xxxOn);
}

void setBytes(byte b[3][2]) {
  memcpy(bytes, b, sizeof(byte)*3*2);
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


