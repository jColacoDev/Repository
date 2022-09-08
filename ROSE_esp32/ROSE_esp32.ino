#include "Arduino.h"
#include "Base64.h"
#include <Wire.h>
#include <SPI.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LoRa
#include <LoRa.h>
#define lora_ss 32
#define lora_rst 33
#define lora_dio0 25

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("--Serial STARTED--");
  Serial1.begin(9600);
  while (!Serial1);
  Serial.println("--Serial1 STARTED--");
  Serial2.begin(9600);
  while (!Serial2);
  Serial.println("--Serial2 STARTED--");

  Serial.println("------- -------");
  delay(500);

  initLora();
}

void loop() {
  checkSerial2();
}

void checkSerial2(){
  if (Serial2.available()) {
    String serialString = Serial2.readString();
    Serial.println(serialString);
    sendPacketLora("&001&3333&001&4444&NETWORK_JOIN");
  }
}
