/*
 * This header defines the image controls and sets up the structure of
 * the image that will be displayed on the Nokia 5110 LCD. The LCD is
 * monochrome and its dimensions are 48px H X 84px W. It is controlled
 * by the PCD8544 LCD controller. It communicates with the MCU by the
 * Serial Peripheral Interface (SPI) and is passed all the bites to display
 * on the LCD one after another beginning with the upper left. Two options
 * are available for addressing the bites: vertical is where the bytes are
 * passed for the left column from top to bottom and then moves to the next
 * column to the right, horizontal is where the bytes are passed for the
 * top column from left to right and then moves to the next row down.
 * The structure of the LCD has been chosen to be a two dimensional array
 * of chars with each index representing one of the bytes passed to the
 * PCD8544.  There will be an array that will be used for storing the
 * currently processing image and there will be an array that will be
 * used for making necessary updates to the image, a working image as it
 * were. The working array can be updated as quickly as the data is
 * updated from the mag/accel. This will then be copied to the processing
 * image for processing.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
//#include "image_parts.h"

#define LCD_SCE                     PORTF |= (1<<4)
#define LCD_SCE_HI		    PORTF |= (1<<4)
#define LCD_SCE_LO		    PORTF &= ~(1<<4)
#define LCD_RST                     PORTF |= (1<<7)
#define LCD_RST_HI		    PORTF |= (1<<7)
#define LCD_RST_LO		    PORTF &= ~(1<<7)
#define LCD_DC                      PORTF |= (1<<6)
#define LCD_DC_HI		    PORTF |= (1<<6)
#define LCD_DC_LO		    PORTF &= ~(1<<6)
#define LCD_SDIN                    PORTB |= (1<<2)
#define LCD_SCLK		    PORTB |= (1<<1)
#define LCD_VDD                     PORTB |= (1<<0)
#define LCD_VDD_HI                  PORTB |= ~(1<<0)
#define LCD_VDD_LO                  PORTB |= ~(1<<0)
#define LCD_BACKLIGHT_HI	    PORTF |= (1<<5)
#define LCD_BACKLIGHT_LO	    PORTF &= ~(1<<5)

#define LCD_C               0
#define LCD_D               1

#define LCD_WIDTH	        84
#define LCD_HEIGHT	        48

/*
 * This structure is used by the system to setup an array of coordinate pairs
 * for appropriate changes
 */
struct coordinate_pair
{
    int x;
    int y;
};

class PCD8544
{
    public:
        PCD8544();
        ~PCD8544();
        void InitPCD8544();
        void ClearDisplay();
        void ConvertImage();
        void DisplayHeading(int);
        //void EditImage(unsigned char new_img, coordinate_pair coords);
        //void LoadImage(unsigned char base_img);
        void SendCommand(uint8_t);
        void WriteDisplay(uint8_t);

    private:
        unsigned char proc_img[][84] PROGMEM;
        unsigned char working_img[][84] PROGMEM;
};
