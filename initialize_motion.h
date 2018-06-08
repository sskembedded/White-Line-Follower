#include <lpc214x.h>

void stop();

void l_forward()
{
IO1SET|=(1<<21);
}

void l_backward()
{
IO0SET|=(1<<22);
}

void r_forward()
{
IO0SET|=(1<<10);
}

void r_backward()
{
IO0SET|=(1<<11);
}

void forward()
{
stop();
l_forward();
r_forward();
}


void reverse()
{
stop();
l_backward();
r_backward();
}

void right()
{
stop();
l_forward();
r_backward();
}

void left()
{
stop();
l_backward();
r_forward();
}

void soft_right()
{
stop();
l_forward();
}

void soft_left()
{
stop();
r_forward();
}

void soft_right2()
{
stop();
r_backward();
}

void soft_left2()
{
stop();
l_backward();
}

void stop()
{
IO0CLR|=(1<<22);        //l_back_stop
IO1CLR|=(1<<21);        //l_forth_stop
IO0CLR|=(1<<11);        //r_back_stop
IO0CLR|=(1<<10);        //r_forth_stop
}

void init_motion()
{
 PINSEL0&=0xFF0FFFFF;		//Set P0.10, P0.11 as GPIO
 PINSEL1&=0xFFFFFCFF;	//Set P0.21 as GPIO
 PINSEL2&=0xFFFFFFF7; // set p1.21 as gpio ***
 IO0DIR&=0xFF9FF37F;
 IO0DIR|= (1<<10) | (1<<11) | (1<<21) | (1<<22) | (1<<7); 	//Set P0.10, P0.11, P0.21, P0.22, P0.7 as Output pins
 IO1DIR&=0xFFDFFFFF;
 IO1DIR|= (1<<21);		// Set P1.21 as output pin
 stop();
}

void init_pwm()
{
 PINSEL0&=0xFFFF3FFF;
 PINSEL0|=0x00008000;	//Enabling P0.7 as PWM2 - 10
 PINSEL1&=0xFFFFF3FF;		
 PINSEL1|=0x00000400;	//Enabling P0.22 as PWM5 - 01

 PWMPR = 30;
 PWMPC  = 0;
 PWMTC  = 0;
 PWMMR0 = 1000;
 PWMMCR |= (1<<1);     // Reset PWMTC on PWMMR0 match
 PWMLER = (1<<0)|(1<<2)|(1<<5);
 PWMPCR |= (1<<10);     // enable PWM 2 output
 PWMPCR |= (1<<13);     // enable PWM 5 output
 PWMTCR |= (1<<1) ;     //Reset PWM TC & PR
 PWMTCR = (1<<0) | (1<<3);     // enable counters and PWM Mode

}

void leftPWM(unsigned int vel)
{
 PWMMR2 = vel;
 PWMLER |= (1<<2);
}

void rightPWM(unsigned int vel)
{
 PWMMR5 = vel;
 PWMLER |= (1<<5);
}
