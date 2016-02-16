

int d = 0;
int x = 0;
int y = 0;

int data[5][4] = {
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1}
};

void setup() {
  for(int i = 0; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  digitalWrite(x+4, data[y][x]);
  delay(d);
  digitalWrite(x+4, LOW);
  x++;
  if(x == 4) {
    x = 0;
    nextrow();
    y++;
    if(y == 5) {
      resetrow(); 
      y = 0;
    }
  }
}

void nextrow() {
  digitalWrite(8, HIGH);
  digitalWrite(8, LOW);
}

void resetrow() {
  digitalWrite(9, HIGH);
  digitalWrite(9, LOW);
}


