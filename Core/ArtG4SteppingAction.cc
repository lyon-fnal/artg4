// ArtG4SteppingAction.cc provides definitions for Art G4's built-in stepping
// action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/Core/ArtG4SteppingAction.hh"

// Other local includes
#include "artg4/services/ActionHolder.hh"
#include "artg4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called at the end of each step
void artg4::ArtG4SteppingAction::UserSteppingAction(const G4Step * currentStep)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their UserSteppingAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> UserSteppingAction(currentStep, this);
  }
}
