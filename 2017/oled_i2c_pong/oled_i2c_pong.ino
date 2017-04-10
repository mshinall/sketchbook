

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define INTERVAL 0

#define XT 127
#define YT 63

#define BTN_TR_PIN 7
#define BTN_BR_PIN 5
#define BTN_TL_PIN 6
#define BTN_BL_PIN 2

#define FULL_PADDLE 16
#define HALF_PADDLE FULL_PADDLE/2
#define PADDLE_MOVE_MULT 2;

#define FULL_BALL 2
#define HALF_BALL FULL_BALL/2
#define BALL_MOVE_MULT 2;
int pr = YT/2;
int pl = YT/2;

int sr = 0;
int sl = 0;

int bx = 0;
int by = 0;

int bxd = 3;
int byd = 1;

void setup() {
  pinMode(BTN_TR_PIN, INPUT_PULLUP);
  pinMode(BTN_BR_PIN, INPUT_PULLUP);
  pinMode(BTN_TL_PIN, INPUT_PULLUP);
  pinMode(BTN_BL_PIN, INPUT_PULLUP);

  randomSeed(analogRead(0));
                  
  //Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  display.clearDisplay();
  display.display();
  bx = XT/2;
  by = YT/2;
}

void loop() {
  display.clearDisplay();

  bx += bxd;
  by += byd;
  
  drawCenterLine();
  drawScores();
  drawRightPaddle();
  drawLeftPaddle();
  drawBall();
  
  if(digitalRead(BTN_TR_PIN) == LOW) {
    pr-=2;
  }
  if(digitalRead(BTN_BR_PIN) == LOW) {
    pr+=2;
  }
  if(digitalRead(BTN_TL_PIN) == LOW) {
    pl-=2;
  }
  if(digitalRead(BTN_BL_PIN) == LOW) {
    pl+=2;
  }
  display.display();
  delay(INTERVAL);
}

void drawScores() {
  drawText(XT/3, 0, String(sl));
  drawText(XT/3*2, 0, String(sr));
}

void resetBall() {
  delay(1000);
  bx = XT/2;
  by = YT/2;
}

void ballBounce() {
  if(by > YT-HALF_BALL) {
    byd = -(byd);
  }
  if(by < 0+HALF_BALL) {
    byd = -(byd);
  }
  if(bx > XT-HALF_BALL) {
    if((by > pr-HALF_PADDLE-HALF_BALL) && (by < pr+HALF_PADDLE+HALF_BALL)) {
      bxd = -(bxd);
    } else {
      sl++;
      resetBall();
    }
  }
  if(bx < 0+HALF_BALL) {
      bxd = -(bxd);
//    if((by > pl-HALF_PADDLE-HALF_BALL) && (by < pl+HALF_PADDLE+HALF_BALL)) {
//      bxd = -(bxd);
//    } else {
//      sr++;
//      resetBall();
//    }
  }  
}

void drawBall() {
  ballBounce();
  display.fillCircle(bx,by,FULL_BALL,WHITE);
}

void drawText(int x, int y, String text) {
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(x, y);
  display.println(text);
  //display.display(); 
}

void drawCenterLine() {
  for(int i = 0; i <= YT; i+=8) {
    display.drawPixel(XT/2,i,WHITE);
    display.drawPixel(XT/2+1,i+4,WHITE);
  }
}

void drawRightPaddle() {
  if(pr < 0+HALF_PADDLE) {
    pr = 0+HALF_PADDLE;
  }
  if(pr > YT-HALF_PADDLE) {
    pr = YT-HALF_PADDLE;
  }
  display.drawLine(XT,pr-HALF_PADDLE,XT,pr+HALF_PADDLE,WHITE);
}

void drawLeftPaddle() {
  if(pl < 0+HALF_PADDLE) {
    pl = 0+HALF_PADDLE;
  }
  if(pl > YT-HALF_PADDLE) {
    pl = YT-HALF_PADDLE;
  }
  display.drawLine(0,pl-HALF_PADDLE,0,pl+HALF_PADDLE,WHITE);
}





