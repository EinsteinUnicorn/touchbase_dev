#include <Wire.h>
// hey becky lurb
#define DEFAULT_SLAVE_ADDRESS 8
#define MAX_DEVICES 10  // Adjust based on the expected number of devices

uint16_t assignedDeviceIDs[MAX_DEVICES];  // Store assigned device IDs
uint8_t assignedAddresses[MAX_DEVICES];   // Store assigned I2C addresses
uint8_t deviceCount = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin();  // Initialize I2C as master

    Serial.println("Scanning and assigning positions to devices...");

    uint8_t position = 1;  // Start positions from 1
    uint8_t newAddress = 10;  // Start new addresses from 10

    for (int i = 0; i < MAX_DEVICES; i++) {
        // Check if a device is responding at the default address
        Wire.beginTransmission(DEFAULT_SLAVE_ADDRESS);
        if (Wire.endTransmission() == 0) {
            // Request the device's ID
            uint16_t deviceID = requestDeviceID(DEFAULT_SLAVE_ADDRESS);

            if (deviceID != 0 && !isDeviceAssigned(deviceID)) {
                Serial.print("Device found. Assigning position: ");
                Serial.println(position);

                // Assign position and new I2C address to the slave
                
                assignPositionAndAddress(DEFAULT_SLAVE_ADDRESS, position, newAddress);

                // Store the assigned device ID and new address
                assignedDeviceIDs[deviceCount] = deviceID;
                assignedAddresses[deviceCount] = newAddress;
                deviceCount++;

                // Request and display the device's ID and assigned position using the new address
                requestDeviceInfo(newAddress);

                position++;   // Increment position for next device
                newAddress+=2; // Increment address for the next device
            } else {
                Serial.println("Device already assigned or invalid ID.");
            }
        } else {
            // No more devices found at the default address
            break;
        }
        delay(50);   // Small delay between assignments
    }

    Serial.println("Position assignment complete.");
}

uint16_t requestDeviceID(uint8_t address) {
    Wire.beginTransmission(address);
    Wire.write(0x01);  // Command to request ID
    Wire.endTransmission();

    delay(10);

    Wire.requestFrom(address, 2);  // Expecting 2 bytes: High(ID), Low(ID)

    if (Wire.available() == 2) {
        uint8_t highByte = Wire.read();
        uint8_t lowByte = Wire.read();
        return (highByte << 8) | lowByte;
    } else {
        Serial.println("Error: Incomplete ID received.");
        return 0;  // Indicate error
    }
}

void assignPositionAndAddress(uint8_t address, uint8_t position, uint8_t newAddress) {
    Wire.beginTransmission(address);
    Wire.write(0x02);         // Command to assign position
    Wire.write(position);     // Position value
    Wire.write(newAddress);   // New I2C address
    Wire.endTransmission();
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

        Serial.print("Device ID: ");
        Serial.print(deviceID);
        Serial.print(", Assigned Position: ");
        Serial.print(position);
        Serial.print(", New Address: ");
        Serial.println(address);
    } else {
        Serial.println("Error: Incomplete data received.");
    }
}

bool isDeviceAssigned(uint16_t deviceID) {
    for (uint8_t i = 0; i < deviceCount; i++) {
        if (assignedDeviceIDs[i] == deviceID) {
            return true;  // Device is already assigned
        }
    }
    return false;  // Device is unassigned
}

void loop() {
    // Nothing here, runs once in setup
}
