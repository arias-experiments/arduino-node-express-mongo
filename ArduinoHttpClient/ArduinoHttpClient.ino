#include <WiFiNINA.h>
#include <SPI.h>
#include <WiFi.h>

#include "wifi_manager.h"

#include <src/rapidjson/document.h>

enum States {WAIT, WGET, WPUT};

States currentState = WAIT;


const int LED1 = 7;
const int LED2 = 8;
const int LED3 = 9;

const int SWITCH1 = 2;
const int SWITCH2 = 3;
const int SWITCH3 = 4;

const int RESET = 5;
const int GET = 6;

const int POT = A0;


WiFiClient client;

char server[] = "192.168.1.11";
int port = 8001;
char path[] = "/api/states";


void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);

  pinMode(RESET, INPUT);
  pinMode(GET, INPUT);
  while (!Serial);

  WifiManager wifi;
  wifi.PrintWifiStatus();

}

void loop() {
  int valSwitch1, valSwitch2, valSwitch3, valGet, valReset;

  valSwitch1 = digitalRead(SWITCH1);
  valSwitch2 = digitalRead(SWITCH2);
  valSwitch3 = digitalRead(SWITCH3);

  valGet = digitalRead(GET);
  valReset = digitalRead(RESET);

  switch(currentState){
    case WAIT:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      if (valGet == LOW){
        Serial.println("GET PRESSED");
        Get();
        currentState = WGET;
        digitalWrite(LED2, HIGH);
        delay(1000);
        digitalWrite(LED2, LOW);
      }else{

      }
      if (valReset == LOW){
        Serial.println("RESET PRESSED");
        Reset();
        currentState = WPUT;
        digitalWrite(LED3, HIGH);
        delay(1000);
        digitalWrite(LED3, LOW);
      }else{

      }


      break;
    case WGET:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);

      Serial.println("-------- GET --------");
      while (client.available()){
        char c = client.read();
        Serial.print(c);
        currentState = WAIT;
      }
      

      break;
    case WPUT:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      Serial.println("-------- RESET --------");
      while (client.available()){
        char c = client.read();
        Serial.print(c);
        currentState = WAIT;
      }
      

      break;
    
  }


  if (valSwitch1 == LOW){
    Serial.println("S-1");
    digitalWrite(LED1, HIGH);   
    delay(1000);
  }else{
    digitalWrite(LED1, LOW);   

  }
  if (valSwitch2 == LOW){
    Serial.println("S-2");
    digitalWrite(LED2, HIGH);   
    delay(1000);
  }else{
    digitalWrite(LED2, LOW);   
  }
  if (valSwitch3 == LOW){
    Serial.println("S-3");
    digitalWrite(LED3, HIGH);   
    delay(1000);
  }else{
    digitalWrite(LED3, LOW);   

  }



}

void Get(){
  
  if (client.connect(server, port)){
    Serial.println("Connected to server... ");
    client.println("GET " + String(path) + " HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
  }

}

void Reset(){
  
  if (client.connect(server, port)){
    Serial.println("Connected to server... ");
    client.println("GET " + String(path) + " HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
  }

}

