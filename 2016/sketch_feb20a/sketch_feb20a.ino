const int CLK_PIN = 0;
const int LCH_PIN = 1;
const int SER_PIN = 2;
const int Z_BITS[3] = {0, 1, 2};
const int XY_BITS[3][3] = {
  {12, 13,  0},
  { 1,  2,  3},
  { 6,  5,  4},
};

const byte BYTE1 = B00000111;
const byte BYTE2 = B00000000;

byte b1 = BYTE1;
byte b2 = BYTE2;

const int ON = HIGH;
const int OFF = LOW;

void setup() {
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  randomSeed(analogRead(A3));
}

void loop() {
  int x = random(0,3);
  int y = random(0,3);
  int z = random(0,3);
  for(int t = 0; t < 20; t++) {
    set(x, y, z, ON);
    clearAll();
  }
}

void draw() {
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, b1);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, b2);
  digitalWrite(LCH_PIN, HIGH);
  digitalWrite(LCH_PIN, LOW);
}

void clearAll() {
  b1 = BYTE1;
  b2 = BYTE2;
  draw();
}

void set(int x, int y, int z, int s) {
  int b = XY_BITS[x][y];
  if(b > 7) {
    bitWrite(b1, b-8, s);
  } else {
    bitWrite(b2, b, s);
  }
  bitWrite(b1, Z_BITS[z], !s);
  draw();
}

