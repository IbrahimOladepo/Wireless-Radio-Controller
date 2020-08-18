#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte jly;
  byte jlx;
  byte jry;
  byte jrx;
  byte bl;
  byte br;
};

//Create a variable with the above structure
Data_Package data; 


void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // set default value for sticks
  data.jly = 90;
  data.jlx = 90;
  data.jry = 90;
  data.jrx = 90;
  data.bl = 0;
  data.br = 0;
}

void loop() {
  // Check whether there is data to be received
  if (radio.available()) {    
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
    Serial.println("Connection Established");
  }

  currentTime = millis();
  if ( currentTime - lastReceiveTime > 5000 ) { 
    resetData(); 
  }

  // print debug
  Serial.println("LEFT ANALOG:");
  Serial.print("RY:       ");
  Serial.println(data.jlx);
  Serial.print("RX:       ");
  Serial.println(data.jly);

  Serial.println("RIGHT ANALOG:");
  Serial.print("LY:       ");
  Serial.println(data.jrx);
  Serial.print("LX:       ");
  Serial.println(data.jry);

  Serial.println("SWITCHES:");
  Serial.print("BR:       ");
  Serial.println(data.bl);
  Serial.print("BL:       ");
  Serial.println(data.br);
  
  Serial.println("");
  Serial.println("");

  delay(100);
}


void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.jly = 90;
  data.jlx = 90;
  data.jry = 90;
  data.jrx = 90;
  data.bl = 0;
  data.br = 0;
}
