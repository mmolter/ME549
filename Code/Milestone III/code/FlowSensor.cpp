#include "Arduino.h"
#include "FlowSensor.h"

FlowSensor::FlowSensor(int pin)
{
  // Set pin mode.
  pinMode(pin, INPUT_PULLUP);

  // Enable interrupts.
  attachInterrupt(digitalPinToInterrupt(pin), _sensorISR, FALLING);

  // Write to private variable.
  _pin = pin;
}

void FlowSensor::_sensorISR() {
  /* Count seconds since last flow sensor pulse, and update flowRate */
  
  frequency = 1000000 / (micros() - _lastPulse);
  _lastPulse = micros();

  flowRate = _frequencyToFlow(frequency);
}

float FlowSensor::_frequencyToFlow(float freq){
  /* Convert pulse frequency [Hz] into flow rate [GPM] */
  
  return freq / 7.500;
}
