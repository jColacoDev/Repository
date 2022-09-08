
void network_join_status(String* subString){
  subString[5] = "";
  for(uint8_t x=0; x < 100;x++){
    if(device_id[x]== subString[2] && device_token[x]== subString[3]){     
      subString[4] = "NETWORK_GOOD";
      network_send_loraPacket(subString); 
      return;
    }
  }
  subString[4] = "NETWORK_BAD";
  network_send_loraPacket(subString);  
}

void network_join(String* subString){
  subString[5] = "";
  for(uint8_t x=0; x < 100; x++){
    if(device_id[x]== ""){
      device_id[x] = String(device_counter);
      device_token[x] = subString[3];
      
      subString[2] = String(device_counter);      
      subString[4] = "NETWORK_GOOD";
      
      network_send_loraPacket(subString);

      device_counter++;
      return;
    }
  }
}

void network_send_loraPacket(String* subString){
  subString[0] = gateway_id;
  subString[1] = gateway_password;
  String packet = "";
  for(uint8_t x= 0; x < 6; x++){
    packet.concat('&');
    packet.concat(subString[x]);
  }
  Serial.println(packet);
  sendPacketLora(packet);
}

bool nodeExists(String* subString){
  if(subString[0]==gateway_id && subString[1]==gateway_password){
    for(uint8_t x=0; x < 100;x++){
      
    }
  }  
}


void lora_receive_commands(String LoRaData){
  String subString[6];

  uint8_t index = LoRaData.indexOf('&');
  uint8_t nextIndex;
    
  for(uint8_t x= 0; x < 6; x++){
    nextIndex= LoRaData.indexOf('&', index+1);  
    if(nextIndex == -1)nextIndex= LoRaData.length();
    subString[x] = LoRaData.substring(index+1,nextIndex);
    Serial.print(subString[x]);Serial.print(", ");
    index = nextIndex;
  }
  Serial.println("");

  if(subString[0]==gateway_id && subString[1]==gateway_password ){
    if(subString[4] == "NETWORK_JOIN"){
      network_join(subString);
    }else if(subString[4] == "NETWORK_JOIN_STATUS"){
      network_join_status(subString);
    }else if(subString[4] == "SENSORS"){
      
    }else if(subString[4] == "ALERT"){
      
    } 
  }
}
