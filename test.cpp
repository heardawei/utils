#include "util-time.h"
#include "util-debug.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "----------------------util-time.h----------------------" << endl;
    string str("");
    cout << "time_2_str(str, t=0) " << utils::Time::time_2_str(str).c_str() << endl;
    cout << "time_2_str(t=0)      " << utils::Time::time_2_str().c_str() << endl;
    cout << "gettimeofday_s()     " << utils::Time::gettimeofday_s() << endl;
    cout << "gettimeofday_ms()    " << utils::Time::gettimeofday_ms() << endl;
    cout << "gettimeofday_us()    " << utils::Time::gettimeofday_us() << endl;

    cout << "----------------------util-debug.h----------------------" << endl;
    DEBUG_PRINT("hell%c %s %d\n", 'o', "world", 2323223);
    ERROR_PRINT("this is %d test %s\n", 9999, "ERROR_PRINT");


    return 0;
}