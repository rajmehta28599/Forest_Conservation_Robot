#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 10
#define ECHO_PIN 12
#define MAX_DISTANCE 80
#define MAX_SPEED 20 // sets speed of DC  motors

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo1;
Servo myservo2;

#define dir myservo1.write
#define uls myservo2.write
int seru=0,setu=0,setd=90,serd=90;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;
int8_t mot2 = 11, mot21 = 6;
int8_t mot1 = 3, mot11 = 4;
int8_t spd1 = 0, spd2 = 0;
int ct =0, ctt=0;
int distanceR = 0;
int distanceL =  0;

void setup()
{
  pinMode(mot1, OUTPUT); pinMode(mot11, OUTPUT);
  pinMode(mot2, OUTPUT); pinMode(mot21, OUTPUT);

  //Serial.begin(115200);
  myservo1.attach(A0);
  myservo2.attach(A1);
  uls(seru);
  dir(serd);
  distance = readPing();
}

void loop()
{
  switch(distance)
  {
    case 0 ... 25:
      spd1=spd2=0;
      distanceR = lookRight();
      while(ctt<10000){ctt++;}
      distanceL = lookLeft();
      while(ctt<10000){ctt++;}
      spd1=spd2=0;
      if (distanceR >= distanceL) { while (ct<=10000) {ct++;setd=150;dir(serd);setu=50;uls(seru);servo_filter(); moveForward();applyspeed();  }}           //r=120//l=50
      else if(distanceR < distanceL){ while (ct<=10000) {ct++;setd=30;dir(serd);setu=150;uls(seru);servo_filter(); moveForward();applyspeed();  }}
      else { while (ct<=10000) {ct++;setd=50;dir(serd);setu=90;uls(seru);servo_filter(); moveForward();applyspeed();  }}
      break;
    default: setd=setu=90;dir(serd);uls(seru);ct = 0;moveForward();break;  
  }
  distance = readPing();
  servo_filter();
  applyspeed();
  
}
void servo_filter()
{
  if(serd<setd)serd++;else if(serd>setd)serd--;else serd=setd;
  if(seru<setu)seru++;else if(seru>setu)seru--;else seru=setu;
}
int lookRight(){ctt=0;setu=50;uls(seru);servo_filter();int distanceR = readPing();return distanceR;}
int lookLeft() {ctt=0;setu=150;uls(seru);servo_filter();int distanceL = readPing();return distanceL;}

int readPing() {int cm = sonar.ping_cm();if (cm == 0) {cm = 250;}  return cm;}

void moveForward() {for (speedSet = 0; speedSet < MAX_SPEED; speedSet++) {spd1 = spd2 = speedSet;}}
void moveBackward() {for (speedSet = 0; speedSet < MAX_SPEED; speedSet++) {spd1 = spd2 = -speedSet;}}
