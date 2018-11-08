/************************* LED io *************************/
#define RGB_LED_R       2
#define RGB_LED_G       3
#define RGB_LED_B       5

enum rgb_mode_e{
  RED = 0,
  GREEN,
  BLUE,
} rgb_mode = RED;

void setup() {
  // put your setup code here, to run once:
  pinMode(RGB_LED_R, OUTPUT);
  pinMode(RGB_LED_G, OUTPUT);
  pinMode(RGB_LED_B, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch( rgb_mode ){
    case RED:
          digitalWrite(RGB_LED_R,LOW);
          digitalWrite(RGB_LED_G,HIGH);
          digitalWrite(RGB_LED_B,HIGH);
          rgb_mode = GREEN;   
      break;
    case GREEN:
          digitalWrite(RGB_LED_R,HIGH);
          digitalWrite(RGB_LED_G,LOW);
          digitalWrite(RGB_LED_B,HIGH);  
          rgb_mode = BLUE;
      break;
    case BLUE:
          digitalWrite(RGB_LED_R,HIGH);
          digitalWrite(RGB_LED_G,HIGH);
          digitalWrite(RGB_LED_B,LOW);  
          rgb_mode = RED;
      break;
  }
  delay(500);

}
