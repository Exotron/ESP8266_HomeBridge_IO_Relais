#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WifiSettings.h"

#define led_built_in_ESP 2
#define led_built_in_Node 16

#define RELAIS_MAIN 14
#define RELAIS_80 12
#define RELAIS_105 13
#define RELAIS_130 15
#define RELAIS_160 3
#define RELAIS_230 1


//***********************************************************//
//                                                           //
//                                                           //
//***********************************************************//
void setRelaisAsOutput()
{
  pinMode(RELAIS_MAIN, OUTPUT);
  pinMode(RELAIS_80, OUTPUT);
  pinMode(RELAIS_105, OUTPUT);
  pinMode(RELAIS_130, OUTPUT);
  pinMode(RELAIS_160, OUTPUT);
  pinMode(RELAIS_230, OUTPUT);
}

void setup() 
{
 setRelaisAsOutput();     //Setze den pinMode für die vorgesehenen Relais
 WiFi.begin(WIFI_SSID,WIFI_PASSWD);
 WiFi.setAutoReconnect(true);

pinMode(led_built_in_ESP, OUTPUT);
pinMode(led_built_in_Node,OUTPUT);

}

void loop()
{
 if(WiFi.isConnected() == false)
 {
   digitalWrite(RELAIS_MAIN,LOW);
   digitalWrite(RELAIS_230,LOW);
      digitalWrite(led_built_in_Node,LOW);
   digitalWrite(led_built_in_ESP,LOW);
 }
 else
 {
   digitalWrite(led_built_in_Node,LOW);
   digitalWrite(led_built_in_ESP,HIGH);
 }
}