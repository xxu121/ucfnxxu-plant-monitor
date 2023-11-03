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
4. Soldering the resistance to test moisture as High moisture leads lower resistance. Solid the DHT22 sensor to measure the temperature and humidity. Use the code [testMoisture.ino](/testMoisture.ino/). The serial plotter will give data flowing img shows like:<img width="662" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/ce576df6-788b-4667-8c5f-272127ca558a"> (from workshop)
5. The programe from DHT library takes moisture and temperature/humidity readings and sends them to our MQTT server. Combine previous code, do a complete data setting for connecting all stuff. Furthermore, a red light illuminates to indicate a moisture level of 10 or higher, and a yellow light activates to signal a temperature below 25 degrees. It will test every 3000ms as it will be quicker show in crit.

This img shows the Moisture is less than 10 and the plant need to water, the temperature is suitable which is larger than 25 degrees.
![image](https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/dc573ad0-83c7-46e7-8ecb-010dc9063bee)

This image shows that both the temperature and the moisture is suitable for the plant. 
![image](https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/6bd1a01a-a30e-4e93-9037-d0c9c69938c9)
Code can be find in [DHT22_MQTT.ino](/DHT22_MQTT.ino/). Also the graph shown in MQTT.

<img width="600" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/95c87d91-dc7e-46cb-95b1-5658a0557b14">

Solder the longer foot of the red LED to pin 14 and the longer lead of the yellow LED to pin 16. Connect the shorter foots of both LEDs to the GND (Ground).(add fig)

‘pinMode(14, OUTPUT);
pinMode(16, OUTPUT);’

The code added in void setup. The effect of these two lines is to configure pin 14 and pin 16 on the microcontroller as digital outputs. After executing these lines, it would be able to turn an LED on or off connected to these pins. 

'if(Temperature <= 25){
     digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else{
      digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
  }'
 
  Incorporated within the void loop() function, these extract of code produce the following behavior: if the temperature is 25 degrees or below, a HIGH digital signal is sent to the output (pin 16), causing the LED to illuminate. Conversely, if the temperature exceeds 25 degrees, a LOW digital signal is issued to the output (pin 16), turning the LED off.

  'if(Moisture < 10){
     digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else{
      digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
  }
  
}'

Within the void readMoisture() function, these lines of code function analogously to the temperature control mechanism. They utilise a HIGH or LOW output to toggle the LED's state. Specifically, if moisture levels are detected to be below 10, the LED is turned on. If the moisture level is above this threshold, the LED is turned off.

## workshop 3
1. Setting up a RPi as a gateway. Following the tutorial in https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up/2, use the institution wifi to connect the RPi and set user's own username and password.
2. Enter ssh username@stud-pi-casa0014.local in terminal. Here the username must the one setted or it will show permission denied.
'Use sudo apt update
sudo apt upgrade -y
sudo reboot' to do a quick update / upgrade to make sure all files are upto date and then reboot before moving on to installing the datastore.
4. All the below programming in terminal. Use 'sudo nano /etc/hostname' to update hostname, and repeat for hosts file 'sudo nano /etc/hosts'. In the hosts file it should to be edited the entry against 127.0.0.1 as '127.0.0.1 celab-pi-casa0014'. Use 'sudo reboot' for good measure, here I enter sudo reboot in my terminal and my computer reboot and I tried serveal times, it also command my computer not the RPi. REMEMBER 'sudo reboot' MUST ENTER AFTER SSH IN THE RPi OR IT WILL COMMAND THE COMPUTER DIRECTLY.
5. Installing InfluxDB on RPi use the code
   'wget -q https://repos.influxdata.com/influxdata-archive_compat.key
echo '393e8779c89ac8d958f81f942f9ad7fb82a25e133faddaf92e15b16e6ac9ce4c influxdata-archive_compat.key' | sha256sum -c && cat influxdata-archive_compat.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg > /dev/null

echo 'deb [signed-by=/etc/apt/trusted.gpg.d/influxdata-archive_compat.gpg] https://repos.influxdata.com/debian stable main' | sudo tee /etc/apt/sources.list.d/influxdata.list'

With the repository added now run another update to the package list 'sudo apt-get update'. Finally install InfluxDB 'sudo apt-get install influxdb2 -y'

Then the telegraf can be set and copy the API in case to clone another one.

6. Installing Telegraf on RPi.
'sudo apt-get update && sudo apt-get install telegraf -y'

'cat /etc/telegraf/telegraf.conf'

First up, define some PATH variables:

'export INFLUX_HOST=http://10.129.101.214:8086' The IP address can be found with the help of command 'ifconfig' 

'export INFLUX_ORG=casa0014'

Following the Load Data -> Telegraf -> 'setup instruction' step by step.

Three personal details, two token and bucket ='telegraf' should be change. Code from [plantMonitor/pi config/etc/telegraf/telegrafv2.conf](/telegraf). The mqtt-data can be visualise in influxdb.<img width="1188" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/1a0f1b56-596b-4f5f-87d0-57ff9c894bec">
<img width="1580" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/ec75f216-d1df-40d4-8932-b6559000a943">

7. Follow the instructions of Workshop step14. It now be able to browse to http://localhost:3000 and see the Grafana welcome page. The localhost should be changed into 'username@stud-pi-casa0014' used previously in RPi setting.
8. Visualising Data on Grafana. Add first datasource show as the figure below with all detail same. <img width="686" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/bfdf9325-3924-465d-b0ce-5f8f78320209">

9. Create a new dashboard, enter queries just like those used in the Dashboard for InfluxDB. <img width="1227" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/5302bac7-c98d-4da6-b259-e6d4a6fcad37"> Actural it, it would provide the graph of moisture, humidity, and temperature. Apply it, it will produce <img width="823" alt="image" src="https://github.com/xxu121/ucfnxxu-plant-monitor/assets/146341729/f4ee9779-3c5f-4956-8de3-d92826357a2b">


## Added function and Future prospects
A red and yellow LED used to test the moisture and temperature if they are not at a specific range. Only two LEDs due to not enough pin to add extra functions. If there's enough time I will link it to arduino to have two more buzzers to play different music, it will remind me if the temperature or moisture is not suitable for my plant.




