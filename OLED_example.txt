// 1602-OLED-Arduino-Library/OLedI2C.cpp
// keywords.txt / OLedI2C.cpp / OLedI2C.h
// The 3 files should be in %your arduino dir%\libraries\OLedI2C\
// The directory name must match the library name for libraries to work.

/*
This is my first Library to make writing to the OLED 1602
 Display much easier, the display is based on the SSD1311.
 The display has 16 characters and 2 lines.
 The library is far from complete and may be prone to errors.
 Feedback welcome, visit www.gadjet.co.uk
 Phil Grant 2013
 Scrolling contributed by Nathan Chantrell http://nathan.chantrell.net/
 Updated 06/11/2013 to include the cursPos data in the sendString function
 sendString("string", col, row)
 */
#include "OLedI2C.h"

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include "Wire.h"
////////////////#define OLED_Address 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

OLedI2C::OLedI2C(){
}
OLedI2C::~OLedI2C(){
}

uint8_t _OLED_Address; //global variable initialization

void OLedI2C::init(uint8_t OLED_Address) {

  _OLED_Address = OLED_Address;

  // *** I2C initial *** //
  delay(100);
  sendCommand(0x2A); //function set (extended command set)
  sendCommand(0x71); //function selection A
  sendData(0x00); // disable internal VDD regulator (2.8V I/O). data(0x5C) = enable regulator (5V I/O)
  sendCommand(0x28); //function set (fundamental sendCommand set)
  sendCommand(0x08); //display off, cursor off, blink off
  sendCommand(0x2A); //function set (extended command set)
  sendCommand(0x79); //OLED command set enabled
  sendCommand(0xD5); //set display clock divide ratio/oscillator frequency
  sendCommand(0x70); //set display clock divide ratio/oscillator frequency
  sendCommand(0x78); //OLED command set disabled
  sendCommand(0x09); //extended function set 4 line
  sendCommand(0x06); //COM SEG direction
  sendCommand(0x72); //function selection B
  sendData(0x00); //ROM CGRAM selection
  sendCommand(0x2A); //function set (extended command set)
  sendCommand(0x79); //OLED command set enabled
  sendCommand(0xDA); //set SEG pins hardware configuration
  sendCommand(0x10); //set SEG pins hardware configuration
  sendCommand(0xDC); //function selection C
  sendCommand(0x00); //function selection C
  sendCommand(0x81); //set contrast control
  sendCommand(0x7F); //set contrast control
  sendCommand(0xD9); //set phase length
  sendCommand(0xF1); //set phase length
  sendCommand(0xDB); //set VCOMH deselect level
  sendCommand(0x40); //set VCOMH deselect level
  sendCommand(0x78); //OLED command set disabled
  sendCommand(0x28); //function set (fundamental command set)
  sendCommand(0x01); //clear display
  sendCommand(0x80); //set DDRAM address to 0x00
  sendCommand(0x0C); //display ON

  delay(150);
  sendCommand(0x0C);  	// **** Turn on Display
  delay(150);
}

// void OLedI2C::cursPos(uint8_t col, uint8_t row)
// {
// int row_offsets[] = { 0x00, 0x40 };
// sendCommand(0x80 | (col + row_offsets[row]));
// }

void OLedI2C::cursPos(uint8_t col, uint8_t row)
{
  int row_offsets[] = {
    0x00, 0x20, 0x40, 0x60   };// **************THIS WAS THE CHANGE FOR 4 LINES
  sendCommand(0x80 | (col + row_offsets[row])); //was 0x80
}

// NEW 03-23-2015
// cloumn, row / setCursor
void OLedI2C::setCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = {
    0x00, 0x20, 0x40, 0x60   };// **************
  sendCommand(0x80 | (col + row_offsets[row]));
}

void OLedI2C::clearLcd()
{
  sendCommand(0x01);
}

// arduino com.
void OLedI2C::clear() // *********Compatible with LiquidCrystal lib.
{
  sendCommand(0x01);
}

