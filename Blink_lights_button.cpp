#include <Arduino.h>


#ifndef LED_BUILTIN
    #define LED_BUILTIN 2
#endif

const int bootButton = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(bootButton, INPUT);
}

void loop()
{
  int pressed = digitalRead(bootButton);
  if (pressed == LOW){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(50);
}
