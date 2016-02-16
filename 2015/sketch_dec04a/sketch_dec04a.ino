/*
 * Simple test for activating a solid state relay
*/

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  analogReference(DEFAULT);
}

void loop() {
  int p = analogRead(A5);
  Serial.println(p);
  if(p > 500) {  
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  delay(100);
}
