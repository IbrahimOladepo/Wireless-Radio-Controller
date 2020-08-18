#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

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
  // Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // map analog values to 0 to 180 range
  data.jly = map(analogRead(A0), 0, 1023, 0, 180);
  data.jlx = map(analogRead(A1), 0, 1023, 0, 180);
  data.jry = map(analogRead(A2), 0, 1023, 0, 180);
  data.jrx = map(analogRead(A3), 0, 1023, 0, 180);

  // get switch values for analog sticks
  data.bl = digitalRead(3);
  data.br = digitalRead(2);

  // send values through radio
  radio.write(&data, sizeof(Data_Package));

  delay(50);
}
