// ParticleGunAction.hh provides the class declaration for the 
// @ParticleGunAction@ action object. This action object generates primaries
// by shooting them into the ring. 

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef PARTICLEGUN_ACTION_HH
#define PARTICLEGUN_ACTION_HH

// Include the base class
#include "artg4/actionBase/PrimaryGeneratorActionBase.hh"

// G4 includes
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "artg4/pluginActions/particleGun/GeneralParticleSource.hh"

// Other library includes
#include "fhiclcpp/ParameterSet.h"

// Everything goes in the Art G4 namespace
namespace artg4 {
  // Declare a class that will be passed in
  class G4VUserPrimaryGeneratorAction;

  class ParticleGunAction : public PrimaryGeneratorActionBase {
  public:
    // A constructor that takes in a parameter set.
    ParticleGunAction(fhicl::ParameterSet const & p);

    // Destructor
    virtual ~ParticleGunAction();

    // To generate primaries, we need to overload the GeneratePrimaries
    // method. 
    virtual void GeneratePrimaries(G4Event * anEvent);

  private:
    // Our particle source
    GeneralParticleSource * GPS_;

    // A message logger for this action object
  };
}

#endif // PARTICLEGUN_ACTION_HH
