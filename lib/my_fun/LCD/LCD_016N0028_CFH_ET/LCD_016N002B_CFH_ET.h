/*
 * LCD_016N002B_CFH_ET.h
 *
 * Created: 01.01.2024
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_LCD_016N002B_CFH_ET
/****************************************************************************************************************
 * Defintions if include required 
*/
#ifndef LCD_INC_LCD_016N002B_CFH_ET_H_
#define LCD_INC_LCD_016N002B_CFH_ET_H_
//===============================================================================================================

#include <avr/io.h>
//#include <avr/delay.h>
#include <util/delay.h>
#include "Global_macros/bit_mask_macros.h"

/****************************************************************************************************************
 * LCD Initialization data instruction in enumerate: 
*/
enum enum_INIT_DATA_STEP
{// Initializing of LCM
	INIT_DATA_STEP_x01_FunctionSet = (uint8_t)0x30, // BF can not be checked before this instruction
	INIT_DATA_STEP_x02_FunctionSet = (uint8_t)0x20, // BF can not be checked before this instruction
	INIT_DATA_STEP_x03_FunctionSet = (uint8_t)0x20, // BF can not be checked before this instruction
	INIT_DATA_STEP_x04_DispOnOffCotrol = (uint8_t)0x00, // Display ON/OFF contro
	INIT_DATA_STEP_x05_DispClear = (uint8_t)0x00, // Display clear
	INIT_DATA_STEP_x06_EntryModeSet = (uint8_t)0x00 // Entry mode set 
};
//===============================================================================================================

/****************************************************************************************************************
 * LCD Delay time required for LCD controler to proced informations:
*/
enum enum_DISPLAY_DELAY_TIME_MS
{// Delay time in ms definitions
    DISPLAY_DELAY_TIME_ms_clr_display = 2U,    // 2ms Minimum required
    DISPLAY_DELAY_TIME_ms_ret_home = 2U,       // 2ms Minimum required
    DISPLAY_DELAY_TIME_ms_long = 2U,           // 2ms Minimum required
    DISPLAY_DELAY_TIME_ms_init = 60U,          // 40ms Minimum required
};
enum enum_DISPLAY_DELAY_TIME_US
{// Delay time in us definitions
    DISPLAY_DELAY_TIME_us_entry_mode = 50U,    // 39us Minimum required
    DISPLAY_DELAY_TIME_us_displ_mode = 50U,    // 39us Minimum required
    DISPLAY_DELAY_TIME_us_cursDispShift = 50U, // 39us Minimum required
    DISPLAY_DELAY_TIME_us_functionSet = 50U,   // 39us Minimum required
    DISPLAY_DELAY_TIME_us_setCGRAM = 50U,      // 39us Minimum required
    DISPLAY_DELAY_TIME_us_setDDRAM = 50U,      // 39us Minimum required
    DISPLAY_DELAY_TIME_us_writeDataRAM = 54U,  // 43us Minimum required
    DISPLAY_DELAY_TIME_us_readDataRAM = 54U,   // 43us Minimum required
    DISPLAY_DELAY_TIME_us_short = 54U          // 43us Minimum required
};
//===============================================================================================================

/****************************************************************************************************************
 * Write “00H” to DDRAM and set DDRAM address to “00H” from AC
 * 0b 0000 0001
*/
#define DISPLAY_COMAND_CODE_ClearDisplay (uint8_t)0x01 // 0b 0000 0001
//===============================================================================================================

/****************************************************************************************************************
 * Set DDRAM address to “00H” from AC
 * and return cursor to its original position
 * if shifted. The contents of DDRAM are
 * not changed.
 * 0b 0000 001x
*/
#define DISPLAY_COMAND_CODE_ReturnHome_BaseCode (uint8_t)0x02 // 0b 0000 0010
//===============================================================================================================

/****************************************************************************************************************
 * Assign cursor moving direction and
 * enable the shift of entire display.
*/
#define LCD_ENTRY_MODE_SH_DISP_SHIFT_OFF (uint8_t)0x00      // 0b 0000 0000
#define LCD_ENTRY_MODE_SH_DISP_SHIFT_ON (uint8_t)0x01       // 0b 0000 0001

