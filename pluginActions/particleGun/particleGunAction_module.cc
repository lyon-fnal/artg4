// @particleGunAction@ is a producer that manages the specialized action 
// @ParticleGunAction@. The producer is responsible for setting up the action 
// and registering it with the @ActionHolder@ service. Furthermore, if the 
// action creates some kind of Art-friendly hit class, this producer is 
// responsible for getting the hits from the action object and putting them 
// into the event or run, as necessary.

// Created by Tasha Arvanitis, July 2012

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

// Include more local files
#include "gm2g4/pluginActions/particleGun/ParticleGunAction.hh"
#include "gm2g4/art/ActionHolder.hh"

// Put code in the g-2 namespace
namespace gm2 {
  // This class is a producer, so it needs to inherit from @EDProducer@.
  class particleGunAction : public art::EDProducer {
  public:
    // The constructor constructs the action object.
    explicit particleGunAction(fhicl::ParameterSet const & p);
    virtual ~particleGunAction();

    // Register the action object with the ActionHolder.
    virtual void beginJob();

    // If you want to extract hits from the action object and put them in an
    // Art event, now is the time to do it! Even if you don't, this method
    // needs to be defined (even if it's just empty).
    virtual void produce(art::Event & e);

  private:
    // Our action object here
    ParticleGunAction * _myAction;

  };

}

// Constructor - we don't produce anything, so there's nothing interesting
// in the body.
gm2::particleGunAction::particleGunAction(fhicl::ParameterSet const & p)
  : _myAction(new ParticleGunAction(p))
{}

// Destructor
gm2::particleGunAction::~particleGunAction()
{
  // Clean up our only member datum
  delete _myAction;
}

// This method is called at the beginning of the Art job, which may encompass
// several runs. Setting the action here ensures that when the GEANT run
// manager is initialized at the beginning of the run, the action objects
// are all registered.
void gm2::particleGunAction::beginJob()
{
  art::ServiceHandle<ActionHolder> actions;
  actions -> registerAction(_myAction);
}

// Definition of the required produce(...) method - we don't produce anything,
// but it needs to be defined here.
void gm2::particleGunAction::produce(art::Event & e)
{}

// Register the producer with Art.
using gm2::particleGunAction;
DEFINE_ART_MODULE(particleGunAction)
