#include <Arduino.h>
// #include <SD.h>
// #include <SPI.h>
// #include <FS.h>
// #include <FFat.h>

#include <MyWifi.cpp>
#include <MyWebServer.cpp>

MyWifi MyWifi1("Your SSID","Your Password");
MyWebServer MyWebServer1;

void setup() {
    Serial.begin(115200);
    MyWifi1.connect();
    Serial.println(MyWifi1.IsConnected());
    MyWebServer1.StartServer();
}

void loop() {
    delay(5000);
}