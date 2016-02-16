
int D = 10;

int G = HIGH;
int G1 = 0;
int G2 = 1;

int L = HIGH;

void setup() {
  for(int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
    pinMode(G1, OUTPUT);
    pinMode(G2, OUTPUT);
  }
}

void loop() {
    
  for(int i = 2; i <= 8; i++) {
    digitalWrite(G1, G);
    digitalWrite(G2, !G);
    G = !G;
    digitalWrite(i, L);
    delay(D);
    digitalWrite(i, !L);
    delay(D);
  }
}
