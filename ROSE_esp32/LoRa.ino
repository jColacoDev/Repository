/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LoRa
#include <SPI.h>
#include <LoRa.h>
#define lora_ss 15
#define lora_rst 16
#define lora_dio0 17
*/

void initLora(){
  LoRa.setPins(lora_ss, lora_rst, lora_dio0);
  //433E6 for Asia //866E6 for Europe //915E6 for North America
  while (!LoRa.begin(433E6)) {Serial.println(".");delay(500);}
  // Change sync word (0xF3) to match the receiver // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void receivePacketLora(){
  String LoRaData;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
    }
    Serial.print(LoRaData); 
    Serial.println(LoRa.packetRssi());

    int str_len = LoRaData.length() + 1; 
    char char_array[str_len];
    LoRaData.toCharArray(char_array, str_len);
    LoRaData = decode(char_array);
    Serial.print(LoRaData);     
  }
}

void sendPacketLora(String LoRaData){
  int str_len = LoRaData.length() + 1; 
  char char_array[str_len];
  LoRaData.toCharArray(char_array, str_len);
    
  LoRa.beginPacket();
  LoRa.println(encode(char_array));
  LoRa.endPacket();
}
