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

//for gyroscop
int16_t mx, my, mz;
bool blinkState = false;

//INTERNAL PARAMETERS
int X_OFFSET = 12;
int Y_OFFSET = 20;
int GLOBEL_X = 96;
int GLOBEL_Y = 70;
int ORNT_1 = 1;
int ORNT_2 = 2;
bool flag = false;

int total_margin = 15;
int common_delay = 1000;
//ultrasnoic oject creation
NewPing sonar_X(X_TRIGGER_PIN, X_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_Y(Y_TRIGGER_PIN, Y_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_XD(XD_TRIGGER_PIN, XD_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_YD(YD_TRIGGER_PIN, YD_ECHO_PIN, MAX_DISTANCE);


void setup() {
    Serial.begin(38400);
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
  bot_engine_stop();
}

void loop() {
  
  bot_margin_fixer();
  
}

void bot_margin_fixer (){

  //for delay weigth calculation
    int W0 = 100;
    int W = 0;
    int DW = 0;
    int Temp_w = 0;
    int D_FACTOR = 50;
  //find the YD distance
  
      delay(common_delay);
      YD_PING_DISTACE = sonar_YD.ping_cm();
      delay(common_delay);

      if(YD_PING_DISTACE > total_margin){

          while(!(YD_PING_DISTACE <= total_margin)){

              //stop
              bot_engine_stop();
              //delay weigth calculation
              Temp_w = (YD_PING_DISTACE - total_margin);
              int fix_offset = 0;
              fix_offset = abs(Temp_w);
              W = (fix_offset * D_FACTOR);
              DW = (W0 + W );
              //forward
              bot_backward(DW);
              //stop
              bot_engine_stop();
              //check y distance
              delay(common_delay);
              YD_PING_DISTACE = sonar_YD.ping_cm();
              delay(common_delay);
    }
      }
}

//suporting functions
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
