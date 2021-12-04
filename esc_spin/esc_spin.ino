#include <Servo.h>
Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

void setup() {
  esc1.attach(6);
  esc2.attach(7);
  esc3.attach(8);
  esc4.attach(9);
  pinMode(A0,INPUT);
}

void loop() {
  esc_spin(map(analogRead(A0),0,1023,0,255));
}

void esc_spin(int spd) {
  spd = map(spd,0,255,1000,2000);
  esc1.writeMicroseconds(spd);
  esc2.writeMicroseconds(spd);
  esc3.writeMicroseconds(spd);
  esc4.writeMicroseconds(spd);
}
