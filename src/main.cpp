#include <Arduino.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <MyDisplay.cpp>
#include <MyThermometer.cpp>
#include <SplashArrayForJosh.h>
// #include <MyWifi.cpp>

MyDisplay MyDisplay1;
MyThermometer MyThermometer1;
MyThermometer MyThermometer2;

int Temp1 = 0;
int Temp2 = 0;
int Humty1 = 0;
int Humty2 = 0;
int Battery1 = 0;
int Battery2 = 0;

// For Timers
unsigned long currentMillis = millis();
unsigned long previousMillis1000 = 0;
unsigned long previousMillis30000 = 0;
unsigned long previousMillis60000 = 0; 
const long interval1000 = 1000; // 1 seconds
const long interval30000 = 30000; // 30 seconds
const long interval60000 = 60000; // 1 minutes
void Function_Interval_1_Seconds() {
}
void Function_Interval_30_Seconds() {
}
void Function_Interval_1_Minute() {

    if (!MyThermometer1.Get_isConnected()){
        MyThermometer1.Connect("a4:c1:38:65:97:23");
    }
    if (!MyThermometer2.Get_isConnected()){
        MyThermometer2.Connect("a4:c1:38:42:97:18");
    }

    if (MyThermometer1.Get_isConnected()){
        Temp1 = MyThermometer1.Get_Temperature();
        Humty1 = MyThermometer1.Get_Humidity();
        Battery1 = MyThermometer1.Get_BatteryLvl();
    }

    if (MyThermometer2.Get_isConnected()){
        Temp2 = MyThermometer2.Get_Temperature();
        Humty2 = MyThermometer2.Get_Humidity();
        Battery2 = MyThermometer2.Get_BatteryLvl();
    }

    if (MyThermometer1.Get_isConnected() && MyThermometer2.Get_isConnected()){
        MyDisplay1.Do_A_Loop(Temp1, Temp2, Humty1, Humty2, Battery1, Battery2,SplashArrayForJosh[random(0, 551)]);
    }else{
        MyDisplay1.Do_A_Loop(-1, -1, -1, -1, -1, -1,"Hi Josh. Nothing To See Here...");
    }

    // Serial.print("Free heap memory: ");
    // Serial.print(ESP.getFreeHeap());
    // Serial.println(" bytes");
    
}

void setup() {

    Serial.begin(115200);

    MyThermometer1.MyInit();
    MyThermometer2.MyInit();

    MyDisplay1.SetUp_Display();

    Function_Interval_1_Seconds();
    Function_Interval_30_Seconds();
    Function_Interval_1_Minute();

}

void loop() {

    currentMillis = millis();

    // Every Second
    if (currentMillis - previousMillis1000 >= interval1000) {
        previousMillis1000 = currentMillis;
        Function_Interval_1_Seconds();
    }
    // Every 30 Seconds
    if (currentMillis - previousMillis30000 >= interval30000) {
        previousMillis30000 = currentMillis;
        Function_Interval_30_Seconds();
    }
    // Every Minute
    if (currentMillis - previousMillis60000 >= interval60000) {
        previousMillis60000 = currentMillis;
        Function_Interval_1_Minute();
    }

    delay(100);

}

