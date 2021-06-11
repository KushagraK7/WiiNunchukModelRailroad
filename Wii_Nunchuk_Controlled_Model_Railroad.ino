/*
 * Arduino code to control a model railway layout's locomotive and multiple turnouts usig a Wii Nunchuk.
 * 
 * By KushagraK7: https://www.instructables.com/member/KushagraK7/
 * An Adafruit Motor Shield V2 is used for driving the locomotive and the turnouts.
 * 
 * Feel free to modify the code to suit your requirements.
 */
#include <Wire.h>
#include <Nunchuk.h>
#include <Adafruit_MotorShield.h>

#define A 4//connecting segment A to PIN4
#define B 5// connecting segment B to PIN5
#define C 6// connecting segment C to PIN6
#define D 7// connecting segment D to PIN7
#define E 8// connecting segment E to PIN8
#define F 9// connecting segment F to PIN9
#define G 10// connecting segment G to PIN10

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *turnout1 = AFMS.getMotor(1);
Adafruit_DCMotor *turnout2 = AFMS.getMotor(2);
Adafruit_DCMotor *turnout3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor = AFMS.getMotor(4);

int x, y, x1, y1, ax, ay;
int s = 0, c = 1;
int d, z, cc, tc = 1;
int noOfTurnouts = 3;

void motorRun(int s)
{
  if (s < 0)
  {
    motor->setSpeed(-s);
    motor->run(BACKWARD);
  }

  if (s > 0)
  {
    motor->setSpeed(s);
    motor->run(FORWARD);
  }

  if (s == 0)
  {
    motor->setSpeed(s);
    motor->run(RELEASE);
  }
}

void display(int num)
{

  if (num == 0)
  {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 0);
    digitalWrite(G, 1);
  } else if (num == 1) {
    digitalWrite(A, 0);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
  } else if (num == 2) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 0);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 0);
  } else if (num == 3) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 0);
  } else if (num == 4) {
    digitalWrite(A, 0);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 5) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 6) {
    digitalWrite(A, 1);
    digitalWrite(B, 0);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 7) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(F, 0);
    digitalWrite(G, 0);
  } else if (num == 8) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  } else if (num == 9) {
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    digitalWrite(E, 0);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
  }
}

void turnout1_side(){
turnout1->setSpeed(255);
turnout1->run(FORWARD);
delay(100);
turnout1->setSpeed(0);
turnout1->run(RELEASE);
}

void turnout1_straight(){
turnout1->setSpeed(255);
turnout1->run(BACKWARD);
delay(100);
turnout1->setSpeed(0);
turnout1->run(RELEASE);
}

void turnout2_side(){
turnout2->setSpeed(255);
turnout2->run(FORWARD);
delay(100);
turnout2->setSpeed(0);
turnout2->run(RELEASE);
}

void turnout2_straight(){
turnout2->setSpeed(255);
turnout2->run(BACKWARD);
delay(100);
turnout2->setSpeed(0);
turnout2->run(RELEASE);
}

void turnout3_side(){
turnout3->setSpeed(255);
turnout3->run(FORWARD);
delay(100);
turnout3->setSpeed(0);
turnout3->run(RELEASE);
}

void turnout3_straight(){
turnout3->setSpeed(255);
turnout3->run(BACKWARD);
delay(100);
turnout3->setSpeed(0);
turnout3->run(RELEASE);
}

void switchTurnoutSide(int no)
{
  switch(no)
  {
    case 1: turnout1_side(); break;
    case 2: turnout2_side(); break;
    case 3: turnout3_side(); break;
  }
}

void switchTurnoutSraight(int no)
{
  switch(no)
  {
    case 1: turnout1_straight(); break;
    case 2: turnout2_straight(); break;
    case 3: turnout3_straight(); break;
  }
}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();
  AFMS.begin();

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);


  // Change TWI speed for nuchuk, which uses Fast-TWI (400kHz)
  Wire.setClock(400000);

  // nunchuk_init_power(); // A1 and A2 is power supply
  nunchuk_init();



}

void loop() {
  // put your main code here, to run repeatedly:

  nunchuk_read();

  x1 = nunchuk_joystickX();

  y1 = nunchuk_joystickY();

  z = nunchuk_buttonZ();

  cc = nunchuk_buttonC();

  ax = nunchuk_accelX();

  if (x1 <= 5) x = map(x1, -127, 5, -128, 0);

  if (x1 > 5) x = map(x1, 6, 128, 0, 128);

  if (y1 <= 2) y = map(y1, -128, 2, -128, 0);

  if (y1 > 2) y = map(y1, 3, 127, 0, 128);

  if (y < 0) d = map(y, -128, 0, 10, 80);

  if (y > 0) d = map(y, 0, 128, 80, 10);

  if (x < -120) switchTurnoutSraight(tc);

  if (x > 120) switchTurnoutSide(tc);

  if (y > 0 && s < 255) s += 1;

  if (y < 0 && s > -255) s -= 1;

  if (z == 1)
  {
    if (s < 0)
      for (s = s; s != 0; s++)
      {
        motorRun(s);
        delay(60);
      }
    if (s > 0)
      for (s = s; s != 0; s--)
      {
        motorRun(s);
        delay(60);
      }
  }

  if (cc == 1) s = 0;

  if (ax > -10 && ax < 10 && c != 0)
  {
    if(c == -1) tc--;

    if(c == 1) tc++;
    
    c = 0;
  }

  if (ax > 60 && ax < 180 && c == 0 && tc < noOfTurnouts)
  {
    c = 1;
  }

  if (ax < -60 && ax > -180 && c == 0 && tc > 1)
  { 
    c = -1;
  }

  display(tc);

  motorRun(s);

  delay(d);



  Serial.print(tc);
  Serial.print("   ");
  Serial.print(c);
  Serial.print("   ");
  Serial.println(ax);



}
