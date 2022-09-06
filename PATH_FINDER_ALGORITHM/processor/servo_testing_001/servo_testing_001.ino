
#include <Servo.h>

Servo myservo;


int pos = 0;


void setup() {
  Serial.begin(115200);
  myservo.attach(9);
}

void loop() {
  delay(50);
  myservo.write(20); 
 
}
