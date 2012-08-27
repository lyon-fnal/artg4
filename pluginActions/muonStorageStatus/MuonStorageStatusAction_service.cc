// This file provides the class declaration for the 
// @MuonStorageStatusAction@ action object, which manages the turn counter
// and keeps track of whether the current muon has been stored and how many
// total muons have been stored in the run.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: August 2012

// The parameter set passed in to the constructor of this object must contain
// the following parameters:
// - name (string): a name describing the action. It is highly recommended
//       that you stick with the default name for this class.
//       Default is 'muonstoragestatus'.

// - turns_for_storage (int): The number of turns required to consider a 
//       muon 'stored'.
//       Default is 2160 (5 muon decay lifetimes in the lab frame).

// - stored_rmin (double): The minimum radius of a muon for it to be considered
//       'stored', in meters.
//       Default is 7.0 m.

// - stored_rmax (double): The maximum radius of a muon for it to be considered
//       'stored', in meters.
//       Default is 8.0 m.

// - stored_y (double): The maximum distance (in meters) a muon can deviate
//       vertically from a centered path to still be considered stored.
//       Default is 0.074 m.


#include "artg4/pluginActions/muonStorageStatus/MuonStorageStatusAction_service.hh"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "artg4/services/ActionHolder_service.hh"

// G4 includes
#include "globals.hh"
#include "G4Step.hh"
#include "G4Track.hh"

using std::string;

artg4::MuonStorageStatusActionService::
MuonStorageStatusActionService(fhicl::ParameterSet const & p, 
			       art::ActivityRegistry &)
  : EventActionBase(p.get<string>("name","muonStorageStatus")),
    RunActionBase(p.get<string>("name","muonStorageStatus")),
    SteppingActionBase(p.get<string>("name","muonStorageStatus")),
    turnsForStorage_(p.get<double>("turns_for_storage",2160)),
    stored_rmin_(p.get<double>("stored_rmin")*m),
    stored_rmax_(p.get<double>("stored_rmax")*m),
    stored_y_(p.get<double>("stored_y")*m),
    turns_(0),
    nStoredMuons_(0),
    currMuStorageStatus_(muonTrackingStatus::trackingMuon),
    myArtHit_(),
    logInfo_("MuonStorageStatusAction")
{
  // Register ourselves with the ActionHolder
  art::ServiceHandle<ActionHolderService> actionHolder;

  EventActionBase * eventPtr = dynamic_cast<EventActionBase*>(this);
  RunActionBase * runPtr = dynamic_cast<RunActionBase*>(this);
  SteppingActionBase * steppingPtr = dynamic_cast<SteppingActionBase*>(this);
  
  // We need to register ourselves as each base class...
  actionHolder -> registerAction(eventPtr);
  actionHolder -> registerAction(runPtr);
  actionHolder -> registerAction(steppingPtr);
}

// Destructor
artg4::MuonStorageStatusActionService::~MuonStorageStatusActionService()
{}

// Use BeginOfEventAction (called at the beginning of each event,
// after the primaries are generated).
void artg4::MuonStorageStatusActionService::
beginOfEventAction(const G4Event * currEvent)
{
  // Initialization per event
  currMuStorageStatus_ = muonTrackingStatus::trackingMuon;

  // Reset the turn counter
  turns_ = 0;
  //turnCounter::getInstance().reset();
}

// Use EndOfEventAction (last chance to extract information from the
// event).
void artg4::MuonStorageStatusActionService::
endOfEventAction(const G4Event * currEvent)
{
  bool muWasStored = (currMuStorageStatus_ == muonTrackingStatus::storedMuon ? 
		      true :
		      false);

  // Create the 'event hit' for this event  
  myArtHit_ = std::auto_ptr<EventArtHit>(new EventArtHit(turns_, muWasStored));

  // Get the current art event and add our event hit to it
  art::ServiceHandle<ActionHolderService> actionHolder;
  art::Event & e = actionHolder -> getCurrArtEvent();

  e.put(myArtHit_);
}

// Use BeginOfRunAction (called at the beginning of each run, funnily 
// enough).
void artg4::MuonStorageStatusActionService::
beginOfRunAction(const G4Run * currRun)
{
  // Initialization per run
  nStoredMuons_ = 0;
}

// Use EndOfRunAction (called at the end of each run).
void artg4::MuonStorageStatusActionService::
endOfRunAction(const G4Run * currRun)
{
  // Calculate some information about the run
  double totalEvents = currRun -> GetNumberOfEvent();
  double captureEfficiency = (nStoredMuons_ * 100.) / totalEvents;
  double dcE = std::sqrt(nStoredMuons_)*100. / totalEvents;

  // Print out the information
  logInfo_ << "\n  Muons injected : "
	   << totalEvents << "\n"
	   << "  Muons stored : "
	   << nStoredMuons_ << "\n"
	   << "  Capture Efficiency : ("
	   << captureEfficiency << " +/- "
	   << dcE << ")%\n\n";
}

// Use UserSteppingAction (called for each step).
// * Kills tracks if they wander into the laboratory or the inflector mandrel.
// * Kills a track and ends the event if the muon survives for a sufficient number of turns.
// * Kills a track if it wanders too far outside the storage volume
void artg4::MuonStorageStatusActionService::
userSteppingAction(const G4Step *currStep)
{
  // Get the current track
  G4Track * currTrack = currStep -> GetTrack();

  string currVolumeName = currTrack -> GetVolume() -> GetName();

  // Check if the particle has entered the inflector mandrel or the lab 
  // itself. If so, kill it. Also check whether the particle in question is 
  // a primary. If so, log its storage status.
  if (currVolumeName== "InflectorMandrel" || currVolumeName== "theLaboratory") {
    if (currTrack -> GetTrackID() == 1) {
      // We have a primary - log it as not stored
      currMuStorageStatus_ = muonTrackingStatus::lostMuon;
    }
  
    // Kill the track.
    currTrack -> SetTrackStatus(fStopAndKill);
  } 

  // Check whether the muon has gone around the ring enough to be counted as 
  // stored. If so, log it and kill the track.
  if (turns_ >= turnsForStorage_) {
    currMuStorageStatus_ = muonTrackingStatus::storedMuon;
    nStoredMuons_++;
    
    currTrack -> SetTrackStatus(fStopAndKill);
  }

  // Check if we're still in range to consider the particle stored
  G4ThreeVector const currentPos = 
    currStep -> GetPostStepPoint() -> GetPosition();
  G4double const posX = currentPos.getX();
  G4double const posY = currentPos.getY();
  G4double const posZ = currentPos.getZ();
  G4double const posR = sqrt(posX*posX + posZ*posZ);
  
  if(posR < stored_rmin_ || posR > stored_rmax_ || std::abs(posY) > stored_y_) {
    currMuStorageStatus_ = muonTrackingStatus::lostMuon;
  }
}

// Tell Art what we produce
void artg4::MuonStorageStatusActionService::
callArtProduces(art::EDProducer * producer)
{
  producer -> produces<EventArtHit>();
}

// Add our information to the Art event.

// ???
// I believe that when we do this, we lose possession of the collection, which
// is a distinctly good thing.
// ???
void artg4::MuonStorageStatusActionService::fillEventWithArtStuff(art::Event &e)
{
  e.put(myArtHit_);
}

using artg4::MuonStorageStatusActionService;
DEFINE_ART_SERVICE(MuonStorageStatusActionService)
