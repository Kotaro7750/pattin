#include <WiFi.h>

#define PRESSURE 0
#define X 1
#define Y 2
#define Z 3

int prev_P = 0;
int prev_z = 0;

char* ssid = "bld2-guest";
char* password = "MatsumotoWay";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  pinMode(PRESSURE,INPUT);
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(Z,INPUT);
  pinMode(0,OUTPUT);
  digitalWrite(7,LOW);


  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  double p = analogRead(0);
  int x = analogRead(1);
  int y = analogRead(2);
  int z = analogRead(3);

  int d_p = p - prev_P;
  int d_z = z - prev_z;

  if(d_p < -100){
    digitalWrite(7,HIGH);
    delay(1000);
  }
  digitalWrite(7,LOW);
  
  Serial.print(p);
  Serial.print(",");
  //Serial.print(x);
  //Serial.print(",");
  //Serial.print(y);
  //Serial.print(",");
  //Serial.print(z);
  Serial.print(d_p);
  Serial.print(",");
  Serial.print(d_z);
  Serial.println(",");
  prev_P = p;
  prev_z = z;
  delay(50);
}
