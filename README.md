# ucfnxxu-plant-monitor
Plant Monitor

# Overview

This provides a summary of how to employ an Arduino to create a plant monitoring system capable of measuring moisture, humidity, and temperature levels.

## workshop 1
1. Launch the Arduino IDE and plug in the Huzzah (got an adaptor)
2. Install the CP2104 driver and the board package
3. Install the ESP8266 Board Package using "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in url
4. Set the Tools -> Board -> "Adafruit Feather HUZZAH ESP8266", 80 MHz as the CPU frequency, 115200 baud for Upload speed, "SLAB_USBtoUART" for port
5.
6. void setup() {
  pinMode(0, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  delay(500);
}
