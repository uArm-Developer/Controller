#include <U8glib.h>
/************************* LCD io *************************/
#define LCD_CS          42
#define LCD_RES         43
#define LCD_CD          44
#define SD_CS           13
#define LCD_SCK         30 
#define LCD_MOSI        35
U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);
////////////////////////////////////////////////////
//key pin
#define UP 33
#define DOWN 41
#define LEFT 32
#define RIGHT 37
#define A 47
#define B 49
////////////////////////////////////////////////////
//
int box_x = 0;
int box_y = 0;
//int box_width = 2;
int box_x_length = 98;//x direction 32  0-31
int box_y_length = 62;//y direction 20  0-19
int snake_max_length = 100; //the body max length of the snake
int snake_x[100];//the x coordinates of the snake's body
int snake_y[100];//the y coordinates of the snake's body
int snake_body_width = 3; //the width of the snake's body
int food_x;//the x coordinates of the food
int food_y;//the y coordinates of the food
int snake_length = 3; //current length of the snake
unsigned int game_speed;//speed

// base on HWT team code.Thanks for LHW.
//////////////////////////////////////////////////////

void setup(void)
{
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(LCD_RES, OUTPUT);
  digitalWrite(LCD_RES, HIGH);
  Serial.begin(115200);
  randomSeed(analogRead(A0)); 
  welcom();
  delay(1000);

}
////////////////////////////////////////////////////
//welcom page
void welcom()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_gdr14r);
    u8g.setPrintPos(0, 30);
    u8g.print("UFACTORY");
    u8g.setPrintPos(0, 50);
    u8g.print("      Controller");
    u8g.setFont(u8g_font_9x18);

  } while (u8g.nextPage());
}

//read key value
int read_key()
{
  int key_temp;
  if (digitalRead(UP) == LOW) {
    key_temp = UP;
    return key_temp;
  }
  if (digitalRead(DOWN) == LOW) {
    key_temp = DOWN;
    return key_temp;
  }
  if (digitalRead(LEFT) == LOW) {
    key_temp = LEFT;
    return key_temp;
  }
  if (digitalRead(RIGHT) == LOW) {
    key_temp = RIGHT;
    return key_temp;
  }
  if (digitalRead(A) == LOW) {
    key_temp = A;
    return key_temp;
  }
  if (digitalRead(B) == LOW) {
    key_temp = B;
    return key_temp;
  }
  return 0;
}
///////////////////////////////////////
void game_over()    //game over
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_gdr14r);
    u8g.setPrintPos(0, 40);
    u8g.print("GAME OVER!");
  } while (u8g.nextPage());  
  snake_length=3;
  snake_x[0] = 15; snake_y[0] = 15;//snake begin pos
  snake_x[1] = snake_x[0]  - 1; snake_y[1] = snake_y[0];
  snake_x[2] = snake_x[1]  - 1; snake_y[2] = snake_y[1];
}
//game main function
void snake_main()
{
  int flag = 1; 
  snake_x[0] = 15; snake_y[0] = 15;//snake begin pos
  snake_x[1] = snake_x[0]  - 1; snake_y[1] = snake_y[0];
  snake_x[2] = snake_x[1]  - 1; snake_y[2] = snake_y[1];
  int snake_dir=RIGHT;
  game_speed=180;
  int food_flag=1;
  Serial.println("snake!");
  food();
  while (flag)
  {
    snake_frame(game_speed);
    delay(game_speed);
    switch(read_key())
    {
      case UP:
        if(snake_dir!=DOWN)
        {
          snake_dir=UP;
          break;
        }
      case DOWN:
        if(snake_dir!=UP)
        {
          snake_dir=DOWN;
          break;
        }
        case LEFT:
        if(snake_dir!=RIGHT)
        {
          snake_dir=LEFT;
          break;
        }
        case RIGHT:
        if(snake_dir!=LEFT)
        {
          snake_dir=RIGHT;
          break;
        }
        default:break;
    }
    if(snake_eat_food(snake_dir)==1)
    {
      food();
      if(snake_length<10){game_speed=180;}
      if(snake_length<30&&snake_length>=10){game_speed=150;}
      if(snake_length<50&&snake_length>=30){game_speed=120;}
      if(snake_length>=50){game_speed=100;}
    }
    else
    {
      if(snake_knock_wall(snake_dir==1))
      {
        game_over();
        flag=0;
      }
      else
      {
        if(snake_eat_body(snake_dir)==1)
        {
          game_over();
          flag=0;
        }
        else
        {
          change_con(snake_dir);
        }
      }
    }
  }
}
//game page
void snake_frame(int s)
{
  u8g.firstPage();
  do
  {
    u8g.drawFrame(box_x, box_y, box_x_length, box_y_length);
    u8g.setFont(u8g_font_5x8);
    u8g.setPrintPos(box_x_length + 1, 12);
    u8g.print("Score");
    u8g.setPrintPos(box_x_length + 1, 22);
    u8g.print((snake_length - 3) * 5);
    u8g.setPrintPos(box_x_length + 1, 46);
    u8g.print("Speed");
    u8g.setPrintPos(box_x_length + 1, 56);
    u8g.print(180-s);
    u8g.drawFrame(food_x*snake_body_width+1, food_y*snake_body_width+1, snake_body_width, snake_body_width);//显示食物
    for (int i = 0; i < snake_length; i++)
    {
      if(i==0)
      {
        u8g.drawBox(snake_x[i]*snake_body_width+1, snake_y[i]*snake_body_width+1, snake_body_width, snake_body_width);
      }
      else
      {
        u8g.drawFrame(snake_x[i]*snake_body_width+1, snake_y[i]*snake_body_width+1, snake_body_width, snake_body_width);
      }
    }
  } while (u8g.nextPage());
}

