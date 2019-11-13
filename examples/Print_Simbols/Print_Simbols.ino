#include <Wire.h>
#include <BAKS_I2C_LCD_12864.h>

// If use Arduino NANO
//#define SDA_PIN   4    //  A4   SDA
//#define SDL_PIN   5    //  A5   SDL

// If use ESP8266 NodeMCU
#define SDA_PIN   D1    //  D1   SDA
#define SCL_PIN   D2    //  D2   SCL

BAKS_I2C_LCD_12864 lcd;

// pull in extra font characters

#include "cp437_font.h"

// helper routine to display one character from the CP437 font set
void show_cp437_char (byte c, const boolean inv = false)
{
  for (byte x = 0; x < 8; x++)
    lcd.writeData (pgm_read_byte (&cp437_font [c] [x]), inv);
} // end of show_cp437_char

void setup () 
{
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  
  lcd.begin ();  

  delay(1000);
  
  lcd.ledOn();

  delay(1000);

  //**************** ONLY FOR ARDUINO BOARD
  //Choose another speed using TWBR (Two Wire Bit Rate) register:
  
  //TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz 
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz 
  
  //TWBR = 78;  // 25 kHz 
  //TWSR |= bit (TWPS0);  // change prescaler

  //TWBR = 158;  // 12.5 kHz 
  //TWSR |= bit (TWPS0);  // change prescaler
  //***********************************************************
  
 for (int i = 0; i <= 127; i++)
     show_cp437_char (i);
  
  delay (5000);

  for (int i = 128; i <= 255; i++)
     show_cp437_char (i);

  delay(2000);
  
  lcd.ledOff();
  
}  // end of setup

void loop () 
{

}  // end of loop
