// Declarations for the @ActionHolderService@ Art service.

// @ActionHolderService@ is a globally-accessible service that manages the action
// objects for a simulation. An action object has a multitude of hooks into
// various points during event creation and processing. All action objects
// must be registered with this service in order to function. 

// Any class can @#include@ and access the @ActionHolderService@ service to get either
// a collection of registered action objects or a specific action object given
// a name.

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef ACTION_HOLDER_SERVICE_HH
#define ACTION_HOLDER_SERVICE_HH

// Includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"

#include <map>

class G4Run;
class G4Event;
class G4Track;
class G4Step;

#include "artg4/actionBase/ActionBase.hh"
#include "artg4/actionBase/RunActionBase.hh"
#include "artg4/actionBase/EventActionBase.hh"
#include "artg4/actionBase/TrackingActionBase.hh"
#include "artg4/actionBase/SteppingActionBase.hh"
#include "artg4/actionBase/StackingActionBase.hh"
#include "artg4/actionBase/PrimaryGeneratorActionBase.hh"

// Everything for the Art G4 simulation goes in the @artg4@ namespace
namespace artg4 {
   
  class ActionHolderService {
  public:
    // Constructor for ActionHolderService
    ActionHolderService(fhicl::ParameterSet const &, art::ActivityRegistry&);

    // This method registers the passed action object with the service
    void registerAction(RunActionBase * const action);
    void registerAction(EventActionBase* const action);
    void registerAction(TrackingActionBase* const action);
    void registerAction(SteppingActionBase* const action);
    void registerAction(StackingActionBase* const action);
    void registerAction(PrimaryGeneratorActionBase* const action);
    
    // Get an action
    ActionBase* getAction(std::string name, RunActionBase* out);
    ActionBase* getAction(std::string name, EventActionBase* out);
    ActionBase* getAction(std::string name, TrackingActionBase* out);
    ActionBase* getAction(std::string name, SteppingActionBase* out);
    ActionBase* getAction(std::string name, StackingActionBase* out);
    ActionBase* getAction(std::string name, PrimaryGeneratorActionBase* out);
    
    // h3. Art-specific methods

    // Call ActionBase::initialize for each action
    void initialize();

    // Tell each action to notify Art of what it will be producing.
    void callArtProduces(art::EDProducer * prod);

    // Tell each action to dump anything it likes into the Art event
    void fillEventWithArtStuff();

    // Set/get the current Art event
    void setCurrArtEvent(art::Event & e) { currentArtEvent_ = &e; }
    art::Event & getCurrArtEvent() { return (*currentArtEvent_); }

    // h3. Action methods

    // h4. Run Actions
    void beginOfRunAction(const G4Run* );    
    void endOfRunAction(const G4Run* );
    
    // h4. Event Actions
    void beginOfEventAction(const G4Event* );
    void endOfEventAction(const G4Event* );
    
    // h4. Tracking actions
    void preUserTrackingAction(const G4Track* );
    void postUserTrackingAction(const G4Track* );
    
    // h4. Stepping actions
    void userSteppingAction(const G4Step* );
    
    // h4. Stacking actions
    bool killNewTrack(const G4Track* );
    
    // h4. Primary Generator actions
    void generatePrimaries(G4Event*);
    

  private:
        
    // A collection of all our actions, arranged by name
    std::map<std::string, RunActionBase*> runActionsMap_;
    std::map<std::string, EventActionBase*> eventActionsMap_;
    std::map<std::string, TrackingActionBase*> trackingActionsMap_;
    std::map<std::string, SteppingActionBase*> steppingActionsMap_;
    std::map<std::string, StackingActionBase*> stackingActionsMap_;
    std::map<std::string, PrimaryGeneratorActionBase*> primaryGeneratorActionsMap_;

    // Hold on to the current Art event
    art::Event * currentArtEvent_;

    // An uber-collection of all registered actions, arranged by name
    std::map<std::string, ActionBase*> allActionsMap_;
        
    // Register the action 
    template <typename A>
    void doRegisterAction(A * const action, std::map<std::string, A *>& actionMap);
    
    // Get an action
    template <typename A>
    A* doGetAction(std::string name, std::map<std::string, A*>& actionMap);

  };
}

#endif // ACTION_HOLDER_HH
