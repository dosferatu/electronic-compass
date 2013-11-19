/* This header defines the image controls and sets up the structure of the the image that will be displayed on the
    Nokia 5110 LCD.  The LCD is monochrome and its dimensions are 48px H X 84px W.  It is controlled by the PCD8544 LCD
    controller.  It communicates with the MCU by the Serial Peripheral Interface (SPI) and is passed all the bites to display
    on the LCD one after another beginning with the upper left.  Two options are available for addressing the bites: vertical
    is where the bytes are passed for the left column from top to bottom and then moves to the next column to the right,
    horizontal is where the bytes are passed for the top column from left to right and then moves to the next row down.

    The structure of the LCD has been chosen to be a two dimensional array of chars with each index representing one of the
    bytes passed to the PCD8544.  There will be an array that will be used for storing the currently processing image and
    there will be an array that will be used for making necessary updates to the image, a working image as it were.  The
    working array can be updated as quickly as the data is updated from the mag/accel.  This will then be copied to the
    processing image for processing.
*/

// Image processing class
class image_interface
{
    public:
        // Functions for editing the image
        void initialize_img(unsigned char * [][]);                                  // Pass it the desired base image of the appropriate size in hex format
        void edit_working_img(unsigned char wrk_img * [][], int top_left_coord);                     // Pass it a new part of the image with the coordinates of where to put it
        void convert_img (unsigned char img_arrays * [][]);                                       // Converts the working image into the processing image

    private:
        unsigned char processing_img * [6][84];                                     // Array for holding the currently processing image
        unsigned char working_img * [48][84];                                                // Array for holding the working image


};
