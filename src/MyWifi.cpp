#include <Arduino.h>
#include "WiFi.h"

class MyWifi{
    private:
        const char* ssid;
        const char* password;

     public:
        MyWifi(const char* ssid, const char* password) : ssid(ssid), password(password) {}

        void connect() {
            WiFi.begin(ssid, password);
        }

        bool IsConnected(){
            return WiFi.status();
        }
};
