int yaw;
int pitch;
int pot;
void setup(){
  pinMode(2, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}

void loop(){
  pot = map(analogRead(A0),0,1023,0,255);
  pitch = map(analogRead(A1),0,1023,0,31);
  yaw = map(analogRead(A2),0,1023,32,63);
  rf_send(pot);
  //rf_send(pitch);
  //rf_send(yaw);
}

void rf_send(int in){
  int i;
  byte input = byte(in);
  for(i=0; i<20; i++){
    digitalWrite(2, HIGH);
    delayMicroseconds(500);
    digitalWrite(2, LOW);
    delayMicroseconds(500);
  }

  digitalWrite(2, HIGH);
  delayMicroseconds(3000);
  digitalWrite(2, LOW);
  delayMicroseconds(500);
  
  
  for(i=0; i<8; i++){
    if(bitRead(input,i)==1) {
      digitalWrite(2, HIGH);
    } else {
    digitalWrite(2, LOW);
    }
    delayMicroseconds(500);
    
    if(bitRead(input,i)==1) {
      digitalWrite(2, LOW);
    } else {
    digitalWrite(2, HIGH);
    }
    delayMicroseconds(500);
  }//i

  
  digitalWrite(2, LOW);
}
