/*
 * Init_328p.h
 *
 * Created: 13.12.2020 13:08:33
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_INIT_328P
/**********************************************************
 * 
*/
#ifndef INIT_H_
#define INIT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Global_macros/bit_mask_macros.h"

//========================================================================================================================================================
// PORTD masks
#define MY_LCD_CONFIG_OUT_PORT_D7_D0    (BITMASK_Tx7 | BITMASK_Tx6 | BITMASK_Tx5 | BITMASK_Tx4 | BITMASK_Tx3 | BITMASK_Tx2 | BITMASK_Tx1 | BITMASK_Tx0)
#define CONFIG_PORTD                    (BITMASK_NULL | MY_LCD_CONFIG_OUT_PORT_D7_D0) // Rest as input
//========================================================================================================================================================

//========================================================================================================================================================
// PORTC masks
#define MY_NOTUSED_CONFIG_PORT_C5_C4    (BITMASK_Fx5 & BITMASK_Fx4)
#define MY_KEYPAD_CONFIG_OUT_PORT_C3_C0 (BITMASK_Tx3 | BITMASK_Tx2 | BITMASK_Tx1 | BITMASK_Tx0)
#define CONFIG_PORTC                    ((BITMASK_NULL & MY_NOTUSED_CONFIG_PORT_C5_C4) | MY_KEYPAD_CONFIG_OUT_PORT_C3_C0) // Rest as input

#define MY_KEYPAD_VALID_OUTPUT_MASK     (uint8_t)0x0F // Mask for set output data to portC
//========================================================================================================================================================

//========================================================================================================================================================
// PORTB masks
#define MY_KEYPAD_CONFIG_IN_PIN_B5_B2   (BITMASK_Fx5 & BITMASK_Fx4 & BITMASK_Fx3 & BITMASK_Fx2)
#define MY_LCD_CONFIG_OUT_PORT_B1_B0    (BITMASK_Tx1 | BITMASK_Tx0) 
#define CONFIG_PORTB                    ((BITMASK_NULL & MY_KEYPAD_CONFIG_IN_PIN_B5_B2) | MY_LCD_CONFIG_OUT_PORT_B1_B0) // Rest as input

// Vaues for data shift and mask 
#define MY_KEYPAD_SHIFT_INPUT_AMOUNT    (uint8_t)0x02 // Shift amount from input configuration
#define MY_KEYPAD_VALID_INPUT_MASK      (uint8_t)0x0F // Mask after data shift 
//========================================================================================================================================================

//========================================================================================================================================================
// Timers initialization predefinitions compare mode options

// COM1A1 = 0, COM1A0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_NormalMode_OCxA (BITMASK_NULL) 
#define INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxA (BITMASK_FULL & BITMASK_Fx7 & BITMASK_Fx6)
// COM1AB1 = 0, COM1B0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_NormalMode_OCxB (BITMASK_NULL) 
#define INIT_TIMERx_TCCRxA_MASK_F_NormalMode_OCxB (BITMASK_FULL & BITMASK_Fx5 & BITMASK_Fx4)

// COM1A1 = 0, COM1A0 = 1, COM1AB1 = 0, COM1B0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_Togle_OCxA (BITMASK_NULL | BITMASK_Tx6) 
#define INIT_TIMERx_TCCRxA_MASK_F_Togle_OCxA (BITMASK_FULL & BITMASK_Fx7 & BITMASK_Fx5 & BITMASK_Fx4) 
// COM1A1 = 0, COM1A0 = 0, COM1AB1 = 0, COM1B0 = 1, 
#define INIT_TIMERx_TCCRxA_MASK_T_Togle_OCxB (BITMASK_NULL | BITMASK_Tx4) 
#define INIT_TIMERx_TCCRxA_MASK_F_Togle_OCxB (BITMASK_FULL & BITMASK_Fx7 & BITMASK_Fx6 & BITMASK_Fx5)
// COM1A1 = 1, COM1A0 = 0, COM1AB1 = 0, COM1B0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_Clear_OCxA (BITMASK_NULL | BITMASK_Tx7) 
#define INIT_TIMERx_TCCRxA_MASK_F_Clear_OCxA (BITMASK_FULL & BITMASK_Fx6 & BITMASK_Fx5 & BITMASK_Fx4)
// COM1A1 = 0, COM1A0 = 0, COM1AB1 = 1, COM1B0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_Clear_OCxB (BITMASK_NULL | BITMASK_Tx5) 
#define INIT_TIMERx_TCCRxA_MASK_F_Clear_OCxB (BITMASK_FULL & BITMASK_Fx7 & BITMASK_Fx6 & BITMASK_Fx4)
// COM1A1 = 1, COM1A0 = 1, COM1AB1 = 0, COM1B0 = 0, 
#define INIT_TIMERx_TCCRxA_MASK_T_Set_OCxA (BITMASK_NULL | BITMASK_Tx7 | BITMASK_Tx6) 
#define INIT_TIMERx_TCCRxA_MASK_F_Set_OCxA (BITMASK_FULL & BITMASK_Fx5 & BITMASK_Fx4)
// COM1A1 = 0, COM1A0 = 0, COM1AB1 = 1, COM1B0 = 1, 
#define INIT_TIMERx_TCCRxA_MASK_T_Set_OCxB (BITMASK_NULL | BITMASK_Tx5 | BITMASK_Fx4)
#define INIT_TIMERx_TCCRxA_MASK_F_Set_OCxB (BITMASK_FULL & BITMASK_Fx7 & BITMASK_Fx6)
//========================================================================================================================================================

