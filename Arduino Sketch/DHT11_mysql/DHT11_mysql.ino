
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>


#define DHTPIN D1

#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


float humidityData;
float temperatureData;


const char* ssid = "INSERT_YOUR_SSID_HERE";
const char* password = "INSERT_YOUR_PASSWORD_HERE";

char server[] = "INSERT_THE_IP_ADDRESS_HERE";   


WiFiClient client;    


void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
;
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(30000); 
 }

 void Sending_To_phpmyadmindatabase()   
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /DHT11test/fetch.php?humidity=");
    client.print("GET /DHT11test/fetch.php?humidity=");     
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print(" ");      
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.0.104");
    client.println("Connection: close");
    client.println();
  } else {

    Serial.println("connection failed");
  }
 }
