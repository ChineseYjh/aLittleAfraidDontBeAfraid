//#define INTERVAL_NET 1000
#include<Wire.h>
#include"./ESP8266.h"
//#define SSID "HANDSOME"
//#define PASSWORD "11281510"
//#define HOST_NAME   "api.heclouds.com"
//const String DEVICEID  = "20452006";
//#define PROJECTID "106284"
//#define HOST_PORT   (80)
//#define apiKey "I0eB3CJjGR9VhUTAhLrnww14TSE="
//#define INTERVAL_OLED 20
#include <SoftwareSerial.h>
SoftwareSerial mySerials(2, 3); /* RX:D3, TX:D2 这个多了个s注意！！！*/
ESP8266 wifi(mySerials);
//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象
//unsigned short  net_time1 =millis() ; //数据上传服务器时间
//#define  sensorPin_1  A0
//bool netInformation;//表示云端是否有信息
//#define bufferLength 55//收到的报文的最大长度
bool judge(void);
//void showInformation(void);
/*************************************************************************/
#include <U8glib.h>
//unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
//#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
//#define setFont_SS u8g.setFont(u8g_font_fub25n)
/************************************************************************/
#include <avr/sleep.h>
#include <avr/power.h>
#include <IRremote.h>
//#define RECV_PIN  10
//IRrecv irrecv(10);//RECV_PIN);
//decode_results results;
//#define goSleep 0x1FE48B7
//#define stopRefresh 0x1FE30CF
//#define Refresh 0x1FE30CF
#define turnDownVoice 0x1FEB04F
//#define toLeft 0x1FEE01F
//#define toRight 0x1FE906F
/*void Interrupt(void) {
    中断唤醒,当中断引脚为低电平时关闭中断
    Serial.println("wake up!!!");
    detachInterrupt(0);
}*/
/*
void enterSleep(void) {
    attachInterrupt(0, Interrupt, LOW);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}*/
bool recvCheck(void)
{
    IRrecv irrecv(10);//RECV_PIN);
    decode_results results;
    irrecv.enableIRIn(); // 启动红外解码
    if(irrecv.decode(&results))
        {
            if(results.value==turnDownVoice)//红外接受检测
         { //Serial.println("pause");   //串口输出 “pause”（暂停）
           //audio_pause();  //音频暂停工作while not declared
           return true;
          }else {
            return false;
            }
          }
  }
  
/***********************************************************************/
#include"./audio.h"
#define music_vol 20 //歌曲音量0~30
/**********************************************************************/
void setup(void)     //初始化函数  
{  
    Wire.begin();       
    Serial.begin(115200);   
    while(!Serial)
    /*{u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);//改动
          u8g.print("The Serial cannot begin!");//打印错误信息
      }while( u8g.nextPage() );};*/
    //pinMode(sensorPin_1, INPUT);//ESP8266初始化

   // Serial.print("setup begin\r\n");   
    u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);//改动
          u8g.print("Welcome to ");
          u8g.setPrintPos(4,39);
          u8g.print("Don't Be Afraid!");//打印欢迎信息
      }while( u8g.nextPage() );
  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());
  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
    /*u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("toStation+softapOk");
      }while( u8g.nextPage() );*/
  } else {
    Serial.print("to station + softap err...\r\n");
   /* u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print("toStation+softapErr...\r\n");
      }while( u8g.nextPage() );*/
      //for(;;);
  }

  if (wifi.joinAP("HANDSOME","11281510"/*SSID, PASSWORD*/)) {      //加入无线网
    Serial.print("Join AP success\r\n");  
  /*  u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("JoinAPsuccess");
      }while( u8g.nextPage() );
    Serial.print("IP: ");*/
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("JoinAPfailure\r\n");
    u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("Join AP failure\r\n");
      }while( u8g.nextPage() );
      for(;;);
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  /*  u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("single ok\r\n");
      }while( u8g.nextPage() );*/
  } else {
    Serial.print("single err\r\n");
  /*  u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("single err...\r\n");
      }while( u8g.nextPage() );
      for(;;);*/
  }
  pinMode(10/*RECV_PIN*/, INPUT);//初始化红外接收
 //   irrecv.enableIRIn(); // 启动红外解码
    /*Serial.println("Irrecv initialisation complete.");*/
    audio_init(DEVICE_TF,MODE_One_END,music_vol);    //初始化mp3模块
  Serial.print("setup end\r\n");
  u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print("setup end~~~\r\n");
      }while( u8g.nextPage() );
}

