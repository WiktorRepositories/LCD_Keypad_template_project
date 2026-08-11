/*
 * LCD_application.h
 *
 * Created: 05.05.2024 
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_LCD_APPLICATION

#include "string.h"
#include "LCD_data_control/LCD_data_control.h"
#include "LCD_016N0028_CFH_ET/LCD_016N002B_CFH_ET.h"
#include "Data_conversion/converion_methods.h"

/*****************************************************************************************************
 * Global data definitions
*/
#define LCD_APP_ROW_START 0x05U
#define LCD_APP_TICKET_ACTIVE_RED (char)('R')
#define LCD_APP_TICKET_ACTIVE_BLU (char)('B')
enum enum_TicketsTeamActive{TICKET_ACTIVE_NONE, 
TICKET_ACTIVE_RED = LCD_APP_TICKET_ACTIVE_RED, 
TICKET_ACTIVE_BLU = LCD_APP_TICKET_ACTIVE_BLU};
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @brief		void
 * @note	    Inheritace two children class
 */
class LCD_application: private LCD_DataControl, LCD_016N002B_CFH_ET
{
private:
    FormatConvert _Convert;
    uint8_t row_n, col_n;
    volatile bool _data_from_keypad_IRQ, _display_data_order_active;
    volatile uint8_t _strLen, _n_row, _n_col;
    char _arrBuffer[16];
//--------------------------------------------------------------------------------------------
    void _PutChar(char c, uint8_t n_row, uint8_t n_col);
    void _PutChar(const char *c, uint8_t n_row, uint8_t n_col);

    void _PutCharOther(char c, uint8_t n_row, uint8_t n_col);
    void _PutCharOther(const char *c, uint8_t n_row, uint8_t n_col);
//--------------------------------------------------------------------------------------------
    void _PrintArrofChars(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void _PrintArrofChars(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);

    void _PrintArrofCharsOther(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void _PrintArrofCharsOther(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
//--------------------------------------------------------------------------------------------
public:
uint8_t debuCursorPosition1, debuCursorPosition2, debuCursorPosition3;

    LCD_application(uint8_t row_n, uint8_t col_n);
    ~LCD_application();
//============================================================================================
// Initialization LCD operations
    void InitializeDevice(void);
    void ClearDisplayData(void);
    void ReturnCursorHome(void);
//============================================================================================
    void PutChar(char c, uint8_t n_row, uint8_t n_col);
    void PutChar(const char *c, uint8_t n_row, uint8_t n_col);
    void Order_PrintChar(uint8_t data);
//============================================================================================
// Definitions for print string data 
    void PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void PrintStr(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);

    void PrintStrOther(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void PrintStrOther(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    
    void Order_PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void Order_PrintStr(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col);
    void Execute_PrintStr(void);
//============================================================================================

//============================================================================================
// Definitions for print string data 
    void PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col);
    void PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col);
    void PrintInt_Format(uint8_t number, uint8_t n_row, uint8_t n_col);
    void PrintInt_Format(uint16_t number, uint8_t n_row, uint8_t n_col);

    void Order_PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col);
    void Order_PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col);
    void Execute_PrintInt(void);
//============================================================================================

//============================================================================================
// Definitions for print time data format 
    void PrintTime(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col); 
    void PrintTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col);
    void Order_PrintTime(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col); 
    void Order_PrintTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col);
    void Execute_PrintTime(void);

    void PrintTimeOther(data_time::time_t *pTime, uint8_t n_row, uint8_t n_col); 
    void PrintTimeOther(uint8_t hour, uint8_t minute, uint8_t second, uint8_t n_row, uint8_t n_col);
//============================================================================================

//============================================================================================
};
//====================================================================================================
#endif // _INC_LCD_APPLICATION
//====================================================================================================