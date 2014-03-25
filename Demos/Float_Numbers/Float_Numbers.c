/*
 * example1_FloatNumber.c
 *
 *  Created on: Nov 25, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Float_Numbers/Float_Numbers.h"

void example_FloatNumbers(void)
{
	T_FLOAT x = 0;
	
	Serial.init(9600);
	Serial.clear();
	
	Serial.write("\fprintFloat = ");
	Serial.printFloat(x, 5);
	Serial.write("\r\nprintNum = ");
	Serial.print((T_SLONG)x);	
	Serial.write("\r\nprintDigits = ");
	Serial.printDigits((T_SLONG)x, 5);
	Serial.newLine();

	for( x = _M_PI; x < 999999999; x*= 10)
	{
		Serial.write("\r\nprintNum = ");
		Serial.print((T_SLONG)x);	
		Serial.write("\r\nprintDigits = ");
		Serial.printDigits((T_SLONG)x, 5);
		Serial.write("\r\nprintFloat = ");
		Serial.printFloat(x, 5);
		Serial.newLine();
	}
	
	x = (_M_PI / 4);

	//Sine
	Serial.write("\r\nSin(X) = ");
	Serial.printFloat(sin(x), 5);
	//Cosine
	Serial.write("\r\nCos(X) = ");
	Serial.printFloat(cos(x), 5);
	//Tangent
	Serial.write("\r\nTan(X) = ");
	Serial.printFloat(tan(x), 5);
	//Root Square
	Serial.write("\r\nsqrt(X) = ");
	Serial.printFloat(sqrt(x), 5);
	//Power Square
	Serial.write("\r\npow(X,2) = ");
	Serial.printFloat(pow(x,2), 5);	
	//Log 10
	Serial.write("\r\nlog10(X) = ");
	Serial.printFloat(log10(x), 5);	
	//Ln
	Serial.write("\r\nlog(X) = ");
	Serial.printFloat(log(x), 5);	
	
}
