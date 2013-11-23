/* This file stores the application specific imagery for use with the LCD.
 *  It will have the image parts stored in byte arrays that it will pass
 *  through the image_interface which will update the image appropriately.
 */

// Letters & Numbers (7 bits wide X 11 bits high)
static unsigned char Letters [][7] = {
    {0xFF, 0x08, 0x30, 0x30, 0xC0, 0x00, 0xFF},         // N Top
    {0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07},         // N Bottom
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0xE0},         // S Top
    {0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03},         // S Bottom
    {0xFF, 0x41, 0x41, 0x41, 0x41, 0x41, 0x01},         // E Top
    {0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},         // E Bottom
    {0x7F, 0xC0, 0x80, 0xF0, 0x80, 0xC0, 0x7F},         // W Top
    {0x00, 0x01, 0x07, 0x00, 0x07, 0x01, 0x00}};        // W Bottom


