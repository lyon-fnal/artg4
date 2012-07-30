// Gm2EventAction.cc provides implementation of g-2's built-in event action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/Core/Gm2EventAction.hh"

// Other local includes
#include "gm2g4/art/ActionHolder.hh"
#include "gm2g4/Core/ActionBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::map;
using std::string;

// Called at the beginning of each event. Pass the call on to action objects
void gm2::Gm2EventAction::BeginOfEventAction(const G4Event * currentEvent)
{
  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their BeginOfEventAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> BeginOfEventAction(currentEvent);
  }
}

// Called at the end of each event. Call detectors to convert hits for the 
// event and pass the call on to the action objects.
void gm2::Gm2EventAction::EndOfEventAction(const G4Event * currentEvent)
{
  // Convert hits

    // Get the hit collection
  G4HCofThisEvent * HCE = currentEvent->GetHCofThisEvent();

  // Get a list of all the detectors registered for this run
  art::ServiceHandle<gm2::DetectorHolder> dh;
  std::map<std::string, gm2::DetectorBase*> 
    detectorMap = dh -> getDetectorMap();

  // Loop over the detectors and call their convertGeantToArtHits methods
  // to artize the event. 
  G4cout << " There are " << detectorMap.size() << " detectors we can artize "
	 << "hits for. Here we go..." << G4endl;
  std::map<std::string,gm2::DetectorBase*>::iterator it;
  for (it = detectorMap.begin(); it != detectorMap.end(); ++it) {
    gm2::DetectorBase * currentDetector = it -> second;
    G4cout << "Converting hits for detector of category: " 
	   << currentDetector -> category() << "." << G4endl;
    currentDetector -> convertGeantToArtHits(HCE);
  }

  // Now pass the action on to the action objects

  // Get a collection (map, actually) of the action objects registered for the
  // run.
  art::ServiceHandle<ActionHolder> actionHolder;
  map<string, ActionBase*> actions = actionHolder -> getActionMap();

  // Loop over the action objects and call their EndOfEventAction methods.
  map<string, ActionBase*>::iterator it;
  for (it = actions.begin(); it != actions.end(); ++it) {
    ActionBase * action = it -> second;
    action -> EndOfEventAction(currentEvent);
  }
}
