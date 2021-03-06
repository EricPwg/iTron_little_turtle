const int ENRB = 2 ; //left front
const int RBP = 40 ;//left front plus
const int RBN = 41;//left front nagative

const int ENRF =  3;//left back
const int RFP = 38;//left front plus
const int RFN = 39;//left front nagative

const int ENLB = 5;//right front
const int LBP  = 42;//left front plus
const int LBN  =43;//left front nagative

const int ENLF  =4;//right back
const int LFP  = 44;//left front plus
const int LFN =45;//left front nagative

bool Serial_3 =0;
int RF[3] = {0, 0, 0};
int RB[3] = {0, 0, 0};
int LF[3] = {0, 0, 0};
int LB[3] = {0, 0, 0};
int serial_state;
int RSpeed;
int LSpeed;
int Dir;
int speed_t;
int dir_t;
bool b;

void setup() {
  b = 0;
  digitalWrite(13, b);
  //Serial.begin(9600);
  //Serial.println("Setup");
  Serial3.begin(9600);
  serial_state = 0;
  RSpeed = 0;
  LSpeed = 0;
  speed_t = 0;
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(ENLF,OUTPUT);
  pinMode(LFP,OUTPUT);
  pinMode(LFN,OUTPUT);
  pinMode(ENRF,OUTPUT);
  pinMode(RFP,OUTPUT);
  pinMode(RFN,OUTPUT);
  pinMode(ENLB,OUTPUT);
  pinMode(LBP,OUTPUT);
  pinMode(LBN,OUTPUT);
  pinMode(ENRB,OUTPUT);
  pinMode(RBP,OUTPUT);
  pinMode(RBN,OUTPUT);
  
}

void set_speed(int s, int d){
  bool FB_flag = (s > 512) ? 1 : 0;
  int Sp = map(s, 0, 1023, -170, 170);
  Sp = (Sp >= 0) ? Sp : -Sp;
  int Trim = (d-512);
  Trim = (Trim < 100 && Trim > 100) ? 0 : Trim;
  Trim /=6;
  digitalWrite(LFP,FB_flag);
  digitalWrite(LFN,!FB_flag);
  analogWrite(ENLF,Sp+Trim-1);
  digitalWrite(RFP,FB_flag);
  digitalWrite(RFN,!FB_flag);
  analogWrite(ENRF,Sp-Trim-1);
  digitalWrite(LBP,FB_flag);
  digitalWrite(LBN,!FB_flag);
  analogWrite(ENLB,Sp+Trim-1);
  digitalWrite(RBP,FB_flag);
  digitalWrite(RBN,!FB_flag);
  analogWrite(ENRB,Sp-Trim-1);
  //Serial.print(Sp);
  //Serial.print(" ");
  //Serial.println(Trim);
}

void loop() {
  b = !b;
  digitalWrite(13, b);
  //Serial.print(Speed);
  //Serial.print(" ");
  //Serial.print(Dir);
  //Serial.print(" ");
  // put your main code here, to run repeatedly:
  char t;
  if (Serial3.available()){
    t = Serial3.read();
    switch(t){
      case 't': serial_state = -1; 
        digitalWrite(RFP,1);  digitalWrite(RFN,0);
        digitalWrite(RBP,1);  digitalWrite(RBN,0);
        break;
      case 'e': serial_state = -1; 
        digitalWrite(RFP,0);  digitalWrite(RFN,1);
        digitalWrite(RBP,0);  digitalWrite(RBN,1);
        break;
      case ';': serial_state = -1; 
        digitalWrite(LFP,1);  digitalWrite(LFN,0);
        digitalWrite(LBP,1);  digitalWrite(LBN,0);
        break;
      case 'k': serial_state = -1; 
        digitalWrite(LFP,0);  digitalWrite(LFN,1);
        digitalWrite(LBP,0);  digitalWrite(LBN,1);
        break;
      case 'r': serial_state = 1; break;
      case ' ': 
        if (serial_state == -1) break;
        else if (serial_state == 0){
          RSpeed = speed_t;
          speed_t = 0;
        }
        else if (serial_state == 1){
          LSpeed = speed_t;
          speed_t = 0;
        }
        break;
      default:
        speed_t = 10*speed_t + ((int)t-48);
    }
    analogWrite(ENLF,LSpeed);
    analogWrite(ENLB,LSpeed);
    analogWrite(ENRF,RSpeed);
    analogWrite(ENRB,RSpeed);
  }
  //delay(1000);
}
