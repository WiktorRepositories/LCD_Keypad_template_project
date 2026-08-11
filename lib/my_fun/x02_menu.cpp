/*******************************************************************************************************************
 * x01_menu.h
 *
 * Created: 12.06.2024 
 *  Author: Wiki
 */ 
#include "x02_menu.h"
#ifdef _INC_x02_MENU_H

/*******************************************************************************************************************
 * @name		Display_App_Test1
 * @brief		Display app for kepad 1x4
 * @param[in]	void
 * @note		Test display application 
 * @return		void
 */
void MenuApplication_1x4::Display_App_Test1(void)
{
	uint8_t tData;

	if(_display_data_order_active == true)
	{	tData = _data_from_keypad_IRQ;

		switch (tData)
		{
		case KEYCODE_01: // Keypad 1
			Ref_LCD_application.ClearDisplayData();
			Ref_LCD_application.PrintStr("RED", 3, 0, 0);
			Ref_LCD_application.PrintStr("BLU", 3, 0, 1);
			break;

		case KEYCODE_02: // Keypad 2
			Ref_LCD_application.ReturnCursorHome();
			break;

		case KEYCODE_03: // Keypad 3
			Ref_LCD_application.PrintStr("Ticket 1", 8, LCD_APP_ROW_START, 0);
			break;

		case KEYCODE_04: // Keypad 4
			Ref_LCD_application.PrintStr("Ticket 2", 8, LCD_APP_ROW_START, 1);
			break;

		default:// Other keypad
			break;
		}
		_display_data_order_active = false;
	}
	else{;}
}
//==================================================================================================================

/*******************************************************************************************************************
 * @name		Display_App_Test2
 * @brief		Display app for kepad 1x4
 * @param[in]	void
 * @note		Test display application 
 * @return		void
 */
void MenuApplication_1x4::Display_App_Test2(void)
{
	uint8_t tData;

	if(_display_data_order_active == true)
	{	tData = _data_from_keypad_IRQ;

		switch (tData)
		{
		case KEYCODE_01:
			Ref_LCD_application.ClearDisplayData();
			Ref_LCD_application.PrintStr("RED", 3, 0, 0);
			Ref_LCD_application.PrintStr("BLU", 3, 0, 1);
			break;

		case KEYCODE_02:
			Ref_LCD_application.ReturnCursorHome();
			break;

		case KEYCODE_03:
			Ref_LCD_application.PrintStr("Ticket 1", 8, LCD_APP_ROW_START, 0);
			break;

		case KEYCODE_04:
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
 * @name		IRQ_TIM1_Display
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void MenuApplication_1x4::IRQ_TIM1_Display(void)
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
 * @name		IRQ_TIM2_Keypad
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void MenuApplication_1x4::IRQ_TIM2_Keypad(void)
{
	_keypad_state = RefKeypad1x4.KeypadStateEvaluation();
	if(_keypad_state != KEYCODE_NOPRESS)
	{
		if(_keypad_state == KEYPAD_KEYPAD_STATE_PULS)
		{	Ref_LCD_application.OrderDisplay_IRQ(RefKeypad1x4.GetKeyCode()); }
		else{;}
	}
	else{;}
}
//==================================================================================================================

//==================================================================================================================
#endif // _INC_x01_MENU_H
//==================================================================================================================