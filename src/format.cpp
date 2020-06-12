#include <iomanip>
#include <string>
#include <sstream>

#include "format.h"

using std::string;

// DER: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{
    int hours = 0;
    int minutes = 0;

    hours = seconds / 3600;
    seconds = seconds % 3600;

    minutes = seconds / 60;
    seconds = seconds % 60;

    std::ostringstream sobj;

    sobj << hours << ":";

    if (minutes < 10)
        sobj << 0;
    sobj << minutes << ":";

    if (seconds < 10)
        sobj << 0;
    sobj << seconds;

    return sobj.str();
}
