/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gas Sensor detect gases in the concentration of range 200 to 10000ppm
#define mq2_anal 1
*/

int get_mq2_gasSensor(){
  int mq2_value = analogRead(mq2_pin);
  if(mq2_print){    
    Serial.print("MQ2 gas Sensor: ");
    Serial.println(mq2_value);
  }
  return mq2_value;
}
