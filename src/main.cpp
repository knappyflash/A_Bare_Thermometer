#include <Arduino.h>
// #include <SD.h>
// #include <SPI.h>
// #include <FS.h>
// #include <FFat.h>

#include <MyWifi.cpp>
#include <MyWebServer.cpp>
#include <MyDisplay.cpp>

MyWifi MyWifi1("SSID", "PASSWORD");
MyWebServer MyWebServer1;
MyDisplay MyDisplay1;

void setup() {
    Serial.begin(115200);
    MyWifi1.connect();
    Serial.println(MyWifi1.IsConnected());
    MyDisplay1.Print_Hello_World();
    MyWebServer1.StartServer();
}

void loop() {
    delay(5000);
}