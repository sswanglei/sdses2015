#include "StdAfx.h"
#include "PCF8563RTC.h"
#include "i2capp.h"
// 
//PCF8563RTC::PCF8563RTC(void)
//{
//	handle = NULL;
//}
//
//PCF8563RTC::~PCF8563RTC(void)
//{
//}
//
//
//int  PCF8563RTC::PCF8563I2CInit(void)
//{
//	int nRet = 0;	
//	DWORD dwFrequency = PCF8563_I2C_SPEED;  //100K
//	BYTE bySelfAddr = 0x10;
//
//	handle=CreateFile(I2C1_FID,
//		GENERIC_READ|GENERIC_WRITE,
//		FILE_SHARE_READ|FILE_SHARE_WRITE,
//		NULL,
//		OPEN_EXISTING,
//		FILE_FLAG_RANDOM_ACCESS,
//		NULL);
//
//	if(handle==NULL)
//	{
//		fprintlog(NULL, "Open I2C1 failed!\r\n"); 
//		nRet = -1;
//		return nRet;
//	}
//
//	if (!I2C_MACRO_SET_MASTER_MODE(handle))
//	{
// 		fprintlog(NULL, "Open I2C1 failed 1!\r\n"); 
//		PCF8563I2CClose();
//		nRet = -1;
//		return nRet;
//	}
//
//	if (!I2C_MACRO_SET_CLOCK_RATE(handle, dwFrequency))
//	{
// 		fprintlog(NULL, "Open I2C1 failed 2!\r\n"); 
//		PCF8563I2CClose();
//		nRet = -1;
//		return nRet;
//	}
//   /*
//	if (!I2C_MACRO_SET_SELF_ADDR(handle, bySelfAddr))
//	{
// 		fprintlog(NULL, "Open I2C1 failed 3!\r\n"); 
//		PCF8563I2CClose();
//		nRet = -1;
//		return nRet;	
//	}
//    */
//	fprintlog(NULL, "Open I2C1 Success!\r\n"); 	
//	return nRet;
//}
//
//int  PCF8563RTC::PCF8563I2CClose(void)
//{
//	if(handle)
//	{
//		CloseHandle(handle);	
//	}
//	return 0;
//}
//
//UINT32  PCF8563RTC::PCF8563WriteRegister( unsigned char ucRegNum, unsigned char ucValue )
//{
//	UINT32 uiStatus = 0;
//	I2C_TRANSFER_BLOCK  I2CXferBlock;
//	I2C_PACKET          I2CPacket;
//	int                 iResult;
//	unsigned char       data[5];
//
//	if (handle == NULL)
//	{
//		uiStatus = -1;
//		return uiStatus;
//	}
//
//	// set data buffer with register value and data
//	data[0] = PCF8563_I2C_ADDR | 0;                  //地址 
//	data[1] = ucRegNum;
//	data[2] = ucValue;
//
//	I2CPacket.wLen = 3;
//	I2CPacket.byRW = I2C_RW_WRITE;
//	I2CPacket.pbyBuf = data;
//	// if I2C encounters an error, it will write to *lpiResult. 
//	I2CPacket.lpiResult = &iResult;
//
//	I2CXferBlock.pI2CPackets = &I2CPacket;
//	I2CXferBlock.iNumPackets = 1;
//
//	// Write register via I2C
//	uiStatus = I2C_MACRO_TRANSFER(handle,&I2CXferBlock);    
//	if (TRUE != uiStatus)
//	{
//		fprintlog(NULL, "PCF8563WriteRegister failed!\r\n");            
//	}
//	else
//	{
//		fprintlog(NULL, "PCF8563WriteRegister succeed!ucRegNum=%d,ucValue =%x.\r\n", ucRegNum,ucValue);            
//	}    	    
//
//	return 0;
//}
//
//UINT32  PCF8563RTC::PCF8563ReadRegister( UINT8 ucRegNum, UINT8* pucValue )
//{
//	UINT32 uiStatus = PCF8563_SUCCESS;
//	I2C_TRANSFER_BLOCK     I2CXferBlock;
//	I2C_PACKET             I2CPktArray[3];
//	INT32 iResult;
//	UINT8 uiRegData[3];
//	UINT8 uiRegValue;
//	UINT8 ucReturn;
//
//	if (handle == INVALID_HANDLE_VALUE)
//	{
//		uiStatus = PCF8563_I2C_HANDLE;
//		fprintlog(NULL, "PCF8563ReadRegister failed 1!\r\n");  
//		return uiStatus;
//	}
//
//	// set data buffer with register value
//	uiRegData[0] = PCF8563_I2C_ADDR | 0;   //
//	uiRegData[1] = ucRegNum;
//
//	I2CPktArray[0].pbyBuf = uiRegData;
//	I2CPktArray[0].wLen = 2; // let I2C know how much to transmit
//	I2CPktArray[0].byRW = I2C_RW_WRITE;
//	I2CPktArray[0].lpiResult = &iResult; 
//
//
//	uiRegValue = PCF8563_I2C_ADDR | 1;
//	
//	I2CPktArray[1].pbyBuf = &uiRegValue;
//	I2CPktArray[1].wLen = 1; // let I2C know how much to receive
//	I2CPktArray[1].byRW = I2C_RW_WRITE;
//	I2CPktArray[1].lpiResult = &iResult; 
//
//	I2CPktArray[2].pbyBuf = pucValue;
//	I2CPktArray[2].wLen = 1; // let I2C know how much to receive
//	I2CPktArray[2].byRW = I2C_RW_READ;
//	// if I2C encounters an error, it will write to *lpiResult.
//	I2CPktArray[2].lpiResult = &iResult; 
//
//
//	I2CXferBlock.pI2CPackets = &I2CPktArray[0];
//	I2CXferBlock.iNumPackets = 3;
//
//	// Read register via I2C
//	uiStatus = I2C_MACRO_TRANSFER(handle,&I2CXferBlock);
//
//	//ucValue = ucReturn;
//
//	if (TRUE != uiStatus)
//	{
//		//fprintlog(NULL, "PCF8563ReadRegister failed uiStatus = %d. ucRegNum=%d,ucValue =%x.\r\n",uiStatus, ucRegNum,*pucValue);
//	}
//	else
//	{
//		//fprintlog(NULL, "PCF8563ReadRegistersucceed!ucRegNum=%d,ucValue =%x.\r\n", ucRegNum,*pucValue);  
//	}
//
//	return uiStatus;
//}
// 
//
//UINT32  PCF8563RTC::EA_ucSetDateTime(const ET_DATETIME *ptDateTime)
//{
//	UINT32 uiStatus =  PCF8563_SUCCESS;
//
//	// EnterCriticalSection(&m_csI2C); 
//
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_YEARS,(UINT8)(ptDateTime->ucYear-CLK_TS_BASE_YEAR));
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_MONTHS,ptDateTime->ucMonth);
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_DAYS,ptDateTime->ucDay);
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_WEEKDAYS, ptDateTime->ucDayOfWeek);
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_HOURS,ptDateTime->ucHour);
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_MINUTES,ptDateTime->ucMinute);
//	uiStatus = PCF8563WriteRegister(PCF8563_REG_SECONDS,ptDateTime->ucSecond);
//
//
//	// Leave critical section lock
//	//LeaveCriticalSection(&m_csI2C);
//
//	return uiStatus;       	
//}  
//
//
//UINT32  PCF8563RTC::EA_ucGetDateTime(ET_DATETIME *ptDateTime)
//{
//	UINT32 uiStatus =  PCF8563_SUCCESS;
//	unsigned char  tmp = 0;
//
//	//EnterCriticalSection(&m_csI2C);     
//
//	//fprintlog(NULL, "EA_ucGetDateTime start!\r\n");
//	uiStatus = PCF8563ReadRegister(PCF8563_REG_YEARS,&tmp);
//	ptDateTime->ucYear = tmp + CLK_TS_BASE_YEAR;
//
//
//	uiStatus  = PCF8563ReadRegister(PCF8563_REG_MONTHS,&tmp);
//	ptDateTime->ucMonth =  tmp&0x1f;
//
//	uiStatus  = PCF8563ReadRegister(PCF8563_REG_DAYS,&tmp);     
//	ptDateTime->ucDay        = tmp&0x3f;
//
//	uiStatus    = PCF8563ReadRegister(PCF8563_REG_WEEKDAYS,&tmp);
//	ptDateTime->ucDayOfWeek  = tmp&0x07;
//
//	uiStatus    = PCF8563ReadRegister(PCF8563_REG_HOURS,&tmp);
//	ptDateTime->ucHour       = tmp&0x3f;
//
//	uiStatus    = PCF8563ReadRegister(PCF8563_REG_MINUTES,&tmp);
//	ptDateTime->ucMinute     = tmp&0x7f;
//
//	uiStatus    = PCF8563ReadRegister(PCF8563_REG_SECONDS,&tmp);
//	ptDateTime->ucSecond     = tmp&0x7f;  
//	//fprintlog(NULL, "EA_ucGetDateTime end!\r\n");   
//	// Leave critical section lock
//	//LeaveCriticalSection(&m_csI2C);
//
//	return uiStatus;      
//}
//
//typedef struct _SYSTEMTIME {
//  WORD wYear;
//  WORD wMonth;
//  WORD wDayOfWeek;
//  WORD wDay;
//  WORD wHour;
//  WORD wMinute;
//  WORD wSecond;
//  WORD wMilliseconds;
//} SYSTEMTIME, *PSYSTEMTIME;



 
PCF8563RTC::PCF8563RTC(void)
{
	handle = NULL;
}

