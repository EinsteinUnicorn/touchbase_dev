/*
#include <WSWire.h>

#define BROADCAST_ADDRESS 0x00
#define START_ADDRESS 0x08 // Starting address for dynamically assigned blocks
#define MAX_BLOCKS 10      // Maximum number of blocks

uint8_t activeBlocks[MAX_BLOCKS]; // Array to store active block addresses
uint8_t blockCount = 0;           // Count of detected blocks

void setup() {
  //Wire.setClock(100000); // Set I2C clock to 100kHz (standard mode)
  Wire.begin(); // Initialize I2C as master
  // Manually set I2C clock to 50kHz
  TWSR = 0x00;      // Prescaler = 1
  TWBR = 152;       // Bit rate register value for 50kHz

  Serial.begin(9600); // Initialize Serial for debugging
  delay(1000);
  Serial.println("Master initialized.");

  // Initialize blocks and assign addresses
  initializeBlocks();
}

void loop() {
  // Query each active block for its ADC value
  for (uint8_t i = 0; i < blockCount; i++) {
    Serial.println("Check 2");
    requestBlockData(activeBlocks[i]);
  }

  delay(1000); // Wait before the next round of queries
}

void initializeBlocks() {
  Serial.println("Initializing blocks...");

  Wire.beginTransmission(BROADCAST_ADDRESS);
  Wire.write(0xFF); // Initialization signal
  if (Wire.endTransmission() != 0) {
    Serial.println("Failed to send initialization signal.");
    return;
  }
  delay(500); // Allow time for blocks to assign addresses

  // Scan for dynamically assigned addresses
  bool blocksDetected = false;
  for (uint8_t address = 0x08; address < 0x78; address++) { // Typical I2C address range
    if (checkAddress(address)) {
      Serial.print("Block found at address: 0x");
      Serial.println(address, HEX);
      blocksDetected = true;
    }
  }

  if (!blocksDetected) {
    Serial.println("No blocks detected.");
    return; // Exit initialization if no blocks are found
  }

  Serial.println("Blocks initialized successfully.");
*/

  /*
  // Send global initialization signal
  Wire.begin();
  Wire.beginTransmission(0); // Broadcast signal to all blocks
  Serial.println("Check 1");
  Wire.write(0xFF);          // Signal for initialization
  delay(1000);
  Serial.println("Check 3");
  Wire.endTransmission();
  Serial.println("Check 4");
  delay(500); // Give blocks time to assign addresses
  

  // Discover active blocks by scanning the I2C bus
  blockCount = 0;
  for (uint8_t address = START_ADDRESS; address < START_ADDRESS + MAX_BLOCKS; address++) {
    //Serial.println("check5");
    Wire.beginTransmission(address);
    Serial.print("end transmission = ");
    Serial.println(Wire.endTransmission());
    if (Wire.endTransmission() == 0) { // If block responds
      activeBlocks[blockCount++] = address;
      Serial.print("Block detected at address: 0x");
      Serial.println(address, HEX);
    }
  }

  if (blockCount == 0) {
    Serial.println("No blocks detected.");
  }
}*/
/*
bool checkAddress(uint8_t address) {
  Wire.beginTransmission(address);

  unsigned long startTime = millis();
  const unsigned long TIMEOUT_MS = 1000;

  while (Wire.endTransmission() != 0) { // Retry communication
    if (millis() - startTime > TIMEOUT_MS) {
      Serial.print("Timeout for address 0x");
      Serial.println(address, HEX);
      return false; // Timeout occurred
    }
  }
  return true; // Address responded successfully
}

void requestBlockData(uint8_t blockAddress) {
  Wire.requestFrom((uint8_t)blockAddress, (size_t)2); // Request 2 bytes (16-bit ADC value)

  if (Wire.available() >= 2) {
    int adcValue = Wire.read() << 8; // Read high byte
    adcValue |= Wire.read();        // Read low byte
    Serial.print("Block ");
    Serial.print(blockAddress, HEX);
    Serial.print(" ADC Value: ");
    Serial.println(adcValue);
  } else {
    Serial.print("No response from block ");
    Serial.println(blockAddress, HEX);
  }
}*/





