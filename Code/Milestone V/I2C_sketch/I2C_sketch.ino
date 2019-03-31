#include<Wire.h>

#define ADDRESS B1101111

#define RTCSEC   0x00
#define RTCMIN   0x01
#define RTCHOUR  0x02
#define RTCWKDAY 0x03
#define RTCDATE  0x04
#define RTCMTH   0x05
#define RTCYEAR  0x06
#define RTCC     0x07

void setup() {
  // Begin serial communications.
  Serial.begin(115200);
  Serial.println("Starting...");

  // Join the I2C buss.
  Wire.begin();

  // Start the RTC.
  Wire.beginTransmission(ADDRESS);  
  Wire.write(RTCSEC);
  Wire.write(B10000000);
  Wire.endTransmission();
  
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCMIN);
  Wire.write(B00000011);
  Wire.endTransmission();
    
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCHOUR);
  Wire.write(B00001001);
  Wire.endTransmission();

  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCDATE);
  Wire.write(B00100111);
  Wire.endTransmission();

  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCMTH);
  Wire.write(B00000011);
  Wire.endTransmission();

  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCYEAR);
  Wire.write(B00011001);
  Wire.endTransmission(ADDRESS);
  
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCC);
  Wire.write(B11000000);
  Wire.endTransmission();
  
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCWKDAY);
  Wire.write(B00000010);
  Wire.endTransmission();
}

void loop() {

  Serial.print(getWeekday());
  
  Serial.print(", ");

  Serial.print(getDay());
  Serial.print(' ');
  Serial.print(getShortMonth());
  Serial.print(' ');
  Serial.print(getYear());

  Serial.print(' ');
  
  Serial.print(getHours());
  Serial.print(':');
  Serial.print(getMinutes());
  Serial.print(':');
  Serial.print(getSeconds());
  Serial.print(' ');
  Serial.print(getAMPM());
  Serial.print('\n');

  delay(1000);
}

String getAMPM(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCHOUR);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte AMPM = (val & B00100000) >> 5;

  switch(AMPM){
    case 0:
      return "AM";
    case 1:
      return "PM";
  }
}

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

String getDay(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCDATE);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte DATETEN = (val & B00110000) >> 4;
  byte DATEONE = (val & B00001111);

  return String(DATETEN) + String(DATEONE);
}

String getMonth(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCMTH);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte MTHTEN = (val & B00010000) >> 4;
  byte MTHONE = (val & B00001111);

  return String(MTHTEN) + String(MTHONE);
}

String getShortMonth(){
  switch(getMonth().toInt()){
    case 1:
      return "JAN";
    case 2:
      return "FEB";
    case 3:
      return "MAR";
    case 4:
      return "APR";
    case 5:
      return "MAY";
    case 6:
      return "JUN";
    case 7:
      return "JUL";
    case 8:
      return "AUG";
    case 9:
      return "SEP";
    case 10:
      return "OCT";
    case 11:
      return "NOV";
    case 12:
      return "DEC";
    default:
      return "ERROR";
  }
}

String getWeekday(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCWKDAY);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte WKDAY = val & B00000111;

  switch(WKDAY){
    case 1:
      return "Monday";
    case 2:
      return "Tuesday";
    case 3:
      return "Wednesday";
    case 4:
      return "Thursday";
    case 5:
      return "Friday";
    case 6:
      return "Saturday";
    case 7:
      return "Sunday";
    default:
      return "ERROR";
  }
}

String getHours(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCHOUR);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte HRONE = (B00001111 & val);
  byte HRTEN = (B00010000 & val) >> 4;

  return String(HRTEN) + String(HRONE);
}

String getMinutes(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCMIN);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte MINONE = (B00001111 & val);
  byte MINTEN = (B01110000 & val) >> 4;

  return String(MINTEN) + String(MINONE);
}

String getSeconds(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(RTCSEC);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);

  byte val = Wire.read();

  byte SECONE = (B00001111 & val);
  byte SECTEN = (B01110000 & val) >> 4;

  return String(SECTEN) + String(SECONE);
}
