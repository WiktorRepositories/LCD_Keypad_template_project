/*
 * LCD_application.h
 *
 * Created: 05.05.2024 
 *  Author: Wiki
 */ 
#include "LCD_application.h"
#ifdef _INC_LCD_APPLICATION

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @brief		Constructor for class LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @param[in]	row_n Amount of rows
 * @param[in]   col_n Amount od columns
 * @note		Chldren class initialization is taken
 */
LCD_application::LCD_application(uint8_t row_n, uint8_t col_n): 
	LCD_DataControl(row_n, col_n), 
	LCD_016N002B_CFH_ET(row_n, col_n),
    row_n(row_n), col_n(col_n)
{;}
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @brief		Deconstructor for class LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @param[in]	void
 * @note		In this situation is empty
 */
LCD_application::~LCD_application(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		InitializeDevice: LCD_016N002B_CFH_ET.Initialize_8bitInterface()
 * @brief		Thid method use inheritanced method from device class
 * @param[in]	void
 * @note		Method to call is Initialize_8bitInterface()
 */
void LCD_application::InitializeDevice(void)
{
    Initialize_8bitInterface();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ClearDisplayData
 * @brief		LCD screen data is cleared
 * @param[in]	void
 * @note		Thid method clear virtual data and LCD data 
 */
void LCD_application::ClearDisplayData(void)
{
	LCD_DataControl::ClearData();
	LCD_016N002B_CFH_ET::ClearDisplay();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ReturnCursorHome
 * @brief		Cursor is moved to home position 0,0
 * @param[in]	void
 * @note		Thid method move cursor to home in virtual data and LCD data 
 */
void LCD_application::ReturnCursorHome(void)
{
	LCD_DataControl::ReturnHome(); 
	LCD_016N002B_CFH_ET::ReturnHome(); 
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutChar
 * @brief		Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Private method
 */
inline void LCD_application::_PutChar(char c, uint8_t n_row, uint8_t n_col)
{
	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Send data for LCD display.
	LCD_016N002B_CFH_ET::PutData(c);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutChar
 * @brief		Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Private method
 */
inline void LCD_application::_PutChar(const char *c, uint8_t n_row, uint8_t n_col)
{
	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Send data for LCD display.
	LCD_016N002B_CFH_ET::PutData(*c);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutCharOther
 * @brief		If character is diffrent that arleady printed then Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Private method
 */
inline void LCD_application::_PutCharOther(char c, uint8_t n_row, uint8_t n_col)
{
	;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutCharOther
 * @brief		If character is diffrent that arleady printed then Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Private method
 */
inline void LCD_application::_PutCharOther(const char *c, uint8_t n_row, uint8_t n_col)
{
	;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PrintArrofChars
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	Pointer char array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Print all string characters string
 */
inline void LCD_application::_PrintArrofChars(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, tByte;

	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Cheque posible characters amount. And asign lenght for loop.
	strLen = LCD_DataControl::PrintStr(arrString, strLen);

	// 3. Send data for LCD display.
	for(i=0; i<strLen; i++)
	{
		tByte = (uint8_t)arrString[i];
		if(tByte != '\0')
			LCD_016N002B_CFH_ET::PutData(tByte);
		else{ break;}
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PrintArrofChars
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	Constant char array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Print all string characters string
 */
inline void LCD_application::_PrintArrofChars(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, tByte;

	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Cheque posible characters amount. And asign lenght for loop.
	strLen = LCD_DataControl::PrintStr(arrString, strLen);

	// 3. Send data for LCD display.
	for(i=0; i<strLen; i++)
	{
		tByte = (uint8_t)arrString[i];
		if(tByte != '\0')
			LCD_016N002B_CFH_ET::PutData(tByte);
		else{ break;}
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PrintArrofCharsOther
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	Pointer char array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Print string with only changes part of a string
 */
inline void LCD_application::_PrintArrofCharsOther(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, offset;
	char tarrstr[16];

	// 1. Load data from buffer
	LCD_DataControl::GetString(tarrstr, n_row, n_col, strLen);

	// 2. Compare data 
	offset = LCD_DataControl::CompareStr(arrString, tarrstr, strLen);
	n_row = n_row + offset;
	strLen = strLen - offset;

	// 3. Asssing str after first change
	for(i=0; i<strLen; i++)
	{
		tarrstr[i] = arrString[offset + i];
	}

	// 4. Print data after optimalization
	_PrintArrofChars(tarrstr, strLen, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PrintArrofCharsOther
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	Pointer char array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Printed string is optimalized
 */
inline void LCD_application::_PrintArrofCharsOther(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, firstChange;
	char tarrstr[16];

	// 1. Load data from buffer
	strLen = LCD_DataControl::GetString(tarrstr, n_row, n_col, strLen);

	// 2. Compare data 
	firstChange = LCD_DataControl::CompareStr(arrString, tarrstr, strLen);
	n_row = n_row + firstChange;

	// 3. Asssing str after first change
	strLen = strLen - firstChange;
	for(i=0; i<strLen; i++)
	{
		tarrstr[i] = arrString[firstChange + i];
	}

	// 4. Print data after optimalization
	_PrintArrofChars(tarrstr, strLen, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutChar
 * @brief		Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Public method
 */
inline void LCD_application::PutChar(char c, uint8_t n_row, uint8_t n_col) { _PutChar(c, n_row, n_col); }
//====================================================================================================

/*****************************************************************************************************
 * @name		PutChar
 * @brief		Send one char to the LCD screen
 * @param[in]	c  Character to send
 * @param[in]	n_row LCD row position for character 
 * @param[in]	n_col LCD column position for character 
 * @note		Public method
 */
inline void LCD_application::PutChar(const char *c, uint8_t n_row, uint8_t n_col) { _PutChar(c, n_row, n_col); }
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintChar
 * @brief		Data is saved for latter display execute
 * @param[in]	data of type uint8_t
 * @note		Prepare data for LCD to print
 */
void LCD_application::Order_PrintChar(uint8_t data)
{
    if(_display_data_order_active == false)
    {
        _data_from_keypad_IRQ = data;
        _display_data_order_active = true;
    }
    else{;}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Public method
 */
void LCD_application::PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{	_PrintArrofChars(arrString, strLen, n_row, n_col); }
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Public method
 */
void LCD_application::PrintStr(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col) 
{	_PrintArrofChars(arrString, strLen, n_row, n_col);}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Public method
 */
void LCD_application::PrintStrOther(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{	_PrintArrofCharsOther(arrString, strLen, n_row, n_col); }
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of chars on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		Public method
 */
void LCD_application::PrintStrOther(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col) 
{	_PrintArrofCharsOther(arrString, strLen, n_row, n_col); }
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintStr
 * @brief		String data is saved for latter data display
 * @param[in]	arrString Constant array of chars for LCD display
 * @param[in]	strLen Lenght of that array of chars
 * @param[in]	n_row Row where start to put data 
 * @param[in]	n_col Column where start to put data
 * @note		This method is usefull in IRQ str diplsy order
 */
void LCD_application::Order_PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i=0;

	if(_display_data_order_active == false)	
	{ 	
		if(strLen > 16) {strLen = 16;}
		else{;}

		while(i < strLen)
		{	_arrBuffer[i] = arrString[i];
			i++;}

		_strLen = strLen;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintStr
 * @brief		String data is saved for latter data display 
 * @param[in]	arrString Pointer to array of chars for LCD display
 * @param[in]	strLen Lenght of that array of chars
 * @param[in]	n_row Row where start to put data 
 * @param[in]	n_col Column where start to put data
 * @note		This method is usefull in IRQ str diplsy order
 */
void LCD_application::Order_PrintStr(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i=0;

	if(_display_data_order_active == false)	
	{ 	
		if(strLen > 16) {strLen = 16;}
		else{;}

		while(i<strLen)
		{	_arrBuffer[i] = arrString[i];
			i++;}

		_strLen = strLen;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Execute_PrintStr
 * @brief		Ordered string data is executed
 * @param[in]	void
 * @note		When data order is in IRQ and LCD display in main aplication
 */
void LCD_application::Execute_PrintStr(void)
{
	if(_display_data_order_active == true)	
	{ 	
		PrintStr(_arrBuffer, _strLen, _n_row, _n_col);
		_strLen = 0;

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint8_t in certain place
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 */
void LCD_application::PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars[TYPE_DEC_uin8_t];
	_Convert.Uint_to_str_dec(arr_chars, number);
	_PrintArrofChars(arr_chars, TYPE_DEC_uin8_t-1, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint16_t in certain place
 * @param[in]	number Number to put on LCD display, type uint16_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 */
void LCD_application::PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars[TYPE_DEC_uint16_t];
	_Convert.Uint_to_str_dec(arr_chars, number);
	_PrintArrofChars(arr_chars, TYPE_DEC_uint16_t-1, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint8_t in certain place
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 */
void LCD_application::PrintInt_Format(uint8_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uin8_t]; 
	char arr_chars_DST[TYPE_DEC_uin8_t];

	_Convert.Uint_to_str_dec(arr_chars_SRC, number);
	_Convert.StrFormatToRight(arr_chars_SRC, TYPE_DEC_uin8_t-1, arr_chars_DST, TYPE_DEC_uin8_t-1, '0');
	_PrintArrofChars(arr_chars_DST, TYPE_DEC_uin8_t, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint16_t in certain place
 * @param[in]	number Number to put on LCD display, type uint16_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 */
void LCD_application::PrintInt_Format(uint16_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uint16_t];
	char arr_chars_DST[TYPE_DEC_uint16_t];

	_Convert.Uint_to_str_dec(arr_chars_SRC, number);
	_Convert.StrFormatToRight(arr_chars_SRC, TYPE_DEC_uint16_t-1, arr_chars_DST, TYPE_DEC_uint16_t-1, '0');
	_PrintArrofChars(arr_chars_DST, TYPE_DEC_uint16_t, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintInt
 * @brief		Data is prepared for print, int is converted to string format
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		This method is usefull in IRQ str display order
 */
void LCD_application::Order_PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uin8_t];
	uint8_t i;

	if(_display_data_order_active == false)	
	{	_Convert.Uint_to_str_dec((char*)arr_chars_SRC, number);

		i = 0;
		while(i < TYPE_DEC_uin8_t)
		{	_arrBuffer[i] = arr_chars_SRC[i];
			i++;}

		_strLen = TYPE_DEC_uin8_t;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintInt
 * @brief		Data is prepared for print, int is converted to string format
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		This method is usefull in IRQ str display order
 */
void LCD_application::Order_PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uint16_t];
	uint8_t i;

	if(_display_data_order_active == false)	
	{ 	_Convert.Uint_to_str_dec((char*)arr_chars_SRC, number);

		i = 0;
		while(i < TYPE_DEC_uint16_t)
		{	_arrBuffer[i] = arr_chars_SRC[i];
			i++;}

		_strLen = TYPE_DEC_uint16_t;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Execute_PrintStr
 * @brief		Converted number to string is executed
 * @param[in]	void
 * @note		This method is same like Execute_PrintStr
 */
void LCD_application::Execute_PrintInt(void)
{
	if(_display_data_order_active == true)	
	{ 	
		_PrintArrofChars(_arrBuffer, _strLen, _n_row, _n_col);
		_strLen = 0;

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTime
 * @brief		Print time data format data_time::time_t
 * @param[in]	pTime 	Poiner to strucuture data_time::time_t*
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Public mthod
 */
void LCD_application::PrintTime(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	_Convert.TimeToStr(pTime, arrChar1, ':');
	_PrintArrofChars(arrChar1, data_time_TIME_LEN, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTime
 * @brief		Print time data format of uint8_t hour, uint8_t minute, uint8_t second
 * @param[in]	hour 	Valut of a hour
 * @param[in]	minute 	Valur of a minute 
 * @param[in]	second 	Value of a second
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Public method
 */
void LCD_application::PrintTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	_Convert.TimeToStr(hour, minute, second, arrChar1, ':');
	_PrintArrofChars(arrChar1, data_time_TIME_LEN, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTimeOther
 * @brief		Print time data format data_time::time_t
 * @param[in]	pTime 	Poiner to strucuture data_time::time_t*
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Only changed data is printed
 */
void LCD_application::PrintTimeOther(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	_Convert.TimeToStr(pTime, arrChar1, ':');
	_PrintArrofCharsOther(arrChar1, data_time_TIME_LEN, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTimeOther
 * @brief		Print time data format of uint8_t hour, uint8_t minute, uint8_t second
 * @param[in]	hour 	Valut of a hour
 * @param[in]	minute 	Valur of a minute 
 * @param[in]	second 	Value of a second
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Only changed data is printed
 */
void LCD_application::PrintTimeOther(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	_Convert.TimeToStr(hour, minute, second, arrChar1, ':');
	_PrintArrofCharsOther(arrChar1, data_time_TIME_LEN, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTime
 * @brief		Print time data format data_time::time_t
 * @param[in]	pTime 	Poiner to strucuture data_time::time_t*
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Prepare data for LCD to print
 */
void LCD_application::Order_PrintTime(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	if(_display_data_order_active == false)	
	{ 	
		_Convert.TimeToStr(pTime, arrChar1, ':');

		_strLen = data_time_TIME_LEN;
		_n_row = n_row;
		_n_col = n_col;

		_display_data_order_active = true;
	}
	else	
	{ 	return; }
} 
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintTime
 * @brief		Print time data format of uint8_t hour, uint8_t minute, uint8_t second
 * @param[in]	hour 	Valut of a hour
 * @param[in]	minute 	Valur of a minute 
 * @param[in]	second 	Value of a second
 * @param[in]	n_row	Row place to display
 * @param[in]	n_col	Column place to display
 * @note		Prepare data for LCD to print
 */
void LCD_application::Order_PrintTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col)
{
	char arrChar1[data_time_TIME_LEN];
	if(_display_data_order_active == false)	
	{ 	
		_Convert.TimeToStr(hour, minute, second, arrChar1, ':');

		_strLen = data_time_TIME_LEN;
		_n_row = n_row;
		_n_col = n_col;

		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

void LCD_application::Execute_PrintTime(void)
{
	if(_display_data_order_active == true)	
	{ 	
		_PrintArrofCharsOther(_arrBuffer, _strLen, _n_row, _n_col);
		_strLen = 0;

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

//====================================================================================================
#endif // _INC_LCD_APPLICATION
//====================================================================================================