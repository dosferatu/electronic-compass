/*
 * The ReadHeading() function uses the Pololu LSM303 Arduino library
 * as the design reference, and the license for that library has been
 * included as "LSM303 LICENSE.TXT" in this directory.
 */

#include <math.h>
#include "LSM303DLH.h"
#include <avr/io.h>
#include <util/delay.h>

LSM303DLH::LSM303DLH()
{
}

LSM303DLH::~LSM303DLH()
{
}

void LSM303DLH::InitLSM303DLH()
{
  // Enable the TWI
  // Set the baud rate to 400KHz (fast mode)
  TWBR = TWI_TWBR;                          // Set the bit rate register for 400KHz
          
  /*
   * We wish to write one byte (0x27) to the accel config register
   *
   * The flow should be:
   * Master: START
   * Master: SAD + W
   * Slave: SAK
   * Master: SUB
   * Slave: SAK
   * Master: DATA
   * Slave: SAK
   * Master: STOP
   */

  // Implement check for a busy transceiver
  // Set up the TWCR to send START
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify START condition
  //if ((TWSR & 0xF8) == 0x08)
    //BlinkLED(1);

  // Load the TWI buffer with the accelerometer read address
  TWDR = LSM303_ACCEL_WRITE_ADDRESS;

  // Set up the TWCR to send repeat START condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + W transmitted, ACK received
  //if ((TWSR & 0xF8) == 0x18)
    //BlinkLED(2);

  // Load the TWI buffer with the SUB address
  TWDR = LSM303_CTRL_REG1_A;

  // Set up the TWCR to send SUB address
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify data byte transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(3);
  
  // Load the TWI buffer with the accelerometer config value
  // 0x27 = 
  TWDR = 0x27;

  // Set up the TWCR to send configuration word
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify data byte transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(3);

  // Set up the TWCR to send STOP condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT)|                       // Clear TWINT to send data
          (1<<(TWSTO));                      // Set STOP condition

  /*
   * We wish to write one byte (0x00) to the accel config register
   *
   * The flow should be:
   * Master: START
   * Master: SAD + W
   * Slave: SAK
   * Master: SUB
   * Slave: SAK
   * Master: DATA
   * Slave: SAK
   * Master: STOP
   */

  // Implement check for a busy transceiver
  // Set up the TWCR to send START
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify repeat START condition
  //if ((TWSR & 0xF8) == 0x10)
    //BlinkLED(1);

  // Load the TWI buffer with the accelerometer read address
  TWDR = LSM303_MAG_WRITE_ADDRESS;

  // Set up the TWCR to send repeat START condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + W transmitted, ACK received
  //if ((TWSR & 0xF8) == 0x18)
    //BlinkLED(2);

  // Load the TWI buffer with the SUB address
  TWDR = LSM303_MR_REG_M;

  // Set up the TWCR to send SUB address
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify data byte transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(3);
  
  // Load the TWI buffer with the magnetometer config value
  // 0x00 = Continuous conversion mode
  TWDR = 0x00;

  // Set up the TWCR to send configuration word
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify data byte transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(3);

  // Set up the TWCR to send STOP condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT)|                       // Clear TWINT to send data
          (1<<(TWSTO));                      // Set STOP condition

  return;
}

