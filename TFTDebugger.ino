#include <TFT.h>  
#include <SPI.h>

#define cs   53
#define dc   45
#define rst  47


struct button{
  int coordX;
  int coordY;
  String text;
  int pin;
};

struct pov{
  int coordX;
  int coordY;
  String text;
  int pinUp;
  int pinDw;
  int pinLf;
  int pinRg;
};

struct analog{
  int coordX;
  int coordY;
  String text;
  int pinX;
  int pinY;
};

struct pedal{
  int coordX;
  int coordY;
  String text;
  int pin;
};

struct button TestButton = {2, 2, "Button Press", 22};
struct button TestButton2 = {2, 9, "Button test 2", 23};
struct pov TestPov = {2, 16, "PovA", 13, 12, 11, 10};
struct pov TestPov2 = {2, 25, "PovB", 7, 6, 5, 4};
struct pedal PedalA = {2, 34, "PedalA", A10};
struct pedal PedalB = {2, 50, "PedalB", A11};
struct analog StickA = {100, 95, "StickA", A0, A1};
struct analog StickB = {40, 95, "StickB", A2, A3};


// create screen for debugging
TFT TFTscreen = TFT(cs, dc, rst);

// create screen for radar
TFT Radar = TFT(29, dc, rst);

void setup() {
  

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setRotation(0);

  Radar.begin();
  Radar.background(0, 0, 0);
  Radar.stroke(255,255,255);
  Radar.setRotation(0);
  Radar.text("hello world", 20, 20);

  drawbuttontext(TestButton);
  drawbuttontext(TestButton2);
  drawpovtext(TestPov);
  drawpovtext(TestPov2);
  drawanalogtext(StickA);
  drawanalogtext(StickB);
  drawpedaltext(PedalA);
  drawpedaltext(PedalB);

}

void loop() {

  drawDebugMode();

}

void drawDebugMode(){
  drawbutton(TestButton);
  drawbutton(TestButton2);

  drawpov(TestPov);
  drawpov(TestPov2);

  drawanalog(StickA);
  drawanalog(StickB);

  drawpedal(PedalA);
  drawpedal(PedalB);
};


void drawbutton(button passedButton){

  int pin = passedButton.pin;
  int x = passedButton.coordX;
  int y = passedButton.coordY; 
  String buttonText = passedButton.text;

  if(digitalRead(pin) == 1){
      TFTscreen.fillRect(x, y, 5, 5, ST7735_WHITE);
    }else{
      TFTscreen.fillRect(x, y, 5, 5, ST7735_BLACK);
  };

};

void drawbuttontext(button controller){
  int x = controller.coordX;
  int y = controller.coordY;
  String text = controller.text;
  TFTscreen.text(text.c_str(), x + 7, y - 2);

  pinMode(controller.pin, INPUT);
};


void drawpov(pov passedPov){

  int U = passedPov.pinUp;
  int D = passedPov.pinDw;
  int L = passedPov.pinLf;
  int R = passedPov.pinRg;
  int x = passedPov.coordX;
  int y = passedPov.coordY; 
  String buttonText = passedPov.text;

  int sizex = 3;
  int sizey = 3;
  int offset = 2;

  if(digitalRead(U) == 1){
      TFTscreen.fillRect(x, y-offset, sizex, sizey, ST7735_WHITE);
    }else{
      TFTscreen.fillRect(x, y-offset, sizex, sizey, ST7735_BLACK);
  };

  if(digitalRead(D) == 1){
      TFTscreen.fillRect(x, y+offset, sizex, sizey, ST7735_WHITE);
    }else{
      TFTscreen.fillRect(x, y+offset, sizex, sizey, ST7735_BLACK);
  };

  if(digitalRead(L) == 1){
      TFTscreen.fillRect(x - offset, y, sizex, sizey, ST7735_WHITE);
    }else{
      TFTscreen.fillRect(x - offset, y, sizex, sizey, ST7735_BLACK);
  };

  if(digitalRead(R) == 1){
      TFTscreen.fillRect(x + offset, y, sizex, sizey, ST7735_WHITE);
    }else{
      TFTscreen.fillRect(x + offset, y, sizex, sizey, ST7735_BLACK);
  };

};

void drawpovtext(pov controller){
  int x = controller.coordX;
  int y = controller.coordY;
  String text = controller.text;
  TFTscreen.text(text.c_str(), x + 7, y - 2);

  pinMode(controller.pinUp, INPUT);
  pinMode(controller.pinDw, INPUT);
  pinMode(controller.pinLf, INPUT);
  pinMode(controller.pinRg, INPUT);

};

void drawanalog(analog passedAnalog){

  int pinX = passedAnalog.pinX;
  int pinY = passedAnalog.pinY;
  int x = passedAnalog.coordX;
  int y = passedAnalog.coordY;

  int aX = map(analogRead(pinX), 0, 1023, -12, 12);
  int aY = map(analogRead(pinY), 0, 1023, -12, 12);

  TFTscreen.fillCircle(x, y, 17, ST7735_BLACK);

  TFTscreen.fillRect(x + aX, y + aY, 3, 3, ST7735_WHITE);

};

void drawanalogtext(analog controller){

  int x = controller.coordX;
  int y = controller.coordY;
  String text = controller.text;
  TFTscreen.text(text.c_str(), x-15, y - 27);
  TFTscreen.drawCircle(x, y, 18, ST7735_WHITE);

  pinMode(controller.pinX, INPUT);
  pinMode(controller.pinY, INPUT);


};

void drawpedal(pedal passedPedal){

  int pin = passedPedal.pin;
  int x = passedPedal.coordX;
  int y = passedPedal.coordY;

  int a = map(analogRead(pin), 0, 1023, 0, 25);

  TFTscreen.fillRect(x + 8, y + 7, 26, 3, ST7735_BLACK);

  TFTscreen.fillRect(x + 7 + a , y + 7, 3, 3, ST7735_WHITE);

};

void drawpedaltext(pedal controller){

  int x = controller.coordX;
  int y = controller.coordY;
  String text = controller.text;
  TFTscreen.text(text.c_str(), x + 7, y - 3);

  TFTscreen.drawRect(x + 7, y + 6, 28, 5, ST7735_WHITE);

  pinMode(controller.pin, INPUT);


};
