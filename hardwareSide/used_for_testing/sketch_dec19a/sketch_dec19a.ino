

#include <avr/sleep.h>
#include <avr/power.h>
#include <IRremote.h>
#include <U8glib.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define INTERVAL_LCD             20             //定义OLED刷新时间间隔  
unsigned long lcd_time = millis();                 //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);     //设置OLED型号  
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)
 
int pin2 = 2;
 
long previousMillis = 0;        // 存储LED最后一次的更新
long interval = 5000;           // 闪烁的时间间隔（毫秒）
unsigned long currentMillis=0;

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
  //((void(*)())0)();    //此句话为新加的！！！！！！
}
 
/***************************************************
 *  Name:        enterSleep
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Enters the arduino into sleep mode.
 ***************************************************/
void enterSleep(void) {

    attachInterrupt(0, pin2Interrupt, LOW);
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
}
 
/***************************************************
 *  Name:        loop
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Main application loop.
 ***************************************************/
void loop() {
    currentMillis = millis();
    Serial.print("Awake for ");
    Serial.print(currentMillis - previousMillis, DEC);
    Serial.println(" second");
    delay(1000);

    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      if(results.value==0x1FE48B7)
      {
        u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print("");
      }while( u8g.nextPage() );
        }else
      {
      u8g.firstPage();
      do {
          setFont_L;
          u8g.setPrintPos(4, 16);
          u8g.print(results.value,HEX);
      }while( u8g.nextPage() );}
      
      irrecv.resume(); // 接收下一个值
      previousMillis = currentMillis;
    }

    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis; 
      Serial.println("Entering sleep");
      enterSleep();
    }
  if(currentMillis<previousMillis)
    previousMillis=currentMillis=0;
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