void OLedI2C::home()
{
  sendCommand(0x02);
}

void OLedI2C::lcdOff()
{
  sendCommand(0x08);  	// **** Turn on Off
}

void OLedI2C::lcdOn()
{
  sendCommand(0x0C);  	// **** Turn on On
}

void OLedI2C::noDisplay() // *********Compatible with LiquidCrystal lib.
{
  sendCommand(0x08);  	// **** Turn on Off
}

void OLedI2C::display() // *********Compatible with LiquidCrystal lib.
{
  sendCommand(0x0C);  	// **** Turn on On
}

// Turns the underline cursor on/off
void OLedI2C::noCursor() {
  sendCommand(0x0C);   // **** Turn Off underline cursor
}
void OLedI2C::cursor() {
  sendCommand(0x0E);  	// **** Turn On underline cursor
}

// Turn on and off the blinking cursor
void OLedI2C::noBlink() {
  sendCommand(0x0C);  	// **** Turn Off blinking cursor
}
void OLedI2C::blink() {
  sendCommand(0x0D);  	// **** Turn On blinking cursor
}


void OLedI2C::sendCommand(unsigned char command)
{
  Wire.beginTransmission(_OLED_Address); 	// **** Start I2C
  Wire.write(OLED_Command_Mode);     		// **** Set OLED Command mode
  Wire.write(command);
  Wire.endTransmission();                 	// **** End I2C
}

// ARDUINO 0.23 ~ ARDUINO 1.0.0 and Up ======= Print ==============================================
#if (ARDUINO <  100)
inline void OLedI2C::write(uint8_t value) {
  sendData(value);
}
#else
inline size_t OLedI2C::write(uint8_t value) {
  sendData(value);
}
#endif

void OLedI2C::setDoubleH(uint8_t MODE) // 09-19-2015 / Double Height Display MODE 0~4
// MODE: "0"=Normal 4-line, "1"=Bottom half Double Height, "2"=Middle Double Height, "3"=Top/Bottom Double Height, "4"=Top Double Height
{
  sendCommand(0x2A);// Function Set  (extended command set / Extension register, RE ("1")set) B00101010
  sendCommand(B00001001);//Extended Function Set (FW = "0": 5-dot font width, black/white invert cursor DIS,NW = "1": 3-line or 4-line display mode)
  switch (MODE) {
  case 0:    //MODE 0 4x20-line
    sendCommand(0x28);// Function Set (Go Back to Fundamental Command Set)//101000
    break;
  case 1:    //MODE 1 0x10 / Double Height (4-line)/Display-dot shift
    sendCommand(B00010000); //MODE 2
    sendCommand(0x2C);//101100 Function Set ( when (N=1 :4-line )and(NW=1), Double height =1 Enable, Extension register, RE"0", Extension register, IS"0" )
    break;
  case 2:    //MODE 2 0x14 / Double Height (4-line)/Display-dot shift
    sendCommand(B00010100);   //MODE 2 0x14 / Double Height (4-line)/Display-dot shift
    sendCommand(0x2C);//101100 Function Set ( when (N=1 :4-line )and(NW=1), Double height =1 Enable, Extension register, RE"0", Extension register, IS"0" )
    break;
  case 3:    //MODE 3 0x18 / Double Height (4-line)/Display-dot shift (DH’ = "0": dot scroll enable (POWER UP))
    sendCommand(B00011000);
    //sendCommand(B00011001); //MODE 3 0x19 / Double Height (4-line)/Display-dot shift (DH’ = "1": display shift enable)
    sendCommand(0x2C);//101100 Function Set ( when (N=1 :4-line )and(NW=1), Double height =1 Enable, Extension register, RE"0", Extension register, IS"0" )
    break;
  case 4:
    sendCommand(B00011100);  //MODE 4 0x1C / Double Height (4-line)/Display-dot shift(DH’ = "0": display shift DIS)
    sendCommand(0x2C);//101100 Function Set ( when (N=1 :4-line )and(NW=1), Double height =1 Enable, Extension register, RE"0", Extension register, IS"0" )
    break;
  }
}

