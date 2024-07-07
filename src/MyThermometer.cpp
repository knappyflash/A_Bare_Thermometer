#include <Arduino.h>
#include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
#include <BLEAdvertisedDevice.h>


class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        // Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    // Serial.println("Connected to the BLE Server.");
  }

  void onDisconnect(BLEClient* pclient) {
    // Serial.println("Disconnected from the BLE Server.");
  }
};

class MyThermometer{

    private:

        BLEClient*  pClient  = BLEDevice::createClient();

        const char* Service_Battery_UUID =       "0000180f-0000-1000-8000-00805f9b34fb";
        const char* Service_Environmental_UUID = "0000181a-0000-1000-8000-00805f9b34fb";

        const char* Char_Battery_Lvl_UUID =      "00002a19-0000-1000-8000-00805f9b34fb";
        const char* Char_Temp_UUID =             "00002a6e-0000-1000-8000-00805f9b34fb";
        const char* Char_Humidity_UUID =         "00002a6f-0000-1000-8000-00805f9b34fb";

    public:

        MyThermometer(){

        }

        void MyInit(){
            // Serial.println("Starting Arduino BLE Client application...");
            BLEDevice::init("");
        }

        void Scan(){
            // Use the BLEDevice to scan for the device with the service you want
            BLEScan* pBLEScan = BLEDevice::getScan();
            pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
            pBLEScan->setInterval(1349);
            pBLEScan->setWindow(449);
            pBLEScan->setActiveScan(true);
            pBLEScan->start(5, false);
        }

        void Connect(const char* MacAdress){
            if (!pClient->isConnected()){
                pClient->setClientCallbacks(new MyClientCallback());
            }
            BLEAddress ThermometerMacAddress(MacAdress);
            pClient->connect(ThermometerMacAddress);
        }

        bool Get_isConnected(){
            return pClient->isConnected();
        }

        int Get_Temperature(){
            int MyValue = 0;
            static BLEUUID SeriveUUID(Service_Environmental_UUID);
            static BLEUUID CharacteristicUUID(Char_Temp_UUID);
            BLERemoteService* pRemoteService = pClient->getService(SeriveUUID);
            BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(CharacteristicUUID);
            if(pRemoteCharacteristic->canRead()) {
                std::string valueRaw = pRemoteCharacteristic->readValue();
                double ValueConverted = (valueRaw[1] << 8) | valueRaw[0];
                MyValue = round((((ValueConverted / 100) * 1.8) + 32));
            }
            return MyValue;
        }

        int Get_Humidity(){
            int MyValue = 0;
            static BLEUUID SeriveUUID(Service_Environmental_UUID);
            static BLEUUID CharacteristicUUID(Char_Humidity_UUID);
            BLERemoteService* pRemoteService = pClient->getService(SeriveUUID);
            BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(CharacteristicUUID);
            if(pRemoteCharacteristic->canRead()) {
                std::string valueRaw = pRemoteCharacteristic->readValue();
                double ValueConverted = (valueRaw[1] << 8) | valueRaw[0];
                MyValue = (round(ValueConverted / 100));
            }
            return MyValue;
        }

        int Get_BatteryLvl(){
            int MyValue = 0;
            static BLEUUID SeriveUUID(Service_Battery_UUID);
            static BLEUUID CharacteristicUUID(Char_Battery_Lvl_UUID);
            BLERemoteService* pRemoteService = pClient->getService(SeriveUUID);
            BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(CharacteristicUUID);
            if(pRemoteCharacteristic->canRead()) {
                std::string valueRaw = pRemoteCharacteristic->readValue();
                MyValue = (uint8_t)valueRaw[0];
            }
            return MyValue;
        }

        void Disconnect(){
            pClient->disconnect();
        }

};


