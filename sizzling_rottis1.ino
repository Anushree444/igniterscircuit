#define ENCA1 2
#define ENCB1 12
#define PWM1 10
#define IN3 6
#define IN4 5

#define ENCA2 3
#define ENCB2 8
#define PWM2 9 
#define IN1 11
#define IN2 7

#define CURRENT1 A0
#define CURRENT2 A1


int pos1=0;
long prevT1 =0;
float eprev1 =0;
float eintegral1 =0;
 
int pos2=0;
long prevT2 =0;
float eprev2 =0;
float eintegral2 =0;

int target1 = 600;
int target2 = 500;

int prevPos1 = 0;
int prevPos2 = 0;

void setup(){
  pinMode(CURRENT1, INPUT);
  pinMode(CURRENT2, INPUT);
  
  pinMode(PWM1, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PWM2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

 Serial.begin(9600);
  pinMode(ENCA1,  INPUT_PULLUP);
  pinMode(ENCB1,  INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);

  pinMode(ENCA2,  INPUT_PULLUP);
  pinMode(ENCB2,  INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoder2, RISING);
}

void loop(){
  
  //PID CONTROLD
  float kp=1;
  float kd=0;
  float ki=0;
  
  //time diff
  long currT1=micros();
  long et1=currT1-prevT1;
  float deltaT1=((float)(currT1-prevT1))/1.0e6;
  prevT1=currT1;
  
  long currT2=micros();
  long et2=currT2-prevT2;
  float deltaT2=((float)(currT2-prevT2))/1.0e6;
  prevT2=currT2;
  
  //error
  int e1= target1-pos1;
  int e2= target2-pos2;
  
  //derivative
  float dedt1 = (e1-eprev1)/deltaT1;
  float dedt2 = (e2-eprev2)/deltaT2;
  //integral
  eintegral1= eintegral1+ e1*deltaT1;
  eintegral2= eintegral2+ e2*deltaT2;
  
  //control signal
  float u1= kp*e1 + kd*dedt1 + ki*eintegral1;
  float u2= kp*e2 + kd*dedt2 + ki*eintegral2;
  
  //motor power
  float pwr1 = fabs(u1);
  if(pwr1>255)pwr1=255;
  float pwr2 = fabs(u2);
  if(pwr2>255)pwr2=255;
  
  //motor direction
  int dir1=1;
  if(u1<0) dir1=-1;
  int dir2=1;
  if(u2<0) dir2=-1;
  
  //signal the motor
  setMotor(dir1,pwr1,PWM1,IN3,IN4);
  setMotor(dir2,pwr2,PWM2,IN1,IN2);
  
  //store prev error
  eprev1=e1;
  eprev2=e2;
  
  //speeds

  float speed1 = (pos1 - prevPos1) / deltaT1;
  float speed2 = (pos2 - prevPos2) / deltaT2;

  prevPos1 = pos1;
  prevPos2 = pos2;
  
  //current
  int raw1 = analogRead(CURRENT1);
  int raw2 = analogRead(CURRENT2);

  float voltage1 = (raw1 / 1023.0) * 5.0;
  float voltage2 = (raw2 / 1023.0) * 5.0;

  // Assume 0.1 ohm resistor:
  float current1 = voltage1 / 0.1; // in Amps
  float current2 = voltage2 / 0.1;


  Serial.print("Target1: ");
  Serial.print(target1);
  Serial.print(" Pos1: ");
  Serial.print(pos1);
  Serial.print(" Speed1: ");
  Serial.print(speed1);
  Serial.print(" Error1: ");
  Serial.print(e1);
  Serial.print("Current1: ");
  Serial.print(current1);
  
  Serial.print(" || Target2: ");
  Serial.print(target2);
  Serial.print(" Pos2: ");
  Serial.print(pos2);
  Serial.print(" Speed2: ");
  Serial.print(speed2);
  Serial.print(" Error2: ");
  Serial.println(e2);
  Serial.print(" A, Current2: ");
  Serial.print(current2);
  Serial.println(" A");

}

void setMotor(int dir, int pwmVal, int pwm, int in3, int in4){
analogWrite(pwm, pwmVal);
  if(dir==1){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
  else if(dir==-1){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
   else {
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }
}

void readEncoder1(){
 int b= digitalRead(ENCB1);
  if(b>0) pos1++;
  else pos1--;
}

void readEncoder2(){
 int b= digitalRead(ENCB2);
  if(b>0) pos2++;
  else pos2--;
}