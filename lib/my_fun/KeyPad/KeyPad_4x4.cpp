#include "KeyPad_4x4.h"
#ifdef _INC_KEYPAD_4x4

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		Constructor for Keypad4x4 class
 * @brief		void
 * @param[in]	dbAmount Debonce amount 
 * @note		void
 */
Keypad4x4::Keypad4x4(uint8_t dbAmount)
{ 	_DEBOUNCE_AMOUNT = dbAmount; 
	irq_n = 0x00;
	_colnum = 0xFF;}
//====================================================================================================

/*****************************************************************************************************
 * @name		Deconstructor for Keypad4x4 class
 * @brief		void
 * @note		void
 */
Keypad4x4::~Keypad4x4(void){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetOutputPort
 * 
 * @brief		Set output for each column in order to cheqe all column and rows
 * 				After each call _i is incremented
 * 
 * @param[in]	inPORTx Data from certain and valid PORT
 * 
 * @note		inPORTx is masked by valid mask data
 * 
 * @return		Ouput data uint8_t for certain PORTx 
 */
uint8_t Keypad4x4::SetOutputPort(uint8_t* pColumn)
{
	static uint8_t sColumn = COLUMN_4;
	switch (sColumn)
	{
	case COLUMN_1:
		sColumn = COLUMN_2;
		break;

	case COLUMN_2:
		sColumn = COLUMN_3;
		break;

	case COLUMN_3:
		sColumn = COLUMN_4;
		break;

	case COLUMN_4:
		sColumn = COLUMN_1;
		break;
		
	default:
		sColumn = COLUMN_1;
		break;
	}
	*pColumn = sColumn;

	return arrayPortOutNegative[sColumn];
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CalculateInputValueNeg
 * @brief		This method decode key from input port and pin
 * @param[in]	inPORT 	Input value from certain port that set outputs for keypad
 * @param[in]	inPIN 	Input velue from certain pin that get vales from keypad
 * @note		In case of no input zero is returned
 * @return		Decoded value of a key
 */
uint8_t Keypad4x4::DecodeKeyCode(uint8_t inPORT, uint8_t inPIN)
{
	uint8_t tROW, tCOL;

	inPIN = KEYPAD_CODE_PINx_MASK_F(inPIN);
	switch (inPIN)
	{
	case KEYPAD_CODE_PINx_02_N:	tROW = 0; break;
	case KEYPAD_CODE_PINx_03_N: tROW = 1; break;
	case KEYPAD_CODE_PINx_04_N: tROW = 2; break;
	case KEYPAD_CODE_PINx_05_N: tROW = 3; break;
	default: return KEYCODE_NOPRESS;
	}

	inPORT = KEYPAD_CODE_PORTx_MASK_F(inPORT);
	switch (inPORT)
	{
	case KEYPAD_CODE_PORTx_01_N: tCOL = 0; break;
	case KEYPAD_CODE_PORTx_02_N: tCOL = 1; break;
	case KEYPAD_CODE_PORTx_03_N: tCOL = 2; break;
	case KEYPAD_CODE_PORTx_04_N: tCOL = 3; break;
	default: return KEYCODE_NOPRESS;
	}

	return arrKeys2D[tROW][tCOL];
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PadDebounce
 * @brief		Debounce for keypad
 * @param[in]	pDebounce Pointer to debounce state machine
 * @param[in]	pCounter Pointer to counter for amount of debounce
 * @param[in]	inState Certain input value of decoded column
 * @note		void
 * @return		Current debounce state
 */
uint8_t Keypad4x4::PadDebounce(uint8_t* pDebounce, uint8_t* pCounter, uint8_t inState)
{	
	switch(*pDebounce) 
	{			
		// Initialization of button debounce state machine
		case KEYPAD_DEBOUNCE_x00_INIT:
			*pDebounce = KEYPAD_DEBOUNCE_x11_STABLE_OFF;
			*pCounter = 0x00;
			break;

		// Stan stabilny zero czekanie na stan wysoki
		case KEYPAD_DEBOUNCE_x11_STABLE_OFF:
			if(inState != KEYPAD_DEBOUNCE_STATE_NOPRESS)
			{	*pDebounce = KEYPAD_DEBOUNCE_x33_DB_OFFON;
				return KEYPAD_DEBOUNCE_x22_RISING_EDGE;}
			else{;}
			break;
			
		// Czekanie na ustabilizowanie sie stanu
		case KEYPAD_DEBOUNCE_x33_DB_OFFON:
			if(*pCounter < _DEBOUNCE_AMOUNT)
			{	*pCounter = *pCounter + 0x01;}
			else
			{	*pDebounce = KEYPAD_DEBOUNCE_x44_STABLE_ON;
				*pCounter = 0x00;}
			break;
	
		// Czekanie na zwolnienie klawicza stan stabilny
		case KEYPAD_DEBOUNCE_x44_STABLE_ON:
			if(inState == KEYPAD_DEBOUNCE_STATE_NOPRESS)
			{	*pDebounce = KEYPAD_DEBOUNCE_x55_FALLING_EDGE;
				return KEYPAD_DEBOUNCE_x55_FALLING_EDGE;}
			else{;}
			break;
			
		// Czekanie na ustabilizowanie sie stanu niskiego		
		case KEYPAD_DEBOUNCE_x66_DB_ONOFF:
			if(*pCounter < _DEBOUNCE_AMOUNT)
			{	*pCounter = *pCounter + 0x01;}
			else
			{	*pDebounce = KEYPAD_DEBOUNCE_x11_STABLE_OFF;
				*pCounter  = 0x00;}
			break;
		
		default:
			*pDebounce = KEYPAD_DEBOUNCE_x00_INIT;
	}

	return *pDebounce;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		KeypadStateEvaluation
 * @brief		For each column seperate debounce variable 
 * @param[in]	void
 * @note		void
 * @return		state of a pressed button 
 */
uint8_t Keypad4x4::KeypadStateEvaluation(void)
{
	static uint8_t sButtonState;
	
	switch (irq_n)
	{
	case KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT:
		irq_n = KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE;
		
		_PORTx = SetOutputPort(&_colnum);
		PORTC = _PORTx;
		break;

	case KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE:
		irq_n = KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON;

		_PINx = KEYPAD_CODE_PINx_MASK_F(PINB);
		switch (_colnum)
		{
		case COLUMN_1: // Keypad debounce for first column
			sButtonState = PadDebounce((uint8_t*)&(arrDebounce[COLUMN_1]), (uint8_t*)&(arrCounter[COLUMN_1]), _PINx);
			break;

		case COLUMN_2: // Keypad debounce for second column
			sButtonState = PadDebounce((uint8_t*)&(arrDebounce[COLUMN_2]), (uint8_t*)&(arrCounter[COLUMN_2]), _PINx);
			break;

		case COLUMN_3: // Keypad debounce for third column
			sButtonState = PadDebounce((uint8_t*)&(arrDebounce[COLUMN_3]), (uint8_t*)&(arrCounter[COLUMN_3]), _PINx);
			break;

		case COLUMN_4: // Keypad debounce for fourth column
			sButtonState = PadDebounce((uint8_t*)&(arrDebounce[COLUMN_4]), (uint8_t*)&(arrCounter[COLUMN_4]), _PINx);
			break;
		
		default:
			break;
		}
		break;

	case KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON:
		irq_n = KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT;

		switch (_colnum)
		{
		case COLUMN_1:
			if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
			{
				keyCode = DecodeKeyCode(_PORTx, _PINx);
				keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
				return KEYPAD_KEYPAD_STATE_PULS;
			}
			else{;}
			break;

		case COLUMN_2:
			if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
			{
				keyCode = DecodeKeyCode(_PORTx, _PINx);
				keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
				return KEYPAD_KEYPAD_STATE_PULS;
			}
			else{;}
			break;

		case COLUMN_3:
			if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
			{
				keyCode = DecodeKeyCode(_PORTx, _PINx);
				keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
				return KEYPAD_KEYPAD_STATE_PULS;
			}
			else{;}
			break;

		case COLUMN_4:
			if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
			{
				keyCode = DecodeKeyCode(_PORTx, _PINx);
				keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
				return KEYPAD_KEYPAD_STATE_PULS;
			}
			else{;}
			break;
		
		default:
			break;
		}
	
	default:
		irq_n = KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT;
		break;
	}

	return KEYCODE_NOPRESS;
}
uint8_t Keypad4x4::GetKeyCode(void)
{	return keyCode;}
//====================================================================================================
#endif // _INC_KEYPAD
//====================================================================================================