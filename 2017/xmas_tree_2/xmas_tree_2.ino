
const int YL = 8;
const int XL = 7;
const int FL = 6;

const int SPEED = 16;
const int BLINK = 100 * SPEED;

const int D_CLOCK_PIN = 3;
const int D_RESET_PIN = 4;

const int S_DATA_PIN = 2;
const int S_LATCH_PIN = 1;
const int S_CLOCK_PIN = 0;

const int DATA[FL][YL] = {{
  B00010000,
  B00111000,
  B01111100,
  B01111100,
  B11111110,
  B01111100,
  B11111110,
  B11000110
},{
  B00010000,
  B00111000,
  B00111100,
  B01111100,
  B11111100,
  B01111100,
  B11111110,
  B11000110
},{
  B00010000,
  B00111000,
  B01111100,
  B01111100,
  B11111110,
  B01111100,
  B11111110,
  B11000110
},{
  B00010000,
  B00111000,
  B01111100,
  B01111100,
  B01111110,
  B01111100,
  B11111100,
  B11000110
},{
  B00010000,
  B00111000,
  B01111100,
  B01111100,
  B11111110,
  B01111100,
  B11111110,
  B11000110
},{
  B00010000,
  B00111000,
  B01111000,
  B01111100,
  B11111110,
  B01111100,
  B01111110,
  B11000110
}};

const int ALL_ON[YL] {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
};

const int ALL_OFF[YL] {
  B00000000,  
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const int LETTER_M[YL] {
  B00000000,
  B01000100,
  B01101100,
  B01010100,
  B01010100,
  B01000100,
  B01000100,
  B00000000
};

const int LETTER_E[YL] {
  B00000000,
  B01111100,
  B01000000,
  B01111100,
  B01000000,
  B01000000,
  B01111100,
  B00000000
};

const int LETTER_R[YL] {
  B00000000,
  B00010000,
  B00101000,
  B01000100,
  B01111100,
  B01001000,
  B01000100,
  B00000000
};

const int LETTER_Y[YL] {
  B00000000,
  B00000000,
  B01000100,
  B01101100,
  B00111000,
  B00010000,
  B00010000,
  B00000000
};

const int LETTER_C[YL] {
  B00000000,
  B00010000,
  B00101000,
  B01000100,
  B01000000,
  B01000000,
  B01111100,
  B00000000
};

const int LETTER_H[YL] {
  B00000000,
  B00000000,
  B01000100,
  B01000100,
  B01110100,
  B01001100,
  B01000100,
  B00000000
};

signed int y = YL-1;
int x = 0;
int i = 0;
int f = 0;

void setup() {
  pinMode(D_CLOCK_PIN, OUTPUT);
  pinMode(D_RESET_PIN, OUTPUT);
  pinMode(S_DATA_PIN, OUTPUT);
  pinMode(S_LATCH_PIN, OUTPUT);
  pinMode(S_CLOCK_PIN, OUTPUT);

  digitalWrite(D_CLOCK_PIN, LOW);
  digitalWrite(D_RESET_PIN, LOW);
  digitalWrite(S_DATA_PIN, LOW);
  digitalWrite(S_LATCH_PIN, LOW);
  digitalWrite(S_CLOCK_PIN, LOW);

  reset();
}

void loop() {
//  if(x > XL) {
//    x = 0;
//    reset();
//  }
//  
//  if(y < 0) {
//    y = YL-1;
//  }
//  
//  if(f > FL-1) {
//    f = 0;
//  }
  
  //byte data = DATA[f][y];
  //shift(data);
  //shift(LETTER_H[y]);
  shift(ALL_ON);
  tick();
  
//  x++;
//  y--;
//  i++;
//  
//  if(i % BLINK == 0) {
//    f++;
//  }
}

void tick() {
  digitalWrite(D_CLOCK_PIN, HIGH);
  digitalWrite(D_CLOCK_PIN, LOW);
}

void reset() {
  digitalWrite(D_RESET_PIN, HIGH);
  digitalWrite(D_RESET_PIN, LOW);
}

void shift(byte b) {
  shiftOut(S_DATA_PIN, S_CLOCK_PIN, LSBFIRST, b);
  digitalWrite(S_LATCH_PIN, HIGH);
  digitalWrite(S_LATCH_PIN, LOW);
  shiftOut(S_DATA_PIN, S_CLOCK_PIN, LSBFIRST, B00000000);
  digitalWrite(S_LATCH_PIN, HIGH);
  digitalWrite(S_LATCH_PIN, LOW);
}

