#include "_include.h"
#ifdef _INC_CONVERT_DATA_AND_TIME

#ifndef CONVERT_DATA_AND_TIME_H
#define CONVERT_DATA_AND_TIME_H

#include "stdint.h"

/*****************************************************************************************************
 * @brief   Definitions for time conversion
 */
#define TIME_CONVERSION_STR_LEN 0x08U

#define TIME_CONVERSION_HOURS_MAX 24U
#define TIME_CONVERSION_MINUTES_MAX 60U
#define TIME_CONVERSION_SOCUNDS_MAX 60U

#define CONVERSION_BASE_NUM_DIGIT_MIN (char)'0'
#define CONVERSION_BASE_NUM_DIGIT_MAX (char)'9'

#define CONVERSION_BASE_NUM_LETER_MIN (char)'A'
#define CONVERSION_BASE_NUM_LETER_MAX (char)'Z'

#define TIME_CONVERSION_NUMBER_BASEBNUM 0x40
//====================================================================================================

namespace data_time{

    #define data_time_TIME_LEN (uint8_t)9U
    #define data_time_DATA_LEN (uint8_t)11U
//============================================================================= 
typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}time_t;
//--------------------

//----------------------------------------------
// Conversion from seconds to time structure
time_t From_ms_to_time(uint32_t ms);
time_t From_sec_to_time(uint32_t sec);

// Conversion from time structure to seconds amount
uint32_t From_time_to_ms(const time_t *pTime);
uint32_t From_time_to_sec(const time_t *pTime);
//=============================================================================
} // namespace myTime

#endif // ifndef CONVERT_DATA_AND_TIME_H
#endif // _INC_CONVERT_DATA_AND_TIME