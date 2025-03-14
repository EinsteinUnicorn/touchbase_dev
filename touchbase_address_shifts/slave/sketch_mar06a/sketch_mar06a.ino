/* ============================
 *  ATtiny (I2C Slave Device)
 * ============================ */
#include <Wire.h>
#include <avr/eeprom.h>

#define DEFAULT_ADDR 0x08 // Default address before assignment
#define ID_PIN PB3  

int LED_PIN = 1;

uint8_t i2cAddress;
uint16_t adcID;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // Ensure LED is always on
    adcID = readADC();
    i2cAddress = eeprom_read_byte((uint8_t*)0);
    
    if (i2cAddress < 0x10 || i2cAddress > 0x7F) {
        i2cAddress = DEFAULT_ADDR;
    }
    
    Wire.begin(i2cAddress);
    Wire.onRequest(sendID);
    Wire.onReceive(receiveNewAddress);
}

void loop() {
    // Nothing required here; event-driven I2C handling
}

uint16_t readADC() {
    ADMUX = (1 << REFS0) | (ID_PIN & 0x07); // Select ADC channel PB3
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS1) | (1 << ADPS2);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

void sendID() {
    Wire.write(lowByte(adcID));
    Wire.write(highByte(adcID));
}

void receiveNewAddress(int numBytes) {
    if (numBytes == 1) {
        i2cAddress = Wire.read();
        eeprom_write_byte((uint8_t*)0, i2cAddress);
        Wire.end();
        Wire.begin(i2cAddress);
    }
}
