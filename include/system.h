#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // DER: See src/system.cpp
  std::vector<Process>& Processes();  // DER: See src/system.cpp
  float MemoryUtilization();          // DER: See src/system.cpp
  long UpTime();                      // DER: See src/system.cpp
  int TotalProcesses();               // DER: See src/system.cpp
  int RunningProcesses();             // DER: See src/system.cpp
  std::string Kernel();               // DER: See src/system.cpp
  std::string OperatingSystem();      // DER: See src/system.cpp

  // DER: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string kernel_ = "";
  std::string os_ = "";
};

#endif