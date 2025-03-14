#include <TinyWireS.h>

#define LED_PIN 1     // LED output
#define ADC_PIN 3     // ADC input to determine device address
#define PREV_IN 4     // ADC input from the previous block

uint8_t i2c_address;
uint8_t prev_address = 0x00;  // Store the previous block's address

void requestEvent() {
    TinyWireS.write(prev_address);  // Send the previous block's address to the master
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(ADC_PIN, INPUT);
    pinMode(PREV_IN, INPUT);

    
    // Read ADC pin 3 to determine this device's I2C address
    int adc_value = analogRead(ADC_PIN);
    i2c_address = (adc_value / 128) + 1;  // Convert ADC to valid address range (1-127)
    
    // Read ADC pin 4 to determine the previous block's address
    int prev_adc_value = analogRead(PREV_IN);
    prev_address = (prev_adc_value / 128) + 1;
    
    // Set I2C address dynamically based on ADC value
    TinyWireS.begin(i2c_address);
    TinyWireS.onRequest(requestEvent);
}

void loop() {
    TinyWireS_stop_check();
}
