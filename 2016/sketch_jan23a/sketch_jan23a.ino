
int DLAYX = 0;
int DLAYY = 0;
int CLOCK_PIN = 0;
int RESET_PIN = 5;

int pin[3] = { 2, 3, 1 };

int roll = 0;
int ctr = 0;

int faces[7][3][3] = {{
  {HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH},
},{
  {HIGH, HIGH, HIGH},
  {HIGH,  LOW, HIGH},
  {HIGH, HIGH, HIGH},
},{
  {HIGH,  LOW, HIGH},
  {HIGH, HIGH, HIGH},
  {HIGH,  LOW, HIGH},
},{
  { LOW, HIGH, HIGH},
  {HIGH,  LOW, HIGH},
  {HIGH, HIGH,  LOW},
},{
  { LOW, HIGH,  LOW},
  {HIGH, HIGH, HIGH},
  { LOW, HIGH,  LOW},
},{
  { LOW, HIGH,  LOW},
  {HIGH,  LOW, HIGH},
  { LOW, HIGH,  LOW},
},{
  { LOW, HIGH,  LOW},
  { LOW, HIGH,  LOW},
  { LOW, HIGH,  LOW},
}};

int pinModeInit[6] = {OUTPUT, OUTPUT, OUTPUT, OUTPUT, OUTPUT, INPUT};
int pinStateInit[6] = {LOW, HIGH, HIGH, HIGH, HIGH, LOW};

void setup() {
  for(int i = 0; i < 5; i++) {
    pinMode(0, pinModeInit[i]);
    digitalWrite(0, pinStateInit[i]);
  }
}

void loop() {
  int button = digitalRead(5);
  if(button == HIGH) {
    doroll();
    digitalWrite(1, HIGH);
    
  }
  reset();
  for(int y = 0; y < 3; y++) {
    for(int x = 0; x < 3; x++) {
      digitalWrite(pin[x], faces[roll][y][x]);
      delay(DLAYX);
      digitalWrite(pin[x], HIGH);
    }
    clock();
  }
}

void doroll() {
  digitalWrite(pin[1], LOW);
  randomSeed(analogRead(0));
  roll = random(1, 7);
  digitalWrite(pin[1], HIGH);
}

void clock() {
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
  delay(DLAYY);
}

void reset() {
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(RESET_PIN, LOW);
}


