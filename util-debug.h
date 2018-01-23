#ifndef __UTIL_DEBUG_H__
#define __UTIL_DEBUG_H__
#include <stdio.h>
#ifndef DEBUG_PRINT
#define DEBUG_PRINT(fmt, arg...) printf("%s " fmt, __func__, ##arg)
#endif /*DEBUG_PRINT*/

#ifndef ERROR_PRINT
#define ERROR_PRINT(fmt, arg...) fprintf(stderr, "%s:%d " fmt, __FILE__, __LINE__, ##arg)
#endif /*ERROR_PRINT*/


#endif /*__UTIL_DEBUG_H__*/
