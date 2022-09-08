#include "data_structures.h"

#include "Arduino.h"
#include "Base64.h"
#include <HardwareSerial.h>
#include <SPI.h>

String gateway_coordinates;
String gateway_id = "001";
String gateway_password = "3333";
String gateway_birthDate;

String device_id[100] = {""};
String device_token[100] = {""};
int device_counter = 0;

//////////////////////////////////////////////////////////////////////
// LoRaWAN TTN
bool lorawan_print = true;
bool lorawan_on = false;

//////////////////////////////////////////////////////////////////////
// LoRa
#include <LoRa.h>
#define lora_ss 32
#define lora_rst 33
#define lora_dio0 25

bool lora_print = true;

//////////////////////////////////////////////////////////////////////
// RTC 3231
#include "RTClib.h"
RTC_DS3231 rtc;
char rtc_daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
float rtc_temperature;
bool rtc_print = true;
bool rtc_on = false;

//////////////////////////////////////////////////////////////////////
// BMI 160 Gyro
#include <BMI160Gen.h>
const int bmi160_addr = 0x69;
int bmi_value[3];
bool bmi160_print = true;
bool bmi160_on = false;

//////////////////////////////////////////////////////////////////////
// Air BME-680
#include "Zanshin_BME680.h"  // Include the BME680 Sensor library
BME680_Class BME680;  ///< Create an instance of the BME680 class
float altitude(const int32_t press, const float seaLevel = 1013.25);
float altitude(const int32_t press, const float seaLevel) {
  static float Altitude;
  Altitude =
      44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903));  // Convert into meters
  return (Altitude);
}
bool bme680_print = true;
bool bme680_on = false;

//////////////////////////////////////////////////////////////////////
// SDcard
#include "SD.h"
#define sd_csPin 27
uint8_t sd_cardType;
uint64_t sd_cardSize;
File sd_File;
bool sd_print = true;
bool sd_on = false;

//////////////////////////////////////////////////////////////////////
// Gas MQ2
#define mq2_pin 14
bool mq2_print = true;

//////////////////////////////////////////////////////////////////////
// Rain Sensor
#define rain_pin 4
bool rain_print = true;

//////////////////////////////////////////////////////////////////////
// UV sensor
#include <SparkFun_VEML6075_Arduino_Library.h>
VEML6075 uv; // Create a VEML6075 object
bool uv_print = true;
bool uv_on = false;

//////////////////////////////////////////////////////////////////////
// Timers
uint32_t checkTime1_start = 0;
int checkTime1_timer = 3000;

//////////////////////////////////////////////////////////////////////
// Variables


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  Serial.println("Serial OK");
  
  initLora();
  initRTC();
  //InitSDcard();
  //InitBmi160();
  initBme680();
  initUV();
}

void loop() {
  receivePacketLora();
  //Check_lorawan();
  
  CheckTimer1();
}

void CheckSensors(){
  //Check_turbulence();
  Check_weather();
}

void CheckTimer1(){
  if(millis() - checkTime1_start > checkTime1_timer){
    CheckSensors();
    
    checkTime1_start = millis();
  }
}
