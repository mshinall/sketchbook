
int D = 100;

int C = HIGH;
int C1 = 0;
int C2 = 1;

int ctr = 2;

void setup() {
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  for(int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  if(ctr > 8) { ctr = 2; }
  if(ctr < 2) { ctr = 8; };
  
  for(int i = 2; i <= 8; i++) {
    if(ctr == i) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
  ctr++;
  delay(D);
}
