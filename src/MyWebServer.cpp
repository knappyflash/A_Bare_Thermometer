#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class MyWebServer{

     public:
        AsyncWebServer server = AsyncWebServer(80);

        String Temp1 = "62";
        String Temp2 = "75";
        String Humty1 = "53";
        String Humty2 = "61";

        int MyFontSize = 5;

        int BG_R = 0;
        int BG_G = 0;
        int BG_B = 50;
        
        int TXT_R = 255;
        int TXT_G = 255;
        int TXT_B = 255;

        MyWebServer(){}

        String Get_Temp1(){
            return Temp1;
        }

        String Get_Temp2(){
            return Temp2;
        }

        String Get_Humty1(){
            return Humty1;
        }

        String Get_Humty2(){
            return Humty2;
        }

        int Get_FontSize(){
            return MyFontSize;
        }

        void Get_BG_Color(int &My_R, int &My_G, int &My_B){
            My_R = BG_R;
            My_G = BG_G;
            My_B = BG_B;
        }

        void Get_TXT_Color(int &My_R, int &My_G, int &My_B){
            My_R = TXT_R;
            My_G = TXT_G;
            My_B = TXT_B;
        }

        static void notFound(AsyncWebServerRequest *request) {
            request->send(404, "text/plain", "Not found");
        }

        void Start_Server(){
            server.on("/", HTTP_GET, [&](AsyncWebServerRequest *request){
                request->send(200, "text/plain", "Welcome :)");
            });

            // Send a GET request to <IP>/get?message=<message>
            server.on("/get", HTTP_GET, [&] (AsyncWebServerRequest *request) {
                String message;
                if (request->hasParam("message")) {
                    message = request->getParam("message")->value();
                } else if (request->hasParam("temperature1")){
                    Temp1 = request->getParam("temperature1")->value();
                } else {
                    message = "No message sent";
                }
                request->send(200, "text/plain", "GET: " + message);
            });

            // Send a POST request to <IP>/post with a form field message set to <message>
            server.on("/post", HTTP_POST, [&](AsyncWebServerRequest *request){
                String message;
                if (request->hasParam("message", true)) {
                    message = request->getParam("message", true)->value();
                    request->send(200, "text/plain", "POST message: " + message);


                // Temperature Data Values
                } else if (request->hasParam("Temp1", true)){
                    Temp1 = request->getParam("Temp1", true)->value();
                    request->send(200, "text/plain", "POST: Temp1 " + Temp1);

                } else if (request->hasParam("Temp2", true)){
                    Temp2 = request->getParam("Temp2", true)->value();
                    request->send(200, "text/plain", "POST: Temp2 " + Temp2);

                } else if (request->hasParam("Humty1", true)){
                    Humty1 = request->getParam("Humty1", true)->value();
                    request->send(200, "text/plain", "POST: Humty1 " + Humty1);

                } else if (request->hasParam("Humty2", true)){
                    Humty2 = request->getParam("Humty2", true)->value();
                    request->send(200, "text/plain", "POST: Humty2 " + Humty2);


                // Background RGB
                } else if (request->hasParam("BG_R", true)){
                    String _bg_r = request->getParam("BG_R", true)->value();
                    BG_R = _bg_r.toInt();
                    request->send(200, "text/plain", "POST: BG_R " + String(BG_R));
                
                } else if (request->hasParam("BG_G", true)){
                    String _bg_g = request->getParam("BG_G", true)->value();
                    BG_G = _bg_g.toInt();
                    request->send(200, "text/plain", "POST: BG_G " + String(BG_G));

                } else if (request->hasParam("BG_B", true)){
                    String _bg_b = request->getParam("BG_B", true)->value();
                    BG_B = _bg_b.toInt();
                    request->send(200, "text/plain", "POST: BG_B " + String(BG_B));


                //Text RGB
                } else if (request->hasParam("TXT_R", true)){
                    String _txt_r = request->getParam("TXT_R", true)->value();
                    TXT_R = _txt_r.toInt();
                    request->send(200, "text/plain", "POST: TXT_R " + String(TXT_R));
                
                } else if (request->hasParam("TXT_G", true)){
                    String _txt_g = request->getParam("TXT_G", true)->value();
                    TXT_G = _txt_g.toInt();
                    request->send(200, "text/plain", "POST: TXT_G " + String(TXT_G));

                } else if (request->hasParam("TXT_B", true)){
                    String _txt_b = request->getParam("TXT_B", true)->value();
                    TXT_B = _txt_b.toInt();
                    request->send(200, "text/plain", "POST: TXT_B " + String(TXT_B));




                // Font Size
                } else if (request->hasParam("MyFontSize", true)){
                    String _MyFontSize = request->getParam("MyFontSize", true)->value();
                    MyFontSize = _MyFontSize.toInt();
                    request->send(200, "text/plain", "POST: MyFontSize " + String(MyFontSize));



                } else {
                    request->send(200, "text/plain", "POST: Not Recognized");
                }

            });

            server.onNotFound(notFound);

            server.begin();

        }

};