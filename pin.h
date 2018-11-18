#ifndef PING_H
#define PING_H

//********** for the CAR RUN******************************** 
{
const int[3] motor_LF=[40,41,2];  //(motor left  front) IN1 IN2 ENA 
const int[3] motor_LB=[38,39,3];  //(motor left  back)  IN1 IN2 ENA 
const int[3] motor_RF=[32,33,5];  //(motor right front) IN1 IN2 ENA 
const int[3] motor_RB=[34,35,6];  //(motor right back)  IN1 IN2 ENA  
}
//**********    for BONUS      ***************************** 
{
const int Servo_PPCT =10; //ping_pong collector
const int Servo_NOKR=7; //Knocker
const int laser = 13  ; //Knocker
}
//**********    for Collector      ***************************** 
{
const int [3] motor_CT=[42,43,4];	//(motor collector  )  IN1 IN2 ENA  
const int Servo_PG= 11;				//Servo PLUG 插銷 
const int Servo_DG= 8;					//Servo Drag 把上板往回拉的伺服馬達
const int Servo_X = 9;					//把機構往前推的伺服馬達
}



#endif