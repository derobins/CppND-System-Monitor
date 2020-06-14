#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, skip, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // Ignore the word "version"
    linestream >> os >> skip >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DER: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  long total = -1;
  long available = -1;

  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          total = std::stol(value);
        }
        else if (key == "MemAvailable:") {
          available = std::stol(value);
        }
      }
    }
  }

  long not_available = total - available;

  return static_cast<float>(not_available) / static_cast<float>(total);
}

// DER: Read and return the system uptime
long LinuxParser::SystemUpTime() {
  string uptime, idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle;
  }
  return (long)std::stof(uptime);
}

// DER: Read and return CPU utilization
// NOTE: Was a vector of type string.
float LinuxParser::CpuUtilization() {
  long user = -1;
  long nice = -1;
  long system = -1;
  long idle = -1;

  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        linestream >> user >> nice >> system >> idle;
      }
    }
  }
  return static_cast<float>(user + nice + system) / static_cast<float>(idle);
}

// DER: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return -1;
}

// DER: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return std::stoi(value);
        }
      }
    }
  }
  return -1;
}

// DER: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line = "";

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + "/" + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }

  return line;
}

// DER: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string value;

  long size_kb = 0;
  long size_mb = 0;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          size_kb = std::stoi(value);
          size_mb = size_kb / 1024;
        }
      }
    }
  }

  return std::to_string(size_mb);
}

// DER: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{
  // First, get the UID from the proc entry
  string line;
  string key;
  string value;
  int uid = -1;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          uid = std::stoi(value);
        }
      }
    }
  }

  // Now get the username
  struct passwd *pwd = getpwuid((uid_t)uid);

  return string(pwd->pw_name);
}

// DER: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ProcessUpTime(int pid) {
  string line = "";
  vector<string> tokens;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + "/" + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream linestream(line);
    string tmp;
    while (std::getline(linestream, tmp, ' ')) {
      tokens.push_back(tmp);
    }
  }

  long start_time = std::stol(tokens[21]);
  long uptime = LinuxParser::SystemUpTime(); /* So inefficient! */

  long seconds = uptime - (start_time / sysconf(_SC_CLK_TCK));

  return seconds;
}

// DER: Read and return the CPU utilization of a a process.
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::CpuUtilization(int pid) {
  string line = "";
  vector<string> tokens;

  std::ifstream filestream(kProcDirectory + std::to_string(pid) + "/" + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream linestream(line);
    string tmp;
    while (std::getline(linestream, tmp, ' ')) {
      tokens.push_back(tmp);
    }
  }

  long utime = std::stol(tokens[13]);
  long stime = std::stol(tokens[14]);
  long cutime = std::stol(tokens[15]);
  long cstime = std::stol(tokens[16]);
  long p_total_time = utime + stime + cutime + cstime;
  p_total_time /= sysconf(_SC_CLK_TCK);

  long p_start_time = std::stol(tokens[21]);
  p_start_time /= sysconf(_SC_CLK_TCK);

  long s_uptime = LinuxParser::SystemUpTime(); /* So inefficient! */

  long p_uptime = s_uptime - p_start_time;

  float utilization = (float)p_total_time / (float)p_uptime;

  return utilization;
}
