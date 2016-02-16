int srDataPin = 9;
int srCLockPin = 10;
int srLatchPin = 11;

int dcResetPin = 12;
int dcClockPin = 13;
int rowCount = 10;

int data[10] = {
  B00010000,
  B00000000,
  B10000010,
  B00101000,
  B00010000,
  B00101000,
  B10000010,
  B00000000,
  B00010000,
  B00000000
};

int ctr = 0;

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
  if(ctr >= rowCount) {
    ctr = 0;
  }
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srCLockPin, MSBFIRST, data[ctr]);
  digitalWrite(srLatchPin, HIGH);
  delayMicroseconds(100);
  
  digitalWrite(srLatchPin, LOW);
  shiftOut(srDataPin, srCLockPin, MSBFIRST, 0);
  digitalWrite(srLatchPin, HIGH);
  
  digitalWrite(dcClockPin, HIGH);
  digitalWrite(dcClockPin, LOW);
  ctr++;
}
