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


