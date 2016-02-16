int led = 13;
int dlay = 100;
int top = dlay;
int intr = 5;
int btm = intr;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(dlay);
  digitalWrite(led, LOW);
  delay(dlay);
  if((dlay <= btm) || (dlay >= top)) {
    intr = -intr;
  }
  dlay += intr;  
}
