// ArtG4RunAction.cc provides definitions for Art G4's built-in run action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/Core/ArtG4RunAction.hh"

// Other local includes
#include "artg4/art/ActionHolder.hh"
#include "artg4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called at the beginning of each run:
void artg4::ArtG4RunAction::BeginOfRunAction(const G4Run * currentRun)
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
void artg4::ArtG4RunAction::EndOfRunAction(const G4Run * currentRun)
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
