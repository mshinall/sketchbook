 
 int SR_SER_PIN = 2;
 int SR_LCH_PIN = 1;
 int SR_CLK_PIN = 0;

int DC_RST_PIN = 3;
int DC_CLK_PIN = 4; 

int DLAY = 0;
int SDLAY = 100;

#define ltr_A     {B00000000,B00111100,B01000010,B01000010,B01000010,B01111110,B01000010,B01000010,B01000010,B00000000}
#define ltr_B     {B00000000,B01111100,B01000010,B01000010,B01111100,B01000010,B01000010,B01000010,B01111100,B00000000}
#define ltr_C     {B00000000,B00111110,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B00111110,B00000000}
#define ltr_D     {B00000000,B01111100,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B01111100,B00000000}
#define ltr_E     {B00000000,B01111110,B01000000,B01000000,B01111100,B01000000,B01000000,B01000000,B01111110,B00000000}
#define ltr_F     {B00000000,B01111110,B01000000,B01000000,B01111100,B01000000,B01000000,B01000000,B01000000,B00000000}
#define ltr_G     {B00000000,B00111100,B01000010,B01000010,B01000000,B01000111,B01000010,B01000010,B00111100,B00000000}
#define ltr_H     {B00000000,B01000010,B01000010,B01000010,B01111110,B01000010,B01000010,B01000010,B01000010,B00000000}
#define ltr_I     {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000}
#define ltr_J     {B00000000,B00011100,B00001000,B00001000,B00001000,B00001000,B01001000,B01001000,B00110000,B00000000}
#define ltr_K     {B00000000,B01000100,B01001000,B01010000,B01100000,B01010000,B01001000,B01000100,B01000010,B00000000}
#define ltr_L     {B00000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01111110,B00000000}
#define ltr_M     {B00000000,B01000100,B10101010,B10010010,B10010010,B10000010,B10000010,B10000010,B10000010,B00000000}
#define ltr_N     {B00000000,B01000010,B01100010,B01010010,B01001010,B01001010,B01001010,B01000110,B01000010,B00000000}
#define ltr_O     {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000}
#define ltr_P     {B00000000,B00111100,B01000010,B01000010,B01000010,B01111100,B01000000,B01000000,B01000000,B00000000}
#define ltr_Q     {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001}
#define ltr_R     {B00000000,B00111100,B01000010,B01000010,B01000010,B01111100,B01000100,B01000010,B01000010,B00000000}
#define ltr_S     {B00000000,B00111100,B01000010,B01000000,B01000000,B00111100,B00000010,B01000010,B00111100,B00000000}
#define ltr_T     {B00000000,B11111110,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000}
#define ltr_U     {B00000000,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000}
#define ltr_V     {B00000000,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000}
#define ltr_W     {B00000000,B10000010,B10000010,B10000010,B10000010,B10010010,B10010010,B10101010,B01000100,B00000000}
#define ltr_X     {B00000000,B01000010,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B01000010,B00000000}
#define ltr_Y     {B00000000,B10000010,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000}
#define ltr_Z     {B00000000,B01111110,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B01111110,B00000000}
#define lit_a {B00000000,B00000000,B00000000,B00000000,B00111000,B01000100,B01000101,B01000101,B00111010,B00000000}
#define lit_b {B00000000,B00000000,B00100000,B00100000,B00100000,B00111100,B00100010,B00100010,B00111100,B00000000}
#define lit_c {B00000000,B00000000,B00000000,B00000000,B00111100,B01000000,B01000000,B01000000,B00111100,B00000000}
#define lit_d {B00000000,B00000000,B00000100,B00000100,B00000100,B00111100,B01000100,B01000100,B00111100,B00000000}
#define lit_e {B00000000,B00000000,B00000000,B00111000,B01000100,B01000100,B01111000,B01000000,B00111100,B00000000}
#define lit_f {B00000000,B00011000,B00100100,B00100000,B00100000,B01110000,B00100000,B00100000,B00100000,B00000000}
#define lit_g {B00000000,B00011100,B00100010,B00100010,B00011110,B00000010,B00000010,B00010010,B00001100,B00000000}
#define lit_h {B00000000,B01000000,B01000000,B01000000,B01000000,B01111000,B01000100,B01000100,B01000100,B00000000}
#define lit_i {B00000000,B00000000,B00010000,B00000000,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000}
#define lit_j {B00000000,B00000000,B00010000,B00000000,B00010000,B00010000,B00010000,B01010000,B00110000,B00000000}
#define lit_k {B00000000,B00000000,B00000000,B01001000,B01010000,B01100000,B01100000,B01010000,B01001000,B00000000}
#define lit_l {B00000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B00000000}
#define lit_m {B00000000,B00000000,B00000000,B00110100,B01001010,B01001010,B01001010,B01001010,B01001010,B00000000}
#define lit_n {B00000000,B00000000,B00000000,B01111000,B01000100,B01000100,B01000100,B01000100,B01000100,B00000000}
#define lit_o {B00000000,B00000000,B00000000,B00000000,B00011100,B00100010,B00100010,B00100010,B00011100,B00000000}
#define lit_p {B00000000,B00000000,B00000000,B00011100,B00100010,B00100010,B00111100,B00100000,B00100000,B00100000}
#define lit_q {B00000000,B00000000,B00000000,B00111000,B01000100,B01000100,B00111100,B00000100,B00000100,B00000100}
#define lit_r {B00000000,B00000000,B00000000,B00111000,B01000000,B01000000,B01000000,B01000000,B01000000,B00000000}
#define lit_s {B00000000,B00000000,B00111000,B01000100,B01000000,B00111000,B00000100,B01000100,B00111000,B00000000}
#define lit_t {B00000000,B00100000,B00100000,B00100000,B01111000,B00100000,B00100000,B00100010,B00011100,B00000000}
#define lit_u {B00000000,B00000000,B00000000,B00000000,B01000100,B01000100,B01000100,B01000100,B00111000,B00000000}
#define lit_v {B00000000,B00000000,B00000000,B01000100,B01000100,B01000100,B01000100,B00101000,B00010000,B00000000}
#define lit_w {B00000000,B00000000,B00000000,B00000000,B01000100,B01000100,B01010100,B01010100,B00101000,B00000000}
#define lit_x {B00000000,B00000000,B00000000,B00000000,B00000000,B00100100,B00011000,B00011000,B00100100,B00000000}
#define lit_y {B00000000,B00000000,B01000100,B01000100,B00111100,B00000100,B00000100,B00000100,B00111000,B00000000}
#define lit_z {B00000000,B00000000,B00000000,B00000000,B01111100,B00001000,B00010000,B00100000,B01111100,B00000000}
#define space {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}
#define num_0 {B00000000,B00111100,B01000110,B01001010,B01001010,B01001010,B01010010,B01100010,B00111100,B00000000}
#define num_1 {B00000000,B00001000,B00011000,B00001000,B00001000,B00001000,B00001000,B00001000,B00011100,B00000000}
#define num_2 {B00000000,B00111100,B01000010,B00000100,B00001000,B00010000,B00100000,B01000000,B01111110,B00000000}
#define num_3 {B00000000,B01111110,B00000010,B00000010,B00011100,B00000010,B00000010,B01000010,B00111100,B00000000}
#define num_4 {B00000000,B00000100,B00001100,B00010100,B00100100,B01000100,B01111110,B00000100,B00000100,B00000000}
#define num_5 {B00000000,B01111110,B01000000,B01000000,B00111100,B00000010,B00000010,B00000010,B01111100,B00000000}
#define num_6 {B00000000,B00111100,B01000000,B01000000,B01111100,B01000010,B01000010,B01000010,B00111100,B00000000}
#define num_7 {B00000000,B01111110,B00000010,B00000100,B00001000,B00010000,B00010000,B00010000,B00010000,B00000000}
#define num_8 {B00000000,B00111100,B01000010,B01000010,B00111100,B01000010,B01000010,B01000010,B00111100,B00000000}
#define num_9 {B00000000,B00111100,B01000010,B01000010,B01000010,B00111110,B00000010,B00000010,B00111100,B00000000}
#define times {B00000000,B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000,B00000000}

