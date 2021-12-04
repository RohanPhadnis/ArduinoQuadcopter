#include <Servo.h>

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

//int i, good, k;
//byte data_in;
void setup() {
  //attachInterrupt(digitalPinToInterrupt(3),data_incoming,RISING);
  //pinMode(3, INPUT);
  esc1.attach(6);
  esc2.attach(7);
  esc3.attach(8);
  esc4.attach(9);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i<255; i+=0) {
    esc_spin(i);
    Serial.println(i);
    delay(50);
  }
}





/*
void data_incoming() {
    
    
    for(i=0; i<100; i++){
      delayMicroseconds(20);
      good=1;
      if(digitalRead(3)==LOW){
      good=0;
      i=100;
      }
    }//for
      
    if(good==1){
    detachInterrupt(digitalPinToInterrupt(3));
    while(1){
      if(digitalRead(3)==LOW){
        delayMicroseconds(750);

        for(i=0; i<8; i++){
          if(digitalRead(3)==HIGH)
          bitWrite(data_in, i, 1);
          else
          bitWrite(data_in, i, 0);
          delayMicroseconds(1000);
        }//for
       break;//secondtwhile
      }//low kickoff
      
    }//second while
    
    }//good check 
  attachInterrupt(digitalPinToInterrupt(3),data_incoming,RISING);
  Serial.println((int)data_in);
  esc_spin((int)data_in);
}
*/

void esc_spin(int spd) {
  spd = map(spd,0,255,1000,2000);
  esc1.writeMicroseconds(spd);
  esc2.writeMicroseconds(spd);
  esc3.writeMicroseconds(spd);
  esc4.writeMicroseconds(spd);
}

//void land() {
  
//}
