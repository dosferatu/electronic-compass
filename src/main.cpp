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
//#include "glcd/glcd.h"

int main()
{
	// Normal power, all axes enabled
	unsigned char accelControlRegValues = 0x27;
	unsigned char heading;

	// Set PD4 as an output low
	DDRD = 0x10;
	PORTD = 0x00;

	// Set the TWI master to initial standby state
	TWI_Master_Initialise();

	// Enable interrupts
	sei();

	// Send the config values to the accel control reg
	SetAccelCTRL1(accelControlRegValues);

	while(true)
	{
		// Check mag status reg for DRDY (bit 0) and do a
		// reading if it is set.
		if (GetMagStatus() & 0x1)
		{
			heading = ReadHeading();

			if (heading >= 0 || heading <= 360)
					PORTD = 0x10;
			// Write to display here
		}
		else
			PORTD = 0x00;
	}
	return 0;
}
