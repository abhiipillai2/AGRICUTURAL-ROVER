#include <NewPing.h>

//PIN CONFIGURATION FOR ULTRASONIC SENSOR
#define X_TRIGGER_PIN  2  
#define X_ECHO_PIN     3  

#define Y_TRIGGER_PIN  4  
#define Y_ECHO_PIN     5  

#define XD_TRIGGER_PIN  6  
#define XD_ECHO_PIN     7  

#define YD_TRIGGER_PIN  8  
#define YD_ECHO_PIN     9 

//MOTOR DRIVER PIN CONFIGURATION
#define M1_FORWARD 10  
#define M1_BACKWARD 11 

#define M2_FORWARD 12  
#define M2_BACKWARD A0 

#define M3_FORWARD A1  
#define M3_BACKWARD A2 

#define M4_FORWARD A3
#define M4_BACKWARD A4 

//MAXIMUM DISTANCE FOR ULTARSONIC SENSOR
#define MAX_DISTANCE 4000

//PARAMETERS
float X_PING_DISTACE;
float Y_PING_DISTACE;
float XD_PING_DISTACE;
float YD_PING_DISTACE;

int W0 = 4000;
int W = 0;
int DW;

//INTERNAL PARAMETERS
int X_OFFSET = 20;
int Y_OFFSET = 30;

//ultrasnoic oject creation
NewPing sonar_X(X_TRIGGER_PIN, X_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_Y(Y_TRIGGER_PIN, Y_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_XD(XD_TRIGGER_PIN, XD_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_YD(YD_TRIGGER_PIN, YD_ECHO_PIN, MAX_DISTANCE);


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

  //MOTOR DRIVER INITIAL CONDITION
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);

}

void loop() {

  //step_1_calulate_all_distance
  delay(50);
  X_PING_DISTACE = sonar_X.ping_cm();
  delay(50);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(50);
  XD_PING_DISTACE = sonar_XD.ping_cm();
  delay(50);
  YD_PING_DISTACE = sonar_YD.ping_cm();

    //MOTOR DRIVER INITIAL CONDITION
  digitalWrite(M1_FORWARD,HIGH);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,HIGH);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);
  
}
