/*
 * This is the routine for the electronic compass.
 * The ATMega32U4 will be initialized making sure to
 * unmask interrupts for the I2C bus and the necessary
 * GPIO interrupts for the magnetometer/accelerometer
 * and LCD display respectively. From here we simply
 * take readings from the sensor package, and map the
 * results to display values for the LCD.
 */

// Register definitions.
//#define INT_TWI 0x0030	// 2-wire Serial Interface Interrupt

#include "TWI_Master.h"

//11100101
//unsigned char twcr = 0xE5;

int main()
{
		TWI_Master_Initialise();

		//while(true)
		//{
				// Tell sensor we want a reading
				// wait for interrupt from sensor
				// read in sensor data
				// calculate heading
				// display to lcd
		//}
		return 0;
}
