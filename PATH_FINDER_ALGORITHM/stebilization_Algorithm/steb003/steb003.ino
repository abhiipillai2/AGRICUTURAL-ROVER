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
int fixTemp_w01 =0;
int fixTemp_w02 =0;
int fixTemp_w1 = 0;
int fixTemp_w2 = 0;

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
  ENGINE_STOP();
}

void loop() {

  //call caliberation unction inside the fixing function
  fixing(CALIBERATION(Y_DISTANCE()));

}


//**********************************************************
//**********************************************************
///////engine_functions

//ENGINE STOP
void ENGINE_STOP (){

  //ENGINE STOP 
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);
  
}

//COUNTER CLOCK FUNCTION
void COUNTER_CLOCK (int DELAY){
  
  //counter clock 
  digitalWrite(M1_FORWARD,HIGH);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,LOW);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,HIGH);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,LOW);
  digitalWrite(M4_BACKWARD,LOW);
  
  delay(DELAY);
}

// CLOCK FUNCTION
void CLOCK (int DELAY){
  
  // clock 
  digitalWrite(M1_FORWARD,LOW);
  digitalWrite(M1_BACKWARD,LOW);

  digitalWrite(M2_FORWARD,HIGH);
  digitalWrite(M2_BACKWARD,LOW);

  digitalWrite(M3_FORWARD,LOW);
  digitalWrite(M3_BACKWARD,LOW);

  digitalWrite(M4_FORWARD,HIGH);
  digitalWrite(M4_BACKWARD,LOW);
  
  delay(DELAY);
}


//params functions
//y distance
int Y_DISTANCE (){
  
  delay(200);
  float distance = sonar_Y.ping_cm();

  return distance;

}

//yd distance
int YD_DISTANCE (){
  
  delay(200);
  float distance = sonar_YD.ping_cm();

  return distance;

}

//dealy weigth calculation function
int DELAY_WEIGHT (int w1,int w2){

        Temp_w = (w1 - w2);
        W = abs(Temp_w);
        DW = (W0 * W );

        return DW;
}

//choice
bool choice (int x0){

    //stop engin
    ENGINE_STOP();

    //(couter_clock)
    COUNTER_CLOCK(3000);

    //stop engin
    ENGINE_STOP();

    float x2 = Y_DISTANCE();
    delay(50);

    if (x2 < x0){

      //counte clock
      bool flag = true ;
      return flag;
    }else{

      //clock
      bool flag = false ;
      return flag;
    }
    
}

//CALIBERATION FUNCTION
int CALIBERATION (int w0){

  if (choice(Y_DISTANCE())){
    //for avg
    int caliber_w1_sum = 0;
    caliber_w1 = Y_DISTANCE;
    while(caliber_w1 > w0){
      
      //stop engin
      ENGINE_STOP();

      //(couter_clock)
      COUNTER_CLOCK(3000);

      //stop engin
      ENGINE_STOP();
      
      //temp store
      caliber_w1 = Y_DISTANCE();
      caliber_w1_sum = caliber_w1_sum + caliber_w1;
      delay(50);
      count = count + 1;
      delay(50);
    }
    //stop engin
    ENGINE_STOP();

    //calculating fixing coordinates
    fixing_w01 = (caliber_w1_sum / count );

    return fixing_w01;
  }else{
    //for avg
    int caliber_w1_sum = 0;
    caliber_w1 = Y_DISTANCE;
    while(caliber_w1 > w0){
      
      //stop engin
      ENGINE_STOP();

      //(_clock)
      CLOCK(3000);

      //stop engin
      ENGINE_STOP();
      
      //temp store
      caliber_w1 = Y_DISTANCE();
      caliber_w1_sum = caliber_w1_sum + caliber_w1;
      delay(50);
      count = count + 1;
      delay(50);
    }
    //stop engin
    ENGINE_STOP();

    //calculating fixing coordinates
    fixing_w01 = (caliber_w1_sum / count );

    return fixing_w01;
  }
    
  }
 
//fixing
int fixing (int x0){

if (choice(Y_DISTANCE())){
  //calculation of distance
        Y_PING_DISTACE = Y_DISTANCE();
        delay(200);

        while(Y_PING_DISTACE >= x0){
        //stop
        ENGINE_STOP ();
        
        //delay weigth
        
        //(couter_clock)
        COUNTER_CLOCK(DELAY_WEIGHT(Y_PING_DISTACE,x0));

        //stop
        ENGINE_STOP ();
        delay(200);
        Y_PING_DISTACE = Y_DISTANCE();
        }
}else{
  //calculation of distance
        Y_PING_DISTACE = Y_DISTANCE();
        delay(200);

        while(Y_PING_DISTACE >= x0){
        //stop
        ENGINE_STOP ();
        
        //delay weigth
        
        //(_clock)
        CLOCK(DELAY_WEIGHT(Y_PING_DISTACE,x0));

        //stop
        ENGINE_STOP ();
        delay(200);
        Y_PING_DISTACE = Y_DISTANCE();
}

}
}
