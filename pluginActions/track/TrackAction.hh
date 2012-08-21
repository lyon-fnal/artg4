// TrackAction.hh provides the class declaration for the @TrackAction@ action
// object. It records information on each track as it is created, and can
// return this information in a collection.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef TRACK_ACTION_HH
#define TRACK_ACTION_HH

// Include the base class
#include "artg4/actionBase/TrackingActionBase.hh"

// Local includes
#include "artg4/pluginActions/track/TrackArtHit.hh"

// G4 includes
#include "G4Track.hh"

// Other library includes
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// Everything goes in the Art G4 namespace
namespace artg4 {

  class TrackAction : public TrackingActionBase {
  public:
    // A constructor that takes in a parameter set.
    TrackAction(fhicl::ParameterSet const & p);

    // Destructor
    virtual ~TrackAction() {};

    // Overload the PreUserTrackingAction method to initialize the track and
    // add it to our collection
    virtual void PreUserTrackingAction(const G4Track * currentTrack);

    // Our own method to return our collection of hits.
    // Note that once this method is called, this object will no longer
    // own the hits. Because we lose our collection of hits, this method
    // cannot be const.
    std::auto_ptr<TrackArtHitCollection> getArtHitsAndLoseOwnership();

  private:
    // A message logger for this action
    mf::LogInfo logInfo_;

    // Our collection of track hits
    std::auto_ptr<TrackArtHitCollection> myArtHits_;
  };
}

#endif // TRACK_ACTION_HH
