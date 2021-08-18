#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int bp = 50;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);

  bottomServo.write(bp);

  Serial.begin(9600);
}

void loop() {
  int color;
  topServo.write(180);
  delay(2000);

  for (int i = 180; i > 105; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(1000);

  color = readColor();
  delay(10);

  switch (color) {
    case 1:
      for (int i = 50; i < 50; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 50;
      break;

    case 2:
      for (int i = 50; i < 75; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 75;
      break;

    case 3:
      for (int i = 50; i < 100; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 100;
      break;

    case 4:
      for (int i = 50; i < 125; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 125;
      break;

    case 5:
      for (int i = 50; i < 150; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 150;
      break;

    case 6:
      for (int i = 50; i < 175; i++) {
        bottomServo.write(i);
        delay(10);
      }
      bp = 175;
      break;

    case 0:
      break;
  }
  delay(1000);

  for (int i = 104; i > 45; i--) {
    topServo.write(i);
    delay(15);
  }
  delay(1000);

  for (int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color = 0;

  for (int i = bp; i > 50; i--) {
    bottomServo.write(i);
    delay(10);
  }
}

// Custom Function - readColor()
int readColor() {
  int t = 50;
  // Setting red filtered photodiodes to be read
  int R = readR(t);
  delay(50);

  // Setting Green filtered photodiodes to be read
  int G = readG(t);
  delay(50);

  // Setting Blue filtered photodiodes to be read
  int B = readB(t);
  delay(50);

  int color;
  if (R > 170 & R<210 & G>290 & G<345 & B>245 & B < 290 ) {
    color = 1; // Red
  }
  else if (R > 140 & R<170 & G>250 & G<315 & B>230 & B < 280 ) {
    color = 2; // Orange
  }
  else if (R > 185 & R<255 & G>205 & G<250 & B>190 & B < 265 ) {
    color = 3; // Green
  }
  else if (R > 110 & R<165 & G>150 & G<200 & B>180 & B < 230 ) {
    color = 4; // Yellow
  }
  else if (R > 165 & R<260 & G>200 & G<330 & B>180 & B < 290 ) {
    color = 5; // Brown
  }
  else if (R > 210 & R<310 & G>220 & G<265 & B>140 & B < 190) {
    color = 6; // Blue
  }
  else {
    color = 7;
  }
  printValues(R, G, B);
    Serial.println(color);
  return color;
}

int readR(int t) {
  int R = 0;
  for (int i = 0; i < t;  i++)
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    R += pulseIn(sensorOut, LOW);
    delay(2);
  }

  return R / t;
}

int readG(int t) {
  int G = 0;
  for (int i = 0; i < t;  i++)
  {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    G += pulseIn(sensorOut, LOW);
    delay(2);
  }
  return G / t;
}

int readB(int t) {
  int B = 0;
  for (int i = 0; i < t;  i++)
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    B += pulseIn(sensorOut, LOW);
    delay(2);
  }
  return  B / t;
}

void printValues(int R, int G, int B) {
  Serial.print("R= ");//printing name
  Serial.print(R);//printing RED color frequency
  Serial.print("  ");

  Serial.print("G= ");//printing name
  Serial.print(G);//printing RED color frequency
  Serial.print("  ");

  Serial.print("B= ");//printing name
  Serial.print(B);//printing RED color frequency
  Serial.println("  ");
}
