#define byte uint8_t

int top = 12;
int btm = 8;
int inc = 1;
int pin = btm;

int pin_g = 6;
byte pin_g_on = 0;

int min_dlay = 1;
int max_dlay = 1000;
int dlay = 25;

volatile byte uppress = 0;
volatile byte dnpress = 0;

void setup() {

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  for(int i = btm; i <= top; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(pin_g, OUTPUT);
  
  attachInterrupt(1, up, LOW);
  attachInterrupt(0, dn, LOW);
}

void loop() {
  noInterrupts();
  if(1 == uppress) {
    uppress = 0;
    dlay -= 10;
  }
  if(1 == dnpress) {
    dnpress = 0;
    dlay += 10;
  }
  interrupts();

  if(dlay < min_dlay) {
    dlay = min_dlay;
  }
  if(dlay > max_dlay) {
    dlay = max_dlay;
  }
  
  if(pin == btm) {
    if(1 == pin_g_on) {
      digitalWrite(pin_g, HIGH);
    } else {
      digitalWrite(pin_g, LOW);
    }
    pin_g_on = !pin_g_on;
  }
  
  digitalWrite(pin, HIGH);
  delay(dlay);

  digitalWrite(pin, LOW);
  delay(dlay);

  pin += inc;
  
  if(pin >= top) {
    inc = -inc;
  }
  if(pin <= btm) {
    inc = -inc;
  }
}

void up() {
  uppress = 1;
}

void dn() {
  dnpress = 1;
}





