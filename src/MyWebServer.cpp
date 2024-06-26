#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class MyWebServer{

     public:
        AsyncWebServer server;
        const char* PARAM_MESSAGE = "message";

        MyWebServer() : server(80) {
            PARAM_MESSAGE = "message";
        }

        void notFound(AsyncWebServerRequest *request) {
            request->send(404, "text/plain", "Not found");
        }

        void StartServer(){
            server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
                request->send(200, "text/plain", "Hello, world");
            });

            server.on("/get", HTTP_GET, [this] (AsyncWebServerRequest *request) {
                String message;
                if (request->hasParam(PARAM_MESSAGE)) {
                    message = request->getParam(PARAM_MESSAGE)->value();
                } else {
                    message = "No message sent";
                }
                request->send(200, "text/plain", "Hello, GET: " + message);
            });

            server.on("/post", HTTP_POST, [this](AsyncWebServerRequest *request){
                String message;
                if (request->hasParam(PARAM_MESSAGE, true)) {
                    message = request->getParam(PARAM_MESSAGE, true)->value();
                } else {
                    message = "No message sent";
                }
                request->send(200, "text/plain", "Hello, POST: " + message);
            });
            
            server.onNotFound(std::bind(&MyWebServer::notFound, this, std::placeholders::_1));
            server.begin();

        }
};