#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal.h>


const int flame = A0; 
const int REDLED = D1;
const int GREENLED = D2;
const int rs = D0, en = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Your threshold value
const int sensorThres = 700;


const char* ssid = "Rahul";
const char* password = "qwerty123";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;


void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Smoke Level");
  
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(flame,INPUT);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

while(1>0)
{
  int analogSensor = analogRead(flame);

  Serial.print("SMOKE LEVEL: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor <300)
  {
    lcd.setCursor(0, 1);
    lcd.print("is in Safe Mode");
  }
  if (analogSensor <320 && analogSensor >=300)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 310         ");
  }
  if (analogSensor <340 && analogSensor >=320)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 330         ");
  }
   if (analogSensor <360 && analogSensor >=340)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 350         ");
  }
   if (analogSensor <380 && analogSensor >=360)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 370         ");
  }
   if (analogSensor <400 && analogSensor >=380)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 390         ");
  }
   if (analogSensor <420 && analogSensor >=400)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 410         ");
  }
   if (analogSensor <440 && analogSensor >=420)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 430         ");
  }
   if (analogSensor <460 && analogSensor >=440)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 450         ");
  }
   if (analogSensor <480 && analogSensor >=460)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 470         ");
  }
  if (analogSensor <500 && analogSensor >=480)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 490         ");
  }
  if (analogSensor <520 && analogSensor >=500)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 510         ");
  }
  if (analogSensor <540 && analogSensor >=520)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 530         ");
  }
   if (analogSensor <560 && analogSensor >=540)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 550         ");
  }
   if (analogSensor <580 && analogSensor >=560)
  {
    lcd.setCursor(0, 1);
    lcd.print("is 570         ");
  }
  if (analogSensor >=580)
  {
    lcd.setCursor(0, 1);
    lcd.print("is in DANGER!  ");
  }
  
  if (analogSensor > sensorThres)
  {
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED, LOW);
    WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  client.setInsecure();
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/trigger/Fire/with/key/c-w2MwnCBRZ3J90p3vsn_";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');

  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  break;
}
  else
  {
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, HIGH);
  }
  delay(100);
}
}
void loop(){}
