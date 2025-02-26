#include <TinyWireS.h>

#define DEFAULT_SLAVE_ADDRESS 8
#define ID_PIN PB3  // ADC pin for unique ID

int LED_PIN = 1;

volatile uint16_t myID = 0;
volatile uint8_t myPosition = 255;  // Unassigned
volatile uint8_t myAddress = DEFAULT_SLAVE_ADDRESS;
volatile bool addressChangeRequested = false;
volatile uint8_t newI2CAddress = DEFAULT_SLAVE_ADDRESS;
//
//void requestEvent() {
//    // Send myID (2 bytes) and myPosition (1 byte) to the master
//    TinyWireS.write((myID >> 8) & 0xFF);  // High byte
//    TinyWireS.write(myID & 0xFF);         // Low byte
//    TinyWireS.write(myPosition);          // Position
//}
//
//void receiveEvent(uint8_t howMany) {
//    if (howMany < 1) return;
//
//    uint8_t cmd = TinyWireS.read();
//
//    if (cmd == 0x01) {
//        // Master requests ID and position
//        // Handled by requestEvent
//    } else if (cmd == 0x02 && howMany >= 3) {
//        // Master assigns position and new I2C address
//        myPosition = TinyWireS.read();
//        newI2CAddress = TinyWireS.read();
//        addressChangeRequested = true;  // Set flag to change address
//    }
//}
//
//uint16_t readResistorID() {
//    // Configure ADC to read from ID_PIN (PB3)
//    ADMUX = (1 << MUX1) | (1 << MUX0);  // Select ADC3
//    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC with prescaler
//
//    // Start conversion
//    ADCSRA |= (1 << ADSC);
//    while (ADCSRA & (1 << ADSC));
//
//    return ADC;  // Return 10-bit ADC value
//}

void setup() {
//    TinyWireS.begin(DEFAULT_SLAVE_ADDRESS);  // Start as I2C slave
//    TinyWireS.onReceive(receiveEvent);
//    TinyWireS.onRequest(requestEvent);
//    
//    // Read unique ID from ADC
//    myID = readResistorID();
}

void loop() {
//    TinyWireS_stop_check();  // Required for TinyWireS to process I2C events
//
//    if (addressChangeRequested) {
//        // Apply the new I2C address
//        addressChangeRequested = false;
//        TinyWireS.begin(newI2CAddress);
//    }
      digitalWrite(LED_PIN, HIGH);

}
