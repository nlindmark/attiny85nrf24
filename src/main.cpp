#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RF24.h"

// ***
// *** Define the RX and TX pins. Choose any two
// *** pins that are unused. Try to avoid D0 (pin 5)
// *** and D2 (pin 7) if you plan to use I2C.
// ***
#define RX    3   // *** D3, Pin 2
#define TX    4   // *** D4, Pin 3

SoftwareSerial ser(RX, TX);

//#define CE_PIN 3
//#define CSN_PIN 3 //Since we are using 3 pin configuration we will use same pin for both CE and CSN
#define CE_PIN 7
#define CSN_PIN 7 //Since we are using 3 pin configuration we will use same pin for both CE and CSN
//NL The RF24 lib has suppo9rt for 3 pin operation. Just set CE and CSN to same pin


RF24 radio(CE_PIN, CSN_PIN);

byte address[11] = "SimpleNode";
unsigned long payload = 0;


void setup() {
  // put your setup code here, to run once:
  ser.begin(9600);
  ser.println("Initializing...");

  radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(address); // Write to device address 'SimpleNode'
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  payload++;
  radio.write( &payload, sizeof(unsigned long) ); //Send data to 'Receiver' ever second
  delay(1000);
  ser.println(".");
 
  
  }


