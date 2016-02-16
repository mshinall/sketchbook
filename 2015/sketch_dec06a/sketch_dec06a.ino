
int dlay = 10;
int sig = 2;
int first = 5;
int last = 12;
int total = last - first + 1;
int bits = 8;
int ascii = 64;
const int totx = 8;
const int toty = 5;
int text[toty][totx] = {
    { 60, 66,129,129,129, 66, 36,  0},
    { 63, 72,136,136,136, 72, 63,  0},
    {128,128,128,255,128,128,128,  0},
    {128,  8,  8,  8,  8,  8,128,  0},
    {192, 32, 16, 15, 16, 32,192,  0},
};

int x = 0;
int y = 0;

void setup() {
  //Serial.begin (9600);
  for(int i = first; i <= last; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(sig, OUTPUT);
  digitalWrite(sig, HIGH);
  delay(100 * dlay);
  
}

void loop() {
  if(x >= totx) {
    Serial.println("--------");
    x = 0;
    y++;
  }
  if(y >= toty) {
    digitalWrite(sig, LOW);
    delay(400 * dlay);
    digitalWrite(sig, HIGH);
    delay(100 * dlay);
    y = 0;
  }
  digitalWrite(sig, HIGH);
  Serial.print("x=");
  Serial.print(x);
  Serial.print(", y=");
  Serial.println(y);
  draw(text[y][x]);
  x++;
  delay(dlay);
  
}

/*

-
128   xxx     xxx   xxxxxxx x     x x     x
64   x   x   x   x     x    x     x x     x
32  x     x x     x    x    x     x  x   x    
16  x       x     x    x    x     x   x x
8   x       xxxxxxx    x    xxxxxxx    x
4   x     x x     x    x    x     x    x
2    x   x  x     x    x    x     x    x
1     xxx   x     x    x    x     x    x
-
*/



void draw(int x) {
  for(int i = 0; i <= bits; i++) {
    if(((x >> i) & 1) == 1) {
      digitalWrite(i + first, HIGH);
    } else {
      digitalWrite(i + first, LOW);
    }
  }
}
