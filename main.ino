/*
* Project Name:   Forest Conservation Robot(e-Yantra Project)
* Author List:    Mehta Raj Vinodbhai,
*                 Purohit Mahima
* 
* Filename:       main.ino
* Functions:      setup()
*                 receiveData(int byteCount)
*                 sendData()
*                 loop()
*                 servo_filter()
*                 lookRight()
*                 lookLeft()
*                 ultra()
*                 moveBackward()
*                 moveForward()
*                 
  * Global Variables: 
                      spd1, spd2,distance,speedSet,ct,d,distanceR, distanceL,seru,setu,setd,serd;data,ispd1,ispd2,state
                      MAX_DISTANCE MAX_SPEED 
*
*/


#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int state = 0;
int enablei2c=10;//pin for enable i2c
int ispd1=0,ispd2=0;

#define MAX_DISTANCE 80
#define MAX_SPEED 20 // sets speed of DC  motors
// ultrasonic
const int  trigPin = 10, echoPin = 12;
int data;

//servo motor
Servo myservo1;
Servo myservo2;
#define dir myservo1.write
#define uls myservo2.write
int seru = 0, setu = 0, setd = 90, serd = 90;

int distance = 0;
int speedSet = 0;
int ct = 0, d = 0;
int distanceR = 0;
int distanceL =  0;

//motor
int8_t spd1 = 0, spd2 = 0;
int8_t mot2 = 11, mot21 = 6;
int8_t mot1 = 3, mot11 = 4;


/*
*
* Function Name:  setup()
* Input:          none
* Output:         define the pins mode input,output
* Logic:          at time of execution of the code that function run first
* Example Call:   setup()
*
*/
void setup()
{

  pinMode(10, INPUT);
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  //motor
  pinMode(mot1, OUTPUT); pinMode(mot11, OUTPUT);
  pinMode(mot2, OUTPUT); pinMode(mot21, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  myservo1.attach(A0);
  myservo2.attach(A1);
  uls(seru);
  dir(serd);
  distance = ultra();
  //Serial.begin(115200);
}

/*
*
* Function Name:  receiveData(int byteCount) 
* Input:          byteCount mean limitation of the size of the data 
* Output:         get the data from the raspberry pi to arduino nano 
* Logic:          read the data spd1 and spd2 from the raspberry pi using the flage logic to differentiate data
* Example Call:   receiveData(int byteCount) 
*
*/
void receiveData(int byteCount) {
   if(Wire.available()) {
      if (state == 0) {
        ispd1 = Wire.read();
        state = 1;
      }
      else {
        ispd2 = Wire.read();
        state = 0;
      }
  }
}

/*
*
* Function Name:  sendData()
* Input:          none
* Output:         respone to the raspberry pi.data travel from arduino to raspberry pi
* Logic:          for the purp[ose of seprating two data use flage logic to differentiate
* Example Call:   sendData()
*
*/
void sendData() {Wire.write(state);}

/*
*
* Function Name:  loop()
* Input:          enablei2c pin data from the raspberry pi
* Output:         main execution of the robot through the help of the subroutines
* Logic:          here the robot enablei2c=1 then it travel through the help of the web control data otherwise obstacle avoiding logic
* Example Call:   loop()
*
*/
void loop()
{
  if(digitalRead(enablei2c)){spd1=ispd1;spd2=ispd2;applyspeed();}
  else  {
        switch (distance)
        {
          case 0 ... 10:
                  while(d==0)
                  {
                    lookRight();
                    lookLeft();  
                    if (distanceR >= distanceL) {setd = 150;dir(serd);servo_acc_dacc();d=1;}    //0 to 180
                    else if (distanceR <distanceL) {setd = 50;uls(seru);servo_acc_dacc();d=1;}
                  }
            break;
          default: 
              setd = setu = 90; uls(seru); moveForward(); applyspeed();
              if(ct>1000){dir(serd);d=ct=0;}else{ct++;} 
              break;
        }
        distance = ultra();
        servo_acc_dacc();
  }
}
/*
*
* Function Name:  servo_acc_dacc()
* Input:          none
* Output:         smooth rotation of the servo motor
* Logic:          the logic of the acc_dacc of the servo motor angle
* Example Call:   servo_acc_dacc()
*
*/

void servo_acc_dacc()
{
  if (serd < setd)serd++; else if (serd > setd)serd--; else serd = setd;
  if (seru < setu)seru++; else if (seru > setu)seru--; else seru = setu;
}
/*
*
* Function Name:  lookRight()
* Input:          none
* Output:         temporary value of the distance
* Logic:          ultrasonic servo rotate right side and get the temp. distance data
* Example Call:   lookRight()
*
*/
int lookRight() {setu = 30;uls(seru);servo_acc_dacc();delay(500);distanceR=0;distanceR = ultra();return distanceR;}
/*
*
* Function Name:  lookLeft()
* Input:          none
* Output:         temporary value of the distance
* Logic:          ultrasonic servo rotate left side and get the temp. distance data
* Example Call:   lookLeft()
*
*/
int lookLeft() {setu = 150;uls(seru);servo_acc_dacc();delay(500);distanceL=0;distanceL = ultra();return distanceL;}
/*
*
* Function Name:  ultra()
* Input:          none
* Output:         value of the distance
* Logic:          getting the ultrasonic value as distance in 6000 miliseconds
* Example Call:   ultra()
*
*/
int ultra()
{
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    data = pulseIn(echoPin, HIGH, 6000);
    data = data * 0.017;
    return data;
}
/*
*
* Function Name:  moveForward()
* Input:          none
* Output:         value of spd1 and spd2 
* Logic:          increase the speed
* Example Call:   moveForward()
*
*/
void moveForward() {for (speedSet = 0; speedSet < MAX_SPEED; speedSet++) {spd1 = spd2 = speedSet;}}
/*
*
* Function Name:  moveBackward()
* Input:          none
* Output:         value of spd1 and spd2 
* Logic:          decrease the speed
* Example Call:   moveBackward()
*
*/
void moveBackward(){for (speedSet = 0; speedSet < MAX_SPEED; speedSet--) {spd1 = spd2 = -speedSet;}}
