/**
 *
 * HX711 library for Arduino
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 * 
 * adapted to stm32l4xx_hal 
 * by gojimmypi 2021
 * 
**/
#include "HX711.h"
#include "DWT_STM32_DELAY.h"
#include "wiring_shift.c"

#define USE_FLASH_CONFIG



// Whether we are actually running on FreeRTOS.
// #define IS_FREE_RTOS moved to common/globals

// Define macro designating whether we're running on a reasonable
// fast CPU and so should slow down sampling from GPIO.
#define FAST_CPU 


#ifdef USE_FLASH_CONFIG
#include "Flash/flash_config.h"
#endif // USE_FLASH_CONFIG


//#if FAST_CPU
//// Make shiftIn() be aware of clockspeed for
//// faster CPUs like ESP32, Teensy 3.x and friends.
//// See also:
//// - https://github.com/bogde/HX711/issues/75
//// - https://github.com/arduino/Arduino/issues/6561
//// - https://community.hiveeyes.org/t/using-bogdans-canonical-hx711-library-on-the-esp32/539
//uint8_t shiftInSlow(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
//    uint8_t value = 0;
//    uint8_t i;
//
//    for (i = 0; i < 8; ++i) {
//        digitalWrite(clockPin, HIGH);
//        delayMicroseconds(1);
//        if (bitOrder == LSBFIRST)
//            value |= digitalRead(dataPin) << i;
//        else
//            value |= digitalRead(dataPin) << (7 - i);
//        digitalWrite(clockPin, LOW);
//        delayMicroseconds(1);
//    }
//    return value;
//}

HX711::HX711() {
    
#ifdef USE_FLASH_CONFIG
    // read from Flash directly as we only new this at initialization time
    OFFSET = DeviceCacheConfig(NoSave)->SCALE_OFFSET;

//    if (FlashNeedsUpdate() > 0)
//    {
//        // TODO check for save errors
//        SaveDeviceConfig();
//    }
#endif // USE_FLASH_CONFIG

}

HX711::~HX711() {
}

void HX711::begin(uint16_t dout, uint16_t pd_sck, byte gain) {

    // FreeRTOS API functions must not be called from within a critical section.
    portENTER_CRITICAL();
    
    // TODO don't override!
    PD_SCK = GPIO_PIN_2; //  ARD.D8 = PB2  0x0004 Gray
    DOUT = GPIO_PIN_15;  //  ARD.D9 = PA15 0x8000 White
    

    // pinMode(PD_SCK, OUTPUT);
    GPIO_InitTypeDef GPIO_InitStructureB;
    GPIO_InitStructureB.Pin = GPIO_PIN_2;

    GPIO_InitStructureB.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureB.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);

    // GPIOA DOUT
    GPIO_InitTypeDef GPIO_InitStructureA;
    GPIO_InitStructureA.Pin = GPIO_PIN_15;
    GPIO_InitStructureA.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructureA.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureA.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructureA);
    portEXIT_CRITICAL();

    power_up();
    
//    HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_RESET);        
//    HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_SET);
//
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);        
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    
    set_gain(gain);
    
}

bool HX711::is_ready() {
    
#ifdef IS_FREE_RTOS
    portENTER_CRITICAL();
#endif
    // TODO we won't always be on GPIOA
    bool res = HAL_GPIO_ReadPin(GPIOA, DOUT) == LOW; // return digitalRead(DOUT) == LOW;

#ifdef IS_FREE_RTOS
    portEXIT_CRITICAL();  
#endif
    return res;
}

void HX711::set_gain(byte gain) {
    switch (gain) {
    case 128:		// channel A, gain factor 128
        GAIN = 1;
        break;
    case 64:		// channel A, gain factor 64
        GAIN = 3;
        break;
    case 32:		// channel B, gain factor 32
        GAIN = 2;
        break;
    }

}

uint8_t shiftIn(uint16_t dataPin, uint16_t clockPin, uint8_t bitOrder); // see https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h


long HX711::read() {

    // Wait for the chip to become ready.
    wait_ready();

    // Define structures for reading data into.
    unsigned long value = 0;
    uint8_t data[3] = { 0 };
    uint8_t filler = 0x00;

    // Protect the read sequence from system interrupts.  If an interrupt occurs during
    // the time the PD_SCK signal is high it will stretch the length of the clock pulse.
    // If the total pulse time exceeds 60 uSec this will cause the HX711 to enter
    // power down mode during the middle of the read sequence.  While the device will
    // wake up when PD_SCK goes low again, the reset starts a new conversion cycle which
    // forces DOUT high until that cycle is completed.
    //
    // The result is that all subsequent bits read by shiftIn() will read back as 1,
    // corrupting the value returned by read().  The ATOMIC_BLOCK macro disables
    // interrupts during the sequence and then restores the interrupt mask to its previous
    // state after the sequence completes, insuring that the entire read-and-gain-set
    // sequence is not interrupted.  The macro has a few minor advantages over bracketing
    // the sequence between `noInterrupts()` and `interrupts()` calls.
    //
#ifdef IS_FREE_RTOS
        // Begin of critical section.
        // Critical sections are used as a valid protection method
        // against simultaneous access in vanilla FreeRTOS.
        // Disable the scheduler and call portDISABLE_INTERRUPTS. This prevents
        // context switches and servicing of ISRs during a critical section.
        // portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
        portENTER_CRITICAL();
#else
        // Disable interrupts.
        noInterrupts();
#endif

        // Pulse the clock pin 24 times to read the data.
        data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);
        data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
        data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);

        // Set the channel and the gain factor for the next reading using the clock pin.
        for (unsigned int i = 0; i < GAIN; i++) {
            HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_SET); // digitalWrite(PD_SCK, HIGH);
            
            
