/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 pwm.h
** 	Description: OSWarrior Pulse Width Modulation (PWM) library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organization; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

/*
** ===================================================================
** PWM includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/PWM/PWM.h"
#include "oswlib/RGB/RGB.h"

/*
** ===================================================================
** RGB Structure definition
** ===================================================================
*/

S_RGBSTR RGB = {
	-1,
	-1,
	-1,
	RGB_enable,
	RGB_disable,
	RGB_setColor
};
	
/*
** ===================================================================
**     Function : RGB.enable
**     Handler  : RGB_enable
**
**     Description :
**         Initialize the analog pins as ADC inputs, doing this the 
**         analog pins will can't be used as digital pins.
**         
**     Parameters  : Nothing
**     
**     Returns     : Nothing
** ===================================================================
*/

void RGB_enable(int channel_red,int channel_green,int channel_blue)
{
	RGB.channel_red = channel_red;
	RGB.channel_green = channel_green;
	RGB.channel_blue = channel_blue;
	
	PWM.enable(RGB.channel_red);
	PWM.enable(RGB.channel_green);
	PWM.enable(RGB.channel_blue);
}

/*
** ===================================================================
**     Function : RGB.disable
**     Handler  : RGB_disable
**
**     Description :
**         Initialize the analog pins as ADC inputs, doing this the 
**         analog pins will can't be used as digital pins.
**         
**     Parameters  : Nothing
**     
**     Returns     : Nothing
** ===================================================================
*/

void RGB_disable(void)
{
	PWM.disable(RGB.channel_red);
	PWM.disable(RGB.channel_green);
	PWM.disable(RGB.channel_blue);
}

/*
** ===================================================================
**     Function : RGB.setColor
**     Handler  : RGB_setColor
**
**     Description :
**         Initialize the analog pins as ADC inputs, doing this the 
**         analog pins will can't be used as digital pins.
**         
**     Parameters  : Nothing
**     
**     Returns     : Nothing
** ===================================================================
*/

void RGB_setColor(int red,int green,int blue)
{
	red = red * 100 / 255;
	green = green * 100 / 255;
	blue = blue * 100 / 255;
	
	PWM.dutyCycle(RGB.channel_red, red);
	PWM.dutyCycle(RGB.channel_green, green);
	PWM.dutyCycle(RGB.channel_blue, blue);	
}
