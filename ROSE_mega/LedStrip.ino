/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FastLeds
#include <FastLED.h>
#define ledStrip_pin        7
#define ledStrip_ledsNum    70
#define ledStrip_brightness 64
CRGB ledStrip_leds[ledStrip_ledsNum];

#define ledStrip_segmentsNum 9
int ledStrip_segments[ledStrip_segmentsNum][2] = {{0,5}, {5,6}, {11,5}, {16,7}, {23,5}, {28,6}, {34,5}, {39,7}, {46,24}};
*/

void initLedStrip(){
  initFastLed();
  ledStrip_turnAllOff();

  for(int i=0;i<ledStrip_segmentsNum;i++){
    led_segment_timer[i] = 1000;
    led_segment_timer_start[i] = 0;
  }
}

void initFastLed(){
  FastLED.addLeds<WS2812B, ledStrip_pin, GRB>(ledStrip_leds, ledStrip_ledsNum);
  FastLED.setBrightness( ledStrip_brightness );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  gPal = HeatColors_p;
}

void createLoopRosePallet(){
  if(mode_rose == "standBy"){
    //ChangePalettePeriodically();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; // motion speed
    FillLEDsFromPaletteColors( startIndex);
  }else if(mode_rose == "greeting"){
    random16_add_entropy( random());
    Fire2012WithPalette(); 
    FastLED.show(); // display this frame
  }
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}
void BlinkSegments(){  
  for(int y = 0; y < ledStrip_segmentsNum; y++){
    int segmentStart= ledStrip_segments[y][0];
    int segmentLenght= ledStrip_segments[y][1];
    
     for(int i = segmentStart; i < segmentStart + segmentLenght; i++){
      ledStrip_leds[i] = get_ledColor("green");
      
      if(y == 0)ledStrip_leds[i] = get_ledColor("green");
      if(y == 1)ledStrip_leds[i] = get_ledColor("red");
      if(y == 2)ledStrip_leds[i] = get_ledColor("white");
      if(y == 3)ledStrip_leds[i] = get_ledColor("red");
      if(y == 4)ledStrip_leds[i] = get_ledColor("blue");
      if(y == 5)ledStrip_leds[i] = get_ledColor("orange");
      if(y == 6)ledStrip_leds[i] = get_ledColor("blueviolet");
      if(y == 7)ledStrip_leds[i] = get_ledColor("red");
    }
    
    FastLED.show();
    delay(300);
    // Now turn the LED off, then pause
      for(int i = segmentStart; i < segmentStart + segmentLenght; i++){
      ledStrip_leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(200); 
  }
}

void ledStrip_turnDirectionOn(String direction, String color){
  uint8_t segment = get_led_segment(direction);
  if(segment < ledStrip_segmentsNum){
    uint8_t segmentStart= ledStrip_segments[segment][0];
    uint8_t segmentLenght= ledStrip_segments[segment][1];
      
    for(int i = segmentStart; i < segmentStart + segmentLenght; i++){
      ledStrip_leds[i] = get_ledColor(color);
    }
    FastLED.show();
    led_segment_timer_start[segment] = millis();
  }
}
void ledStrip_checkExpired(){
  for(uint8_t x= 0; x < ledStrip_segmentsNum; x++){
    if((millis() - led_segment_timer_start[x] > led_segment_timer[x]) && led_segment_timer_start[x] != 0){
      ledStrip_turnSegmentOff( x );
      led_segment_timer_start[x] = 0;
    }
  }
}

CRGB get_ledColor(String color){
  CRGB ledColor;
  if( color == "black") ledColor= CRGB::Black; else
  if( color == "white") ledColor= CRGB::White; else
  if( color == "green") ledColor= CRGB::Green; else
  if( color == "red"  ) ledColor= CRGB::Red; else
  if( color == "blue" ) ledColor= CRGB::Blue; else
  if( color == "orange")ledColor= CRGB::Orange; else
  if( color == "blueviolet")ledColor= CRGB::BlueViolet;
  return ledColor;
}

uint8_t get_led_segment(String direction){
  uint8_t segment;
  if(direction == "S.East") segment=0; else
  if(direction == "East") segment=1; else
  if(direction == "N.East") segment=2; else
  if(direction == "North") segment=3; else
  if(direction == "S.West") segment=4; else
  if(direction == "West") segment=5; else
  if(direction == "S.West") segment=6; else
  if(direction == "South") segment=7; else
  if(direction == "Center") segment=8;
  return segment;
}

void ledStrip_turnSegmentOff(uint8_t segment){
  uint8_t segmentStart= ledStrip_segments[segment][0];
  uint8_t segmentLenght= ledStrip_segments[segment][1];
  for(int i = segmentStart; i < segmentStart + segmentLenght; i++){
    ledStrip_leds[i] = CRGB::Black;
  }
  FastLED.show(); 
}
void ledStrip_turnSegmentOn(uint8_t segment, String color){
  uint8_t segmentStart= ledStrip_segments[segment][0];
  uint8_t segmentLenght= ledStrip_segments[segment][1];
  for(int i = segmentStart; i < segmentStart + segmentLenght; i++){
    ledStrip_leds[i] = get_ledColor(color);
  }
  FastLED.show(); 
}

void ledStrip_turnAllOn(String color){
  for(uint8_t x = 0; x < ledStrip_segmentsNum; x++){
    ledStrip_turnSegmentOn( x, color );
  }
  FastLED.show(); 
}

void ledStrip_turnAllOff(){
  for(uint8_t x = 0; x < ledStrip_segmentsNum; x++){
    ledStrip_turnSegmentOff( x );
  }
  FastLED.show(); 
}


void FillLEDsFromPaletteColors( uint8_t colorIndex){
    uint8_t brightness = 255;
    for( int i = 0; i < ledStrip_ledsNum; ++i) {
        ledStrip_leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically(){
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};


void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[ledStrip_ledsNum];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < ledStrip_ledsNum; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / ledStrip_ledsNum) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= ledStrip_ledsNum - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < ledStrip_ledsNum; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (ledStrip_ledsNum-1) - j;
      } else {
        pixelnumber = j;
      }
      ledStrip_leds[pixelnumber] = color;
    }
}
