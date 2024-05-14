

#include "motor.h"
#include <Arduino.h>

Motor::Motor(int forward_pin, int reverse_pin) {
  forward_pin_ = forward_pin;
  reverse_pin_ = reverse_pin;
  pinMode(forward_pin_, OUTPUT);
  pinMode(reverse_pin_, OUTPUT);
  stop();
}

void Motor::set_speed(int speed) {
  speed_ = speed;
  if (speed == 0) {
    digitalWrite(forward_pin_, LOW);
    digitalWrite(reverse_pin_, LOW);
  } else if (speed > 0) {
    digitalWrite(reverse_pin_, LOW);
    analogWrite(forward_pin_, speed);
  } else { /* speed < 0 */
    digitalWrite(forward_pin_, LOW);
    analogWrite(reverse_pin_, -speed);
  }
}