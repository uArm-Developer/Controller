#include <U8glib.h>
#include <FlexiTimer2.h>
#include <stdio.h>
/************************* LCD io *************************/
#define LCD_CS          42
#define LCD_RES         43
#define LCD_CD          44
#define LCD_SCK         8
#define LCD_MOSI        53
U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);  // SW SPI Com: SCK = 52, MOSI = 51, CS = 42, CD = 44
/************************* button io *************************/
#define BUTTON_A        47
#define BUTTON_B        49
#define BUTTON_C        12
#define BUTTON_D        11
/*************************  joystick   *************************/
#define JOY_UP     33
#define JOY_DOWN    41
#define JOY_LEFT    32
#define JOY_RIGHT   37
#define JOY_CENTRE  40
/*************************  joystick   *************************/
#define VOLUME      15


struct uarm_param_t{
  float x;
  float y;
  float z;
  uint8_t speed;
  uint8_t interval;
} uarm_param;

void setup() {
  // put your setup code here, to run once:
  char cmd[50], x_str[20], y_str[20], z_str[20];
  Serial.begin(115200);
  Serial2.begin(115200);
//  Serial2.write( "G0 X200 Y0 Z150 F130\r\n" );
  
  pinMode(LCD_RES, OUTPUT);
  digitalWrite(LCD_RES, HIGH);

  pinMode(JOY_UP, INPUT_PULLUP);
  pinMode(JOY_DOWN, INPUT_PULLUP);
  pinMode(JOY_LEFT, INPUT_PULLUP);
  pinMode(JOY_RIGHT, INPUT_PULLUP);
  pinMode(JOY_CENTRE, INPUT_PULLUP);
  pinMode(BUTTON_C,INPUT_PULLUP);
  pinMode(BUTTON_D,INPUT_PULLUP);

  uarm_param.x = 200.0;
  uarm_param.y = 0.0;
  uarm_param.z = analogRead(VOLUME) * 300.0 / 1023 - 100;
  if( uarm_param.z > 170 ){
    uarm_param.z = 170;
  }else if( uarm_param.z < -100 ){
    uarm_param.z = -100;
  }
  uarm_param.interval = 10;
  uarm_param.speed = 50;

  dtostrf(uarm_param.x,3,1,x_str);
  dtostrf(uarm_param.y,3,1,y_str);
  dtostrf(uarm_param.z,3,1,z_str);

  sprintf(cmd, "G1 X%s Y%s Z%s F%d\r\n", x_str, y_str, z_str, uarm_param.speed);
  Serial2.write(cmd); 
}

void loop() {
  // put your main code here, to run repeatedly:
    move();
    if( digitalRead(BUTTON_C) == LOW ){ 
      delay(50);
      if( digitalRead(BUTTON_C) == LOW ){
        while(digitalRead(BUTTON_C) == LOW);
        static bool mode_flag = false;
        if( mode_flag ){
          mode_flag = false;
          uarm_param.interval = 1;
          uarm_param.speed = 5;
        }else{
          mode_flag = true;
          uarm_param.interval = 10;
          uarm_param.speed = 50;
        }
      } 
    }       

}

void move(void){
  static char cmd[50], x_str[20], y_str[20], z_str[20];
  static bool init_flag = false;
  static float high = uarm_param.z;
  
  if( !init_flag ){
    init_flag = true;
    dtostrf(uarm_param.x,3,1,x_str);
    dtostrf(uarm_param.y,3,1,y_str);
    dtostrf(uarm_param.z,3,1,z_str);
  }
  
  uarm_param.z = analogRead(VOLUME) * 300.0 / 1023 - 100;
  if( uarm_param.z > 170 ){
    uarm_param.z = 170;
  }else if( uarm_param.z < -100 ){
    uarm_param.z = -100;
  }
  if( abs(high-uarm_param.z) > 1 ){
    dtostrf(uarm_param.z,3,1,z_str);
    sprintf(cmd, "G1 Z%s F%d\r\n", z_str, uarm_param.speed); 
    Serial2.write(cmd);
    delay(1);
    high = uarm_param.z;
  }
 
  if( digitalRead(JOY_UP) == LOW ){   
    uarm_param.x += uarm_param.interval;
    dtostrf(uarm_param.x,3,1,x_str);
    sprintf(cmd, "G1 X%s F%d\r\n", x_str, uarm_param.speed); 
    Serial2.write(cmd);
    delay(1);
  }
  if( digitalRead(JOY_DOWN) == LOW ){     
    uarm_param.x -= uarm_param.interval;
    dtostrf(uarm_param.x,3,1,x_str);
    sprintf(cmd, "G1 X%s F%d\r\n", x_str, uarm_param.speed);
    Serial2.write(cmd); 
    delay(1);
  }
  if( digitalRead(JOY_LEFT) == LOW ){     
    uarm_param.y += uarm_param.interval;
    dtostrf(uarm_param.y,3,1,y_str);
    sprintf(cmd, "G1 Y%s F%d\r\n", y_str, uarm_param.speed); 
    Serial2.write(cmd);
    delay(1);
  }
  if( digitalRead(JOY_RIGHT) == LOW ){    
    uarm_param.y -= uarm_param.interval;
    dtostrf(uarm_param.y,3,1,y_str);
    sprintf(cmd, "G1 Y%s F%d\r\n", y_str, uarm_param.speed); 
    Serial2.write(cmd); 
    delay(1);
  }
  if( digitalRead(BUTTON_D) == LOW ){
    delay(50);
    if( digitalRead(BUTTON_D) == LOW ){
      while(digitalRead(BUTTON_D) == LOW);
      static bool pump_sw = false;
      if( pump_sw ){
        pump_sw = false;
        Serial2.write("M2231 V0\r\n");
        delay(1);
      }else{
        pump_sw = true;
        Serial2.write("M2231 V1\r\n");
        delay(1);
      }
    }
  }
  
  u8g.firstPage();
  do{   
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(20, 15, "UF Control ");
    u8g.setFont(u8g_font_profont10);
    u8g.drawStr(5, 30, "speed:" );
    u8g.setPrintPos(80,30);
    u8g.print(uarm_param.speed);  
    u8g.drawStr(5, 45, "interval:" );
    u8g.setPrintPos(80,45);
    u8g.print(uarm_param.interval);    
    char dispaly_str[50];
    sprintf(dispaly_str, "X:%s Y:%s Z:%s", x_str, y_str, z_str);
    u8g.drawStr(5, 60, dispaly_str);
  }while(u8g.nextPage());      
}
