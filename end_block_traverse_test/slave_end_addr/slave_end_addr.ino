#include <TinyWireS.h>

#define LED_PIN 1     // LED output
#define PREV_IN 4     // ADC input from the previous block
#define ADC_IN 3     // ADC input from the previous block
#define END_ADDRESS 0x08  // Fixed address for the end block

uint8_t prev_address = 0x00;  // Store the previous block's address

void requestEvent() {
    uint8_t prev_adc_value = (analogRead(PREV_IN) << 8) >> 8;
    prev_address = prev_adc_value; // Convert ADC value to address range (1-127)
    TinyWireS.write(prev_address);  // Send the previous block's address to the master
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(PREV_IN, INPUT);
    pinMode(ADC_IN, INPUT);
    
    // Set I2C address to fixed end block address
    TinyWireS.begin(END_ADDRESS);
    TinyWireS.onRequest(requestEvent);
    
    // Read the previous block's address from pin 4
    //int prev_adc_value = analogRead(PREV_IN);
    //prev_address = (prev_adc_value / 128) + 1; // Convert ADC value to address range (1-127)
}

void loop() {
    pinMode(LED_PIN, HIGH);
    TinyWireS_stop_check();
}
