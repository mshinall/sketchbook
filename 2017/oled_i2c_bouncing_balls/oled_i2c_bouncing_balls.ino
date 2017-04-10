#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SIZE 2
#define COUNT 4
#define INTERVAL 20

#define XT 127
#define YT 31
#define XB 0
#define YB 0

#define XTS XT - SIZE - 1
#define YTS YT - SIZE - 1
#define XBS XB + SIZE
#define YBS YB + SIZE

#define DT 4
#define DB 1

int i = 0;
int c = 0;

int x[COUNT];
int y[COUNT];

int xd[COUNT];
int yd[COUNT];

int fill[COUNT];

void setup()   {                
  Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  drawSplash();
  delay(500);
  randomSeed(analogRead(0));
  initBounce();
}

void loop() {
  display.clearDisplay();
  if(i >= 200) {
    i = 0;
    //initDirection();
  }
  checkLimits();
  checkCollisions();
  for(int c = 0; c < COUNT; c++) {
    x[c] += xd[c];
    y[c] += yd[c];
    //display.drawPixel(x[c], y[c], WHITE);
    if(fill[c] == 1) {
      display.fillCircle(x[c], y[c], SIZE, WHITE);
    } else {
      display.drawCircle(x[c], y[c], SIZE, WHITE);
    }
  }
  display.display();
  delay(INTERVAL);
  i++;
}

void checkCollisions() {
  if(c <= 10) {
    c++;
    return;    
  }
  for(int c = 0; c < COUNT; c++) {
    for(int d = 0; d < COUNT; d++) {
      if(c == d) {
        continue;
      }
      if(1 == hasCollided(c, d)) {
        fill[c] = -1;
        fill[d] = -1;
      } else {
        fill[c] = 1;
        fill[d] = 1;
      }
    }
  }
}

void drawText(int x, int y, char* text) {
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(x, y);
  display.println(text);
}

int hasCollided(int c, int d) {
  int hs = SIZE; // / 2;
  if(
      (x[c]+hs > x[d]-hs) && (x[c]-hs < x[d]+hs) &&
      (y[c]+hs > y[d]-hs) && (y[c]-hs < y[d]+hs)
    ) {
    return 1;
  }
  return 0;
}

void checkLimits() {
  for(int c = 0; c < COUNT; c++) {
    if(x[c] > XTS) {
      x[c] = XTS;
      xd[c] = -(xd[c]);
    }
    if(x[c] <= XBS) {
      x[c] = XBS;
      xd[c] = -(xd[c]);
    }
    if(y[c] > YTS) {
      y[c] = YTS;
      yd[c] = -(yd[c]);
    }
    if(y[c] <= YBS) {
      y[c] = YBS;
      yd[c] = -(yd[c]);
    }
  }
}

void initBounce() {
  for(int c = 0; c < COUNT; c++) {
    x[c] = random(XBS, XTS);
    y[c] = random(YBS, YTS);
    fill[c] = 1;
  }
  initDirection();
}

void initDirection() {
  for(int c = 0; c < COUNT; c++) {
    if(xd[c] > 0) {
      xd[c] = random(DB, DT);
    } else {
      xd[c] = -(random(DB, DT));
    }
    if(yd[c] > 0) {
      yd[c] = random(DB, DT);
    } else {
      yd[c] = -(random(DB, DT));
    }
  }
}

void drawSplash() {
  display.clearDisplay();
  drawBox();  
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(44, 6);
  display.println("Mathias");
  display.setCursor(44, 16);
  display.println("Shinall");
  display.display(); 
}

void drawBox() {
  display.drawLine(XB, YB, XT, YB, WHITE);
  display.drawLine(XT, YB, XT, YT, WHITE);
  display.drawLine(XT, YT, XB, YT, WHITE);
  display.drawLine(XB, YT, XB, YB, WHITE);
}






