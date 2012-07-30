// Gm2RunAction.cc provides definitions for g-2's built-in run action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/Core/Gm2RunAction.hh"

// Other local includes
#include "gm2g4/art/ActionHolder.hh"
#include "gm2g4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called at the beginning of each run:
void gm2::Gm2RunAction::BeginOfRunAction(const G4Run * currentRun)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their BeginOfRun methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> BeginOfRunAction(currentRun);
  }
}

// Called at the end of each run:
void gm2::Gm2RunAction::EndOfRunAction(const G4Run * currentRun)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their EndOfRun methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> EndOfRunAction(currentRun);
  }
}
