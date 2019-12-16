//    SERVO
#include <Servo.h>
Servo srvup;
#define s srvup.write
int ct=180,f;
void setup() {
  srvup.attach(A0);
}

void loop() {
  if(ct<=180){ct--;}
  s(ct);
}

