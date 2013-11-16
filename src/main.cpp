/*
 * This is the routine for the electronic compass.
 * The ATMega32U4 will be initialized making sure to
 * unmask interrupts for the I2C bus and the necessary
 * GPIO interrupts for the magnetometer/accelerometer
 * and LCD display respectively. From here we simply
 * take readings from the sensor package, and map the
 * results to display values for the LCD.
 */

#define stuff PORTD

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "LSM303/LSM303.h"
//#include "images.h"

extern "C"
{
  #include "glcd/glcd.h"
}


void BlinkLED(int);

int main()
{
  // Normal power, all axes enabled
  int headingValue = 0x00;

  // Set PD4 as an output low
  DDRD = 0x10;
  PORTD = 0x00;

  // Set PC as an output low
  DDRF = 0x20;
  PORTF = 0x00;

  // Set the TWI master to initial standby state
  //TWI_Master_Initialise();

  // Enable interrupts
  //sei();

  // Initialize the device
  EnableDefaults();
  
  //GetMagStatus();

  while(true)
  {
  //glcd_test_circles();
    //Turn the LED off
    //PORTD = 0x00;

    //BlinkLED(ReadHeading());

    //Check mag status reg for DRDY (bit 0) and do a
    //reading if it is set.
    //if (GetMagStatus() & 0x1)
    //{
    headingValue = ReadHeading();

    if (headingValue >= 0 && headingValue <= 360)
      BlinkLED(headingValue / 10);
    //PORTD = 0x10;
    //else
    //PORTD = 0x00;

    // Write to display here
    //}
  }
  return 0;
}