const int dataLength = 16;
byte data[dataLength][10] = {
  ltr_M,lit_a,lit_t,lit_h,lit_i,lit_a,lit_s,
  space,
  ltr_S,lit_h,lit_i,lit_n,lit_a,lit_l,lit_l
};
void setup() {
  for(int i = 0; i < 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  dcReset();
}

void loop() {
  for(int x = 0; x < dataLength; x++) { //letters
    for (int z = 0; z < 8; z++) { //scrolling
      //for(int t = 0; t < 8; t++) { //scroll delay
        for(int y = 0; y < 10; y++) { //bytes in letters
          byte temp = data[x][y]; 
          byte temp_2=data[x + 1][y];
          output((temp << z) + (temp_2 >> 7 - z));
          dcClock();
        }
      //}
      delay(SDLAY);
    }
  }
}
 
void wait() {
  delay(DLAY);
}

void output(byte b) {
  shiftOut(SR_SER_PIN, SR_CLK_PIN, MSBFIRST, b);
  srLatch();
  //shiftOut(SR_SER_PIN, SR_CLK_PIN, MSBFIRST, B00000000);
  //srLatch();
}

void srLatch() {
  pulse(SR_LCH_PIN);
}

void dcClock() {
  pulse(DC_CLK_PIN);
}

void dcReset() {
  pulse(DC_RST_PIN);
}

void pulse(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}
