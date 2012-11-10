// This file is the header for the @StackingActionBase@ class.

// There is no implementation file, as it is intended only as a base class.

// All action objects MUST inherit from this class.

// When you create an action object, you have the option to overload the
// following methods:

// The usual method in @G4UserStackingAction@ is @ClassifyNewTrack@. Here, you instead 
// supply a function for @killNewTrack@, which returns @true@ if the track should be killed
// and @false@ if the track should remain in the Urgent list (there is no capability to 
// put a track on the waiting list). See @artg4/geantInit/ArtG4StackingAction.hh@ and @.cc@ for 
// how this class is handled. 

// Include guard
#ifndef STACKING_ACTION_BASE_HH
#define STACKING_ACTION_BASE_HH

#include <string>
#include <iostream>

#include "artg4/actionBase/ActionBase.hh"

// Declarations of types we use as input parameters
class G4Track;


// Everything goes in the Art G4 namespace
namespace artg4 {

  class StackingActionBase : public ActionBase {
  public:
    // Constructor. The derived class must call this constructor. It takes a 
    // single string for the name of the action object.
    StackingActionBase(std::string myName)
      : ActionBase(myName)
    {}

    // Destructor
    virtual ~StackingActionBase(){}

    // killNewTrack (see above)
    virtual bool killNewTrack( const G4Track* ) { return false; }

  };
}


#endif // STACKING_ACTION_BASE_HH
