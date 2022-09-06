
#include <Servo.h>
Servo myservo;



#define LOADER_PIN  13
int COND_ON = 1;
int COND_OFF =0;   



void setup() {
  Serial.begin(115200);
  myservo.attach(9);
  pinMode(LOADER_PIN,OUTPUT);
  digitalWrite(LOADER_PIN,LOW);
  myservo.write(20); 
}

void loop() {

  BOT_LOADER(COND_ON);
 
}

void BOT_LOADER (int cond){
  if(cond == 1){
    digitalWrite(LOADER_PIN,HIGH);
    delay(500);
    myservo.write(60); 
  }else if(cond == 0 ){
    digitalWrite(LOADER_PIN,LOW);
    delay(500);
    myservo.write(20);
  }
}
