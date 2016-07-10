# IoT_BBQ
ESP8266 Based Temperature and Propane Tank Weight Project

First you need a NodeMCU ESP8266 like this one:

http://www.ebay.com/itm/400999083640

Note it has a CH340G USB chip, so works well with Windows 10

Next, download flasher from https://github.com/nodemcu/nodemcu-flasher

In the \Resources\Binaries directory, there are Lua formware images (one support floats, the other only ints)

Once you've uploaded the image, this tool can be helpful for getting Lua code onto your device:

http://benlo.com/esp8266/ 

You can read more about NodeLUA here: https://nodelua.org/

Next, you will need a MAX6675 Module + K Type Thermocouple Temperature Sensor like this one: 

http://www.ebay.com/itm/400798924042

see this respository for spec sheet on MAX6675, or visit 

https://datasheets.maximintegrated.com/

Note that for connection to the ESP8266, you'll need to pull CS down to ground with a 10k resistor so the ESP8266 will boot.

I soldered a resistor on the board between those pins.



