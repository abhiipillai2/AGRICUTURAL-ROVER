#include <NewPing.h>

//PIN CONFIGURATION FOR ULTRASONIC SENSOR
#define X_TRIGGER_PIN  2  
#define X_ECHO_PIN     4  

#define Y_TRIGGER_PIN  7  
#define Y_ECHO_PIN     8  

#define XD_TRIGGER_PIN  13  
#define XD_ECHO_PIN     0  

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
int X_PING_DISTACE;
int Y_PING_DISTACE;
int XD_PING_DISTACE;
int YD_PING_DISTACE;
int *DISTANCE;

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
  
  if(flag){
    
  }else{
   bot_stebilizer(GLOBEL_X,GLOBEL_Y,ORNT_1);
    flag = true;
  }

}


//bot stebilizer function
void bot_stebilizer (int X , int Y, int ornt){

  //internal parameters
  int ref_x = 0;
  int ref_y = 0;
  int internal_x = 0;
  int internal_y = 0;

  bool rot_flag = false;
  bool counter_flag = false;

  //for delay weigth calculation
  int W0 = 100;
  int W = 0;
  int DW = 0;
  int Temp_w = 0;

  //body of the function
  //engine stop
  bot_engine_stop();
  delay(500);

  //calulate_all_distance
  DISTANCE = distance_calculator(ORNT_1);
  
  X_PING_DISTACE = *DISTANCE;
  
  Y_PING_DISTACE = *DISTANCE + 1;
 
  XD_PING_DISTACE = *DISTANCE + 2;
  
  YD_PING_DISTACE = *DISTANCE + 3;
  

  //calculation of internal parameters
  internal_y = (Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET);
  internal_x =(X_PING_DISTACE + XD_PING_DISTACE + X_OFFSET);
  
  ref_y = internal_y;

  delay(1000);

      //stebilizer loop
      while(!(internal_y <= GLOBEL_Y && internal_x <= GLOBEL_X)){
        
        //stop
        bot_engine_stop();

        //delay weigth calculation
        Temp_w = (internal_y - 70);
        int fix_offset = 0;
        fix_offset = abs(Temp_w);
        W = (fix_offset * 50);
        DW = (W0 + W );

        //check LSH or RSH
        if(counter_flag){
        
          if(internal_y > ref_y || internal_y > ref_y + 5 || internal_y > ref_y + 10 || internal_y > ref_y + 15 || internal_y > ref_y + 20 ) {
              rot_flag = false;
              counter_flag = false; 
          } 
        }else{
          
            if(internal_y > ref_y || internal_y > ref_y + 5 || internal_y > ref_y + 10 || internal_y > ref_y + 15 || internal_y > ref_y + 20 ){
              rot_flag = true;
              counter_flag = true;
          }
        }

        //rotae bot based on the Flags
        if(rot_flag){
          //(counter_clock)
        bot_anti_clock(DW);
          
        }else{
          //(clock)
        bot_clock(DW);
          }
        //stop
        bot_engine_stop();

        //calulate_all_internal_distance
        //calulate_all_distance
        DISTANCE = distance_calculator(ORNT_1);
        
        X_PING_DISTACE = *DISTANCE;
        
        Y_PING_DISTACE = *DISTANCE + 1;
       
        XD_PING_DISTACE = *DISTANCE + 2;
        
        YD_PING_DISTACE = *DISTANCE + 3;
        
        internal_y = (Y_PING_DISTACE + YD_PING_DISTACE + Y_OFFSET);
        delay(1000);
        internal_x =(X_PING_DISTACE + XD_PING_DISTACE + X_OFFSET);
        
        //check brek conditions
        if(internal_y == GLOBEL_X && internal_x == GLOBEL_Y){
          
          break;
          
        }
      }
}

//bot distance calculator
int * distance_calculator (int ornt){

  //internal parameters
  int x = 0;
  int y = 0;
  int xd = 0;
  int yd = 0 ;
  static int distance[4] = {0,0,0,0};

if(ornt == 1){

  //calulate_all_internal_distance
        delay(1000);
        x = sonar_X.ping_cm();
        delay(1000);
        y = sonar_Y.ping_cm();
        delay(1000);
        xd = sonar_XD.ping_cm();
        delay(1000);
        yd = sonar_YD.ping_cm();
        delay(1000);

        distance[0] = x;
        distance[1] = y;
        distance[2] = xd;
        distance[3] = yd;

        return distance;
}else if(ornt == 2){

  //calulate_all_internal_distance_for_ornt_2
        delay(1000);
        x = sonar_YD.ping_cm();
        delay(1000);
        y = sonar_X.ping_cm();
        delay(1000);
        xd = sonar_Y.ping_cm();
        delay(1000);
        yd = sonar_XD.ping_cm();
        delay(1000);

        distance[0] = x;
        distance[1] = y;
        distance[2] = xd;
        distance[3] = yd;

        return distance;
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
