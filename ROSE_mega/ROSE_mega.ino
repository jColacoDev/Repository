#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "SoftwareSerial.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gas Sensor
#define mq2_pin A5
bool mq2_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RTC ds3231
#include "RTClib.h"
RTC_DS3231 rtc;
char rtc_daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool rtc_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bmp280
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;
float bmp_values[3];
bool bmp_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MP3 DFplayer
#include "DFRobotDFPlayerMini.h"
DFRobotDFPlayerMini DFplayer;
bool dfPlayer_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BMI 160 Gyro
#include <BMI160Gen.h>
const int bmi160_addr = 0x68;
bool gyro_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PN532 RFID
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
bool rfid_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compass
#include <QMC5883LCompass.h>
QMC5883LCompass compass;
bool magneto_print = true;
char compass_direction[3];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SDcard
#include "SD.h"
#define sd_csPin 52
uint8_t sd_cardType;
uint64_t sd_cardSize;
File sd_File;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ultrassonic
#define echoPin A1 // attach pin to pin Echo of HC-SR04
#define trigPin A3 //attach pin to pin Trig of HC-SR04
bool ultrassonic_print = true;
uint32_t presenceDetected = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Keypad
#include <Keypad.h>
#define keypad_ROW_NUM     4
#define keypad_COLUMN_NUM  4
char keypad_keys[keypad_ROW_NUM][keypad_COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte keypad_pin_rows[keypad_ROW_NUM] = {A0, A2, A4, A6}; //connect to the row pinouts of the keypad
byte keypad_pin_column[keypad_COLUMN_NUM] = {A8, A10, A12, A14};

Keypad keypad = Keypad(makeKeymap(keypad_keys), keypad_pin_rows, keypad_pin_column, keypad_ROW_NUM, keypad_COLUMN_NUM );
bool keypad_print = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastLeds
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

#include <FastLED.h>
#define ledStrip_pin        A7
#define ledStrip_ledsNum    70
#define ledStrip_brightness 64
#define FRAMES_PER_SECOND 60
CRGB ledStrip_leds[ledStrip_ledsNum];
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 500
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
CRGBPalette16 gPal;
bool gReverseDirection = false;
String mode_rose = "standBy";
#define ledStrip_segmentsNum 9
int ledStrip_segments[ledStrip_segmentsNum][2] = {{0,5}, {5,6}, {11,5}, {16,7}, {23,5}, {28,6}, {34,5}, {39,7}, {46,24}};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Timers
uint32_t checkTimeRFID_start = 0;
int checkTimeRFID_timer = 2000;

uint32_t checkTime1_start = 0;
uint32_t checkTime1_timer = 60000;

uint32_t checkTime2_start = 0;
uint32_t checkTime2_timer = 1000;

uint32_t dfPlayer_timer_start = 0;
int dfPlayer_timer = 0;

uint32_t led_segment_timer_start[ledStrip_segmentsNum];
int led_segment_timer[ledStrip_segmentsNum];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Direction Map
String keypad_directions[10] = {"North","N.East","East","S.East","South","S.West","West","S.West","CENTER", "East"};
String keypad_directions_place[10] = {"Porto","Coimbra","Albufeira","Corvos","Madrid","Nazare","ErgoFace", "Guarda", "Torre de Belem","Meca"};
uint32_t keypad_directions_distance[10] = {322000,5,345867,286978,523967,13653, 213,74,1257,9234};

// Uid Bank
String rfid_uid[100];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Seven Segments 595
#include <SevSegShift.h>
long number = 0; 

#define SHIFT_PIN_SHCP 37
#define SHIFT_PIN_STCP 35
#define SHIFT_PIN_DS   33

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);
byte numDigits = 4;
byte digitPins[] = {63, 65, 67, 69}; // These are the PINS of the ** Arduino **
byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // these are the PINs of the ** Shift register **
bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_CATHODE; // See README.md for options
bool updateWithDelays = true; // Default 'false' is Recommended
bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  delay(2000);
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("--Serial STARTED--");
  Serial1.begin(9600);
  while (!Serial1);
  Serial.println("--Serial1 STARTED--");
  Serial2.begin(9600);
  while (!Serial2);
  Serial.println("--Serial2 STARTED--");
  Serial3.begin(9600);
  while (!Serial3);
  Serial.println("--Serial3 STARTED--");
  Serial.println("------- -------");
  delay(500);

  initLCD();
  initMagneto();
  initBmp280();
  initRTC();
  initRFID();
  initDFplayer();
  initLedStrip();
  initUltrassonic();
  initSevenSegments();
  
  initSDcard();
  initBmi160Gyro();

  testSDcard();

  playAudioNoDelay("proximity_sensor");
  Serial.println("-------------- --------------");
  Serial.println("--------- Setup End ---------");
  Serial.println("-------------- --------------");
  lcd.clear();
  currentPalette = CloudColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("! Compass Rose !");

  createLoopRosePallet();
  dfPlayer_checkExpired();
  ledStrip_checkExpired();
  checkSerial2();
  checkRFID();
  checkKeypad();
  get_ultraSonic_distance();

  checkTimer1();
}

void checkTimer1(){
  if(millis() - checkTime1_start > checkTime1_timer){
    Serial.println("");
    Serial.println("-- Timer1 START --");
    playAudioNoDelay("loop_birds");
    Serial.print("Date: ");
    Serial.print(get_rtc_fullDateStamp());
    Serial.println(" dd/MM/YYYY hh/mm/ss");
    Serial.print("Interior temperature: ");
    Serial.print(get_rtc_temperature());
    Serial.println(" *C");
    Serial.print("Pointing direction: ");
    
    getSensors();
    sendSensors();
    
    Serial.println("-- Timer1 END --");
    checkTime1_start = millis();
  }
}

void checkTimer2(){
  if(millis() - checkTime2_start > checkTime2_timer){
    
    checkTime2_start = millis();
  }
}

void getSensors(){
    get_magneto_direction();Serial.println("");
    get_bmp280();
    get_mq2_gasSensor();

    get_bmi160gyro();

    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(get_rtc_timeHours());lcd.print("h ");
    lcd.print(String(bmp_values[0],1));lcd.print((char)223);lcd.print("C ");
    lcd.print(compass_direction[0]);lcd.print(compass_direction[1]);lcd.print(compass_direction[2]);
}

void sendSensors(){
    Serial2.print("&temperature=");
    Serial2.print(bmp_values[0],1);
    Serial2.print("&pressure=");
    Serial2.print(bmp_values[1],1);
    Serial2.print("&altitude=");
    Serial2.print(bmp_values[2],1);
    Serial2.print("&gas=");
    Serial2.println(get_mq2_gasSensor());
}
