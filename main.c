#include <lpc214x.h>
#include "lcdyo.h"
#include "initialize_adc.h"
#include "initialize_motion.h"
#include <string.h>


void main()
{
	init_motion();
	init_pwm();
	Init_ADC_Pin();
	leftPWM(700);
	rightPWM(700);
	DelaymSec(100);
	Init_Peripherals();
  LCD_4Bit_Mode();
  LCD_Init();
  LCD_Command(0x01);
  DelaymSec(20);
  LCD_Command(0x81);
  DelaymSec(20);
  LCD_String("AML PROJECT");
  DelaymSec(20);
  LCD_Command(0xC1);
  DelaymSec(20);
  LCD_String("64 65 81");
  DelaymSec(1000);
  LCD_Command(0x01);
  DelaymSec(20);
	
	unsigned short int centeradc=0, leftadc=0 ,rightadc=0;
 while(1)	
 { 
  	 
  	unsigned char buf[50]= {0};
		LCD_Cursor(1,1);
	  leftadc=adc_left_read();
		centeradc=adc_center_read();
		rightadc=adc_right_read();
  	sprintf((char *)buf, "L:%dC:%dR:%d",leftadc,centeradc,rightadc);
  	LCD_String(buf);
		if((centeradc<45) && (rightadc<45) && (leftadc<45))   // if white surface on each sensor go ahead
			forward();
		else if ((centeradc>45) && (rightadc>45) && (leftadc>45))
			stop();
		else if ((rightadc<45) && (centeradc<45) && (leftadc>45))
		{
		  //while((centeradc>45) | (rightadc>45) | (leftadc>45))
			
				soft_right();
			
		
		}
		else if ((rightadc>45) && (centeradc<45) && (leftadc<45))
		{
			//while((centeradc>45) | (rightadc>45) | (leftadc>45))
			
				soft_left();
			
		
		}
	
}
}