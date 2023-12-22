#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H




class WifiManager{
private:
  char _ssid[100];
  char _pass[100];
  int _key;
  int _status;
  void EnableWifi();
  void ConnectWifi();
public:
  WifiManager(const char* ssid, const char* password, int key = 1);
  WifiManager();
  ~WifiManager();
  void PrintWifiStatus();


};

#endif