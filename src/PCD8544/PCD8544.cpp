#include <stdlib.h>
#include "PCD8544.h"

using namespace std;

PCD8544::PCD8544()
{
  // Initialize the base image here when we decide on the initial UI
}

PCD8544::~PCD8544()
{
}

void PCD8544::InitPCD8544()
{
  // Pulse reset low to reset internal registers
  DDRF = LCD_RST;
  PORTF = LCD_RST_LO;
  PORTF = LCD_RST_HI;

  // Assert the chip enable of the LCD
  // GET RID OF THIS SINCE TIED LOW IN DESIGN
  DDRF = LCD_SCE;       
  PORTF = LCD_SCE_LO;

  // Initiate ATMega32U4 as a master on the SPI bus
  // Set MOSI and SCK output, all others input
  DDRB = (1<<PB2)|(1<<PB1);

  // Enable SPI, Master, set clock rate fck/16
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

   //Set to active mode, vertical addressing, extended
   //instruction set.
  SendCommand(0x23);
  
  // Set Vop to (a + 16 * b)
  SendCommand(0x90);

  // Set temp coefficient
  // Taken from SparkFun arduino sketch
  SendCommand(0x04);

  // LCD Bias
  SendCommand(0x13);
  
  // Set to normal instruction set
  SendCommand(0x22);
   
  // Set to normal display mode
  SendCommand(0x0C);
}

// Function to clear the display
void PCD8544::ClearDisplay()
{
  // Write 0's to all 84 columns
  for (int i = 0; i < LCD_WIDTH; ++i)
    WriteDisplay(0x00);
}

void PCD8544::DisplayHeading(int headingValue)
{
  // Take in the heading value and map it to the appropriate image to display
  char headingArray[3];

  itoa(headingValue, headingArray, 10);

  DisplayString(headingArray);
}

void PCD8544::WriteDisplay(uint8_t column)
{
  DDRF = LCD_DC;        // Set PCD8544 to data input
  PORTF = LCD_DC_HI;

  // Start transmission
  SPDR = column;

  // Wait for transmission to complete
  while (!(SPSR & (1<<SPIF)));
  
  return;
}

//void PCD8544::LoadImage(unsigned char base_img)
//{

//}

//void PCD8544::EditImage(unsigned char new_img, coordinate_pair coords)
//{

//}

void PCD8544::ConvertImage()
{

}

void PCD8544::SendCommand(uint8_t command)
{
  DDRF = LCD_DC;        // Set PCD8544 to command input
  PORTF = LCD_DC_LO;
  
  // Start transmission
  SPDR = command;

  // Wait for transmission to complete
  while (!(SPSR & (1<<SPIF)));
  
  return;
}

void PCD8544::DisplayString(char *characters)
{
  while (*characters)
  {
    DisplayCharacter(*characters++);
  }
}

void PCD8544::DisplayCharacter(char character)
{
  WriteDisplay(0x00);
  for (int index = 0; index < 5; index++)
  {
      WriteDisplay(ASCII[character - 0x20][index]);
    }
  WriteDisplay(0x00);
}
