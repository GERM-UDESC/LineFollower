#ifndef	SysClock_H
#define SysClock_H
#include "Micro.h"
#include "GPIO.h"


typedef enum{
	BASE_100ms 	= (7200000-1),	
	BASE_10ms 	= (720000	-1),
	BASE_1ms 		= (72000	-1),
	BASE_100us  = (7200		-1),
	BASE_10us  	= (720		-1),
	BASE_1us  	= (72			-1),
}SysTickBaseTimeEnum;

class	SysClock
{
	private:
	void HSEClockInit();
	
	
	public:
	SysClock();
	
	void SysClockInit();	//Initillizes the clock as 72MHz 
	void MCO();						//Config. PA8 as a output clock source
	void SysTickInit(SysTickBaseTimeEnum BASE_TIME); //Initialize the SysTick
	bool SysTickGetEvent();
	
};

#endif