//========================================================================================================================================================
// Timers initialization predefinitions prescaler predefinitions
// ICNC1 = 1, ICES1 = 1
#define INIT_TIMERx_TCCRxB_7_ICNC1_T  BITMASK_Tx7 // Input Capture Noise Canceler
#define INIT_TIMERx_TCCRxB_6_ICES1_T  BITMASK_Tx6 // Input Capture Edge Select

#define INIT_TIMERx_TCCRxB_7_ICNC1_F  BITMASK_Fx7 // Input Capture Noise Canceler
#define INIT_TIMERx_TCCRxB_6_ICES1_F  BITMASK_Fx6 // Input Capture Edge Select

// CS12 = 0, CS11 = 0, CS10 = 0
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_STOP (BITMASK_NULL)                                 
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_STOP (BITMASK_FULL & BITMASK_Fx2 & BITMASK_Fx1 & BITMASK_Fx0)
// CS12 = 0, CS11 = 0, CS10 = 1
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_0001 (BITMASK_NULL | BITMASK_Tx0)                  
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_0001 (BITMASK_FULL & BITMASK_Fx2 & BITMASK_Fx1)    
// CS12 = 0, CS11 = 1, CS10 = 0
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_0008 (BITMASK_NULL | BITMASK_Tx1)                   
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_0008 (BITMASK_FULL & BITMASK_Fx2 & BITMASK_Fx0)    
// CS12 = 0, CS11 = 1, CS10 = 1
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_0064 (BITMASK_NULL | BITMASK_Tx1 | BITMASK_Tx0)     
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_0064 (BITMASK_FULL & BITMASK_Fx2)
// CS12 = 1, CS11 = 0, CS10 = 0
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_0256 (BITMASK_NULL | BITMASK_Tx2)                   
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_0256 (BITMASK_FULL & BITMASK_Fx1 & BITMASK_Fx0)   
// CS12 = 1, CS11 = 0, CS10 = 1
#define INIT_TIMERx_TCCRxB_MASK_T_CLK_1024 (BITMASK_NULL | BITMASK_Tx2 | BITMASK_Tx0)     
#define INIT_TIMERx_TCCRxB_MASK_F_CLK_1024 (BITMASK_FULL & BITMASK_Fx1)            
// CS12 = 1, CS11 = 1, CS10 = 0
#define INIT_TIMERx_TCCRxB_MASK_T_EXT_Tx_Faling (BITMASK_NULL | BITMASK_Tx2 | BITMASK_Tx1) 
#define INIT_TIMERx_TCCRxB_MASK_F_EXT_Tx_Faling (BITMASK_FULL BITMASK_Fx0)               
// CS12 = 1, CS11 = 1, CS10 = 1
#define INIT_TIMERx_TCCRxB_MASK_T_EXT_Tx_Rising (BITMASK_NULL | BITMASK_Tx2 | BITMASK_Tx1 | BITMASK_Tx0) 
#define INIT_TIMERx_TCCRxB_MASK_F_EXT_Tx_Rising (BITMASK_FULL)                          
//========================================================================================================================================================

//========================================================================================================================================================
// Waveform Generation Mode
#define INIT_TIMERx_TCCRxB_4_WGM13_T  BITMASK_Tx4 // 
#define INIT_TIMERx_TCCRxB_3_WGM12_T  BITMASK_Tx3 // 

#define INIT_TIMERx_TCCRxA_1_WGM11_T  BITMASK_Tx1 //
#define INIT_TIMERx_TCCRxA_0_WGM10_T  BITMASK_Tx0 // 
//========================================================================================================================================================

/*********************************************************************************************************************************************************
 * InitPeryferia_m328p
 */
class InitPeryferia_m328p
{
private:
    bool _sei_set;

/**************************************************************************************** 
 * Methods for TIMER1 initialization 
*/
void Timer1Init_TCCR1A(void);
void Timer1Init_TCCR1B(void);
void Timer1Init_WaveformGeneration(void);
/**************************************************************************************** 
 * Methods for TIMER2 initialization 
*/
void Timer2Init_TCCR2A(void);
void Timer2Init_TCCR2B(void);
void Timer2Init_WaveformGeneration(void);
/**************************************************************************************** 
 * Methods for TIMER2 initialization 
*/
//=======================================================================================
public:
/****************************************************************************************
 * Class constructors and deconstructors
*/
    InitPeryferia_m328p(void);
    ~InitPeryferia_m328p();

    void DataDirectionsResistrsInit(void);

    // Initialization for TIMER's
    void Timer1Init(void);
    void Timer2Init(void);
};
#endif /* INIT_H_ */
//========================================================================================================================================================
#endif // _INC_INIT