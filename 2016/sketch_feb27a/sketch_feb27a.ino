


int state = HIGH;
volatile int pot = 0;
volatile long lastButtonPress = 0L;
void setup() {
  pinMode(0, OUTPUT);
  pinMode(A3, INPUT);
  pot = analogRead(A3);
  initInterrupts();
}

void loop() {
  digitalWrite(0, state);
  delayMicroseconds(pot/2);
  state = !state;
}

void initInterrupts() {    // initialize Timer1
  cli();  // disable global interrupts
  
  TCCR1A = (1 << WGM01);             //CTC mode
  TCCR0B = (2 << CS00);              //div8
  OCR1A = 1;    // 50us compare value
  TIMSK |= (1<<OCIE1A);              //if you want interrupt
  
  GIMSK |= _BV(PCIE); //enable pin change interrupt
  PCMSK |= _BV(PCINT3); //use PB3 as interrupt pin
  
  sei();
}

ISR(TIMER1_COMPA_vect) {
  pot = analogRead(A3);
}

ISR(PCINT0_vect) {
  if((millis() - lastButtonPress) < 100) {
  } else {
  }
}
