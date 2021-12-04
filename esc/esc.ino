#include <Servo.h>

Servo esc;

void setup() {
  // put your setup code here, to run once:
  esc.attach(8);
  esc.writeMicroseconds(1000);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  esc.writeMicroseconds(map(analogRead(A0),0,1023,1000,2000));
  Serial.println((map(analogRead(A0),0,1023,1000,2000)));
}
