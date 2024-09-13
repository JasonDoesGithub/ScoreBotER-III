

/* encoder.h
 *  written by Jason and Chad Lester 2024
 *   
 *  The Encoder class is used to scan a 2-bit grey code encoder
 *  to keep track of the position of something such as a motor. 
 *  
 *  Grey codes can be read about here:
 *  https://en.wikipedia.org/wiki/Gray_code
 *  
 *  But the gist of it is that as a motor one of the two position
 *  pins will take turns flipping from HIGH to LOW or back again.
 *  
 *              ---->  Forward direction --->
 *              <----  Reverse direction <---
 *  pin1   LOW  HIGH  HIGH  LOW   LOW  HIGH  HIGH  LOW
 *  pin2   LOW  LOW   HIGH  HIGH  LOW  LOW   HIGH  HIGH   .  .  .  . 
 *          0    1     2     3     0    1     2     3 
 *  
 *  In the example above as you move left to right, first pin1 changes, 
 *  then pin2, alternating forever.
 *  
 *  In order for an encoder to be accurate you need to scan the encoder pins
 *  at least as fast as they might change.  If the encoder moves 2 steps, we
 *  cannot be sure whether the encoder moved forward or reverse because two steps
 *  forward results in the same pin values as two steps back.  In this case
 *  we call this a "skip" and increment a skip_counter.
 *  
 *  If the encoder moved 3 steps forward without a scan it looks just the same as
 *  the enocder moved backward 1 step.   These cannot be detected, so the 
 *  skip_counter cannot detect skips where an odd number of positions is skipped..
 *  
 *  example:
 *  
 *  Motor elbow_motor(13,14);
 *  Encoder elbow_encoder(15,16);
 *  
 *  elbow_motor.set_speed(255);
 *  while (elbow.scan() < 50) {
 *    // don't do anything until the elbow gets to at least positon 50;
 *    if (elbow_encoder.skip_count_ > 0) {
 *      Serial.println("encoder skipped!");
 *      break;
 *    }
 *  }
 *  elbow_motor.stop();
 *  Serial.print("final elbow position: ");
 *  Serial.println(elbow_encoder.pos_);
 */


class Encoder {
  public:
    Encoder(int pin1, int pin2);
    int scan(); // this method should be called as often as possible
    int pos_;  // the current position.  The user can write to this value
    int skip_count_; // the number of "skips" that we've detected
  private:
    int pin1_;
    int pin2_;
    int last_encoding_;
};
