void Check_weather(){
  Check_air();
  Check_gas();
  Check_rain();
  Check_uv();  
}

void Check_air(){
  checkBme680();
}
void Check_gas(){
  get_mq2_gasSensor();
}
void Check_rain(){
  get_rainSensor();
}
void Check_uv(){
  Serial.println(String(uv.uva()) + ", " + String(uv.uvb()) + ", " + String(uv.index()));
}

void initUV(){
  if (uv.begin() == false)
  {
    Serial.println("Unable to communicate with VEML6075.");
    while (1)
      ;
  }
}

int get_rainSensor(){
  int rain_value = analogRead(rain_pin);
  if(rain_print){    
    Serial.print("Rain Sensor: ");
    Serial.println(rain_value);
  }
  return rain_value;
}
