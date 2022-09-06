#include <NewPing.h>

//PIN CONFIGURATION FOR ULTRASONIC SENSOR
#define X_TRIGGER_PIN  2  
#define X_ECHO_PIN     4  

#define Y_TRIGGER_PIN  7  
#define Y_ECHO_PIN     8  

#define XD_TRIGGER_PIN  13  
#define XD_ECHO_PIN     0  

#define YD_TRIGGER_PIN  1  
#define YD_ECHO_PIN     A5 

//MOTOR DRIVER PIN CONFIGURATION
#define M1_FORWARD 10  
#define M1_BACKWARD 11 

#define M2_FORWARD 12  
#define M2_BACKWARD A0 

#define M3_FORWARD A1  
#define M3_BACKWARD A2 

#define M4_FORWARD A3
#define M4_BACKWARD A4

#define M1_ENB 3
#define M2_ENA 5

#define M3_ENB 6
#define M4_ENA 9

void setup() {
  Serial.begin(115200);
  //MOTOR DRIVER PIN CONFIGURATION
  pinMode(M1_FORWARD, OUTPUT);
  pinMode(M1_BACKWARD, OUTPUT);

  pinMode(M2_FORWARD, OUTPUT);
  pinMode(M2_BACKWARD, OUTPUT);

  pinMode(M3_FORWARD, OUTPUT);
  pinMode(M3_BACKWARD, OUTPUT);

  pinMode(M4_FORWARD, OUTPUT);
  pinMode(M4_BACKWARD, OUTPUT);

  pinMode(M1_ENB, OUTPUT);
  pinMode(M2_ENA, OUTPUT);

  pinMode(M3_ENB, OUTPUT);
  pinMode(M4_ENA, OUTPUT);


//SPEED CONTROL
analogWrite(M1_ENB,HIGH);
analogWrite(M2_ENA,HIGH);
analogWrite(M3_ENB,HIGH);
analogWrite(M4_ENA,HIGH);
/////////////////////////

  //MOTOR DRIVER INITIAL CONDITION
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,HIGH);

  digitalWrite(M2_FORWARD,HIGH);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,HIGH);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,HIGH);

  delay(5000);
  
}

void loop() {
}
