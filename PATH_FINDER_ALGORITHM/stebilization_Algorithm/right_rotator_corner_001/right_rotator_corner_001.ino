#include <NewPing.h>

//PIN CONFIGURATION FOR ULTRASONIC SENSOR
#define X_TRIGGER_PIN  2  
#define X_ECHO_PIN     4  

#define Y_TRIGGER_PIN  7  
#define Y_ECHO_PIN     8  

#define XD_TRIGGER_PIN  13  
#define XD_ECHO_PIN     9  

#define YD_TRIGGER_PIN  5 //  
#define YD_ECHO_PIN     6 //

//MOTOR DRIVER PIN CONFIGURATION
#define M1_FORWARD 10  
#define M1_BACKWARD 11 

#define M2_FORWARD 12  
#define M2_BACKWARD A0 

#define M3_FORWARD  A1
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

//INTERNAL PARAMETERS
int X_OFFSET = 12;
int Y_OFFSET = 20;
int GLOBEL_X = 96;
int GLOBEL_Y = 70;
int ORNT_1 = 1;
int ORNT_2 = 2;
bool flag = false;

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

  //MOTOR DRIVER INITIAL CONDITION
  bot_engine_stop();}

void loop() {
 //for delay weigth calculation
  int W0 = 100;
  int W = 0;
  int DW = 0;
  int Temp_w = 0;
  int x_distance = 0;
  int index = 1;
  bool loop_flag = false;
  if(flag){
    
  }else{
//calulate_all_distance
  delay(1000);
  X_PING_DISTACE = sonar_X.ping_cm();
  delay(1000);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(1000);
  XD_PING_DISTACE = sonar_XD.ping_cm();
  delay(1000);
  YD_PING_DISTACE = sonar_YD.ping_cm();
  delay(1000);
  int ref_distance = 0;
  int calculator_distance = 0;
  ref_distance = (X_PING_DISTACE + XD_PING_DISTACE + X_OFFSET);
  calculator_distance = (Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET);
  //loop -1
  while(!(calculator_distance >= ref_distance)){
 
    //stop
    bot_engine_stop();
     //bot_anti_clock
     bot_clock(300);
     //stop
    bot_engine_stop();
    delay(1000);
    Y_PING_DISTACE = sonar_Y.ping_cm();
    delay(1000);
    YD_PING_DISTACE = sonar_YD.ping_cm();
    delay(1000);
     calculator_distance = (Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET);
     loop_flag = true;
    
  }
  //oposit loop
  //loop -2
  while(loop_flag){
      int count = 0;
    //stop
    bot_engine_stop();
    //delay weigth calculation
        if(count > 4){
          DW = 130;
        }else{
          DW = 200;
        }

      //bot_anti_clock
      bot_clock(DW);
      //stop
      bot_engine_stop();
      delay(1000);
      X_PING_DISTACE = sonar_X.ping_cm();
      delay(1000);
      Y_PING_DISTACE = sonar_Y.ping_cm();
      delay(1000);
      XD_PING_DISTACE = sonar_XD.ping_cm();
      delay(1000);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(1000);
      
      calculator_distance = (Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET);
      x_distance = (X_PING_DISTACE + XD_PING_DISTACE + X_OFFSET);

      count = count + 1;
      if(calculator_distance <= ref_distance){
        index = 0;
      }
      if(index == 0)
      {
        break;
      }
  }
    flag = true;
  }
}

//suporting functions
void bot_clock (int w){
  
  //(clock)
        digitalWrite(M1_FORWARD,LOW);
        digitalWrite(M1_BACKWARD,HIGH);

        digitalWrite(M2_FORWARD,HIGH);
        digitalWrite(M2_BACKWARD,LOW);

        digitalWrite(M3_FORWARD,LOW);
        digitalWrite(M3_BACKWARD,HIGH);

        digitalWrite(M4_FORWARD,HIGH);
        digitalWrite(M4_BACKWARD,LOW);
        delay(w);
  
}

void bot_anti_clock (int w){
  
  //(counter_clock)
        digitalWrite(M1_FORWARD,HIGH);
        digitalWrite(M1_BACKWARD,LOW);

        digitalWrite(M2_FORWARD,LOW);
        digitalWrite(M2_BACKWARD,HIGH);

        digitalWrite(M3_FORWARD,HIGH);
        digitalWrite(M3_BACKWARD,LOW);

        digitalWrite(M4_FORWARD,LOW);
        digitalWrite(M4_BACKWARD,HIGH);
        delay(w);
  
}

void bot_engine_stop (){

  //stop
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);
  
}

void bot_forward (int w){

  //forward
  digitalWrite(M1_FORWARD,HIGH);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,HIGH);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,HIGH);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,HIGH);
  digitalWrite(M4_BACKWARD,LOW);
  delay(w);
  
}

void bot_backward (int w){

  //backward
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,HIGH);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,HIGH);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,HIGH);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,HIGH);
  delay(w);
  
}
