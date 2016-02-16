#include <Servo.h>

int potpin = A1;
int srvpin = 6;
Servo servo;

void setup() {
  servo.attach(srvpin);
}

void loop() {
  int val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 178);
  servo.write(val);
  delay(15);
}
