#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

using namespace LinuxParser;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// DER: Return the system's kernel identifier (string)
std::string System::Kernel()
{
    if(kernel_.empty())
        kernel_ = LinuxParser::Kernel();

    return kernel_;
}

// DER: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DER: Return the operating system name
std::string System::OperatingSystem()
{
    if(os_.empty())
        os_ = LinuxParser::OperatingSystem();

    return os_;
}

// DER: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DER: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DER: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::SystemUpTime(); }