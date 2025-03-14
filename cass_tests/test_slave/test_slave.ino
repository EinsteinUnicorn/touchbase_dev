/*
#include <TinyWire.h>

#define START_ADDRESS 0x08 // Starting address for dynamically assigned blocks
#define ADC_PIN 3
#define MAX_BLOCKS 10

const int LED_PIN = 1;         // Pin used for the ADC

uint8_t assignedAddress = 0; // Dynamically assigned I2C address

void setup() {
  TinyWire.begin(); // Join the I2C bus in an unaddressed state
  TinyWire.onReceive(receiveEvent);  // Register callback for initialization and commands
  TinyWire.onRequest(sendData);     // Register callback to send data

  pinMode(LED_PIN, OUTPUT);
  pinMode(ADC_PIN, INPUT);
}

void loop() {
  // No specific loop logic; the block reacts to events
  digitalWrite(LED_PIN, HIGH);
}

void receiveEvent(int howMany) {

  if (howMany > 0) {
    uint8_t signal = TinyWire.read();

    if (signal == 0xFF && assignedAddress == 0) {
      int adcValue = analogRead(ADC_PIN);
      // Assign a unique address based on ADC reading or position
      assignedAddress = START_ADDRESS + (adcValue % MAX_BLOCKS); // Example dynamic assignment
      TinyWire.begin(assignedAddress); // Rejoin I2C bus with assigned address
      //Serial.print("Assigned address: 0x");
      //Serial.println(assignedAddress, HEX);
    }
  }
}

void sendData() {
  TinyWire.write(assignedAddress);
}*/



////USE THIS ONE FOR JUST ONE BLOCK DETECTION



#include <TinyWire.h>

#define ADC_PIN_CURR 3          // Pin used for the current block's ADC
#define ADC_PIN_NEXT 4         // Pin for the next block's ADC
//#define PROGRAM_BLOCK_ADDRESS 0x08 // I2C address of this block

int currAdcValue = 0;

int LED_PIN = 1;

void setup() {
  pinMode(ADC_PIN_CURR, INPUT);           // Configure ADC pin as input
  pinMode(ADC_PIN_NEXT, INPUT);           // Configure ADC pin as input

  currAdcValue = analogRead(ADC_PIN_CURR); // Read ADC value

  uint8_t currAddress = map(currAdcValue, 0, 1023, 0, 127);

  TinyWire.begin(currAddress); // Join the I2C bus as a slave
  TinyWire.onRequest(sendADCValue);      // Register the request handler
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
}

void sendADCValue() {
  int nextAdcValue = analogRead(ADC_PIN_NEXT);   // Read ADC value
  uint8_t nextAddress = map(nextAdcValue, 0, 1023, 0, 127);
  TinyWire.write(nextAddress);

}

























/*
  I2C Slave Control Demo
  i2c-slave-demo-control.ino
  Demonstrate use of I2C bus
  Receives potentimeter position data
  Controls LED blink rate
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
/*
// Include Arduino Wire library for I2C
#include <TinyWire.h>

#define MAST_ADDR 10

// Define Slave I2C Address
#define SLAVE_ADDR 9

//String answer = "000";

// Define LED Pin
int LED = 1;

// Variable for received data
int rd;

// Variable for blink rate
int br;

void setup() {

  pinMode(LED, OUTPUT);
  
  // Initialize I2C communications as Slave
  TinyWire.begin(SLAVE_ADDR);
   
  // Function to run when data received from master
  TinyWire.onReceive(receiveEvent);

  //TinyWire.onRequest(requestEvent);
  
  // Setup Serial Monitor 
  //Serial.begin(9600);
  //Serial.println("I2C Slave Demonstration");
  //Serial.println("test 2");
}


void loop() {
  delay(50);

  //Serial.println(rd);
  //Serial.println("test");
 
  // Calculate blink value
  br = map(rd, 1, 255, 100, 2000);
  digitalWrite(LED, HIGH);
  delay(br);
  digitalWrite(LED, LOW);
  delay(br);

}

void receiveEvent() {
  // read one character from the I2C
  rd = TinyWire.read();
  // Print value of incoming data
  //Serial.println(rd);
  
  
  //TinyWire.write(rd);
    
}

void requestEvent() {
 
  
  // Setup byte variable in the correct size
  byte response[VALUE_SIZE];
  
  // Format answer as array
  for (byte i=0;i<VALUE_SIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }

  TinyWire.beginTransmission(MAST_ADDR);

  // Send response back to Master
  TinyWire.write(rd);
  
  // Print to Serial Monitor
  //Serial.println("Request event");
}*/