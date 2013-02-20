#include<stdio.h>
#include<Serial.h>

char c = 0;
char buffer[80] = "";


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    buffer[0] = '\0';
    int idx = 0;
    while((c = Serial.read()) >= 0) {
      c = Serial.read();
      buffer[idx++] = c;
      Serial.print(c);
      Serial.println();
    }
    buffer[idx] = '\0';
    Serial.println(sprintf("got: %s", buffer));
  }
}
