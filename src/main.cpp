#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WifiSettings.h"
#include "Lufter.h"

#define led_built_in_ESP 2
#define led_built_in_Node 16

#define RELAIS_MAIN 14
#define RELAIS_80 12
#define RELAIS_105 13
#define RELAIS_130 15
#define RELAIS_160 3
#define RELAIS_230 1

#define on 1
#define off 0

Lufter luft;

WiFiServer server(80);
void setRelaisAsOutput()
{
  pinMode(RELAIS_MAIN, OUTPUT);
  pinMode(RELAIS_80, OUTPUT);
  pinMode(RELAIS_105, OUTPUT);
  pinMode(RELAIS_130, OUTPUT);
  pinMode(RELAIS_160, OUTPUT);
  pinMode(RELAIS_230, OUTPUT);
}

String Weboutput(int status)
{
  String output;
  output += "http/1.x 200 OK\n";
  output += "Content-Type: text/html; charset=UTF-8\n\n";
  output += "<!DOCTYPE HTML>";
  output += "<html>";
  switch (status)
  {
  case 0:
    output += "<h1>Luftkiste: AUS</h1>";
    break;
  case 80:
    output += "<h1>Luftkiste: 80V</h1>";
    break;
  case 105:
    output += "<h1>Luftkiste: 105V</h1>";
    break;
  case 130:
    output += "<h1>Luftkiste: 130V</h1>";
    break;
  case 160:
    output += "<h1>Luftkiste: 160V</h1>";
    break;
  case 230:
    output += "<h1>Luftkiste: 230V</h1>";
    break;
  default:
    output += "<h1>Luftkiste: Falscher Wert</h1>";
    break;
  }

  output += "<form action=\"\" method=\"GET\">";
  output += "<button name=\"mode\" value=\"0\">AUS</button>";
  output += "<br><br>";
  output += "<button name=\"mode\" value=\"80\">80V</button>";
  output += "<br><br>";
  output += "<button name=\"mode\" value=\"105\">105V</button>";
  output += "<br><br>";
  output += "<button name=\"mode\" value=\"130\">130V</button>";
  output += "<br><br>";
  output += "<button name=\"mode\" value=\"160\">160V</button>";
  output += "<br><br>";
  output += "<button name=\"mode\" value=\"230\">230V</button>";
  output += "</form>";
  output += "</html>";
  return output;
}

void allRelaisOff()
{
  digitalWrite(RELAIS_MAIN, off);
  digitalWrite(RELAIS_230, off);
  digitalWrite(RELAIS_80, off);
  digitalWrite(RELAIS_105, off);
  digitalWrite(RELAIS_130, off);
  digitalWrite(RELAIS_160, off);
  delay(100);
}

void setup()
{
  setRelaisAsOutput(); //Setze den pinMode für die vorgesehenen Relais
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  WiFi.setAutoReconnect(true);
  delay(1000);
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();
  int tryConnect = 1;

  while (WiFi.isConnected() == false)
  {
    delay(500);
    if (tryConnect >= 60)
    {
      allRelaisOff();
      luft.setState(0);
      return;
    }
    tryConnect++;
  }
  if (!client)
  {
    return;
  }
  String request = client.readStringUntil('\r');
  client.flush();

  if (request == "")
  {
    client.stop();
    return;
  }

  //GPIOS schalten
  if (request.indexOf("mode=0") >= 0)
  {
    digitalWrite(led_built_in_Node, on);
    luft.setState(0);
    allRelaisOff();
  }
  else if (request.indexOf("mode=80") >= 0)
  {
    luft.setState(80);
    allRelaisOff();
    digitalWrite(RELAIS_80, on);
    digitalWrite(RELAIS_MAIN, on);
    digitalWrite(led_built_in_Node, off);
  }
  else if (request.indexOf("mode=105") >= 0)
  {
    luft.setState(105);
    allRelaisOff();
    digitalWrite(RELAIS_105, on);
    digitalWrite(RELAIS_MAIN, on);
    digitalWrite(led_built_in_Node, off);
  }
  else if (request.indexOf("mode=130") >= 0)
  {
    luft.setState(130);
    allRelaisOff();
    digitalWrite(RELAIS_130, on);
    digitalWrite(RELAIS_MAIN, on);
    digitalWrite(led_built_in_Node, off);
  }
  else if (request.indexOf("mode=160") >= 0)
  {
    luft.setState(160);
    allRelaisOff();
    digitalWrite(RELAIS_160, on);
    digitalWrite(RELAIS_MAIN, on);
    digitalWrite(led_built_in_Node, off);
  }
  else if (request.indexOf("mode=230") >= 0)
  {
    luft.setState(230);
    allRelaisOff();
    digitalWrite(RELAIS_230, on);
    digitalWrite(led_built_in_Node, off);
  }

  //Ausgabe erzeugen
  client.print(Weboutput(luft.getState()));
  client.stop();
}