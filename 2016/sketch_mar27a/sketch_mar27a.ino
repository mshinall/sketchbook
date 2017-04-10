void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
}

boolean state = HIGH;
long ctr = 0;
void loop() {
  if(ctr % 200 == 0) {
    digitalWrite(3, state);
    digitalWrite(4, !state);
    state = !state;
  }
  ctr++;
  if(ctr > 99999) {
    ctr = 0;
  }
}
