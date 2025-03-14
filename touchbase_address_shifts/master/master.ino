/* ============================
 *  Arduino Uno (I2C Master) 
 * ============================
 */
#include <Wire.h>

#define DEFAULT_ADDR 0x08 // Default address for uninitialized devices
#define MAX_DEVICES 8     // Maximum expected ATtiny devices

struct Device {
    uint8_t address;
    uint16_t id;
};

Device devices[MAX_DEVICES];
uint8_t assignedAddress = 0x10; // Start assigning addresses from 0x10

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(1000);
    Serial.println("Scanning and assigning addresses...");
    assignAddresses();
    printDevices();
}

void loop() {
    // Main loop can handle further communication if needed
}

void assignAddresses() {
    uint8_t numDevices = 0;

    for (int i = 0; i < MAX_DEVICES; i++) {
        Wire.beginTransmission(DEFAULT_ADDR);
        if (Wire.endTransmission() == 0) { // Device found at default address
            uint16_t adcID = requestID(DEFAULT_ADDR);
            devices[numDevices] = {assignedAddress, adcID};
            sendNewAddress(DEFAULT_ADDR, assignedAddress);
            assignedAddress++;
            numDevices++;
            delay(100); // Allow the device time to update its address
        }
    }
}

uint16_t requestID(uint8_t addr) {
    Wire.requestFrom(addr, (uint8_t)2); // Request 2 bytes for ADC ID
    uint16_t id = 0;
    if (Wire.available() >= 2) {
        id = Wire.read();
        id |= (Wire.read() << 8);
    }
    return id;
}

void sendNewAddress(uint8_t oldAddr, uint8_t newAddr) {
    Wire.beginTransmission(oldAddr);
    Wire.write(newAddr);
    Wire.endTransmission();
}

void printDevices() {
    Serial.println("Device Positions:");
    for (int i = 0; i < MAX_DEVICES; i++) {
        if (devices[i].address == 0) break;
        Serial.print("Position ");
        Serial.print(i + 1);
        Serial.print(" -> Address: 0x");
        Serial.print(devices[i].address, HEX);
        Serial.print(" | ID: ");
        Serial.println(devices[i].id);
    }
}
