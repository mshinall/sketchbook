/*
 * 3x3x3 led cube
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

const byte BYTE1_OFF = B00000111;
const byte BYTE2_OFF = B00000000;

const byte BYTE1_ON = B11111000;
const byte BYTE2_ON = B11111111;

const int DUR = 50;
const int P = 1;

byte b1 = BYTE1_OFF;
byte b2 = BYTE2_OFF;

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
  int r = 9;
  patternBlink(r);
  patternRandomOn(r);
  patternFadeBlink(r);
  //patternRandomOff(r);
  patternX(r);
  patternSpinX(r);
  patternY(r);
  patternSpinY(r);
  patternZ(r);  
  patternSpinZ(r);
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

void allOff() {
  allOff(0);
}

void allOff(int d) {
  b1 = BYTE1_OFF;
  b2 = BYTE2_OFF;
  draw(d);
}

void allOn() {
  allOn(0);
}

void allOn(int d) {
  b1 = BYTE1_ON;
  b2 = BYTE2_ON;
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

void unset(int x, int y, int z) {
  //HIGH is ON for x and y
  int b = XY_BITS[x][y];
  if(b > 7) {
    bitWrite(b1, b-8, LOW);
  } else {
    bitWrite(b2, b, LOW);
  }
  setZ(z);  
}

void patternBlink(int rr) {
  int d = DUR*40;
  for(int r = 0; r < rr; r++) {
    allOn(d);
    allOff(d);  
  }
}

void patternFadeBlink(int rr) {
  int d = DUR/2;
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < d; i++) {
      allOn(0 + i);
      allOff(d - i);  
    }
    for(int i = 0; i < d; i++) {
      allOn(d);
    }
    for(int i = 0; i < d; i++) {
      allOn(d - i);
      allOff(0 + i);  
    }
    for(int i = 0; i < d; i++) {
      allOff(d);
    }
  }
}

void patternRandomOn(int rr) {
  int d = DUR;
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < d; i++) {
        int x = random(0,3);
        int y = random(0,3);
        int z = random(0,3);
        set(x, y, z);
        draw(d);
        allOff(d);
    }
  }
}

//void patternRandomOff(int rr) {
//  int d = DUR;
//  for(int r = 0; r < rr; r++) {
//    for(int i = 0; i < d; i++) {
//        int x = random(0,3);
//        int y = random(0,3);
//        int z = random(0,3);
//        unset(x, y, z);
//        draw(d);
//        allOn(d);
//    }
//  }
//}

void patternX(int rr) {
  int d = DUR*10;
  for(int r = 0; r < rr; r++) {
    for(int x = 0; x < 3; x++) {
      for(int y = 0; y < 3; y++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(d);
      allOff();      
    }
    for(int x = 2; x >= 0; x--) {
      for(int y = 0; y < 3; y++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(d);
      allOff();
    }
  }
}

void patternY(int rr) {
  int d = DUR*10;
  for(int r = 0; r < rr; r++) {
    for(int y = 0; y < 3; y++) {
      for(int x = 0; x < 3; x++) {    
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(d);
      allOff();
    }
    for(int y = 2; y >= 0; y--) {
      for(int x = 0; x < 3; x++) {
        for(int z = 0; z < 3; z++) {
          set(x, y, z);
        }
      }
      draw(d);
      allOff();
    }
  }
}

void patternZ(int rr) {
  int d = DUR*10;
  for(int r = 0; r < rr; r++) {
    for(int z = 0; z < 3; z++) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) { 
          set(x, y, z);
        }          
      }
      draw(d);
      allOff();
    }
    for(int z = 2; z >= 0; z--) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x, y, z);
        }
      }
      draw(d);
      allOff();
    }
  }
}

void patternSpinX(int rr) {
  int d = DUR/4;
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < d; i++) {
      int x = 1;
      for(int z = 0; z < 3; z++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,x);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      int z = 1;
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      int z = 1;
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,2-x);
        }
        draw(d);
        allOff();
      }
    }
  }
}

void patternSpinY(int rr) {
  int d = DUR/4;
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < d; i++) {
      int y = 1;
      for(int z = 0; z < 3; z++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,y);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      int z = 1;
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      int z = 1;
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,2-y);
        }
        draw(d);
        allOff();
      }
    }
  }
}

void patternSpinZ(int rr) {
  int d = DUR/4;
  for(int r = 0; r < rr; r++) {
    for(int i = 0; i < d; i++) {
      int x = 1;
      for(int z = 0; z < 3; z++) {
        for(int y = 0; y < 3; y++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(y,y,x);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      int y = 1;
      for(int z = 0; z < 3; z++) {
        for(int x = 0; x < 3; x++) {
          set(x,y,z);
        }
        draw(d);
        allOff();
      }
    }
    for(int i = 0; i < d; i++) {
      for(int y = 0; y < 3; y++) {
        for(int x = 0; x < 3; x++) {
          set(2-y,y,x);
        }
        draw(d);
        allOff();
      }
    }
  }
}




