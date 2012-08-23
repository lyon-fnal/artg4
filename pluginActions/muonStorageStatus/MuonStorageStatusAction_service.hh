// MuonStorageStatusActionService is the service that provides the muonStorageStatus action. It 
// records information on each muonStorageStatus as it is created, and can output this
// information in a collection
// To use this action, all you need to do is put it in the services section
// of the configuration file, like this:
// 
// services: { 
//   ...
//   user: {
//     MuonStorageStatusActionService: {}
//     ...
//   }
// }

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

// Include guard
#ifndef MUONSTORAGESTATUSACTION_SERVICE_HH
#define MUONSTORAGESTATUSACTION_SERVICE_HH

// Includes for general action service
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"
#include "art/Framework/Core/EDProducer.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art/Framework/Principal/Event.h"

// Get the base class
#include "actionBase/EventActionBase.hh"
#include "actionBase/RunActionBase.hh"
#include "actionBase/SteppingActionBase.hh"

// Other includes
#include "artg4/pluginActions/muonStorageStatus/EventArtHit.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4Step.hh"

namespace artg4 {


  // If anything external wants the muon tracking status, it can get it in
  // the form of a artg4::muonTrackingStatus::state object.
  namespace muonTrackingStatus {
    enum state { trackingMuon, storedMuon, lostMuon };
  }


  class MuonStorageStatusActionService 
    : public EventActionBase,
      public RunActionBase,
      public SteppingActionBase
  {
  public: 
    MuonStorageStatusActionService(fhicl::ParameterSet const&, 
				   art::ActivityRegistry&);
    virtual ~MuonStorageStatusActionService();

    // Use BeginOfEventAction (called at the beginning of each event,
    // after the primaries are generated).
    virtual void BeginOfEventAction(const G4Event * currEvent);

    // Use EndOfEventAction (last chance to extract information from the
    // event).
    virtual void EndOfEventAction(const G4Event * currEvent);

    // Use BeginOfRunAction (called at the beginning of each run, funnily 
    // enough).
    virtual void BeginOfRunAction(const G4Run * currRun);

    // Use EndOfRunAction (called at the end of each run).
    virtual void EndOfRunAction(const G4Run * currRun);

    // Use UserSteppingAction (called for each step).
    virtual void UserSteppingAction(const G4Step *currStep);

    // We want to add something to the event, so we need callArtProduces
    // and fillEventWithArtStuff.

    // Tell Art what we'll be adding to the event
    virtual void callArtProduces(art::EDProducer * producer);

    // Actually add the collection to the Art event.
    virtual void fillEventWithArtStuff(art::Event & e);

    // Increment the turn count (should only be called by turn counter SD)
    virtual void incrementTurnCount() {turns_++;}
  private:
    // Member data!

    // How many turns are required to call a muon stored?
    int turnsForStorage_;

    double stored_rmin_;
    double stored_rmax_;
    double stored_y_;

    // How many turns has the muon gone through so far?
    int turns_;

    // How many muons have been stored this run?
    int nStoredMuons_;

    // Has the current muon been stored?
    muonTrackingStatus::state currMuStorageStatus_;

    // Create an EventHit at the end of each event, to log whether the muon
    // in question was stored, and how many turns it took around the ring
    std::auto_ptr<EventArtHit> myArtHit_;

    // A message logger for this action
    mf::LogInfo logInfo_;
  };
}

#endif
