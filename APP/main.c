/*
 * main.c
 *
 * Created on: Aug 30, 2026
 * Author: Mohammed
 */

#include "../LIB/BitMath.h"
#include "../LIB/StdTypes.h"

#include "../MCAL/MDIO/DIO.h"
#include "../MCAL/MTimer1/Timer1.h"

#include "../HAL/HKP/KP.h"
#include "../HAL/H7SEG/7Seg.h"
#include "../HAL/HLCD/LCD.h"
#include "../HAL/HBuzzer/Buzzer.h"

#define APP_MODE_SETUP     0
#define APP_MODE_COUNTDOWN 1
#define APP_MODE_ALARM     2

#define APP_HH_MAX    32
#define APP_MM_MAX    59
#define APP_SS_MAX    59

static u8  G_u8Mode        = APP_MODE_SETUP ;
static u8  G_u8SetupPos    = 0              ;
static u8  G_u8Digits [6]  = {0 , 0 , 0 , 0 , 0 , 0} ;
static u8  G_u8HH          = 0              ;
static u8  G_u8MM          = 0              ;
static u8  G_u8SS          = 0              ;
static volatile u8 G_u8SecFlag = 0          ;
static u8  G_u8FirstTick = 0                ;

static Seg_t G_xSeg ;

static const u8 G_u8SlotCol [6] = {0 , 1 , 5 , 6 , 10 , 11} ;

static void App_voidOnTimer (void)
{
	G_u8SecFlag = 1 ;
}

static void App_voidBuildDigits (void)
{
	G_u8Digits [H7SEG_DIG0] = (u8)(G_u8HH / 10) ;
	G_u8Digits [H7SEG_DIG1] = (u8)(G_u8HH % 10) ;
	G_u8Digits [H7SEG_DIG2] = (u8)(G_u8MM / 10) ;
	G_u8Digits [H7SEG_DIG3] = (u8)(G_u8MM % 10) ;
	G_u8Digits [H7SEG_DIG4] = (u8)(G_u8SS / 10) ;
	G_u8Digits [H7SEG_DIG5] = (u8)(G_u8SS % 10) ;
}

static void App_voidEnterDigit (u8 A_u8Key)
{
	G_u8Digits [G_u8SetupPos] = (u8)(A_u8Key - '0') ;
	HLCD_voidMoveCursor(LCD_ROW1 , G_u8SlotCol [G_u8SetupPos]) ;
	HLCD_voidWriteData(A_u8Key) ;
	G_u8SetupPos ++ ;
}

static void App_voidCheckPair (void)
{
	u8 L_u8Last  = (u8)(G_u8SetupPos - 1) ;
	u8 L_u8Pair  = (u8)(L_u8Last / 2)     ;
	u8 L_u8Start = (u8)(L_u8Pair * 2)     ;
	u8 L_u8Max   = 0                      ;
	u8 L_u8Value = 0                      ;

	if (L_u8Pair == 0)
	{
		L_u8Max = APP_HH_MAX ;
	}
	else if (L_u8Pair == 1)
	{
		L_u8Max = APP_MM_MAX ;
	}
	else
	{
		L_u8Max = APP_SS_MAX ;
	}

	L_u8Value = (u8)(G_u8Digits [L_u8Start] * 10 + G_u8Digits [L_u8Start + 1]) ;

	if (L_u8Value > L_u8Max)
	{
		G_u8Digits [L_u8Start]     = 0 ;
		G_u8Digits [L_u8Start + 1] = 0 ;
		G_u8SetupPos = L_u8Start ;
		HLCD_voidMoveCursor(LCD_ROW1 , G_u8SlotCol [L_u8Start])     ;
		HLCD_voidWriteData('_') ;
		HLCD_voidMoveCursor(LCD_ROW1 , G_u8SlotCol [L_u8Start + 1]) ;
		HLCD_voidWriteData('_') ;
	}
}

static void App_voidShowSetTime (void)
{
	HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL0) ;
	HLCD_voidWriteData((u8)((G_u8HH / 10) + '0')) ;
	HLCD_voidWriteData((u8)((G_u8HH % 10) + '0')) ;

	HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL5) ;
	HLCD_voidWriteData((u8)((G_u8MM / 10) + '0')) ;
	HLCD_voidWriteData((u8)((G_u8MM % 10) + '0')) ;

	HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL10) ;
	HLCD_voidWriteData((u8)((G_u8SS / 10) + '0')) ;
	HLCD_voidWriteData((u8)((G_u8SS % 10) + '0')) ;
}