PCF8563RTC::~PCF8563RTC(void)
{

}


//----------------------------------------------------------------------------------
//初始化I2C接口
//正确返回0,错误返回-1
//----------------------------------------------------------------------------------
int  PCF8563RTC::PCF8563I2CInit(void)
{
	int     nRet          = 0;	
	DWORD   dwFrequency   = PCF8563_I2C_SPEED;  //100K
 

	handle=CreateFile(I2C1_FID,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_RANDOM_ACCESS,
		NULL);

	if(handle==NULL)
	{
		//fprintlog(NULL, "Open I2C1 failed!\r\n"); 
		nRet = -1;
		return nRet;
	}

	if (!I2C_MACRO_SET_MASTER_MODE(handle))
	{
 		//fprintlog(NULL, "Open I2C1 failed 1!\r\n"); 
		PCF8563I2CClose();
		nRet = -1;
		return nRet;
	}

	if (!I2C_MACRO_SET_CLOCK_RATE(handle, dwFrequency))
	{
 		//fprintlog(NULL, "Open I2C1 failed 2!\r\n"); 
		PCF8563I2CClose();
		nRet = -1;
		return nRet;
	}
 	return nRet;
}

//----------------------------------------------------------------------------------
// 
// 
//----------------------------------------------------------------------------------
int  PCF8563RTC::PCF8563I2CClose(void)
{
	if(handle)
	{
		CloseHandle(handle);	
	}
	return 0;
}

