#include <TFT_eSPI.h>
#include <TouchDrvCSTXXX.hpp>
#include "utilities.h"

//CONSTRUCTORS::::::::::::::::::::::::::::::::
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

TouchDrvCSTXXX touch;
int16_t x[5], y[5];

//COLORS::::::::::::::::::::::::::::::::::::::


//VARIABLES:::::::::::::::::::::::::::::::::::
int n=0;

void setBrightness(uint8_t value)
{
    static uint8_t level = 0;
    static uint8_t steps = 16;
    if (value == 0) {
        digitalWrite(BOARD_TFT_BL, 0);
        delay(3);
        level = 0;
        return;
    }
    if (level == 0) {
        digitalWrite(BOARD_TFT_BL, 1);
        level = steps;
        delayMicroseconds(30);
    }
    int from = steps - level;
    int to = steps - value;
    int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++) {
        digitalWrite(BOARD_TFT_BL, 0);
        digitalWrite(BOARD_TFT_BL, 1);
    }
    level = value;
}


void setup()
{

    tft.init();
    tft.fillScreen(TFT_BLACK);

    // Initialize capacitive touch
    touch.setPins(BOARD_TOUCH_RST, BOARD_TOUCH_IRQ);
    touch.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, CST226SE_SLAVE_ADDRESS);

    spr.createSprite(222,480);
    setBrightness(4);
   
}

void draw()
  {
    spr.fillSprite(TFT_BLACK);
    spr.drawString(String(n),50,100,7);
    spr.pushSprite(0,0);
  }


void loop()
{
    uint8_t touched = touch.getPoint(x, y, touch.getSupportTouchPoint());
    if (touched) 
      if(y[0]>240)
     {
      n=0; 
     }
       
  n++;
  draw();
}





