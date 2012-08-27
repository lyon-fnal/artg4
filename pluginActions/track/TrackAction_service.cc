// This file provides the implementation for an action object that records
// information on each particle track as it is created.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

#include "artg4/pluginActions/track/TrackAction_service.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/ActionHolder_service.hh"

using std::string;

artg4::TrackActionService::TrackActionService(fhicl::ParameterSet const & p, 
					      art::ActivityRegistry &)
  : TrackingActionBase(p.get<string>("name","track")),
    myArtHits_(),
    logInfo_("TrackAction")
{
  // Register ourselves with the ActionHolder
  art::ServiceHandle<ActionHolderService> actionHolder;

  actionHolder -> registerAction(this);
}

// Destructor
artg4::TrackActionService::~TrackActionService()
{}


// Overload the PreUserTrackingAction method to initialize the track and
// add it to our collection
void artg4::TrackActionService::
preUserTrackingAction(const G4Track * currentTrack)
{
  // Ignore tracks for xtal volumes
  if( currentTrack->GetVolume()->GetName().find( "xtal" ) !=
      std::string::npos ) {
    return ;
  }
  
  // Create a hit
  TrackArtHit tr;
  
  // Fill it based on the track.
  tr.trackType = std::string(currentTrack->GetDefinition()->GetParticleName());
  tr.trackID = currentTrack->GetTrackID();
  tr.parentTrackID = currentTrack->GetParentID();

  // Omit turns for now
  //  tr.turn = turnCounter::getInstance().turns();

  // We haven't yet set up the 
  //  tr.volumeUID = get_uid(currentTrack->GetVolume());

  G4ThreeVector pos = currentTrack->GetPosition();
  // BUG: TrackAction is g-2 specific because of this 'R_magic' reference.
  //      This could be eliminated by generalizing this action object, but
  //      since we want to get the same information in the ROOT file, this
  //      will just have to be moved out of artg4.
  tr.rhat = std::sqrt(pos.x()*pos.x() + pos.z()*pos.z());// - R_magic();
  tr.vhat = pos.y();
  tr.theta = std::atan2(pos.z(),pos.x());
  if( tr.theta < 0 )
    tr.theta+= 2.*M_PI;
  tr.time = currentTrack->GetGlobalTime();

  G4ThreeVector mom = currentTrack->GetMomentum();
  tr.p = mom.mag();
  tr.prhat = 
    (mom.x()*pos.x() + mom.z()*pos.z()) /
    sqrt(pos.x()*pos.x()+pos.z()*pos.z()) / 
    tr.p;
  tr.pvhat = mom.y()/mom.mag();

  // Add the hit to our collection
  (myArtHits_.get())->push_back(tr);
}

// Tell Art what we produce
void artg4::TrackActionService::callArtProduces(art::EDProducer * producer)
{
  producer -> produces<TrackArtHitCollection>();
}

// Add our collection to the Art event.
// ???
// I believe that when we do this, we lose possession of the collection, which
// is a distinctly good thing.
// ???
void artg4::TrackActionService::fillEventWithArtStuff(art::Event & e)
{
  e.put(myArtHits_);
}

using artg4::TrackActionService;
DEFINE_ART_SERVICE(TrackActionService)
