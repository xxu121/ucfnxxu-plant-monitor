#include <ESP8266WiFi.h>
#include <ezTime.h>
//ssid & password same to the test wifi one
const char* ssid     = "ssid here";
const char* password = "your password here";

Timezone GB;
// time here is in milliseconds
void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network and same to previous one
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
// eztime function called waitForSync which facilitates the establishment of a connection with an NTP server
  waitForSync();

  Serial.println("UTC: " + UTC.dateTime());
  

  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());  

}

void loop() {
  delay(1000);
  Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
}
