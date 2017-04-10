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
const int DLY = 20;
const int SDUR = 1000 / DLY;
const int DUR = 1000 / DLY / 5;
const int LDUR = 10000 / DLY;
const int P = 1;

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
  patternTest();
  patternRandom();
  patternX();
  patternY();
  patternZ();
}

void patternRandom() {
  for(int i = 0; i < LDUR; i++) {
    clearAll();
    draw();
    for(int p = 0; p < P; p++) {
      int x = random(0,3);
      int y = random(0,3);
      int z = random(0,3);
      set(x, y, z, ON);
    }
    for(int t = 0; t < DLY; t++) {
      draw();
    }
  }
}

void patternTest() {
  for(int i = 0; i < SDUR; i++) {
    for(int x = 0; x < 3; x++) {
      for(int y = 0; y < 3; y++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z, ON);
          draw();
          clearAll();
          draw();
        }
      }
    }
  }
}

void patternX() {
  for(int i = 0; i < DUR; i++) {
    for(int x = 0; x < 3; x++) {
      for(int t = 0; t < 5; t++) {
        for(int y = 0; y < 3; y++) {
          for(int z = 0; z < 3; z++) {
            set(x, y, z, ON);
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
            set(x, y, z, ON);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
  }
}

void patternY() {
  for(int i = 0; i < DUR; i++) {
    for(int y = 0; y < 3; y++) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {    
          for(int z = 0; z < 3; z++) {
            set(x, y, z, ON);
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
            set(x, y, z, ON);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
  }
}

void patternZ() {
  for(int i = 0; i < DUR; i++) {
    for(int z = 0; z < 3; z++) {
      for(int t = 0; t < 5; t++) {
        for(int x = 0; x < 3; x++) {
          for(int y = 0; y < 3; y++) { 
            set(x, y, z, ON);
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
            set(x, y, z, ON);
            draw();
            clearAll();
            draw();
          }
        }
      }
    }
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
}

void set(int x, int y, int z, int s) {
  int b = XY_BITS[x][y];
  if(b > 7) {
    bitWrite(b1, b-8, s);
  } else {
    bitWrite(b2, b, s);
  }
  bitWrite(b1, Z_BITS[z], !s);
}

