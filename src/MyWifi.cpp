#include <Arduino.h>
// #include <WiFi.h>
#include <WiFiManager.h>

// WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
// it is a good practice to make sure your code sets wifi mode how you want it.

// put your setup code here, to run once:

//WiFiManager, Local intialization. Once its business is done, there is no need to keep it around

// reset settings - wipe stored credentials for testing
// these are stored by the esp library
// wm.resetSettings();

// Automatically connect using saved credentials,
// if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
// if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
// then goes into a blocking loop awaiting configuration and will return success result

// res = wm.autoConnect(); // auto generated AP name from chipid
// res = wm.autoConnect("AutoConnectAP"); // anonymous ap

class MyWifi{
     public:

        void Reset_Settings(){
            WiFiManager wm;
            wm.resetSettings();
        }

        void Connect(){
            WiFiManager wm;

            bool res;
            res = wm.autoConnect("A_Bare_Thermometer", "SclRT64*"); // password protected ap

            if(!res) {
                Serial.println("Failed to connect");
                // ESP.restart();
            } 
            else {
                //if you get here you have connected to the WiFi    
                Serial.println("connected...yeey :)");
            }
        }
};
