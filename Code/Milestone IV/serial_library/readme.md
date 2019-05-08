# Milestone IV
## Serial Library

This is the first milestone in a series on the three major communication protocols (e.g. Serial, SPI, and I2C). The goal of this milestone is to establish communication with a serial device. I chose serial as my first communication milestone because I believed it to be the most robust, and easiest to implement.

This library communicates with a **OHAUS Scout Pro 200/400 g** lab balance. The scale has a USB output cable that can be directly connected to the USB port on an Arduino. Most current Arduinos contain an additional ATMEGA microcontroller acting as a liazon between the hardware USB port, and the on-board serial controller for the Arduino. This hardware is what let me easily communicate with the scale.

All of the features of the scale can be accessed through simple human-readable, ASCII commands. Tarring the scale or reading the current value only requires a single character command followed by a line return. The scale then reports either an ACK or the answer on the serial bus. 

In fact, the hardest part of this implementation was the human readable nature of the communication. Arduinos are not powerful enough to have built-in regular expression processing, so parsing apart human readable strings is a very manual process. 

The demo itself provides functions for tarring and reading the scale. 
