
const unsigned long TOP = 100000;
const unsigned long BTM = 0;
const unsigned long BDLY = 500;

int state = HIGH;
volatile unsigned long dly = 0;
volatile unsigned long lbp = 0;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  initInterrupts();
}

void loop() {
  digitalWrite(0, state);
  state = !state;
  delayMicroseconds(dly);
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
  if((digitalRead(4) == HIGH) && ((millis() - lbp) > BDLY)) {
    lbp = millis();
    dly++;
    if(dly > TOP) {
      dly = TOP;
    }
  } else if((digitalRead(3) == HIGH) && ((millis() - lbp) > BDLY)) {
    lbp = millis();
    dly--;
    if(dly < BTM) {
      dly = BTM;
    }
  } else {
    //nothing
  }
}

