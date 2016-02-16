
int C = HIGH;
int C1 = 7;
int C2 = 6;

int L = 6;
int R[6] = {0,1,2,3,4,5};

int disp[2][6] = {
  {0,0,0,0,0,0},
  {0,0,0,0,0,0},
};

int ctr1 = 0;
int ctr2 = 0;

void setup() {
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  for(int i = 0; i < L; i++) {
    pinMode(R[i], OUTPUT);
  }
}

void loop() {
  refresh();
  shift();
  delay(1);
}

void shift() {
  ctr1++;
  if(ctr1 >= 100) {
    ctr1 = 0;
    ctr2++;
    for(int i = 0; i < L; i++) {
      disp[1][i] = disp[0][i];
      disp[0][i] = (ctr2 >> i) & 1;
    }
  }
}

void refresh() {
  digitalWrite(C1, C);
  digitalWrite(C2, !C);
  C = !C;
  if(C == HIGH) {
    for(int i = 0; i < L; i++) {
      if(disp[0][i] == 1) {
        digitalWrite(R[i], HIGH);
      } else {
        digitalWrite(R[i], LOW);
      }
    }
  } else {
    for(int i = 0; i < L; i++) {
      if(disp[1][i] == 1) {
        digitalWrite(R[i], HIGH);
      } else {
        digitalWrite(R[i], LOW);
      }
    }
  }
}


