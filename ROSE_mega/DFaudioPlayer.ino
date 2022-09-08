/*
// MP3 DFplayer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DFRobotDFPlayerMini.h"
SoftwareSerial DFplayerSerial(15, 14); // RX, TX
DFRobotDFPlayerMini DFplayer;
bool dfPlayer_print = true;

// DFplayerSerial.begin(9600);
*/

void initDFplayer(){
  uint8_t aux = 0;
  uint8_t tries = 5;
  
  Serial.println(F("Initializing DFPlayer ..."));
  delay(4000);
  while(!DFplayer.begin(Serial1) && aux < tries){
    Serial.print("Didn't find DFplayer try number: ");Serial.println(aux);
    aux++;
    delay(1000);
  }
  delay(4000);
  if (tries == aux) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }else{
    Serial.println(F("DFPlayer Mini online."));
  }
  DFplayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  DFplayer.volume(18);  //Set volume value (0~30).
//  DFplayer.volumeUp(); //Volume Up
//  DFplayer.volumeDown(); //Volume Down
  
  //----Set different EQ----
  DFplayer.EQ(DFPLAYER_EQ_NORMAL);
//  DFplayer.EQ(DFPLAYER_EQ_POP);
//  DFplayer.EQ(DFPLAYER_EQ_ROCK);
//  DFplayer.EQ(DFPLAYER_EQ_JAZZ);
//  DFplayer.EQ(DFPLAYER_EQ_CLASSIC);
//  DFplayer.EQ(DFPLAYER_EQ_BASS);
  
  //----Set device we use SD as default----
//  DFplayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  DFplayer.outputDevice(DFPLAYER_DEVICE_SD);
//  DFplayer.outputDevice(DFPLAYER_DEVICE_AUX);
//  DFplayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
//  DFplayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  if(dfPlayer_print){
    DFplayer_readInformation();
  }
}
void DFplayer_control(){
      //----Mp3 control----
//  DFplayer.sleep();     //sleep
//  DFplayer.reset();     //Reset the module
//  DFplayer.enableDAC();  //Enable On-chip DAC
//  DFplayer.disableDAC();  //Disable On-chip DAC
//  DFplayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15
}
void DFplayer_readInformation(){
  //----Read imformation----
  Serial.print("MP3 state: ");Serial.println(DFplayer.readState()); //read mp3 state
  Serial.print("MP3 volume(max=30): ");Serial.println(DFplayer.readVolume()); //read current volume
  Serial.print("MP3 Equalizer setting: ");Serial.println(DFplayer.readEQ()); //read EQ setting
  Serial.print("MP3 files: ");Serial.println(DFplayer.readFileCounts()); //read all file counts in SD card
  Serial.print("MP3 current audio: ");Serial.println(DFplayer.readCurrentFileNumber()); //read current play file number
  Serial.print("MP3 files in folder 3: ");Serial.println(DFplayer.readFileCountsInFolder(3)); //read file counts in folder SD:/03
}

void playAudio(String type){
  if(type == "rfid_success") playAudioNumber(0, 1000);
  if(type == "rfid_error") playAudioNumber(0, 1000);
  if(type == "keypad_direction") playAudioNumber(0, 1000);
  if(type == "proximity_sensor") playAudioNumber(1, 6000);
}
void playAudioNoDelay(String type){
  if(type == "loop_birds") playAudioNumberNoDelay(0, 2000);
  if(type == "keypad_direction") playAudioNumberNoDelay(2, 4000);
  if(type == "rfid_success") playAudioNumberNoDelay(0, 1000);
  if(type == "rfid_error") playAudioNumberNoDelay(0, 1000);
  if(type == "proximity_sensor") playAudioNumberNoDelay(1, 6000);
}
    
void playAudioNumberNoDelay(int audioNumber, int timeLenght){
  DFplayer.pause();
  DFplayer.play(audioNumber);
  dfPlayer_timer_start = millis();
  dfPlayer_timer = timeLenght;
}

void playAudioNumber(int audioNumber, int timeLenght){
  DFplayer.pause();
  DFplayer.play(audioNumber);
  delay(timeLenght);
  DFplayer.pause();
}

void playTestMusics(){
  for(int x = 0; x < 4; x++){
    Serial.print("Playing Audio: ");Serial.println(x);
    DFplayer.play(x);
    delay(3000);
  }
  DFplayer.pause();
}

void playTestMusics_functions(){
  //----Mp3 play----
  DFplayer.next();  //Play next mp3
  delay(1000);
  DFplayer.previous();  //Play previous mp3
  delay(1000);
  DFplayer.play(1);  //Play the first mp3
  delay(1000);
  DFplayer.loop(1);  //Loop the first mp3
  delay(1000);
  DFplayer.pause();  //pause the mp3
  delay(1000);
  DFplayer.start();  //start the mp3 from the pause
  delay(1000);
  DFplayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  DFplayer.enableLoopAll(); //loop all mp3 files.
  delay(1000);
  DFplayer.disableLoopAll(); //stop loop all mp3 files.
  delay(1000);
  DFplayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
  delay(1000);
  DFplayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
  delay(1000);
  DFplayer.stopAdvertise(); //stop advertise
  delay(1000);
  DFplayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
  delay(1000);
  DFplayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
  delay(1000);
  DFplayer.randomAll(); //Random play all the mp3.
  delay(1000);
  DFplayer.enableLoop(); //enable loop.
  delay(1000);
  DFplayer.disableLoop(); //disable loop.
  delay(1000);
}

void dfPlayer_checkExpired(){
  if((millis()-dfPlayer_timer_start > dfPlayer_timer_start) && dfPlayer_timer_start != 0){
    dfPlayer_timer_start = 0;
    dfPlayer_timer = 0;
    DFplayer.pause();
  }
}
