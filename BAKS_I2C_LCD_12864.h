/*
 BAKS_I2C_LCD_12864.h
 
 Edited by BAKS
 Date: 1 November 2019.
 
 * These changes required hardware changes to pin configurations
 
 PERMISSION TO DISTRIBUTE
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in 
 all copies or substantial portions of the Software.
 
 
 LIMITATION OF LIABILITY
 
 The software is provided "as is", without warranty of any kind, express or implied, 
 including but not limited to the warranties of merchantability, fitness for a particular 
 purpose and noninfringement. In no event shall the authors or copyright holders be liable 
 for any claim, damages or other liability, whether in an action of contract, 
 tort or otherwise, arising from, out of or in connection with the software 
 or the use or other dealings in the software. 
 
 */


#ifndef BAKS_I2C_LCD_12864_H
#define BAKS_I2C_LCD_12864_H

// #define WRITETHROUGH_CACHE

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <avr/pgmspace.h>

// MCP23017 registers (everything except direction defaults to 0)

#define IODIRA   0x00   // IO direction  (0 = output, 1 = input (Default))
#define IODIRB   0x01
#define IOPOLA   0x02   // IO polarity   (0 = normal, 1 = inverse)
#define IOPOLB   0x03
#define GPINTENA 0x04   // Interrupt on change (0 = disable, 1 = enable)
#define GPINTENB 0x05
#define DEFVALA  0x06   // Default comparison for interrupt on change (interrupts on opposite)
#define DEFVALB  0x07
#define INTCONA  0x08   // Interrupt control (0 = interrupt on change from previous, 1 = interrupt on change from DEFVAL)
#define INTCONB  0x09
#define IOCON    0x0A   // IO Configuration: bank/mirror/seqop/disslw/haen/odr/intpol/notimp
//#define IOCON 0x0B  // same as 0x0A
#define GPPUA    0x0C   // Pull-up resistor (0 = disabled, 1 = enabled)
#define GPPUB    0x0D
#define INFTFA   0x0E   // Interrupt flag (read only) : (0 = no interrupt, 1 = pin caused interrupt)
#define INFTFB   0x0F
#define INTCAPA  0x10   // Interrupt capture (read only) : value of GPIO at time of last interrupt
#define INTCAPB  0x11
#define GPIOA    0x12   // Port value. Write to change, read to obtain value
#define GPIOB    0x13
#define OLLATA   0x14   // Output latch. Write to latch output.
#define OLLATB   0x15

			/************************************ Pins MCP23017 chip ************************************************
			*													*
			*                 Purpose  NAME   PIN                    PIN   NAME      Purpose			*
			* 	                                _____________							*
			*                   PORTB  GPB0   1 ___|    |||||    |___ 28   GPA7      PORTA				*
			*                   PORTB  GPB1   2 ___|     \_/     |___ 27   GPA6      PORTA				*
			*                   PORTB  GPB2   3 ___|             |___ 26   GPA5      PORTA				*
			*                   PORTB  GPB3   4 ___|             |___ 25   GPA4      PORTA				*
			*                   PORTB  GPB3   5 ___|             |___ 24   GPA3      PORTA				*
			*                   PORTB  GPB3   6 ___|             |___ 23   GPA2      PORTA				*
			*                   PORTB  GPB3   7 ___|             |___ 22   GPA1      PORTA				*
			*                   PORTB  GPB3   8 ___|             |___ 21   GPA0      PORTA				*
			*                   POWER  VDD    9 ___|             |___ 20   INTA      Interrupt output for PORTA	*
			*                  GROUND  VSS   10 ___|             |___ 19   INTB      Interrupt output for PORTB	*
			*                      NC  NC    11 ___|             |___ 18   RESET     Hardware reset			*
			*      Serial clock input  SCK   12 ___|             |___ 17   A2        Hardware address pin		*
			*      Serial data I/O     SDA   13 ___|             |___ 16   A1        Hardware address pin		*
			*                      NC  NC    14 ___|             |___ 15   A0        Hardware address pin		*
			*                                      |_____________|							*
			*                                      									*
			********************************************************************************************************/

