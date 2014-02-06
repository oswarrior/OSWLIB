/*
 * example1_FloatNumber.c
 *
 *  Created on: Nov 25, 2013
 *      Author: HuAr
 */

#include "oswlib/Examples/Float_Numbers/Float_Numbers.h"

void example_FloatNumbers(void)
{
	T_FLOAT x = 0;
	
	Serial.init(9600);
	Serial.clear();
	
	Serial.print("\fprintFloat = ");
	Serial.printFloat(x, 5);
	Serial.print("\r\nprintNum = ");
	Serial.printNum((T_SLONG)x);	
	Serial.print("\r\nprintDigits = ");
	Serial.printDigits((T_SLONG)x, 5);
	Serial.newLine();

	for( x = _M_PI; x < 999999999; x*= 10)
	{
		Serial.print("\r\nprintNum = ");
		Serial.printNum((T_SLONG)x);	
		Serial.print("\r\nprintDigits = ");
		Serial.printDigits((T_SLONG)x, 5);
		Serial.print("\r\nprintFloat = ");
		Serial.printFloat(x, 5);
		Serial.newLine();
	}
	
	x = (_M_PI / 4);

	//Sine
	Serial.print("\r\nSin(X) = ");
	Serial.printFloat(sin(x), 5);
	//Cosine
	Serial.print("\r\nCos(X) = ");
	Serial.printFloat(cos(x), 5);
	//Tangent
	Serial.print("\r\nTan(X) = ");
	Serial.printFloat(tan(x), 5);
	//Root Square
	Serial.print("\r\nsqrt(X) = ");
	Serial.printFloat(sqrt(x), 5);
	//Power Square
	Serial.print("\r\npow(X,2) = ");
	Serial.printFloat(pow(x,2), 5);	
	//Log 10
	Serial.print("\r\nlog10(X) = ");
	Serial.printFloat(log10(x), 5);	
	//Ln
	Serial.print("\r\nlog(X) = ");
	Serial.printFloat(log(x), 5);	
	
}