#ifndef FLS
#define FLS

#include "Arduino.h"

class FlowSensor
{
  public:
    FlowSensor(int pin);
    
    float flowRate;
    float frequency;
    
  private:
    int  _pin;
    long _lastPulse = 0;
    
    void _sensorISR();
    float _frequencyToFlow(float freq);
};

#endif
