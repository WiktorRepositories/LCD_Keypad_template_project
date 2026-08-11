#include "_include.h"
#ifdef _INC_TIME_MODULE

#ifndef TIME_MODULE_H
#define TIME_MODULE_H

#include "stdint.h"
#include "Data_conversion/convert_data_and_time.h"

class DataAndTime
{
private:
    uint8_t _F;
    uint8_t hour, minute, second, n;
    uint32_t _n_sec;

    void IncSecond(void);

public:
    DataAndTime(const uint8_t in_F);
    ~DataAndTime(void){;}

    void IRQ_TickEvent(void);
    
    void SetTime(data_time::time_t* pTime);
    void SetTime(uint8_t inhour, uint8_t inminute, uint8_t insecond);

    data_time::time_t GetTime(void);
    void GetTime(data_time::time_t* pTime);
};

#endif // TIME_MODULE_H
#endif // _INC_TIME_MODULE