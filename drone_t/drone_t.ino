#include <RH_ASK.h>
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

char *msg;
String output;

boolean mode = true;
int old_val;
int new_val;

int throt = 1000;
int yaw = 5;
int pitch = 5;

void setup() {
    // Initialize ASK Object
    rf_driver.init();
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(8,INPUT);
    pinMode(13,OUTPUT);
}

void loop() {
  old_val = new_val;
  new_val = digitalRead(8);
  if (old_val == 0 && new_val == 1) {
    if (mode) {
      mode = false;
    } else {
      mode = true;
    }
  }
  if (mode) {
    digitalWrite(13,HIGH);
    throt = map(analogRead(A1),0,1023,1000,2000);
  } else {
    digitalWrite(13,LOW);
    pitch = map(analogRead(A1),0,1023,1,9);
  }
  yaw = map(analogRead(A0),0,1023,1,9);
  output = String(throt)+String(yaw)+String(pitch);
  msg = output.c_str();
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
}
