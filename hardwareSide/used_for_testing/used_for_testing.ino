#define INTERVAL_SENSOR   17000             //定义传感器采样时间间隔  597000
#define INTERVAL_NET      17000             //定义发送时间
//传感器部分================================   
#include <avr/sleep.h>
#include <avr/power.h>
#include <Wire.h>                                  //调用库  

#include "ESP8266.h"
                               //调用库  
//温湿度   
#include <SHT2x.h>
//光照
#define  sensorPin_1  A0
int i=0;

#define SSID           "HANDSOME"                   // cannot be longer than 32 characters!
#define PASSWORD       "281510"

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
                                  
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

//WEBSITE     
#define HOST_NAME   "api.heclouds.com"
#define DEVICEID   "9939133"
#define PROJECTID "91729"
#define HOST_PORT   (80)
String apiKey="VeFI0HZ44Qn5dZO14AuLbWSlSlI=";
char buf[10];

#define INTERVAL_sensor 2000
unsigned long sensorlastTime = millis();

float tempOLED, humiOLED, lightnessOLED;

#define INTERVAL_OLED 1000

String mCottenData;
String jsonToSend;

//3,传感器值的设置 
float sensor_tem, sensor_hum, sensor_lux;                    //传感器温度、湿度、光照   
char  sensor_tem_c[7], sensor_hum_c[7], sensor_lux_c[7] ;    //换成char数组传输
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
ESP8266 wifi(mySerial);
//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象
unsigned long net_time1 = millis();                          //数据上传服务器时间
unsigned long sensor_time = millis();                        //传感器采样时间计时器

//int SensorData;                                   //用于存储传感器数据
String postString;                                //用于存储发送数据的字符串
//String jsonToSend;                                //用于存储发送的json格式参数
void pin2Interrupt(void) {
    /* 中断唤醒 */
 
    /*当中断引脚为低电平时关闭中断*/
    Serial.println("wake up!!!");
    detachInterrupt(0);
  //((void(*)())0)();    //此句话为新加的！！！！！！
}
void setup(void)     //初始化函数  
{       
  //初始化串口波特率  
    Wire.begin();
    Serial.begin(115200);   
    while(!Serial);
    pinMode(sensorPin_1, INPUT);

   //ESP8266初始化
    Serial.print("setup begin\r\n");   

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {      //加入无线网
    Serial.print("Join AP success\r\n");  
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");
    
  
}
void loop(void)
{
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");
    i++;
    if(i>3){
      attachInterrupt(0, pin2Interrupt, LOW);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
      }
  if (wifi.releaseTCP()) {                                 //释放TCP连接
        Serial.print("release tcp ok\r\n");
        } 
     else {
        Serial.print("release tcp err\r\n");
        }
   } else {
    Serial.print("create tcp err\r\n");
    i++;
    if(i>3)
    {
       attachInterrupt(0, pin2Interrupt, LOW);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
      }
  }
  
  
  }
