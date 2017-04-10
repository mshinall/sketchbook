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
const int DUR = 50;
const int P = 1;

byte b1 = BYTE1;
byte b2 = BYTE2;

const int ON = HIGH;
const int OFF = LOW;

int nn = 0;

void setup() {
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  randomSeed(analogRead(A3));
}

void loop() {
  int r = 10;
  int n = random(0, 7);
  while(n == nn) {
    n = random(0, 7);
  }
  nn = n;
  switch(n) {
    case 0: patternBlink(r); break;
    case 1: patternRandom(r); break;
    case 2: patternX(r); break;
    case 3: patternY(r); break;
    case 4: patternZ(r); break;
    case 5: patternSpinX(r); break;
    case 6: patternSpinY(r); break;
    case 7: patternSpinZ(r); break;
  }
}

void draw() {
  draw(0);
}

void draw(int d) {
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, b1);
  shiftOut(SER_PIN, CLK_PIN, LSBFIRST, b2);
  digitalWrite(LCH_PIN, HIGH);
  digitalWrite(LCH_PIN, LOW);
  delay(d);
}

void clearAll() {
  clearAll(0);
}

void clearAll(int d) {
  b1 = BYTE1;
  b2 = BYTE2;
  draw(d);
}

void setZ(int z) {
  //LOW is ON for z
  bitWrite(b1, Z_BITS[z], LOW);
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
}

void patternAllOn() {
  for(int z = 0; z < 3; z++) {
    for(int x = 0; x < 3; x++) {
      for(int y = 0; y < 3; y++) {
        set(x, y, z);
      }
    }
  }
  draw(DUR*2);
}

void patternAllOff() {
  clearAll(DUR*2);
}

void patternBlink(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < 4; i++) {
      patternAllOn();
      patternAllOff();  
    }
  }
}

void patternRandom(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < DUR/2; i++) {
        int x = random(0,3);
        int y = random(0,3);
        int z = random(0,3);
        set(x, y, z);
        draw(10);
        clearAll(30);
    }
  }
}

void patternX(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int x = 0; x < 3; x++) {
      for(int y = 0; y < 3; y++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(DUR);
      clearAll();      
    }
    for(int x = 2; x >= 0; x--) {
      for(int y = 0; y < 3; y++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(DUR);
      clearAll();
    }
  }
}

void patternY(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int y = 0; y < 3; y++) {
      for(int x = 0; x < 3; x++) {    
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(DUR);
      clearAll();
    }
    for(int y = 2; y >= 0; y--) {
      for(int x = 0; x < 3; x++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(DUR);
      clearAll();
    }
  }
}

void patternZ(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int z = 0; z < 3; z++) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) { 
          set(x, y, z);
        }          
      }
      draw(DUR);
      clearAll();
    }
    for(int z = 2; z >= 0; z--) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x, y, z);
        }
      }
      draw(DUR);
      clearAll();
    }
  }
}

void patternSpinX(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < DUR/2; i++) {
      int x = 1;
      for(int z = 0; z < 3; z++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,x);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      int z = 1;
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      int z = 1;
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,2-x);
        }
        draw();
        clearAll();
      }
    }
  }
}

void patternSpinY(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < DUR/2; i++) {
      int y = 1;
      for(int z = 0; z < 3; z++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,y);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      int z = 1;
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      int z = 1;
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,2-y);
        }
        draw();
        clearAll();
      }
    }
  }
}

void patternSpinZ(int rr) {
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < DUR/2; i++) {
      int x = 1;
      for(int z = 0; z < 3; z++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(y,y,x);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      int y = 1;
      for(int z = 0; z < 3; z++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw();
        clearAll();
      }
    }
    for(int i = 0; i < DUR/2; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(2-y,y,x);
        }
        draw();
        clearAll();
      }
    }
  }
}




