# ucfnxxu-plant-monitor
Plant Monitor

# Overview

This provides a summary of how to employ an Arduino to create a plant monitoring system capable of measuring moisture, humidity, and temperature levels.

## workshop 1
Familiar with Arduino and test blinking, connect to wifi, and getting current time.
1. Launch the Arduino IDE and plug in the Huzzah (got an adaptor)
2. Install the CP2104 driver and the board package
3. Install the ESP8266 Board Package using "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in url
4. Set the Tools -> Board -> "Adafruit Feather HUZZAH ESP8266", 80 MHz as the CPU frequency, 115200 baud for Upload speed, "SLAB_USBtoUART" for port
5. Use the code for blinkling test and if it success (generally success), and go straigt to connecting web server. Code can be find in [WS1-testHTTP.ino](/WS1-testHTTP.ino/) and it explain why we print a . to the Serial monitor.
6. Use code of eztime from the libray and create a Timezone instance called GB. Code can be find in [eztime.ino](/eztime.ino/). After upload in the ESP8266 the serial monitor should produce time in seconds every 1000 millisecond.

## workshop 2
After testing, sharing data in a public area through MQTT allow checking data with others or read others plant situation.
1. A library called "arduino_secrets.h" include wifi ssid & password, and MQTT student user details will be remember. "#include "arduino_secrets.h"" allows us to use data in this library.
2. Follow the code [testMQTT.ino](/testMQTT.ino/) and change the personal id will prepare sending message to MQTT.
3. Publish "student/CASA0014/plant/ucxxxxx/inTopic" in raw and the message will shown. A payload of 1 to publish, causing the built-in LED on the Huzzah to illuminate. Then, change the payload to 0 and publish again to turn the light off.
4. Soild the resistance to test moisture as High moisture leads lower resistance. Solid the DHT22 sensor to measure the temperature and humidity. Use the code [testMoisture.ino](/testMoisture.ino/). The serial plotter will give data flowing img shows like:.<img width="662" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/ce576df6-788b-4667-8c5f-272127ca558a">

