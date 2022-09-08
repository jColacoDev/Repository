/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RTC ds3231
RTC_DS3231 rtc;
char rtc_daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool rtc_print = true;
float rtc_temperature;
*/

void initRTC(){
  uint8_t aux = 0;
  uint8_t tries = 5;
  
  Serial.println("Initializing RTC ...");
  while(!rtc.begin() && aux < tries){
    Serial.print("Didn't find RTC try number: ");Serial.println(aux);
    aux++;
    delay(1000);
  }
  if (tries == aux) {
    Serial.println(F("Unable to begin RTC"));
  }else{
    Serial.println(F("RTC online."));
    if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
  }
}

float get_rtc_temperature(){
  return rtc.getTemperature();
}

String get_rtc_fullDateStamp(){
  return String(get_rtc_dateStamp() + " " + get_rtc_timeStamp());
}

String get_rtc_dateStamp(){   
  DateTime now = rtc.now(); 
  String date = "";
  String aux = String(now.day());
  if(aux.length() < 2)date.concat("0"); 
  date.concat(aux);
  date.concat("/");
  aux = String(now.month());
  if(aux.length() < 2)date.concat("0"); 
  date.concat(aux);
  date.concat("/");
  date.concat(String(now.year()));
  return date; 
}

String get_rtc_timeHours(){
  DateTime now = rtc.now();   
  String hours = "";
  String aux = String(now.hour());
  if(aux.length() < 2)hours.concat("0"); 
  hours.concat(aux);
  hours.concat(":");
  aux = String(now.minute());
  if(aux.length() < 2)hours.concat("0");
  hours.concat(aux);
    
  return hours;
}

String get_rtc_timeStamp(){
  DateTime now = rtc.now(); 
  String timeStamp = get_rtc_timeHours();
  String aux = String(now.second());
  timeStamp.concat(":");   
  if(aux.length() < 2)timeStamp.concat("0"); 
  timeStamp.concat(String(now.second()));
  
  return timeStamp;
}
/*
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
*/
