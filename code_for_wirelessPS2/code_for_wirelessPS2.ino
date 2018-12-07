#include <PS2X_lib.h>
#include <Servo.h>

#ifndef PING_H
#define PING_H

//********** for the CAR RUN******************************** 

const int motor_LF[3]={31,30,2};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={38,39,3};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={33,32,5};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={34,35,6};  //(motor right back)  IN1 IN2 ENA  

//**********    for BONUS      ***************************** {
const int Servo_PPCT =7; //ping_pong collector
const int Servo_NOKR=10; //Knocker
const int laser = 13; //Knocker

Servo PPCT;
# define PPCT_init 120
# define PPCT_action 30
int PPCT_angle;

//**********    for Collector      ***************************** 

const int motor_CT[3]={37, 36};  //(motor collector  )  IN1 IN2 ENA  
const int Servo_PG= 9;       //Servo PLUG ? 
const int Servo_DG= 8;          //Servo Drag ???踹????撩?收??
const int Servo_PX = 11;          //??瑽???撩?收??

Servo PG;
# define PG_max 130
# define PG_init 117
# define PG_min 50
int PG_angle;

Servo PX;
# define PX_init 170
# define PX_action 105
int PX_angle;

Servo DG;
# define DG_init 140
# define DG_max 170
# define DG_min 100
int DG_angle;

Servo NOKR;
#define NOKR_init 175
#define NOKR_action 90
int NOKR_angle;

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
  pinMode(Servo_PX, OUTPUT);
  pinMode(laser, OUTPUT);
  //digitalWrite(laser, HIGH);
  
  //error = ps2x.config_gamepad(PS2_clk, PS2_cmd, PS2_att, PS2_data, true, true);
  error = ps2x.config_gamepad(true, true);
  int type = ps2x.readType();
  Serial.println(error);
  while (error != 0){
    delay(1000);
    //ps2x.reconfig_gamepad();
    delay(1000);
    //error = ps2x.config_gamepad(PS2_clk, PS2_cmd, PS2_att, PS2_data, true, true);
    error = ps2x.config_gamepad(true, true);
    Serial.println(error);
  }
  PPCT.attach(Servo_PPCT);
  PPCT.write(PPCT_init);
  PPCT_angle = PPCT_init;
  
  PG.attach(Servo_PG);
  PG.write(PG_init);
  PG_angle = PG_init;

  DG.attach(Servo_DG);
  DG.write(DG_init);
  DG_angle = DG_init;

  PX.attach(Servo_PX);
  PX.write(PX_init);
  PX_angle = PX_init;

  NOKR.attach(Servo_NOKR);
  NOKR.write(NOKR_init);
  NOKR_angle = NOKR_init;
  
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
  //Serial.print(ly);
  //Serial.print(" ");
  //Serial.print(rx);
  //Serial.println(" "); 
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
  
  //****PPCT
  if(ps2x.Button(PSB_R2)){ PPCT_angle -= 1; PG.write(PG_init); PG_angle = PG_init;}
  if(ps2x.Button(PSB_R1)){ PPCT_angle += 3; PG.write(PG_init); PG_angle = PG_init;}
  PPCT_angle = (PPCT_angle > PPCT_init) ? PPCT_init : (PPCT_angle < PPCT_action) ? PPCT_action : PPCT_angle;
  PPCT.write(PPCT_angle);

  //****PG
  if(ps2x.Button(PSB_RED)) PG_angle -= 1;
  if(ps2x.Button(PSB_PINK)) PG_angle += 1;
  PG_angle = (PG_angle > PG_max) ? PG_max : (PG_angle < PG_min) ? PG_min : PG_angle;
  PG.write(PG_angle);
  if(ps2x.Button(PSB_GREEN)) PX_angle -= 1;
  if(ps2x.Button(PSB_BLUE)) PX_angle += 1;
  PX_angle = (PX_angle > PX_init) ? PX_init : (PX_angle < PX_action) ? PX_action : PX_angle;
  PX.write(PX_angle);

  
  //**DG
  if(ps2x.Button(PSB_PAD_UP)) DG_angle -= 1;
  if(ps2x.Button(PSB_PAD_DOWN)) DG_angle += 1;
  DG_angle = (DG_angle > DG_max) ? DG_max : (DG_angle < DG_min) ? DG_min : DG_angle;
  DG.write(DG_angle);

  if(ps2x.Button(PSB_L1)) NOKR_angle -= 5;
  if(ps2x.Button(PSB_L2)) NOKR_angle += 1;
  NOKR_angle = (NOKR_angle > NOKR_init) ? NOKR_init : (NOKR_angle < NOKR_action) ? NOKR_action : NOKR_angle;
  NOKR.write(NOKR_angle);
  
  if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
    digitalWrite(motor_CT[0], 0);
    digitalWrite(motor_CT[1], 1);
    delay(20);
  }
  if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {
    digitalWrite(motor_CT[0], 1);
    digitalWrite(motor_CT[1], 0);
    delay(20);
  }
  digitalWrite(motor_CT[0], 0);
  digitalWrite(motor_CT[1], 0);
  delay(5);
}
