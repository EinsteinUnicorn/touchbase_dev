#include <Wire.h>

#define MAX_I2C_ADDRESS 127  // Max I2C address range

void setup() {
    Serial.begin(115200);
    Wire.begin();  // Initialize I2C as master

    Serial.println("Scanning I2C Bus for devices and positions...");
    delay(1000);

    for (uint8_t address = 1; address < MAX_I2C_ADDRESS; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            // Device found at this address
            Serial.print("Device found at address 0x");
            Serial.print(address, HEX);
            Serial.println();

            // Request ID and Position
            requestDeviceInfo(address);
        }
    }

    Serial.println("I2C Scan Complete.");
}

void requestDeviceInfo(uint8_t address) {
    Wire.beginTransmission(address);
    Wire.write(0x01);  // Command to request ID and position
    Wire.endTransmission();

    delay(10);

    Wire.requestFrom(address, 3);  // Expecting 3 bytes: High(ID), Low(ID), Position

    if (Wire.available() == 3) {
        uint8_t highByte = Wire.read();
        uint8_t lowByte = Wire.read();
        uint8_t position = Wire.read();

        uint16_t deviceID = (highByte << 8) | lowByte;

        Serial.print("  -> Device ID: ");
        Serial.print(deviceID);
        Serial.print(" | Position: ");
        Serial.println(position);
    } else {
        Serial.println("  -> Error: Incomplete data received.");
    }
}

void loop() {
    // Do nothing after initial scan
}
