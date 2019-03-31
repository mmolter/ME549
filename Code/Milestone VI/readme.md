# Milestone VI

The purpose of milestone VI is to interface with an I2C chip.

For this assignment, I will be working with the MC7940M I2C real-time clock/calendar. This chip keeps time using a 32.768 kHz external quartz crystal, and provides a lot of calendar functionality that other real-time clocks (RTCs) do not. For example, you can read a register on the chip to determine what day of the week it is. Once you set the time by changing registers on the chip, it automatically calculates the number of days in a month, whether or not to account for leap year, and other conveniences. Further, all the datetime information is stored in binary coded decimal format. This allows data to be directly fed into something like a 7-segment display.

Communicating with an I2C chip is made simple by the "Wire.h" library. The first step is to read the datasheet thoroughly. The principle behind I2C is that each chip has a series of registers to store/set data and configuration parameters. For example, one-bit on the RTCSEC register of the MC7940M starts or stops the clock. The I2C protocol is simply used to transfer new information to these registers, or read information from these registers.

Communication starts by initializing the Arduino to listen on the I2C bus.

```
Wire.begin();
```

Next, a transmission session is started with the hexidecimal address of the chip. I often define this value as a constant. Next, the name of the address you want to change is written onto the bus, followed by the byte you want to place into that register. Then you declare the end of the transmission. You can only change or read a single register per transmission; however, some registers contain multiple bytes of information that needs to be written or read.

```
#define ADDRESS  B1101111
#define RTCSEC   0x00

Wire.beginTransmission(ADDRESS);
Wire.write(RTCSEC);
Wire.write(B10000000);
Wire.endTransmission();
```

Similarly, a register can be read using:

```
String getYear(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCYEAR);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte YRTEN = (val & B11110000) >> 4;
  byte YRONE = (val & B00001111);

  return "20" + String(YRTEN) + String(YRONE);
}
```

This particular chip reports values as binary coded decimal. In some instances--as when communicating with a display--this may be more convenient; however in my case, I had to do a lot of work to convert between binary numbers and their binary coded decimal equivalents. I still do not have code to set the clock to a users defined value. That may be a good project for the final project.
