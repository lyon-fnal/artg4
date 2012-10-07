// ClockActionService is the service that manages the clock for the simulation.
// It records how long a run takes and prints its result.
// To use this action, all you need to do is put it in the services section
// of the configuration file, like this:
// 
// services: { 
//   ...
//   user: {
//     ClockActionService: {}
//     ...
//   }
// }

// Expected parameters:

// - name (string): A name describing the action.
//       Default is 'clock'.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

// Include guard
#ifndef CLOCKACTION_SERVICE_HH
#define CLOCKACTION_SERVICE_HH

// Includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "art/Framework/Core/EDProducer.h"

#include "messagefacility/MessageLogger/MessageLogger.h"

#include <time.h>

// Get the base class
#include "artg4/actionBase/RunActionBase.hh"

namespace artg4 {

  class ClockActionService : public RunActionBase {
  public: 
    ClockActionService(fhicl::ParameterSet const&, art::ActivityRegistry&);
    virtual ~ClockActionService();

    // Overload the BeginOfRunAction method to initialize the clock
    virtual void beginOfRunAction(const G4Run *) override;

    // Overload the EndOfRunAction method to finalize the clock and print out
    // how long the run took.
    virtual void endOfRunAction(const G4Run *) override;

    // We don't add anything to the event, so we don't need callArtProduces
    // or FillEventWithArtStuff.

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
    mf::LogInfo logInfo_;
  };
}

#endif
