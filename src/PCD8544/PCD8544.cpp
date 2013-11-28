#include <util/delay.h>
#include "PCD8544.h"
#include "image_parts.h"

using namespace std;

PCD8544::PCD8544()
{
}

PCD8544::~PCD8544()
{
}

// Function to clear the display
void PCD8544::ClearDisplay()
{
  // Write 0's to all 84 columns
  for (int i = 0; i < LCD_WIDTH; ++i)
    WriteColumn(0x00);

  return;
}

// Uses the given heading to update the UI accordingly
void PCD8544::DisplayHeading(const int headingValue)
{
  DisplayImage(compassUI);

  /*
   * Clear the letters field:
   * Width is 20px (9px for both letters  + 2px spacing
   * Height is 16px
   */
  // Ensure the X address is reset
  SendCommand(0x80);

  // Ensure the Y address is reset
  SendCommand(0x40);

  // Clear the first 30 columns
  for (int i = 0; i < 30; ++i)
    for (int j = 0; i < 6; ++i)
      WriteColumn(0x00);

  // Update all subcomponents of the UI
  //UpdateLetters(headingValue);
  //UpdateNumbers(headingValue);
  //UpdateCompass(headingValue);

  return;
}

void PCD8544::DisplayImage(const uint8_t image[][6])
{
  // Set the X address of the PCD8544 RAM to 0x0
  SendCommand(0x80);

  for (int i = 0; i < LCD_WIDTH; ++i)
    for(int j = 5; j > -1; --j)
      WriteColumn(image[i][j]);

  return;
}

void PCD8544::InitPCD8544()
{
  // Pulse reset low to reset internal registers
  DDRF = LCD_RST;
  PORTF = LCD_RST_LO;
  _delay_ms(100);
  PORTF = LCD_RST_HI;

  // Enable the Data/Command# output
  DDRF = LCD_DC;        

  // Assert the chip enable of the LCD
  // GET RID OF THIS SINCE TIED LOW IN DESIGN
  DDRF = LCD_SCE;       
  PORTF = LCD_SCE_LO;

  // Initiate ATMega32U4 as a master on the SPI bus
  // Set MOSI and SCK output, all others input
  DDRB = (1<<PB2)|(1<<PB1);

  // Enable SPI, Master, set clock rate fck/16 for 1MHz
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

   //Set to active mode, vertical addressing, extended
   //instruction set.
  SendCommand(0x23);
  
  // Set Vop to (a + 16 * b)
  SendCommand(0x8E);

  // Set temp coefficient
  // Taken from SparkFun arduino sketch
  SendCommand(0x04);

  // LCD Bias
  SendCommand(0x14);
  
  // Set to normal instruction set
  SendCommand(0x22);
   
  // Set to normal display mode
  SendCommand(0x0C);

  // Set compass UI to default state
  ClearDisplay();
  DisplayImage(compassUI);

  return;
}

void PCD8544::SendCommand(const uint8_t command)
{
  PORTF = LCD_DC_LO;  // Set PCD8544 to command input
  
  // Start transmission
  SPDR = command;

  // Wait for transmission to complete
  while (!(SPSR & (1<<SPIF)));

  return;
}

void PCD8544::UpdateLetters(const int headingValue)
{
  // Display North
  if (headingValue >= 340 && headingValue <= 20)
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
    SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(N[i][j]);
    }

  // Display NorthEast
  else if(headingValue > 20 && headingValue < 70)
  {
    // The 'N'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));
      
      for (int j = 0; j < 2; ++j)
        WriteColumn(N[i][j]);
    }

    // The 'E'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i + 10));

      for (int j = 0; j < 2; ++j)
        WriteColumn(E[i][j]);
    }
  }

    // Display East
  else if(headingValue >= 70 && headingValue <= 110)
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(E[i][j]);
    }

  // Display SouthEast
  else if(headingValue > 110 && headingValue < 160)
  {
    // The 'S'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(S[i][j]);
    }

    // The 'E'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i + 10));

      for (int j = 0; j < 2; ++j)
        WriteColumn(E[i][j]);
    }
  }

  // Display South
  else if(headingValue >= 160 && headingValue <= 200)
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(S[i][j]);
    }

  // Display SouthWest
  else if(headingValue > 200 && headingValue < 250)
  {
    // The 'S'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(S[i][j]);
    }

    // The 'W'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i + 10));

      for (int j = 0; j < 2; ++j)
        WriteColumn(W[i][j]);
    }
  }

  // Display West
  else if(headingValue >= 250 && headingValue <= 290)
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(W[i][j]);
    }

  // Display NorthWest
  else if(headingValue > 290 && headingValue < 340)
  {
    // The 'S'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i));

      for (int j = 0; j < 2; ++j)
        WriteColumn(N[i][j]);
    }

    // The 'W'
    for (int i = 0; i < 9; ++i)
    {
      // Increment the X address
      SendCommand(0x80 | (UI_LETTERS_X + i + 10));

      for (int j = 0; j < 2; ++j)
        WriteColumn(W[i][j]);
    }
  }
    
  return;
}

void PCD8544::UpdateNumbers(const int headingValue)
{
  return;
}

void PCD8544::UpdateCompass(const int headingValue)
{
  return;
}

void PCD8544::WriteColumn(const uint8_t column)
{
  PORTF = LCD_DC_HI;  // Set PCD8544 to data input

  // Start transmission
  SPDR = column;

  // Wait for transmission to complete
  while (!(SPSR & (1<<SPIF)));

  return;
}
