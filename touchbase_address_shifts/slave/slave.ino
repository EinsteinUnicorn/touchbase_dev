/* ============================
 *  ATtiny85 (I2C Slave Device)
 * ============================ */
#include <TinyWireS.h>
#include <avr/eeprom.h>

#define DEFAULT_ADDR 0x08  // Default I2C address
#define ID_PIN PB3         // ADC pin for reading the ID
#define LED_PIN PB1        // LED pin

int flag = 0;

uint8_t i2cAddress;
uint16_t adcID;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);  // Ensure LED is always on

    adcID = readADC();
    i2cAddress = eeprom_read_byte((uint8_t*)0);
    
    if (i2cAddress < 0x10 || i2cAddress > 0x7F) {
        i2cAddress = DEFAULT_ADDR;
    }
    
    TinyWireS.begin(i2cAddress);
    TinyWireS.onRequest(sendID);
    TinyWireS.onReceive(receiveNewAddress);
}

void loop() {
    TinyWireS_stop_check();  // Required for TinyWireS to function properly
}

// Read ADC value from ID_PIN
uint16_t readADC() {
    ADMUX = (1 << REFS0) | (ID_PIN & 0x07); // Select ADC channel PB3
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS1) | (1 << ADPS2);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// Send ADC ID when master requests data
void sendID() {
    TinyWireS.write(lowByte(adcID));
    TinyWireS.write(highByte(adcID));
    flag = 1;
}

// Receive new I2C address from master
void receiveNewAddress(uint8_t numBytes) {
    if (TinyWireS.available()) {
        i2cAddress = TinyWireS.read();
        eeprom_write_byte((uint8_t*)0, i2cAddress);
        TinyWireS.begin(i2cAddress);  // Restart TinyWireS with new address
    }
}
