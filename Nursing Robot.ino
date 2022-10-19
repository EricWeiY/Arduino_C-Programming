
#include <Arduino.h>
#include "DFRobot_Heartrate.h"
#define GSMSerial Serial
#define heartratePin A1

int PIR_sensor = A5;    //指定PIR模拟端口 A5   
int val = 0;            //存储获取到的PIR数值
int status1 = 0;
int status2 = 0;
uint8_t rateValue;
String bloothResult="A";
//char startflag='';
char stopflag='B';
char parseflag=',';

int i=0;
//心率
DFRobot_Heartrate heartrate(DIGITAL_MODE); 


void SendMessage()
{
  GSMSerial.print("AT+CSCS=");  
  GSMSerial.print('"'); 
  GSMSerial.print("GSM");
  GSMSerial.print('"');
  GSMSerial.print("\r\n");

  delay(1000);
  GSMSerial.print("AT+CMGF=1\r\n");
  delay(1000);
      
  GSMSerial.print("AT+CMGS=");  
  GSMSerial.print('"'); 
  GSMSerial.print("15602336501");     //发送目标手机号在这里设置
  GSMSerial.print('"');
  GSMSerial.print("\r\n");
  delay(1000);
  GSMSerial.print("Emergency! Senior tripped!");      //短信内容
  delay(1000);
  GSMSerial.write(0x1A);      //发送操作
  delay(1000);
}

//< ANALOG_MODE or DIGITAL_MODE




void setup() {
  //一氧化碳
  pinMode (3,OUTPUT);
  pinMode (4,INPUT);
  //人体红外
  pinMode(PIR_sensor, INPUT);   //设置PIR模拟端口为输入模式  
  Serial.begin(9600);  
  
  //设置串口波特率为9600

  GSMSerial.begin(9600);  //设置通讯的波特率为9600
}

void co()
{
   int value;
  value=analogRead(0);
  Serial.println(value,DEC);
  delay(0);

  if(value > 250)
  {
    for(int i=0;i<30;i++)
    {
    digitalWrite(3,HIGH);
    delayMicroseconds(1800);
      digitalWrite(3,LOW);
    delayMicroseconds(1800);
    }
  }
  else
  {
    digitalWrite(3,LOW);
  }

  
}

void hongwai()
{
  delay(1000);
  val = analogRead(A5);    //读取A0口的电压值并赋值到val  
  //Serial.println(val);            //串口发送val值  
   if(val <150)
   {  
      if (status1 == 0||status1 == 1){
            status1 ++;
            SendMessage(); 
        }
   }   

}

void loop() 
{
   
  //一氧化碳
  if(analogRead(0)>250)
    {
      co();
    }
  //人体红外
  if(analogRead(A5)<150)
    {
      hongwai();
    }
   //心率
    
     heartrate.getValue(heartratePin); ///< A1 foot sampled values
     rateValue = heartrate.getRate(); ///< Get heart rate value 
     if(60<rateValue&&rateValue<90) 
        {
           
            bloothResult+=rateValue;
            bloothResult+=parseflag;
            i+=1;
      
            if(i==6)
            {
              bloothResult+=stopflag;
              Serial.println(bloothResult);
              bloothResult="A";
              i=0;
            }
        }
     
    

  
}

