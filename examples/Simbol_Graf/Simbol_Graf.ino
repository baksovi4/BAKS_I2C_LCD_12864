#include <Wire.h>
#include <SPI.h>
#include <BAKS_I2C_LCD_12864.h>

// If use Arduino NANO
//#define SDA_PIN   4    //  A4   SDA
//#define SDL_PIN   5    //  A5   SDL

// If use ESP8266 NodeMCU
#define SDA_PIN   D1    //  D1   SDA
#define SCL_PIN   D2    //  D2   SCL

BAKS_I2C_LCD_12864 lcd;

// example bitmap
const byte picture [] PROGMEM = {
  0x1C, 0x22, 0x49, 0xA1, 0xA1, 0x49, 0x22, 0x1C,  // face
  0x10, 0x08, 0x04, 0x62, 0x62, 0x04, 0x08, 0x10,  // star destroyer
  0x4C, 0x52, 0x4C, 0x40, 0x5F, 0x44, 0x4A, 0x51,  // OK logo
};

unsigned char const Battery100[19] PROGMEM =
{   0,  0,  0,  0, 124, 198, 130, 186, 186, 130, 186, 186, 130, 186, 186, 130, 254,  0,  0}; //100%

unsigned char const Battery50[19]  PROGMEM =
{   0,  0,  0,  0, 124, 198, 130, 130, 130, 130, 186, 186, 130, 186, 186, 130, 254,  0,  0}; //70%

unsigned char const Battery25[19]  PROGMEM =
{   0,  0,  0,  0, 124, 198, 130, 130, 130, 130, 130, 130, 130, 186, 186, 130, 254,  0,  0}; //50%

unsigned char const Battery0[19]  PROGMEM =
{   0,  0,  0,  0, 124, 198, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 254,  0,  0}; //25%


int count = 100;   //  ms

void setup ()
{
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.begin();

  //lcd.ledOn();
  lcd.clear();
  lcd.textSize(4);
  lcd.gotoxy(6, 20);
  lcd.string("HELLO", 0);

  delay(count);
  lcd.ledOn();
  delay(count);
  lcd.ledOff();
  delay(count);
  lcd.ledOn();
  delay(count);
  lcd.ledOff();
  delay(count);
  lcd.ledOn();
  delay(count);
  lcd.ledOff();
  delay(count);
  lcd.ledOn();
  
  //**** ONLY FOR ARDUINO BOARD
  //Choose another speed using TWBR (Two Wire Bit Rate) register:

  //TWBR = 12;  // 400 kHz (maximum)
  //TWBR = 32;  // 200 kHz
  //TWBR = 72;  // 100 kHz (default)
  //TWBR = 152;  // 50 kHz

  //TWBR = 78;  // 25 kHz
  //TWSR |= bit (TWPS0);  // change prescaler

  //TWBR = 158;  // 12.5 kHz
  //TWSR |= bit (TWPS0);  // change prescaler
  //*********************************************
  /*
    // draw all available letters
    for (int i = ' '; i <= 0x7F; i++)
      lcd.letter (i);

    lcd.gotoxy (40, 56);
    lcd.blit (Battery100, sizeof Battery100);
    lcd.gotoxy (60, 56);
    lcd.blit (Battery50, sizeof Battery50);
    lcd.gotoxy (80, 56);
    lcd.blit (Battery25, sizeof Battery25);
    lcd.gotoxy (100, 56);
    lcd.blit (Battery0, sizeof Battery0);

    // black box
    lcd.clear (6, 40, 30, 63, 0xFF);

    // draw text in inverse
    lcd.gotoxy (40, 40);
    lcd.string ("from BAKS.", true);

    // bit blit in a picture
    lcd.gotoxy (40, 56);
    lcd.blit (picture, sizeof picture);

    // draw a framed rectangle
    lcd.frameRect (40, 49, 60, 53, 1, 1);

    // draw a white diagonal line
    lcd.line (6, 40, 30, 63, 1);
  */
} 

void loop () {

  /*
    lcd.clear();

    lcd.gotoxy (30, 56);
    lcd.print("Hello BAKS");

    delay(3000);
    lcd.clear();
    lcd.print("Circle painting...");
    lcd.circle(20,32,20,1);
    //lcd.fillCircle(60,32,16,1);
    lcd.gotoxy(80,56);
    delay(2000);
  */
}
