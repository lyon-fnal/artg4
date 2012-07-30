// TrackAction.cc provides the implementation for an action object that 
// records information on each particle track as it is created

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include header
#include "gm2g4/pluginActions/track/TrackAction.hh"

#include "gm2g4/pluginActions/track/TrackArtHit.hh"

using std::string;

// Constructor takes a parameter set, calls the base class's constructor, and
// initializes member data
gm2::TrackAction::TrackAction(fhicl::ParameterSet const & p)
  : ActionBase(p.get<string>("name", "track")),
    // Initialize our message logger
    _logInfo("TRACKACTION")
{}

// Overload the PreUserTrackingAction method to initialize the track and
// add it to our collection
void gm2::TrackAction::PreUserTrackingAction(const G4Track * currentTrack)
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

  tr.volumeUID = get_uid(currentTrack->GetVolume());

  G4ThreeVector pos = currentTrack->GetPosition();
  tr.rhat = std::sqrt(pos.x()*pos.x() + pos.z()*pos.z()) - R_magic();
  tr.vhat = pos.y();
  tr.theta = std::atan2(pos.z(),pos.x());
  if( tr.theta < 0 )
    tr.theta+= 2.*M_PI;
  tr.time = currentTrack->GetGlobalTime();

  G4ThreeVector mom = currentTrack->GetMomentum();
  tr.p = mom.mag();
  tr.prhat = 
    (mom.x()*pos.x() + mom.z()*pos.z())/sqrt(pos.x()*pos.x()+pos.z()*pos.z())/tr.p;
  tr.pvhat = mom.y()/mom.mag();

  // Add the hit to our collection
  _myArtHits.push_back(tr);
}

// Our own method to return our collection of hits.
inline TrackArtHitCollection & getArtHits() const
{
  return _myArtHits;
}
