#include "main.h"
extern int inByte, num;
extern int x_openmv, y_openmv;
extern int x_uarm, y_uarm;
extern unsigned long times;
extern char buf[20], flag;
extern char color_sel,AS;
char c;
bool openmv_flag=false;//detect connect
bool cube_flag=false;//detect find cube
int i2;
void openmv_connect()
{
  switch (color_sel) {
    case 0: Serial3.write('y'); break;
    case 1: Serial3.write('r'); break;
    case 2: Serial3.write('g'); break;
    default: break;
  }
  Serial3.write('S');//send vision start command
  Serial.write("vision start for finding the cube\n");//send vision start command
  times = millis();
}
void error_page()
{
  if((openmv_flag==false)&&(cube_flag==false))
{

  fourth_page();
}
if((openmv_flag==true)&&(cube_flag==false))
{
 
  sixth_page();


}
if((openmv_flag==true)&&(cube_flag==true))
{
  fifth_page();
  
}
}
void wait_for_finish_moving()
{
  AS = ""; //clear the buffer
  while (AS != 'k') {
    if (Serial2.available() > 0) {
      AS = Serial2.read();
      Serial.println(AS);
    }
  }
        Serial.println("OUT");

}

//get object coordinates from openm
unsigned char get_openmv_data()
{
     // openmv_flag=false;
//        times = millis();

  if (Serial3.available() > 0)
  {
    inByte = Serial3.read();
    buf[num++] = inByte;
    Serial.write(inByte);
    if((buf[0]=='s')&&(num==1))
    {
      openmv_flag=true;
      cube_flag=false;
      Serial.println("stop");
      return 0;
    }
    if ((inByte == '\n') && (buf[1] == 'x'))
    {
      openmv_flag=true;
      cube_flag=true;
      Serial.write("get openmv data\n");
      int counters = 2; //jump the letter x
      x_openmv = 0;
      do {
        x_openmv = x_openmv * 10;
        x_openmv += buf[counters++] - 48;
      } while ((buf[counters] >= 0x30) && (buf[counters] <= 0x39));
      y_openmv = 0;
      counters++;//jump the letter y
      do {
        y_openmv = y_openmv * 10;
        y_openmv += buf[counters++] - 48;
      } while (counters + 1 < num);
      num = 0;
      return 1;
    }
  }
  if ((millis() - times > 10000) && (flag == 1)) //if no object detected, reset the flag every 10s
  {
    //clear the uart buffers
    while (Serial3.available() > 0)
    {
      inByte = Serial3.read();
    }
    //reset the count of uart
    num = 0;
    times = millis();
    flag = 0;
    buf[0]='a';
    Serial.write("status 1\n");//NO OBJECT IN CAMERA
  }
  return 0;
}



//move the detected object to the fixed position
void pick_and_palce()
{
  Serial2.write("G0 Z23 F10000\n");
  Serial2.write("M2231 V1\n");
  Serial2.write("G0 Z120 F10000\n");
  delay(500);
  Serial2.write("G2202 N0 V15\n");
  Serial2.write("G0 Z50 F10000\n");
      wait_for_finish_moving();

  Serial2.write("M2231 V0\n");
  Serial2.write("G0 Z80 F10000\n");
      wait_for_finish_moving();

  Serial2.write("G2202 N0 V90\n");

  delay(10000);
    wait_for_finish_moving();

  //change the color of tracking
  //color_sel++;
  //color_sel = color_sel%3;
}
