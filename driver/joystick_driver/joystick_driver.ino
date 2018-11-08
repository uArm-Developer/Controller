/*************************  joystick   *************************/
#define JOY_UP      33
#define JOY_DOWN    41
#define JOY_LEFT    32
#define JOY_RIGHT   37
#define JOY_CENTRE  40

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print( "joystick test\r\n" );
  pinMode(JOY_UP,INPUT_PULLUP);
  pinMode(JOY_DOWN,INPUT_PULLUP);
  pinMode(JOY_LEFT,INPUT_PULLUP);
  pinMode(JOY_RIGHT,INPUT_PULLUP);
  pinMode(JOY_CENTRE,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(JOY_UP) == LOW){
    delay(10);                              // <! 
     if(digitalRead(JOY_UP) == LOW){
      while(digitalRead(JOY_UP) == LOW);
      Serial.print("joystick up\r\n");
     }
  }
  if(digitalRead(JOY_DOWN) == LOW){
    delay(10);                              // <! 
     if(digitalRead(JOY_DOWN) == LOW){
      while(digitalRead(JOY_DOWN) == LOW);
      Serial.print("joystick down\r\n");
     }
  }
  if(digitalRead(JOY_LEFT) == LOW){
    delay(10);                              // <! 
     if(digitalRead(JOY_LEFT) == LOW){
      while(digitalRead(JOY_LEFT) == LOW);
      Serial.print("joystick left\r\n");
     }
  }
  if(digitalRead(JOY_RIGHT) == LOW){
    delay(10);                              // <! 
     if(digitalRead(JOY_RIGHT) == LOW){
      while(digitalRead(JOY_RIGHT) == LOW);
      Serial.print("joystick right\r\n");
     }
  }
  if(digitalRead(JOY_CENTRE) == LOW){
    delay(10);                              // <! 
     if(digitalRead(JOY_CENTRE) == LOW){
      while(digitalRead(JOY_CENTRE) == LOW);
      Serial.print("joystick center\r\n");
     }
  }
}
