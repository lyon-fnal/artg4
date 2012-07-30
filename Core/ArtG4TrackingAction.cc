// Gm2TrackingAction.cc provides definitions for g-2's built-in tracking action

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/Core/Gm2TrackingAction.hh"

// Other local includes
#include "gm2g4/art/ActionHolder.hh"
#include "gm2g4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::string;
using std::map;

// Called after the creation of a track and before it's actually simulated
void gm2::Gm2TrackingAction::PreUserTrackingAction(const G4Track * currTrack)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their PreUserTrackingAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> PreUserTrackingAction(currTrack);
  }
}

// Called once a track has been stopped
void gm2::Gm2TrackingAction::PostUserTrackingAction(const G4Track * currTrack)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their PostUserTrackingAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> PostUserTrackingAction(currTrack);
  }
}
