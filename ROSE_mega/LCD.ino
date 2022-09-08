/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
*/

void initLCD(){
  LiquidCrystal_I2C lcd(0x27,16,2);
  lcd.begin();

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  Compass Rose  ");
  lcd.setCursor(0,1);
  lcd.print("initializating..");

  Serial.println("LCD STARTED");
}
