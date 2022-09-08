/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BMI 160 Gyro
#include <BMI160Gen.h>
const int bmi160_addr = 0x69;
*/

void InitBmi160(){  
  Serial.println("Initializing BMI160 gyro...");
  if(!BMI160.begin(BMI160GenClass::I2C_MODE, bmi160_addr)){
    Serial.println("Not ");
  }else{
    bmi160_on = true;
  }
  Serial.println("Initialized ");
  Serial.println("");
}

void CheckBmi160Gyro(){
  BMI160.readGyro(bmi_value[0], bmi_value[1], bmi_value[2]);
  
  if(bmi160_print){
    Serial.println("-----------");
    Serial.print("g:\t");
    Serial.print(bmi_value[0]);
    Serial.print("\t");
    Serial.print(bmi_value[1]);
    Serial.print("\t");
    Serial.print(bmi_value[2]);
    Serial.println();     
  }
}
