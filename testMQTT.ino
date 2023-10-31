/*
 *  Code from Duncan Wilson 
 *  OCT 2023
 *  
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wifi and MQTT
#include "arduino_secrets.h" 


const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;

const char* mqtt_server = "mqtt.cetools.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  
  // We setup an LED to be controllable via MQTT
  // Initialize the BUILTIN_LED pin as an output 
  // Turn the LED off by making the voltage HIGH
  // turn the LED on and off via MQTT and initialise the MQTT client
  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH);  

 
  Serial.begin(115200);
  delay(100); 

  startWifi();

  // 1884 for  using a username and password to connect to the broker
  client.setServer(mqtt_server, 1884);
  
  client.setCallback(callback);

}

void loop() {
  delay(5000);
  sendMQTT();
}


// This function is used to set-up the connection to the wifi
void startWifi(){
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//reconnect function called above is a while loop that repeats until the client is connected
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and subscribe to messages on broker
      client.subscribe("student/CASA0014/plant/ucjtdjw/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


// Create a new function called sendMQTT
void sendMQTT() {
  //if statement checks to see if a connection has already been established to the MQTT server and if not it creates one
  if (!client.connected()) {
    reconnect();
  }
  //loop functions checks to see if any new messages have been received by the client
  client.loop();
  //value keep track of how many messages have been sent to the server
  ++value;
  snprintf (msg, 50, "hello world #%ld", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucjtdjw", msg);

}

// The callback function is called when an incoming message is received

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
