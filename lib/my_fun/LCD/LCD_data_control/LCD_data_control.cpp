/*
 * LCD_data_control.h
 *
 * Created: 04.05.2024 
 *  Author: Wiki
 */ 
#include "LCD_data_control.h"
#ifdef _INC_LCD_DATA_CONTROL
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
 * @name		LCD_DataControl
 * @brief		Constructor for class LCD_DataControl
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_DataControl::LCD_DataControl(uint8_t row_n, uint8_t col_n): _idx_row(0), _idx_col(0)
{	ClearData();}
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_DataControl
 * @brief		Deconstructor for class LCD_DataControl
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_DataControl::~LCD_DataControl(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutDataBuffer
 * @brief		void
 * @param[in]	data Input data 
 * @note		void
 * @return		Status if data was added
 */
 uint8_t LCD_DataControl::_PutDataBuffer(uint8_t data)
 {
	if(_idx_row < DISPLAY_BUFFER_MAX_ROW_AMOUT) 
	{
		_arrDisplayData[_idx_col][_idx_row] = data;
		_idx_row++;

		return TRUE;
	}
	else
	{
		if(_idx_col == DISPLAY_BUFFER_LINE_1)
		{
			_idx_row = 0;
			_idx_col = DISPLAY_BUFFER_LINE_2;
			_PutDataBuffer(data);
		} 
		else{;}
	}
	return FALSE; 
 }
//====================================================================================================

/*****************************************************************************************************
 * @name		ClearData
 * @brief		Clear LCD data buffer 
 * @param[in]	void
 * @note		void
 */
void LCD_DataControl::ClearData(void)
{
	uint8_t i, j;

	_idx_row = 0;
	_idx_col = 0;

	for(j=0; j<DISPLAY_BUFFER_MAX_COL_AMOUT; j++)
	{	for(i=0; i<DISPLAY_BUFFER_MAX_ROW_AMOUT; i++)
		{	_arrDisplayData[j][i] = 0x00; }}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ReturnHome
 * @brief		Return cursor to start position
 * @param[in]	void
 * @note		void
 */
void LCD_DataControl::ReturnHome(void)
{
	_idx_row = 0;
	_idx_col = 0;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		AmountCharsToBegin
 * @brief		Gets amout of characters from current cursor place to begin of LCD
 * @param[in]	void
 * @note		
 * @return		Amount of characters from current place to begin of LCD
 */
uint8_t LCD_DataControl::AmountCharsToBegin(void)
{
	return (_idx_row + 1);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		AmountCharsToEnd
 * @brief		Gets amout of characters from current cursor place end of LCD
 * @param[in]	void
 * @note		
 * @return		Amount of characters from current place to end of LCD
 */
uint8_t LCD_DataControl::AmountCharsToEnd(void)
{
	return (DISPLAY_BUFFER_MAX_ROW_AMOUT - _idx_row);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCurrsorToPosition
 * @brief		Cursor is placed to certain position
 * 
 * @param[in]	row_n Certain row is set 
 * @param[in]	col_n Certain col is set
 * 
 * @note		Data is set when input atays in range
 * 
 * @return		Bool value, true when column or row value is changed
 */
bool LCD_DataControl::SetCurrsorToPosition(uint8_t* p_nRow, uint8_t* p_nCol)
{	bool tBool = false;
	if(*p_nCol < DISPLAY_BUFFER_MAX_COL_AMOUT)
	{	_idx_col = *p_nCol; }
	else
	{	*p_nCol = _idx_col; tBool |= true; }

	if(*p_nRow < DISPLAY_BUFFER_MAX_ROW_AMOUT)
	{	_idx_row = *p_nRow; }
	else
	{	*p_nRow = _idx_row; tBool |= true; }

	return tBool;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCurrsorToPosition
 * @brief		Cursor is placed to certain position
 * 
 * @param[in]	row_n Certain row is set 
 * @param[in]	col_n Certain col is set
 * 
 * @note		Data is set when input atays in range
 * 
 * @return		Current row cursor value
 */
uint8_t LCD_DataControl::SetCurrsorToPosition(uint8_t nRow, uint8_t nCol)
{
	if(nCol < DISPLAY_BUFFER_MAX_COL_AMOUT)
	{	_idx_col = nCol; }
	else
	{	nCol = _idx_col;}

	if(nRow < DISPLAY_BUFFER_MAX_ROW_AMOUT)
	{	_idx_row = nRow; }
	else
	{	nRow = _idx_row;}

	return nRow;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutOneChar
 * @brief		void
 * @param[in]	data Input data to insert into data array
 * @note		void
 * @return		void
 */
bool LCD_DataControl::PutOneChar(uint8_t data)
{
	uint8_t iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) {return false;}
	else{;}

	_arrDisplayData[_idx_col][_idx_row] = data;
	_idx_row++;

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return true;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		GetOneChar
 * @brief		Write char in place passed by values.
 * @param[in]	data Input data to insert into data array
 * @note		void
 * @return		Error code that contain error bit set of type lcdDataError_en
 */
ERROR_CODE LCD_DataControl::GetChar(uint8_t n_row, uint8_t n_col, char* pchar)
{
	uint8_t error = LCD_DATA_OK;
	if(n_row > DISPLAY_BUFFER_CURRSOR_IDX_END) 
	{
		n_row = DISPLAY_BUFFER_CURRSOR_IDX_END;
		error = error | LCD_DATA_ER_cursor;
	}
	else{;}

	if(n_col > DISPLAY_BUFFER_LINE_2)
	{
		n_col = DISPLAY_BUFFER_LINE_2;
		error = error | LCD_DATA_ER_line;
	}
	else{;}

	*pchar = _arrDisplayData[n_row][n_col];

	return error;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Print array of characters on LCD screen
 * 
 * @param[in]	pStr Constatnt array of pointers to pint on LCD screen
 * @param[in]	strLen Lenght of a constant array of characters
 * 
 * @note		Amount of characters that will not be printed return as uint8_t
 * 				To print on certain place method SetCurrsorToPosition need to be used
 * @return		Amout of printed characters
 */
uint8_t LCD_DataControl::PrintStr(const char pStr[], uint8_t strLen)
{
	uint8_t i, iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		_arrDisplayData[_idx_col][_idx_row] = pStr[i];
		_idx_row++;
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Print array of characters on LCD screen
 * 
 * @param[in]	pStr Constatnt array of pointers to pint on LCD screen
 * @param[in]	strLen Lenght of a constant array of characters
 * 
 * @note		Amount of characters that will not be printed return as uint8_t
 * 				To print on certain place method SetCurrsorToPosition need to be used
 * @return		Amout of printed characters
 */
uint8_t LCD_DataControl::PrintStr(char pStr[], uint8_t strLen)
{
	uint8_t i, iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		_arrDisplayData[_idx_col][_idx_row] = pStr[i];
		_idx_row++;
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		DeletStr
 * @brief		Print array of characters on LCD screen
 * 
 * @param[in]	pStr Constatnt array of pointers to pint on LCD screen
 * @param[in]	strLen Lenght of a constant array of characters
 * 
 * @note		Amount of characters that will not be printed return as uint8_t
 * 				To print on certain place method SetCurrsorToPosition need to be used
 * @return		Amout of printed characters
 */
uint8_t LCD_DataControl::DeletStr(const char pStr[], uint8_t strLen)
{
	uint8_t i, iMAX;

	iMAX = AmountCharsToBegin();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		_arrDisplayData[_idx_col][_idx_row] = pStr[i];
		_idx_row--;
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		GetStr 
 * @brief		Load string from data buffer
 * @param[in]	pStr[] Pointer to destination string array, dublet data will be removed
 * @param[in]	strLen Lenght of source string
 * @note		Removes characted if the same exist in LCD data
 * 				Optimalization to not print already printed char
 * @return		void
 */
uint8_t LCD_DataControl::GetString(char pStr[], uint8_t n_row, uint8_t n_col, uint8_t strLen)
 {
	uint8_t i, irow, iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		irow = _idx_row + i;
		pStr[i] = _arrDisplayData[_idx_col][irow];
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
 }
//====================================================================================================

/*****************************************************************************************************
 * @name		CompareStr
 * @brief		Compare two strings 
 * @param[in]	pStr1 String array first 
 * @param[in]	pStr2 String array second
 * @param[in]	strLen String lenght 
 * @note		Return value is a first diferences 
 * @return		First changes in two string comparason
 */
uint8_t LCD_DataControl::CompareStr(char pStr1[], char pStr2[], uint8_t strLen)
{
	uint8_t i;
	for(i=0; i<strLen; i++)
	{
		if(pStr1[i] != pStr2[i])	
			return i;
		else{;}
	}

	return 0;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CompareStr
 * @brief		Compare two strings 
 * @param[in]	pStr1 String array first 
 * @param[in]	pStr2 String array second
 * @param[in]	strLen String lenght 
 * @note		Return value is a first diferences 
 * @return		First changes in two string comparason
 */
uint8_t LCD_DataControl::CompareStr(const char pStr1[], char pStr2[], uint8_t strLen)
{
	uint8_t i;
	for(i=0; i<strLen; i++)
	{
		if(pStr1[i] != pStr2[i])	
			return i;
		else{;}
	}
	return strLen;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CompareStr
 * @brief		Compare two strings
 * @param[in]	pStr1 String array first 
 * @param[in]	pStr2 String array second
 * @param[in]	pCmp Bool array that will contain compare of both strings
 * @param[in]	strLen String lenght 
 * @note		Same characters in boll array is set as true
 * @return		void
 */
void LCD_DataControl::CompareStr(char pStr1[], char pStr2[], bool pCmp[], uint8_t strLen)
{
	uint8_t i;
	for(i=0; i<strLen; i++)
	{
		if(pStr1[i] == pStr2[i])
			pCmp[i] = true; 
		else
			pCmp[i] = false; 
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CompareStr
 * @brief		Compare two strings
 * @param[in]	pStr1 String array first 
 * @param[in]	pStr2 String array second
 * @param[in]	pCmp Bool array that will contain compare of both strings
 * @param[in]	strLen String lenght 
 * @note		Same characters in boll array is set as true
 * @return		void
 */
void LCD_DataControl::CompareStr(const char pStr1[], char pStr2[], bool pCmp[], uint8_t strLen)
{
	uint8_t i;
	if(strLen > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	strLen = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		if(pStr1[i] == pStr2[i])
		{	pCmp[i] = true; }
		else
		{	pCmp[i] = false; }
	}
}
//====================================================================================================
#endif // _INC_LCD_DATA_CONTROL
//====================================================================================================