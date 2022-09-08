/*
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PN532 RFID
  #include <Wire.h>
  #include <PN532_I2C.h>
  #include <PN532.h>
  #include <NfcAdapter.h>

  PN532_I2C pn532_i2c(Wire);
  NfcAdapter nfc = NfcAdapter(pn532_i2c);
*/

void initRFID() {
  Serial.println("Initializing RFID ...");
  nfc.begin();
  Serial.println(F("RFiD online."));
}

void checkRFID() {
  if(millis() - checkTimeRFID_start > checkTimeRFID_timer){
    if (nfc.tagPresent(15)) {
      NfcTag tag = nfc.read();
      String tag_string = tag.getUidString();
        uint32_t timeStart = millis(); 
        lcd.setCursor(0,0);
        if(rfid_uid_exists(tag_string)){    
          ledStrip_turnDirectionOn("Center", "green");
          lcd.print("Hello User!     ");
          playAudio("rfid_success");
        }else{            
          ledStrip_turnDirectionOn("Center", "red");
          lcd.print("Hello stranger! ");
          playAudio("rfid_error");
        }
        lcd.setCursor(0,1);lcd.print(tag_string);
        while(millis()-timeStart < 1500);
        ledStrip_turnDirectionOn("Center", "black");
          
      if (rfid_print) {
        Serial.println(tag.getTagType());
        Serial.print("UID: "); Serial.println(tag.getUidString());
      }
      if (tag.hasNdefMessage()) {
        NdefMessage message = tag.getNdefMessage();
        if (rfid_print) {
          Serial.print("\nThis NFC Tag contains an NDEF Message with ");
          Serial.print(message.getRecordCount());
          Serial.print(" NDEF Record");
          if (message.getRecordCount() != 1) {
            Serial.print("s");
          }
          Serial.println(".");
        }
        // cycle through the records, printing some info from each
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++)
        {
          NdefRecord record = message.getRecord(i);
          if (rfid_print) {
            Serial.print("\nNDEF Record "); Serial.println(i + 1);
            // NdefRecord record = message[i]; // alternate syntax
            Serial.print("  TNF: "); Serial.println(record.getTnf());
            Serial.print("  Type: "); Serial.println(record.getType()); // will be "" for TNF_EMPTY
          }
          // The TNF and Type should be used to determine how your application processes the payload
          // There's no generic processing for the payload, it's returned as a byte[]
          int payloadLength = record.getPayloadLength();
          byte payload[payloadLength];
          record.getPayload(payload);
  
          if (rfid_print) {
            // Print the Hex and Printable Characters
            Serial.print("  Payload (HEX): ");
            PrintHexChar(payload, payloadLength);
          }
          // Force the data into a String (might work depending on the content)
          // Real code should use smarter processing
          String payloadAsString = "";
          for (int c = 0; c < payloadLength; c++) {
            payloadAsString += (char)payload[c];
          }
          
          String uid = record.getId();
          playAudioNoDelay("rfid_success");
          if (rfid_print) {
            Serial.print("  Payload (as String): ");
            Serial.println(payloadAsString);
            // id is probably blank and will return ""
            if (uid != "") {
              Serial.print("  ID: "); Serial.println(uid);
            }
          }
        }
      }
      checkTimeRFID_start = millis();
    }
  }
}

bool rfid_uid_exists(String uid){
  for(int x=0; x < 100; x++){
    if(rfid_uid[x] == uid) return true;
  }
  return false;
}
