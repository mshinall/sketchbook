int srDataPin = 9;
int srCLockPin = 10;
int srLatchPin = 11;

int dcResetPin = 12;
int dcClockPin = 13;
int rowCount = 10;

int ctr = 0;
int rnd = 0;

void setup(){
  pinMode(srDataPin, OUTPUT);
  pinMode(srCLockPin, OUTPUT);
  pinMode(srLatchPin, OUTPUT);
  pinMode(dcResetPin, OUTPUT);
  pinMode(dcClockPin, OUTPUT);

  //reset the 4017
  digitalWrite(dcResetPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(dcResetPin,LOW);
}

void loop(){
  if(ctr >= 100) {
    ctr = 0;
  }
  rnd = random(1024);
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srCLockPin, MSBFIRST, rnd);
  digitalWrite(srLatchPin, HIGH);
  delayMicroseconds(100);
  
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srCLockPin, MSBFIRST, 0);
  digitalWrite(srLatchPin, HIGH);
  
  digitalWrite(dcClockPin, HIGH);
  digitalWrite(dcClockPin, LOW);
  ctr++;
}
