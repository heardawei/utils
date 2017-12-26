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
    static int64_t gettimeofday_us()
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return tv.tv_sec * utils::kNumMicrosecsPerSec + tv.tv_usec;
    }

    static int64_t gettimeofday_ms()
    {
        return gettimeofday_us() / utils::kNumMicrosecsPerMillisec;
    }

    static int64_t gettimeofday_s()
    {
        return gettimeofday_us() / utils::kNumMicrosecsPerSec;
    }

    // 2017-12-26 15:34:04
    static std::string &time_2_str(std::string &timestr, time_t t = 0)
    {
        struct tm tm1;
        char buff[128];
        if(!t) {
            t = gettimeofday_s();
        }
        localtime_r(&t, &tm1);
        strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm1);
        return timestr = buff;
    }
    static std::string time_2_str(time_t t = 0)
    {
        std::string time_str;
        return time_2_str(time_str, t);
    }

}; // class Time












} // namespace utils

#endif //__UTIL_TIME_H__