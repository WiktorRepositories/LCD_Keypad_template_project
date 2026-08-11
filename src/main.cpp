#include <Initialization_328p/Init_328p.h>
#include <KeyPad/KeyPad_4x4.h>
#include "External_time_module/time_module.h"
#include "x01_menu.h"

/**************************************************************************
 * Initialization of a class objects
*/
InitPeryferia_m328p 	myInitialization_uC;
LCD_application 		myLCD_app(16,2);
Keypad4x4 				myKeyPad4x4(0x07);
DataAndTime 			myDataAndTime(2);
// Call for applicatin
MenuApplication_4x4		myMenuApp_4x4(myLCD_app, myKeyPad4x4, myDataAndTime);
//=========================================================================

int main(void)
{
	myInitialization_uC.DataDirectionsResistrsInit();	// Inicializacja Port�w
	myInitialization_uC.Timer1Init();	// Inicializacja TIMER1 16 bit, szczegóły w definicji klasy
	myInitialization_uC.Timer2Init();	// Inicializacja TIMER2 8 bit

// Inicializacja wyswetlacza LCD, zajmje przynajmniej 40ms
	myLCD_app.InitializeDevice();
//============================================================================

// Miejsce na wyswitlanie danych pod wstępnej inicializacji 
	myMenuApp_4x4.InitializeDisplay_AppTest1();
	while(1)
	{
		myMenuApp_4x4.Display_App_Test1();
	}
	return 0;
}
//=============================================================================

/******************************************************************************
 * Przerwanie dla Timer1 z powodu porównania dla licznika
*/
ISR(TIMER1_COMPA_vect)
{
	;
}
//=============================================================================

/******************************************************************************
 * Przerwanie dla Timer1 z powodu przepełnienia
*/
ISR(TIMER1_OVF_vect)
{
	myMenuApp_4x4.IRQ_TIM1_();
}
//=============================================================================

/******************************************************************************
 * Interrupt call for Timer 2
*/
ISR(TIMER2_OVF_vect)
{ 
	myMenuApp_4x4.IRQ_TIM2_Keypad();
}
//=============================================================================