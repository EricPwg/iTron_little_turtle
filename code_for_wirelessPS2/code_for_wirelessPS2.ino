#include <PS2X_lib.h>

#ifndef PING_H
#define PING_H

//********** for the CAR RUN******************************** 

const int motor_LF[3]={40,41,2};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={38,39,3};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={32,33,5};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={34,35,6};  //(motor right back)  IN1 IN2 ENA  

//**********    for BONUS      ***************************** {
const int Servo_PPCT =10; //ping_pong collector
const int Servo_NOKR=7; //Knocker
const int laser = 13; //Knocker

//**********    for Collector      ***************************** 

const int motor_CT[3]={42,43,4};  //(motor collector  )  IN1 IN2 ENA  
const int Servo_PG= 11;       //Servo PLUG ? 
const int Servo_DG= 8;          //Servo Drag ???踹????撩?收??
const int Servo_X = 9;          //??瑽???撩?收??


# define PS2_clk 22
# define PS2_cmd 23
# define PS2_att 24
# define PS2_data 25

#endif

int error;
PS2X ps2x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  for (int i = 0; i<3;i++) pinMode(motor_LF[i], OUTPUT);
  for (int i = 0; i<3;i++) pinMode(motor_LB[i], OUTPUT);
  for (int i = 0; i<3;i++) pinMode(motor_RF[i], OUTPUT);
  for (int i = 0; i<3;i++) pinMode(motor_RB[i], OUTPUT);
  for (int i = 0; i<3;i++) pinMode(motor_CT[i], OUTPUT);
  pinMode(Servo_PG, OUTPUT);
  pinMode(Servo_DG, OUTPUT);
  pinMode(Servo_X, OUTPUT);
  
  error = ps2x.config_gamepad(PS2_clk, PS2_cmd, PS2_att, PS2_data, true, true);
  int type = ps2x.readType();
  Serial.println(error);
  while (error != 0){
    delay(1000);
    //ps2x.reconfig_gamepad();
    delay(1000);
    error = ps2x.config_gamepad(PS2_clk, PS2_cmd, PS2_att, PS2_data, true, true);
    Serial.println(error);
  }
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

void loop() {
  ps2x.read_gamepad();

  byte ly = ps2x.Analog(PSS_LY);
  //byte ly = ps2x.Button(PSB_L2);
  byte rx = ps2x.Analog(PSS_RX);
  Serial.print(ly);
  Serial.print(" ");
  Serial.print(rx);
  Serial.println(" ");
  int lw = 0;
  int rw = 0;
  transfer_function(ly, rx, &lw, &rw);
  if (rw > 0){
    digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    analogWrite(motor_RF[2], rw);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    analogWrite(motor_RB[2], rw);
    //Serial.print("t"); //right wheel forward
    //Serial.print(" ");
    //Serial.print("r");
    //Serial.print(rw);
  } 
  else{
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    analogWrite(motor_RF[2], -rw);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    analogWrite(motor_RB[2], -rw);
    //Serial.print("e"); //right wheel backward
    //Serial.print(" ");
    //Serial.print("r");
    //Serial.print(-rw);
  } 
  //Serial.print(" ");
  
  if (lw > 0){
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    analogWrite(motor_LF[2], lw);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    analogWrite(motor_LB[2], lw);
    //Serial.print(";"); //left wheel forward
    //Serial.print(" ");
    //Serial.print("l");
    //Serial.print(lw);
  } 
  else{
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    analogWrite(motor_LF[2], -lw);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    analogWrite(motor_LB[2], -lw);
    //Serial.print("k"); //left wheel backward
    //Serial.print(" ");
    //Serial.print("l");
    //Serial.print(-lw);
  }
  //Serial.print(" ");
  //Serial.print("\n");
  delay(100);

}
