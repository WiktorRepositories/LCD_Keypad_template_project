#include "convert_data_and_time.h"
#ifdef _INC_CONVERT_DATA_AND_TIME

namespace data_time{
//---------------------------------------------------------------------------------------------------

/*****************************************************************************************************
 * @name		  From_ms_to_time
 * @brief		  Convert to structure time_t from misecond amount
 * @param[in]	ms Milisecond amount
 * @note		  void
 * @return		Time in format time_t
 */
time_t From_ms_to_time(uint32_t ms)
{
  time_t tTime;

  tTime.hour = ms / 360000;
  ms = ms - (tTime.hour * 360000);

  tTime.minute = ms / 6000;
  ms = ms - (tTime.minute * 6000);

  tTime.second = ms / 100;
  ms = ms - (tTime.second * 100);

  ms = ms;

  return tTime;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  From_ms_to_time
 * @brief		  Convert to structure time_t from misecond amount
 * @param[in]	ms Milisecond amount
 * @note		  void
 * @return		Time in format time_t
 */
time_t From_sec_to_time(uint32_t sec)
{
  time_t tTime;

  tTime.hour = sec / 3600;
  sec = sec - (tTime.hour * 3600);

  tTime.minute = sec / 60;
  sec = sec - (tTime.minute * 60);

  tTime.second = sec;

  return tTime;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  From_time_to_ms
 * @brief		  Conversion from time format to miliseconds amount
 * @param[in]	pTime Constant pointer to time structure data
 * @note		  void
 * @return		Amount of miliseconds
 */
uint32_t From_time_to_ms(const time_t *pTime)
{
  return ((pTime->hour * 360000) + (pTime->minute * 6000) + (pTime->second * 100));
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  From_time_to_sec
 * @brief		  Conversion from time format to seconds amount
 * @param[in]	pTime Constant pointer to time structure data
 * @note		  void
 * @return		Amount of seconds
 */
uint32_t From_time_to_sec(const time_t *pTime)
{
  return ((pTime->hour * 3600) + (pTime->minute * 60) + (pTime->second));
}
//====================================================================================================

//----------------------------------------------------------------------------------------------------
} // namespace myTime
#endif // _INC_CONVERT_DATA_AND_TIME