#pragma once

 #include "stdafx.h"
//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define I2C1_FID                         _T("I2C1:")
#define I2C2_FID                         _T("I2C2:")
#define I2C3_FID                         _T("I2C3:")

 

#define I2C_RW_WRITE                    1           // Perform Write operation
#define I2C_RW_READ                     2           // Perform Read operation
#define I2C_METHOD_MASK                 0x7f

#define I2C_MODE_MASK                   0x80
#define I2C_POLLING_MODE                0x80
#define I2C_INTERRUPT_MODE              0x00 

#define I2C_MAX_FREQUENCY               400000      // Maximum I2C frequency setting

//
// IO Control Codes
//
// Developers are encourage to use the macros listed below to access the driver
// capabilities.
// All the IOCTL codes provided here has a macro equivalent. The details for each
// IOCTL will be explained in the corresponding macros.
//
 
#define I2C_IOCTL_SET_SLAVE_MODE        CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3000, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Set I2C Bus to Slave Mode
#define I2C_IOCTL_SET_MASTER_MODE       CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3001, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Set I2C Bus to Master Mode
#define I2C_IOCTL_IS_MASTER             CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3002, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Is it in Master Mode?
#define I2C_IOCTL_IS_SLAVE              CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3003, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Is it in Slave Mode?
#define I2C_IOCTL_GET_CLOCK_RATE        CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3004, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Get Last Known Clock Rate
#define I2C_IOCTL_SET_CLOCK_RATE        CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3005, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Set Clock Rate
#define I2C_IOCTL_SET_SELF_ADDR         CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3007, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Set My Address (Slave Mode)
#define I2C_IOCTL_GET_SELF_ADDR         CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3008, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Get My Address (Slave Mode)
#define I2C_IOCTL_TRANSFER              CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3009, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Transfer Data
#define I2C_IOCTL_RESET                 CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3010, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Software Reset
#define I2C_IOCTL_ENABLE_SLAVE          CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3011, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Enable slave mode
#define I2C_IOCTL_DISABLE_SLAVE         CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3012, METHOD_BUFFERED, FILE_ANY_ACCESS)  // Disable slave mode


//------------------------------------------------------------------------------
// Types
//------------------------------------------------------------------------------
// I2C Packet
typedef struct
{
    //BYTE byAddr;       // I2C slave device address for this I2C operation
    BYTE byRW;         // Read = I2C_READ or Write = I2C_WRITE
    PBYTE pbyBuf;      // Message Buffer
    WORD wLen;         // Message Buffer Length
    LPINT lpiResult;   // Contains the result of last operation
} I2C_PACKET, *PI2C_PACKET;

// I2C Transfer Block
typedef struct
{
    I2C_PACKET *pI2CPackets;
    INT32 iNumPackets;
} I2C_TRANSFER_BLOCK, *PI2C_TRANSFER_BLOCK;





#define PCF8563_I2C_ADDR               0xa2
#define PCF8563_I2C_SPEED              100000 // 100kHz
#define PCF8563_SUCCESS                0x0
#define PCF8563_INVALID                0x1  // invalid parameter
#define PCF8563_I2C_HANDLE             0x2  // invalid I2C handle
#define PCF8563_I2C_OPERROR            0x3  // I2C operation error

#define CLK_TS_BASE_YEAR               2000

#define  PCF8563_REG_SECONDS     0x02
#define  PCF8563_REG_MINUTES     0x03
#define  PCF8563_REG_HOURS       0x04
#define  PCF8563_REG_DAYS        0x05
#define  PCF8563_REG_WEEKDAYS    0x06
#define  PCF8563_REG_MONTHS      0x07
#define  PCF8563_REG_YEARS       0x08 

 

class PCF8563RTC
{
public:
   HANDLE  handle;

	PCF8563RTC(void);
	~PCF8563RTC(void);
    int  PCF8563I2CInit(void);
	int  EA_ucGetDateTime(SYSTEMTIME *ptDateTime);
	int  EA_ucSetDateTime(SYSTEMTIME *ptDateTime);
private:
	int  PCF8563I2CClose(void);
    int  PCF8563WriteRegister( unsigned char ucRegNum, unsigned char ucValue );
    int  PCF8563ReadRegister( UINT8 ucRegNum, UINT8* pucValue );

};
