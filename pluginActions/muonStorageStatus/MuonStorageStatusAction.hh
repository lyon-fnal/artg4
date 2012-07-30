// MuonStorageStatusAction.hh provides the class declaration for the 
// @MuonStorageStatusAction@ action object, which manages the turn counter
// and keeps track of whether the current muon has been stored and how many
// total muons have been stored in the run.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// The parameter set passed in to the constructor of this object must contain
// the following parameters:
// - name (string): a name describing the action. It is highly recommended
//       that you stick with the default name for this class.
//       Default is 'muonstoragestatus'.

// - turns_for_storage (int): The number of turns required to consider a 
//       muon 'stored'.
//       Default is 2160 (5 muon decay lifetimes in the lab frame).

// Include guard
#ifndef MUON_STORAGE_ACTION_HH
#define MUON_STORAGE_ACTION_HH

// Include the base class
#include "artg4/Core/ActionBase.hh"

// Include our event hit class
#include "artg4/pluginActions/muonStorageStatus/EventHit.hh"

// G4 includes
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Step.hh"

// Other includes
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// Everything goes in the Art G4 namespace
namespace artg4 {

  // If anything external wants the muon tracking status, it can get it in
  // the form of a artg4::muonTrackingStatus::state object.
  namespace muonTrackingStatus {
    enum state { trackingMuon, storedMuon, lostMuon };
  }
  
  class MuonStorageStatusAction : public ActionBase {
  public:
    // Constructor takes in a parameter set.
    MuonStorageStatusAction(fhicl::ParameterSet const & p);

    // Destructor
    virtual ~MuonStorageStatusAction() {};

    // Use BeginOfEventAction (called at the beginning of each event,
    // after the primaries are generated).
    void BeginOfEventAction(const G4Event * currEvent);

    // Use EndOfEventAction (last chance to extract information from the
    // event).
    void EndOfEventAction(const G4Event * currEvent);

    // Use BeginOfRunAction (called at the beginning of each run, funnily 
    // enough).
    void BeginOfRunAction(const G4Run * currRun);

    // Use EndOfRunAction (called at the end of each run).
    void EndOfRunAction(const G4Run * currRun);

    // Use UserSteppingAction (called for each step).
    void UserSteppingAction(const G4Step *currStep);

    // Return our art hit for the event.
    EventHit getArtHit();

  private:
    // Member data!

    // How many turns are required to call a muon stored?
    int _turnsForStorage;

    // How many turns has the muon gone through so far?
    int _turns;

    // How many muons have been stored this run?
    int _nStoredMuons;

    // Has the current muon been stored?
    muonTrackingStatus::state _currMuStorageStatus;

    // Create an EventHit at the end of each event, to log whether the muon
    // in question was stored, and how many turns it took around the ring
    EventHit _myHit;
  };
};



#endif // MUON_STORAGE_ACTION_HH
