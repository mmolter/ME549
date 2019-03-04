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

const int pinLED    = 4;   // Lights up if flow rate is greater than 5 GPM.
const int pinSENSOR = 2;    // Requires interrupt pin (i.e. 2 or 3 on UNO).

volatile long lastPulse = 0;
volatile float frequency = 0;
volatile float flowRate  = 0;

long lastRefresh = 0;
long refreshRate = 125;   // milliseconds.

float frequencyToFlow(float freq){
  // Converts pulse frequency [Hz] into flow rate [GPM]
  return freq / 7.500;
}

void capturePulse() {
  frequency = 1000.0 / ((float) (millis() - lastPulse));
  lastPulse = millis();

  flowRate = frequencyToFlow(frequency);
  flowRate > 10.0 ? digitalWrite(pinLED, HIGH) : digitalWrite(pinLED, LOW);
}

void setup() {
  // Begin communicating over serial.
  Serial.begin(115200);
  Serial.println("Initializing sensor...");

  // Set pin modes.
  pinMode(pinLED,    OUTPUT);
  pinMode(pinSENSOR, INPUT_PULLUP);

  // Enable interrupts.
  attachInterrupt(digitalPinToInterrupt(pinSENSOR), capturePulse, FALLING);
}

void loop() {
  if (millis() - lastRefresh > refreshRate){
    Serial.print(flowRate, 2);
    Serial.print(" [GPM]: ");
    Serial.print(frequency, 1);
    Serial.print(" [Hz]\n");
    
    lastRefresh = millis();
  }
}
