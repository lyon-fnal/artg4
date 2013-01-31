// Provides the implementation for the @ActionHolderService@ service.
// For more comprehensive documentation, see the header file ActionHolderService.hh

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Includes
#include "artg4/services/ActionHolder_service.hh"

#include "art/Framework/Services/Registry/ServiceMacros.h"

#include "messagefacility/MessageLogger/MessageLogger.h"

#include "artg4/actionBase/RunActionBase.hh"
#include "artg4/actionBase/EventActionBase.hh"
#include "artg4/actionBase/TrackingActionBase.hh"
#include "artg4/actionBase/SteppingActionBase.hh"
#include "artg4/actionBase/StackingActionBase.hh"
#include "artg4/actionBase/PrimaryGeneratorActionBase.hh"

#include <algorithm>

// Don't type 'std::' all the time...
using std::string;
using std::map;
using std::pair;

// Message category
static std::string msgctg = "ActionHolderService";

// Constructor doesn't do much with the passed arguments, but does initialize
// the logger for the service
artg4::ActionHolderService::ActionHolderService(fhicl::ParameterSet const&,
						art::ActivityRegistry&) :
  runActionsMap_(),
  eventActionsMap_(),
  trackingActionsMap_(),
  steppingActionsMap_(),
  stackingActionsMap_(),
  primaryGeneratorActionsMap_(),
  currentArtEvent_(nullptr),
  allActionsMap_()
{}


// Register actions
template <typename A>
void artg4::ActionHolderService::doRegisterAction(A * const action, 
						  std::map<std::string, A *>& actionMap) 
{
  LOG_DEBUG(msgctg) << "Registering action " << action->myName();
  
  // Check if the name exists in the specific action map
  if ( 0 == actionMap.count( action->myName() ) ) {
    // Add the action!
    actionMap.insert(
                     pair<string, A *>( action->myName(), action )
                     );

    // Now, check whether the name exists in the overall map of all the actions
    // If so, move on (don't throw an exception, since a single action may need
    // to register in multiple maps). Otherwise, add it.
    if ( 0 == allActionsMap_.count( action->myName() ) ) {
      allActionsMap_.insert( 
        pair<string, ActionBase*>( action->myName(), dynamic_cast<ActionBase*>(action) ));
    }
  }
 
  else {
    // We already have this action in the specific action map - this is bad!
    throw cet::exception("ActionHolderService")
    << "Duplicate action named " << action->myName() << ".\n";
  }

}

void artg4::ActionHolderService::registerAction(RunActionBase * const action) {
  doRegisterAction(action, runActionsMap_);
}

void artg4::ActionHolderService::registerAction(EventActionBase * const action) {
  doRegisterAction(action, eventActionsMap_);
}

void artg4::ActionHolderService::registerAction(TrackingActionBase * const action) {
  doRegisterAction(action, trackingActionsMap_);
}

void artg4::ActionHolderService::registerAction(SteppingActionBase * const action) {
  doRegisterAction(action, steppingActionsMap_);
}

void artg4::ActionHolderService::registerAction(StackingActionBase * const action) {
  doRegisterAction(action, stackingActionsMap_);
}

void artg4::ActionHolderService::registerAction(PrimaryGeneratorActionBase * const action) {
  doRegisterAction(action, primaryGeneratorActionsMap_);
}

template <typename A>
A* artg4::ActionHolderService::doGetAction(std::string name, std::map<std::string, A*>& actionMap) {
  
  // Make a typedef
  typedef typename std::map<std::string, A*>::const_iterator map_const_iter;
  
  // Find the action corresponding to the passed in name in the map
  map_const_iter actionIter = actionMap.find(name);
  if ( actionIter == actionMap.end() ) {
    throw cet::exception("ActionHolderService") << "No action found with name "
        << name << ".\n";
  }
  return actionIter->second;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, RunActionBase* out) {
  out = doGetAction(name, runActionsMap_);
  return out;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, EventActionBase* out) {
  out = doGetAction(name, eventActionsMap_);
  return out;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, TrackingActionBase* out) {
  out = doGetAction(name, trackingActionsMap_);
  return out;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, SteppingActionBase* out) {
  out = doGetAction(name, steppingActionsMap_);
  return out;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, StackingActionBase* out) {
  out = doGetAction(name, stackingActionsMap_);
  return out;
}

