# Milestone II

### Introduction

This code will read a Digiten Water Flow Sensor, and report the flow rate over serial. The code provides for a teach pushbutton, and an LED to report when the flow rate is above the taught threshold. To teach the alarm level, simply run the alarm level flow through the sensor, and press the teach button. The LED will flash three times to indicate the device was taught succesfully. 

### Updates from Milestone II

All of the sensor functionality has been put in separate functions. A teach button has been added with some basic deboucing code. 

### Sensor Operation

The sensor uses a paddle wheel to detect the flow rate of the fluid. The sensor produces two pulses for each turn of the paddle wheel. The frequency of the pulses is related to the flow rate by:

Q = f / 7.5

### Wiring the Sensor

The sensor has a red lead (+5 VDC), a black lead (0 VDC), and a yellow lead (signal). The sensor needs to be on a pin capable of interrupts. This is either pin 2 or pin 3 on the Arduino Uno.

Both the LED pin and the sensor pin can be changed at the to of the program by chaning pinLED and pinSENSOR respectively.

The push button should be connected to an interrupt pin (i.e. 2 or 3 on the Arduino Uno).

### Changing the Alarm Speed

The alarm level can be changed by pressing the "Teach" button. The LED will flash three times to signal the sensor was taught, and then the LED alarm will light every time the flow is faster than the taught speed.
