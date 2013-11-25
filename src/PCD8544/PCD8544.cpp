#include "PCD8544.h"
#include <stdlib.h>

PCD8544::PCD8544()
{

}

PCD8544::~PCD8544()
{

}

void PCD8544::InitPCD8544()
{
  // Power on the display
  //DDRx = LCD_WHATEVER;
  //PORTx = LCD_WHATEVER;
  
  // Pulse reset low to reset internal registers
  DDRF = LCD_RST;
  PORTF = LCD_RST_LO;
  PORTF = LCD_RST_HI;

  /*
   * Set to active mode, vertical addressing, extended
   * instruction set.
   */
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

void PCD8544::ClearDisplay()
{

}

void PCD8544::DisplayHeading(int headingValue)
{
}

void PCD8544::WriteDisplay()
{

}

void PCD8544::LoadImage(unsigned char base_img)
{

}

void PCD8544::EditImage(unsigned char new_img, coordinate_pair coords)
{

}

void PCD8544::ConvertImage()
{

}

void PCD8544::SendCommand(uint8_t command)
{
  DDRF = LCD_SCE;       // Set SCE# low
  PORTF = LCD_SCE_LO;
  DDRF = LCD_DC;        // Set PCD8544 to command input
  PORTF = LCD_DC_LO;
  
  // Clock in command
  return;
}
