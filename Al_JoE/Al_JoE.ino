#include <Servo.h> //라이브러리 불러오기
#include <Battery.h>
#include <AFMotor.h>

#define TRIG 7 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 6 //ECHO 핀 설정 (초음파 받는 핀)

Battery battery(5045, 11100, A3);

AF_DCMotor motor_R(2);
AF_DCMotor motor_L(4);

int fo,tu,bk = 0;

Servo bldc_left, bldc_right, bldc_stop; //모터 선언

float sensorValue_front, sensorValue_left, sensorValue_right;
float sensitivity = 0.1;
float filter_front, filter_left, filter_right= 0;

int cm_front, cm_left, cm_right;
int i = 0;

int bldc_1, bldc_2 = 0;

unsigned long fir_time;
unsigned long sec_time;

long duration, sonic;


void setup() {
  Serial.begin(9600);
  while (!Serial);
  //battery.begin(4100, 2.7);
  
  //delay(4000);
  
  sensorValue_front = analogRead(A0);
  sensorValue_left = analogRead(A1);
  sensorValue_right = analogRead(A2);
  
  //bldc_left.attach(8,1000,2000);         // bldc 1번 모터
  //bldc_right.attach(9,1000,2000);
  //bldc_stop.attach(7,1000,2000);

  pinMode(10, OUTPUT);
  
  //Serial.setTimeout(50);
  
  //bldc_left.write(0);
  //bldc_right.write(0);
  
  digitalWrite(10, HIGH);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  motor_R.setSpeed(230);
  motor_L.setSpeed(240);
  
  motor_R.run(RELEASE);
  motor_L.run(RELEASE);

  delay(2000);
}

void loop() {
  fir_time = millis();
  move_AlJoe();
}

void Sensor_val_front()
{
  sensorValue_front = analogRead(A0);
  filter_front = filter_front * (1 - sensitivity) + sensorValue_front * sensitivity;
  cm_front = 10650.08 * pow(filter_front,-0.935) - 10;          //전방 적외선 cm 변환
}

void Sensor_val_left()
{
  sensorValue_left = analogRead(A1);
  filter_left = filter_left * (1 - sensitivity) + sensorValue_left * sensitivity;
  cm_left = 10650.08 * pow(filter_left,-0.935) - 10;            //왼쪽 적외선 cm 변환
}

void Sensor_val_right()
{
  sensorValue_right = analogRead(A2);
  filter_right = filter_right * (1 - sensitivity) + sensorValue_right * sensitivity;
  cm_right = 10650.08 * pow(filter_right,-0.935) - 10;          //오른쪽 적외선 cm 변환
}

void move_AlJoe()
{
  Sensor_val_front();
  Sensor_val_left();
  Sensor_val_right();
  //Sonic();
 /*
  Serial.print(cm_front);
  Serial.print("   ");
  Serial.print(cm_left);
  Serial.print("   ");
  Serial.println(cm_right);*/
  //cm_front = 70;
  if(cm_front >= 80 && cm_left >= 80 && cm_right >= 80 /*&& sonic >= 20*/)      //60cm 안에 장애물이 감지가 안됬을 경우 직진
  {
    sec_time = fir_time;
    //모터는 최소 45, 최대 180값을 받을 수 있습니다. 적어도 이 코드 안에서는
    //ms();

   if(fo == 0)
       delay(1000);

    fo = 1;
    tu = 0;
    bk = 0;
   
    motor_R.run(RELEASE);
    motor_L.run(RELEASE);
    front_move();
    //delay(1000);
  }

  else if(cm_front < 80 && cm_left > cm_front && cm_right > cm_front)              //장애물이 감지되었을 경우
  {

    if(bk == 0)
      delay(1000);
    bk = 1;
    fo = 0;
    tu = 0;

    motor_R.run(RELEASE);
    motor_L.run(RELEASE);
    back_move();
  
    /*
    sec_time = fir_time;
   
   // ms();
    motor_R.run(RELEASE);
    motor_L.run(RELEASE);
    
    Discrimination();                 //좌우 장애물의 상태를 판별하는 함수 
    */
  }

  else if(cm_front > cm_left && cm_left < 80 && cm_right > cm_left)
  {
    if(tu == 0 || tu == 2)
       delay(1000);
    
    fo = 0;
    tu = 1;
    bk = 0;
    left_move();
  }
  
   else if(cm_front > cm_right && cm_left > cm_right && cm_right < 80)
   {
       if(tu == 0 || tu == 1)
       delay(1000);

    fo = 0;
    tu = 2;
    bk = 0;
    right_move();
  }
 }
