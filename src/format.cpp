#include <iomanip>
#include <string>
#include <sstream>

#include "format.h"

using std::string;

// DONE: Complete this helper function
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

    // Unclear at this time what should be done when hours has
    // more than two digits. For now, just display XX.
    if (hours > 99)
        sobj << "XX:";
    else {
        if (hours < 10)
            sobj << 0;
        sobj << hours << ":";
    }

    if (minutes < 10)
        sobj << 0;
    sobj << minutes << ":";

    if (seconds < 10)
        sobj << 0;
    sobj << seconds;

    return sobj.str();
}
