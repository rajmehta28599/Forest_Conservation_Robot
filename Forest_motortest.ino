
//    MOTOR
  int mot2 = 11, mot21 = 6;
  int mot1 = 3, mot11 = 4;
  int spd1 = 0, spd2 = 0;
  
void setup() 
{
    pinMode(mot1,OUTPUT); pinMode(mot11,OUTPUT);
    pinMode(mot2,OUTPUT); pinMode(mot21,OUTPUT);
}

void loop() {
    spd1=100;
    spd2=100;
    applyspeed();
}

void applyspeed()
{
    switch(spd1)
    {
      case -255 ... -1:    analogWrite(mot1, -spd1);digitalWrite(mot11 , HIGH);      break;
      case 1 ... 255:      analogWrite(mot1, spd1); digitalWrite(mot11 , LOW);     break;
      default:             analogWrite(mot1,0);     digitalWrite(mot11 , LOW);      break;
      
    }
    switch(spd2)
    {
      case -255 ... -1:    analogWrite(mot2, -spd2);digitalWrite(mot21 , LOW);    break;
      case 1 ... 255:      analogWrite(mot2, spd2); digitalWrite(mot21 , HIGH);     break;
      default:             analogWrite(mot2, 0); digitalWrite(mot21 , LOW);        break;
    }
}