#define LCD_ENTRY_MODE_ID_CURS_DIR_L (uint8_t)0x00          // 0b 0000 0000
#define LCD_ENTRY_MODE_ID_CURS_DIR_R (uint8_t)0x02          // 0b 0000 0010

#define DISPLAY_COMAND_CODE_BASE_VALUE_03 (uint8_t) 0x04    // 0b 0000 0100
#define DISPLAY_COMAND_CODE_FUN_EntryModee(id, sh) (DISPLAY_COMAND_CODE_BASE_VALUE_03 | id | sh) // 0b 0000 01xx
//===============================================================================================================

/****************************************************************************************************************
 * Set display (D), cursor (C), and blinking
 * of cursor (B) on/off control bit.
*/
#define LCD_DISPLAY_CONTROL_B_CURSOR_BLINK_ON (uint8_t)0x01 // 0b 0000 0001
#define LCD_DISPLAY_CONTROL_B_CURSOR_BLINK_OFF (uint8_t)0x00// 0b 0000 0000 

#define LCD_DISPLAY_CONTROL_C_CURSOR_ON (uint8_t)0x02       // 0b 0000 0010
#define LCD_DISPLAY_CONTROL_C_CURSOR_OFF (uint8_t)0x00      // 0b 0000 0000

#define LCD_DISPLAY_CONTROL_D_DISPLAY_ON (uint8_t)0x04      // 0b 0000 0100
#define LCD_DISPLAY_CONTROL_D_DISPLAY_OFF (uint8_t)0x00     // 0b 0000 0000

#define DISPLAY_COMAND_CODE_BASE_VALUE_04 (uint8_t)0x08     // 0b 0000 1000
#define DISPLAY_COMAND_CODE_FUN_DisplayControl(b, c, d) (DISPLAY_COMAND_CODE_BASE_VALUE_04 | b | c | d)
//===============================================================================================================

/****************************************************************************************************************
 * Set cursor moving and display shift
 * control bit, and the direction, without
 * changing of DDRAM data
*/
#define LCD_CURSOR_DISPLAY_SHIFT_RL_MOVING_DIR_L (uint8_t)0x04  // 0b 0000 0100
#define LCD_CURSOR_DISPLAY_SHIFT_RL_MOVING_DIR_R (uint8_t)0x00  // 0b 0000 0000

#define LCD_CURSOR_DISPLAY_SC_SHIFT_MOVING_ON (uint8_t)0x08     // 0b 0000 1000
#define LCD_CURSOR_DISPLAY_SC_SHIFT_MOVING_OFF (uint8_t)0x00    // 0b 0000 0000


#define DISPLAY_COMAND_CODE_BASE_VALUE_05 (uint8_t)0x10         // 0b 0001 0000
#define DISPLAY_COMAND_CODE_FUN_CursorDisplayShift(rl, sc) (DISPLAY_COMAND_CODE_BASE_VALUE_05 | rl | sc)

enum displayMovingDirection_enum{DISPLAY_CURRSOR_L, DISPLAY_CURRSOR_R, DISPLAY_MOVING_L, DISPLAY_MOVING_R};
//===============================================================================================================

/****************************************************************************************************************
 * Set interface data length
 * (DL:8-bit/4-bit), numbers of display line
 * (N:2-line/1-line)and, display font type
 * (F:5ǘ11 dots/5ǘ8 dots)
*/
#define LCD_FUNCTION_SET_F_5X11_DOTS (uint8_t)0x04      // 0b 0000 0100
#define LCD_FUNCTION_SET_F_5X8_DOTS (uint8_t)0x00       // 0b 0000 0000

#define LCD_FUNCTION_SET_N_LINE_2 (uint8_t)0x08         // 0b 0000 1000
#define LCD_FUNCTION_SET_N_LINE_1 (uint8_t)0x00         // 0b 0000 0000

#define LCD_FUNCTION_SET_DL_LINE_AMOUT_8 (uint8_t)0x10  // 0b 0001 0000
#define LCD_FUNCTION_SET_DL_LINE_AMOUT_4 (uint8_t)0x00  // 0b 0000 0000

