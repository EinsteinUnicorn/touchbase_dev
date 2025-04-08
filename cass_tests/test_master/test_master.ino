#include <SBWire.h>


volatile uint8_t TARGET_BLOCK =  0x7C; // I2C address of the program block
int addresses [127];
int i = 0;

void setup() {
  Wire.begin(); // Initialize as master
  Wire.setTimeout(1000); //timeout value in uSec - SBWire uses 100 uSec, so 1000 should be OK
  Serial.begin(9600); // For debugging
  delay(1000); // Allow time for initialization
  Serial.println("Brain block initialized.");
  pinMode(LED_BUILTIN, OUTPUT);
  memset(addresses,0,sizeof(addresses));
  addresses[0] = (int)TARGET_BLOCK;
}

//int missedI2Crequest = 0;
void loop() {
  Wire.requestFrom((int)TARGET_BLOCK, 1, true);
  delay(150); 
  
  if (Wire.available() >= 1) { 
    i++;
    Serial.println("target address:");
    Serial.println(TARGET_BLOCK);

    uint8_t nextAddress = Wire.read();

    TARGET_BLOCK = nextAddress;
    Serial.println("Next address:");
    Serial.println(nextAddress);

    addresses[i] = (int)nextAddress;
  } else {
    //missedI2Crequest++;
    Serial.println("Nothing else connected");
  }

  /*
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // remove whitespace

    if (command == "GET") {
      for (int i = 0; i < 127; i++) {
        Serial.println(addresses[i]);
      }
    }
  }
  */
  
//
//  if(missedI2Crequest > 15){
//    Serial.println(missedI2Crequest);
//    String program = createProgram();
//    Serial.print(program);
//  }

  delay(500);
}

String createProgram() {
  Serial.println("In create program");
  String program = "";
  for(int j = 0; j < i; j++){
    switch((int)addresses[j]){
      case 86:
         program += "start/n";
         break;
      case 124:
         program += "middle /n";
         break;
      case 105:
        program += "end/n";
        break;
      default:
        break;
    }
  }
  return program;
}