//----------------------------------------------------------------------------------
// 
// //正确返回0,错误返回-1
//----------------------------------------------------------------------------------
int  PCF8563RTC::PCF8563WriteRegister( unsigned char ucRegNum, unsigned char ucValue )
{
	int uiStatus = 0;
	I2C_TRANSFER_BLOCK  I2CXferBlock;
	I2C_PACKET          I2CPacket;
	int                 iResult;
	unsigned char       data[5];

	if (handle == NULL)
	{
		uiStatus = -1;
		return uiStatus;
	}

	// set data buffer with register value and data
	data[0] = PCF8563_I2C_ADDR | 0;                  //地址 
	data[1] = ucRegNum;
	data[2] = ucValue;

	I2CPacket.wLen = 3;
	I2CPacket.byRW = I2C_RW_WRITE;
	I2CPacket.pbyBuf = data;
	// if I2C encounters an error, it will write to *lpiResult. 
	I2CPacket.lpiResult = &iResult;

	I2CXferBlock.pI2CPackets = &I2CPacket;
	I2CXferBlock.iNumPackets = 1;

	// Write register via I2C
	   
	if (TRUE != I2C_MACRO_TRANSFER(handle,&I2CXferBlock))
	{
		uiStatus = -1;
		//fprintlog(NULL, "PCF8563WriteRegister failed!\r\n");            
	}
	else
	{
		//fprintlog(NULL, "PCF8563WriteRegister succeed!ucRegNum=%d,ucValue =%x.\r\n", ucRegNum,ucValue);            
	}    	    

	return uiStatus;
}

