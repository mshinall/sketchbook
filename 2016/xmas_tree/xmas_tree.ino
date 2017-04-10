
const int ORDER = LSBFIRST;

const int STAR = 0;
const int CLOCK = 3;
const int DATA = 7;
const int LATCH = 2;

int i = 0;
int g = 0;
int r = 0;

#define gl 5
#define rl 3

int ga[gl] = {3,2,6,1,0};
int ra[rl] = {4,5,7};

int interval = 10;
float dutycycle = 1;

void setup() {
  pinMode(STAR, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);

  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA, LOW);
  digitalWrite(LATCH, LOW);

  allOff();
}

void loop() {
  if(dutycycle > 0) {
    on();
  }
  delay(interval - (interval * dutycycle));
  if(dutycycle < 1) {
    allOff();
  }
  delay(interval * dutycycle);
  if(i < 0) {
    i = 0;
  } else {
    i++;  
  }
}

void on() {
  byte b = B00000000;
  g = i % gl;
  if(i % (interval * 2) == 0) {
    r = i % rl;
  }

  digitalWrite(STAR, HIGH);
  bitSet(b, ga[g]);
  bitSet(b, ra[r]);
  
  
  shiftData(b);
}

void allOff() {
  digitalWrite(STAR, LOW);
  shiftData(B00000000);
}

void shiftData(byte b) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, ORDER, b);
  digitalWrite(LATCH, HIGH);
}


