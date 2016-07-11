pin=8 
spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
gpio.mode(pin, gpio.OUTPUT)

gpio.write(pin, gpio.HIGH)
tmr.delay(30)
gpio.write(pin, gpio.LOW)
tmr.delay(1)

read1 = spi.recv(1, 1)

read2= spi.recv(1, 1)
print(string.byte(read1) )
print(string.byte(read2) )

print(string.byte(read2) + string.byte(read1) * 256)
print(string.byte(read1) + string.byte(read2) * 256)

print((string.byte(read2) + string.byte(read1) * 256)/32)

gpio.write(pin, gpio.HIGH)
tmr.delay(100)