#ifdef ARCH_ESPRESSIF
            DWT_Delay_us(2);  // WARNING! Hard, non-RTOS Delay // delayMicroseconds(1);
#else
            DWT_Delay_us(1);
#endif

            HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_RESET); // digitalWrite(PD_SCK, LOW);


#ifdef ARCH_ESPRESSIF
            DWT_Delay_us(2); // WARNING! Hard, non-RTOS Delay // delayMicroseconds(1);
#else
            DWT_Delay_us(1);
#endif
        }
#ifdef IS_FREE_RTOS
   // End of critical section.
   portEXIT_CRITICAL();
    
#else
// Enable interrupts again.
    interrupts();
#endif

    // Replicate the most significant bit to pad out a 32-bit signed integer
    if (data[2] & 0x80) {
        filler = 0xFF;
    }
    else {
        filler = 0x00;
    }

    // Construct a 32-bit signed integer
    value = (static_cast<unsigned long>(filler) << 24
    		| static_cast<unsigned long>(data[2]) << 16
    		| static_cast<unsigned long>(data[1]) << 8
    		| static_cast<unsigned long>(data[0]));

    return static_cast<long>(value);
}

void HX711::wait_ready(unsigned long delay_ms) {
    // Wait for the chip to become ready.
    // This is a blocking implementation and will
    // halt the sketch until a load cell is connected.
    while (!is_ready()) {
        // Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
        // https://github.com/bogde/HX711/issues/73
        
        osDelay((TickType_t)(10 / portTICK_PERIOD_MS));
        // TODO what if it is never ready? see wait_ready_timeout()
    }
}

bool HX711::wait_ready_retry(int retries, unsigned long delay_ms) {
    // Wait for the chip to become ready by
    // retrying for a specified amount of attempts.
    // https://github.com/bogde/HX711/issues/76
    int count = 0;
    while (count < retries) {
        if (is_ready()) {
            return true;
        }
        osDelay((TickType_t)((1000 * delay_ms) / portTICK_PERIOD_MS)); //  DWT_Delay_us(1000 * delay_ms); // delay(delay_ms);
        count++;
    }
    return false;
}

bool HX711::wait_ready_timeout(unsigned long timeout, unsigned long delay_ms) {
    // Wait for the chip to become ready until timeout.
    // https://github.com/bogde/HX711/pull/96
    unsigned long millisStarted = 0;
    unsigned long millis = 0;
    while (millis - millisStarted < timeout) {
        if (is_ready()) {
            return true;
        }
        millis += 1000 * delay_ms;
        osDelay((TickType_t)((1000 * delay_ms) / portTICK_PERIOD_MS)); // DWT_Delay_us(1000 * delay_ms); // delay(delay_ms);
    }
    return false;
}

long HX711::read_average(byte times) {
    long sum = 0;
    for (byte i = 0; i < times; i++) {
        sum += read();
        // Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
        // https://github.com/bogde/HX711/issues/73
        // 
        // DWT_Delay_us(1); // WARNING! Hard, non-RTOS Delay
        osDelay((TickType_t)(1));
    }
    return sum / times;
}

double HX711::get_value(byte times) {
    return read_average(times) - OFFSET;
}

float HX711::get_units(byte times) {
    return get_value(times) / SCALE;
}

void HX711::tare(byte times) {
    double sum = read_average(times);
    set_offset(sum);
}

void HX711::set_scale(float scale) {
    SCALE = scale;
}

float HX711::get_scale() {
    return SCALE;
}

void HX711::set_offset(long offset) {

#ifdef USE_FLASH_CONFIG
    // if Flash is enabled, update both the RAM cache as save to Flash
    SetScaleOffset( offset);
#endif // USE_FLASH_CONFIG

    OFFSET = offset;
    SaveDeviceConfig();
}

long HX711::get_offset() {
    return OFFSET;
}

void HX711::power_down() {
    
    portENTER_CRITICAL();
    HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_RESET); // digitalWrite(PD_SCK, LOW);
    DWT_Delay_us(2); // WARNING! Hard non-RTOS delay
    HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_SET); // digitalWrite(PD_SCK, HIGH);
    DWT_Delay_us(2); // WARNING! Hard, non-RTOS Delay
    portEXIT_CRITICAL();
}

void HX711::power_up() {
    // clock is low during power up mode
    portENTER_CRITICAL();
    HAL_GPIO_WritePin(GPIOB, PD_SCK, GPIO_PIN_RESET); // digitalWrite(PD_SCK, LOW);
    portEXIT_CRITICAL();
}
