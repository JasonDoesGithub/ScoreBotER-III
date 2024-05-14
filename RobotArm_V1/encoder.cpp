
#include "encoder.h"
#include <Arduino.h>

Encoder::Encoder(int pin1, int pin2) {
  pin1_ = pin1;
  pin2_ = pin2;
  pinMode(pin1_, INPUT_PULLUP);
  pinMode(pin2_, INPUT_PULLUP);
  
  scan();  // scan once to initialize the last_encoding_;
  skip_count_ = 0;
  pos_ = 0;







































  
}



int Encoder::scan() {
  int pin1_value = digitalRead(pin1_);
  int pin2_value = digitalRead(pin2_);

  /*              ---->  Forward direction --->
   *              <----  Reverse direction <---
   *  pin1   LOW  HIGH  HIGH  LOW   LOW  HIGH  HIGH  LOW
   *  pin2   LOW  LOW   HIGH  HIGH  LOW  LOW   HIGH  HIGH   .  .  .  . 
   *          0    1     2     3     0    1     2     3 
   */

  // determine the encoding value 0-3 of the pins.
  int encoding;
  if (pin1_value == LOW) {
    if (pin2_value == LOW) encoding = 0; else encoding = 3;
  } else {
    if (pin2_value == LOW) encoding = 1; else encoding = 2;
  }

  switch (encoding - last_encoding_) {
    case -1:
    case 3:
      pos_--;
      break;
    case 1:
    case -3:
      pos_++;
      break;
    case 2:
    case -2:
      skip_count_++;
  }
  last_encoding_ = encoding;
}
