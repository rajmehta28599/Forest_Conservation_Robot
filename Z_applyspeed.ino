
/*
*
* Function Name:  applyspeed()
* Input:          none
* Output:         speed and direction of the motor
* Logic:          here if the speed of motor is positive the one direction and the negative then another direction and default for stop the motion
* Example Call:   applyspeed()
*
*/
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
