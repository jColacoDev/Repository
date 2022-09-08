/*
#include <SevSegShift.h>

#define SHIFT_PIN_SHCP 37
#define SHIFT_PIN_STCP 35
#define SHIFT_PIN_DS   33

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);
byte numDigits = 4;
byte digitPins[] = {63, 65, 67, 69}; // These are the PINS of the ** Arduino **
byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // these are the PINs of the ** Shift register **
bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_CATHODE; // See README.md for options
bool updateWithDelays = false; // Default 'false' is Recommended
bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

//loop always no delay!
sevseg.refreshDisplay();

//use:
sevseg.setNumber(500);
*/

void initSevenSegments(){
  Serial.println(F("Initializing SevenSegments ..."));
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
  Serial.println(F("SevenSegments Initialized"));
}
