int grnled = 6;
int redled = 8;
volatile int state = LOW;

void setup() {
  pinMode(grnled, OUTPUT);
  attachInterrupt(1, on, LOW);
  attachInterrupt(0, off, HIGH);
}

void loop() {
  delay(100);
}

void on() {
  digitalWrite(grnled, HIGH);
}
  
void off() {
  digitalWrite(grnled, LOW);
}





