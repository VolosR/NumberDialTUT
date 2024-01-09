#include <TFT_eSPI.h>
#include <TouchDrvCSTXXX.hpp>
#include "utilities.h"

//CONSTRUCTORS::::::::::::::::::::::::::::::::
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

TouchDrvCSTXXX touch;
int16_t x[5], y[5];

//COLORS::::::::::::::::::::::::::::::::::::::
#define col1 0x0228
#define blck TFT_BLACK

//VARIABLES:::::::::::::::::::::::::::::::::::
bool debounce=0;
String txt="";
int xpos[3]={0,74,148};
int ypos[4]={184,258,332,406};
String buttons[4][3]={{"1","2","3"},
              {"4","5","6"},
              {"7","8","9"},
              {"DEL","0","<"}};

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
    draw();
}

void draw()
  {
    spr.fillSprite(TFT_BLACK);
    spr.setTextColor(TFT_WHITE,blck);
    spr.setTextDatum(4);
    spr.drawString(txt,111,100,6);

    
    spr.setTextColor(TFT_WHITE,col1);
    

    for(int yy=0;yy<4;yy++)
    for(int xx=0;xx<3;xx++)
    {
    spr.fillRoundRect(xpos[xx]+2, ypos[yy], 70, 70,5, col1);
    spr.drawString(buttons[yy][xx],xpos[xx]+37,ypos[yy]+34,4);
    }



    spr.pushSprite(0,0);
  }


void loop()
{
    uint8_t touched = touch.getPoint(x, y, touch.getSupportTouchPoint());
    if (touched){
      if(debounce==0)
      {
      debounce=1;
        for(int yy=0;yy<4;yy++)
        for(int xx=0;xx<3;xx++)
        if(x[0]>xpos[xx] && x[0]<xpos[xx]+74 && y[0]>ypos[yy] && y[0]<ypos[yy]+74)
          {
          if(buttons[yy][xx]=="DEL")
          txt="";
          else if(buttons[yy][xx]=="<")
          txt=txt.substring(0,txt.length()-1);
          else
          txt=txt+buttons[yy][xx];
          }
      }
    draw();
    }else debounce=0;
       

 
}





