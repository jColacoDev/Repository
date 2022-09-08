/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bmp280
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;
float bmp_temperature;
float bmp_pressure;
float bmp_altitude;
bool bmp_print = true;
*/

void initBmp280(){
  uint8_t aux = 0;
  uint8_t tries = 5;
  Serial.println("Initializing BMP280 ...");
  // bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)
  while(!bmp.begin(0x76) && aux < tries){
    Serial.print("Didn't find Magneto try number: ");Serial.println(aux);
    aux++;
    delay(1000);
  }
  if (tries == aux) {
    Serial.println(F("Unable to begin Magneto"));
  }else{
    Serial.println(F("Magneto online."));
            /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  }
}
void get_bmp280(){  
  if (bmp.takeForcedMeasurement()) {
    bmp_values[0] = bmp.readTemperature();
    bmp_values[1] = bmp.readPressure();
    bmp_values[2] = bmp.readAltitude(1013.25);

    if(bmp_print){
      Serial.print(F("Temperature = "));
      Serial.print(bmp_values[0]);
      Serial.println(" *C");
  
      Serial.print(F("Pressure = "));
      Serial.print(bmp_values[1]);
      Serial.println(" Pa");
  
      Serial.print(F("Approx altitude = "));
      Serial.print(bmp_values[2]); /* Adjusted to local forecast! */
      Serial.println(" m"); 
    }
  } else {
    Serial.println("BMP280 measurement failed!");
  }
}
