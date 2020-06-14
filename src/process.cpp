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

Process::Process(int pid) : pid_(pid) {
    // Cache this for sorting
    utilization_ = LinuxParser::CpuUtilization(pid_);
    ram_ = LinuxParser::Ram(pid_);
}

// DER: Return this process's ID
int Process::Pid() { return pid_; }

// DER: Return this process's CPU utilization
float Process::CpuUtilization() {

  return utilization_;
}

// DER: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DER: Return this process's memory utilization in MB
float Process::Ram() {
    return ram_;
}

// DER: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DER: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::ProcessUpTime(pid_); }

// DER: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  //return ram_ < a.ram_;
  //return pid_ < a.pid_;
  return utilization_ < a.utilization_;
}
bool Process::operator>(Process const& a) const {
  //return ram_ > a.ram_;
  //return pid_ > a.pid_;
  return utilization_ > a.utilization_;
}