static void App_voidStartCountdown (void)
{
	if ( (G_u8HH == 0) && (G_u8MM == 0) && (G_u8SS == 0) )
	{
		G_u8Mode = APP_MODE_ALARM ;
		App_voidBuildDigits() ;
		H7SEG_voidDisplay(G_xSeg , G_u8Digits) ;
		HBuzzer_voidBuzzerOff(DIO_PORTB , DIO_PIN3) ;
		HLCD_voidClrScreen() ;
		HLCD_voidMoveCursor(LCD_ROW0 , LCD_COL4) ;
		HLCD_voidDisplayStr((u8*)"TIME UP!") ;
		HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL2) ;
		HLCD_voidDisplayStr((u8*)"00 : 00 : 00") ;
		return ;
	}

	G_u8Mode = APP_MODE_COUNTDOWN ;
	G_u8FirstTick = 1 ;
	App_voidBuildDigits() ;
	H7SEG_voidDisplay(G_xSeg , G_u8Digits) ;
	HLCD_voidClrScreen() ;
	HLCD_voidMoveCursor(LCD_ROW0 , LCD_COL4) ;
	HLCD_voidDisplayStr((u8*)"RUNNING") ;
	HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL0) ;
	HLCD_voidDisplayStr((u8*)"00 : 00 : 00") ;
	App_voidShowSetTime() ;

	MTimer1_voidInit(TIMER1_PRESCALLER256 , TIMER1_CTC_TOP_OCR1A) ;
	MTimer1_voidSetDesiredTime(1000000 , App_voidOnTimer) ;
}

static void App_voidOnKey (u8 A_u8Key)
{
	if ( (A_u8Key >= '0') && (A_u8Key <= '9') && (G_u8SetupPos < 6) )
	{
		App_voidEnterDigit(A_u8Key) ;
		if ( (G_u8SetupPos % 2) == 0 )
		{
			App_voidCheckPair() ;
		}
	}
	else if ( (A_u8Key == '=') && (G_u8SetupPos == 6) )
	{
		G_u8HH = (u8)(G_u8Digits [0] * 10 + G_u8Digits [1]) ;
		G_u8MM = (u8)(G_u8Digits [2] * 10 + G_u8Digits [3]) ;
		G_u8SS = (u8)(G_u8Digits [4] * 10 + G_u8Digits [5]) ;
		App_voidStartCountdown() ;
	}
}

static void App_voidTick (void)
{
	if (G_u8SecFlag == 1)
	{
		G_u8SecFlag = 0 ;

		if (G_u8Mode == APP_MODE_COUNTDOWN)
		{
			if (G_u8FirstTick != 0)
			{
				G_u8FirstTick = 0 ;
			}
			else if (G_u8SS > 0)
			{
				G_u8SS -- ;
			}
			else
			{
				G_u8SS = APP_SS_MAX ;
				if (G_u8MM > 0)
				{
					G_u8MM -- ;
				}
				else
				{
					G_u8MM = APP_MM_MAX ;
					if (G_u8HH > 0)
					{
						G_u8HH -- ;
					}
				}
			}

			App_voidBuildDigits() ;

			if ( (G_u8HH == 0) && (G_u8MM == 0) && (G_u8SS == 0) )
			{
				G_u8Mode = APP_MODE_ALARM ;
				HBuzzer_voidBuzzerOff(DIO_PORTB , DIO_PIN3) ;
				HLCD_voidClrScreen() ;
				HLCD_voidMoveCursor(LCD_ROW0 , LCD_COL4) ;
				HLCD_voidDisplayStr((u8*)"TIME UP!") ;
				HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL2) ;
				HLCD_voidDisplayStr((u8*)"00 : 00 : 00") ;
			}
		}
		else if (G_u8Mode == APP_MODE_ALARM)
		{
			HBuzzer_voidBuzzerTog(DIO_PORTB , DIO_PIN3) ;
		}
	}

	if (G_u8Mode != APP_MODE_SETUP)
	{
		H7SEG_voidRefresh(G_xSeg) ;
	}
}

void main (void)
{
	u8 L_u8Key = KP_NOT_PRESSED ;

	G_u8Mode     = APP_MODE_SETUP ;
	G_u8SetupPos = 0 ;
	G_u8HH = 0 ; G_u8MM = 0 ; G_u8SS = 0 ;

	G_xSeg.Data_Port = DIO_PORTA ;
	G_xSeg.Comm_Port = DIO_PORTC ;
	G_xSeg.Type      = COMM_CATHODE ;

	HKP_voidInit(DIO_PORTD) ;
	H7SEG_voidInit(G_xSeg) ;
	H7SEG_voidOff(G_xSeg) ;
	HLCD_voidInit() ;
	HBuzzer_voidBuzzerInit(DIO_PORTB , DIO_PIN3) ;

	HLCD_voidMoveCursor(LCD_ROW0 , LCD_COL3) ;
	HLCD_voidDisplayStr((u8*)"SET TIMER") ;
	HLCD_voidMoveCursor(LCD_ROW1 , LCD_COL0) ;
	HLCD_voidDisplayStr((u8*)"__ : __ : __") ;

	while (1)
	{
		if (G_u8Mode == APP_MODE_SETUP)
		{
			L_u8Key = HKP_u8GetPressedValue(DIO_PORTD) ;
			if (L_u8Key != KP_NOT_PRESSED)
			{
				App_voidOnKey(L_u8Key) ;
			}
		}
		else
		{
			App_voidTick() ;
		}
	}
}
