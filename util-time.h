#ifndef __UTIL_TIME_H__
#define __UTIL_TIME_H__

#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <string>

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