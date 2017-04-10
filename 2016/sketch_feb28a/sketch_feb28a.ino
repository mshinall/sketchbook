#include <avr/interrupt.h>    // Needed to use interrupts

const long TOP = 100000;
const long BTM = 1;

int state = HIGH;
volatile long dly = BTM;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  initInterrupts();
}

void loop() {
    digitalWrite(0, state);
    delayMicroseconds(dly);
    state=!state;
}

void initInterrupts() {    // initialize Timer1
  cli();  // disable global interrupts
  TCCR1A = (1 << WGM01);             //CTC mode
  TCCR0B = (2 << CS00);              //div8
  OCR1A = 255;    // 50us compare value
  TIMSK |= (1<<OCIE1A);              //if you want interrupt
  sei();
}

ISR(TIMER1_COMPA_vect) {
  if(digitalRead(4) == HIGH) {
    dly = (dly < TOP) ? dly + 1 : TOP;
  } else if(digitalRead(3) == HIGH) {
    dly = (dly > BTM) ? dly - 1 : BTM;
  } else {
    //nothing
  }
}


