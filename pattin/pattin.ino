#include <ESP8266WiFi.h>

#define SSID "Xperia XZ_9772"
#define PASSWORD "bdmbdmbdm"
#define WIFI_MAX_TRY 30

#define ServerIP "192.168.43.194"
#define ServerPort 3000

#define LED 15
#define TH 120

//--- utility
#define Log(x) Serial.print(x);
#define Logln(x) Serial.println(x);

extern "C" {
#include "user_interface.h"
}

int prev_z = 0;

bool isPattin(){
  int z = system_adc_read();
  int d_z = z - prev_z;
  prev_z = z;
  Serial.print(z);
  Serial.print(",");
  Serial.print(d_z);
  Serial.println(",");
  if (d_z < -TH || TH < d_z ){
    return true;
  }
  return false;
}

void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  if(WiFiSetup(SSID,PASSWORD) == false){
    light(100);
    delay(100);
    light(100);
    Serial.println("owari");
  }
  light(1000);
}

void loop() {
  if(isPattin()){
    WiFiClient client;
    if(!client.connect(ServerIP,ServerPort)){
      Serial.println("connection failed");
      return;
    }

    String url = "/";
    Serial.print("Requesting URL: ");
    Serial.println(url);

    //HTTP通信をする
    //client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    client.print(String("GET ") + url + " HTTP/1.1\r\n");
    client.stop();
    Serial.print("send!");
    light(100);
  }
  delay(50);
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

void light(int time){
  digitalWrite(LED,HIGH);
  delay(time);
  digitalWrite(LED,LOW);
}
