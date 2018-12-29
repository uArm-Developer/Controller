#include <U8glib.h>
#include <stdio.h>

#include "coord_convert.h"

/************************* LCD io *************************/
#define LCD_CS          42
#define LCD_RES         43
#define LCD_CD          44
#define LCD_SCK         30 
#define LCD_MOSI        35

U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);
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
  
  pinMode(LCD_RES, OUTPUT);
  digitalWrite(LCD_RES, HIGH);

  pinMode(JOY_UP, INPUT_PULLUP);
  pinMode(JOY_DOWN, INPUT_PULLUP);
  pinMode(JOY_LEFT, INPUT_PULLUP);
  pinMode(JOY_RIGHT, INPUT_PULLUP);
  pinMode(JOY_CENTRE, INPUT_PULLUP);
  pinMode(BUTTON_C,INPUT_PULLUP);
  pinMode(BUTTON_D,INPUT_PULLUP);

  if( check_firmware() == false ){
    u8g.firstPage();                                        // oled display
    do{   
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr(35, 15, "ERROR ");
      u8g.setFont(u8g_font_profont10);
      u8g.drawStr(0, 35, "1.Check uArmPro firmware!");
      u8g.drawStr(0, 45, "Upgrade to V4.3.0 or later!");
      u8g.drawStr(0, 55, "2.Check wire and connecter");
    }while(u8g.nextPage());     
    while(1);
  }
  
  uarm_param.x = 200.0;
  uarm_param.y = 0.0;
  uarm_param.z = analogRead(VOLUME) * 300.0 / 1023 - 100;     // get the high
  if( uarm_param.z > 170 ){
    uarm_param.z = 170;
  }else if( uarm_param.z < -100 ){
    uarm_param.z = -100;
  }
  uarm_param.interval = 10;
  uarm_param.speed = 50;

  dtostrf(uarm_param.x,3,1,x_str);                      // float value to str
  dtostrf(uarm_param.y,3,1,y_str);
  dtostrf(uarm_param.z,3,1,z_str);
  Serial2.write("M2400 S0\r\n");
  delay(500);
  sprintf(cmd, "G1 X%s Y%s Z%s F%d\r\n", x_str, y_str, z_str, uarm_param.speed);  // fill the cmd
  Serial2.write(cmd);                                                            // set the start position
  delay(500);
  Serial2.write("G2202 N3 V180 F30");                                           // set the end-effecter start angle
}

void loop() {
  // put your main code here, to run repeatedly:
    move();
    if( digitalRead(BUTTON_C) == LOW ){       // chage the speed
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

bool check_firmware(void){
#define FIRMWARE_VER   "ok V4"   

enum check_e{
  SEND_CMD = 0,
  RECV_RESULT,
  PRASE_RESULT,
} state = SEND_CMD;

  Serial.println( "check firmware" );
  String comdata = "";
  String temp_str = "";
  int check_cnt = 0;
  while(1){
    switch( state ){
      case SEND_CMD:
            Serial2.write("P2203\r\n");
            delay(2);
      case RECV_RESULT:
            while( Serial2.available() > 0 ){
              comdata += char(Serial2.read());
              delay(2);
            }
      case PRASE_RESULT:
          temp_str = comdata.substring(0,5);
          if( temp_str == "ok V4" ){
            Serial.println( "check ok" );
            return true;
          }else{
            
            if( check_cnt++ > 5 ){
              Serial.println( "check fail" );
              return false; 
            }
            Serial.println(check_cnt);
            Serial.print( comdata );
          }
          comdata = "";
        break;
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
  
  uarm_param.z = analogRead(VOLUME) * 300.0 / 1023 - 100;     // get the z aixs value
  if( uarm_param.z > 170 ){
    uarm_param.z = 170;
  }else if( uarm_param.z < -100 ){
    uarm_param.z = -100;
  }
  if( abs(high-uarm_param.z) > 1 ){         // if the z value changed 
    if( ckeck_coord(uarm_param.x, uarm_param.y, uarm_param.z) == false ){ return; }
    dtostrf(uarm_param.z,3,1,z_str);
    sprintf(cmd, "G1 Z%s F%d\r\n", z_str, uarm_param.speed);  //set the z value
    Serial2.write(cmd);
    delay(1);
    high = uarm_param.z;
  }
 
  if( digitalRead(JOY_UP) == LOW ){  
    uarm_param.x += uarm_param.interval;
    if( ckeck_coord(uarm_param.x, uarm_param.y, uarm_param.z) == false ){ 
      uarm_param.x -= uarm_param.interval;
      return; 
    }
    dtostrf(uarm_param.x,3,1,x_str);
    sprintf(cmd, "G1 X%s F%d\r\n", x_str, uarm_param.speed);  //set the x value
    Serial2.write(cmd);
    delay(1);
  }
  if( digitalRead(JOY_DOWN) == LOW ){   
    uarm_param.x -= uarm_param.interval;
    if( ckeck_coord(uarm_param.x, uarm_param.y, uarm_param.z) == false ){ 
      uarm_param.x += uarm_param.interval;
      return; 
    }
    dtostrf(uarm_param.x,3,1,x_str);
    sprintf(cmd, "G1 X%s F%d\r\n", x_str, uarm_param.speed);  //set the x value
    Serial2.write(cmd); 
    delay(1);
  }
  if( digitalRead(JOY_LEFT) == LOW ){    
    uarm_param.y += uarm_param.interval;
    if( ckeck_coord(uarm_param.x, uarm_param.y, uarm_param.z) == false ){ 
      uarm_param.y -= uarm_param.interval;
      return; 
    }
    dtostrf(uarm_param.y,3,1,y_str);
    sprintf(cmd, "G1 Y%s F%d\r\n", y_str, uarm_param.speed); //set the y value
    Serial2.write(cmd);
    delay(1);
  }
  if( digitalRead(JOY_RIGHT) == LOW ){   
    uarm_param.y -= uarm_param.interval;
    if( ckeck_coord(uarm_param.x, uarm_param.y, uarm_param.z) == false ){ 
      uarm_param.y += uarm_param.interval;
      return; 
    }
    dtostrf(uarm_param.y,3,1,y_str);
    sprintf(cmd, "G1 Y%s F%d\r\n", y_str, uarm_param.speed); //set the y value
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
        Serial2.write("M2232 V0\r\n");                    // close the gripper
        delay(1);
      }else{
        pump_sw = true;
        Serial2.write("M2232 V1\r\n");                   // open the gripper
        delay(1);
      }
    }
  }
  
  u8g.firstPage();                                        // oled display
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

bool ckeck_coord(float x, float y, float z){
  float anglea=0, angleb=0, anglec=0;
  coord_effect2arm(&x, &y, &z);
  coord_to_angle(x, y, z, &anglea, &angleb, &anglec);
  return is_angle_legal(anglea, angleb, anglec);
}
