/*
 * This is the routine for the electronic compass.
 * The ATMega32U4 will be initialized making sure to
 * unmask interrupts for the I2C bus and the necessary
 * GPIO interrupts for the magnetometer/accelerometer
 * and LCD display respectively. From here we simply
 * take readings from the sensor package, and map the
 * results to display values for the LCD.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LSM303DLH/LSM303DLH.h"
#include "PCD8544/PCD8544.h"

int main()
{
  PCD8544 display;
  LSM303DLH compass;

  // Normal power, all axes enabled
  int headingValue = 0x00;

  // Set PD4 as an output low for the debug LED
  DDRD |= (1<<PD4);
  PORTD |= ~(1<<PD4);

  // Set PB0 (SS) as an output HIGH
  DDRB |= (1<<PB0);
  PORTB |= (1<<PB0);

  // Power on the compass and the display
  DDRB |= (1<<PB6);
  PORTB |= (1<<PB6);

  // Initialize the LSM303
  compass.InitLSM303DLH();

  // Initialize the Nokia 5110
  display.InitPCD8544();

  while(true)
  {
    headingValue = compass.ReadHeading();

    display.DisplayHeading(headingValue);
    //compass.BlinkLED(headingValue / 10);
    _delay_ms(1);
  }

  return 0;
}
