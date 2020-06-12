#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

using namespace LinuxParser;

Process::Process(int pid) : pid_(pid) {}

// DER: Return this process's ID
int Process::Pid() { return pid_; }

// DER: Return this process's CPU utilization
float Process::CpuUtilization()
{
    // Cache this for sorting
    if (utilization_ < 0.0)
        utilization_ = LinuxParser::CpuUtilization(pid_);

    return utilization_;
}

// DER: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DER: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DER: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DER: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::ProcessUpTime(pid_); }

// DER: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return utilization_ < a.utilization_; }