//电机控制接口：左前 1号 40 41；右前 2号 42 43；右后 3号 44 45；左后 4号 46 47
          //PWM 1,9 2,10 3,11 4,12
//电机编码器：
//ps2 dat4 cmd5 cs6 clk7
#include <PS2X_lib.h>
PS2X ps2x;
int s;
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

    if(ps2x.Analog(PSS_LY)<127)//前进
    {
      LY = ps2x.Analog(PSS_LY);
      s = 255-(2*LY);
      analogWrite(9,s);
      analogWrite(10,s);
      analogWrite(11,s);
      analogWrite(12,s);
      go_forward();
    }
    vibrate = ps2x.Analog(PSAB_BLUE);
     if(ps2x.Analog(PSS_LY)>127)//后退
    {
      LY = ps2x.Analog(PSS_LY);
      s = (LY-128)*2;
      Serial.println(s);
      analogWrite(9,s);
      analogWrite(10,s);
      analogWrite(11,s);
      analogWrite(12,s);
      go_back();
    }
    vibrate = ps2x.Analog(PSAB_BLUE);
     if(ps2x.Analog(PSS_RX)<127)//右摇杆控制左转
    {
      RX = ps2x.Analog(PSS_RX);
      s = 255-(2*RX);
      analogWrite(9,s);
      analogWrite(10,s);
      analogWrite(11,s);
      analogWrite(12,s);
      go_left();
    }
    vibrate = ps2x.Analog(PSAB_BLUE);
     if(ps2x.Analog(PSS_RX)>127)//右摇杆控制右转
    {
      RX = ps2x.Analog(PSS_RX);
      s = (RX-128)*2;
      analogWrite(9,s);
      analogWrite(10,s);
      analogWrite(11,s);
      analogWrite(12,s);
      go_right();
    }
    vibrate = ps2x.Analog(PSAB_BLUE);
  }
}
void go_forward()
{
  digitalWrite(40,HIGH);
  digitalWrite(41,LOW);
  digitalWrite(42,HIGH);
  digitalWrite(43,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(45,LOW);
  digitalWrite(46,HIGH);
  digitalWrite(47,LOW);
  delay(10);
}
void go_left()
{
  digitalWrite(40,LOW);
  digitalWrite(41,HIGH);
  digitalWrite(42,HIGH);
  digitalWrite(43,LOW);
  digitalWrite(44,HIGH);
  digitalWrite(45,LOW);
  digitalWrite(46,LOW);
  digitalWrite(47,HIGH);
  delay(10);
}
void go_right()
{
  digitalWrite(40,HIGH);
  digitalWrite(41,LOW);
  digitalWrite(42,LOW);
  digitalWrite(43,HIGH);
  digitalWrite(44,LOW);
  digitalWrite(45,HIGH);
  digitalWrite(46,HIGH);
  digitalWrite(47,LOW);
  delay(10);
}
void go_back()
{
  digitalWrite(40,LOW);
  digitalWrite(41,HIGH);
  digitalWrite(42,LOW);
  digitalWrite(43,HIGH);
  digitalWrite(44,LOW);
  digitalWrite(45,HIGH);
  digitalWrite(46,LOW);
  digitalWrite(47,HIGH);
  delay(10);
}
