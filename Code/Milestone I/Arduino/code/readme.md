# Milestone I

### Introduction

This code will read a Digiten Water Flow Sensor, and report the flow rate over serial. The code also provides for an LED light that will show a HIGH alarm if the flow rate is greater than 10 GPM. 

### Wiring the Sensor

The sensor has a red lead (+5 VDC), a black lead (0 VDC), and a yellow lead (signal). The sensor needs to be on a pin capable of interrupts. This is either pin 2 or pin 3 on the Arduino Uno.

Both the LED pin and the sensor pin can be changed at the to of the program by chaning pinLED and pinSENSOR respectively.

### Changing the Alarm Speed

The alarm level can be changed by modifying the line:

  flowRate > 10.0 ? digitalWrite(pinLED, HIGH) : digitalWrite(pinLED, LOW);

Simply change the 10.0 to the desired flow rate.
