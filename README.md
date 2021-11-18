
The Imaginary Embedded System that does not exist for the _Making Embedded Systems_ class is the Barbeque Grill 
monitoring system project started (and abandoned) 5 years ago as noted below that was intially tinkered with using
an ESP8266 an the `LUA` language, but never completed. 

The `IoT_BBQ` system is a monitoring device to primarily measure the weight of the propane tank to ensure that
when it is time to cook, that the fuel supply is not nearly empty. Having an electronic scale monitoring the weight
is much more precise, accurate, and convenient as compared to the mechanical spring scales. A custom solution is also 
needed as the amount of available physical space is so limited, that even a bathroom scale is not practical for both 
size and viewing angle.

A premium version of this system will also include internal grill box temperature, as well as various atmospheric sensors, 
such as ambient temperature and pressure. 

Some sort of information display will be needed: either a local LCD panel and/or a web interface.

Components needed include:

- Controller board
- Power Supply
- Load cell (weight sensor)
- Temperature sensor
- Other atmospheric sensors
- Enclosure
- Mounting hardware

# Diagram:

![image](https://user-images.githubusercontent.com/13059545/142352018-6cc0b29a-dc3a-40f1-bdc3-9d5999a4fc22.png)



My original README follows:

# IoT_BBQ
ESP8266 Based Grill Temperature and Propane Tank Weight Project

First you need a NodeMCU ESP8266 like this one:

http://www.ebay.com/itm/400999083640

Note it has a CH340G USB chip, so works well with Windows 10

![Windows Device Manager](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/Windows10_DeviceManager_CH340.JPG)

Next, download flasher from https://github.com/nodemcu/nodemcu-flasher

In the \Resources\Binaries directory, there are Lua firmware images (one support floats, the other only ints)

![config setting](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/Programmer_Config.jpg)

Once you've uploaded the image, this tool can be helpful for getting Lua code onto your device:

http://benlo.com/esp8266/ 

You can read more about NodeLUA here: https://nodelua.org/

Next, you will need a MAX6675 Module + K Type Thermocouple Temperature Sensor like this one: 

http://www.ebay.com/itm/400798924042

see this respository for spec sheet on MAX6675, or visit 

https://datasheets.maximintegrated.com/

Note that for connection to the ESP8266, you'll need to pull CS down to ground with a 10k resistor so the ESP8266 will boot.

I soldered a resistor on the board between those pins.

![soldered resistor](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/resistor.jpg)

Connect your thermocouple to the ESP8266 (see pics for pinout)

![board wiring](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/board.jpg)

Once everything is connected, setup ESP8266 to connect to WiFi. 

```Lua
wifi.setmode(wifi.STATION)
wifi.sta.config("yourWiFiName","yourWifFiPassword")
wifi.sta.connect()
```

Consider security issues of hard coding password. You can configure once & ESP8266 will remember after reboot.

Next, find your device on the local network segment. For this, I use fing:

https://play.google.com/store/apps/details?id=com.overlook.android.fing&hl=en

![fing](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/fing.jpg)

Once you find the device, click on it, and scan for open ports. You should have port 80 open:

![fing scan](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/fing-scan.jpg)

If you found the ESP8266 on your network, upload the thermocouple.lua file:

![thermocouple.lua upload](https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/upload_thermocouple.jpg)

If everything is working, you'll see the temperature on your phone! (temperature shown in Celsius)

![webpage sample]( https://github.com/gojimmypi/IoT_BBQ/blob/master/pics/webpage.jpg)

Load the file in init.lua to maintain web server operations after a reboot. I found that it is best to delete the init.lua file, reboot, then load a fresh init.lua when making changes. Again, fing is handy for detecting port 80 being open or not.

Next weekend, I will work on adding the weight sensor. I used one like this:

20KG Scale Load Cell Weight Weighing Sensor +HX711 Weighing Sensors AD Module 

http://www.ebay.com/itm/281916193412

feedback, comments, suggestions? contact me at gmail or twitter.