int LSM303DLH::ReadHeading()
{
  // Format is low byte, high byte, etc...
  unsigned char accelData[6] = {0};

  // Format is high byte, low byte, etc...
  unsigned char magData[6] = {0};

  // Heading calculation vectors
  int heading;
  vector accel;
  vector mag;
  vector east;
  vector north;
  vector from = {0, -1, 0};

  /*
   * We need to read 6 bytes from the accelerometer.
   *
   * The flow for this is:
   * Master: START, SAD + W
   * Slave: SAK
   * Master: SUB
   * Slave: SAK
   * Master: RESTART, SAD + R
   * Slave: SAK
   *
   * The following iterates for 5 bytes in our case:
   * Slave: DATA
   * Master: MAK
   * ...
   *
   * Slave: DATA
   * MASTER: NMAK, STOP
   */

  /*
   * BEGIN ACCELEROMETER READ
   */

    // Set up the TWCR to send START
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify START condition
  //if ((TWSR & 0xF8) == 0x08)
    //BlinkLED(1);

  // Verify repeat START condition
  //if ((TWSR & 0xF8) == 0x10)
    //BlinkLED(2);

  // Load the TWI buffer with SLA + W
  TWDR = LSM303_ACCEL_WRITE_ADDRESS;

  // Set up the TWCR to send SLA + W
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + W transmitted, ACK received
  //if ((TWSR & 0xF8) == 0x18)
    //BlinkLED(3);

  // Load the TWI buffer with the SUB address and
  // make sure the MSB is set so that the accelerometer
  // knows to autoincrement the internal address pointer
  // for subsequent reads
  TWDR = LSM303_OUT_X_L_A | (1 << 7);

  // Set up the TWCR to send SUB address
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SUB transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(4);

  // Load the TWI buffer with SLA + R
  TWDR = LSM303_ACCEL_READ_ADDRESS;

  // Set up the TWCR to send repeat START condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify repeat START condition
  //if ((TWSR & 0xF8) == 0x10)
    //BlinkLED(2);

  // Set up the TWCR to send SLA + R
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + R transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x40)
    //BlinkLED(5);

  // Receive the first 5 data bytes
  for (int i = 0; i < 5; ++i)
  {
    // Set up the TWCR to receive the data byte and return ACK
    TWCR =  (1<<TWEN)|                        // TWI enabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|  // Send ACK
            (0<<TWWC);

    // Hold execution until TWI interrupt flag is set
    while(!(TWCR & (1<<TWINT)));

    // Verify data byte received, ACK transmitted
    //if ((TWSR & 0xF8) == 0x50)
      //BlinkLED(6);

    // Read the data byte in
    accelData[i] = TWDR;
  }

    // Set up the TWCR to receive the data byte and return NACK
    TWCR =  (1<<TWEN)|                        // TWI disabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|  // Send ACK
            (0<<TWWC);

    // Hold execution until TWI interrupt flag is set
    while(!(TWCR & (1<<TWINT)));

    // Verify data byte received, NACK transmitted
    //if ((TWSR & 0xF8) == 0x58)
      //BlinkLED(7);

    // Read the last data byte in
    accelData[5] = TWDR;

    // Set up the TWCR to send the STOP condition
    TWCR =  (0<<TWEN)|                        // TWI disabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|  // Initiate a STOP condition
            (0<<TWWC);
  /*
   * END ACCELEROMETER READ
   */

  // Combine low and high bytes in to [x,y,z] vector
  accel.x = ((int16_t)(accelData[1] << 8 | accelData[0])) >> 4;
  accel.y = ((int16_t)(accelData[3] << 8 | accelData[2])) >> 4;
  accel.z = ((int16_t)(accelData[5] << 8 | accelData[4])) >> 4;

  /*
   * We need to read 6 bytes from the magnetometer.
   *
   * The flow for this is:
   * Master: START, SAD + W
   * Slave: SAK
   * Master: SUB
   * Slave: SAK
   * Master: RESTART, SAD + R
   * Slave: SAK
   *
   * The following iterates for 5 bytes in our case:
   * Slave: DATA
   * Master: MAK
   * ...
   *
   * Slave: DATA
   * MASTER: NMAK, STOP
   */

  /*
   * BEGIN MAGNETOMETER READ
   */

    // Set up the TWCR to send START
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify START condition
  //if ((TWSR & 0xF8) == 0x08)
    //BlinkLED(1);

  // Verify repeat START condition
  //if ((TWSR & 0xF8) == 0x10)
    //BlinkLED(2);

  // Load the TWI buffer with SLA + W
  TWDR = LSM303_MAG_WRITE_ADDRESS;

  // Set up the TWCR to send SLA + W
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + W transmitted, ACK received
  //if ((TWSR & 0xF8) == 0x18)
    //BlinkLED(3);

  // Load the TWI buffer with the SUB address
  TWDR = LSM303_OUT_X_H_M;

  // Set up the TWCR to send SUB address
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SUB transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x28)
    //BlinkLED(4);

  // Load the TWI buffer with SLA + R
  TWDR = LSM303_MAG_READ_ADDRESS;

  // Set up the TWCR to send repeat START condition
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
          (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|  // Initiate a START condition
          (0<<TWWC);

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify repeat START condition
  //if ((TWSR & 0xF8) == 0x10)
    //BlinkLED(2);

  // Set up the TWCR to send SLA + R
  TWCR =  (1<<TWEN)|                        // TWI enabled
          (1<<TWINT);                       // Clear TWINT to send data

  // Hold execution until TWI interrupt flag is set
  while(!(TWCR & (1<<TWINT)));

  // Verify SLA + R transmitted, ACK received.
  //if ((TWSR & 0xF8) == 0x40)
    //BlinkLED(5);

  // Receive the first 5 data bytes
  for (int i = 0; i < 5; ++i)
  {
    // Set up the TWCR to receive the data byte and return ACK
    TWCR =  (1<<TWEN)|                        // TWI enabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|  // Send ACK
            (0<<TWWC);

    // Hold execution until TWI interrupt flag is set
    while(!(TWCR & (1<<TWINT)));

    // Verify data byte received, ACK transmitted
    //if ((TWSR & 0xF8) == 0x50)
      //BlinkLED(6);

    // Read the data byte in
    accelData[i] = TWDR;
  }

    // Set up the TWCR to receive the data byte and return NACK
    TWCR =  (1<<TWEN)|                        // TWI disabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|  // Send ACK
            (0<<TWWC);

    // Hold execution until TWI interrupt flag is set
    while(!(TWCR & (1<<TWINT)));

    // Verify data byte received, NACK transmitted
    //if ((TWSR & 0xF8) == 0x58)
      //BlinkLED(7);

    // Read the last data byte in
    accelData[5] = TWDR;

    // Set up the TWCR to send the STOP condition
    TWCR =  (0<<TWEN)|                        // TWI disabled
            (0<<TWIE)|(1<<TWINT)|             // Disable interrupts and clear flag
            (0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|  // Initiate a STOP condition
            (0<<TWWC);
  /*
   * END MAGNETOMETER READ
   */

  // Combine high and low bytes in to [x,y,z] vector
  mag.x = (int16_t)(magData[0] << 8 | magData[1]);
  mag.y = (int16_t)(magData[2] << 8 | magData[3]);
  mag.z = (int16_t)(magData[4] << 8 | magData[5]);

  // Shift and scale
  // Probably need to do our own calibration values
  mag.x = (mag.x - cal_x_min) / (cal_x_max - cal_x_min) * 2 - 1.0;
  mag.y = (mag.y - cal_y_min) / (cal_y_max - cal_y_min) * 2 - 1.0;
  mag.z = (mag.z - cal_z_min) / (cal_z_max - cal_z_min) * 2 - 1.0;

  // Normalize the accel vector
  VectorNormalize(&accel);
  //VectorNormalize(&mag);

  // Compute East and North
  VectorCross(&mag, &accel, &east);
  VectorNormalize(&east);
  VectorCross(&accel, &east, &north);

  // Calculate the heading
  heading = round(atan2(VectorDot(&east, &from), VectorDot(&north, &from)) * 180 / M_PI);

  if (heading < 0)
    heading += 360;

  return heading;
}

/*
 * Write a configuration byte to the CTRL1_REG_A and the MR_REG_M
 * configurations in the accelerometer and magnetometer devices.
 */

void LSM303DLH::VectorCross(const vector *a, const vector *b, vector *out)
{
  out->x = a->y*b->z - a->z*b->y;
  out->y = a->z*b->x - a->x*b->z;
  out->z = a->x*b->y - a->y*b->x;
}

float LSM303DLH::VectorDot(const vector *a,const vector *b)
{
  return a->x*b->x+a->y*b->y+a->z*b->z;
}

void LSM303DLH::VectorNormalize(vector *a)
{
  float mag = sqrt(VectorDot(a,a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}

void LSM303DLH::BlinkLED(int count)
{
  for (int i = 0; i < count; ++i)
  {
    PORTD = 0x10;
    _delay_ms(100);

    PORTD = 0x00;
    _delay_ms(100);
  }
  _delay_ms(1000);
  return;
}
