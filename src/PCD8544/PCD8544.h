#include <avr/io.h>
#include <inttypes.h>

#define LCD_RST                     PORTB |= (1<<PB5)
#define LCD_RST_HI		    PORTB |= (1<<PB5)
#define LCD_RST_LO		    PORTB &= ~(1<<PB5)
#define LCD_DC                      PORTB |= (1<<PB4)
#define LCD_DC_HI		    PORTB |= (1<<PB4)
#define LCD_DC_LO		    PORTB &= ~(1<<PB4)
#define LCD_SDIN                    PORTB |= (1<<PB2)
#define LCD_SCLK		    PORTB |= (1<<PB1)
#define LCD_VDD                     PORTB |= (1<<PB0)
#define LCD_VDD_HI                  PORTB |= ~(1<<PB0)
#define LCD_VDD_LO                  PORTB |= ~(1<<PB0)
#define LCD_BACKLIGHT_HI            PORTB |= (1<<PB6)
#define LCD_BACKLIGHT_LO            PORTB &= ~(1<<PB6)

#define LCD_C                       0
#define LCD_D                       1

#define LCD_WIDTH	            84
#define LCD_HEIGHT	            48

#define UI_LETTERS_X                10
#define UI_LETTERS_Y                2
#define UI_NUMBERS_X                40
#define UI_NUMBERS_Y                2

class PCD8544
{
  public:
    PCD8544();
    ~PCD8544();
    void ClearDisplay();
    void ConvertImage();
    void DisplayHeading(const int);
    void InitPCD8544();
    void SendCommand(const uint8_t);
    void WriteColumn(const uint8_t);

    // For debugging
    void BlinkDisplay(int);

  private:
    void DisplayImage(const uint8_t [][6]);
    void PrintDigit(const int, const int);
    void UpdateLetters(const int);
    void UpdateNumbers(const int);
    void UpdateCompass(const int);
};
