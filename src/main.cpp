/*
 * This is the routine for the electronic compass.
 * The ATMega32U4 will be initialized making sure to
 * unmask interrupts for the I2C bus and the necessary
 * GPIO interrupts for the magnetometer/accelerometer
 * and LCD display respectively. From here we simply
 * take readings from the sensor package, and map the
 * results to display values for the LCD.
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LSM303DLH/LSM303DLH.h"
#include "PCD8544/PCD8544.h"

int main()
{
  PCD8544 display;
  LSM303DLH compass;

  // Normal power, all axes enabled
  int headingValue = 0x00;

  // Set PD4 as an output low
  DDRD = 0x10;
  PORTD = 0x00;

  // Initialize the LSM303
  compass.InitLSM303DLH();

  // Initialize the Nokia 5110
  display.InitPCD8544();

  while(true)
  {
    display.ClearDisplay();

    headingValue = compass.ReadHeading();

    if (headingValue >= 0 && headingValue <= 360)
      compass.BlinkLED(headingValue / 10);

    // Write to display here
    display.WriteDisplay(headingValue);
  }
  return 0;
}
