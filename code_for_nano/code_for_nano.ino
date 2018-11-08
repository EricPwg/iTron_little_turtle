#include <PS2X_lib.h>
#include <string.h>

PS2X ps2x;
int error = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  error = ps2x.config_gamepad(13,11,10,12, true, true);
  int type = ps2x.readType();
  Serial.println(type);
  if (error == 0) Serial.println("OK!!");
  else Serial.println("ERROR!!");
  delay(2000);
  
}

void transfer_function(byte l, byte r, int *lw, int *rw){
  int ly = (int)l;
  int rx = (int)r;
  int rotate = map(rx, 0, 255, -100, 100);
  int lwr = l-rotate;
  int rwr = l+rotate;
  lwr-=128;
  rwr-=128;
  lwr *= -2;
  rwr *= -2;
  *lw = (lwr > 255) ? 255 : (lwr < -255) ? -255 : lwr;
  *rw = (rwr > 255) ? 255 : (rwr < -255) ? -255 : rwr;
}

//void getcontrol(char*);
void loop() {
  ps2x.read_gamepad();
  // put your main code here, to run repeatedly:
  byte ly = ps2x.Analog(PSS_LY);
  //byte ly = ps2x.Button(PSB_L2);
  byte rx = ps2x.Analog(PSS_RX);
  //Serial.print(ly);
  //Serial.print(" ");
  //Serial.print(rx);
  //Serial.print(" ");
  int lw = 0;
  int rw = 0;
  transfer_function(ly, rx, &lw, &rw);
  if (rw > 0){
    Serial.print("t"); //right wheel forward
    Serial.print(" ");
    Serial.print("r");
    Serial.print(rw);
  } 
  else{
    Serial.print("e"); //right wheel backward
    Serial.print(" ");
    Serial.print("r");
    Serial.print(-rw);
  } 
  Serial.print(" ");
  
  if (lw > 0){
    Serial.print(";"); //left wheel forward
    Serial.print(" ");
    Serial.print("l");
    Serial.print(lw);
  } 
  else{
    Serial.print("k"); //left wheel backward
    Serial.print(" ");
    Serial.print("l");
    Serial.print(-lw);
  }
  Serial.print(" ");
  //Serial.print("\n");
  delay(100);
}
/*
void getcontrol(char* control){
 char axis_x[]="";
 char axis_y[]="";
 strcat(axis_x,axis_y);
 strcpy(control,axis_x);
  }
  */
