/*
#include <Ultrasonic.h>
Ultrasonic ultrasonic(A2, A1); // trigger, echo
int distance;
bool uSonic_print = true;
*/

void initUltrassonic(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.println("Ultrassonic Initialized");
}

void checkPresenceDetected(){
  if((millis() - presenceDetected > 10000) && presenceDetected != 0){
    presenceDetected = 0;  
    mode_rose = "standBy"; 
  }
}

int get_ultraSonic_distance(){
  long duration; // variable for the duration of sound wave travel
  int distance; // variable for the distance measurement
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  if(distance < 10){
    if(presenceDetected == 0) playAudioNoDelay("proximity_sensor");
    presenceDetected = millis();  
    mode_rose = "greeting"; 
    if(ultrassonic_print){
      Serial.print("Presence detected, distance: ");
      Serial.print(distance);
      Serial.println(" cm");  
    }
  }
  checkPresenceDetected();
  
  return distance;
}
