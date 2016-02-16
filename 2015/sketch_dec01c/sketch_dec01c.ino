/*
  print contents of the EEPROM (1024 bytes on atmega328)
*/
#include<EEPROM.h>

int addr = 0;
byte value;
void setup() {
  Serial.begin(9600);
  while(!Serial) {}
  //EEPROM[1001] = 1;
}

void loop() {
  value = EEPROM.read(addr);
  Serial.print(addr);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  addr++;
  if(addr == EEPROM.length()) {
    delay(1000);
    exit(0);
  }
}
