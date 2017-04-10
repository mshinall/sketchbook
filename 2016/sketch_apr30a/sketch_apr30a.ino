






void setup() {
}

void loop() {
  int pot = analogRead(A2);
  int pwm = (pot / 4);
  analogWrite(0, pwm);
}
