/*
 * InterruptInit.c
 *
 * Created: 13.12.2020 13:10:28
 *  Author: TAPZawadzki
 */ 
#include "Init_328p.h"
#ifdef _INC_INIT_328P
/*******************************************************************************************************************
 * 
*/

/*******************************************************************************************************************
 * @name 		InitPeryferia_m328p
 * @brief		Constructor for class InitPeryferia_m328p
 * @param[in]	void
 * @note		void
 * @return		void
*/
InitPeryferia_m328p::InitPeryferia_m328p(void){ _sei_set = false; }
//=================================================================================================================

/******************************************************************************************************************
 * @name 		~InitPeryferia_m328p
 * @brief		Deconstructor for class InitPeryferia_m328p
 * @param[in]	void
 * @note		void
 * @return		void
*/
InitPeryferia_m328p::~InitPeryferia_m328p(){;}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		PortsInit
 * @brief		Initialize demand peryferia for LCD and Keypad peryferial
 * @param[in]	void
 * @note		void
 * @return		void
*/
void InitPeryferia_m328p::DataDirectionsResistrsInit(void)
{
	// Last connfiguration for LCD and keypad
	// Ustawianie bit�w					  7654 3210
	//DDRB = 0x0F; //B0 - B3 jako wyjscia  0b0000 1111
	//DDRC = 0x0F; //C0 - C3 jako wyjscia  0b0000 1111
	//DDRD = 0xFF; //D0 - D7 jako wyjscia  0b1111 1111
		
	//PORTB =  PORTB | 0x08; // ustawienie pinu w stan wysoki

	// New connfiguration for LCD and keypad
	// Ustawianie kierunku dla "Data Direction Register D,C,B"
	// Szczególy konfiguracji w pliku makr "Init.h
	DDRD = CONFIG_PORTD; //D0 - D7 jako wyjscia  0b1111 1111
	DDRC = CONFIG_PORTC; //C0 - C3 jako wyjscia  0b0000 1111
	DDRB = CONFIG_PORTB; //B0 - B3 jako wyjscia  0b0011 1100
}
//==================================================================================================================

/******************************************************************************************************************
 * @name 		Timer1Init_TCCR1A
 * @brief		Initialization register TCCR1A for 16bit Timer interrupt
 * @param[in]	void
 * @note		This method change regarding to demanding comfiguration
 * @return		void
*/
void InitPeryferia_m328p::Timer1Init_TCCR1A(void)
{// Initialy nothing is set or reset
	uint8_t temp_reset_TCCR1A 	= 0xFF;
	uint8_t temp_set_TCCR1A 	= 0x00;

	//1. Initialization: Compare Output Mode
	temp_reset_TCCR1A &= INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxA;
	temp_reset_TCCR1A &= INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxB;

	// Demanding bits are reset, Normal mode is selected

	// Asign configuration to register 
	TCCR1A &= temp_reset_TCCR1A;
	//TCCR1A |= temp_set_TCCR1A;
}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		Timer1Init_TCCR1B
 * @brief		Initialization register TCCR1B for 16bit Timer interrupt
 * @param[in]	void
 * @note		This method change regarding to demanding comfiguration
 * @return		void
*/
void InitPeryferia_m328p::Timer1Init_TCCR1B(void)
{// Initialy nothing is set or reset
	uint8_t temp_reset_TCCR1B 	= 0xFF;
	uint8_t temp_set_TCCR1B 	= 0x00;

	// 1. Configuration of a Input Capture Noise Canceler
	temp_reset_TCCR1B &= INIT_TIMERx_TCCRxB_7_ICNC1_F;
	// 2. Configuration of a Input Capture Edge Select
	temp_reset_TCCR1B &= INIT_TIMERx_TCCRxB_6_ICES1_F;

	// 3. Configure prescaler or external signal source
	temp_reset_TCCR1B &= INIT_TIMERx_TCCRxB_MASK_F_CLK_1024;
	temp_set_TCCR1B |= INIT_TIMERx_TCCRxB_MASK_T_CLK_1024;

	// Asign configuration to register 
	TCCR1B &= temp_reset_TCCR1B;
	TCCR1B |= temp_set_TCCR1B;
}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		Timer2Init_TCCR2A		TIMER2
 * @brief		Initialization register TCCR2A for 16bit Timer interrupt
 * @param[in]	void
 * @note		This method change regarding to demanding comfiguration
 * @return		void
