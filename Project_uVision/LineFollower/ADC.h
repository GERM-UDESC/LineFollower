#ifndef ADC_DRIVER
#define ADC_DRIVER
#include "GPIO.h"
#include "TIMER.h"


typedef enum{
	SINGLE_CONVERSION,
	CONTINUOUS_CONVERSION,
}ADC_CONVERSION_MODES;

typedef enum{
	ADC_CH0 = 0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7,
	ADC_CH8,
	ADC_CH9,
}ADC_CHANNELS;

class ADC : protected GPIO
{
private:
	static ADC_CONVERSION_MODES ADCMode;
	ADC_CHANNELS ADCChannel;
	
	void ADCCalibrate();
	

protected:
	void ConfigADCPin();
	//SETTERS
	//void SetADCMode(ADC_CONVERSION_MODES ADCMode);
	void SetADCChannel(ADC_CHANNELS ADCChannel);
//	ADC(){};

public:
	//Constructor
	ADC(ADC_CHANNELS ADCChannel);
	
	//Methods
	uint16_t analogRead();							
	
	//GETTERS
//	ADC_CONVERSION_MODES GetADCMode();
	ADC_CHANNELS GetADCChannel();
	
	

};

#endif
