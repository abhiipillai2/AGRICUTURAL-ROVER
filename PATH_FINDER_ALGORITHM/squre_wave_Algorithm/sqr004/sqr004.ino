#include <NewPing.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"
HMC5883L mag;

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
//ultrasnoic oject creation
NewPing sonar_X(X_TRIGGER_PIN, X_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_Y(Y_TRIGGER_PIN, Y_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_XD(XD_TRIGGER_PIN, XD_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_YD(YD_TRIGGER_PIN, YD_ECHO_PIN, MAX_DISTANCE);


void setup() {
    Wire.begin();
    Serial.begin(38400);
    mag.initialize();
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

  //for delay weigth calculation
  int W0 = 100;
  int W = 0;
  int DW = 0;
  int Temp_w = 0;
  
    //calulate_all_distance
  delay(1000);
  Y_PING_DISTACE = sonar_Y.ping_cm();
  delay(1000);
  XD_PING_DISTACE = sonar_XD.ping_cm();
  delay(1000);

  if(XD_PING_DISTACE >= total_margin){
    
    while(!(Y_PING_DISTACE <= total_margin)){

        //stop
        bot_engine_stop();
        
        //delay weigth calculation
        Temp_w = (Y_PING_DISTACE - total_margin);
        int fix_offset = 0;
        fix_offset = abs(Temp_w);
        W = (fix_offset * 50);
        DW = (W0 + W );
        //forward
        bot_forward(DW);
        //stop
        bot_engine_stop();
        //check y distance
        delay(1000);
        Y_PING_DISTACE = sonar_Y.ping_cm();
        delay(1000);
    }

    //stopengin
    bot_engine_stop();
    //rotate_90_right
    right_rotator();
    //stop
    bot_engine_stop();
    delay(1500);
    //forward
    bot_forward(600);
    //stopengin
    bot_engine_stop();
    delay(1500);
    //rotate_90_right
    right_rotator();
    //stop
    bot_engine_stop();
    //check y distance
    delay(1000);
    Y_PING_DISTACE = sonar_Y.ping_cm();
    delay(1000);

    //second_loop
    while(!(Y_PING_DISTACE <= total_margin)){

        //stop
        bot_engine_stop();
        
        //delay weigth calculation
        Temp_w = (Y_PING_DISTACE - total_margin);
        int fix_offset = 0;
        fix_offset = abs(Temp_w);
        W = (fix_offset * 50);
        DW = (W0 + W );
        //forward
        bot_forward(DW);
        //stop
        bot_engine_stop();
        //check y distance
        delay(1000);
        Y_PING_DISTACE = sonar_Y.ping_cm();
        delay(1000);
    }

    //stopengin
    bot_engine_stop();
    //rotate_90_right
    left_rotaor();
    //stop
    bot_engine_stop();
    delay(1500);
    //forward
    bot_forward(500);
    //stopengin
    bot_engine_stop();
    delay(1500);
    //rotate_90_right
    left_rotaor();
    //stop
    bot_engine_stop();
  }
}

//suporting functions

//bot rigt rotator
void right_rotator (){

 
  float ref_coordinate = 0;
  float end_coordinate = 0;
  bool case_flag = false;
  delay(1000);
  
  if(ref_coordinate > 50 && ref_coordinate < 120){
    
    end_coordinate = 198;
    
  }else if(ref_coordinate > 150 && ref_coordinate < 210){
    
    end_coordinate = 250;
    
  }else if(ref_coordinate > 240 && ref_coordinate < 360){
    
    case_flag = true;
    
  }else{
    
    end_coordinate = 94;
    
  }
  
  bool loop_flag = true;
  while(loop_flag){
    float coordinate = 0;
    coordinate = bot_compass();
    delay(1000); 
    if(case_flag){

        if(coordinate >= 20 && coordinate <= 50){
          
        break;
        case_flag = false;
        
      }
         
    }else{
      
        if(coordinate >= end_coordinate){
        
        break;
      }
    }
    //rotator
    bot_clock(400);
    bot_engine_stop();
    delay(2000);
  }
}


void left_rotaor (){

 
  float ref_coordinate = 0;
  float end_coordinate = 0;
  bool case_flag = false;
  ref_coordinate = bot_compass();
  delay(1000);
  
  if(ref_coordinate > 50 && ref_coordinate < 120){
    
    end_coordinate = 22;
    
  }else if(ref_coordinate > 150 && ref_coordinate < 210){
    
    end_coordinate =94;
    
  }else if(ref_coordinate < 50){
    
    case_flag = true;
    
    
  }else{
    
    end_coordinate =199;
    
  }
  
  bool loop_flag = true;
  while(loop_flag){
    float coordinate = 0;
    coordinate = bot_compass();
    delay(1000); 
    if(case_flag){

        if(coordinate <= 250 && coordinate >= 200){
          
        break;
        case_flag = false;
        
      }
         
    }else{
      
        if(coordinate <= end_coordinate){
        
        break;
      }
    }
    //rotator
    bot_anti_clock(400);
    bot_engine_stop();
    delay(2000);
  }
}
//gyrosciop
float bot_compass (void){
    mag.getHeading(&mx, &my, &mz);
    float heading = atan2(my, mx);
    float heading_degree = 0;
    if(heading < 0)
      heading += 2 * M_PI;
      heading_degree = (heading * 180/M_PI);

      return heading_degree;
}
//clock
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
