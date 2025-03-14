#include <Wire.h>

#define END_ADDRESS 0x08  // Fixed address for end block

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(100);
    
    Serial.println("Checking for end block...");
    if (checkDevice(END_ADDRESS)) {
        Serial.println("End block found at address 0x08");
        uint8_t next_address = getNextAddress(END_ADDRESS);
        Serial.print("Next block address: 0x");
        Serial.println(next_address, HEX);

        if (checkDevice(next_address)) {
          Serial.print("Next block address: 0x");
          Serial.println(getNextAddress(next_address), HEX);
        }
        
    } else {
        Serial.println("End block not found!");
    }
}

void loop() {
    // Nothing needed in loop
}

// Check if an I2C device responds at a given address
bool checkDevice(uint8_t address) {
    Wire.beginTransmission(address);
    return (Wire.endTransmission() == 0);
}

// Request the next address from the given block
uint8_t getNextAddress(uint8_t current_address) {
    Wire.requestFrom(current_address, 1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0x00; // Return 0x00 if no valid response
}
