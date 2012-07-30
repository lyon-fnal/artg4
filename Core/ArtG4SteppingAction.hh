// Gm2SteppingAction.hh provides declarations for the built-in stepping
// action for the g-2 simulation. In its main method, UserSteppingAction,
// it gets a collection of all action objects for the current run from the
// Action Holder service, and loops over them, calling their respective
// UserSteppingAction methods.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef GM2_STEPPING_ACTION_HH
#define GM2_STEPPING_ACTION_HH

// A couple of G4 includes
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

// Everything goes in the g-2 namespace
namespace gm2 {
  // Declaration of the class
  class Gm2SteppingAction : public G4UserSteppingAction {
  public:
    // Compiler-generated constructor, destructor, copy constructor, and 
    // equality operator are okay here.
    
    // Called at the end of each step (I think; the documentation is vague)
    void UserSteppingAction(const G4Step *);
  };

}

#endif // GM2_STEPPING_ACTION_HH
