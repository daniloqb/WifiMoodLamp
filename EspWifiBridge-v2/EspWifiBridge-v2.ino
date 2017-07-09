#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>  

#define MAX_PARAMS 5

ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/plain", "");
}

void handleNotFound(){


  String message;
  String s;
  StaticJsonBuffer<200> jsonBuffer;

  
  JsonObject& root = jsonBuffer.createObject();
  root["uri"] = server.uri();

  JsonObject& params = root.createNestedObject("params");

  for (uint8_t i = 0; i < server.args(); i++){
    if (i > MAX_PARAMS) break;

    params[server.argName(i)] = server.arg(i);
  }

  root.printTo(message);
  //server.send(200, "application/json",message);


  while (Serial.available()) {
     char c = Serial.read();
   }

     
  Serial.println(message);


  long timeout = millis();

while(millis() - timeout < 400){
  if (Serial.available() > 0)
    break;
}

while (Serial.available()) {
     char c = Serial.read();
     if (isprint(c))
       s += c;
     delay(2);
  }

  s = s+'\n';


 Serial.flush();

server.send(200, "application/json",s);

s = String();

}

void setup(void){

  
    // put your setup code here, to run once:
  Serial.setRxBufferSize(1024);
  Serial.begin(9600);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    
    //if you get here you have connected to the WiFi
      Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );
 Serial.println("connected...yeey :)");


 server.on ( "/", handleRoot );
 server.onNotFound(handleNotFound);
 server.begin();
 Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();

}
