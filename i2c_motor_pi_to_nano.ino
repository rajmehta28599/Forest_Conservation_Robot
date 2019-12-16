#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
//    MOTOR
int mot2 = 11, mot21 = 6;
int mot1 = 3, mot11 = 4;
int spd1 = 0, spd2 = 0,f;

void setup() {
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  pinMode(mot1, OUTPUT); pinMode(mot11, OUTPUT);
  pinMode(mot2, OUTPUT); pinMode(mot21, OUTPUT);

  Serial.println("Ready!");
}
void loop() {
}

// callback for received data
void receiveData(int byteCount) 
{
  while (Wire.available()) 
  {
    Serial.print(" spd1=");
    Serial.print(spd1);
    Serial.print(" spd2=");
    Serial.print(spd2);
    Serial.print(" f=");
    Serial.println(f);
      if (f == 0) 
      {
          spd1 = Wire.read();
          f = 1;
      }
      else 
      {
        spd2 = Wire.read();
        f = 0;
      }
  }
}
void sendData() { Wire.write(f);}


void applyspeed()
{
  switch (spd1)
  {
    case -255 ... -1:    analogWrite(mot1, -spd1); digitalWrite(mot11 , HIGH);      break;
    case 1 ... 255:      analogWrite(mot1, spd1); digitalWrite(mot11 , LOW);     break;
    default:             analogWrite(mot1, 0);     digitalWrite(mot11 , LOW);      break;

  }
  switch (spd2)
  {
    case -255 ... -1:    analogWrite(mot2, -spd2); digitalWrite(mot21 , LOW);    break;
    case 1 ... 255:      analogWrite(mot2, spd2); digitalWrite(mot21 , HIGH);     break;
    default:             analogWrite(mot2, 0); digitalWrite(mot21 , LOW);        break;
  }
}
