pin=8 
spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, spi.DATABITS_8, 0);
gpio.mode(pin, gpio.OUTPUT)


srv=net.createServer(net.TCP) 
srv:listen(80,function(conn) 
    conn:on("receive",function(conn,payload) 
    --print(payload) 

    gpio.write(pin, gpio.HIGH)
    tmr.delay(30)
    gpio.write(pin, gpio.LOW)
    tmr.delay(1)

    read1 = spi.recv(1, 1)
    read2 = spi.recv(1, 1)

    -- optional diagnostics
    --print(string.byte(read1) )
    --print(string.byte(read2) )
    --print(string.byte(read2) + string.byte(read1) * 256)
  
    temperature = (string.byte(read2) + string.byte(read1) * 256)/32
    --print((string.byte(read2) + string.byte(read1) * 256)/32)

    gpio.write(pin, gpio.HIGH)

    conn:send("<h1> Temperature is " .. temperature  .. " !!</h1>")
    conn:close()
	end) 
end)
          

