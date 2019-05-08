# Milestone V
## SPI Sensor Communication

The purpose of this milestone was to create a demo of an SPI-based chip. The chip I have chosen is the **Texas Instruments DAC081S101**. This chip is an 8-bit, rail-to-rail, digital-to-analog converter. While a number of these chips are available from major suppliers (e.g. Adafruit), I chose this chip specifically because it did not already have an SPI library written for it.

Serial Peripheral Interface (SPI) is four-wire communication protocol. The connections include a master in/slave out (MISO), Clock (SCLK), slave in/master out (MOSI), and chip select (SS). Communication begins when the master pulls the SS line low, and then begins shifting data out on the MOSI line by pulsing the SCLK line as it simultaneously reads in data on the MISO line. The communication is synchronous, and unlike UART, can operate at any speed, limited only by the communication hardware.

This particular chip implements a very simple version of SPI. The chip only contains a single 16-bit register. This register has two mode control bits, and room for an 8-bit byte containing the DAC output value. The remainder of this register is padded with ignored bits. 

My implemention in the demo manually shifts the bits out on the MOSI line rather than using the built-in ``<SPI.h>`` library. I wanted a full understanding of what was happening on the hardware level.
