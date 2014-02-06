#include "oswlib/settings.h"

#include "oswlib/PWM/PWM.h"
#include "oswlib/RGB/RGB.h"
#include "oswlib/Serial/serial.h"

#include "oswlib/Examples/TSD/PR5/PR5_UART.h"
#include "oswlib/Examples/TSD/PR5/PR5_EXT_WOM.h"

S_EXT_WOM_PKG EXT_WOM_pkg;

E_RGB_Colors RGB_Color_Selected;

T_UBYTE PR5_current_Color_R;
T_UBYTE PR5_current_Color_G;
T_UBYTE PR5_current_Color_B;

void PR5_S2_Event_Listener(void)
{
	PRIVATE_DATA T_UWORD luw_tick_counter = 0;
	int luw_buttonStatus;
	luw_buttonStatus = readPin(S2);
	if(luw_buttonStatus == 0)
	{		 								//Push Button is ON
		luw_tick_counter++;					//Count ticks
	}
	else
	{										//Push Button is OFF
		if(luw_tick_counter != 0)			//Wait for counter change
		{																
			PR5_Toggle_Ext_Mode();
			luw_tick_counter = 0; 			//Reset Counter
		}
	}	
}

T_BOOLEAN EXT_Mode_Active = FALSE;

void PR5_Toggle_Ext_Mode(void)
{
	
	EXT_Mode_Active = !EXT_Mode_Active;
	
	if(EXT_Mode_Active)
	{
		Serial.print("\r\n\r\nExternal Mode: Active \r\n\r\n>> ");
		Serial2.init(9600);
		Serial2.onReceive = PR5_EXT_WOM_Listener;				//Add Event listener	
	}
	else
	{
		Serial.print("\r\n\r\nExternal Mode: Inactive \r\n\r\n>> ");
		Serial2.end();
	}

}

//S_EXT_WOM_PKG  = {0, 0, 0 };

PRIVATE_DATA T_BOOLEAN Frame_ID_received = FALSE;	//Clear flag

void PR5_EXT_WOM_Listener(void)
{
	PRIVATE_DATA E_EXT_WOM_FRAME NextFrame = SYNC_FRAME;

	if( Serial2.data == SYNC_FRAME_ID )	//Wait for SYNC byte
	{
		NextFrame = SYNC_FRAME;			//Reset Frame
		Frame_ID_received = TRUE;		//Set Flag
	}
	
	if(Frame_ID_received)
	{
		switch(NextFrame)
		{
			case(SYNC_FRAME):
				EXT_WOM_pkg.SYNC = Serial2.data;
				NextFrame = CMD_FRAME;
			break;
			
			case(CMD_FRAME):
				EXT_WOM_pkg.CMD = Serial2.data;
				NextFrame = CHK_FRAME;
			break;
			
			case(CHK_FRAME):
				EXT_WOM_pkg.CHK = Serial2.data;
				Frame_ID_received = FALSE;			//Reset frame
				NextFrame = SYNC_FRAME;
				EXT_WOM_pkg_decode();
			break;
		}	
	}
}

void EXT_WOM_pkg_decode(void)
{
	T_UBYTE EXT_WOM_rx_clc_chk = 0;						//CHK - Checksum (Calculated)
	
	T_UBYTE write_value = 0;	
			
	if(EXT_WOM_pkg.SYNC == EXT_WOM_RX_SYNC)							//SYNC correct
	{							

		EXT_WOM_rx_clc_chk += EXT_WOM_pkg.SYNC;						//Calculated CHK
		EXT_WOM_rx_clc_chk += (T_UBYTE)EXT_WOM_pkg.CMD;						//Calculated CHK

		if(EXT_WOM_rx_clc_chk == EXT_WOM_pkg.CHK)					//CHK Correct
		{			
			
			if( (T_UBYTE)EXT_WOM_pkg.CMD >= 0x80 )
			{
				write_value = (T_UBYTE)EXT_WOM_pkg.CMD - EXT_WOM_CAL_OFF;
				EXT_WOM_pkg.CMD = CAL_COLOR;
			}
			
			switch( EXT_WOM_pkg.CMD )
			{
				case(MODE_OFF):						
						PR5_current_Mode = PR5_MODE_OFF;
						RGB_Color_Selected = RGB_NO_COLOR;
						PR5_current_Color_R = 0x00;
						PR5_current_Color_G = 0x00;
						PR5_current_Color_B = 0x00;
						RGB.setColor(PR5_current_Color_R, PR5_current_Color_G, PR5_current_Color_B);
						PR5_Set_OFF_Mode();
				break;
				case(MODE_SEQ):
						PR5_current_Mode = PR5_MODE_SEQ;
						RGB_Color_Selected = RGB_NO_COLOR;
						PR5_Set_SEQ_Mode();
				break;
				case(MODE_ANALOG):
						PR5_current_Mode = PR5_MODE_ANALOG;
						RGB_Color_Selected = RGB_NO_COLOR;
						PR5_Mode_OFF();
						PR5_Set_ANALOG_Mode();
				break;
				case(SET_COLOR_RED):
					if(PR5_current_Mode == PR5_MODE_ANALOG)
					{
						RGB_Color_Selected = RGB_COLOR_RED;
						Serial.print("\r\n\r\nAnalog Mode - Color: Red \r\n\r\n>> ");
					}
				break;
				case(SET_COLOR_GREEN):
					if(PR5_current_Mode == PR5_MODE_ANALOG)
					{
						RGB_Color_Selected = RGB_COLOR_GREEN;
						Serial.print("\r\n\r\nAnalog Mode - Color: Green \r\n\r\n>> ");
					}
				break;
				case(SET_COLOR_BLUE):
					if(PR5_current_Mode == PR5_MODE_ANALOG)
					{
						RGB_Color_Selected = RGB_COLOR_BLUE;
						Serial.print("\r\n\r\nAnalog Mode - Color: Blue \r\n\r\n>> ");
					}
				break;
				case(CAL_COLOR):
					if(PR5_current_Mode == PR5_MODE_ANALOG)
					{
						
						switch(RGB_Color_Selected)
						{
							case(RGB_COLOR_RED):
								PR5_current_Color_R = write_value;
							break;
							case(RGB_COLOR_GREEN):
								PR5_current_Color_G = write_value;
							break;
							case(RGB_COLOR_BLUE):
								PR5_current_Color_B = write_value;							
							break;
						}
						
						RGB.setColor
						(
							map(PR5_current_Color_R, 0, 100, 0, 255), 
							map(PR5_current_Color_G, 0, 100, 0, 255), 
							map(PR5_current_Color_B, 0, 100, 0, 255)
						);
						
					}
				break;
			}
		}
	}		
}
