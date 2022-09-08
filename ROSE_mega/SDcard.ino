/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SDcard
#include "SD.h"

#define sd_csPin 53
uint8_t sd_cardType;
uint64_t sd_cardSize;
File sd_File;
*/

void initSDcard(){
  uint8_t aux = 0;
  uint8_t tries = 5;
  
  Serial.println("Initializing SdCard ...");
  while(!SD.begin(sd_csPin) && aux < tries){
    Serial.print("Didn't find SDcard try number: ");Serial.println(aux);
    aux++;
    delay(1000);
  }
  if (tries == aux) {
    Serial.println(F("Unable to begin SDcard"));
  }else{
    Serial.println(F("SDcard online."));
  }
}

void testSDcard(){
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
