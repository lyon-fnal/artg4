// ArtG4EventAction.cc provides implementation of Art G4's built-in event action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/geantInit/ArtG4EventAction.hh"

// Other local includes
#include "artg4/services/ActionHolder_service.hh"
#include "artg4/services/DetectorHolder_service.hh"
#include "artg4/Core/DetectorBase.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"

// C++
#include <map>

using std::map;
using std::string;

// Called at the beginning of each event. Pass the call on to action objects
void artg4::ArtG4EventAction::BeginOfEventAction(const G4Event * currentEvent)
{
  // Get the action holder service
  art::ServiceHandle<ActionHolderService> ahs;
  
  // Run beginOfEvent
  ahs -> beginOfEventAction(currentEvent);

}

// Called at the end of each event. Call detectors to convert hits for the 
// event and pass the call on to the action objects.
void artg4::ArtG4EventAction::EndOfEventAction(const G4Event * currentEvent)
{
  // Convert geant hits to art
  art::ServiceHandle<artg4::DetectorHolderService> dhs;
  dhs -> fillEventWithArtHits( currentEvent->GetHCofThisEvent() );
 
  // Run EndOfEventAction
  art::ServiceHandle<ActionHolderService> ahs;
  ahs -> endOfEventAction(currentEvent);
}
