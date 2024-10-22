// Synopsis: A simple class to save debugging comments to files
//
// Authors: Martin Kutz <kutz@math.fu-berlin.de>,
//          Kaspar Fischer <kf@iaeth.ch>

#ifndef SEB_DEBUG_H
#define SEB_DEBUG_H

#include <fstream>
#include <map>
#include <string>
#include <windows.h> // Include Windows header for timing functions

namespace SEB_NAMESPACE {

class Logger
// A singleton class which sends debugging comments to log files.
{
private: // (Construction and destruction are private to prevent
    // more than one instantiation.)

    Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);
    ~Logger();

public: // access and routines:

    static Logger& instance();
    // Returns a reference to the only existing instance of this class:

    void log(const char *channel, const std::string& msg);
    // If this is the first call to log with string channel as the
    // first parameter, then the file with name channel.log is
    // opened (at the beginning) for writing and msg is written to
    // it.  Otherwise, the string msg is written to the already open
    // file channel.log.

private: // private members:
    typedef std::map<std::string, std::ofstream*> Streams;
    Streams channels; // a collection of pairs (k,v) where
    // k is the file-name and v is the
    // (open) stream associated with k
};

class Timer
// A singleton class which maintains a collection of named timers.
{
private: // (Construction and destruction are private to prevent
    // more than one instantiation.)

    Timer();
    Timer(const Timer&);
    Timer& operator=(const Timer&);

public: // access and routines:

    static Timer& instance();
    // Returns a reference to the only existing instance of this class:

    void start(const char *name);
    float lapse(const char *name);

private: // private members:
    typedef std::map<std::string, LARGE_INTEGER> Timers;
    Timers timers; // a collection of pairs (k,v) where
    // k is the timer name and v is the
    // (started) timer associated with k
};

} // namespace SEB_NAMESPACE

#endif // SEB_DEBUG_H
