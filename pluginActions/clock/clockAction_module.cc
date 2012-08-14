// @clockAction@ is a producer that manages the specialized action 
// @ClockAction@. The producer is responsible for setting up the action and
// registering it with the @ActionHolder@ service. Furthermore, if the action
// creates some kind of Art-friendly hit class, this producer is responsible
// for getting the hits from the action object and putting them into the event
// or run, as necessary.

// Created by Tasha Arvanitis, July 2012

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

// Include more local files
#include "artg4/pluginActions/clock/ClockAction.hh"
#include "artg4/services/ActionHolder_service.hh"

// Put code in the Art G4 namespace
namespace artg4 {
  // This class is a producer, so it needs to inherit from @EDProducer@.
  class clockAction : public art::EDProducer {
  public:
    // The constructor constructs the action object.
    explicit clockAction(fhicl::ParameterSet const & p);
    virtual ~clockAction();

    // Register the action object with the ActionHolder.
    virtual void beginJob();

    // If you want to extract hits from the action object and put them in an
    // Art event, now is the time to do it! Even if you don't, this method
    // needs to be defined (even if it's just empty).
    virtual void produce(art::Event & e);

    // If you want to extract hits from the action object and put them in an
    // Art run, now is the time! 
    // virtual void endRun(art::Run & r);

  private:
    // Our action object here
    ClockAction * myAction_;

  };

}

// Constructor
artg4::clockAction::clockAction(fhicl::ParameterSet const & p)
  : myAction_(new ClockAction(p))
{
  // If you want to eventually add something to the event, you need to tell
  // Art now. 
  // If you're adding in something of type @T@, the appropriate command is:
  // produces<T>();
}

// Destructor
artg4::clockAction::~clockAction()
{
  // Clean up our only member datum
  delete myAction_;
}

// This method is called at the beginning of the Art job, which may encompass
// several runs. Setting the action here ensures that when the GEANT run
// manager is initialized at the beginning of the run, the action objects
// are all registered.
void artg4::clockAction::beginJob()
{
  art::ServiceHandle<ActionHolderService> ahs;
  ahs -> registerAction(myAction_);
}

// Definition of the required produce(...) method.
void artg4::clockAction::produce(art::Event & e)
{
  // If you want to get hits out of your action object and put them in the
  // art event, do it here. 

  // Note that to put a hit class into the art event, it must be defined
  // in a classes.h and classes_def.xml file, so that Art knows how to put it
  // into ROOT.
  
  // MyHitClass hits = _myAction -> someMethodToGetHits();
  // e.put(hits);
}

// Register the producer with Art.
using artg4::clockAction;
DEFINE_ART_MODULE(clockAction)
