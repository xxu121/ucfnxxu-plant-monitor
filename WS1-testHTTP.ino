/*
 *  Simple HTTP get webclient test
 *  Code from Duncan Wilson 
 *  Oct 2023
 */


#include <ESP8266WiFi.h>

// use WIFI passward & SSID of ce-student one
const char* ssid     = "xxx";
const char* password = "xxx";
const char* host = "iot.io";


void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.println("-------------------------------");
  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(host + url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  delay(500);

 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  delay(1000000);
  
}
