
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"
HMC5883L mag;

int16_t mx, my, mz;
bool blinkState = false;

void setup() {
    Wire.begin();
    Serial.begin(38400);
    //Serial.begin(9600);
    mag.initialize();
}

void loop() {

Serial.println(bot_compass());
    
}

float bot_compass (void){
    mag.getHeading(&mx, &my, &mz);
    float heading = atan2(my, mx);
    float heading_degree = 0;
    if(heading < 0)
      heading += 2 * M_PI;
      heading_degree = (heading * 180/M_PI);

      return heading_degree;
}
