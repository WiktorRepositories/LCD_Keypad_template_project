#include "time_module.h"
#ifdef _INC_TIME_MODULE


DataAndTime::DataAndTime(const uint8_t in_F)
{  _F = in_F; hour = 0; minute = 0; second = 0; n = 1; _n_sec = 0;}

/***************************************************************
 * @name    IncSecond
 * @brief   Add one second time data
 */
void DataAndTime::IncSecond(void)
{
    if(second < 59)
    {   second++;}
    else
    {   second=0;
        if(minute < 59)
        {   minute++;}
        else
        {   minute=0;
            if(hour < 24)
            {   hour++;}
            else
            {   hour=0;}
        }
    }
    _n_sec++;
}
//==============================================================

/***************************************************************
 * @name    IncSecond
 * @brief   Add one second time data
 */
void DataAndTime::IRQ_TickEvent(void)
{
    if(n < _F)
    {   n++;}
    else
    {   IncSecond();
        n=1;}
}
//==============================================================

void DataAndTime::SetTime(data_time::time_t* pTime)
{
    hour = pTime->hour;
    minute = pTime->minute;
    second = pTime->second;
}
//==============================================================

void DataAndTime::SetTime(uint8_t inhour, uint8_t inminute, uint8_t insecond)
{
    hour = inhour;
    minute = inminute;
    second = insecond;
}
//==============================================================

/***************************************************************
 * @name    GetTime
 * @brief   Return current time value
 * @return  Time format "data_time::time_t"
 */
data_time::time_t DataAndTime::GetTime(void)
{
    data_time::time_t tTime;
    tTime.hour = hour;
    tTime.minute = minute;
    tTime.second = second;
    return tTime;
}
//==============================================================

/***************************************************************
 * @name    GetTime
 * @brief   Return current time value
 * @param[in] pTime Pointer to structure of type data_time::time_t
 * @return  void
 */
void DataAndTime::GetTime(data_time::time_t* pTime)
{
    pTime->hour = hour;
    pTime->minute = minute;
    pTime->second = second;
}
//==============================================================
#endif // _INC_TIME_MODULE
//==============================================================