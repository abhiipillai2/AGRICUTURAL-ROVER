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

#define M3_FORWARD  A1
#define M3_BACKWARD A2 

#define M4_FORWARD A3
#define M4_BACKWARD A4 

#define M1_ENB 3
#define M2_ENA 5

#define M3_ENB 6
#define M4_ENA 9


//MAXIMUM DISTANCE FOR ULTARSONIC SENSOR
#define MAX_DISTANCE 4000

//PARAMETERS
float X_PING_DISTACE;
float Y_PING_DISTACE;
float XD_PING_DISTACE;
float YD_PING_DISTACE;

int W0 = 2000;
int W = 0;
int DW;
int Temp_w;
int caliber_w01 =0;
int caliber_w02 = 0;
int caliber_w1 = 0;
int caliber_w2 = 0;
int count = 0;
int fixing_w01 = 0;
int fixing_w02 = 0;

//INTERNAL PARAMETERS
int X_OFFSET = 25;
int Y_OFFSET = 40;

//ultrasnoic oject creation
NewPing sonar_X(X_TRIGGER_PIN, X_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_Y(Y_TRIGGER_PIN, Y_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_XD(XD_TRIGGER_PIN, XD_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_YD(YD_TRIGGER_PIN, YD_ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  //MOTOR DRIVER PIN CONFIGURATION
  pinMode(M1_FORWARD,OUTPUT);
  pinMode(M1_BACKWARD,OUTPUT);

  pinMode(M2_FORWARD,OUTPUT);
  pinMode(M2_BACKWARD,OUTPUT);

  pinMode(M3_FORWARD,OUTPUT);
  pinMode(M3_BACKWARD,OUTPUT);

  pinMode(M4_FORWARD,OUTPUT);
  pinMode(M4_BACKWARD,OUTPUT);

  pinMode(M1_ENB, OUTPUT);
  pinMode(M2_ENA, OUTPUT);

  pinMode(M3_ENB, OUTPUT);
  pinMode(M4_ENA, OUTPUT);

  //SPEED CONTROL
  analogWrite(M1_ENB,200);
  analogWrite(M2_ENA,200);
  analogWrite(M3_ENB,200);
  analogWrite(M4_ENA,200);

  //MOTOR DRIVER INITIAL CONDITION
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);

 delay(5000);
}

void loop() {

//step_1_calulate_y_and_yd_distance
  delay(200);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(200);
  YD_PING_DISTACE = sonar_YD.ping_cm();
  delay(200);

//store values
caliber_w01 = Y_PING_DISTACE;
caliber_w02 = YD_PING_DISTACE;

//step_1(choice)
  delay(2000);

  //engine stop
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);

  //step_2(couter_clock)
  digitalWrite(M1_FORWARD,HIGH);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,HIGH);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);
  delay(3000);

  //stop engin
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);

  //step_3(check_y_yd)
  delay(200);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(200);
  YD_PING_DISTACE = sonar_YD.ping_cm();
  delay(200);

  //temp store
  caliber_w1 = Y_PING_DISTACE;
  caliber_w2 = YD_PING_DISTACE;

  //step 4
  if(caliber_w1 < caliber_w01){

    //for avg
    int caliber_w1_sum = caliber_w1;
    int caliber_w2_sum = caliber_w2;
    
    while(caliber_w1 > caliber_w01 ){
      //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

      //(couter_clock)
      digitalWrite(M1_FORWARD,HIGH);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,HIGH);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);
      delay(3000);

      delay(200);
      Y_PING_DISTACE = sonar_Y.ping_cm();
      delay(200);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(200);

      //temp store
      caliber_w1 = Y_PING_DISTACE;
      caliber_w1_sum = caliber_w1_new + caliber_w1;
      delay(50);
      caliber_w2 = YD_PING_DISTACE;
      caliber_w2_sum = caliber_w2_new + caliber_w2;
      delay(50);
      count = count + 1;
      delay(50);
    }
    //stop
    digitalWrite(M1_FORWARD,LOW);
    digitalWrite(M1_BACKWARD,LOW);

    digitalWrite(M2_FORWARD,LOW);
    digitalWrite(M2_BACKWARD,LOW);

    digitalWrite(M3_FORWARD,LOW);
    digitalWrite(M3_BACKWARD,LOW);

    digitalWrite(M4_FORWARD,LOW);
    digitalWrite(M4_BACKWARD,LOW);
    
    //calculating fixing coordinates
    fixing_w01 = (caliber_w1_sum / count );
    fixing_w02 = (caliber_w2_sum / count );
    delay(50);

    //fixing
    delay(200);
    Y_PING_DISTACE = sonar_Y.ping_cm();
    delay(200);
    YD_PING_DISTACE = sonar_YD.ping_cm();
    delay(200);
    
    while(Y_PING_DISTACE == fixing_w01 && YD_PING_DISTACE == fixing_w02){
      //stop
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

      //delay weigth
      Temp_w = (Y_PING_DISTACE - YD_PING_DISTACE);
      int fix_offset = 0;
      fix_offset = abs(Temp_w);
      W = fix_offset + 1;
      DW = (W0 * W );

      //(couter_clock)
      digitalWrite(M1_FORWARD,HIGH);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,HIGH);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);
      delay(DW);

      delay(200);
      Y_PING_DISTACE = sonar_Y.ping_cm();
      delay(200);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(200);
    }
    
      //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);
  }else{

    //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

      //(clock)
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,HIGH);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,HIGH);
      digitalWrite(M4_BACKWARD,LOW);
      delay(3000);

      //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

    
    //for avg
    int caliber_w1_sum = caliber_w1;
    int caliber_w2_sum = caliber_w2;
    
    while(caliber_w1 > caliber_w01 ){
      //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

      //(clock)
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,HIGH);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,HIGH);
      digitalWrite(M4_BACKWARD,LOW);
      delay(3000);

      delay(200);
      Y_PING_DISTACE = sonar_Y.ping_cm();
      delay(200);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(200);

      //temp store
      caliber_w1 = Y_PING_DISTACE;
      caliber_w1_sum = caliber_w1_new + caliber_w1;
      delay(50);
      caliber_w2 = YD_PING_DISTACE;
      caliber_w2_sum = caliber_w2_new + caliber_w2;
      delay(50);
      count = count + 1;
      delay(50);
    }
    //stop
    digitalWrite(M1_FORWARD,LOW);
    digitalWrite(M1_BACKWARD,LOW);

    digitalWrite(M2_FORWARD,LOW);
    digitalWrite(M2_BACKWARD,LOW);

    digitalWrite(M3_FORWARD,LOW);
    digitalWrite(M3_BACKWARD,LOW);

    digitalWrite(M4_FORWARD,LOW);
    digitalWrite(M4_BACKWARD,LOW);
    
    //calculating fixing coordinates
    fixing_w01 = (caliber_w1_sum / count );
    fixing_w02 = (caliber_w2_sum / count );
    delay(50);

    //fixing
    delay(200);
    Y_PING_DISTACE = sonar_Y.ping_cm();
    delay(200);
    YD_PING_DISTACE = sonar_YD.ping_cm();
    delay(200);
    
    while(Y_PING_DISTACE == fixing_w01 && YD_PING_DISTACE == fixing_w02){
      //stop
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);

      //delay weigth
      Temp_w = (Y_PING_DISTACE - YD_PING_DISTACE);
      int fix_offset = 0;
      fix_offset = abs(Temp_w);
      W = fix_offset + 1;
      DW = (W0 * W );

      //(_clock)
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,HIGH);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,HIGH);
      digitalWrite(M4_BACKWARD,LOW);
      delay(DW);

      delay(200);
      Y_PING_DISTACE = sonar_Y.ping_cm();
      delay(200);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(200);
    }
    
      //stop engin
      digitalWrite(M1_FORWARD,LOW);
      digitalWrite(M1_BACKWARD,LOW);

      digitalWrite(M2_FORWARD,LOW);
      digitalWrite(M2_BACKWARD,LOW);

      digitalWrite(M3_FORWARD,LOW);
      digitalWrite(M3_BACKWARD,LOW);

      digitalWrite(M4_FORWARD,LOW);
      digitalWrite(M4_BACKWARD,LOW);
  }
  
  
}
