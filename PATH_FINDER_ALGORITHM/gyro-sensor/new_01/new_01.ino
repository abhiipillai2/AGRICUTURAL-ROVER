/*
For HMC5883L_Header_Arduino_Auto_calibration library
ref: http://hobbylogs.me.pn/?p=17
*/

#include "U8glib.h"
#include <Wire.h>
#include "compass.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define Task_t 10          // Task Time in milli seconds

int dt=0;
unsigned long t;
// Main code -----------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  // Serial.print("Setting up I2C ........\n");
  Wire.begin();
  compass_x_offset = -48.23;  //122.17;
  compass_y_offset = 284.69;  //230.08;
  compass_z_offset = 59.87;  //389.85;
  compass_x_gainError = 1.07;  //1.12;
  compass_y_gainError = 1.09;  //1.13;
  compass_z_gainError = 1.01;  //1.03;
  
  compass_init(2);
  //compass_debug = 1;
  //compass_offset_calibration(3);

}

// Main loop 
// Main loop -----------------------------------------------------------------
void loop(){
  
  t = millis();
 
  float load;
 
  compass_scalled_reading();
  
  Serial.print("x = ");
  Serial.println(compass_x_scalled);
  Serial.print("y = ");
  Serial.println(compass_y_scalled);
  Serial.print("z = ");
  Serial.println(compass_z_scalled);
  
  compass_heading();
  Serial.print ("Heading angle = ");
  Serial.print (bearing);
  Serial.println(" Degree");
  
  dt = millis()-t;
  load = (float)dt/(Task_t/100);
  Serial.print ("Load on processor = ");
  Serial.print(load);
  Serial.println("%");
  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  
  delay(100);
}

void draw(void) {
  u8g.setFont(u8g_font_unifont);

  u8g.setPrintPos(0, 15);
  u8g.print("x: ");
  u8g.setPrintPos(70, 15);
  u8g.print(compass_x_scalled);
  
  u8g.setPrintPos(0, 30);
  u8g.print("y: ");
  u8g.setPrintPos(70, 30);
  u8g.print(compass_y_scalled);
  
  u8g.setPrintPos(0, 45);
  u8g.print("z: ");
  u8g.setPrintPos(70, 45);
  u8g.print(compass_z_scalled);
  
  u8g.setPrintPos(0, 60);
  u8g.print("bearing: ");
  u8g.setPrintPos(70, 60);
  u8g.print(bearing);

}