void OLedI2C::sendFloat(float digit, uint8_t dec, uint8_t nad, uint8_t col, uint8_t row)
{
  char line[10];//Ten characters, I hope that's enough
  dtostrf(digit,dec,nad,line);//Convert the float value to a string
  sendString(line, col, row);
}

void OLedI2C::setContrast(unsigned char contrast) // contrast as 0x00 to 0xFF
{
  //Set OLED Command set
  sendCommand(0x2A);        //Function Set  N = 1, BE = 0, RE = 1 Set, REV = "0": normal display (POR)  B00101010
  sendCommand(0x79);        //OLED Characterization / 0x79 B1111001 =  OLED command set is enabled
  sendCommand(0x81);  	// Set Contrast
  sendCommand(contrast);	// send contrast value
  sendCommand(0x78);  	// OLED Characterization / 0x78 B1111000 =Exiting Set OLED Command set disabled (POR)
  sendCommand(0x28);       // Function Set / B101000 (Go Back to Fundamental Command Set)
}

void OLedI2C::sendString(const char *String, uint8_t col, uint8_t row)
{
  cursPos(col, row);
  unsigned char i=0;
  while(String[i])
  {
    sendData(String[i]);      // *** Show String to OLED
    i++;
  }
}

void OLedI2C::sendData(unsigned char data)
{
  Wire.beginTransmission(_OLED_Address);  	// **** Start I2C
  Wire.write(OLED_Data_Mode);     		// **** Set OLED Data mode
  Wire.write(data);
  Wire.endTransmission();                     // **** End I2C
}

void OLedI2C::scrollString(char* message, byte row, unsigned int time)//written by Nathan Chantrell http://nathan.chantrell.net/
{
  char buffer[16];
  for (byte i=0;i<strlen(message)+16;i++) {
    byte pos = i+1;
    for (byte j=0;j<16;j++) {
      if ((pos<16)||(pos>strlen(message)+15)) { // pad and trail with blank spaces
        buffer[j]=' ';
      }
      else buffer[j]=message[pos-16];
      pos++;
    }
    //cursPos(0,row); removed by PG
    sendString(buffer, 0, row); //Edited by PG tho include the cursor pos within the sendString command
    delay(time);
  }
}




//#define OLED_Command_Mode 0x80
//#define OLED_Data_Mode 0x40
// NEW 03-23-2015
// Allows us to fill the first 8 CGRAM locations
// with custom characters
void OLedI2C::createChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7; // we only have 8 locations 0-7
  //Wire.beginTransmission(_OLED_Address);
  //Wire.write(OLED_Data_Mode | (location << 3)); // SETCGRAMADDR 0x40  [ Wire.write(B01000000); ]
  //Wire.endTransmission();

  Wire.beginTransmission(_OLED_Address); 	// **** Start I2C
  Wire.write(OLED_Command_Mode); // 0x80
  Wire.write(0x40 | (location << 3));      // **** Set OLED Command mode
  Wire.endTransmission();                  // **** End I2C
 

  for (uint8_t i = 0 ; i < 8 ; i++) {
    Wire.beginTransmission(_OLED_Address); 	// **** Start I2C
    Wire.write(OLED_Data_Mode);     		// **** Set OLED Data mode
    Wire.write(charmap[i]);
    Wire.endTransmission();                     
  }
}
 
/*
// NEW 03-31-2015
// Allows us to fill the first 8 CGRAM locations
// with custom characters
void OLedI2C::createChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7;            // we only have 8 locations 0-7

    sendCommand(0x40 | (location << 3));

  for (int i=0; i<8; i++)
  {
    sendData(charmap[i]);      // call the virtual write method
  }
}
*/
