// ArtG4StackingAction.cc provides definitions for Art G4's built-in stacking
// action.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "artg4/geantInit/ArtG4StackingAction.hh"

// Other local includes
#include "artg4/services/ActionHolder_service.hh"

// Art
#include "art/Framework/Services/Registry/ServiceHandle.h"


// Called at the end of each step
G4ClassificationOfNewTrack artg4::ArtG4StackingAction::ClassifyNewTrack(const G4Track * currTrack)
{
  // Get the action holder service
  art::ServiceHandle<ActionHolderService> actionHolder;
  
  // Run userStackingAction
  bool killTrack = actionHolder -> killNewTrack(currTrack);
  
  G4ClassificationOfNewTrack trackDisposition = fUrgent;
  if ( killTrack ) {
    trackDisposition = fKill;
  }
  
  return trackDisposition;
}
