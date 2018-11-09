/************************* button io *************************/
#define BUTTON_A        47
#define BUTTON_B        49
#define BUTTON_C        12
#define BUTTON_D        11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print( "button test\r\n" );
  pinMode(BUTTON_A,INPUT_PULLUP);
  pinMode(BUTTON_B,INPUT_PULLUP);
  pinMode(BUTTON_C,INPUT_PULLUP);
  pinMode(BUTTON_D,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON_A) == LOW){
    delay(10);                              // <! delay
     if(digitalRead(BUTTON_A) == LOW){
      while(digitalRead(BUTTON_A) == LOW);
      Serial.print("button a\r\n");
     }
  }
  if(digitalRead(BUTTON_B) == LOW){
    delay(10);                              // <! delay
     if(digitalRead(BUTTON_B) == LOW){
      while(digitalRead(BUTTON_B) == LOW);
      Serial.print("button b\r\n");
     }
  }
  if(digitalRead(BUTTON_C) == LOW){
    delay(10);                              // <! delay
     if(digitalRead(BUTTON_C) == LOW){
      while(digitalRead(BUTTON_C) == LOW);
      Serial.print("button c\r\n");
     }
  }
  if(digitalRead(BUTTON_D) == LOW){
    delay(10);                              // <! delay
     if(digitalRead(BUTTON_D) == LOW){
      while(digitalRead(BUTTON_D) == LOW);
      Serial.print("button d\r\n");
     }
  }
}
