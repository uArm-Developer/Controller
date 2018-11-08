#include <Adafruit_TCS34725.h>

enum pick_mode_e {
  RED_MODE = 0,
  GREEN_MODE,
  YELLOW_MODE,
};

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);             // <! debug uart
  Serial2.begin(115200);            // <! uarm uart
                   
  if( !tcs.begin() ){                            // <! init color sensor
    Serial.print( "color sensor error!" );
  }
  delay(100);
  Serial2.write("G0 X150 Y0 Z100 F2000000\n");

}

bool is_red(uint16_t r, uint16_t g, uint16_t b){        // <! is the red block?
  if( (r<2000) || (r>3500) ){
    return false;
  }
  if( (g<200) || (g>1500) ){
    return false;
  }
  if( (b<200) || (b>1000) ){
    return false;
  }
  return true;  
}

bool is_green(uint16_t r, uint16_t g, uint16_t b){    // <! is the green block?
  if( (r<1500) || (r>3000) ){
    return false;
  }
  if( (g<3000) || (g>4500) ){
    return false;
  }
  if( (b<1200) || (b>2000) ){
    return false;
  }
  return true;
}

bool is_yellow(uint16_t r, uint16_t g, uint16_t b){   // <! is the yellow block?
  if( (r<5000) || (r>6500) ){
    return false;
  }
  if( (g<4500) || (g>5600) ){
    return false;
  }
  if( (b<500) || (b>2000) ){
    return false;
  }
  return true;
}

void pick_up_cube_to_cloar(){
  static int cnt = 0;
  if( cnt > 8 ){ return; }
  float x = 201.7, y = 24.6;
  char x_str[20], y_str[20];
  char cmd[50];

  Serial2.write("G0 Z80 F2000000\n");
  delay(1000);
  
  int i = cnt / 3;
  int j = cnt % 3;
  x -= 30 * i;
  y -= 30 * j;
  
  cnt++;
  dtostrf(x, 5, 2, x_str);
  dtostrf(y, 5, 2, y_str);
  sprintf( cmd, "G0 X%s Y%s F2000000\n",x_str, y_str );
  Serial2.write(cmd);

  Serial2.write("G0 Z25 F2000000\n");
  delay(1000);
  Serial2.write("M2231 V1\n");
  delay(1000);
  Serial2.write("G0 Z80 F2000000\n");
  delay(1000);

  Serial2.write("G0 X267 Y7 Z80 F2000000\n");
  delay(1000);
  Serial2.write("G0 X267 Y7 Z37 F2000000\n");
  delay(1000);
  Serial2.write("M2231 V0\n");
  delay(1000);
  Serial2.write("G0 X267 Y7 Z80 F2000000\n");
  delay(1000);   
}

void pick_up_cube_form_color(){
  Serial2.write("G0 X267 Y7 Z80 F2000000\n");
  delay(1000);
  Serial2.write("G0 X267 Y7 Z37 F2000000\n");
  delay(1000);
  Serial2.write("M2231 V1\n");
  delay(1000);
  Serial2.write("G0 X267 Y7 Z80 F2000000\n");
  delay(1000);  
}

void pick_down_red(){
  char xy_cmd[20],cmd[50];
  static int cnt=0;
  switch( cnt++ ){
    case 0:
      strcpy( xy_cmd, "X310 Y67.2" );
      break;
    case 1:
      strcpy( xy_cmd, "X310 Y27.2" );
      break;
    case 2:
      strcpy( xy_cmd, "X310 Y-27.2" );
      break;
  }
  sprintf(cmd, "G0 %s Z80 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  

  sprintf(cmd, "G0 %s Z25 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  
  
  Serial2.write("M2231 V0\n");
  delay(1000); 
  
//  sprintf(cmd, "G0 %s Z50 F2000000\n", xy_cmd );
//  Serial2.write(cmd);
//  delay(1000);  
}

void pick_down_green(){
  char xy_cmd[20],cmd[50];
  static int cnt=0;
  switch( cnt++ ){
    case 0:
      strcpy( xy_cmd, "X115 Y157" );
      break;
    case 1:
      strcpy( xy_cmd, "X165 Y157" );
      break;
    case 2:
      strcpy( xy_cmd, "X215 Y157" );
      break;
  }
  sprintf(cmd, "G0 %s Z80 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  

  sprintf(cmd, "G0 %s Z25 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  
  
  Serial2.write("M2231 V0\n");
  delay(1000); 
  
//  sprintf(cmd, "G0 %s Z50 F2000000\n", xy_cmd );
//  Serial2.write(cmd);
//  delay(1000);  
}

void pick_down_yellow(){
  char xy_cmd[20],cmd[50];
  static int cnt=0;
  switch( cnt++ ){
    case 0:
      strcpy( xy_cmd, "X115 Y-157" );
      break;
    case 1:
      strcpy( xy_cmd, "X165 Y-157" );
      break;
    case 2:
      strcpy( xy_cmd, "X215 Y-157" );
      break;
  }
  sprintf(cmd, "G0 %s Z80 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  

  sprintf(cmd, "G0 %s Z25 F2000000\n", xy_cmd );
  Serial2.write(cmd);
  delay(1000);  
  
  Serial2.write("M2231 V0\n");
  delay(1000); 
  
//  sprintf(cmd, "G0 %s Z50 F2000000\n", xy_cmd );
//  Serial2.write(cmd);
//  delay(1000);  
}

enum work_mode_e{
  IDLE_MODE = 0,
  PICK_MODE,
} work_mode = IDLE_MODE;

void loop() {
  uint16_t r, g, b, c;
  if( work_mode == IDLE_MODE ){
    Serial.print(" pick up cube \n");
    work_mode = PICK_MODE;
    pick_up_cube_to_cloar();
  }else{
    tcs.getRawData(&r, &g, &b, &c);       // <! read the color sensor value
    if(  is_red(r, g, b) ){
       Serial.print(" red \n");
       pick_up_cube_form_color();
       pick_down_red();
       work_mode = IDLE_MODE;
    }else if( is_green(r, g, b) ){
      Serial.print(" green \n");
      pick_up_cube_form_color();
      pick_down_green();
      work_mode = IDLE_MODE;
    }else if( is_yellow(r, g, b) ){
      Serial.print(" yellow \n");
      pick_up_cube_form_color();
      pick_down_yellow();
      work_mode = IDLE_MODE;
    }    
  }
  


 

//  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print(b, DEC); Serial.print("\r\n");   

}
