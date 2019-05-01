/* -------------------------------------------------------
 *  
 *    Project:    DAC081S101 SPI Library
 *    
 *    Author:     M. Molter
 *    
 *    Date:       15 APR 2019
 *    
 *    Desc:       Create a basic library for the DAC081S101
 *                digital-to-analog converter. The chip is a 
 *                small (TSOT23), 8-bit, rail-to-rail DAC 
 *                that communicates over the SPI bus.
 *                
 *                The main goal of this project is to gain
 *                experience writing SPI libraries.
 *                
 *                The datasheet is on GitHub.
 *  
 * ------------------------------------------------------*/

/* CHIP PINS
 *  
 *  1 - Vout:        DAC Analog Output Voltage
 *  2 - GND:         Ground
 *  3 - Va:          Power Supply/Reference Voltage
 *  4 - Din:         Serial Data In
 *  5 - SCLK:        Serial Clock In
 *  6 - NOT SYNC:    NOT Chip Select
 */

/* SPI COMMS PROTOCOL
 *  
 *  STEP 1) Write LOW To NOT SYNC (PIN 6)
 *  
 *  STEP 2) Clock data in on Din, transfers on FALLING SCLK edges.
 *  
 *  STEP 3) Chip executes on 16th falling edge, NOT SYNC can be
 *          brought back to HIGH.
 *          
 * INTERNAL REGISTER
 *          
 *  DB16: X     
 *  DB15: X
 *  DB14: PD1
 *  DB13: PD0
 *  DB12: D7
 *  DB11: D6
 *  DB10: D5
 *  DB9:  D4
 *  DB8:  D3
 *  DB7:  D2
 *  DB6:  D1
 *  DB5:  D0
 *  DB4:  X
 *  DB3:  X
 *  DB2:  X
 *  DB1:  X
 *  
 * CONTROL REGISTER SETTINGS
 * 
 *  MODE                            DB14/PD1    DB13/PD0
 *  
 *  Normal Operation                   0           0
 *  Power-down with 1kOhm to GND       0           1
 *  Power-down with 100kOhm to GND     1           0
 *  Power-down with Hi-Z               1           1
 */

#define SS  5
#define DO  11
#define CLK 13

enum DACMode {
  NORMAL,
  PULLDOWN1K,
  PULLDOWN100K,
  HIZ
};

currentMode  = DACMode.NORMAL;
currentValue = 0; 

void setup() {

}

void loop() {

}

void writeToPot(int value) {
  // Construct blank data packet.
  unsigned int DATABYTE = 0x0000;

  // Append mode command.
  unsigned int MODEBYTE = 0b00;
  switch (currentMode){
    case DACMode.NORMAL:
      MODEBYTE = 0b00;
      break;
    case DACMode.PULLDOWN1K:
      MODEBYTE = 0b01;
      break;
    case DACMode.PULLDOWN100K:
      MODEBYTE = 0b10;
      break;
    case DACMode.HIZ:
      MODEBYTE = 0b11;
      break;
  }

  // Value byte
  unsigned int VALUEBYTE = 0x00;

  if (value > 256)
    VALUEBYTE = 256;
  else if (value < 0)
    VALUEBYTE = 0;
  else
    VALUEBYTE = value;
  
  // Combine the mode and value bytes.
  DATEBYTE = (MODEBYTE << 12) | (VALUEBYTE << 4)

  // Send out the byte.
  digitalWrite(SS, LOW);
  shiftOut(DO, CLK, LSBFIRST, DATABYTE);
  digitalWrite(SS, HIGH);
}

void setDACMode(DACMode mode) {
  // Set the mode global variable.
  currentMode = mode;

  // Update the value on the chip.
  writeToPot(currentValue);
}
