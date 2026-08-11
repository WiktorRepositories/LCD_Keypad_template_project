/*
 * x01_menu.h
 *
 * Created: 12.06.2024 
 *  Author: Wiki
 */ 
#include "x01_menu.h"
#ifdef _INC_x01_MENU_H

#define ROW_RED 4U
#define ROW_BLU 4U

#define COL_RED 0U
#define COL_BLU 1U

/*******************************************************************************************************************
 * @name		InitializeDisplay_AppTest1
 * @brief		Prepare LCD display data for Display_App_Test1
 * @param[in]	void
 * @note		Informations RED and BLU team are displayed in certain place
 * @return		void
 */
void MenuApplication_4x4::InitializeDisplay_AppTest1(void)
{
	Ref_LCD_application.ClearDisplayData();

	Ref_LCD_application.PrintStr("RED", 3, 0, COL_RED);
	Ref_LCD_application.PrintStr("   ", 3, 4, COL_RED);
	Ref_LCD_application.PrintInt(MENU_VALUE_ZERO_uint8_t, ROW_RED, COL_RED);

	Ref_LCD_application.PrintStr("BLU", 3, 0, COL_BLU);
	Ref_LCD_application.PrintStr("   ", 3, 4, COL_BLU);
	Ref_LCD_application.PrintInt(MENU_VALUE_ZERO_uint8_t, ROW_BLU, COL_BLU);

	_ticketRedNum = 0;
	_ticketBluNum = 0;
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		Display_App_Test1
 * @brief		Display app for kepad 4x4
 * @param[in]	void
 * @note		Data and screen to display is set from DisplaySetOrder
 * @return		void
 */
void MenuApplication_4x4::Display_App_Test1(void)
{
	uint8_t tData = _data_from_keypad_IRQ;

	if(tData == true)
	{	//tData = _data_from_keypad_IRQ;
		switch (tData)
		{
		case KEYCODE_11: // Keypad 11, Increase RED tickets
			_ticketRedNum++;
			Ref_LCD_application.PrintInt_Format(_ticketRedNum, 3, 0);
			break;

		case KEYCODE_12: // Keypad 12, Decrease RED tickets
			_ticketRedNum--;
			Ref_LCD_application.PrintInt_Format(_ticketRedNum, 3, 0);
			break;

		case KEYCODE_13: // Keypad 13, Increase BLU tickets
			_ticketBluNum++;
			Ref_LCD_application.PrintInt_Format(_ticketBluNum, 3, 1);
			break;

		case KEYCODE_14: // Keypad 14, Decrease BLU tickets
			_ticketBluNum--;
			Ref_LCD_application.PrintInt_Format(_ticketBluNum, 3, 1);
			break;

		default:// Other keypad
			break;
		}
		_display_data_order_active = false;
	}
	else{;}

	if(_printtime == true) 
	{
		Ref_LCD_application.PrintTimeOther((data_time::time_t*)&(_time), 8, 0);
		Ref_LCD_application.PrintTimeOther((data_time::time_t*)&(_time), 8, 1);
		_printtime = false;
	}
	else{;}
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		InitializeDisplay_AppTest2
 * @brief		Prepare LCD display data for Display_App_Test2
 * @param[in]	void
 * @note		Informations RED and BLU team are displayed in certain place
 * @return		void
 */
void MenuApplication_4x4::InitializeDisplay_AppTest2(void)
{
	Ref_LCD_application.ClearDisplayData();

	Ref_LCD_application.PrintStr("RED", 3, 0, 0);
	Ref_LCD_application.PrintStr("BLU", 3, 0, 1);

	//Ref_LCD_application.PrintInt(MENU_VALUE_ZERO_uint8_t, 8,0);
	//Ref_LCD_application.PrintInt(MENU_VALUE_ZERO_uint8_t, 8,0);
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		Display_App_Test2
 * @brief		Display app for kepad 1x4
 * @param[in]	void
 * @note		Test display application 
 * @return		void
 */
void MenuApplication_4x4::Display_App_Test2(void)
{
	uint8_t tData;

	if(_display_data_order_active == true)
	{	tData = _data_from_keypad_IRQ;

		switch (tData)
		{
		case KEYCODE_11: // Keypad 11
			Ref_LCD_application.ClearDisplayData();
			Ref_LCD_application.PrintStr("RED", 3, 0, 0);
			Ref_LCD_application.PrintStr("BLU", 3, 0, 1);
			break;

		case KEYCODE_12: // Keypad 12
			Ref_LCD_application.ReturnCursorHome();
			break;

		case KEYCODE_13: // Keypad 13
			Ref_LCD_application.PrintStr("Ticket 1", 8, LCD_APP_ROW_START, 0);
			break;

		case KEYCODE_14: // Keypad 14
			Ref_LCD_application.PrintStr("Ticket 2", 8, LCD_APP_ROW_START, 1);
			break;

		default:
			break;
		}
		_display_data_order_active = false;
	}
	else{;}
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		IRQ_TIM1_AddMilisecondsAmount
 * @brief		Increase time by seconds amount
 * @param[in]	sec Amount of seconds to increase
 * @note		Cyclical time increase in timer interrupt
 */
void MenuApplication_4x4::IRQ_TIM1_(void)
{
	RefDataAndTime.IRQ_TickEvent();
	RefDataAndTime.GetTime((data_time::time_t*)&_time);
	_printtime = true;
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		IRQ_TIM1_Display
 * @brief		Cyclical data incrementation for: Display_App_Test1, Display_App_Test2
 * @param[in]	void
 * @note		Data and information is taken from IRQ_TIM2_Keypad()
 * @return		void
 */
inline void MenuApplication_4x4::IRQ_TIM1_Display(void)
{
    static uint8_t n_TIMER1, someNum;
    switch (n_TIMER1)
	{
	case 0x00:
		n_TIMER1 = 0x11;

		//RefConvertTime.NumToString(someNum, arrChars1, TYPE_DEC_uin8_t);
		//RefConvertTime.ToStrFormatDec(arrChars1, 3, arrChars2, 3);

		Ref_LCD_application.PrintStr(arrChars2, 4,  6, 0);
		break;

	case 0x11:
		n_TIMER1 = 0x22;
		
		//RefConvertTime.NumToString(someNum, arrChars1, TYPE_HEX_uin8_t);
		//RefConvertTime.ToStrFormatHex(arrChars1, 3, arrChars2, 3);

		Ref_LCD_application.PrintStr(arrChars2, 4,  6, 1);
	
		someNum++;
		n_TIMER1 = 0x00;
		break;

	default:
		someNum++;
		n_TIMER1 = 0x00;
		break;
	}
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		DisplaySetOrder
 * @brief		Data is saved from cyclical and presed keypad IRQ 
 * @param[in]	inData Data from keypad to display
 * @note		void
 * @return		void
 */
 bool MenuApplication_4x4::KeypadButtonData(uint8_t inData)
 {
	if(_display_data_order_active == false)
	{
		_data_from_keypad_IRQ = inData;
		_display_data_order_active = true;
		return true;
	}
	else
	{	return false; }
 }
//==================================================================================================================

/*******************************************************************************************************************
 * @name		IRQ_TIM2_Keypad
 * @brief		Cyclical keypad scan for key press
 * @param[in]	void
 * @note		Key cyclical scan in IRQ interrupt for timer 2
 * @return		void
 */
void MenuApplication_4x4::IRQ_TIM2_Keypad(void)
{
	_keypad_state = RefKeypad4x4.KeypadStateEvaluation();
	if(_keypad_state != KEYCODE_NOPRESS)
	{	
		if(_keypad_state == KEYPAD_KEYPAD_STATE_PULS)
		{	
			KeypadButtonData(RefKeypad4x4.GetKeyCode());
		}
		else{;}
	}
	else{;}
}
//==================================================================================================================

//==================================================================================================================
#endif // _INC_x01_MENU_H
//==================================================================================================================