/*
 * LCD_application.h
 *
 * Created: 17.05.2024 
 *  Author: Wiki
 */
#include "converion_methods.h"
#include <stdio.h>
#include "string.h"
#ifdef _INC_CONVERSION_METHODS

/*****************************************************************************************************
 * @name		  void
 * @brief		  void
 * @param[in]	void
 * @note		  void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name    itoa_uint
 * @brief   itoa for unsigned int 
 * @param   num Number to convert into string
 * @param   p_buffer Pointer to char buffer 
 * @param   base Base of number format to convert into [8, 10, 16]
 * @return  pointer to char this function is recursive 
 */
char* NumbersConversion::itoa_uint(char* p_buffer, unsigned int num, const unsigned int base)
{
  switch (base)
  {
  case 8:
    if(num >= 8)
    {   p_buffer = itoa_uint( p_buffer, num/8, 8); } else{;}

    *p_buffer++ = '0' + (num % 8);

    return p_buffer;
    break;

  case 10:
    if(num >= 10)
    {   p_buffer = itoa_uint(p_buffer, num/10, 10); } else{;}

    *p_buffer++ = '0' + (num % 10);

    return p_buffer;
    break;

  case 16:
    if(num >= 16)
    {   p_buffer = itoa_uint(p_buffer, num/16, 16); } else{;}

    num = (num % 16);
    if(num > 9)  { num = ('7' + num);} // '7' + 10 = 'A'
    else          { num = ('0' + num);}
    *p_buffer++ = num;

    return p_buffer;
    break;
  
  default:
    break;
  }

  return p_buffer;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  itoa_int
 * @brief		  itoa for signed int
 * @param[in]	dest Pointer to destination array with strig data 
 * @note		  void
 * @return		void
 */
char* NumbersConversion::itoa_int(char* p_buffer, unsigned int num, const int base)
{
  char* p_char;

  if (num < 0) 
    *p_char++ = '-';
  else 
    num = -num;
  *itoa_uint(p_char, num, base) = '\0';
  return p_buffer;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	DecimalNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int NumbersConversion::Uint_to_str_oct(char* p_buffer, unsigned int num)
{
  *(itoa_uint(p_buffer, num, 8)) = '\0';
  return strlen(p_buffer);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	DecimalNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int NumbersConversion::Uint_to_str_dec(char* p_buffer, unsigned int num)
{
  *(itoa_uint(p_buffer, num, 10)) = '\0';
  return strlen(p_buffer);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	DecimalNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int NumbersConversion::Int_to_str_dec(char* p_buffer, int num)
{
  *(itoa_int(p_buffer, num, 10)) = '\0';
  return strlen(p_buffer);
}
//====================================================================================================


/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format hexadecimal
 *
 * @param[in] 	number Number that will be converted to string
 * @param[in]	  arrChar[] Pointer to array of chars
 * @param[in] 	HexadeciNumberStringSize destination string size
 *
 * @note		  void
 * @return		strlen(arrChar)
 */
unsigned int NumbersConversion::Uint_to_str_hex(char* p_buffer, unsigned int num)
{
  *(itoa_uint(p_buffer, num, 16)) = '\0';
  return strlen(p_buffer);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CUST_CONV_StrFormatToRight
 * @brief		Convert string from front to end of a string array
 *
 * @param[in]	arrSRC[] Pointer to source array
 * @param[in]	lenSRC strlen(arrChar)
 * @param[in]	arrDST[] Pointer to destination array
 * @param[in]	lenDST strlen(arrChar)
 * @param[in] c char to fil empty spaces
 *
 * @note		  Input lenght need to be strlen(arrChar)
 *            This string is formating specyfic
 * @return		void
 */
void FormatConvert::StrFormatToRight(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST, char c)
{
  unsigned int i,j;
  for(i=0; i<lenDST; i++) 
  { arrDST[i] = c; }

  arrDST[lenDST] = '\0';

  j = lenDST - 1;
  i = lenSRC - 1;
  while((j < 0x7F) && (i < 0x7F))
  { arrDST[j--] = arrSRC[i--];}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  TimeToStr
 * @brief		  Time data format convert to string format
 * @param[in]	pTime Pointer to data_time::conv_time_t fromat data
 * @note		  void
 * @return		void
 */
void FormatConvert::TimeToStr(data_time::time_t *pTime, char arrChar[], char mark)
{
  char tArray[8];
  unsigned int t_strlen;
  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[0], pTime->hour);
  StrFormatToRight((char*)&tArray[0], 2, (char*)&arrChar[0], 2, '0');

  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[3], pTime->minute);
  StrFormatToRight((char*)&tArray[3], 2, (char*)&arrChar[3], 2, '0');

  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[7], pTime->second);
  StrFormatToRight((char*)&tArray[7], 2, (char*)&arrChar[7], 2, '0');

  arrChar[2] = mark;
  arrChar[6] = mark;
  arrChar[8] = '\0';
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  TimeToStr
 * @brief		  Time data format convert to string format
 * @param[in]	hour Value of a hour
 * @param[in] minute Value of a minute 
 * @param[in] second Value of a second
 * @note		  void
 * @return		void
 */
void FormatConvert::TimeToStr(uint8_t hour, uint8_t minute, uint8_t second, char arrChar[], char mark)
{
  char tArray[8];
  unsigned int t_strlen;
  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[0], hour);
  StrFormatToRight((char*)&tArray[0], 2, (char*)&arrChar[0], 2, '0');

  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[3], minute);
  StrFormatToRight((char*)&tArray[3], 2, (char*)&arrChar[3], 2, '0');

  t_strlen = NumbersConversion::Uint_to_str_dec((char*)&tArray[7], second);
  StrFormatToRight((char*)&tArray[7], 2, (char*)&arrChar[7], 2, '0');

  arrChar[2] = mark;
  arrChar[6] = mark;
  arrChar[8] = '\0';
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  TimeToStr
 * @brief		  Time data format convert to string format by using sprintf
 * @param[in]	hour Value of a hour
 * @param[in] minute Value of a minute 
 * @param[in] second Value of a second
 * @note		  void
 * @return		void
 */
void TimeToStr(uint8_t hour, uint8_t minute, uint8_t second, char arrChar[])
{
  sprintf(arrChar, "%02d:%02d:%02d", hour, minute, second);
}
//====================================================================================================

//====================================================================================================
#endif // _INC_CONVERSION_METHODS
//====================================================================================================