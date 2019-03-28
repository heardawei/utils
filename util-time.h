#ifndef __UTIL_TIME_H__
#define __UTIL_TIME_H__

#include <time.h>
#include <stdint.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
int gettimeofday(struct timeval *tv, void *tz);
#else
#include <sys/time.h>
#endif

#ifdef _WIN32
int gettimeofday(struct timeval *tv, void *tz)
{
    time_t clock;
    struct tm tm; 
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1; 
    clock = mktime(&tm);
    tv->tv_sec = clock;
    tv->tv_usec = wtm.wMilliseconds * 1000;
    return 0;
}
#endif

namespace utils {

static const int64_t kNumMillisecsPerSec = INT64_C(1000);
static const int64_t kNumMicrosecsPerSec = INT64_C(1000000);
static const int64_t kNumNanosecsPerSec = INT64_C(1000000000);

static const int64_t kNumMicrosecsPerMillisec =
    kNumMicrosecsPerSec / kNumMillisecsPerSec;
static const int64_t kNumNanosecsPerMillisec =
    kNumNanosecsPerSec / kNumMillisecsPerSec;
static const int64_t kNumNanosecsPerMicrosec =
    kNumNanosecsPerSec / kNumMicrosecsPerSec;

class Time
{
public:
    static int64_t gettimeofday_us();
    static int64_t gettimeofday_ms();
    static int64_t gettimeofday_s();
    static std::string &time_2_str(std::string &timestr, time_t t = 0);
    static std::string time_2_str(time_t t = 0);



}; // class Time












} // namespace utils

#endif //__UTIL_TIME_H__
