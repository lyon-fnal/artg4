// Gm2RunAction.hh provides declarations for the built-in run action for
// the g-2 simulation. It gets the collection of all action objects for the
// run and loops over them for both BeginOfRunAction and EndOfRunAction,
// calling the respective methods in each action object.

// Authors: Tasha Arvanitis, Adam Lyon  
// Date: July 2012

// Include guard
#ifndef GM2_RUN_ACTION_HH
#define GM2_RUN_ACTION_HH

// Some G4 includes
#include "G4UserRunAction.hh"
#include "G4Run.hh"

// Everything goes in the g-2 namespace
namespace gm2 {

  class Gm2RunAction : public G4UserRunAction {
  public:
    // Compiler-generated default constructor, destructor, copy constructor, 
    // and equality operator are all okay.

    // Called at the beginning of each run
    void BeginOfRunAction(const G4Run * currentRun);

    // Called at the end of each run
    void EndOfRunAction(const G4Run * currentRun);
  };
}
#endif // GM2_RUN_ACTION_HH
