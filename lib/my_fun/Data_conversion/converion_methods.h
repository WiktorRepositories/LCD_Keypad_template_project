/*
 * LCD_application.h
 *
 * Created: 17.05.2024 
 *  Author: Wiki
 */
#include "_include.h"
#ifdef _INC_CONVERSION_METHODS

#include "stdint.h"
#include "convert_data_and_time.h"
#include "Global_macros/bit_mask_macros.h"

#define CONVERSION_TYPE_ASCI_HEX_BASE ('A' - 0xA)

enum DecimalNumberStringSize
{
    TYPE_DEC_time_t = 3U,
    TYPE_DEC_uin8_t = 4U, TYPE_DEC_int8_t = 5U, 
    TYPE_DEC_uint16_t = 6U, TYPE_DEC_int16_t = 7U,
    TYPE_DEC_uint32_t = 10U, TYPE_DEC_int32_t = 11U,
};
enum HexadeciNumberStringSize
{
    TYPE_HEX_uin8_t = 3U, TYPE_HEX_int8_t = 3U, 
    TYPE_HEX_uint16_t = 5U, TYPE_HEX_int16_t = 5U,
    TYPE_HEX_uint32_t = 8U, TYPE_HEX_int32_t = 8U
};

struct NumberStrSize_t
{
    enum enum_DecimalNumberStringSize
    {
        TYPE_DEC_uin8_t = 4U, TYPE_DEC_int8_t = 5U, 
        TYPE_DEC_uint16_t = 6U, TYPE_DEC_int16_t = 7U,
        TYPE_DEC_uint32_t = 10U, TYPE_DEC_int32_t = 11U,
    };
}; // https://en.cppreference.com/w/cpp/language/enum

/*****************************************************************************************************
 * @name		NumbersConversion
 * @brief		Clas to convert nmbers system
 */
class NumbersConversion
{
private:
    char* itoa_uint(char* p_buffer, unsigned int num, const unsigned int base);
    char* itoa_int(char* p_buffer, unsigned int num, const int base);

public:
    NumbersConversion(void) {;}
    ~NumbersConversion(void) {;}
    
    unsigned int Uint_to_str_oct(char* p_buffer, unsigned int num);

    unsigned int Uint_to_str_dec(char* p_buffer, unsigned int num);
    unsigned int Int_to_str_dec(char* p_buffer, int num);

    unsigned int Uint_to_str_hex(char* p_buffer, unsigned int num);
};
//====================================================================================================

/*****************************************************************************************************
 * @brief   Definitions for time conversion
 */
#define TIME_CONVERSION_STR_LEN 0x08U

#define TIME_CONVERSION_HOURS_MAX 24U
#define TIME_CONVERSION_MINUTES_MAX 60U
#define TIME_CONVERSION_SOCUNDS_MAX 60U
//====================================================================================================

/*****************************************************************************************************
 * @name		ConvertTime
 * @brief		Clas to convert nmbers system
 */
class FormatConvert: public NumbersConversion
{
private:
    void _SetCharArray(char arrChar[], uint8_t strLen, char inChar);

public:
    FormatConvert(void);
    ~FormatConvert();

    // String custom formating 
    void StrFormatToRight(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST, char c);

    // Time to string formating
    void TimeToStr(data_time::time_t *pTime, char arrChar[], char mark);
    void TimeToStr(uint8_t hour, uint8_t minute, uint8_t second, char arrChar[], char mark);
    void TimeToStr(uint8_t hour, uint8_t minute, uint8_t second, char arrChar[]);
};
//====================================================================================================
#endif // _INC_CONVERSION_METHOD
//====================================================================================================