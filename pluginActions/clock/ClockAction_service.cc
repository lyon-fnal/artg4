// This file provides the implementation for an action object that records how
// long runs take and outputs its results.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

#include "artg4/pluginActions/clock/ClockAction_service.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/ActionHolder_service.hh"

using std::string;

artg4::ClockActionService::ClockActionService(fhicl::ParameterSet const & p, 
					      art::ActivityRegistry &)
  : RunActionBase(p.get<string>("name","clock")),
    // Set the clock to use 'real time'.
    clockID(CLOCK_REALTIME),
    // Initialize our message logger
    logInfo_("ClockAction")
{
  // Register ourselves with the ActionHolder
  art::ServiceHandle<ActionHolderService> actionHolder;

  actionHolder -> registerAction(this);
}

// Destructor
artg4::ClockActionService::~ClockActionService()
{}


// Overload beginOfRunAction, called at the beginning of each run.
// Here we assign a value to the start clock.
void artg4::ClockActionService::beginOfRunAction(const G4Run * currentRun)
{
  // Find the current time and assign it to our member variable @start@
  clock_gettime(clockID, &start);
}

// Overload EndOfRunAction, called at the end of each run.
// Here we assign a value to the end clock and print how long the run took.
void artg4::ClockActionService::endOfRunAction(const G4Run * currentRun)
{
  // Find the current time and assign it to our member variable @end@
  clock_gettime(clockID, &end);

  // Print out how long the run took
  logInfo_ << "Elapsed time this run: " 
	   << diff(start, end) << " seconds\n";
}

// This private member function finds the time difference between the two
// provided timespec values, in seconds.
double artg4::ClockActionService::diff(timespec start, timespec end)
{
  timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp.tv_sec + temp.tv_nsec/1e9;
}


using artg4::ClockActionService;
DEFINE_ART_SERVICE(ClockActionService)
