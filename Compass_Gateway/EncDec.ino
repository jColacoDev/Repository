/*
#include "Base64.h"

  String str = encode("This ?!#$%&/()='}][{§££@");
  
  int str_len = str.length() + 1; 
  char char_array[str_len];
  str.toCharArray(char_array, str_len);

  decode(char_array);
*/


String decode(char inputString[]){
  int inputStringLength = strlen(inputString);
  int decodedLength = Base64.decodedLength(inputString, inputStringLength);
  char decodedString[decodedLength];
  Base64.decode(decodedString, inputString, inputStringLength);
  
  return String(decodedString);
}

String encode(char inputString[]){
  int inputStringLength = strlen(inputString);
  int encodedLength = Base64.encodedLength(inputStringLength);
  char encodedString[encodedLength];
  Base64.encode(encodedString, inputString, inputStringLength);

  return String(encodedString);
}
