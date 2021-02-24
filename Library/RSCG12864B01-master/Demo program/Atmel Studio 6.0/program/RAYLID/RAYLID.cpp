/*
 * RAYLID.cpp
 *
 * Created: 2017-03-10 12:23:21
 *  Author: zhang
 */ 

#include <avr/io.h>
#include "RSCG12864B.h"

int main(void)
{
	unsigned long n;
	RSCG12864B.begin();   //Initialize LCD
	RSCG12864B.clear();   //Clear screen LCD
	RSCG12864B.brightness(0XFF); //Backlight brightness
	n=0;
	while(1)
	{
		RSCG12864B.print_U32_8x16_xy(0,32,n++);
	}
}