#define DISPLAY_COMAND_CODE_BASE_VALUE_06 (uint8_t)0x20 // 0b 0010 0000
#define DISPLAY_COMAND_CODE_FUN_FunctionSet(dl, n, f) (DISPLAY_COMAND_CODE_BASE_VALUE_06 | dl | n | f)
//===============================================================================================================

/****************************************************************************************************************
 * Set CGRAM address in address counter. 
*/
#define LCD_SET_CGRAM_ADDR_BASE (uint8_t)0x40           // 0b 0100 0000
#define LCD_SET_CGRAM_ADDR_MASK (uint8_t)0x3F           // 0b 0011 1111
//#define DISPLAY_COMAND_CODE_FUN_SetCGRAM_ADDR(addr) (LCD_SET_CGRAM_ADDR_BASE | addr)
#define DISPLAY_COMAND_CODE_FUN_SetCGRAM_ADDR(addr) (LCD_SET_CGRAM_ADDR_BASE | (LCD_SET_CGRAM_ADDR_MASK & addr))
//===============================================================================================================

/****************************************************************************************************************
 * Set DDRAM address in address counter.
*/
#define LCD_SET_DDRAM_ADDR_BASE (uint8_t)0x80           // 0b 1000 0000
#define LCD_SET_DDRAM_ADDR_MASK (uint8_t)0x7F           // 0b 0111 1111
//#define DISPLAY_COMAND_CODE_FUN_SetDDRAM_ADDR(addr) (LCD_SET_DDRAM_ADDR_BASE | addr)
#define DISPLAY_COMAND_CODE_FUN_SetDDRAM_ADDR(addr) (LCD_SET_DDRAM_ADDR_BASE | (LCD_SET_DDRAM_ADDR_MASK & addr))

enum displayColLineNum_enum{DISPLAY_LINE_1  = (uint8_t)0x00,   DISPLAY_LINE_2  = (uint8_t)0x01};
enum displayLineOffset_enum{DISPLAY_LINE_TOP= (uint8_t)0x00,   DISPLAY_LINE_BOT= (uint8_t)0x40};
//===============================================================================================================

/****************************************************************************************************************
 * Port masks configurations
 * R/W - Stays 0. Data is only write to LCD display
*/
#define LCD_MASK_PORTB_CLR_B0_RS   (BITMASK_Fx0)
#define LCD_MASK_PORTB_CLR_B1_E    (BITMASK_Fx1)

#define LCD_MASK_PORTB_SET_B0_RS   (BITMASK_Tx0)
#define LCD_MASK_PORTB_SET_B1_E    (BITMASK_Tx1)
//===============================================================================================================

/****************************************************************************************************************
 * Class for menage LCD display 016N002B-CFH-ET 2x16
*/
class LCD_016N002B_CFH_ET
{
private:
//Send long instruction for LCD display 
void _PutCommandLong(uint8_t cmd, enum_DISPLAY_DELAY_TIME_MS time_ms);

//Send short instruction for LCD display 
void _PutCommandShort(uint8_t cmd, enum_DISPLAY_DELAY_TIME_US time_us);
//====================================================================

public:
    uint8_t curstorPosition;

/*********************************************************************
 * Definitions for public class varibales 
*/
    LCD_016N002B_CFH_ET(uint8_t row_n, uint8_t col_n);
    ~LCD_016N002B_CFH_ET();

    // LCD initialization is nesesary before use
    void Initialize_8bitInterface(void);

    // LCD reset instructions
    void ClearDisplay(void);
    void ReturnHome(void);

    // Cursor movement menagment
    void SetCursorMovingDirectionL(void);
    void SetCursorMovingDirectionR(void);
    void SetCurrsorToPosition(uint8_t n_row, displayColLineNum_enum n_col);

    // LCD data displayed momvemt
    void SetDisplayMovingDirectionL(void);
    void SetDisplayMovingDirectionR(void);

    //Send single byte data to LCD display */
    void PutData(uint8_t data);
};
//==============================================================================================
#endif // ifndef LCD_H_
//==============================================================================================
#endif // ifdef _INC_LCD
//==============================================================================================