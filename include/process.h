#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process() = delete;
  Process(int pid);

  int Pid();               // DER: See src/process.cpp
  std::string User();      // DER: See src/process.cpp
  std::string Command();   // DER: See src/process.cpp
  float CpuUtilization();  // DER: See src/process.cpp
  std::string Ram();       // DER: See src/process.cpp
  long UpTime();           // DER: See src/process.cpp

  bool operator<(Process const& a) const;  // DER: See src/process.cpp
  bool operator>(Process const& a) const;  // DER: See src/process.cpp

  // DER: Declare any necessary private members
 private:
  int pid_ = -1;
  float utilization_ = -1.0;
};

#endif