//----------------------------------------------------------------------------------
// 
// //正确返回0,错误返回-1
//----------------------------------------------------------------------------------
int  PCF8563RTC::PCF8563ReadRegister( UINT8 ucRegNum, UINT8* pucValue )
{
	int uiStatus = PCF8563_SUCCESS;
	I2C_TRANSFER_BLOCK     I2CXferBlock;
	I2C_PACKET             I2CPktArray[3];
	INT32 iResult;
	UINT8 uiRegData[3];
	UINT8 uiRegValue;
 

	if (handle == INVALID_HANDLE_VALUE)
	{
		uiStatus = -1;
		//fprintlog(NULL, "PCF8563ReadRegister failed 1!\r\n");  
		return uiStatus;
	}

	// set data buffer with register value
	uiRegData[0] = PCF8563_I2C_ADDR | 0;   //
	uiRegData[1] = ucRegNum;

	I2CPktArray[0].pbyBuf = uiRegData;
	I2CPktArray[0].wLen = 2; // let I2C know how much to transmit
	I2CPktArray[0].byRW = I2C_RW_WRITE;
	I2CPktArray[0].lpiResult = &iResult; 


	uiRegValue = PCF8563_I2C_ADDR | 1;
	
	I2CPktArray[1].pbyBuf = &uiRegValue;
	I2CPktArray[1].wLen = 1; // let I2C know how much to receive
	I2CPktArray[1].byRW = I2C_RW_WRITE;
	I2CPktArray[1].lpiResult = &iResult; 

	I2CPktArray[2].pbyBuf = pucValue;
	I2CPktArray[2].wLen = 1; // let I2C know how much to receive
	I2CPktArray[2].byRW = I2C_RW_READ;
	// if I2C encounters an error, it will write to *lpiResult.
	I2CPktArray[2].lpiResult = &iResult; 


	I2CXferBlock.pI2CPackets = &I2CPktArray[0];
	I2CXferBlock.iNumPackets = 3;

	// Read register via I2C


	//ucValue = ucReturn;

	if (TRUE != I2C_MACRO_TRANSFER(handle,&I2CXferBlock))
	{
		uiStatus = -1;
		//fprintlog(NULL, "PCF8563ReadRegister failed uiStatus = %d. ucRegNum=%d,ucValue =%x.\r\n",uiStatus, ucRegNum,*pucValue);
	}
	else
	{
		//fprintlog(NULL, "PCF8563ReadRegistersucceed!ucRegNum=%d,ucValue =%x.\r\n", ucRegNum,*pucValue);  
	}

	return uiStatus;
}

