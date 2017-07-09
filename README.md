# WifiMoodLamp

Control a Mood Lamp (RGB Leds) through WIFI using Arduino, Esp8266-01 and Android app

*This project is under development*

**Dependences**

https://github.com/electronicdrops/MoodLamp

https://github.com/esp8266/Arduino


This module will be part of a project called SHOFE (Smart Home for Everyone).

Parts:
  -Esp8266-01: it is a wifi brigde, that receives the connection, and through it serial send a JSON to Arduino in a form: 
  
  ```javascript
  { "uri":"/rgb/", "params":{"color":120, "brightness":100}}
  ```
  
  -Arduino: it is the lamp controller. Receives the json strings, decode and modify its pwm ports to change the lamp color
  
  -Android app: conect to the esp8266 and send the request. **Under development**
  
  
  
