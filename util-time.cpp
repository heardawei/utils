#include <stdint.h>
#include <string>
#include "util-time.h"

namespace utils {

int64_t Time::gettimeofday_us()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec * utils::kNumMicrosecsPerSec + tv.tv_usec;
}

int64_t Time::gettimeofday_ms()
{
    return gettimeofday_us() / utils::kNumMicrosecsPerMillisec;
}

int64_t Time::gettimeofday_s()
{
    return gettimeofday_us() / utils::kNumMicrosecsPerSec;
}

// 2017-12-26 15:34:04
std::string &Time::time_2_str(std::string &timestr, time_t t)
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
std::string Time::time_2_str(time_t t)
{
    std::string time_str;
    return time_2_str(time_str, t);
}

} /*namespace utils*/