//----------------------------------------------------------------------------------
// 
// //正确返回0,错误返回-1
//----------------------------------------------------------------------------------
int  PCF8563RTC::EA_ucSetDateTime(SYSTEMTIME *ptDateTime)
{
	int uiStatus =  0;

	// EnterCriticalSection(&m_csI2C); 

 
	UINT8 tmp;
	tmp = ptDateTime->wYear - CLK_TS_BASE_YEAR;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_YEARS, ((tmp/10)*0x10+(tmp%10)));
	if(uiStatus==-1)
	{
	   return uiStatus;
	}

	tmp = ptDateTime->wMonth;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_MONTHS,((tmp/10)*0x10+(tmp%10)));
	if(uiStatus==-1)
	{
	   return uiStatus;
	}

	tmp = ptDateTime->wDay;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_DAYS,((tmp/10)*0x10+(tmp%10)));
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	tmp = ptDateTime->wHour;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_HOURS,((tmp/10)*0x10+(tmp%10)));	
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	tmp = ptDateTime->wMinute;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_MINUTES,((tmp/10)*0x10+(tmp%10)));
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	tmp = ptDateTime->wSecond;
	uiStatus = PCF8563WriteRegister(PCF8563_REG_SECONDS,((tmp/10)*0x10+(tmp%10)));
 
	//uiStatus = PCF8563WriteRegister(PCF8563_REG_WEEKDAYS, ptDateTime->ucDayOfWeek);
 
	// Leave critical section lock
	//LeaveCriticalSection(&m_csI2C);

	return uiStatus;       	
}  

//----------------------------------------------------------------------------------
// 
// //正确返回0,错误返回-1
//----------------------------------------------------------------------------------
int  PCF8563RTC::EA_ucGetDateTime(SYSTEMTIME *ptDateTime)
{
	int uiStatus =  0;
	unsigned char  tmp = 0;

	//EnterCriticalSection(&m_csI2C);     

	//fprintlog(NULL, "EA_ucGetDateTime start!\r\n");

	uiStatus = PCF8563ReadRegister(PCF8563_REG_YEARS,&tmp);
	ptDateTime->wYear = ((tmp/0x10)*10+tmp%0x10) + CLK_TS_BASE_YEAR;    //1601 through 30827.
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	uiStatus  = PCF8563ReadRegister(PCF8563_REG_MONTHS,&tmp);
	tmp = tmp&0x1f;
	//ptDateTime->wMonth =  tmp&0x1f;    //1~12
	ptDateTime->wMonth =   (tmp/0x10)*10+tmp%0x10;
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	uiStatus  = PCF8563ReadRegister(PCF8563_REG_DAYS,&tmp);     
	tmp = tmp&0x3f;
	ptDateTime->wDay   =   (tmp/0x10)*10+tmp%0x10; //1 through 31.
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	//uiStatus    = PCF8563ReadRegister(PCF8563_REG_WEEKDAYS,&tmp);
	//tmp = tmp&0x07;
	//ptDateTime->wDayOfWeek  =  (tmp/0x10)*10+tmp%0x10;   //0~6

	uiStatus    = PCF8563ReadRegister(PCF8563_REG_HOURS,&tmp);
	tmp = tmp&0x3f;
	ptDateTime->wHour       =   (tmp/0x10)*10+tmp%0x10;  //0~23
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	uiStatus    = PCF8563ReadRegister(PCF8563_REG_MINUTES,&tmp);
	tmp = tmp&0x7f;
	ptDateTime->wMinute     =   (tmp/0x10)*10+tmp%0x10;   //0~59
	if(uiStatus==-1)
	{
	   return uiStatus;
	}


	uiStatus    = PCF8563ReadRegister(PCF8563_REG_SECONDS,&tmp);
	tmp = tmp&0x7f;
	ptDateTime->wSecond     = (tmp/0x10)*10+tmp%0x10;     //0~59
 

	//fprintlog(NULL, "EA_ucGetDateTime end!\r\n");   
	// Leave critical section lock
	//LeaveCriticalSection(&m_csI2C);

	return uiStatus;      
}