*/
void InitPeryferia_m328p::Timer2Init_TCCR2A(void)
{// Initialy nothing is set or reset
	uint8_t temp_reset_TCCR2A 	= 0xFF;
	uint8_t temp_set_TCCR2A 	= 0x00;

	//1. Initialization: Compare Output Mode
	temp_reset_TCCR2A &= INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxA;
	temp_reset_TCCR2A &= INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxB;

	// Demanding bits are reset, Normal mode is selected

	// Asign configuration to register 
	TCCR2A &= temp_reset_TCCR2A;
	//TCCR1A |= temp_set_TCCR2A;
}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		Timer2Init_TCCR1B		TIMER2
 * @brief		Initialization register TCCR2B for 8bit Timer interrupt
 * @param[in]	void
 * @note		This method change regarding to demanding comfiguration
 * @return		void
*/
void InitPeryferia_m328p::Timer2Init_TCCR2B(void)
{// Initialy nothing is set or reset
	uint8_t temp_reset_TCCR2B 	= 0xFF;
	uint8_t temp_set_TCCR2B 	= 0x00;

	// 1. Configuration of a Input Capture Noise Canceler
	temp_reset_TCCR2B &= INIT_TIMERx_TCCRxB_7_ICNC1_F;
	// 2. Configuration of a Input Capture Edge Select
	temp_reset_TCCR2B &= INIT_TIMERx_TCCRxB_6_ICES1_F;

	// 3. Configure prescaler or external signal source
	temp_reset_TCCR2B &= INIT_TIMERx_TCCRxB_MASK_F_CLK_1024;
	temp_set_TCCR2B |= INIT_TIMERx_TCCRxB_MASK_T_CLK_1024;

	// Asign configuration to register 
	TCCR2B &= temp_reset_TCCR2B;
	TCCR2B |= temp_set_TCCR2B;
}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		Timer2Init_WaveformGeneration	TIMER2
 * @brief		Initialization: Waveform Generation Mode Bit Description
 * @param[in]	void
 * @note		This method change regarding to demanding comfiguration
 * @return		void
*/
void InitPeryferia_m328p::Timer2Init_WaveformGeneration(void)
{
	// Initialy nothing is set or reset
	uint8_t temp_reset_TCCR2A 	= BITMASK_FULL;;
	uint8_t temp_set_TCCR2A 	= BITMASK_NULL;

	uint8_t temp_reset_TCCR2B 	= BITMASK_FULL;
	uint8_t temp_set_TCCR2B 	= BITMASK_NULL;


	// Asign configuration to register
	TCCR2A &= temp_reset_TCCR2A;
	TCCR2A |= temp_set_TCCR2A;

	TCCR2B &= temp_reset_TCCR2B;
	TCCR2B |= temp_set_TCCR2B;
}

/******************************************************************************************************************
 * @name 		Timer1Init
 * @brief		Initialization for Timer interrupt
 * @param[in]	void
 * @note		void
 * @return		void
*/
void InitPeryferia_m328p::Timer1Init(void)
{
	// Configuration of timers interrupts
	TCCR1A = TCCR1A & 0x0F; // TC1 Control Register A
	TIMSK1 = TIMSK1 | 0x01;

	if(_sei_set == false) 
	{
		sei();
		_sei_set = true;
	}
	TCCR1B = TCCR1B | 0x04;
}
//=================================================================================================================

/******************************************************************************************************************
 * @name 		Timer2Init
 * @brief		Initialization for Timer interrupt
 * @param[in]	void
 * @note		void
 * @return		void
*/
void InitPeryferia_m328p::Timer2Init(void)
{
	// Configuration of timers interrupts
	TCCR2A = TCCR2A & 0x0F;
	TIMSK2 = TIMSK2 | 0x01;

	if(_sei_set == false) 
	{
		sei();
		_sei_set = true;
	}
	TCCR2B = TCCR2B | 0x04;
}
//=================================================================================================================
#endif // _INC_INIT