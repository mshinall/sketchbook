/*
   Small Program to Simulate a Numpad using a 2.4" TFT Touchscreen
   Program does not act as an USB HID Device, for reference purposes only
   Tested on Arduino UNO Only and 0x9341
   By William Tavares

   Note:
   This version is coplete with styling and numbers,
   if you want the smaller version get the "numpad-layout" program
   from my Github https://github.com/williamtavares/Arduino-Uno-NumPad

   Open the Serial Monitor to see the program running
   Enjoy!
*/

#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 1
#define MAXPRESSURE 1000

const char j[4] = {'-','\\','|','/'};

int x1 = 0;
int y1 = 0;
int x2 = 0;
int y2 = 0;
int i = 0;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() {
  Serial.begin(9600);

  tft.reset();
  delay(1);
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  
  //Background color
  tft.fillScreen(BLACK);

  tft.setTextSize(2);
  tft.setTextColor(LIGHTGREY);
  tft.setCursor(0, 0);
  tft.print("id: ");
  tft.println(identifier);
  tft.print("width: ");
  tft.println(tft.width());
  tft.print("height: ");
  tft.println(tft.height());
  
  tft.print("count: ");
  x1 = tft.getCursorX();
  y1 = tft.getCursorY();
  tft.println(i);

  tft.print("spin: ");
  x2 = tft.getCursorX();
  y2 = tft.getCursorY();
  tft.println(j[i%4]);
}

void loop() {
  delay(100);
  tft.setTextColor(BLACK);
  tft.setCursor(x1, y1);  
  tft.println(i);
  tft.setCursor(x2, y2);
  tft.println(j[i%4]);

  i++;
  tft.setTextColor(LIGHTGREY);  
  tft.setCursor(x1, y1);  
  tft.println(i);
  tft.setCursor(x2, y2);
  tft.println(j[i%4]);

  
  
    
}


