/*----------------------------------------------------------
 * 
 *  Project:    OHAUS Scout RS232 Interface
 *  
 *  Objective:  Build a serial communication library to inteface
 *              with a digital lab scale over serial.
 *  
 *  Author:     Michael Molter
 *  
 *  Date:       3 APR 2019
 * 
 * 
 *---------------------------------------------------------*/

#include <SoftwareSerial.h>

// Setup additional serial port for PC communications.
SoftwareSerial computer(10, 11); // RX/TX

void setup() {
  // Initialize default serial port configuration parameters.
  
  // The Arduino will communicate with the balance over the default
  // serial port, because that one has a female USB connector on it.

  // 9600 Baud, 8 data bits, no parity, 1 stop bit(s).
  Serial.begin(9600, SERIAL_8N1);

  // The Arduino will communicate with my PC over software serial w/
  // an FTDI TTL-USB converter. 
  computer.begin(96000);
  computer.println("Starting....");

  computer.println("Reading the scale...");
  computer.println(readScale());
  computer.println("Taring the scale...");
  bool success = tare();

  if (!success){
    computer.println("Tare failed! Exiting...");
    return 0;
  }

  computer.println("Reading the scale after the tare...");
  computer.println(readScale());
  computer.println("Exiting...");
  return 0;
}

void loop() {
  return 0;
}

bool tare(){
  // Tare the scale.
  Serial.println("T");

  // Report whether or not command was acknowledged.
  if (Serial.readString() == "ES")
    return true;  // Succes.
  else
    return false; // Failed.
}

String readScale() {
  // Read the immediate value of the scale in grams.

  Serial.println("P");

  return Serial.readString();
}
