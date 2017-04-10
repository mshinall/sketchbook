

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define INTERVAL 10

#define XD 8
#define YD 4

#define XT 128/XD
#define YT 32/YD

int px[XT][YT];

void setup()   {                
  Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  
  randomSeed(analogRead(0));
  initBoard();
  drawBoard();
}

void loop() {
  initBoard();
  drawBoard();
  delay(INTERVAL);
}

void drawText(int x, int y, char* text) {
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(x, y);
  display.println(text);
  display.display(); 
}

//void drawSplash() {
//  display.clearDisplay();
//  drawBox();  
//  drawText(44, 6, "Mathias");
//  drawText(44, 16, "Shinall");
//  delay(2000);
//  display.clearDisplay();
//  drawBox();  
//  drawText(40, 12, "Presents");
//  delay(2000);
//  display.clearDisplay();
//  drawBox();  
//  drawText(26, 12, "John Conway's");
//  delay(2000);
//  display.clearDisplay();
//  drawBox();  
//  drawText(26, 12, "Game of Life");
//  delay(2000);
//}

//void drawBox() {
//  display.drawLine(XB, YB, XT, YB, WHITE);
//  display.drawLine(XT, YB, XT, YT, WHITE);
//  display.drawLine(XT, YT, XB, YT, WHITE);
//  display.drawLine(XB, YT, XB, YB, WHITE);
//}

void initBoard() {
  display.clearDisplay();
  for(int x = 0; x < XT; x++) {
    for(int y = 0; y < YT; y++) {
      px[x][y] = random(0, 2);
    }
  }
}

void drawBoard() {
  for(int x = 0; x < XT; x++) {
    for(int y = 0; y < YT; y++) {
      if(px[x][y] == 1) {
        display.fillRect(x*XD+1, y*YD+1, XD-1, YD-1, WHITE);
      } else {
        display.fillRect(x*XD+1, y*YD+1, XD-1, YD-1, BLACK);
      }
    }
  }
  display.display();
}

void evalPixel(int x, int y) {
  /*
  * For a space that is 'populated':
  *    Each cell with one or no neighbors dies, as if by solitude.
  *    Each cell with four or more neighbors dies, as if by overpopulation.
  *    Each cell with two or three neighbors survives.
  * For a space that is 'empty' or 'unpopulated'
  *    Each cell with three neighbors becomes populated.
  */
  
}





