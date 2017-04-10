/*
 * 8x8x8 led cube
 * matt.shinall@gmail.com
 * 20160223
*/


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
const int DLY = 0;
const int DUR = 100;
const int P = 1;

byte b1 = BYTE1;
byte b2 = BYTE2;

const int ON = HIGH;
const int OFF = LOW;

int zz = 0;

void setup() {
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  randomSeed(analogRead(A3));
}

void loop() {
  patternTest(DUR/5);
  patternRandom(DUR*10);
  
  patternTest(DUR/5);
  patternX(DUR/25);
  
  patternTest(DUR/5);
  patternY(DUR/25);
  
  patternTest(DUR/5);
  patternZ(DUR/25);
  
  patternTest(DUR/5);
  patternSpinX(DUR/25);
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

void setZ(int z) {
  //LOW is ON for z
  for(int i = 0; i < 3; i++) {
    if(i == z) {
      bitWrite(b1, Z_BITS[i], LOW);
    } else {
      //bitWrite(b1, Z_BITS[i], HIGH);
    }
  }
}

void set(int x, int y, int z) {
  //HIGH is ON for x and y
  int b = XY_BITS[x][y];
  if(b > 7) {
    bitWrite(b1, b-8, HIGH);
  } else {
    bitWrite(b2, b, HIGH);
  }
  setZ(z);  
  draw();
}


void patternTest(int dur) {
  for(int i = 0; i < dur; i++) {
    for(int z = 0; z < 3; z++) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x, y, z);
        }
      }
    }
  }
}

void patternRandom(int dur) {
  for(int i = 0; i < dur; i++) {
    clearAll();
    draw();
    for(int p = 0; p < P; p++) {
      int x = random(0,3);
      int y = random(0,3);
      int z = random(0,3);
      set(x, y, z);
    }
    for(int t = 0; t < DLY; t++) {
      draw();
    }
  }
}

void patternX(int dur) {
  for(int i = 0; i < dur; i++) {
    for(int x = 0; x < 3; x++) {
      for(int t = 0; t < 5; t++) {
        for(int y = 0; y < 3; y++) {
          for(int z = 0; z < 3; z++) {
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
    for(int x = 2; x >= 0; x--) {
      for(int t = 0; t < 5; t++) {
        for(int y = 0; y < 3; y++) {
          for(int z = 0; z < 3; z++) {
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
  }
}

void patternY(int dur) {
  for(int i = 0; i < dur; i++) {
    for(int y = 0; y < 3; y++) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {    
          for(int z = 0; z < 3; z++) {
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
    for(int y = 2; y >= 0; y--) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {
          for(int z = 0; z < 3; z++) {
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
  }
}

void patternZ(int dur) {
  for(int i = 0; i < dur; i++) {
    for(int z = 0; z < 3; z++) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {
          for(int y = 0; y < 3; y++) { 
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
    for(int z = 2; z >= 0; z--) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {
          for(int y = 0; y < 3; y++) {
            set(x, y, z);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
  }
}

void patternSpinX(int dur) {
  for(int i = 0; i < dur; i++) {
    
  }
}


