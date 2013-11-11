#ifndef LSM303_h
#define LSM303_h

// LSM303 device addresses
#define LSM303_ACCEL_READ_ADDRESS	0x31
#define LSM303_ACCEL_WRITE_ADDRESS	0x30
#define LSM303_MAG_READ_ADDRESS		0x3D
#define LSM303_MAG_WRITE_ADDRESS	0x3C

// LSM303 control/status regs
#define LSM303_CTRL_REG1_A       0x20
#define LSM303_CTRL_REG2_A       0x21
#define LSM303_CTRL_REG3_A       0x22
#define LSM303_CTRL_REG4_A       0x23
#define LSM303_CTRL_REG5_A       0x24
#define LSM303_HP_FILTER_RESET_A 0x25
#define LSM303_REFERENCE_A       0x26
#define LSM303_STATUS_REG_A      0x27

// LSM303 accel output regs
#define LSM303_OUT_X_L_A         0x28
#define LSM303_OUT_X_H_A         0x29
#define LSM303_OUT_Y_L_A         0x2A
#define LSM303_OUT_Y_H_A         0x2B
#define LSM303_OUT_Z_L_A         0x2C
#define LSM303_OUT_Z_H_A         0x2D

// LSM303 accel interrupt regs
#define LSM303_INT1_CFG_A        0x30
#define LSM303_INT1_SRC_A        0x31
#define LSM303_INT1_THS_A        0x32
#define LSM303_INT1_DURATION_A   0x33
#define LSM303_INT2_CFG_A        0x34
#define LSM303_INT2_SRC_A        0x35
#define LSM303_INT2_THS_A        0x36
#define LSM303_INT2_DURATION_A   0x37

#define LSM303_CRA_REG_M         0x00
#define LSM303_CRB_REG_M         0x01
#define LSM303_MR_REG_M          0x02

// LSM303 mag output regs
/* 
 * Starting a read will cause the LSM303 to increment the internal
 * sub address pointer automatically, so we just need the first regs
 */
#define LSM303_OUT_X_H_M         0x03
#define LSM303_OUT_X_L_M         0x04

// LSM303 status and ID regs
#define LSM303_SR_REG_M          0x09
#define LSM303_IRA_REG_M         0x0A
#define LSM303_IRB_REG_M         0x0B
#define LSM303_IRC_REG_M         0x0C
#define LSM303_WHO_AM_I_M        0x0F

// LSM303 mag output regs
#define LSM303_OUT_Y_H_M      0x05
#define LSM303_OUT_Y_L_M      0x06
#define LSM303_OUT_Z_H_M      0x07
#define LSM303_OUT_Z_L_M      0x08

#include "TWI_Master.h"

// LSM303 interfaces I felt like implementing
unsigned char GetMagStatus();
unsigned char ReadHeading();
void SetAccelCTRL1(unsigned char);

#endif
