// ClockAction.cc provides the implementation for an action object that 
// records how long runs take and outputs its results.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/pluginActions/clock/ClockAction.hh"

using std::string;

// Constructor takes a parameter set, calls the base class's constructor, and
// initializes member data
artg4::ClockAction::ClockAction(fhicl::ParameterSet const & p)
  : ActionBase(p.get<string>("name", "clock")),
    // Set the clock to use 'real time'.
    clockID(CLOCK_REALTIME),
    // Initialize our message logger
    _logInfo("CLOCKACTION")
{}

// Overload BeginOfRunAction, called at the beginning of each run.
// Here we assign a value to the start clock.
void artg4::ClockAction::BeginOfRunAction(const G4Run * currentRun,
					  G4UserRunAction *)
{
  // Find the current time and assign it to our member variable @start@
  clock_gettime(clockID, &start);
}

// Overload EndOfRunAction, called at the end of each run.
// Here we assign a value to the end clock and print how long the run took.
void artg4::ClockAction::EndOfRunAction(const G4Run * currentRun,
					G4UserRunAction *)
{
  // Find the current time and assign it to our member variable @end@
  clock_gettime(clockID, &end);

  // Print out how long the run took
  _logInfo << "Elapsed time this run: " 
	   << diff(start, end) << " seconds\n";
}

// This private member function finds the time difference between the two
// provided timespec values, in seconds.
double artg4::ClockAction::diff(timespec start, timespec end)
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
