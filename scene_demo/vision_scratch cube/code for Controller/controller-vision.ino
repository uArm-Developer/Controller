#include "main.h"
int inByte = 0,//serial buf
    num = 0;//buf counter
int x_openmv = 0, y_openmv = 0;
int x_uarm = 134, y_uarm = 65;
unsigned long times;
char buf[20],
     flag = 0,
     AS;
char color_sel = 4; // 0:yellow   1:red   2:green
extern bool openmv_flag;//detect connect
extern bool cube_flag;//detect find cube
extern int i2;
extern bool work_mode_flag;
extern int x_offest, y_offest;


void setup() {
  button_init();
  pinMode(LED_R, OUTPUT);
  LED_OFF;
  oled_init();
  joystick_init();
  button_init();
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  Serial2.write("G0 X200 Y0 Z160 F10000\n");


  first_page();
  while (digitalRead(BUTTON_A) == HIGH);
  LED_ON;
//  second_page();
//  openmv_connect();

  Serial.write("V2 START!\n");

  Serial2.write("M2400 S0\n");//set the mode of uarm
  delay(4000);
  Serial2.write("M2400 S0\n");//set the mode of uarm
  Serial2.write("M2122 V1\n");//report when finish the movemnet
  //  get_openmv_data();
  times = millis();
  cube_flag=false;
//  pick_and_palce();
}
void work()
{
  if ((flag == 0)&&(cube_flag == false))
  {
    LED_ON;

    //    mode_choose();
    Serial2.write("G0 X200 Y0 Z160 F10000\n");


//    wait_for_finish_moving();
       delay(2400);

        Serial2.write("G0 X200 Y0 Z160 F10000\n");
//    delay(500);//wait for the uarm to finish the moving then start the vision tracking
//        Serial2.begin(115200);

//    wait_for_finish_moving();
    Serial3.begin(115200);
    
    flag = 1;//vision start
    openmv_connect();
    times = millis();

  }
  LED_OFF;
  //get object coordinates from openmv
  if (get_openmv_data() == 1)
  {

    Serial.write("move\n");//confirm the openmv data
    Serial3.end();
    //new algorithm
    x_uarm = (y_openmv * (-0.7035) - 3.635 + 88 + 70 + 200) + x_offest;
    y_uarm = (x_openmv * (-0.7488) + 12.391 + 107.5 + 15 + 0) + y_offest;
    Serial.println(y_openmv);
    Serial.println(x_openmv);

    fifth_page();
    String commands = "G0 X";
    commands.concat(x_uarm);
    commands += " Y";
    commands.concat(y_uarm);
    commands += " Z100 F10000\n";
    Serial2.print(commands);

    Serial.print(commands);

    pick_and_palce();
    cube_flag = false;
    num = 0;
        flag = 0;//vision end

  }
  if ((buf[0] != 's') && (cube_flag == false))
  {
    //flag = 0;//vision end
    num=0;
    Serial.println("jsk");
    openmv_flag = false;
    openmv_connect();
    delay(2500);
    get_openmv_data();

  }
  error_page();
}
void loop() {
   fifth_page();
  // delay(3000);
//  button_mode();

  // joystick_work();
  // x_uarm=x_offest+200;
  // y_uarm=y_offest+0;
  //     String commands = "G0 X";
  //    commands.concat(x_uarm);
  //    commands += " Y";
  //    commands.concat(y_uarm);
  //    commands += " Z100 F10000\n";
  //    Serial2.print(commands);
  //    offest_page();
}
