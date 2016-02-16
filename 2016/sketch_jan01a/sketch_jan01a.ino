

void setup() {
  Serial.begin(115200);
}

void loop() {
  int left = analogRead(A4);
  int right = analogRead(A3);
  int ground = analogRead(A2);
  int mic = analogRead(A1);

  Serial.print(left);
  Serial.print(",");
  Serial.print(right);
  Serial.print(",");
  Serial.print(ground);
  Serial.print(",");
  Serial.print(mic);
  Serial.println("");
  delay(200);
}