void loop(void)
{
 // if(irrecv.decode(&results))
  //{
  //  if(results.value==goSleep)
   // {
   //   Serial.println("Entering sleep");
      /*u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print("Entering sleep~\r\n");
      }while( u8g.nextPage() );*/
  //    u8g.firstPage();
  //    do {
  //        setFont_L;
 //         u8g.setPrintPos(4, 16);
 //         u8g.print("");
//      }while( u8g.nextPage() );
 //     enterSleep();
  //    }
 // }
 // if (net_time1 > millis()) { net_time1 = millis();}
//  else if (millis() - net_time1 > 1000/*INTERVAL_NET*/)                  //查看数据时间间隔
 // {                
    if (wifi.createTCP("api.heclouds.com",(80)/*HOST_NAME, HOST_PORT*/)) 
    { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");//将数据上传到服务器的函数
    if(judge())//用函数确定是否有信息
      {
         //netInformation=true;
         //showInformation();//展示信息//realized in function judge()
        // Serial.println("play");   //串口输出 “play”（工作
         audio_play();              //音频工作//放音乐
        /* if(irrecv.decode(&results))
          { if(results.value==turnDownVoice)//红外接受检测
         { //Serial.println("pause");   //串口输出 “pause”（暂停）
           audio_pause();  //音频暂停工作
          }
          irrecv.resume(); // 接收下一个值*/
          if(recvCheck())
          {
            audio_pause();
          }
          }
         
      
      /*else
      {
        netInformation=false;
      }*/
    if (wifi.releaseTCP()) {                                 //释放TCP连接
        Serial.print("release tcp ok\r\n");
        }
     else {
        Serial.print("release tcp err\r\n"); }
        }
        
   else {
    Serial.print("create tcp err\r\n");
   /* u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print("create tcp err...\r\n");
      }while( u8g.nextPage() );*/
  }
 // }
}//查看云端信息，若云端有信息，则屏幕更新位置信息，音乐放声（看红外接受）;若无，则睡眠

bool judge(void)
{
  String postarray=" GET /devices/20452006/datapoints?datastream_id=latitude,longitude,phoneNumber,ThisIsAWorkByChineseYjhsTeam&limit=1 HTTP/1.1\r\n";
 postarray+=" api-key: I0eB3CJjGR9VhUTAhLrnww14TSE=\r\n";
 postarray+=" Host:api.heclouds.com\r\n";
 postarray+=" Connection:close\r\n\r\n";
 Serial.println(postarray);
 const char*postChar=postarray.c_str();
 wifi.send((const uint8_t*)postChar, strlen(postChar));
String Data=mySerials.readString();
const char*data=Data.c_str();
Serial.println(data);
if((Data.indexOf("latitude")!=-1)&&(Data.indexOf("longitude")!=-1)&&(Data.indexOf("phoneNumber")!=-1)&&(Data.indexOf("ThisIsAWorkByChineseYjhsTeam")!=-1))
  {
    Data=Data.substring(Data.indexOf("latitude"),(Data.indexOf("ThisIsAWorkByChineseYjhsTeam")+30));
    data=Data.c_str();
    Serial.println(data);
    u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print((Data.substring(Data.indexOf("latitude"),Data.indexOf("longitude"))).c_str());
          u8g.setPrintPos(4,28);
          u8g.print((Data.substring(Data.indexOf("longitude"),Data.indexOf("phoneNumber"))).c_str());
          u8g.setPrintPos(4,40);
          u8g.print((Data.substring(Data.indexOf("phonenumber"),Data.indexOf("ThisIsAWorkByChineseYjhsTeam"))).c_str());
      }while( u8g.nextPage() );
    return true;
    }
 else
 {return false;}

  }
