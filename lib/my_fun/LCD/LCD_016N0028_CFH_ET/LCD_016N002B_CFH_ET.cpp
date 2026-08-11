/*
 * LCD_016N002B_CFH_ET.h
 *
 * Created: 01.01.2024
 *  Author: Wiki
 */
#include "LCD_016N002B_CFH_ET.h"
#ifdef _INC_LCD_016N002B_CFH_ET
/*****************************************************************************************************
 * 
*/

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_016N002B_CFH_ET
 * @brief		Constructor for class LCD_016N002B_CFH_ET
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_016N002B_CFH_ET::LCD_016N002B_CFH_ET(uint8_t row_n, uint8_t col_n){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_016N002B_CFH_ET
 * @brief		Deconstructor for class LCD_016N002B_CFH_ET
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_016N002B_CFH_ET::~LCD_016N002B_CFH_ET(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutCommand
 * @brief		Send comand for LCD display
 * @param[in]	cmd Input comand as uint8_t
 * @note		Pins configuration depend from conections
 * 				This method need to be modyfied depend on connection
 * @return		void
 */
inline void LCD_016N002B_CFH_ET::_PutCommandLong(uint8_t cmd, enum_DISPLAY_DELAY_TIME_MS time_ms)
{
	PORTD = cmd;

	// Clear B0 RS PIN do zapisywania znaku lub komendy
	PORTB = PORTB & LCD_MASK_PORTB_CLR_B0_RS;

	// Clear B1 E PIN, Set B1 E enable pin
	PORTB = PORTB & LCD_MASK_PORTB_CLR_B1_E;
	PORTB = PORTB | LCD_MASK_PORTB_SET_B1_E;

	_delay_ms(time_ms);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutCommand
 * @brief		Send comand for LCD display
 * @param[in]	cmd Input comand as uint8_t
 * @note		Pins configuration depend from conections
 * 				This method need to be modyfied depend on connection
 * @return		void
 */
inline void LCD_016N002B_CFH_ET::_PutCommandShort(uint8_t cmd, enum_DISPLAY_DELAY_TIME_US time_us)
{
	PORTD = cmd;

	// Clear B0 RS PIN do zapisywania znaku lub komendy
	PORTB = PORTB & LCD_MASK_PORTB_CLR_B0_RS;

	// Clear B1 E PIN, Set B1 E enable pin
	PORTB = PORTB & LCD_MASK_PORTB_CLR_B1_E;
	PORTB = PORTB | LCD_MASK_PORTB_SET_B1_E;

	_delay_us(time_us);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutData
 * @brief		Send data for LCD display
 * @param[in]	cmd Input data as uint8_t
 * @note		Pins configuration depend from conections
 * 				This method need to be modyfied depend on connection
 * @return		void
 */
void LCD_016N002B_CFH_ET::PutData(uint8_t data)
{
	PORTD = data;

	// set B0 RS PIN do zapisywania znaku lub komendy
	PORTB = PORTB | LCD_MASK_PORTB_SET_B0_RS;
	
	// Clear B1 E PIN, Set B1 E enable pin
	PORTB = PORTB & LCD_MASK_PORTB_CLR_B1_E; 
	PORTB = PORTB | LCD_MASK_PORTB_SET_B1_E;

	_delay_us(DISPLAY_DELAY_TIME_us_writeDataRAM);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ClearDisplay
 * @brief		Clear LCD display 
 * @param[in]	void
 * @note		Method working OK
 * @return		void
 */
void LCD_016N002B_CFH_ET::ClearDisplay(void)
{
	_PutCommandLong(DISPLAY_COMAND_CODE_ClearDisplay, DISPLAY_DELAY_TIME_ms_clr_display);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ReturnHome
 * @brief		Return cursor on home 
 * @param[in]	void
 * @note		Method working OK
 * @return		void
 */
void LCD_016N002B_CFH_ET::ReturnHome(void)
{
	_PutCommandLong(DISPLAY_COMAND_CODE_ReturnHome_BaseCode, DISPLAY_DELAY_TIME_ms_ret_home);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCursorMovingDirectionL
 * 
 * @brief		Assign cursor moving direction to left

 * @note		This function is using predefined macros
 * 				Method working OK
 */
void LCD_016N002B_CFH_ET::SetCursorMovingDirectionL(void)
{	
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_EntryModee(LCD_ENTRY_MODE_ID_CURS_DIR_L, LCD_ENTRY_MODE_SH_DISP_SHIFT_OFF), 
		DISPLAY_DELAY_TIME_us_entry_mode);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCursorMovingDirectionR
 * 
 * @brief		Assign cursor moving direction to right

 * @note		This function is using predefined macros
 * 				Method working OK
 */
void LCD_016N002B_CFH_ET::SetCursorMovingDirectionR(void)
{
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_EntryModee(LCD_ENTRY_MODE_ID_CURS_DIR_R, LCD_ENTRY_MODE_SH_DISP_SHIFT_OFF),
		DISPLAY_DELAY_TIME_us_entry_mode);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetDisplayMovingDirectionL
 * 
 * @brief		Assign whole display moving direction to left
 * 
 * @note		This function is using predefined macros
 * 				Method working OK
 */
void LCD_016N002B_CFH_ET::SetDisplayMovingDirectionL(void)
{
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_EntryModee(LCD_ENTRY_MODE_ID_CURS_DIR_L, LCD_ENTRY_MODE_SH_DISP_SHIFT_ON),
		DISPLAY_DELAY_TIME_us_entry_mode);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetDisplayMovingDirectionR
 * 
 * @brief		Assign whole display moving direction to right
 * 
 * @note		This function is using predefined macros
 * 				Method working OK
 */
void LCD_016N002B_CFH_ET::SetDisplayMovingDirectionR(void)
{
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_EntryModee(LCD_ENTRY_MODE_ID_CURS_DIR_R, LCD_ENTRY_MODE_SH_DISP_SHIFT_ON),
		DISPLAY_DELAY_TIME_us_entry_mode);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Initialize
 * @brief		LCD display is initialize to default mode
 * 
 * @note		1. Wait more than 40ms after VDD rises to 4,5V
 * 				2. Function set: 
 * 				3. Function set: 
 * 				4. Display ON / OFF control
 * 				5. Clear display
 * 				6. Entry mode set 
 * 				7. Return home
 */
void LCD_016N002B_CFH_ET::Initialize_8bitInterface(void)
{
	// 1. Wait more than 40ms after VDD rises to 4,5V
	_delay_ms(DISPLAY_DELAY_TIME_ms_init);

	// 2. Function set: 
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_FunctionSet(
			LCD_FUNCTION_SET_DL_LINE_AMOUT_8,
			LCD_FUNCTION_SET_N_LINE_2,
			LCD_FUNCTION_SET_F_5X11_DOTS),
		DISPLAY_DELAY_TIME_us_functionSet);

	// 3. Function set: 
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_FunctionSet(
			LCD_FUNCTION_SET_DL_LINE_AMOUT_8,
			LCD_FUNCTION_SET_N_LINE_2,
			LCD_FUNCTION_SET_F_5X11_DOTS),
		DISPLAY_DELAY_TIME_us_functionSet);

	// 4. Display ON / OFF control
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_DisplayControl(
			LCD_DISPLAY_CONTROL_D_DISPLAY_ON,
			LCD_DISPLAY_CONTROL_C_CURSOR_ON,
			LCD_DISPLAY_CONTROL_B_CURSOR_BLINK_OFF),
		DISPLAY_DELAY_TIME_us_displ_mode);

	// 5. Clear display
	ClearDisplay();

	//6. Entry mode set 
	_PutCommandShort(DISPLAY_COMAND_CODE_FUN_EntryModee(
			LCD_ENTRY_MODE_ID_CURS_DIR_R,
			LCD_ENTRY_MODE_SH_DISP_SHIFT_OFF),
		DISPLAY_DELAY_TIME_us_entry_mode);

	// 7. Return home
	ReturnHome();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCurrsorToPosition
 * @brief		Cursor is placed to certain position
 * 
 * @param[in]	n Amount of uint8_ts to move 
 * @param[in]	line Line top or bottom, input of type displayLineOffset_enum
 * 
 * @note		To work correctly LCD need to be initialized in proper way
 */
#define _DISPLAY_LCD_POSITION_MAX_MASK 0x0FU
void LCD_016N002B_CFH_ET::SetCurrsorToPosition(uint8_t n_row, displayColLineNum_enum n_col)
{
	n_row = (n_row & _DISPLAY_LCD_POSITION_MAX_MASK);

	switch (n_col)
	{
	case DISPLAY_LINE_1:
		n_row = n_row | DISPLAY_LINE_TOP;
		_PutCommandShort(DISPLAY_COMAND_CODE_FUN_SetDDRAM_ADDR(n_row), DISPLAY_DELAY_TIME_us_setDDRAM);
		curstorPosition = n_row & 0x0F;
		break;

	case DISPLAY_LINE_2:
		n_row = n_row | DISPLAY_LINE_BOT;
		_PutCommandShort(DISPLAY_COMAND_CODE_FUN_SetDDRAM_ADDR(n_row), DISPLAY_DELAY_TIME_us_setDDRAM);
		curstorPosition = n_row & 0x0F;
		break;
	
	default:
		n_row = n_row | DISPLAY_LINE_BOT;
		_PutCommandShort(DISPLAY_COMAND_CODE_FUN_SetDDRAM_ADDR(n_row), DISPLAY_DELAY_TIME_us_setDDRAM);
		break;
	}
}
//====================================================================================================
#endif // _INC_LCD
//====================================================================================================
