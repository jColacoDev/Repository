/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compass
#include <QMC5883LCompass.h>

QMC5883LCompass compass;
char compass_direction[3];
bool magneto_print = true;;
*/

void initMagneto(){
  Serial.println("Initializing Magneto...");
  compass.init();
  Serial.println("Magneto Initialized");
  Serial.println("-------------- --------------");
}
void get_magneto_direction(){
  compass.read();
  byte a = compass.getAzimuth();
  compass.getDirection(compass_direction, a);

  if(magneto_print){
    Serial.print(compass_direction[0]);
    Serial.print(compass_direction[1]);
    Serial.print(compass_direction[2]);
    Serial.println();
  }
}
