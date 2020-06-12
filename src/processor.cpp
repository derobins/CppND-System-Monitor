#include "linux_parser.h"
#include "processor.h"

using namespace LinuxParser;

// DER: Return the aggregate CPU utilization
float Processor::Utilization() { return LinuxParser::CpuUtilization(); }