/*
  else if(sonic < 20)
  {
    if(bk == 0)
      delay(1000);
    bk = 1;
    fo = 0;
    tu = 0;

    motor_R.run(RELEASE);
    motor_L.run(RELEASE);
    back_move();
  }
}
*/
void back_move()
{
  while(1)
  {
    Serial.print("후진");
    Serial.println("  ");
    //Serial.println(sonic);
    Sensor_val_front();
    Sensor_val_left();
    Sensor_val_right();
    //Sonic();
    
    motor_R.run(FORWARD);
    motor_L.run(BACKWARD);
    //mf();
    
    if(cm_front >= 80) break;
    if(cm_left < cm_front) break;
    if(cm_right < cm_front) break;
  }
    motor_R.run(RELEASE);
    motor_L.run(RELEASE);
}

void front_move()
{
  while(1)
  {
    Serial.print("전진");
    Serial.println("  ");
    //Serial.println(sonic);
    Sensor_val_front();
    Sensor_val_left();
    Sensor_val_right();
  
    motor_R.run(BACKWARD);
    motor_L.run(FORWARD);
    //mf();
    
    if(cm_front < 80) break;
    if(cm_left < 80) break;
    if(cm_right < 80) break;
  }
 // ms();
  
  motor_R.run(RELEASE);
  motor_L.run(RELEASE);
  //stop_motion();
}

void left_move()
{
  while(1)
  {
    Sensor_val_front();
    Sensor_val_left();
    Sensor_val_right();
    
    //Sonic();
    
    Serial.print("죄회전  ");
    Serial.print(cm_left);
    Serial.print("  ");
    Serial.println(cm_right);
    
    motor_R.run(FORWARD);
    motor_L.run(FORWARD);
    //mf();
    
    //if(sonic < 20) break;
    if(cm_left > cm_right) break;
    if(cm_left > 150) break;
    //if(cm_front > 50) break;
  }
  //ms();

   motor_R.run(RELEASE);
   motor_L.run(RELEASE);
  //stop_motion();
}

void right_move()
{
  sec_time = fir_time;

  while(1)
  {
    Sensor_val_front();
    Sensor_val_left();
    Sensor_val_right();
    //Sonic();
    
    Serial.print("우회전");
    Serial.print(cm_left);
    Serial.print("  ");
    Serial.println(cm_right);
    motor_R.run(BACKWARD);
    motor_L.run(BACKWARD);
    //mf();

    //if(cm_left > 60) break;
    if(cm_right > cm_left) break;
    if(cm_right > 150) break;
  }


  motor_R.run(RELEASE);
  motor_L.run(RELEASE);
  //ms();
  //stop_motion();
}

void Discrimination()
{
  Sensor_val_left();
  Sensor_val_right();
  
  if(cm_left > 100 && cm_right > 100)     //이곳은 영상처리 기반 방향전환 조건문입니다.
  {
    //ms();
    motor_R.run(BRAKE);
    motor_L.run(BRAKE);
  }
  
  else if(cm_left > cm_right)          //왼쪽에 장애물이 없을 경우 뱡향 왼쪽으로 전환
  {
    if(tu == 0 || tu == 2)
       delay(1000);
    
    fo = 0;
    tu = 1;
    bk = 0;
    left_move();
  }

  else if(cm_left < cm_right)     //오른쪽에 장애물이 없을 경우 방향 왼쪽으로 전환
  {
    if(tu == 0 || tu == 1)
       delay(1000);

    fo = 0;
    tu = 2;
    bk = 0;
    right_move();
  }
}

void ms()
{
    for (i=170; i!=150; i--) {
      Serial.println("감속");
      motor_R.setSpeed(i);
      motor_L.setSpeed(i);  
      delay(10);
    }
}

void mf()
{
    for (i=150; i<170; i++) {
      Serial.println("증가");
      motor_R.setSpeed(i);
      motor_L.setSpeed(i);  
      delay(10);
   }
}

void Sonic()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH);
  sonic = duration * 17 / 1000; 

  if(sonic > 20)
    sonic = 20;
  
 // Serial.print(sonic); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  //Serial.println(" Cm");
}
