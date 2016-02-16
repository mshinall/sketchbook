int r = 9;
int g = 10;
int b = 11;
int sr = 7;
int sg = 6;
int sb = 5;

int top = 245;
int btm = 10;
int stp = 1;

int xr = top;
int xg = top;
int xb = top;

boolean dr = true;
boolean dg = true;
boolean db = true;

void setup() {
  pinMode(sr, OUTPUT);
  pinMode(sg, OUTPUT);
  pinMode(sb, OUTPUT);
}

void loop() {
  if(xr >= top) {
    xr == top;
    dr = !dr;
  }
  if(xr <= btm) {
    xr == btm;
    dr = !dr;
  }

  if(xg >= top) {
    xg == top;
    dg = !dg;
  }
  if(xg <= btm) {
    xg == btm;
    dg = !dg;
  }

  if(xb >= top) {
    xb == top;
    db = !db;
  }
  if(xb <= btm) {
    xb == btm;
    db = !db;
  }

  analogWrite(r, xr);
  analogWrite(g, xg);
  analogWrite(b, xb);
  
  if(digitalRead(sr)) {
    if(dr) {
      xr += stp;
    } else {
      xr -= stp;
    }
  }
  if(digitalRead(sg)) {
    if(dg) {
      xg += stp;
    } else {
      xg -= stp;
    }
  }
  if(digitalRead(sb)) {
    if(db) {
      xb += stp;
    } else {
      xb -= stp;
    }
  }

  delay(10);
}

