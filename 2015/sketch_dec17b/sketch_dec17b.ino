#include <Servo.h>

int srvpin = 6;
Servo servo;

int btm = 30;
int top = 120;
int dly = 500;

void setup() {
  servo.attach(srvpin);
  servo.write(btm);
  delay(dly);
}

void loop() {
  servo.write(btm);
  delay(dly);
  servo.write(top);
  delay(dly);
}
