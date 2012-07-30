// Gm2SteppingAction.cc provides definitions for g-2's built-in stepping
// action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/Core/Gm2SteppingAction.hh"

// Other local includes
#include "gm2g4/art/ActionHolder.hh"
#include "gm2g4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called at the end of each step
void gm2::Gm2SteppingAction::UserSteppingAction(const G4Step * currentStep)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their UserSteppingAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> UserSteppingAction(currentStep);
  }
}
