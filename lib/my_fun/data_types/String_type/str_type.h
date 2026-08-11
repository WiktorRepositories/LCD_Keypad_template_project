#define INC_STR_TYPE_H
#ifdef INC_STR_TYPE_H

//#include <string.h>
// My Implementaion for string.h ...

namespace datatype{
/***************************************************************************
 * Data type for string 
 */
typedef struct str_type
{
    unsigned char n;
    char* pStr;
};
//==========================================================================
/***************************************************************************
 * 
 */
class String
{
private:
    /* data */
public:
    String(const char arrChar[]);
    ~String();
};
//==========================================================================
}

#endif // INC_STR_TYPE_H