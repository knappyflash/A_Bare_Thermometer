#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

class MyDisplay{
    public:
        TFT_eSPI tft = TFT_eSPI();
        void Print_Hello_World(){
            tft.init();
            tft.setRotation(1);
            tft.fillScreen(TFT_BLACK);
            tft.setTextColor(TFT_WHITE);
            tft.setTextSize(2);
            tft.setCursor(100, 100);
            tft.println("Hello, World!");
        }
};