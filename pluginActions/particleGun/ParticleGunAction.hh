// ParticleGunAction.hh provides the class declaration for the 
// @ParticleGunAction@ action object. This action object generates primaries
// by shooting them into the ring. 

// Authors: Tasha Arvanitis, Adam Lyon
// Date: July 2012

// Include guard
#ifndef PARTICLEGUN_ACTION_HH
#define PARTICLEGUN_ACTION_HH

// Include the base class
#include "gm2g4/Core/ActionBase.hh"

// G4 includes
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "gm2g4/Core/g2GeneralParticleSource.hh"

// Other library includes
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// Everything goes in the g-2 namespace
namespace gm2 {
  class ParticleGunAction : public ActionBase {
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
    g2GeneralParticleSource * g2GPS;

    // A message logger for this action object
    mf::LogInfo _logInfo
  };
}

#endif // PARTICLEGUN_ACTION_HH
