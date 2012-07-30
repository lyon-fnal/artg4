// ArtG4PrimaryGeneratorAction.cc provides definitions for Art G4's built-in
// primary generator action

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/Core/ArtG4PrimaryGeneratorAction.hh"

// Other local-ish includes
#include "artg4/art/ActionHolder.hh"
#include "artg4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called to create primaries for an event
void artg4::ArtG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their GeneratePrimaries methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> GeneratePrimaries(anEvent);
  }
}
