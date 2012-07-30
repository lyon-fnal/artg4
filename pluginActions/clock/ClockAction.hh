// ClockAction.hh provides the class declaration for the @ClockAction@ action
// object. It records how long a run takes and prints its result.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef CLOCK_ACTION_HH
#define CLOCK_ACTION_HH

// Include the base class
#include "gm2g4/Core/ActionBase.hh"

// G4 includes
#include "G4Run.hh"

// Other library includes
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// C++ includes
#include <time.h>

// Everything goes in the g-2 namespace
namespace gm2 {
  class ClockAction : public ActionBase {
  public:
    // A constructor that takes in a parameter set.
    ClockAction(fhicl::ParameterSet const & p);

    // Destructor
    virtual ~ClockAction() {};

    // Overload the BeginOfRunAction method to initialize the clock
    virtual void BeginOfRunAction(const G4Run * currentRun);

    // Overload the EndOfRunAction method to finalize the clock and print
    // out the results.
    virtual void EndOfRunAction(const G4Run * currentRun);

  private:
    // A method to find the difference between two timespec values
    double diff(timespec start, timespec end);

    // timespec values for the start and end of the run;
    timespec start;
    timespec end;

    // An identifier to say whether we care about real time (CLOCK_REALTIME)
    // or absolute time (TIMER_ABSTIME).
    // (see <time.h> documentation for more information)
    clockid_t clockID;

    // A message logger for this action
    mf::LogInfo _logInfo
  };
}

#endif // CLOCK_ACTION_HH
