#ifndef OSWARRIOR_HCSR04_H_
	#define OSWARRIOR_HCSR04_H_

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	void HCSR04_enable(int trig, int echo);
	T_ULONG HCSR04_read(void);
	
	T_ULONG HCSR04_read_cm(void);
	T_FLOAT HCSR04_read_cm_float(void);
	T_ULONG HCSR04_read_inches(void);
	T_FLOAT HCSR04_read_inches_float(void);

	/*
	** ===================================================================
	** HC-SR04 Sensor Structure Definition
	** ===================================================================
	*/
	
	typedef struct{
		int TRIG;
		int ECHO;
		void (*enable)(int trig, int echo);		/*** HC-SR04 - Initialization function ***/
		T_ULONG (*cm)(void);					/*** HC-SR04 - Centimetres Read Function ***/
		T_FLOAT (*cmFloat)(void);				/*** HC-SR04 - Centimetres Float Read Function ***/
		T_ULONG (*inches)(void);				/*** HC-SR04 - Inches Read Function ***/
		T_FLOAT (*inchesFloat)(void);			/*** HC-SR04 - Inches Float Read Function ***/
	}HCSR04STR;	
	
	extern HCSR04STR HCSR04;
	
#endif