artg4::ActionBase* artg4::ActionHolderService::getAction(std::string name, PrimaryGeneratorActionBase* out) {
  out = doGetAction(name, primaryGeneratorActionsMap_);
  return out;
}

// h3. Art-specific methods
void artg4::ActionHolderService::callArtProduces(art::EDProducer * prod)
{

  // Loop over the "uber" activity map and call @callArtProduces@ on each
  for ( auto entry : allActionsMap_) {
    (entry.second)->callArtProduces(prod);
  }
}

void artg4::ActionHolderService::initialize() {
  for ( auto entry : allActionsMap_ ) {
    (entry.second)->initialize();
  }
}

void artg4::ActionHolderService::fillEventWithArtStuff()
{

  // Loop over the "uber" activity map and call @fillEventWithArtStuff@ on each
  for ( auto entry : allActionsMap_ ) {
    (entry.second)->fillEventWithArtStuff(getCurrArtEvent());
  }
}

void artg4::ActionHolderService::fillRunWithArtStuff()
{
  // Loop over the run activities and call @fillRunWithArtStuff@ on each
  for ( auto entry : runActionsMap_ ) {
    (entry.second)->fillRunWithArtStuff(getCurrArtRun());
  }
}

// h2. Action methods

// I tried to be good and use @std::for_each@ but it got really messy very 
// quickly. Oh well. 

// h3. Run action methods
void artg4::ActionHolderService::beginOfRunAction(const G4Run* theRun) {
  
  // Loop over the runActionsMap and call @beginOfRunAction@ on each
  for ( auto entry : runActionsMap_ ) {
    (entry.second)->beginOfRunAction(theRun);
  }
}

void artg4::ActionHolderService::endOfRunAction(const G4Run* theRun) {

  // Loop voer the runActionsMap and call @endOfRunAction@ on each
  for ( auto entry : runActionsMap_ ) {
    (entry.second)->endOfRunAction(theRun);
  }
}

// h3. Event action methods
void artg4::ActionHolderService::beginOfEventAction(const G4Event* theEvent) {
  for ( auto entry : eventActionsMap_ ) {
    (entry.second)->beginOfEventAction(theEvent);
  }
}

void artg4::ActionHolderService::endOfEventAction(const G4Event* theEvent) {
  for ( auto entry : eventActionsMap_ ) {
    (entry.second)->endOfEventAction(theEvent);
  }
}

// h3. Tracking action methods
void artg4::ActionHolderService::preUserTrackingAction(const G4Track* theTrack) {
  for ( auto entry : trackingActionsMap_ ) {
    (entry.second)->preUserTrackingAction(theTrack);
  }
 
}

void artg4::ActionHolderService::postUserTrackingAction(const G4Track* theTrack) {
  for (auto entry : trackingActionsMap_ ) {
    (entry.second)->postUserTrackingAction(theTrack);
  }
}

// h3. Stepping actions
void artg4::ActionHolderService::userSteppingAction(const G4Step* theStep) {
  for ( auto entry : steppingActionsMap_ ) {
    (entry.second)->userSteppingAction(theStep);
  }
}

// h3. Stacking actions
bool artg4::ActionHolderService::killNewTrack(const G4Track* newTrack) {
  
  bool killTrack = false;

  for (auto entry : stackingActionsMap_) {
    if ( (entry.second)->killNewTrack(newTrack) ) {
      killTrack = true;
      break;
    }
  }
  
  return killTrack;
}
  
// h3. Primary generator actions
void artg4::ActionHolderService::generatePrimaries(G4Event* theEvent) {
  for ( auto entry : primaryGeneratorActionsMap_ ) {
    (entry.second)->generatePrimaries(theEvent);
  }
}


// Register the service with Art
using artg4::ActionHolderService;
DEFINE_ART_SERVICE(ActionHolderService)
