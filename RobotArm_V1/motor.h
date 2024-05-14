
/* motor.h
 *  Written by Jason Lester, 2024
 *  
 *  The Motor class controls a 2-pin variable speed motor.
 *  
 *  It uses 2 Pulse-Width-Modulated (PWM) igital output pins to drive the motor.
 *  The two pins that are needed are
 *    1. forward_pin, which drives the motor forward
 *    2. reverse_pin, which drives the motor in reverse.
 *  
 *  This class ensures that both pins are not on at the same time.
 *  
 *  It has a set_speed() method, which accepts a speed argument from -255 to 255.
 *  A positive speed is forward and a negative speed is reverse.
 *  
 *  Example usage:
 *  
 *  Motor base(8,9);
 *  
 *  // move forward for 1 second
 *  base.set_speed(255);
 *  delay(1000);
 *  base.stop();
 */

class Motor {
  public:
    // initialize the motor with fowrad and reverse pins
    Motor(int forwrard_pin, int reverse_pin);

    // if this motor object is deleted we should stop the motor
    ~Motor() { stop(); };

    // set the speed of the motor from -255 (full reverse) to +255 (full forward)
    void set_speed(int speed);

    void forward() { set_speed(255); }

    void reverse() { set_speed(-255); }

    // stop the motor
    void stop() { set_speed(0); }

    // return the last set speed
    int get_speed() { return speed_; }

  private:
    int forward_pin_;  // The pin that when HIGH, drives the motor forward
    int reverse_pin_;  // The pin that when HIGH, drives the motor in reverse
    int speed_;  // The current speed of the motor
};