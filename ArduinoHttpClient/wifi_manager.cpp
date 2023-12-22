#include <WiFiNINA.h>
#include <SPI.h>
#include <WiFi.h>

#include "wifi_manager.h"
#include "wifi_constants.h"

void WifiManager::EnableWifi(){
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}
void WifiManager::ConnectWifi(){
  // attempt to connect to Wifi network:
  while (_status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(_ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    _status = WiFi.begin(_ssid, _pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

}
WifiManager::WifiManager(const char* ssid, const char* password, int key){
  strcpy(_ssid, ssid);
  strcpy(_pass, password);
  _key = key;
  _status = WL_IDLE_STATUS;      //connection status
  EnableWifi();
  ConnectWifi();
}
WifiManager::WifiManager(){
  strcpy(_ssid, defaultSsid);
  strcpy(_pass, defaultPass);
  _key = defaultKeyIndex;
  _status = WL_IDLE_STATUS;      //connection status
  EnableWifi();
  ConnectWifi();
}
WifiManager::~WifiManager(){

}
void WifiManager::PrintWifiStatus(){
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("Device IP: ");
  Serial.println(ip);

}
