//#include <ESPmDNS.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#define SSID "Xperia XZ_9772"
#define PASSWORD "bdmbdmbdm"
#define WIFI_MAX_TRY 30

#define LED 15

//--- utility
#define Log(x) Serial.print(x);
#define Logln(x) Serial.println(x);

ESP8266WebServer server(80);

void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  Serial.println("setup");
  if(WiFiSetup(SSID,PASSWORD) == false){
    Serial.println("owari");
  }
  Serial.println("wifi begin");
  delay(200);
  digitalWrite(LED,LOW);

  serverSetUp();
}

void loop() {
  server.handleClient();
}

boolean WiFiSetup(char* ssid,char* password){
  delay(10);
  Log("Connection to ");
  Logln(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  for(int i = 0;(WiFi.status() != WL_CONNECTED) && i < WIFI_MAX_TRY;i++){
    delay(500);
    Log(".");
  }
  if(WiFi.status() != WL_CONNECTED){
    light(500);
    delay(500);
    light(500);
    return false;
  }

  Logln("");
  Logln("WiFi connected");
  Log("IP address: ");
  Logln(WiFi.localIP());

  light(1000);

  return true;
}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
  Serial.println("received");
  light(1000);
}

void serverSetUp(){
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server Started");
}

void light(int time){
  digitalWrite(LED,HIGH);
  delay(time);
  digitalWrite(LED,LOW);
}
