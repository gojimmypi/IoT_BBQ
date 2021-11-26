/*
  wiring_shift.c - shiftOut() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  Adapted from https://github.com/arduino/ArduinoCore-avr/blob/9f8d27f09f3bbd1da1374b5549a82bda55d45d44/cores/arduino/wiring_shift.c
  by gojimmypi
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include <sys/_stdint.h>
#include <stm32l4xx_hal.h>
#define HIGH 0x1
#define LOW  0x0
#define LSBFIRST 0
#define MSBFIRST 1


uint8_t shiftIn(uint16_t dataPin, uint16_t clockPin, uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        //digitalWrite(clockPin, HIGH);
        HAL_GPIO_WritePin(GPIOB, clockPin, GPIO_PIN_SET);
        
        if (bitOrder == LSBFIRST)
            //value |= digitalRead(dataPin) << i;
        value |= HAL_GPIO_ReadPin(GPIOB, dataPin) << i;
        
        else
            value |= HAL_GPIO_ReadPin(GPIOB, dataPin)  << (7 - i);
        // digitalWrite(clockPin, LOW);
        HAL_GPIO_WritePin(GPIOB, clockPin, GPIO_PIN_RESET);
    }
    return value;
}

GPIO_PinState PinStateOf(int v)
{
    if (v == 0)
    {
        return GPIO_PIN_RESET;
    }
    else
    {
        return GPIO_PIN_SET ;
    }
}

void shiftOut(uint16_t dataPin, uint16_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++) {
        if (bitOrder == LSBFIRST) {
            // digitalWrite(dataPin, val & 1);
            HAL_GPIO_WritePin(GPIOB, dataPin, PinStateOf(val & 1));
            val >>= 1;
        }
        else {	
            // digitalWrite(dataPin, (val & 128) != 0);
            HAL_GPIO_WritePin(GPIOB, dataPin, PinStateOf((val & 128) != 0));
            val <<= 1;
        }
		
        //digitalWrite(clockPin, HIGH);
        //digitalWrite(clockPin, LOW);		
        HAL_GPIO_WritePin(GPIOB, clockPin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, clockPin, GPIO_PIN_RESET);
    }
}