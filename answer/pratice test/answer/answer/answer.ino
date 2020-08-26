#include <ssd1306.h>
#include <ssd1306_console.h>
Ssd1306Console console;
int readnum = 0;
int n = 366;
bool flag2 = true;
int speed = random(750,760);
void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  pinMode(15,INPUT);
  pinMode(2,INPUT);
  ledcSetup(0, 5000, 10);
  ledcSetup(1, 5000, 10);
  ledcSetup(2, 5000, 10);
  ledcSetup(3, 5000, 10);
  ledcAttachPin(2, 2);
  ledcAttachPin(4, 3);
  ledcAttachPin(13, 0);
  ledcAttachPin(27, 1);
  digitalWrite(4,HIGH);
  Serial.begin(115200);
  while(!digitalRead(2));
  attachInterrupt(15,f,FALLING);
}
void loop() {
  console.println(readnum);
  if(readnum - n >= random(5)){
    Stop();
    flag2 = false;
  }
}
void f(){
  detachInterrupt(15);
  if(readnum - n >= random(5)){
    Stop();
    flag2 = false;
  }
  readnum += 1*int(flag2);
  attachInterrupt(15,f,FALLING);
}
void forward() {
  ledcWrite(0, speed);
  ledcWrite(1, 0);
  ledcWrite(2, speed);
  ledcWrite(3, 0);
}
void backward() {
  ledcWrite(0, 0);
  ledcWrite(1, speed);
  ledcWrite(2, 0);
  ledcWrite(3, speed);
}
void Stop() {
  ledcWrite(0, 1);
  ledcWrite(1, 1);
  ledcWrite(2, 1);
  ledcWrite(3, 1);
  
}
