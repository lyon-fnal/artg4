// Gm2PrimaryGeneratorAction.cc provides definitions for g-2's built-in
// primary generator action

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/Core/Gm2PrimaryGeneratorAction.hh"

// Other local-ish includes
#include "gm2g4/art/ActionHolder.hh"
#include "gm2g4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called to create primaries for an event
void gm2::Gm2PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
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
