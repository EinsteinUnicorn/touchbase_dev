#include <Wire.h>

#define DEFAULT_SLAVE_ADDRESS 8
#define MAX_DEVICES 10  // Adjust based on the expected number of devices

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialize I2C as master

  Serial.println("Scanning and assigning positions to devices...");

  uint8_t position = 1;  // Start positions from 1

  for (int i = 0; i < MAX_DEVICES; i++) {
    // Check if a device is responding at the default address
    Wire.beginTransmission(DEFAULT_SLAVE_ADDRESS);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found. Assigning position: ");
      Serial.println(position);

      // Assign position to the slave
      assignPosition(DEFAULT_SLAVE_ADDRESS, position);

      // Request and display the device's ID and assigned position
      requestDeviceInfo(DEFAULT_SLAVE_ADDRESS);

      position++;  // Increment position for next device
      delay(50);   // Small delay between assignments
    } else {
      // No more devices found at the default address
      break;
    }
  }

  Serial.println("Position assignment complete.");
}

void assignPosition(uint8_t address, uint8_t position) {
  Wire.beginTransmission(address);
  Wire.write(0x02);     // Command to assign position
  Wire.write(position); // Position value
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
    Serial.println(position);
  } else {
    Serial.println("Error: Incomplete data received.");
  }
}

void loop() {
  // Nothing here, runs once in setup
}
