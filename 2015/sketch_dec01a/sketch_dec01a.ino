/*
    simple binary counter using 8 leds on digital pins 2 through 9
*/



int dlay = 10;
int first = 2;
int last = 9;
int total = last - first + 1;
int ctr = 0;
int on = HIGH;
int off = LOW;

void setup() {
  //Serial.begin(9600);
  for(int i = first; i <= last; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  //Serial.println(ctr);
  for(int i = first; i <= last; i++) {
    int b = (ctr >> i) & 1;    
    if(b == 1) {
      digitalWrite(i, on);
    } else {
      digitalWrite(i, off);
    }


  }
  ctr++;
  delay(dlay);
}
