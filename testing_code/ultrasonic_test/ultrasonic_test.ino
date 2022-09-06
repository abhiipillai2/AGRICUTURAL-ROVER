#include <NewPing.h>

//PIN CONFIGURATION FOR ULTRASONIC SENSOR
#define X_TRIGGER_PIN  2  
#define X_ECHO_PIN     4  

#define Y_TRIGGER_PIN  7  
#define Y_ECHO_PIN     8 

#define XD_TRIGGER_PIN  13 
#define XD_ECHO_PIN     9  

#define YD_TRIGGER_PIN  5
#define YD_ECHO_PIN     6 

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
int X_OFFSET = 12;
int Y_OFFSET = 20;

//ultrasnoic oject creation
NewPing sonar_X(X_TRIGGER_PIN, X_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_Y(Y_TRIGGER_PIN, Y_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_XD(XD_TRIGGER_PIN, XD_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_YD(YD_TRIGGER_PIN, YD_ECHO_PIN, MAX_DISTANCE);


void setup() {
  Serial.begin(115200);
  

}

void loop() {

  //step_1_calulate_all_distance
  delay(1000);
  X_PING_DISTACE = sonar_X.ping_cm();
  delay(1000);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(1000);
  XD_PING_DISTACE = sonar_XD.ping_cm();
  delay(1000);
  YD_PING_DISTACE = sonar_YD.ping_cm();
  delay(1000);
  float total = 0;
  total = Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET ;
  float total_x = 0;
  total_x = X_PING_DISTACE + XD_PING_DISTACE + X_OFFSET;
//  Serial.prtotal_xintln("X_PING_DISTANCE");
//  Serial.println(X_PING_DISTACE);

Serial.println("X_PING_DISTACE");
Serial.println(X_PING_DISTACE);
Serial.println("Y_PING_DISTACE");
Serial.println(Y_PING_DISTACE);
Serial.println("XD_PING_DISTACE");
Serial.println(XD_PING_DISTACE);
Serial.println("YD_PING_DISTACE");
Serial.println(YD_PING_DISTACE);
Serial.println("----------------------");
Serial.println("----------------------");
Serial.println("total_x");
Serial.println(total_x);
Serial.println("total_y");
Serial.println(total);
Serial.println("----------------------");
Serial.println("----------------------");
delay(3000);
}
