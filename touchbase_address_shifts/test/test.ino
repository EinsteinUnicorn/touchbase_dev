
#include <Wire.h>


void setup() {
    Serial.begin(9600);
    Wire.begin();
    Serial.println("I2C Scanner");
}

void loop() {
    Serial.println("Scanning...");
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.print("Device found at 0x");
            Serial.println(addr, HEX);
        }
    }
    delay(5000);
}