///// USE THIS ONE FOR JUST ONE BLOCK DETECTION



#include <Wire.h>


String blockType = "";
uint8_t TARGET_BLOCK =  0x7C; // I2C address of the program block
int addresses [127];
int i = 0;

void setup() {
  Wire.begin(); // Initialize as master
  Serial.begin(9600); // For debugging
  delay(1000); // Allow time for initialization
  Serial.println("Brain block initialized.");
  pinMode(LED_BUILTIN, OUTPUT);
  memset(addresses,0,sizeof(addresses));
  addresses[0] = (int)TARGET_BLOCK;
}


void loop() {
  
  // Request data from the program block
  //Serial.println("check2");
  Wire.requestFrom((int)TARGET_BLOCK, 1); // Request 2 bytes (16-bit ADC value)
  //Serial.println("check");
  delay(100);
  if (Wire.available() >= 1) { // Wait until we receive 2 bytes

    i++;
    Serial.println("target address:");
    Serial.println(TARGET_BLOCK);

    uint8_t nextAddress = Wire.read();

    Serial.println("Next address:");
    Serial.println(nextAddress);

    addresses[i] = (int)nextAddress;
    while(nextAddress != 0){
      TARGET_BLOCK = nextAddress;
    }
    
    // int currAdcValue = Wire.read() << 8; // Read high byte
    // currAdcValue |= Wire.read();
    // Serial.print("Current block value: ");
    // Serial.println(currAdcValue);

    // int nextAdcValue = Wire.read() << 8; // Read high byte
    // nextAdcValue |= Wire.read();
    // Serial.print("Next block value: ");
    // Serial.println(nextAdcValue);
    
    // if (adcValue >= 1020) {
    //   blockType = "if";
    // }
    // else if (adcValue < 1020 && adcValue >= 1000) {
    //   blockType = "pressed";
    // }
    // else if (adcValue < 1000) {
    //   blockType = "button";
    // }        
    // Serial.print("Block: ");
    // Serial.println(blockType);       // Print the ADC value
  } else {
    blockType = "missing";
    Serial.println("No response from program block.");
  }

  //delay(5000); // Wait 1 second before the next request
  digitalWrite(LED_BUILTIN, HIGH);
  delay(getDelay(blockType));
  digitalWrite(LED_BUILTIN, LOW);
  delay(getDelay(blockType));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(getDelay(blockType));
  digitalWrite(LED_BUILTIN, LOW);
  delay(getDelay(blockType));
  delay(1000);
}



int getDelay(String block) {
  if (block == "if") {
    return 150;
  }

  else if (block == "variable1") {
    return 500;
  }

  else if (block == "servo") {
    return 1000;
  }

  else if (block == "missing") {
    return 10;
  }

  else {
    return 2000;
  }
}















/*
  I2C Master Control Demo
  i2c-master-demo-control.ino
  Demonstrate use of I2C bus
  Master sends potentimeter position data
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
/*
// Include Arduino Wire library for I2C
#include <Wire.h>

#define MAST_ADDR 10

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Analog pin for potentiometer
int analogPin = A0;
// Integer to hold potentiometer value
int val = 0;

// Variable for received data
int rd;

void setup() {
  Serial.begin(9600);

  Serial.println("I2C began.");

  // Initialize I2C communications as Master
  Wire.begin();
  
  //Wire.onReceive(receiveEvent);
}

void loop() {
  delay(50);
  
  // Read pot value 
  // Map to range of 1-255 for flash rate
  Serial.println("break 1");
  val = map(analogRead(analogPin), 0, 1023, 255, 1);
    
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(val);
  Serial.println("break 2");
  Serial.print("Sent: ");
  Serial.println(val);
  Serial.print("break 4");
  Wire.endTransmission();
  Serial.println("break 3");
}

void receiveEvent() {
  // read one character from the I2C
  rd = Wire.read();
  // Print value of incoming data
  //Serial.print("Block ");
  //Serial.print()
  Serial.print("Block Received: ");
  Serial.println(rd);
}*/