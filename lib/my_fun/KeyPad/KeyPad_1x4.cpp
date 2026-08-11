#include "KeyPad_1x4.h"
#ifdef _INC_KEYPAD_1x4

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		Constructor for Keypad1x4 class
 * @brief		void
 * @param[in]	dbAmount Debonce amount 
 * @note		void
 */
KeyPad1x4::KeyPad1x4(uint8_t dbAmount)
{ 	_DEBOUNCE_AMOUNT = dbAmount; 
	irq_n = 0x00;
	_colnum = 0xFF;}
//====================================================================================================
/*****************************************************************************************************
 * @name		Deconstructor for Keypad1x4 class
 * @brief		void
 * @note		void
 */
KeyPad1x4::~KeyPad1x4(void){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		DecodeKeyCode
 * @brief		All buttons are connected to 5V
 * 				When press input port signal 0V
 * 
 * @param[in]	inPIN Input pin value
 * 
 * @note		Simple input 4 buttons
 * @return		void
 */
uint8_t KeyPad1x4::DecodeKeyCode(uint8_t inPIN)
{
	uint8_t tCOL;

	inPIN = KEYPAD_CODE_PINx_MASK_F(inPIN);
	switch (inPIN)
	{
	case KEYPAD_CODE_PINx_02_N:	tCOL = 0; break;
	case KEYPAD_CODE_PINx_03_N: tCOL = 1; break;
	case KEYPAD_CODE_PINx_04_N: tCOL = 2; break;
	case KEYPAD_CODE_PINx_05_N: tCOL = 3; break;
	default: return KEYCODE_NOPRESS;
	}

	return arrKeys2D[0][tCOL];
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
uint8_t KeyPad1x4::PadDebounce(uint8_t* pDebounce, uint8_t* pCounter, uint8_t inState)
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
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		state of a pressed button 
 */
uint8_t KeyPad1x4::KeypadStateEvaluation(void)
{
	static uint8_t sButtonState;
	
	switch (irq_n)
	{
	case KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE:
		irq_n = KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON;

		_PINx = KEYPAD_CODE_PINx_MASK_F(PINB);
		sButtonState = PadDebounce((uint8_t*)&(arrDebounce[0]), (uint8_t*)&(arrCounter[0]), _PINx);
		break;

	case KEYPAD_IRQ_OPERATION_x22_DECODE_BUTTON:
		irq_n = KEYPAD_IRQ_OPERATION_x00_SET_OUTPUT;

		if(sButtonState == KEYPAD_DEBOUNCE_x22_RISING_EDGE)
		{
			keyCode = DecodeKeyCode(_PINx);
			keyState = KEYPAD_DEBOUNCE_x22_RISING_EDGE;
			return KEYPAD_KEYPAD_STATE_PULS;
		}
		else{;}
		break;
		
	default:
		irq_n = KEYPAD_IRQ_OPERATION_x11_INPUT_DEBOUNCE;
		break;
	}

	return KEYCODE_NOPRESS;
}
uint8_t KeyPad1x4::GetKeyCode(void)
{	return keyCode;}
//====================================================================================================

#endif // _INC_KEYPAD
//====================================================================================================