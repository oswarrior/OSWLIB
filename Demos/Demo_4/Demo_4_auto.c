#include "oswlib/Demos/Demo_4/Demo_4_auto.h"
	
#define STEP_FULL		0
#define STEP_HALF		4
#define STEP_QUARTER	2
#define STEP_EIGHTH		6
#define STEP_SIXTEENTH	7

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void Demo_4_auto(void)
{
	//Control Signals
	int CLK = 3, DIR = 0, EN = 7;
	int MS1 = 17, MS2 = 16, MS3 = 15;
	
	//Local Variables
	static int freq_signal[10] = 	{ 50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
	static int step_qty[10] = 		{30, 50, 120, 80, 200, 10, 50, 30, 20, 10};
	static int step_res = STEP_FULL;
	static int i,a;
	int CLK_Delay[2];
	int CLK_Delay_temp;
	
	//Configure Pin Direction
	pinDirection(DIR, OUTPUT);
	pinDirection(CLK, OUTPUT);

	writePin(DIR,LEFT);
	writePin(CLK, OFF);
	
	// Set Motor Step Resolution
	pinDirection(MS1, OUTPUT);
	pinDirection(MS2, OUTPUT);
	pinDirection(MS3, OUTPUT);
	
	writePin(MS1, (step_res & 0x04));
	writePin(MS2, (step_res & 0x02));
	writePin(MS3, (step_res & 0x01));	
		
	for(;;)	
	{
		for(a = 0; a < 10; a++)
		{
			for(i = 0; i < (step_qty[a] * 2); i++)
			{
				togglePin(CLK);   
				delay( (int)( 500/freq_signal[a] ) );
			}
		}
		togglePin(DIR);
		
		for(a = 10; a > 0; a--)
		{
			for(i = 0; i < (step_qty[a] * 2); i++)
			{
				togglePin(CLK);   
				delay( (int)( 500/freq_signal[a] ) );
			}
		}
		togglePin(DIR);
	}
	
	return;
}

