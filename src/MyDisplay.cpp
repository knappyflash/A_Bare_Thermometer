#include <Arduino.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

/*
Cheap Yellow Display (CYD) (ESP32-2432S028R) 320 x 240 2.8 LCD
TFT_eSPI ILI9341_2_DRIVER
https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display
*/

class MyDisplay{

    private:
        int TxtBG_R = 26;
        int TxtBG_G = 26;
        int TxtBG_B = 26;

    public:

        TFT_eSPI tft = TFT_eSPI();
        // TFT_eSprite sprA = TFT_eSprite(&tft);
        // TFT_eSprite sprB = TFT_eSprite(&tft);
        // TFT_eSprite sprC = TFT_eSprite(&tft);

        MyDisplay() {
        }

        void SetUp_Display(){
            tft.init();
            tft.setRotation(1);
            tft.fillScreen(tft.color565(0,0,80));
            tft.setTextColor(tft.color565(0,255,0),tft.color565(TxtBG_R,TxtBG_G,TxtBG_B),true);
            tft.setFreeFont(&FreeSans9pt7b);
            tft.setTextSize(2);

            Screen_Disolve();

            Serial.println("Display Has Been Setup.");
        }

        void Print(String Msg){
            if (tft.getCursorY() >= 224){
                tft.fillScreen(TFT_BLACK);
                tft.setCursor(0, 0);
            }
            tft.println(Msg);
        }

        void All_Black(){
            tft.fillScreen(TFT_BLACK);
        }

        // Ran out of ram creating sprites, so I am just going to do one big loop instead
        void Do_A_Loop(int Temp1, int Temp2, int Humidy1, int Humidy2, int Batt1, int Batt2, const char* SplashTxt){
            
            Screen_Disolve();

            int Col_x = 10;

            int RowHeader = 2;
            int Row1_y = 35;
            int Row2_y = 80;
            int Row3_y = 140;
            int RowSplash = 200;

            int Cell_Width = 300;
            int Cell_Heaight = 40;

            int TxtShd_R = 100;
            int TxtShd_G = 100;
            int TxtShd_B = 100;



            tft.setTextSize(1);

            // Header Row
            tft.fillRoundRect(Col_x, RowHeader, Cell_Width, 30, 5,tft.color565(TxtBG_R,TxtBG_G,TxtBG_B));
            tft.drawString(String("Temp"),Col_x + 15, RowHeader + 7);
            tft.drawString(String("Humidity"),Col_x + 120, RowHeader + 7);
            tft.drawString(String("Batt"),Col_x + 230, RowHeader + 7);

            tft.setTextSize(2);

            // Thermometer 1
            tft.fillRoundRect(Col_x, Row1_y,Cell_Width, Cell_Heaight, 10,tft.color565(TxtBG_R,TxtBG_G,TxtBG_B));
            tft.drawString(String(Temp1) + "F",Col_x + 15, Row1_y + 5);
            tft.drawString(String(Humidy1) + "%",Col_x + 120, Row1_y + 5);
            tft.drawString(String(Batt1) + "%",Col_x + 210, Row1_y + 5);

            // Thermometer 2
            tft.fillRoundRect(Col_x, Row2_y,Cell_Width, Cell_Heaight, 10,tft.color565(TxtBG_R,TxtBG_G,TxtBG_B));
            tft.drawString(String(Temp2) + "F",Col_x + 15, Row2_y + 5);
            tft.drawString(String(Humidy2) + "%",Col_x + 120, Row2_y + 5);
            tft.drawString(String(Batt2) + "%",Col_x + 210, Row2_y + 5);

            // Thermometer Difference
            int Dif_R;
            int Dif_G;
            int Dif_B;
            int TempDffInt;
            int HumtyDifInt;
            String TempDiff;
            String HumidyDiff;

            TempDffInt = Temp2 - Temp1;
            HumtyDifInt = Humidy2 - Humidy1;

            if (TempDffInt == 0){
                Dif_R = TxtBG_R;
                Dif_G = TxtBG_G;
                Dif_B = TxtBG_B;
                TempDiff = String(TempDffInt) + "F";
            }else if (TempDffInt > 0){
                Dif_R = 255;
                Dif_G = 0;
                Dif_B = 0;
                TempDiff = "+" + String(TempDffInt) + "F";
            }else{
                Dif_R = 0;
                Dif_G = 0;
                Dif_B = 255;
                TempDiff = String(TempDffInt) + "F";
            }

            if (HumtyDifInt > 0){
                HumidyDiff = "+" + String(HumtyDifInt) + "%";
            }else{
                HumidyDiff = String(HumtyDifInt) + "%";
            }

            tft.fillRoundRect(Col_x - 5, Row3_y - 5, Cell_Width+10,Cell_Heaight+10,10, tft.color565(Dif_R,Dif_G,Dif_B));
            tft.fillRoundRect(Col_x, Row3_y,Cell_Width, Cell_Heaight, 10,tft.color565(TxtBG_R,TxtBG_G,TxtBG_B));
            tft.drawString(TempDiff,Col_x + 15, Row3_y + 5);
            tft.drawString(HumidyDiff,Col_x + 120, Row3_y + 5);

            tft.setTextSize(1);

            // Rnd Splash Text
            tft.fillRoundRect(0, RowSplash, 320, 30, 5,tft.color565(TxtBG_R,TxtBG_G,TxtBG_B));
            tft.drawString(String(SplashTxt),2, RowSplash + 7);

        }

        void Screen_Disolve(){
             for(int i = 0; i <= 60000; i++) {
                int ColorChance = random(0, 20);
                int RndX = random(0, 320);
                int RndY = random(0, 240);
                if (ColorChance == 0){
                    tft.drawPixel(RndX,RndY,tft.color565(0,255,0));
                }else{
                    tft.drawPixel(RndX,RndY,tft.color565(0,0,80));
                }
            }
        }

        void Error_Screen(const char* Msg_Line1, const char* Msg_Line2, const char* Msg_Line3){
            tft.fillScreen(tft.color565(255,0,0));
            tft.textbgcolor = tft.color565(255,255,0);
            tft.textcolor = tft.color565(0,0,0);
            tft.drawString(String("!!! ERROR !!!"),0, 2);
            tft.drawString(String(Msg_Line1),0, 40);
            tft.drawString(String(Msg_Line2),0, 70);
            tft.drawString(String(Msg_Line3),0, 140);
        }

};