/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BMI 160 Gyro
#include <BMI160Gen.h>
const int bmi160_addr = 0x69;
int gyro_X, gyro_Y, gyro_Z;
bool gyro_print = true;
*/

void initBmi160Gyro(){
  uint8_t aux = 0;
  uint8_t tries = 5;
  Serial.println("Initializing bmi160 Gyro ...");
  while(!BMI160.begin(BMI160GenClass::I2C_MODE, bmi160_addr) && aux < tries){
    Serial.print("Didn't find Gyro try number: ");Serial.println(aux);
    aux++;
    delay(1000);
  }
  if (tries == aux) {
    Serial.println(F("Unable to begin Gyro"));
  }else{
    Serial.println(F("Gyro online."));
  }
}

int* get_bmi160gyro(){
  int gyro[3];

  BMI160.readGyro(gyro[0], gyro[1], gyro[2]);

  if(gyro_print){
    // display tab-separated gyro x/y/z values
    Serial.print("g:\t");
    Serial.print(gyro[0]);
    Serial.print("\t");
    Serial.print(gyro[1]);
    Serial.print("\t");
    Serial.print(gyro[2]);
    Serial.println();  
  } 
  return gyro;
}
