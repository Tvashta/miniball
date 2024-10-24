// Synopsis: Switches to adapt the code
//
// Authors: Martin Kutz <kutz@math.fu-berlin.de>,
//          Kaspar Fischer <kf@iaeth.ch>

#ifndef SEB_CONFIGURE_H
#define SEB_CONFIGURE_H

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream> // Ensure this is included

#define SEB_NAMESPACE Seb // namespace of the library
// #define SEB_ASSERTION_MODE // enables (cheap) assertions
// #define SEB_DEBUG_MODE // enables debugging checks (cheap and expensive ones)
// #define SEB_TIMER_MODE // enables runtime measurements
// #define SEB_STATS_MODE // enables statistics

#include "Seb_debug.h"

// We provide the following debugging routines:
//
// - SEB_DEBUG(expr): evaluates the expression expr when debugging mode
//   is on (see SEB_DEBUG_MODE above), or does nothing otherwise.
//
// - SEB_LOG(channel,expr): Writes to file channel.log the string
//   produced by the expression 's << expr' (where s is the stream for
//   file channel.log). This only happens when the debugging mode is
//   enabled; nothing is done otherwise.
//
// - SEB_ASSERT(expr): Asserts that the Boolean expression expr evaluates
//   to true. This only happens when the assertion mode is enabled. This
//   macro should only be used for cheap assertions (which do not heavily
//   affect the running time).
//
// - SEB_ASSERT_EXPENSIVE(expr): Asserts that the Boolean expression expr
//   evaluates to true. This only happens when the debugging mode is on,
//   and not otherwise. (The assertion mode alone doesn't enable such
//   assertions.)
//
// - SEB_TIMER_START(timer): Restarts the timer with name timer. Nothing
//   happens when the timer mode is disabled (see SEB_TIMER_MODE above).
//
// - SEB_TIMER_PRINT(timer): Prints a string to std::cout telling how
//   much time has elapsed since the last SEB_TIMER_START(timer).
//
// - SEB_TIMER_STRING(timer): Returns a string with the number of seconds
//   elapsed since the last SEB_TIMER_START(timer).
//
// - SEB_STATS(expr): evaluates the expression when stats mode is
//   enabled (see SEB_STATS_MODE above), or does nothing otherwise.

// Debugging mode:
#ifdef SEB_DEBUG_MODE
  // The debugging mode always enables the timer mode as well:
  #ifndef SEB_TIMER_MODE
  #define SEB_TIMER_MODE
  #endif
  #ifndef SEB_ASSERTION_MODE
  #define SEB_ASSERTION_MODE
  #endif

  #define SEB_ASSERT_EXPENSIVE(expr) assert(expr)
  #define SEB_DEBUG(expr) expr
  #define SEB_LOG(channel, expr) \
    { \
      std::stringstream s; \
      s << expr; \
      SEB_NAMESPACE::Logger::instance().log(channel, s.str()); \
    }
#else // SEB_DEBUG_MODE not defined
  #define SEB_ASSERT_EXPENSIVE(expr)
  #define SEB_DEBUG(expr)
  #define SEB_LOG(channel, expr)
#endif // SEB_DEBUG_MODE

// Assertion mode:
#ifdef SEB_ASSERTION_MODE
  #define SEB_ASSERT(expr) assert(expr)
#else // SEB_ASSERTION_MODE
  #define SEB_ASSERT(expr)
#endif // SEB_ASSERTION_MODE

// Timing mode:
#ifdef SEB_TIMER_MODE
  #define SEB_TIMER_START(timer) \
    { \
      SEB_NAMESPACE::Timer::instance().start(timer); \
    }
  #define SEB_TIMER_PRINT(timer) \
    { \
      std::cout << "Timer \'" << timer << "\': " \
                << std::setprecision(5) \
                << SEB_NAMESPACE::Timer::instance().lapse(timer) \
                << 's' << std::endl; \
    }
  #define SEB_TIMER_STRING(timer) \
    SEB_NAMESPACE::Timer::instance().lapse(timer)
#else // SEB_TIMER_MODE
  #define SEB_TIMER_START(timer)
  #define SEB_TIMER_PRINT(timer)
  #define SEB_TIMER_STRING(timer)
#endif // SEB_TIMER_MODE

// Stats mode:
#ifdef SEB_STATS_MODE
  #define SEB_STATS(expr) { expr; }
#else // SEB_STATS_MODE
  #define SEB_STATS(expr)
#endif // SEB_STATS_MODE

#endif // SEB_CONFIGURE_H
