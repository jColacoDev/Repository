/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Keypad
#include <Keypad.h>
#define keypad_ROW_NUM     4 // four rows
#define keypad_COLUMN_NUM  4 // four columns

char keys[keypad_ROW_NUM][keypad_COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte pin_rows[keypad_ROW_NUM]      = {2,4,6,8}; // GIOP19, GIOP18, GIOP5, GIOP17 connect to the row pins
byte pin_column[keypad_COLUMN_NUM] = {10,11,12,14};
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, keypad_ROW_NUM, keypad_COLUMN_NUM );
*/
int firstDigit(int n){
    // Find total number of digits - 1
    int digits = (int)log10(n);
    // Find first digit
    n = (int)(n / pow(10, digits));
    // Return first digit
    return n;
}
void keypadDirectionsPrinter(char key){
  uint32_t timeStart = millis();
  int intKey = String(key).toInt(); 
  ledStrip_turnAllOn("blueviolet");  
  ledStrip_turnDirectionOn(keypad_directions[intKey], "green");
  ledStrip_turnDirectionOn("Center", "green");
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(keypad_directions_place[intKey]);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  
  uint32_t distance = keypad_directions_distance[intKey];
  if(distance < uint32_t(1000)){
    lcd.print(distance);lcd.print("m at ");
    //sevseg.setNumber(distance);
     sevseg.setNumber(distance,3);
  }else if(distance < uint32_t(10000)){
    sevseg.setNumber(distance/10,3);
  }else{
    lcd.print(distance/uint32_t(1000));lcd.print(",");lcd.print(firstDigit(distance%1000));lcd.print("Km ");
    sevseg.setNumber(distance/1000);
  }
  lcd.print(keypad_directions[intKey]);
  while(millis()-timeStart < 5000){
      sevseg.refreshDisplay(); 
  }
}

void checkKeypad(){
  //Serial.println("keypad Getting it! :   ----");
  char key = keypad.getKey();
  if (key){    
    if(keypad_print){
      Serial.println(key);  
    }    
    switch (key) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      keypadDirectionsPrinter(key);
      playAudioNoDelay("keypad_direction");
        break;
        
      case 'A':
        break;
      case 'B':
        break;
      case 'C':
        break;
      case 'D':      
        break;
      case '*':
        break;
      case '#':
      
        break;
      default:
        break;
    }
  }
}
