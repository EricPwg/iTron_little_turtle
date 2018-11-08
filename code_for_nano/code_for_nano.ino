#include <string.h>
void setup() {
  // put your setup code here, to run once:
pinMode(A5,INPUT);
pinMode(A6,INPUT);
Serial.begin(9600);
}
//void getcontrol(char*);
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("s");
  Serial.print(analogRead(A5));
  Serial.print(" ");
  Serial.print("d");
  Serial.print(analogRead(A6));
  Serial.print(" ");
  delay(500);
}
/*
void getcontrol(char* control){
 char axis_x[]="";
 char axis_y[]="";
 strcat(axis_x,axis_y);
 strcpy(control,axis_x);
  }
  */
