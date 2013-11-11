#include <math.h>
#include "LSM303.h"

unsigned char GetMagStatus()
{
	unsigned char data;
	unsigned char message[2] =	{LSM303_MAG_READ_ADDRESS,
								LSM303_SR_REG_M};

	if (TWI_statusReg.lastTransOK)
	{
		TWI_Start_Transceiver_With_Data(message, 2);
		TWI_Get_Data_From_Transceiver(message, 1);
	}

	data = message[0];
	return data;
}

unsigned char ReadHeading()
{
	// Format is [x,y,z]
	char accelVector[3];
	char magVector[3];
	
	// Format is low byte, high byte, etc...
	unsigned char accelData[6];

	// Format is high byte, low byte, etc...
	unsigned char magData[6];

	// Heading calculation vectors
	char east[3];
	char north[3];

	int fromVector[3] = {0, -1, 0};

	float eastFromDotProduct;
	float northFromDotProduct;

	// Heading
	unsigned char heading;
	
	// TWI instructions
	// Assert the MSB of the LSM303 accel reg sub address to get
	// the sub address auto increment to occur for both reads.
	unsigned char accelReadRequest[2] =	{LSM303_ACCEL_READ_ADDRESS,
										LSM303_OUT_X_L_A | (1 << 7)};

 
	unsigned char magReadRequest[2] =	{LSM303_MAG_READ_ADDRESS,
										LSM303_OUT_X_H_M};
	
	// Read in the accel data
	if (TWI_statusReg.lastTransOK)
	{
		TWI_Start_Transceiver_With_Data(accelReadRequest, 2);
		TWI_Get_Data_From_Transceiver(accelData, 6);

		// Combine low and high bytes in to [x,y,z] vector
		accelVector[0] = (accelData[1] << 8 | accelData[0]) >> 4;
		accelVector[1] = (accelData[3] << 8 | accelData[2]) >> 4;
		accelVector[2] = (accelData[5] << 8 | accelData[4]) >> 4;
	}

	// Read in the mag data
	if (TWI_statusReg.lastTransOK)
	{
		TWI_Start_Transceiver_With_Data(magReadRequest, 2);
		TWI_Get_Data_From_Transceiver(magData, 6);

		// Combine high and low bytes in to [x,y,z] vector
		magVector[0] = magData[0] << 8 | magData[1];
		magVector[1] = magData[2] << 8 | magData[3];
		magVector[2] = magData[4] << 8 | magData[5];
	}

	/* Accel vector normalization */
	// First perform vector dot function
	float mag =	sqrt(accelVector[0] * accelVector[0] +
					accelVector[1] * accelVector[1] + 
					accelVector[2] * accelVector[2]);

	// Now normalize it
	// I know the vector may be undefined, but if it is we have bigger problems.
#pragma GCC diagnostic ignored "-Wsequence-point"
	accelVector[0] = accelVector[0] /= mag;
	accelVector[1] = accelVector[1] /= mag;
	accelVector[2] = accelVector[2] /= mag;

	// Normalize mag vector?

	// Compute East
	// Perform vector cross function
	east[0] = magVector[1] * accelVector[2] - magVector[2] * accelVector[1];
	east[1] = magVector[2] * accelVector[0] - magVector[0] * accelVector[2];
	east[2] = magVector[0] * accelVector[1] - magVector[1] * accelVector[0];

	/* East vector normalization */
	// First perform vector dot function
	mag = sqrt(east[0] * east[0] +
				east[1] * east[1] +
				east[2] * east[2]);
	
	// Now normalize it
	east[0] = east[0] / mag;
	east[1] = east[1] / mag;
	east[2] = east[2] / mag;

	// Perform vector cross function on the accel and East vectors
	north[0] = accelVector[1] * east[2] - accelVector[2] * east[1];
	north[1] = accelVector[2] * east[0] - accelVector[0] * east[2];
	north[2] = accelVector[0] * east[1] - accelVector[1] * east[0];

	/* Heading calculations */
	// Perform vector dot function on the east and from vectors
	eastFromDotProduct = sqrt(east[0] * fromVector[0] +
							east[1] * fromVector[1] +
							east[2] * fromVector[2]);

	northFromDotProduct = sqrt(north[0] * fromVector[0] +
							north[1] * fromVector[1] +
							north[2] * fromVector[2]);

	// Calculate the heading
	heading = round(atan2(eastFromDotProduct, northFromDotProduct) * 180 / M_PI);

	if (heading < 0)
			heading += 360;

	return heading;
}

void SetAccelCTRL1(unsigned char configByte)
{
	unsigned char message[3] =	{LSM303_ACCEL_WRITE_ADDRESS,
								LSM303_CTRL_REG1_A,
								configByte};

	if (TWI_statusReg.lastTransOK)
	{
		TWI_Start_Transceiver_With_Data(message, 3);
	}

	return;
}
