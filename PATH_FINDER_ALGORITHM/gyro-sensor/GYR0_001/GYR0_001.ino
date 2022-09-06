
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"
HMC5883L mag;

int16_t mx, my, mz;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    Wire.begin();
    Serial.begin(38400);
    mag.initialize();
}

void loop() {
    // read raw heading measurements from device
    mag.getHeading(&mx, &my, &mz);
// To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    Serial.print("heading:\t");
    Serial.println(heading * 180/M_PI);

}
