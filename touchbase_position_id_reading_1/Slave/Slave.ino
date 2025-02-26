#include <TinyWireS.h>
#include <avr/io.h>

#define I2C_SLAVE_ADDRESS  8  // Default I2C address (all devices start here)
#define ID_PIN             PB3  // ADC3 for reading resistor value

int LED_PIN = 1;

volatile uint16_t myID = 0;  // Raw ADC value (0-1023)
volatile uint8_t myPosition = 255;  // Unassigned position indicator

void requestEvent() {
  TinyWireS.write((myID >> 8) & 0xFF);  // High byte of myID
  TinyWireS.write(myID & 0xFF);         // Low byte of myID
  TinyWireS.write(myPosition);          // Position
}


void receiveEvent(uint8_t howMany) {
    if (howMany < 1) return;  // No data received

    uint8_t cmd = TinyWireS.read();

    if (cmd == 0x01) {
        // Master requested ID and position (handled in requestEvent)
    } 
    else if (cmd == 0x02 && howMany >= 2) {
        // Master is assigning a position
        myPosition = TinyWireS.read();  // Read assigned position
    }
}

uint16_t readResistorID() {
    // Configure ADC to read from ADC3 (PB3)
    ADMUX = (1 << MUX1) | (1 << MUX0);  // Select ADC3
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC with prescaler 8

    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));  // Wait for conversion

    return ADC;  // Return raw 10-bit ADC value
}

void setup() {
    TinyWireS.begin(I2C_SLAVE_ADDRESS);  // Start as I2C slave
    TinyWireS.onRequest(requestEvent);   // Respond to master read
    TinyWireS.onReceive(receiveEvent);   // Handle master's commands

    // Read resistor-based ID from ADC on PB3
    myID = readResistorID();
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    TinyWireS_stop_check();  // Must be called in the loop for TinyWireS to work properly
}