//create food pos
void food()
{
  int flag = 1;
  while (flag)
  {
    food_x = random(0,(box_x_length-2)/3);
    food_y = random(0,(box_y_length-2)/3);
    for (int i = 0; i < snake_length; i++)
    {
        if((food_x==snake_x[i])&&(food_y==snake_y[i]))
        {
          break;
        }
        flag=0;
    }
  }
}
//change pos
void change_con(int DIR)
{
  int temp_x[snake_length+2];
  int temp_y[snake_length+2];
  for(int i=0;i<snake_length-1;i++)
  {
    temp_x[i]=snake_x[i];
    temp_y[i]=snake_y[i];
  }
  switch(DIR)
  {
    case RIGHT: {snake_x[0]+=1;break;}
    case LEFT: {snake_x[0]-=1;break;}
    case UP: {snake_y[0]-=1;break;}
    case DOWN: {snake_y[0]+=1;break;}
  }
  for(int i=1;i<snake_length;i++)
  {
    snake_x[i]=temp_x[i-1];
    snake_y[i]=temp_y[i-1];
  }
}
//change pos after eat food
void change_pos()
{
  int temp_x[snake_length+2];
  int temp_y[snake_length+2];
  for(int i=0;i<snake_length-1;i++)
  {
    temp_x[i]=snake_x[i];
    temp_y[i]=snake_y[i];
  }
  snake_x[0]=food_x;
  snake_y[0]=food_y;
  for(int i=1;i<snake_length;i++)
  {
    snake_x[i]=temp_x[i-1];
    snake_y[i]=temp_y[i-1];
  }
}

//juge if eat food. 0-not to eat  1-eat to  2-invalid
int snake_eat_food(int dir)
{
  int x_temp=snake_x[0];
  int y_temp=snake_y[0];
  switch(dir)
  {
    case UP :y_temp-=1;break;
    case DOWN :y_temp+=1;break;
    case LEFT :x_temp-=1;break;
    case RIGHT :x_temp+=1;break;
  }
  if((x_temp==food_x)&&(y_temp==food_y))
  {
      snake_length+=1;
      change_pos();
      return 1;
  }
  else
  {
    return 0;
  }
}

//juge if reach the wall  0-did't reach  1-reach  2-invalid
int snake_knock_wall(int dir)
{
  int x_temp=snake_x[0];
  int y_temp=snake_y[0];
  switch(dir)
  {
    case UP :y_temp-=1;break;
    case DOWN :y_temp+=1;break;
    case LEFT :x_temp-=1;break;
    case RIGHT :x_temp+=1;break;
  }
  if(x_temp<0||x_temp>31||y_temp<0||y_temp>19)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//judge if it's eating itself. 0-not to eat  1-eat to  2-invalid
int snake_eat_body(int dir)
{
  int x_temp=snake_x[0];
  int y_temp=snake_y[0];
  switch(dir)
  {
    case UP :y_temp-=1;break;
    case DOWN :y_temp+=1;break;
    case LEFT :x_temp-=1;break;
    case RIGHT :x_temp+=1;break;
  }
  for(int i=1;i<snake_length;i++)
  {
    if((snake_x[0]==snake_x[i])&&(snake_y[0]==snake_y[i]))
    {
      return 1;
    }
  }
  return 0;
}

void loop(void)//main loop
{
  while (1)
  {
    if( digitalRead(UP)==LOW || digitalRead(LEFT)==LOW || digitalRead(DOWN)==LOW || digitalRead(RIGHT)==LOW || digitalRead(A)==LOW || digitalRead(B)==LOW ){
      snake_main();
    }
  }
}
