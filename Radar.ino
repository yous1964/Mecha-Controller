#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

#define TFT_DC 7
#define TFT_CS 10

//Screen limit to reset bogey placement
#define LIMIT 230

Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

struct bogey{
  int coordX;
  int coordY;
  String name;
  int isTGT;
  int beingTGT;
};

struct bogey Onivai{60,60,"Onivai Horizon",1,1};
struct bogey Daisaku{40,60,"Daisaku Trabukko",0,0};
struct bogey Bogelby{30,120,"Bogelby Raster",0,0};

void setup() {
  Serial.begin(9600);

  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  drawBorder();
  
  
}

void loop() {

  drawPlayer();
  
  // 
  drawBogey(Onivai);

  Onivai.coordY = Onivai.coordY + 1;
  Onivai.coordX = Onivai.coordX + 2;

  if (Onivai.coordX>LIMIT){Onivai.coordX=40;};
  if (Onivai.coordY>LIMIT){Onivai.coordY=40;};

  drawBogey(Daisaku);

  Daisaku.coordY = Daisaku.coordY + 2;
  Daisaku.coordX = Daisaku.coordX + 0;

  if (Daisaku.coordX>LIMIT){Daisaku.coordX=40;};
  if (Daisaku.coordY>LIMIT){Daisaku.coordY=60;};

  drawBogey(Bogelby);

  Bogelby.coordY = Bogelby.coordY + 0;
  Bogelby.coordX = Bogelby.coordX + 4;

  if (Bogelby.coordX>LIMIT){Bogelby.coordX=30;};
  if (Bogelby.coordY>LIMIT){Bogelby.coordY=120;};

  //delay(200);

}

void drawPlayer(){
  tft.fillRect(120,120,10,10, GC9A01A_WHITE);

};

void drawBorder(){
  tft.drawCircle(120,120,119,GC9A01A_WHITE);
};


void drawBogey(bogey bogey){

  int x = bogey.coordX;
  int y = bogey.coordY;
  String name = bogey.name;
  int tgt = bogey.isTGT;
  int beingTGT = bogey.beingTGT;

  tft.fillRect(x-12,y-12,24,24,GC9A01A_BLACK);

  tft.drawCircle(x,y,5,GC9A01A_WHITE);

  /*if(tgt == 1){
    Paint_DrawString_EN(x, y+16, "TGT",&Font16,  BLACK, RED);
  };*/

  if (beingTGT == 1){
    tft.drawRect(x-8,y-9,17,18, GC9A01A_WHITE);
  };

  if (x>=LIMIT || y>=LIMIT){
    tft.fillRect(x-12,y-12,24,24,GC9A01A_BLACK);
    drawBorder();
  };

};