/*************************************** Pins I2C expander for lcd 1602/2001/12864 on MCP23017 chip ***************************************************
                                                                                        
                     o1 o2 o3 o4 o5 o6        
                     |  |  |  |  |  |                                                  
                   __|__|__|__|__|__|__       
                  |  o  o  o  o  o  o  |      PIN   NAME    PURPOUSE                   |  PIN   NAME    PURPOUSE
                  |                    |       
      GND    1 ___| o  o   1602        |       1    GND     Ground                     |  o1    GND     Ground for MCP23017
      VCC    2 ___| o  o   \           |       2    VCC     Supply voltage for logic   |  o2    VCC     +5V Power for MCP23017
      Vo     3 ___| o  o   2001        |       3    Vo      Operating voltage for LCD  |  o3    SCL     connect to Arduino pin A5 (I2C) (ESP8266 - )
      PA7    4 ___| o  o   \           |       4    PA7     Enable data transfer       |  o4    SDA     connect to Arduino pin A4 (I2C) (ESP8266 - )
      PA6    5 ___| o  o   12864       |       5    PA6     1 = read, 0 = write        |  o5    RST     Tie to +5V via 10K resistor (reset signal)
      PA5    6 ___| o  o   \           |       6    PA5     1 = data, 0 = instruction  |  o6    INTA    Interrupt output for PORTA
      PB0    7 ___| o  o   I2C         |       7    PB0     Data bit 0                 |  o7    INTB    Interrupt output for PORTB
      PB1    8 ___| o  o   exspander   |       8    PB1     Data bit 1                 |____________________________________________________________
      PB2    9 ___| o  o               |       9    PB2     Data bit 2
      PB3   10 ___| o  o               |      10    PB3     Data bit 3
      PB4   11 ___| o  o               |      11    PB4     Data bit 4
      PB5   12 ___| o  o               |      12    PB5     Data bit 5
      PB6   13 ___| o  o               |      13    PB6     Data bit 6
      PB7   14 ___| o  o               |      14    PB7     Data bit 7
      PA4   15 ___| o  o               |      15    PA4     Chip select for IC1
      PA3   16 ___| o  o               |      16    PA3     Chip select for IC2
      PA2   17 ___| o                  |      17    PA2     Reset signal 1 = not reset, 0 = reset
      Vout  18 ___| o                  |      18    Vout    Negative voltage
      VCC   19 ___| o                  |      19    VCC*    Power supply for LED light (+5V)              A=anode
      PA1   20 ___| o                  |      20    PA1*    GND for LED light (controlled by transistor)  K=cathode
                  |____________________|        

******************************************************************************************************************************************************/

/**************************************************************** LCD RG12864A-GKW-V ******************************************************************

         ____________________________________________________________
        |  ________________________________________________________  |
        | | 							   | |
        | |                                                        | |
        | |                                                        | |
        | |       __   __          __   ___            ___         | |
        | | |    |  | |  \    /|  |  | /   \          /   \  |   | | |
        | | |    |    |   |  / |    /  |___|  \   /   |___   |___| | |
        | | |    |    |   |    |   /   |   |    X     |   \      | | |
        | | |__| |__| |__/   __|_ /___ \___/  /   \   \___/      | | |
        | |                                                        | |
        | |                                                        | |
        | |                                                        | |
        | |                                                        | |
        | |________________________________________________________| |
        |                   LCD - RG12864A-GKW-V                     |
        | O  O  O  O  O  O  O  O  O  O  O  O  O  O  O  O  O  O  O  O |
        |_|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|__|_|
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |---->  pin 20 -   K  - Power Supply for LED backlight ( - )
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |------->  pin 19 -   A  - Power Supply for LED backlight ( + )
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |---------->  pin 18 - Vout - Negative Voltage output
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |------------->  pin 17 - /RES - Reset signal
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |---------------->  pin 16 -  CS2 - Select Column 65~ Column 128
          |  |  |  |  |  |  |  |  |  |  |  |  |  |  |------------------->  pin 15 -  CS1 - Select Column 1~ Column 64
          |  |  |  |  |  |  |  |  |  |  |  |  |  |---------------------->  pin 14 -  DB7 - Data bit 7
          |  |  |  |  |  |  |  |  |  |  |  |  |------------------------->  pin 13 -  DB6 - Data bit 6
          |  |  |  |  |  |  |  |  |  |  |  |---------------------------->  pin 12 -  DB5 - Data bit 5
          |  |  |  |  |  |  |  |  |  |  |------------------------------->  pin 11 -  DB4 - Data bit 4
          |  |  |  |  |  |  |  |  |  |---------------------------------->  pin 10 -  DB3 - Data bit 3
          |  |  |  |  |  |  |  |  |------------------------------------->  pin 9 -   DB2 - Data bit 2
          |  |  |  |  |  |  |  |---------------------------------------->  pin 8 -   DB1 - Data bit 1
          |  |  |  |  |  |  |------------------------------------------->  pin 7 -   DB0 - Data bit 0
          |  |  |  |  |  |---------------------------------------------->  pin 6 -    E  - Enable data transfer on 1 -> 0 transition
          |  |  |  |  |------------------------------------------------->  pin 5 -   R/W - 1 = not reset, 0 = reset
          |  |  |  |---------------------------------------------------->  pin 4 -   D/I - 1 = data, 0 = instruction
          |  |  |------------------------------------------------------->  pin 3 -   Vo  - (Variable) Operating voltage for LCD
          |  |---------------------------------------------------------->  pin 2 -   VDD - Supply voltage for logic 5.0V
          |------------------------------------------------------------->  pin 1 -   VSS - Ground

******************************************************************************************************************************************************/

// GPA port - these show which wires from the LCD are connected to which pins on the I/O expander

