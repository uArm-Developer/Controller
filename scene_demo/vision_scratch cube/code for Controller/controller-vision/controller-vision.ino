#include "main.h"
#define SOFTWARE_VERSION "V1.1.4\n"
int inByte = 0,//serial buf
    num = 0;//buf counter
int x_openmv = 0, y_openmv = 0;
int x_uarm = 0, y_uarm = 0;
unsigned long times;
char buf[1024],
     flag = 0,
     AS;
char color_sel = 4; // 0:yellow   1:red   2:green
extern int x_offest, y_offest;
extern enum commuincation openmv_state;
extern unsigned long time2;


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
  Serial.write("V2 START!\n");
  Serial2.write("M2400 S0\n");//set the mode of uarm
  Serial2.write("M2400 S0\n");//set the mode of uarm
  Serial2.write("M2122 V1\n");//report when finish the movemnet
  delay(400);
}

void work()
{
  if (flag == 0)
  {
    LED_ON;
    waiting_page();
    Serial2.write("G0 X200 Y0 Z160 F10000\n");
    //    wait_for_finish_moving();
    delay(1000);
    Serial2.write("G0 X200 Y0 Z160 F10000\n");
    delay(500);//wait for the uarm to finish the moving then start the vision tracking
    Serial2.begin(115200);
    //    wait_for_finish_moving();
    Serial3.begin(115200);
    flag = 1;//vision start
    openmv_connect();
  }
  LED_OFF;
  //get object coordinates from openmv
  get_openmv_data() ;
  if ((millis - time2 > 500) && (openmv_state != bedoing) && (openmv_state != bedata))
  {
    while (Serial3.available() > 0)
    {
      Serial3.read();
    }
    num = 0;
    openmv_state = befailed;
    if (digitalRead(BUTTON_D) == LOW) {
      delay(10);                              // <! delay
      if (digitalRead(BUTTON_D) == LOW) {
        while (digitalRead(BUTTON_D) == LOW);
        Serial.print("buttond\r\n");
        return 0;
      }
    }
    openmv_connect();
    delay(2500);
    get_openmv_data();
  }
  error_page();
}

void loop() {
  if (mode_choose () == true)
  {
    work();
  }
}
