/* ---------------------------------------------------------
 *  
 *    Project:  Milestone I
 *    
 *    Author:   M. Molter
 *    
 *    Date:     4 MAR 2019
 *    
 *    Desc:     Reads the flow cell, and outputs
 *              to an LED if the rate is fast enough.
 *              
 * ---------------------------------------------------- */

 #include "FlowSensor.h"

const int pinLED    = 4;    // Lights up if flow rate is greater than 5 GPM.
const int pinSENSOR = 2;    // Requires interrupt pin (i.e. 2 or 3 on UNO).
const int pinBUTTON = 3;    // Requires interrupt pin (i.e. 2 or 3 on UNO).

volatile float setRate   = 5;

long lastRefresh = 0;
long refreshRate = 125;   // milliseconds.

bool taughtFlag = false;

FlowSensor sensor(pinSENSOR);


void setup() {
  /* Initialize outputs, begin serial communication, and attach interrupts */
  
  // Begin communicating over serial.
  Serial.begin(115200);
  Serial.println("Initializing sensor...");

  // Set pin modes.
  pinMode(pinLED,    OUTPUT);
  pinMode(pinBUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinBUTTON), teach, FALLING);

}

void loop() {
  if (millis() - lastRefresh > refreshRate){
    Serial.print(sensor.flowRate, 2);
    Serial.print(" [GPM] : ");
    Serial.print(sensor.frequency, 1);
    Serial.print(" [Hz]\n");
    
    lastRefresh = millis();
  }

  if (taughtFlag && digitalRead(pinBUTTON)){
    Serial.print("Sensor alarm level set to ");
    Serial.print(setRate, 2);
    Serial.print(" [GPM]");
    
    for(int i = 0; i < 3; i++){
      digitalWrite(pinLED, HIGH);
      delay(200);
      digitalWrite(pinLED, LOW);
      delay(200);
    }
    
    taughtFlag = false;
  }

  sensor.flowRate > setRate ? digitalWrite(pinLED, HIGH) : digitalWrite(pinLED, LOW);
}

void teach(){
  /* Change the triggered flow rate to the current flow rate. */

  if (!taughtFlag){
    setRate = sensor.flowRate;
    taughtFlag = true;
  }
}
