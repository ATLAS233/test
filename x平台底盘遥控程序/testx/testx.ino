//电机控制接口：左前 1号 40 41；右前 2号 42 43；右后 3号 44 45；左后 4号 46 47
          //PWM 1,9 2,10 3,11 4,12
//电机编码器：
//ps2 dat4 cmd5 cs6 clk7
#include <PS2X_lib.h>
PS2X ps2x;
int s;
int s1,s2,s3,s4;//处理后的摇杆数值
int v1,v2,v3,v4;//处理后每个轮子的速度
int V1,V2,V3,V4;//速度防溢出
int error = 0;
byte type = 0;
byte vibrate = 0;
int LX,LY;
int RX,RY;
void setup()
{
  Serial.begin(56700);
  delay(300);
  error = ps2x.config_gamepad(7,5,6,4,true,true);
  ps2x.read_gamepad(false,vibrate);
  type = ps2x.readType();
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop()
{
   if (error == 1)
        return;
     if (type == 2)
      {return;}
     
  else
  {
    ps2x.read_gamepad(false,vibrate);

    LY = (ps2x.Analog(PSS_LY)-127)*2;
    LX = (ps2x.Analog(PSS_LX)-127)*2;
    RX = (ps2x.Analog(PSS_RX)-127)*2;
    s1 = LY-LX+RX;
    s2 = LY+LX-RX;
    s3 = LY-LX-RX;
    s4 = LY+LX+RX-4;
    m1();
    m2();
    m3();
    m4();
    Serial.println(V1);
  }
}
void m1()
{
  if(s1 > 0)
  {
    v1=s1-1;
    V1=min(v1,255);
    digitalWrite(40,LOW);
    digitalWrite(41,HIGH);
    analogWrite(9,V1);
    delay(10);
  }
  if(s1 <=0)
  {
    v1=abs(s1);
    V1=min(v1,255);
    digitalWrite(40,HIGH);
    digitalWrite(41,LOW);
    analogWrite(9,V1);
    delay(10);
  }
}
void m2()
{
  if(s2 > 0)
  {
    v2=s2-1;
    V2=min(v2,255);
    digitalWrite(42,LOW);
    digitalWrite(43,HIGH);
    analogWrite(10,V2);
    delay(10);
  }
  if(s2 <=0)
  {
    v2=abs(s2);
    V2=min(v2,255);
    digitalWrite(42,HIGH);
    digitalWrite(43,LOW);
    analogWrite(10,V2);
    delay(10);
  }
}
void m3()
{
  if(s3 > 0)
  {
    v3=s3-1;
    V3=min(v3,255);
    digitalWrite(44,LOW);
    digitalWrite(45,HIGH);
    analogWrite(11,V3);
    delay(10);
  }
  if(s3 <=0)
  {
    v3=abs(s3);
    V3=min(v3,255);
    digitalWrite(44,HIGH);
    digitalWrite(45,LOW);
    analogWrite(11,V3);
    delay(10);
  }
}
void m4()
{
  if(s4 > 0)
  {
    v4=s4-1;
    V4=min(v4,255);
    digitalWrite(46,LOW);
    digitalWrite(47,HIGH);
    analogWrite(12,V4);
    delay(10);
  }
  if(s4 <=0)
  {
    v4=abs(s4);
    V4=min(v4,255);
    digitalWrite(46,HIGH);
    digitalWrite(47,LOW);
    analogWrite(12,V4);
    delay(10);
  }
}
