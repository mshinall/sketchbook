


void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
}

void loop() {
  Serial.print(millis());  
  Serial.print(": ");  
  Serial.println(analogRead(A5));  
  delay(2000);

}
