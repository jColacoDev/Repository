/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SDcard
#include "SD.h"
#define sd_csPin 25
uint8_t sd_cardType;
uint64_t sd_cardSize;
File sd_File;

*/

void InitSDcard(){
  Serial.println("Initializing SDcard...");
  if(!SD.begin(sd_csPin)){
    Serial.print("Not ");
  }else{
    if(sd_cardType == CARD_NONE){
      Serial.println("No SD card attached");
    }else{
      sd_on = true;
    }
  }
  Serial.println("Initialized ");
  Serial.println("");
}

void TestSDcard(){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  sd_File = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (sd_File) {
    Serial.print("Writing to test.txt...");
    sd_File.println("testing 1, 2, 3.");
    // close the file:
    sd_File.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  sd_File = SD.open("test.txt");
  if (sd_File) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (sd_File.available()) {
      Serial.write(sd_File.read());
    }
    // close the file:
    sd_File.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