/********************************* FOR LCD - RG12864A-GKW-V with MCP23017 EXPANDER *************************************/
//												Pins MCP23017 chip	|
#define LCD_LED_BIT 0b00000010   // BASE transistor J3Y (ON\OFF LED CATODE LCD)		0x00	  22  	GPA1		|
#define LCD_RESET   0b00000100   // reset 	                                     	0x04	  23	GPA2		|
#define LCD_CS2     0b00001000   // chip select 2  	                            	0x08	  24	GPA3		|
#define LCD_CS1     0b00010000   // chip select 1  	                            	0x10	  25	GPA4		|
#define LCD_ENABLE  0b00100000   // enable by toggling high/low  	              	0x20	  26	GPA5		|
#define LCD_READ    0b01000000   // x1xxxxxx = read; x0xxxxxx = write  	        	0x40	  27	GPA6		|
#define LCD_DATA    0b10000000   // 1xxxxxxx = data; 0xxxxxxx = instruction	  	0x80	  28    GPA7		|
/***********************************************************************************************************************/

// Commands sent when LCD in "instruction" mode (LCD_DATA bit set to 0)

#define EXPANDER_ADDRESS 0x20
#define LCD_LED_PIN      0x00		// 
#define LCD_ON           0x3F
#define LCD_OFF          0x3E
#define LCD_SET_ADD      0x40   	// plus X address (0 to 63) 
#define LCD_SET_PAGE     0xB8   	// plus Y address (0 to 7)
#define LCD_DISP_START   0xC0   	// plus X address (0 to 63) - for scrolling

class BAKS_I2C_LCD_12864 : public Print
{
private:
  
  byte _chipSelect;  // currently-selected chip (LCD_CS1 or LCD_CS2)
  byte _lcdx;        // current x position (0 - 127)
  byte _lcdy;        // current y position (0 - 63)

  byte _port;        // port that the MCP23017 is on (should be 0x20 to 0x27)
  byte _ssPin;       // if non-zero use SPI rather than I2C (and this is the SS pin)

  void expanderWrite (const byte reg, const byte data);
  byte readData ();
  void startSend ();    // prepare for sending to MCP23017  (eg. set SS low)
  void doSend (const byte what);  // send a byte to the MCP23017
  void endSend ();      // finished sending  (eg. set SS high)

  boolean _invmode;
  boolean _cathode;// = false;
  byte _textsize;
  
  
#ifdef WRITETHROUGH_CACHE
  byte _cache [64 * 128 / 8];
  int  _cacheOffset;
#endif
  
public:
  
  // constructor
  BAKS_I2C_LCD_12864 () : _port (0x20), _ssPin (10), _invmode(false),  _cathode(false) {};
  
  //void begin (const byte port = 0x20, const byte i2cAddress = 0, const byte ssPin = 0);
  void begin (uint8_t port, uint8_t i2cAddress, uint8_t ssPin);
  void begin (void);
  void cmd (const byte data);
  void gotoxy (byte x, byte y);
  void writeData (byte data, const boolean inv);
  void writeData (byte data) { writeData(data, _invmode);}
  void letter (byte c, const boolean inv);
  void letter (byte c) {letter(c, _invmode);}
  void string (const char * s, const boolean inv);
  void string (const char * s) {string(s, _invmode);}
  void blit (const byte * pic, const unsigned int size);
  void clear (const byte x1 = 0,    // start pixel
              const byte y1 = 0,     
              const byte x2 = 127,  // end pixel
              const byte y2 = 63,   
              const byte val = 0);   // what to fill with 
  void setPixel (const byte x, const byte y, const byte val = 1);
  void fillRect (const byte x1 = 0,   // start pixel
                const byte y1 = 0,     
                const byte x2 = 127, // end pixel
                const byte y2 = 63,    
                const byte val = 1);  // what to draw (0 = white, 1 = black) 
  void frameRect (const byte x1 = 0,    // start pixel
                 const byte y1 = 0,     
                 const byte x2 = 127, // end pixel
                 const byte y2 = 63,    
                 const byte val = 1,    // what to draw (0 = white, 1 = black) 
                 const byte width = 1);
  void line  (const byte x1 = 0,    // start pixel
              const byte y1 = 0,     
              const byte x2 = 127,  // end pixel
              const byte y2 = 63,   
              const byte val = 1);  // what to draw (0 = white, 1 = black) 
  void scroll (const byte y = 0);   // set scroll position

  void ledOn (void);	// LCD backlight ON
  void ledOff (void);	// LCD backlight OFF
  void circle (const byte x = 64,     // Center of circle
               const byte y = 32,
               const byte r = 30,     // Radius
               const byte val = 1);   // what to draw (0 = white, 1 = black)
  void fillCircle (const byte x = 64,     // Center of circle
                   const byte y = 32,
                   const byte r = 30,     // Radius
                   const byte val = 1);   // what to draw (0 = white, 1 = black)

#if defined(ARDUINO) && ARDUINO >= 100
	size_t write(uint8_t c) {letter(c, _invmode); return 1; }
#else
	void write(uint8_t c) { letter(c, _invmode); }
#endif

  void setInv(boolean inv) {_invmode = inv;} // set inverse mode state true == inverse
  void textSize(const byte s = 1) {_textsize = (s > 0 && s < 5) ? s : _textsize;}
};

#endif  // BAKS_I2C_LCD_12864_H

