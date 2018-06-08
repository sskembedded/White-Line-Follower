#include <lpc214x.h>


void Init_ADC_Pin(void)
{
 PINSEL0|= 0x03000000;		//Seting P0.12 as ADC1.3
 PINSEL1&= 0xF0FFFFFF;		
 PINSEL1|= 0x05000000;	    //Settin pins P0.28, P0.29 as ADC0.1 ad0.2
}

unsigned short adc_left_read()
{
	unsigned int adcdata;

	  AD1CR=0x01200C08;
	 while(!((adcdata = AD1GDR) & 0x80000000));		// Check end of conversion 
	 return((adcdata >> 6) & 0x3ff) ;				// Return 10 bit result
}
unsigned short adc_right_read()
{
	unsigned int adcdata;
		AD0CR=0x01200C04;
	
	while(!((adcdata = AD0GDR) & 0x80000000));		// Check end of conversion 
	return((adcdata >> 6) & 0x3ff) ;				// Return 10 bit result
}
unsigned short adc_center_read()
{
	unsigned int adcdata;
		AD0CR=0x01200C02;
	
	while(!((adcdata = AD0GDR) & 0x80000000));		// Check end of conversion 
	return((adcdata >> 6) & 0x3ff) ;				// Return 10 bit result
}