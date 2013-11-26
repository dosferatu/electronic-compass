#include "PCD8544.h"

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

  // Initiate ATMega32U4 as a master on the SPI bus
  // Set MOSI and SCK output, all others input
  DDRB = (1<<PB2)|(1<<PB1);

  // Enable SPI, Master, set clock rate fck/16
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

   //Set to active mode, vertical addressing, extended
   //instruction set.
  SendCommand(0x23);
  
  /* CHANGE THIS TO SUIT OUR MUX RATE */
  /* NEED TO SET [BS2:BS0] TO CORRECT BIAS FOR MUX RATE */
  // Set Vop to (a + 16 * b)
  SendCommand(0x90);
  
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
    WriteDisplay(0);
}

void PCD8544::DisplayHeading(int headingValue)
{
  // Take in the heading value and map it to the appropriate image to display
}

void PCD8544::WriteDisplay(uint8_t column)
{
  DDRF = LCD_SCE;       // Set SCE# low
  PORTF = LCD_SCE_LO;
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
  DDRF = LCD_SCE;       // Set SCE# low
  PORTF = LCD_SCE_LO;
  DDRF = LCD_DC;        // Set PCD8544 to command input
  PORTF = LCD_DC_LO;
  
  // Start transmission
  SPDR = command;

  // Wait for transmission to complete
  while (!(SPSR & (1<<SPIF)));
  
  return;
}
