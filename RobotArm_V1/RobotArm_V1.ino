/* Robot Arm
 *  written by Jason and Chad Lester, 2024
 *  
 *  This program controls a 6 motor robotic arm with a gripper
 *  
 */

// The motor library is used to control reversable variable speed motors
#include "motor.h"
#include "encoder.h"
Motor * base;
Motor * shoulder;
Motor * elbow;
Motor * wrist1;
Motor * wrist2
Motor * gripper
Encoder * base_enc;
Encoder * wrist1_enc;
Encoder * shoulder_enc;
Encoder * elbow_enc;
Encoder * wrist2_enc
Encoder * gripper_enc
const int baseZero = 2;
const int shoulderZero = 3;
const int wrist1Zero = 19;
const int elbowZero = 18;



void setup() {
  // put your setup code here, to run once:
  base = new Motor(13, 12);
  shoulder = new Motor(6,7);
  elbow = new Motor(8,9);
  wrist2 = new Motor(4, 5);
  wrist1 = new Motor(10, 11);
  gripper = new Motor(44, 45);
  base_enc = new Encoder(22, 23);
  elbow_enc = new Encoder(26, 27);
  shoulder_enc = new Encoder(24, 25);
  wrist1_enc = new Encoder(28, 29);
  wrist2_enc = new Encoder(30, 31);
  gripper_enc = new Encoder(32, 33);

  Serial.begin(115200);
  pinMode(baseZero, INPUT_PULLUP);
  pinMode(shoulderZero, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(shoulderZero), shoulderInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(elbowZero), elbowInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(baseZero), baseInterrupt, FALLING);
  //Serial.println("Setup");
}



void goTo(Motor * m, Encoder * e, int pos){
  
  while(pos > e->pos_){
    m->set_speed(255);
    e ->scan();
    }
  while(pos < e->pos_){
    m->set_speed(-255);
    e->scan();
    }
  m->stop();
}

void shoulderInterrupt(){
//Serial.println("Shoulder Tripped");
shoulder_enc->pos_ = 0;
}
void elbowInterrupt(){
Serial.println("Elbow Tripped");
shoulder_enc->pos_ = 0;
}

void baseInterrupt(){
 
  //Serial.println("Base Tripped");
  base_enc->pos_ = 0;
}

void botDelay(long int time) {
  long int startTime = millis();
  while((millis() - startTime) < time){
    base_enc ->scan();
    shoulder_enc->scan();
  }
}


void waitForStop(Encoder * enc){
 while(true){
    int pos = enc->pos_;
    botDelay(100);
   // Serial.println(pos);
    if(pos == enc->pos_){
     // Serial.println("Stopped");
      break;
    }
  }
}
void findZero(Motor * m, Encoder * e){
 // Serial.println("Forward");
  m -> forward();
  waitForStop(e);
  m->stop();
  // Serial.println("Reverse");
  m -> reverse();
  waitForStop(e);
  m->stop();
  goTo(m,e,0);
}
void calibration(){
  shoulder -> reverse();
  base -> reverse();
  botDelay("2000");
  shoulder -> stop();
  base -> stop();
  Serial.print("Starting Calibration");
  botDelay("3000");
  Serial.println("Base Callibration Started");
  findZero(base, base_enc);
  Serial.println("Base Callibration Finished");
  botDelay("3000");
  Serial.println("Shoulder Callibration Started");
  findZero(shoulder, shoulder_enc);
  Serial.println("Shoulder Callibration finished");
  while(true);
}

void loop() {
  calibration();
//elbow -> forward();
//botDelay(1000);
//elbow -> stop();
//elbow -> reverse();
//botDelay(1000);
//elbow -> stop();


}
