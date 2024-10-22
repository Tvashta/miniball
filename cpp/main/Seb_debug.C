// Synopsis: A simple class to save debugging comments to files
//
// Authors: Martin Kutz <kutz@math.fu-berlin.de>,
//          Kaspar Fischer <kf@iaeth.ch>

#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <chrono>
#include <windows.h>

#include "Seb_configure.h"

namespace SEB_NAMESPACE {

  // Implementation of class Logger:

  Logger::Logger() {
  }

  Logger::~Logger() {
    // We walk through the list of all opened files and close them:
    for (auto it = channels.begin(); it != channels.end(); ++it) {
      it->second->close();
      delete it->second;
    }
  }

  Logger& Logger::instance() {
    // Here's where we maintain the only instance:
    static Logger instance;
    return instance;
  }

  void Logger::log(const char* ch, const std::string& msg) {
    const std::string name(ch);
    auto it = channels.find(name);

    // Have we already opened this file?
    if (it != channels.end()) {
      // If so, then just append the message:
      *(it->second) << msg;
      it->second->flush();
    } else {
      // If we haven't seen 'name' before, we create a new file:
      std::ofstream* o = new std::ofstream((name + ".log").c_str(),
                                            std::ofstream::out | std::ofstream::trunc);
      channels[name] = o;
      *o << msg;
    }
  }

  // Implementation of class Timer:

  Timer::Timer() {
  }

  Timer& Timer::instance() {
    // Here's where we maintain the only instance:
    static Timer instance;
    return instance;
  }

  void Timer::start(const char *timer_name) {
    // Get current time:
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    timers[std::string(timer_name)] = now.QuadPart;
  }

  float Timer::lapse(const char *name) {
    // Assert that start(name) has been called before:
    SEB_ASSERT(timers.find(std::string(name)) != timers.end());

    // Get current time:
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    // Compute elapsed time:
    float elapsed = (now.QuadPart - timers[std::string(name)]) * 1000.0f / frequency.QuadPart;
    return elapsed; // Return time in milliseconds
  }

  void Timer::initialize() {
    // Initialize the frequency for high-resolution performance counter
    QueryPerformanceFrequency(&frequency);
  }

  LARGE_INTEGER Timer::frequency;

} // namespace SEB_NAMESPACE
