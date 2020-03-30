
/*
 * Autor: Jesús David / jDabo
 * 
 * potenciometros conectados a A1 y A0
 * 
 * Potenciometers A1 and A0
 */
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#define ANCHO 128
#define ALTO 64 
#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO,ALTO,&Wire,OLED_RESET);

int y = 32;
int x = 64;

int yPos = 0;
int yPos2 = 0;
int dx = random(1,5);
int dy = random(1,5);

int puntaje1 = 0;
int puntaje2 = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(A1,INPUT);

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.setCursor(20,30);
  oled.print("Pong");
  delay(1500);
}

void loop() {
  yPos = map(analogRead(A0),0,512,0,49);  
  yPos2 = map(analogRead(A1),0,512,0,49);  
  oled.clearDisplay();
  if(puntaje1 >= 12 || puntaje2 >= 12){
    fin();
  }
  
  oled.drawLine(ANCHO/2,0,ANCHO/2,ALTO,WHITE);
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setCursor(20,5);
  oled.print(puntaje1);
  oled.setCursor(108,5);
  oled.print(puntaje2);
  oled.fillRect(2,yPos,3,15,WHITE);
  oled.fillRect(121,yPos2,3,15,WHITE);
  x += dx;
  y += dy;
  
  oled.fillCircle(x,y,3,WHITE);
  
  colision();
  oled.display();
}

void fin(){
  if(puntaje1 > puntaje2){
    puntaje1 = 0;
    puntaje2 = 0;
  }else{
    puntaje1 = 0;
    puntaje2 = 0;
  }
}

void colision(){
  for(int i = -3; i <= 18; i++){
    if(x - 3 == 7 && y == yPos + i){
      dx = random(2,5);
     }
  }
  for(int i = 0; i <= 18; i++){
    if(x == ANCHO - 10 && y == yPos2 + i){
      dx = -random(2,5);
     }
  }

    
  if(x <= ANCHO - ANCHO){
    delay(100);
    puntaje2 += 1;
    delay(100);
    dx = random(2,3);
    x  = 64;
    y = 32;
  }else if(x >= ANCHO){
    delay(100);
    puntaje1 += 1;
    delay(100);
    dx = -2;
    x  = 64;
    y = 32;
  }
  
  if(y == ALTO - ALTO ){
    dy = random(2,3);
  }else if(y == ALTO){
    dy = -2;
  }
}
