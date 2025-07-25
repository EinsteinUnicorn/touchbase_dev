#include <TinyWireS.h>

#define ADC_PIN_CURR 3          // Pin used for the current block's ADC
#define ADC_PIN_NEXT 2         // Pin for the next block's ADC

int currAdcValue = 0;

int LED_PIN = 1;

void setup() {
  pinMode(ADC_PIN_CURR, INPUT);           // Configure ADC pin as input
  pinMode(ADC_PIN_NEXT, INPUT);           // Configure ADC pin as input

  currAdcValue = analogRead(ADC_PIN_CURR); // Read ADC value

  uint8_t currAddress = map(currAdcValue, 0, 1023, 0, 127);

  TinyWireS.begin(currAddress); // Join the I2C bus as a slave
  TinyWireS.onRequest(sendADCValue);      // Register the request handler
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
}

void sendADCValue() {
  int nextAdcValue = analogRead(ADC_PIN_NEXT);   // Read ADC value
  uint8_t nextAddress = map(nextAdcValue, 0, 1023, 0, 127);
  TinyWireS.write(nextAddress);

}
