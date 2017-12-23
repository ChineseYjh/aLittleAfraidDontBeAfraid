
#define music_num_MAX 9        //歌曲最大数，可改

#include <SoftwareSerial.h>
//用户自定义部分------------------------

#include <Wire.h>

//EEPROM---------------------
#include <EEPROM.h>
#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}

struct config_type
{
  int EEPROM_music_num;       //歌曲的数目
  int EEPROM_music_vol;       //歌曲的音量
};

//用户自定义部分------------------------
#include "audio.h"   //"arduino.h"是控制音频文件

//#include "U8glib.h"
//-------字体设置，大、中、小
//#define setFont_L u8g.setFont(u8g_font_7x13)
//#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
//#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
/*
font:
 u8g_font_7x13
 u8g_font_fixed_v0r
 u8g_font_chikitar
 u8g_font_osb21
 u8g_font_courB14r
 u8g_font_courB24n
 u8g_font_9x18Br
 */

//屏幕类型--------
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define init_draw 500  //主界面刷新时间
unsigned long timer_draw;

int MENU_FONT = 1;  //初始化字体大小 0：小，1：中，2：大

boolean music_status = false; //歌曲播放状态
int music_num = 1;    //歌曲序号
int music_vol=20;               //音量0~30


boolean key,key_cache;          //定义mp3的开关

unsigned long music_vol_time_cache=0;     
unsigned long music_vol_time=0;           
boolean music_vol_sta=false;              

#include <avr/sleep.h>
#include <avr/power.h>
#include <IRremote.h>
#include <U8glib.h>
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define INTERVAL_LCD            20             //定义OLED刷新时间间隔  
unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
 #define music_vol 20 //歌曲音量0~30
int pin2 = 2;
//long previousMillis = 0;        // 存储LED最后一次的更新
long interval = 5000;           // 闪烁的时间间隔（毫秒）
//unsigned long currentMillis=0;

/***************************************************
 *  Name:        pin2Interrupt
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Service routine for pin2 interrupt    
 ***************************************************/
void pin2Interrupt(void) {
    /* 中断唤醒 */
 
    /*当中断引脚为低电平时关闭中断*/
    Serial.println("wake up!!!");
    detachInterrupt(0);
 // ((void(*)())0)();    //此句话为新加的！！！！！！
}
 
/***************************************************
 *  Name:        enterSleep
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Enters the arduino into sleep mode.
 ***************************************************/
void enterSleep(void) {
     Serial.println("Entering sleep");
    attachInterrupt(0, pin2Interrupt, CHANGE);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}
 
/***************************************************
 *  Name:        setup
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Setup for the Arduino.           
 ***************************************************/
void setup() {
    Serial.begin(9600);
    /* Setup the pin direction. */
    pinMode(pin2, INPUT);
    irrecv.enableIRIn(); // 启动红外解码
    Serial.println("Initialisation complete.");
     audio_init(DEVICE_TF,MODE_One_END,music_vol); 
}
 
/***************************************************
 *  Name:        loop
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Main application loop.
 ***************************************************/
void loop() {
 // previosMillis=millis();
   // currentMillis = millis();
   // Serial.print("Awake for ");
   // Serial.print(currentMillis - previousMillis, DEC);
   // Serial.println(" second");
    //delay(1000);
     u8g.firstPage();
      do {
          setFont_S;
          u8g.setPrintPos(4, 16);
          u8g.print("latitude:40.15747");
          u8g.setPrintPos(4,28);
          u8g.print("longitude:116.28637");
          u8g.setPrintPos(4,40);
          u8g.print("phoneNumber:");
          u8g.setPrintPos(4,52);
          u8g.print("15101072086");
      }while( u8g.nextPage() );
      audio_play();
      
      if(irrecv.decode(&results))
      {
         if(results.value==0x1FEB04F)
         {
          audio_pause();
          }
          if(results.value==0x1FE48B7)
          {
            enterSleep();
            }
        irrecv.resume(); // 接收下一个值
      }
     // while(1)
     // {
       // if（millis()>previousMillis+15000)break;
    //  }
    //  }
     // previousMillis = currentMillis;
}
//显示函数 
//void volcd() {
//  u8g.firstPage();
//  do {
//      setFont_L;
//      u8g.setPrintPos(4, 16);
//      u8g.setPrint(ss);
//  }
//  while( u8g.nextPage() );
//}


